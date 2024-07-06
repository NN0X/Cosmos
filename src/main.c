#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "screen.h"
#include "vector.h"
#include "buffer.h"
#include "object.h"
#include "console.h"
#include "utility.h"
#include "defines.h"

int main()
{
    Vector2 size = {800, 600};

    initConsole(size);

    Screen screen = createScreen(size);
    fillBuffer(&screen.backBuffer, (char)219);

    Object player = createObject(newVector2(20, 20), newDVector2(400, 550));
    fillBuffer(&player.buffer, ' ');

    Object debugData = createObject(newVector2((4 + 3) * 8, 16), newDVector2(0, 0)); // 4 - 'FPS: ', 3 - number
    fillBuffer(&debugData.buffer, ' ');

    Timer *timer = createTimer();
    int fps = 0;
    int speed = 50;
    while (1)
    {
        renderBackBuffer(&screen, BLUE, BLACK_BG);
        renderToScreen(&screen, &player, RED, GREEN_BG);

        fillBuffer(&debugData.buffer, ' ');
        sprintf(debugData.buffer.data, "FPS: %d", fps);
        renderToScreen(&screen, &debugData, WHITE, BLACK_BG);

        if (GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState('A'))
        {
            moveObject(&player, newDVector2(-1, 0), speed * timer->deltaTime / 1000.0, wrapMovementAroundScreen, (void *)&size);
        }
        if (GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState('D'))
        {
            moveObject(&player, newDVector2(1, 0), speed * timer->deltaTime / 1000.0, wrapMovementAroundScreen, (void *)&size);
        }
        if (GetAsyncKeyState(VK_UP) || GetAsyncKeyState('W'))
        {
            moveObject(&player, newDVector2(0, -1), speed * timer->deltaTime / 1000.0, wrapMovementAroundScreen, (void *)&size);
        }
        if (GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState('S'))
        {
            moveObject(&player, newDVector2(0, 1), speed * timer->deltaTime / 1000.0, wrapMovementAroundScreen, (void *)&size);
        }

        if (GetAsyncKeyState(VK_ESCAPE))
        {
            break;
        }

        updateTimer(timer);
        if (timer->deltaTime != 0)
            fps = 1000 / timer->deltaTime;

        Sleep(1);
    }

    destroyScreen(&screen);
    destroyObject(&player);
    destroyObject(&debugData);
    free(timer);

    return 0;
}