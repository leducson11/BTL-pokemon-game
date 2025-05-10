#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "graphics.h"
#include "defs.h"
#include "logic.h"
#include "resources.h"
#include "game.h"
#include "mouse.h"
#include "mouse.h"

using namespace std;

int main(int argc, char *argv[])
{
    Graphics graphics;
    graphics.init();
    Mouse mouse(graphics);
    Memory memory;
    ScrollingBackground background;

    loadResources(graphics, memory);

    gameLoop(graphics, memory, mouse, background);

    graphics.quit();
    return 0;
}
