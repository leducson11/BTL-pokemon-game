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
    SDL_Texture* background;
    SDL_Texture* youwin;
    int openedCount = 0;                  // Số ô đang mở (0, 1 hoặc 2)
    SDL_Point openedCards[2];         // Vị trí 2 ô đang mở
    int imageId[rows][cols];
    bool isComparing = false;
    Uint32 compareStartTime;          // Thời điểm bắt đầu so sánh
    const Uint32 COMPARE_DELAY = 650; // Thời gian chờ so sánh
    bool checkWin(bool matched[rows][cols]);
    void waitUntilKeyPressed();
    void mouseClickEvent(Memory& memory, int x, int y);
    void compareBall(Memory& memory);

    Memory();
    ~Memory();
};

#endif
