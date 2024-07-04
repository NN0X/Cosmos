#include "object.h"

Object createObject(Vector2 size, dVector2 position)
{
    Object object;
    object.buffer = createBuffer(size);
    object.position = position;
    return object;
}