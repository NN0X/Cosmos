#ifndef UTILITY_H
#define UTILITY_H

#include <windows.h>

struct Timer
{
    LARGE_INTEGER frequency;
    LARGE_INTEGER time;
    int deltaTime;
} typedef Timer;

Timer *createTimer();
void updateTimer(Timer *timer);

#endif