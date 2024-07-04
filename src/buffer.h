#ifndef BUFFER_H
#define BUFFER_H

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "vector.h"

struct Buffer
{
    char *data;
    Vector2 size;
} typedef Buffer;

Buffer createBuffer(Vector2 size);
void fillBuffer(Buffer *buffer, char fill);
void insertToBuffer(Buffer *buffer, Buffer *insterted, Vector2 position);
void renderBuffer(Buffer *buffer);
void destroyBuffer(Buffer *buffer);

#endif
