#include "input.h"

dVector2 getMousePosition(Screen *screen)
{
    POINT p;
    GetCursorPos(&p);
    ScreenToClient(GetConsoleWindow(), &p);

    RECT consoleRect;
    GetClientRect(GetConsoleWindow(), &consoleRect);

    if (p.x < 0)
    {
        p.x = 0;
    }
    else if (p.x > consoleRect.right)
    {
        p.x = consoleRect.right;
    }

    if (p.y < 0)
    {
        p.y = 0;
    }
    else if (p.y > consoleRect.bottom)
    {
        p.y = consoleRect.bottom;
    }

    double x = (double)p.x / consoleRect.right;
    double y = (double)p.y / consoleRect.bottom;

    return newDVector2(x * screen->size.x, y * screen->size.y);
}

int isKeyPressed(int key)
{
    return GetAsyncKeyState(key) & 0x8000;
}

int isKeyReleased(int key)
{
    return GetAsyncKeyState(key) & 0x0001;
}

int isMouseLeftPressed()
{
    return GetAsyncKeyState(VK_LBUTTON) & 0x8000;
}

int isMouseRightPressed()
{
    return GetAsyncKeyState(VK_RBUTTON) & 0x8000;
}

int isMouseMiddlePressed()
{
    return GetAsyncKeyState(VK_MBUTTON) & 0x8000;
}

int isMouseLeftReleased()
{
    return GetAsyncKeyState(VK_LBUTTON) & 0x0001;
}

int isMouseRightReleased()
{
    return GetAsyncKeyState(VK_RBUTTON) & 0x0001;
}

int isMouseMiddleReleased()
{
    return GetAsyncKeyState(VK_MBUTTON) & 0x0001;
}
