#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "defs.h"
#include "logic.h"
#include "mouse.h"
#include "graphics.h"

void gameLoop(Graphics& graphics, Memory& memory, Mouse& mouse, ScrollingBackground& background);

#endif // GAME_H
