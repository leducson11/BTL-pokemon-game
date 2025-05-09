#include "button.h"
#include "graphics.h"

Button::Button(Graphics& graphics){
    static SDL_Texture* t = IMG_LoadTexture(graphics.renderer, "image/Play.png");
    tex = t;

    sourRect.h = 250;
    sourRect.w = 256;
    sourRect.x = 0;

    desRect.h = 97;
    desRect.w = 128;
}

Button::~Button(){SDL_DestroyTexture(tex);}

void Button::update(Mouse& mouse)
{
    if(SDL_HasIntersection(&desRect, &mouse.point))
    {
        isSelected = true;
        sourRect.x = 330;
    }
    else
    {
        isSelected = false;
        sourRect.x = 0;
    }
}

void Button::draw(Graphics& graphics)
{
    SDL_RenderCopy(graphics.renderer, tex, &sourRect, &desRect);
}
