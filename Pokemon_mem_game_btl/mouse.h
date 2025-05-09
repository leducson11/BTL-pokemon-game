#ifndef MOUSE_H
#define MOUSE_H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "graphics.h"

class Mouse{

Graphics& graphics;
    public:
    SDL_Texture* cursor;
    SDL_Rect rect;
    SDL_Rect point;

    Mouse(Graphics& graphics) : graphics(graphics)
    {
        cursor = graphics.loadTexture("image/doremon2.png");
        rect.w = 80;
        rect.h = 80;
        point.w = 1;
        point.h = 1;
        SDL_ShowCursor(false);
    }

    ~Mouse() {
        if (cursor) SDL_DestroyTexture(cursor);
    }

    void update()
    {
        SDL_GetMouseState(&rect.x, &rect.y);
        point.x = rect.x;
        point.y = rect.y;
    }

    void draw()
    {
        SDL_RenderCopy(graphics.renderer, cursor, NULL, &rect);
        graphics.presentScene();
    }
};

#endif // MOUSE_H
