#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <string>

#include "graphics.h"
#include "defs.h"
#include "logic.h"
#include "resources.h"
#include "game.h"

using namespace std;

int main(int argc, char *argv[])
{
    Graphics graphics;
    graphics.init();
    Memory memory;

    loadResources(graphics, memory);

    gameLoop(graphics, memory);

    graphics.quit();
    return 0;
}
