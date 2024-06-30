#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

struct Vector2
{
    int x;
    int y;
} typedef Vector2;

struct Buffer
{
    char *data;
    Vector2 size;
} typedef Buffer;

Buffer *createBuffer(Vector2 size)
{
    size.x /= 8;
    size.y /= 16;
    Buffer *buffer = (Buffer *)malloc(sizeof(Buffer));
    buffer->data = (char *)malloc(size.x * size.y);
    buffer->size = size;
    return buffer;
}

void fillBuffer(Buffer *buffer, char fill)
{
    for (int i = 0; i < buffer->size.x * buffer->size.y; i++)
    {
        buffer->data[i] = fill;
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
    free(buffer);
}

void setConsoleSize(Vector2 size)
{
    size.x /= 8;
    size.y /= 16;
    char command[30];
    sprintf(command, "mode con cols=%d lines=%d", size.x, size.y);
    system(command);
}

void init(Vector2 size)
{
    setConsoleSize(size);

    // Hide cursor
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.dwSize = 1;
    cursorInfo.bVisible = 0;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

    // Disable resizing
    HWND console = GetConsoleWindow();
    SetWindowLong(console, GWL_STYLE, GetWindowLong(console, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);

    // disable fullscreen
    SetWindowLong(console, GWL_STYLE, GetWindowLong(console, GWL_STYLE) & ~WS_MAXIMIZEBOX);

    // disable close
    EnableMenuItem(GetSystemMenu(console, FALSE), SC_CLOSE, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);

    // disable editing
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    DWORD prev_mode;
    GetConsoleMode(hInput, &prev_mode);
    SetConsoleMode(hInput, prev_mode & ~ENABLE_QUICK_EDIT_MODE);

    // disable input
    HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD prev_mode_out;
    GetConsoleMode(hOutput, &prev_mode_out);
    SetConsoleMode(hOutput, prev_mode_out | ENABLE_PROCESSED_OUTPUT);
}

void changeColor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

int main()
{
    Vector2 size = {800, 600};

    init(size);

    // set blue color
    changeColor(9);

    Buffer *buffer = createBuffer(size);
    fillBuffer(buffer, 219);

    while (1)
    {
        renderBuffer(buffer);
        if (GetAsyncKeyState(VK_ESCAPE))
        {
            break;
        }
        // sleep ms
        Sleep(1000 / 60);
    }

    return 0;
}