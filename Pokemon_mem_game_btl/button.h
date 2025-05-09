#ifndef BUTTON_H
#define BUTTON_H

#include "mouse.h"
#include "graphics.h"

class Button {
public:
    SDL_Texture* tex;
    SDL_Rect sourRect, desRect;
    bool isSelected = false;
    Button(Graphics& graphics);
    virtual ~Button();

    void update(Mouse& mouse);
    void draw(Graphics& graphics);
};

#endif // BUTTON_H
