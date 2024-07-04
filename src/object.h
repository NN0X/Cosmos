#ifndef OBJECT_H
#define OBJECT_H

#include "buffer.h"
#include "vector.h"

struct Object
{
    Buffer buffer;
    dVector2 position;
} typedef Object;

Object createObject(Vector2 size, dVector2 position);

#endif
