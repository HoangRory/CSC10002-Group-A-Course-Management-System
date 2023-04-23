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
    while (1)
        if (_kbhit())
        {
            int tmp = _getch();
            break;
        }
    return;
}
//? Popup message box
void Message_Warning(string message, string title)
{
    EnableWindow(GetConsoleWindow(), false);
    MessageBoxA(NULL, message.c_str(), title.c_str(), MB_OK | MB_ICONINFORMATION);
    EnableWindow(GetConsoleWindow(), true);
}

bool Message_YesNo(string message, string title)
{
    EnableWindow(GetConsoleWindow(), false);
    int result = MessageBoxA(NULL, message.c_str(), title.c_str(), MB_YESNO | MB_ICONQUESTION);
    EnableWindow(GetConsoleWindow(), true);
    return (result == IDYES ? true : false);
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

string Limit_Input(int x, int y, int limit, int color)
{
    ShowConsoleCursor(true);
    goToXY(x, y);
    TextColor(color);
    string input;
    char c;
    int i = 0;
    while (true)
    {
        c = _getch();
        if (c == 13 && i > 0)
            break;
        else if (c == 8)
        {
            if (i > 0)
            {
                i--;
                input.pop_back();
                goToXY(x + i, y);
                cout << " ";
                goToXY(x + i, y);
            }
        }
        else if (i < limit)
        {
            input.push_back(c);
            cout << c;
            i++;
        }
    }
    TextColor(7);
    ShowConsoleCursor(false);
    return input;
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