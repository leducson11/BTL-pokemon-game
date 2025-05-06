#ifndef RESOURCES_H
#define RESOURCES_H

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "defs.h"
#include "logic.h"
#include "mouse.h"
#include "graphics.h"

SDL_Texture* checkLoadImage(Graphics& graphics, const char* path);
void loadResources(Graphics& graphics, Memory& memory);

#endif // RESOURCES_H
