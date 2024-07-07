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
#include "input.h"

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

    GameTimer *timer = createGameTimer();
    int speed = 50;
    while (1)
    {
        renderBackBuffer(&screen, BLUE, BLACK_BG);
        renderToScreen(&screen, &player, RED, GREEN_BG);

        fillBuffer(&debugData.buffer, ' ');
        sprintf(debugData.buffer.data, "FPS: %d", timer->fps);
        renderToScreen(&screen, &debugData, WHITE, BLACK_BG);

        if (isKeyPressed(KEY_LEFT) || isKeyPressed(KEY_A))
        {
            moveObject(&player, newDVector2(-1, 0), speed * timer->deltaTime / 1000.0, wrapMovementAroundScreen, (void *)&size);
        }
        if (isKeyPressed(KEY_RIGHT) || isKeyPressed(KEY_D))
        {
            moveObject(&player, newDVector2(1, 0), speed * timer->deltaTime / 1000.0, wrapMovementAroundScreen, (void *)&size);
        }
        if (isKeyPressed(KEY_UP) || isKeyPressed(KEY_W))
        {
            moveObject(&player, newDVector2(0, -1), speed * timer->deltaTime / 1000.0, wrapMovementAroundScreen, (void *)&size);
        }
        if (isKeyPressed(KEY_DOWN) || isKeyPressed(KEY_S))
        {
            moveObject(&player, newDVector2(0, 1), speed * timer->deltaTime / 1000.0, wrapMovementAroundScreen, (void *)&size);
        }

        if (isMouseLeftPressed())
        {
            setPositionObject(&player, getMousePosition(&screen), limitMovementToScreen, (void *)&size);
        }

        if (isKeyPressed(KEY_ESCAPE))
        {
            break;
        }

        updateGameTimer(timer);
        Sleep(1);
    }

    destroyScreen(&screen);
    destroyObject(&player);
    destroyObject(&debugData);
    free(timer);

    return 0;
}