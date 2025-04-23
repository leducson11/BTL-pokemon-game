#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <algorithm>
#include <random>

#include "graphics.h"
#include "defs.h"
#include "logic.h"

using namespace std;

// Constructor
    Memory::Memory()
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                board[i][j].x = startX + j * (cellWidth + MARGIN_X);
                board[i][j].y = startY + i * (cellHeight + MARGIN_Y);
                board[i][j].w = cellWidth;
                board[i][j].h = cellHeight;
                isFlipped[i][j] = false;
                matched[i][j] = false;
                openBall[i][j] = nullptr;
            }
        }
        closeBall = nullptr;
    }
// Destructor
    Memory::~Memory()
    {
        for(int i = 0; i < rows; i++)
        {
            for(int j = 0; j < cols; j++)
            {
                if(openBall[i][j] != nullptr)
                {
                    SDL_DestroyTexture(openBall[i][j]);
                    openBall[i][j] = nullptr;
                }
            }
        }

        if(closeBall != nullptr)
        {
            SDL_DestroyTexture(closeBall);
            closeBall = nullptr;
        }
    }

void loadTextures(Graphics& graphics, Memory& memory)
{
    const char* ballImages[] =
    {
        "image/poke1.png", "image/poke2.png",
        "image/poke3.png", "image/poke4.png",
        "image/poke5.png", "image/poke6.png",
        "image/poke7.png", "image/poke8.png"
    };

    vector<int> imageIds;
    for(int i = 0; i < numImages; i++)
    {
        imageIds.push_back(i);
        imageIds.push_back(i);
    }

    random_device rd;
    mt19937 gen(rd());
    shuffle(imageIds.begin(), imageIds.end(), gen);

    int k = 0;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            int id = imageIds[k];
            memory.imageId[i][j] = id;

            memory.openBall[i][j] = graphics.loadTexture(ballImages[id]);
            if (!memory.openBall[i][j])
            {
                cerr << "Failed to load texture: " << ballImages[k] << endl;
            }
            k++;
            //memory.imageId[i][j] = k / 2;
        }
    }
}

    bool checkWin(bool matched[rows][cols])
{
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            if (!matched[i][j]) return false;
    return true;
}

void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true)
    {
        if ( SDL_PollEvent(&e) != 0 && (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
            return;
        SDL_Delay(100);
    }
}

void initGame(){

    Graphics graphics;
    graphics.init();

    SDL_Texture* background = graphics.loadTexture("image/p3.png_large");
    if (!background)
    {
        cerr << "Failed to load background!" << endl;
        //return 1;
    }
    SDL_Texture* youwin = graphics.loadTexture("image/youwin.png");
    if (!youwin)
    {
        cerr << "Failed to load win image!" << endl;
    }
    graphics.prepareScene(background);
    graphics.presentScene();
    //waitUntilKeyPressed();

    Memory memory;
    loadTextures(graphics, memory);
    memory.closeBall = graphics.loadTexture("image/ball2.png");

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            memory.isFlipped[i][j] = false;
        }
    }

    SDL_Event event;
    bool quit = false;
    while (! quit)
    {
        graphics.prepareScene(background);
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                if (memory.isFlipped[i][j] || memory.matched[i][j])
                {
                    //SDL_RenderCopy(graphics.renderer, background, &memory.board[i][j], &memory.board[i][j]);
                    SDL_RenderCopy(graphics.renderer, memory.openBall[i][j], NULL, &memory.board[i][j]);
                }
                else
                {
                    SDL_RenderCopy(graphics.renderer, memory.closeBall, NULL, &memory.board[i][j]);
                }
            }
        }

        //Hiển thị lên màn hình
        graphics.presentScene();
        SDL_PollEvent(&event);
        switch (event.type)
        {
        case SDL_QUIT:
            quit = true;
            break;
        case SDL_MOUSEBUTTONDOWN:
            int mouseX, mouseY;
            SDL_GetMouseState(&mouseX, &mouseY);
            cerr << "Mouse clicked at: " << mouseX << ", " << mouseY << endl;
            for (int i = 0; i < rows; i++)
            {
                for (int j = 0; j < cols; j++)
                {
                    if (mouseX >= memory.board[i][j].x &&
                            mouseX <= memory.board[i][j].x + memory.board[i][j].w &&
                            mouseY >= memory.board[i][j].y &&
                            mouseY <= memory.board[i][j].y + memory.board[i][j].h)
                    {
                        cerr << "Clicked on card: [" << i << "][" << j << "]" << endl;
                        if(!memory.isFlipped[i][j] && memory.openedCount < 2 && !memory.matched[i][j])
                        {
                            memory.isFlipped[i][j] = true;
                            // Lưu vị trí ô được mở
                            memory.openedCards[memory.openedCount] = {i, j};
                            memory.openedCount++;

                            if (memory.openedCount == 2)
                            {
                                memory.isComparing = true;
                                memory.compareStartTime = SDL_GetTicks();
                            }
                        }
                    }
                }
            }
            break;
        }

        if (memory.isComparing && SDL_GetTicks() - memory.compareStartTime > memory.COMPARE_DELAY)
        {
            int i1 = memory.openedCards[0].x;
            int j1 = memory.openedCards[0].y;
            int i2 = memory.openedCards[1].x;
            int j2 = memory.openedCards[1].y;

            cerr << "Comparing cards: [" << i1 << "][" << j1 << "] vs ["
                 << i2 << "][" << j2 << "]" << endl;

            if (memory.imageId[i1][j1] == memory.imageId[i2][j2])
            {
                memory.matched[i1][j1] = true;  // Đánh dấu đã ghép đúng
                memory.matched[i2][j2] = true;
                cerr << "Cards match!" << endl;
            }
            else
            {
                memory.isFlipped[i1][j1] = false;
                memory.isFlipped[i2][j2] = false;
                cerr << "Cards don't match!" << endl;
            }

            // Reset trạng thái
            memory.openedCount = 0;
            memory.isComparing = false;  //Đặt lại sau khi so sánh xong
        }



        if (checkWin(memory.matched))
        {
            cerr << "You win!" << endl;
            graphics.prepareScene(background);
            for (int i = 0; i < rows; i++)
            {
                for (int j = 0; j < cols; j++)
                {
                    SDL_RenderCopy(graphics.renderer, memory.openBall[i][j], NULL, &memory.board[i][j]);
                }
            }

            if (youwin) {
        SDL_Rect dst;
        dst.w = 612;
        dst.h = 408;
        dst.x = (SCREEN_WIDTH - dst.w) / 2;
        dst.y = (SCREEN_HEIGHT - dst.h) / 2;

        SDL_RenderCopy(graphics.renderer, youwin, NULL, &dst);
    }

            graphics.presentScene();

            waitUntilKeyPressed();
            quit = true;
        }

        // Cap frame rate
        SDL_Delay(16); // 60 FPS
    }
    SDL_DestroyTexture(background);
    graphics.quit();
}


