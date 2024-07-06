#ifndef BUFFER_H
#define BUFFER_H

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "vector.h"

struct Buffer
{
    char *data;
    int size;
} typedef Buffer;

Buffer createBuffer(int size);
void fillBuffer(Buffer *buffer, char fill);
void destroyBuffer(Buffer *buffer);

#endif
