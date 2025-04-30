#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <algorithm>
#include <random>

#include "graphics.h"
#include "defs.h"
#include "logic.h"

using namespace std;

SDL_Texture* checkLoadImage(Graphics& graphics, const char* path){
    SDL_Texture* texture = graphics.loadTexture(path);
    if(!texture){
        cerr << "Failed to load texture" << path << endl;
    }
    return texture;
}

void loadResources(Graphics& graphics, Memory& memory){
    memory.background = checkLoadImage(graphics, "image/p3.png_large");
    memory.youwin = checkLoadImage(graphics, "image/youwin.png");
    memory.closeBall = checkLoadImage(graphics, "image/ball2.png");

     const char* ballImages[] =
    {
        "image/poke1.png", "image/poke2.png",
        "image/poke3.png", "image/poke4.png",
        "image/poke5.png", "image/poke6.png",
        "image/poke7.png", "image/poke8.png"
    };

    vector<int> imageIds;
    for(int i = 0; i < numImages; i++)
    {
        imageIds.push_back(i);
        imageIds.push_back(i);
    }

    random_device rd;
    mt19937 gen(rd());
    shuffle(imageIds.begin(), imageIds.end(), gen);

    int k = 0;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            int id = imageIds[k];
            memory.imageId[i][j] = id;
            memory.openBall[i][j] = checkLoadImage(graphics, ballImages[id]);
            k++;
        }
    }
}
