#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

struct Vector2
{
    int x;
    int y;
} typedef Vector2;

struct dVector2
{
    double x;
    double y;
} typedef dVector2;

struct Buffer
{
    char *data;
    Vector2 size;
} typedef Buffer;

struct Object
{
    Buffer *buffer;
    dVector2 position;
} typedef Object;

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

    // enable ansi colors
    system("color");
}

void getDeltaTime(LARGE_INTEGER *time, LARGE_INTEGER frequency, int *deltaTime)
{
    LARGE_INTEGER currentTime;
    QueryPerformanceCounter(&currentTime);
    *deltaTime = (currentTime.QuadPart - time->QuadPart) * 1000 / frequency.QuadPart;
    *time = currentTime;
}

#define MOV_VERT 8
#define MOV_HOR 16

int main()
{

    Vector2 size = {800, 600};

    init(size);

    Buffer *buffer = createBuffer(size);
    fillBuffer(buffer, 219);

    Object player;
    player.position = (dVector2){400, 550};
    player.buffer = createBuffer((Vector2){20, 20});
    fillBuffer(player.buffer, ' ');

    Object debugData;
    debugData.position = (dVector2){0, 0};
    debugData.buffer = createBuffer((Vector2){(4 + 3) * 8, 16}); // 4 - 'FPS: ', 3 - number
    fillBuffer(debugData.buffer, ' ');

    LARGE_INTEGER time;
    LARGE_INTEGER frequency;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&time);
    int deltaTime = 0;
    int fps = 0;
    int speed = 50;
    while (1)
    {
        renderBuffer(buffer);
        fillBuffer(buffer, 219);
        insertToBuffer(buffer, player.buffer, (Vector2){player.position.x, player.position.y});

        fillBuffer(debugData.buffer, ' ');
        sprintf(debugData.buffer->data, "FPS: %d", fps);
        insertToBuffer(buffer, debugData.buffer, (Vector2){debugData.position.x, debugData.position.y});

        if (GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState('A'))
        {
            player.position.x -= MOV_VERT * deltaTime / 1000.0 * speed;
        }
        if (GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState('D'))
        {
            player.position.x += MOV_VERT * deltaTime / 1000.0 * speed;
        }

        if (GetAsyncKeyState(VK_ESCAPE))
        {
            break;
        }

        getDeltaTime(&time, frequency, &deltaTime);
        if (deltaTime != 0)
            fps = 1000 / deltaTime;

        Sleep(1);
    }

    destroyBuffer(buffer);
    destroyBuffer(player.buffer);
    destroyBuffer(debugData.buffer);

    return 0;
}