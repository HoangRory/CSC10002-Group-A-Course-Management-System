#include "../Header/Utility.h"

//? Show the blinking cursor in the terminal, disable when using arrow
void ShowConsoleCursor(bool visible)
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO lpCursor;
    lpCursor.bVisible = visible;
    lpCursor.dwSize = 20;
    SetConsoleCursorInfo(console, &lpCursor);
}
void Pause()
{
    ShowConsoleCursor(false);
    while (1)
        if (_kbhit())
        {
            int tmp = _getch();
            break;
        }
    ShowConsoleCursor(true);
    return;
}

//? Change the text color in terminal
void TextColor(int x) // X là mã màu
{
    // Các hàm này là hàm thao tác API với windows bạn cứ coppy thôi không cần phải hiểu quá sâu
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);
}

void goToXY(int x, int y)
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD cursorPosition;
    cursorPosition.X = x;
    cursorPosition.Y = y;
    SetConsoleCursorPosition(console, cursorPosition);
}

void resizeWindow(int x, int y)
{
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r);
    MoveWindow(console, r.left, r.top, x, y, TRUE);
}

void hideScrollBar()
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screenBufferInfo;
    GetConsoleScreenBufferInfo(console, &screenBufferInfo);

    COORD new_screen_buffer_size;

    new_screen_buffer_size.X = screenBufferInfo.srWindow.Right - screenBufferInfo.srWindow.Left + 1;
    new_screen_buffer_size.Y = screenBufferInfo.srWindow.Bottom - screenBufferInfo.srWindow.Top + 1;

    SetConsoleScreenBufferSize(console, new_screen_buffer_size);
}

void initWindow(int width, int length)
{
    resizeWindow(width, length);
    hideScrollBar();
}




void SetWindowSize(int width, int height)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

    SMALL_RECT WindowSize;
    WindowSize.Top = 0;
    WindowSize.Left = 0;
    WindowSize.Right = width;
    WindowSize.Bottom = height;
 
    SetConsoleWindowInfo(hStdout, 1, &WindowSize);
}