#include "buffer.h"

Buffer createBuffer(Vector2 size)
{
    size.x /= 8;
    size.y /= 16;
    Buffer buffer;
    buffer.data = (char *)malloc(size.x * size.y);
    buffer.size = size;
    return buffer;
}

void fillBuffer(Buffer *buffer, char fill)
{
    for (int i = 0; i < buffer->size.x * buffer->size.y; i++)
    {
        buffer->data[i] = fill;
    }
}

void insertToBuffer(Buffer *buffer, Buffer *insterted, Vector2 position)
{
    position.x /= 8;
    position.y /= 16;

    for (int y = 0; y < insterted->size.y; y++)
    {
        for (int x = 0; x < insterted->size.x; x++)
        {
            buffer->data[(position.y + y) * buffer->size.x + position.x + x] = insterted->data[y * insterted->size.x + x];
        }
    }
}

void renderBuffer(Buffer *buffer)
{
    COORD coord = {0, 0};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), buffer->data, buffer->size.x * buffer->size.y, NULL, NULL);
}

void destroyBuffer(Buffer *buffer)
{
    free(buffer->data);
}