#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>

#include "graphics.h"

using namespace std;

void Graphics::logErrorAndExit(const char* msg, const char* error)
{
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "%s: %s", msg, error);
    SDL_Quit();
}

void Graphics::init()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logErrorAndExit("SDL_Init", SDL_GetError());

    window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    //full screen
    //window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP);
    if (window == nullptr) logErrorAndExit("CreateWindow", SDL_GetError());

    if (!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG))
        logErrorAndExit( "SDL_image error:", IMG_GetError());

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
                                  SDL_RENDERER_PRESENTVSYNC);
    //Khi chạy trong máy ảo (ví dụ phòng máy ở trường)
    //renderer = SDL_CreateSoftwareRenderer(SDL_GetWindowSurface(window));

    if (renderer == nullptr) logErrorAndExit("CreateRenderer", SDL_GetError());

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void Graphics::prepareScene(SDL_Texture * background)
{
    SDL_RenderClear(renderer);
    SDL_RenderCopy( renderer, background, NULL, NULL);
}

void Graphics::presentScene()
{
    SDL_RenderPresent(renderer);
}

SDL_Texture* Graphics::loadTexture(const char *filename)
{
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);

    SDL_Texture *texture = IMG_LoadTexture(renderer, filename);
    if (texture == NULL)
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Load texture %s", IMG_GetError());

    return texture;
}

void Graphics::renderTexture(SDL_Texture *texture, int x, int y)
{
    SDL_Rect dest;

    dest.x = x;
    dest.y = y;
    SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

    SDL_RenderCopy(renderer, texture, NULL, &dest);
}

void Graphics::quit()
{
    IMG_Quit();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Graphics::renderBoard(Graphics& graphics, Memory& memory)
{
    graphics.prepareScene(memory.background);
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            if(memory.isFlipped[i][j] || memory.matched[i][j])
            {
                SDL_RenderCopy(graphics.renderer, memory.openBall[i][j], NULL, &memory.board[i][j]);
            }
            else
            {
                SDL_RenderCopy(graphics.renderer, memory.closeBall, NULL, &memory.board[i][j]);
            }
        }
    }
}

void Graphics::renderWinBoard(Graphics& graphics, Memory& memory)
{
    if(memory.youwin != NULL)
    {
        SDL_Rect winBoard;
        winBoard.w = 662;
        winBoard.h = 458;
        winBoard.x = (SCREEN_WIDTH - winBoard.w) / 2;
        winBoard.y = (SCREEN_HEIGHT - winBoard.h) / 2;

        SDL_RenderCopy(graphics.renderer, memory.youwin, NULL, &winBoard);
        graphics.presentScene();
        memory.waitUntilKeyPressed();
    }
}

void Graphics::render(ScrollingBackground& background)
{
    renderTexture(background.tex, background.scrollingOffset, 0);
    renderTexture(background.tex, background.scrollingOffset - background.width, 0);
}

void ScrollingBackground::setTexture(SDL_Texture* _texture)
{
    tex = _texture;
    SDL_QueryTexture(tex, NULL, NULL, &width, & height);
}

void ScrollingBackground::scroll(int distance)
{
    scrollingOffset -= distance;
    if(scrollingOffset < 0)
    {
        scrollingOffset = width;
    }
}
