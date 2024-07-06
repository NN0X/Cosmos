#ifndef INPUT_H
#define INPUT_H

#include "windows.h"
#include "vector.h"
#include "screen.h"

enum Keys
{
    KEY_UP = VK_UP,
    KEY_DOWN = VK_DOWN,
    KEY_LEFT = VK_LEFT,
    KEY_RIGHT = VK_RIGHT,
    KEY_W = 'W',
    KEY_A = 'A',
    KEY_S = 'S',
    KEY_D = 'D',
    KEY_ESCAPE = VK_ESCAPE
};

dVector2 getMousePosition(Screen *screen);

int isKeyPressed(int key);
int isKeyReleased(int key);

int isMouseLeftPressed();
int isMouseRightPressed();
int isMouseMiddlePressed();

int isMouseLeftReleased();
int isMouseRightReleased();
int isMouseMiddleReleased();

#endif