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

void moveObject(Object *object, dVector2 direction, double speed, void (*movementModifier)(Object *, void *), void *args);

void limitMovementToScreen(Object *object, void *screenSizeP);
void wrapMovementAroundScreen(Object *object, void *screenSizeP);

#endif
