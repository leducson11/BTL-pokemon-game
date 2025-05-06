#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <algorithm>
#include <random>

#include "graphics.h"
#include "defs.h"
#include "logic.h"
#include "resources.h"

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

        if(background != nullptr){
            SDL_DestroyTexture(background);
            background = nullptr;
        }

        if(youwin != nullptr){
            SDL_DestroyTexture(youwin);
            youwin = nullptr;
        }
    }

    bool Memory::checkWin(bool matched[rows][cols])
{
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            if (!matched[i][j]) return false;
    return true;
}

void Memory::waitUntilKeyPressed()
{
    SDL_Event e;
    while (true)
    {
        SDL_ShowCursor(true);
        if ( SDL_PollEvent(&e) != 0 && (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
            return;
        SDL_Delay(100);
    }
}

void Memory::mouseClickEvent(Memory& memory, int mouseX, int mouseY){
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
}
void Memory::compareBall(Memory& memory){
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
}
