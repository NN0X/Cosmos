#include "buffer.h"

Buffer createBuffer(int size)
{
    Buffer buffer;
    buffer.data = (char *)malloc(size);
    buffer.size = size;
    return buffer;
}

void fillBuffer(Buffer *buffer, char fill)
{
    for (int i = 0; i < buffer->size; i++)
    {
        buffer->data[i] = fill;
    }
}

void destroyBuffer(Buffer *buffer)
{
    for (int i = 0; i < buffer->size; i++)
    {
        buffer->data[i] = 0;
    }

    free(buffer->data);
}