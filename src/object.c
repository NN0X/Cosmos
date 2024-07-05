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

Object convertToScreen(Vector2 screenSize, Object *object)
{
    if (object->size.x + object->position.x > screenSize.x + MOV_VERT)
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

    Vector2 sizeAdjusted = {object->size.x / MOV_VERT, object->size.y / MOV_HOR};
    dVector2 positionAdjusted = {object->position.x / MOV_VERT, object->position.y / MOV_HOR};
    Object objectAdjusted = createObject(sizeAdjusted, positionAdjusted);

    return objectAdjusted;
}