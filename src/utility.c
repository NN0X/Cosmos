#include "utility.h"

GameTimer *createGameTimer()
{
    GameTimer *timer = (GameTimer *)malloc(sizeof(GameTimer));
    QueryPerformanceFrequency(&timer->frequency);
    QueryPerformanceCounter(&timer->time);
    timer->deltaTime = 0;
    return timer;
}

void updateGameTimer(GameTimer *timer)
{
    LARGE_INTEGER currentTime;
    QueryPerformanceCounter(&currentTime);
    timer->deltaTime = (currentTime.QuadPart - timer->time.QuadPart) * 1000 / timer->frequency.QuadPart;
    timer->time = currentTime;
    if (timer->deltaTime != 0)
    {
        timer->fps = 1000 / timer->deltaTime;
    }
}