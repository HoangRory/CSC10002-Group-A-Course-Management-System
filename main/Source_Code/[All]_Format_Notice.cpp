#include "../Header/Semester.h"
#include "../Header/Login.h"
#include "../Header/Year.h"
#include "../Header/Utility.h"
#include "../Header/course.h"

void Notice_Login(int x, int y)
{
    goToXY(x, y++);
    cout << "Enter username and password (limit 42 characters)";
}

void Notice_Move(int x, int y)
{
    goToXY(x, y++);
    cout << "Use the arrow to move up and down";
}

void Change_Password(int x, int y)
{
    goToXY(x, y++);
    cout << "Enter your new password and the new one (42 char)";
}