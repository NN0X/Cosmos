#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "vector.h"
#include "buffer.h"
#include "object.h"
#include "console.h"
#include "utility.h"

#define MOV_VERT 8
#define MOV_HOR 16

int main()
{

    Vector2 size = {800, 600};

    initConsole(size);

    Buffer buffer = createBuffer(size);
    fillBuffer(&buffer, 219);

    Object player = createObject((Vector2){20, 20}, (dVector2){400, 550});
    fillBuffer(&player.buffer, ' ');

    Object debugData = createObject((Vector2){(4 + 3) * 8, 16}, (dVector2){0, 0}); // 4 - 'FPS: ', 3 - number
    fillBuffer(&debugData.buffer, ' ');

    Timer *timer = createTimer();
    int fps = 0;
    int speed = 50;
    while (1)
    {
        renderBuffer(&buffer);
        fillBuffer(&buffer, 219);
        insertToBuffer(&buffer, &player.buffer, (Vector2){player.position.x, player.position.y});

        fillBuffer(&debugData.buffer, ' ');
        sprintf(debugData.buffer.data, "FPS: %d", fps);
        insertToBuffer(&buffer, &debugData.buffer, (Vector2){debugData.position.x, debugData.position.y});

        if (GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState('A'))
        {
            player.position.x -= MOV_VERT * timer->deltaTime / 1000.0 * speed;
        }
        if (GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState('D'))
        {
            player.position.x += MOV_VERT * timer->deltaTime / 1000.0 * speed;
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

    destroyBuffer(&buffer);
    destroyBuffer(&player.buffer);
    destroyBuffer(&debugData.buffer);

    return 0;
}