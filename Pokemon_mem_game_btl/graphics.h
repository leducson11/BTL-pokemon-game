#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "defs.h"
#include "logic.h"

using namespace std;

struct ScrollingBackground
{
    SDL_Texture* tex;
    int scrollingOffset = 0;
    int width, height;

    void setTexture(SDL_Texture* _texture);
    void scroll(int distance);
};

struct Graphics
{
    SDL_Renderer *renderer;
    SDL_Window *window;

    void logErrorAndExit(const char* msg, const char* error);
    void init();
    void prepareScene(SDL_Texture * background);
    void presentScene();
    SDL_Texture* loadTexture(const char *filename);
    void renderTexture(SDL_Texture *texture, int x, int y);
    void quit();
    void renderBoard(Graphics& graphics, Memory& memory);
    void renderWinBoard(Graphics& graphics, Memory& memory);
    void render(ScrollingBackground& background);

};

#endif // GRAPHICS_H
