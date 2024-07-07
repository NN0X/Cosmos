#ifndef UTILITY_H
#define UTILITY_H

#include <windows.h>
#include "vector.h"

struct GameTimer
{
    LARGE_INTEGER frequency;
    LARGE_INTEGER time;
    int fps;
    int deltaTime;
} typedef GameTimer;

GameTimer *createGameTimer();
void updateGameTimer(GameTimer *timer);

#endif