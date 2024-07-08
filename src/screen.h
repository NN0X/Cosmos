#ifndef SCREEN_H
#define SCREEN_H

#include "buffer.h"
#include "vector.h"
#include "defines.h"

struct Screen
{
    Buffer backBuffer;
    Vector2 size;
    char *foregroundColor;
    char *backgroundColor;
} typedef Screen;

void createScreen(Vector2 size, char fill, char *foregroundColor, char *backgroundColor);
void renderBackBuffer(Screen *screen);
void destroyScreen(Screen *screen);

#endif
