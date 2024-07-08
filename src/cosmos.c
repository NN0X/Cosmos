#include "cosmos.h"

void onStartup()
{
    createScreen(newVector2(800, 600), (char)219, BLUE, BLACK_BG);

    Object *player = createObject(newVector2(20, 20), newVector2(50, 25), newDVector2(400, 550), GREEN, BLACK_BG, (char *)"player");
    fillBuffer(&player->buffer, (char)219);
}

void onEachFrame()
{
    Object *player = getObjectByLabel((char *)"player");

    if (isKeyPressed(KEY_LEFT) || isKeyPressed(KEY_A))
    {
        moveObject(player, newDVector2(-1, 0), cTimer->deltaTime, wrapMovementAroundScreen, (void *)&cScreen->size);
    }
    if (isKeyPressed(KEY_RIGHT) || isKeyPressed(KEY_D))
    {
        moveObject(player, newDVector2(1, 0), cTimer->deltaTime, wrapMovementAroundScreen, (void *)&cScreen->size);
    }
    if (isKeyPressed(KEY_UP) || isKeyPressed(KEY_W))
    {
        moveObject(player, newDVector2(0, -1), cTimer->deltaTime, wrapMovementAroundScreen, (void *)&cScreen->size);
    }
    if (isKeyPressed(KEY_DOWN) || isKeyPressed(KEY_S))
    {
        moveObject(player, newDVector2(0, 1), cTimer->deltaTime, wrapMovementAroundScreen, (void *)&cScreen->size);
    }

    if (isMouseLeftPressed())
    {
        setPositionObject(player, getMousePosition(cScreen), limitMovementToScreen, (void *)&cScreen->size);
    }
}

void onShutdown()
{
}