#ifndef _RESOURCES_H
#define _RESOURCES_H

#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "defs.h"
#include "logic.h"

SDL_Texture* checkLoadImage(Graphics& graphics, const char* path);
void loadResources(Graphics& graphics, Memory& memory);

#endif // _RESOURCES_H
