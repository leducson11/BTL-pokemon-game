#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <algorithm>
#include <random>

#include "graphics.h"
#include "defs.h"
#include "logic.h"
#include "game.h"
#include "mouse.h"
#include "button.h"

using namespace std;

enum GameState
{
    MENU,
    PLAYING
};

void gameLoop(Graphics& graphics, Memory& memory, Mouse& mouse){
    GameState gameState = MENU;
    SDL_Event event;
    bool quit = false;

    Button startButton(graphics);
    startButton.sourRect.y = 0;
    startButton.desRect.x = SCREEN_WIDTH / 2 - startButton.desRect.w / 2;
    startButton.desRect.y = 600;
    while (! quit)
    {
        graphics.renderBoard(graphics, memory);
        SDL_PollEvent(&event);
        switch (event.type)
        {
        case SDL_QUIT:
            quit = true;
            break;
        case SDL_MOUSEBUTTONDOWN:
            int mouseX, mouseY;
            SDL_GetMouseState(&mouseX, &mouseY);
            if(gameState == PLAYING)
            {
            memory.mouseClickEvent(memory, mouseX, mouseY);
            }
            break;
        case SDL_MOUSEBUTTONUP:
            if(event.button.button == SDL_BUTTON_LEFT)
            {
                if(gameState == MENU && startButton.isSelected)
                {
                    cerr << "Star button has been clicked\n";
                    gameState = PLAYING;
                }
            }
            break;
        }

        mouse.update();

        if(gameState == MENU)
        {
            SDL_RenderCopy(graphics.renderer, memory.menu, NULL, NULL);
            startButton.update(mouse);
            startButton.draw(graphics);
        }
        else if(gameState == PLAYING)
        {
            graphics.renderBoard(graphics, memory);
            memory.compareBall(memory);
            if (memory.checkWin(memory.matched))
        {
            cerr << "You win!" << endl;
            graphics.renderWinBoard(graphics, memory);
            quit = true;
        }
        }
        mouse.draw();
        SDL_Delay(16);
    }

}
