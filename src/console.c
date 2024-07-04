#include "console.h"

void setConsoleSize(Vector2 size)
{
    size.x /= 8;
    size.y /= 16;
    char command[30];
    sprintf(command, "mode con cols=%d lines=%d", size.x, size.y);
    system(command);
}

void initConsole(Vector2 size)
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