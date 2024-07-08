#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "cosmos.h"
#include "screen.h"
#include "vector.h"
#include "buffer.h"
#include "object.h"
#include "console.h"
#include "utility.h"
#include "defines.h"
#include "input.h"

Screen *cScreen;
Object *cObjects;
Timer *cTimer;

int cEXIT_KEY = KEY_ESCAPE;
int cDEBUG = 1;

int main()
{
    cScreen = (Screen *)malloc(sizeof(Screen));
    onStartup();
    initConsole(cScreen->size);

    Object *debugData = createObject(newVector2((4 + 3) * 8, 16), newVector2(0, 0), newDVector2(0, 0), WHITE, BLACK_BG, (char *)"cDebugData"); // 4 - 'FPS: ', 3 - number
    fillBuffer(&debugData->buffer, ' ');

    cTimer = createTimer();
    while (1)
    {
        renderBackBuffer(cScreen);

        if (cDEBUG)
        {
            sprintf(debugData->buffer.data, "FPS: %d", cTimer->fps);
        }

        renderAllObjects();
        onEachFrame();

        if (isKeyPressed(cEXIT_KEY))
        {
            break;
        }

        updateTimer(cTimer);
        Sleep(1);
    }

    onShutdown();

    destroyScreen(cScreen);
    destroyAllObjects();
    free(cTimer);

    return 0;
}