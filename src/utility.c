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
    if (timer->deltaTime != 0)
    {
        timer->fps = 1000 / timer->deltaTime;
    }
}

int compareCharStrings(char *string1, char *string2)
{
    int i = 0;
    while (string1[i] != '\0' && string2[i] != '\0')
    {
        if (string1[i] != string2[i])
        {
            return 0;
        }
        i++;
    }
    return 1;
}