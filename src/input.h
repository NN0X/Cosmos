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
    KEY_ESCAPE = VK_ESCAPE,
    KEY_SPACE = VK_SPACE,
    KEY_ENTER = VK_RETURN,
    KEY_A = 0x41,
    KEY_B,
    KEY_C,
    KEY_D,
    KEY_E,
    KEY_F,
    KEY_G,
    KEY_H,
    KEY_I,
    KEY_J,
    KEY_K,
    KEY_L,
    KEY_M,
    KEY_N,
    KEY_O,
    KEY_P,
    KEY_Q,
    KEY_R,
    KEY_S,
    KEY_T,
    KEY_U,
    KEY_V,
    KEY_W,
    KEY_X,
    KEY_Y,
    KEY_Z
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