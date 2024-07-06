#include "screen.h"

Screen createScreen(Vector2 size)
{
    Screen screen;
    int sizeAdjusted = (size.x / MOV_VERT) * (size.y / MOV_HOR);
    screen.backBuffer = createBuffer(sizeAdjusted);
    screen.size = size;
    return screen;
}

void renderBackBuffer(Screen *screen, char *foregroundColor, char *backgroundColor)
{
    COORD coord = {0, 0};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    printf(foregroundColor);
    printf(backgroundColor);
    WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), screen->backBuffer.data, screen->backBuffer.size, NULL, NULL);
    printf("\x1b[0m");
}

void renderToScreen(Screen *screen, Object *object, char *foregroundColor, char *backgroundColor)
{
    Vector2 postitionAdjusted = divideVector2(convertDVector2(object->position), newVector2(MOV_VERT, MOV_HOR));
    Vector2 sizeAdjusted = divideVector2(object->size, newVector2(MOV_VERT, MOV_HOR));

    if (postitionAdjusted.x + sizeAdjusted.x > screen->size.x / MOV_VERT)
    {
        return;
    }
    else if (postitionAdjusted.x < 0)
    {
        return;
    }

    if (postitionAdjusted.y + sizeAdjusted.y > screen->size.y / MOV_HOR)
    {
        return;
    }
    else if (postitionAdjusted.y < 0)
    {
        return;
    }

    COORD coord = {(short)postitionAdjusted.x, (short)postitionAdjusted.y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    printf(foregroundColor);
    printf(backgroundColor);
    WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), object->buffer.data, object->buffer.size, NULL, NULL);
    printf("\x1b[0m");
}

void destroyScreen(Screen *screen)
{
    destroyBuffer(&screen->backBuffer);
}