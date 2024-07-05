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
    Object objectAdjusted = convertToScreen(screen->size, object);

    COORD coord = {(short)objectAdjusted.position.x, (short)objectAdjusted.position.y};
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