#include "screen.h"

extern Screen *cScreen;

void createScreen(Vector2 size, char fill, char *foregroundColor, char *backgroundColor)
{
    Screen screen;
    int sizeAdjusted = (size.x / MOV_VERT) * (size.y / MOV_HOR);
    screen.backBuffer = createBuffer(sizeAdjusted);
    screen.size = size;
    fillBuffer(&screen.backBuffer, fill);
    screen.foregroundColor = foregroundColor;
    screen.backgroundColor = backgroundColor;
    *cScreen = screen;
}

void renderBackBuffer(Screen *screen)
{
    COORD coord = {0, 0};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    printf(screen->foregroundColor);
    printf(screen->backgroundColor);
    WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), screen->backBuffer.data, screen->backBuffer.size, NULL, NULL);
    printf("\x1b[0m");
}

void destroyScreen(Screen *screen)
{
    destroyBuffer(&screen->backBuffer);
}