#ifndef SCREEN_H
#define SCREEN_H

#include "object.h"
#include "buffer.h"
#include "vector.h"
#include "defines.h"

struct Screen
{
    Buffer backBuffer;
    Vector2 size;
} typedef Screen;

Screen createScreen(Vector2 size);
void renderBackBuffer(Screen *screen, char *foregroundColor, char *backgroundColor);
void renderToScreen(Screen *screen, Object *object, char *foregroundColor, char *backgroundColor);
void destroyScreen(Screen *screen);

#endif
