#include "logic.h"
#include <vector>
#include <algorithm>
#include <random>
#include <iostream>

using namespace std;

void loadTextures(Graphics& graphics, Memory& memory)
{
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

            memory.openBall[i][j] = graphics.loadTexture(ballImages[id]);
            if (!memory.openBall[i][j])
            {
                cerr << "Failed to load texture: " << ballImages[k] << endl;
            }
            k++;
            //memory.imageId[i][j] = k / 2;
        }
    }
}


