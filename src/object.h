#ifndef OBJECT_H
#define OBJECT_H

#include "screen.h"
#include "buffer.h"
#include "vector.h"
#include "defines.h"
#include "utility.h"

struct Object
{
    Buffer buffer;
    Vector2 size;
    Vector2 speed;
    dVector2 position;
    char *foregroundColor;
    char *backgroundColor;
    char *label;
} typedef Object;

void renderAllObjects();
void destroyAllObjects();

Object *addObject(Object object);
Object *createObject(Vector2 size, Vector2 speed, dVector2 position, char *foregroundColor, char *backgroundColor, char *label);
void renderToScreen(Screen *screen, Object *object, char *foregroundColor, char *backgroundColor);
Object *getObjectByLabel(char *label);
void destroyObject(Object *object);

void moveObject(Object *object, dVector2 direction, double speed, void (*movementModifier)(Object *, void *), void *args);
void setPositionObject(Object *object, dVector2 position, void (*movementModifier)(Object *, void *), void *args);

// Movement modifiers
void limitMovementToScreen(Object *object, void *screenSizeP);
void wrapMovementAroundScreen(Object *object, void *screenSizeP);

#endif
