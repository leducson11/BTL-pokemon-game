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

void gameLoop(Graphics& graphics, Memory& memory){
    SDL_Event event;
    bool quit = false;
    while (! quit)
    {
        renderBoard(graphics, memory);
        SDL_PollEvent(&event);
        switch (event.type)
        {
        case SDL_QUIT:
            quit = true;
            break;
        case SDL_MOUSEBUTTONDOWN:
            int mouseX, mouseY;
            SDL_GetMouseState(&mouseX, &mouseY);
            mouseClickEvent(memory, mouseX, mouseY);
            break;
        }
        compareBall(memory);

        if (checkWin(memory.matched))
        {
            cerr << "You win!" << endl;
            renderWinBoard(graphics, memory);
            quit = true;
        }

        SDL_Delay(16);
    }

}
