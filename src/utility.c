#include "utility.h"

Timer *createTimer()
{
    Timer *timer = (Timer *)malloc(sizeof(Timer));
    QueryPerformanceFrequency(&timer->frequency);
    QueryPerformanceCounter(&timer->time);
    timer->deltaTime = 0;
    return timer;
}

void updateTimer(Timer *timer)
{
    LARGE_INTEGER currentTime;
    QueryPerformanceCounter(&currentTime);
    timer->deltaTime = (currentTime.QuadPart - timer->time.QuadPart) * 1000 / timer->frequency.QuadPart;
    timer->time = currentTime;
}