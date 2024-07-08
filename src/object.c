#include "object.h"

extern Screen *cScreen;
extern Object *cObjects;
extern int cDEBUG;

int cObjectsCount = 0;

void renderAllObjects()
{
    for (int i = 0; i < cObjectsCount; i++)
    {
        if (compareCharStrings(cObjects[i].label, (char *)"cDebugData") && cDEBUG == 0)
        {
            continue;
        }
        renderToScreen(cScreen, &cObjects[i], cObjects[i].foregroundColor, cObjects[i].backgroundColor);
    }
}

void destroyAllObjects()
{
    for (int i = 0; i < cObjectsCount; i++)
    {
        destroyObject(&cObjects[i]);
    }
    free(cObjects);
}

Object *addObject(Object object)
{
    cObjects = (Object *)realloc(cObjects, sizeof(Object) * (cObjectsCount + 1));
    cObjects[cObjectsCount] = object;
    cObjectsCount++;
    return &cObjects[cObjectsCount - 1];
}

Object *createObject(Vector2 size, Vector2 speed, dVector2 position, char *foregroundColor, char *backgroundColor, char *label)
{
    Object object;
    int sizeAdjusted = (size.x / MOV_VERT) * (size.y / MOV_HOR);
    object.buffer = createBuffer(sizeAdjusted);
    object.size = size;
    object.speed = speed;
    object.position = position;
    object.foregroundColor = foregroundColor;
    object.backgroundColor = backgroundColor;
    object.label = label;
    return addObject(object);
}

void renderToScreen(Screen *screen, Object *object, char *foregroundColor, char *backgroundColor)
{
    Vector2 postitionAdjusted = divideVector2(convertDVector2(object->position), newVector2(MOV_VERT, MOV_HOR));
    Vector2 sizeAdjusted = divideVector2(object->size, newVector2(MOV_VERT, MOV_HOR));

    if (postitionAdjusted.x + sizeAdjusted.x > screen->size.x / MOV_VERT)
    {
        return;
    }
    else if (postitionAdjusted.x < 0)
    {
        return;
    }

    if (postitionAdjusted.y + sizeAdjusted.y > screen->size.y / MOV_HOR)
    {
        return;
    }
    else if (postitionAdjusted.y < 0)
    {
        return;
    }

    COORD coord = {(short)postitionAdjusted.x, (short)postitionAdjusted.y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    printf(foregroundColor);
    printf(backgroundColor);
    WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), object->buffer.data, object->buffer.size, NULL, NULL);
    printf("\x1b[0m");
}

Object *getObjectByLabel(char *label)
{
    for (int i = 0; i < cObjectsCount; i++)
    {
        if (compareCharStrings(cObjects[i].label, label))
        {
            return &cObjects[i];
        }
    }
    return NULL;
}

void destroyObject(Object *object)
{
    destroyBuffer(&object->buffer);
}

void moveObject(Object *object, dVector2 direction, double deltaTime, void (*movementModifier)(Object *, void *), void *args)
{
    object->position.x += direction.x * MOV_VERT * object->speed.x * deltaTime / 1000.0;
    object->position.y += direction.y * MOV_HOR * object->speed.y * deltaTime / 1000.0;
    if (movementModifier != NULL)
    {
        movementModifier(object, args);
    }
}

void setPositionObject(Object *object, dVector2 position, void (*movementModifier)(Object *, void *), void *args)
{
    object->position = position;
    if (movementModifier != NULL)
    {
        movementModifier(object, args);
    }
}

void limitMovementToScreen(Object *object, void *screenSizeP)
{
    Vector2 screenSize = *(Vector2 *)screenSizeP;
    if (object->position.x + object->size.x > screenSize.x + MOV_VERT)
    {
        object->position.x = screenSize.x - object->size.x + MOV_VERT;
    }
    else if (object->position.x < 0)
    {
        object->position.x = 0;
    }

    if (object->position.y + object->size.y > screenSize.y)
    {
        object->position.y = screenSize.y - object->size.y;
    }
    else if (object->position.y < 0)
    {
        object->position.y = 0;
    }
}

void wrapMovementAroundScreen(Object *object, void *screenSizeP)
{
    Vector2 screenSize = *(Vector2 *)screenSizeP;
    if (object->position.x + object->size.x > screenSize.x + MOV_VERT)
    {
        object->position.x = 0;
    }
    else if (object->position.x < 0)
    {
        object->position.x = screenSize.x - object->size.x + MOV_VERT;
    }

    if (object->position.y + object->size.y > screenSize.y)
    {
        object->position.y = 0;
    }
    else if (object->position.y < 0)
    {
        object->position.y = screenSize.y - object->size.y;
    }
}