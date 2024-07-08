#ifndef UTILITY_H
#define UTILITY_H

#include <windows.h>
#include "vector.h"

struct Timer
{
    LARGE_INTEGER frequency;
    LARGE_INTEGER time;
    int fps;
    int deltaTime;
} typedef Timer;

Timer *createTimer();
void updateTimer(Timer *timer);

int compareCharStrings(char *string1, char *string2);

#endif