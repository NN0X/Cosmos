#ifndef OBJECT_H
#define OBJECT_H

#include "buffer.h"
#include "vector.h"
#include "defines.h"

struct Object
{
    Buffer buffer;
    Vector2 size;
    dVector2 position;
} typedef Object;

Object createObject(Vector2 size, dVector2 position);
void destroyObject(Object *object);

Object convertToScreen(Vector2 screenSize, Object *object);

#endif
