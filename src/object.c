#include "object.h"

Object createObject(Vector2 size, dVector2 position)
{
    Object object;
    int sizeAdjusted = (size.x / MOV_VERT) * (size.y / MOV_HOR);
    object.buffer = createBuffer(sizeAdjusted);
    object.size = size;
    object.position = position;
    return object;
}

void destroyObject(Object *object)
{
    destroyBuffer(&object->buffer);
}

void moveObject(Object *object, dVector2 direction, double speed, void (*movementModifier)(Object *, void *), void *args)
{
    object->position.x += direction.x * MOV_VERT * speed;
    object->position.y += direction.y * MOV_HOR * speed;
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