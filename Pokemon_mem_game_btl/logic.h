#ifndef _LOGIC__H
#define _LOGIC__H

#include <SDL.h>
#include <vector>
#include <algorithm>
#include <random>
#include "defs.h"
#include "graphics.h"

struct Memory
{
    SDL_Rect board[rows][cols];  // Ma trận các ô
    bool isFlipped[rows][cols];
    bool matched[rows][cols];
    SDL_Texture* closeBall;
    SDL_Texture* openBall[rows][cols];
    int openedCount = 0;                  // Số ô đang mở (0, 1 hoặc 2)
    SDL_Point openedCards[2];         // Vị trí 2 ô đang mở
    int imageId[rows][cols];
    bool isComparing = false;
    Uint32 compareStartTime;          // Thời điểm bắt đầu so sánh
    const Uint32 COMPARE_DELAY = 400; // Thời gian chờ so sánh
    // Constructor
    Memory()
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                board[i][j].x = startX + j * (cellWidth + MARGIN_X);
                board[i][j].y = startY + i * (cellHeight + MARGIN_Y);
                board[i][j].w = cellWidth;
                board[i][j].h = cellHeight;
                isFlipped[i][j] = false;
                matched[i][j] = false;
                openBall[i][j] = nullptr;
            }
        }
        closeBall = nullptr;
    }

    ~Memory()
    {
        // Giải phóng
        for(int i = 0; i < rows; i++)
        {
            for(int j = 0; j < cols; j++)
            {
                if(openBall[i][j] != nullptr)
                {
                    SDL_DestroyTexture(openBall[i][j]);
                    openBall[i][j] = nullptr;
                }
            }
        }

        if(closeBall != nullptr)
        {
            SDL_DestroyTexture(closeBall);
            closeBall = nullptr;
        }
    }
};
void loadTextures(Graphics& graphics, Memory& memory);

#endif

