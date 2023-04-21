#include "../Header/Login.h"
#include "../Header/Utility.h"

void LoggingIn(Account *accHead, std::string &user, std::string &pass, int &role)
{
    system("cls");
    Render_Login();

    goToXY(50, 18);
    TextColor(0x0E);
    cout << "Username";

    TextColor(63);
    for (int i = 0; i < 3; i++)
    {
        goToXY(50, 19 + i);
        cout << "                                              ";
    }

    goToXY(50, 23);
    TextColor(0x0E);
    cout << "Password";
    TextColor(63);
    for (int i = 0; i < 3; i++)
    {
        goToXY(50, 24 + i);
        cout << "                                              ";
    }

    user = Limit_Input(52, 20, 30, 63);
    pass = Limit_Input(52, 25, 30, 63);
    TextColor(WHITE);

    Account *cur = accHead;
    bool loggedIn = false;
    while (cur)
    {
        if (cur->username == user && cur->password == pass)
        {
            loggedIn = true;
            break;
        }
        cur = cur->next;
    }

    if (!loggedIn)
    {
        string message = "Wrong username or password!!!\nRetry!";
        string title = "Login Failed";
        Message_Warning(message, title);
        // TextColor(LIGHT_RED);

        // goToXY(60, 28);
        // cout << "Wrong username or password";
        // goToXY(66, 29);

        // cout << "Try again!!!";
        // TextColor(WHITE);

        // Pause();
        LoggingIn(accHead, user, pass, role);
        return;
    }
    role = cur->role;
    string message = "Logged in successfully!!\nHello, " + cur->lastName + " " + cur->firstName + "!";
    string title = "Login Success";
    Message_Warning(message, title);
    // TextColor(LIGHT_YELLOW);
    // goToXY(60, 28);
    // cout << "Logged in successfully!!";
    // goToXY(60, 29);
    // cout << "Hello, " << cur->lastName << ' ' << cur->firstName << "!";
    // Pause();

    return;
}

void ChangePass(Account *accHead, std::string &user, std::string &pass)
{
    system("cls");
    Render_Account();
    TextColor(0x0B);
    goToXY(50, 18);
    TextColor(0x0E);
    cout << "Old Password";
    TextColor(63);
    for (int i = 0; i < 3; i++)
    {
        goToXY(50, 19 + i);
        cout << "                                              ";
    }
    goToXY(50, 23);
    TextColor(0x0E);
    cout << "New Password";
    TextColor(63);
    for (int i = 0; i < 3; i++)
    {
        goToXY(50, 24 + i);
        cout << "                                              ";
    }
    goToXY(50, 28);
    TextColor(0x0E);
    cout << "Confirm Password";
    TextColor(63);
    for (int i = 0; i < 3; i++)
    {
        goToXY(50, 29 + i);
        cout << "                                              ";
    }
    string tmp;
    TextColor(63);
    tmp = Limit_Input(52, 20, 30, 63);

    while (tmp != pass) // If the password is wrong
    {
        TextColor(0x3C);
        goToXY(80, 20);
        cout << "Wrong Password";
        Pause();

        TextColor(63);
        goToXY(50, 20);
        cout << "                                              ";
        tmp = Limit_Input(52, 20, 30, 63);
    }

    string p1, p2;
    p1 = Limit_Input(52, 25, 30, 63);
    p2 = Limit_Input(52, 30, 30, 63);

    while (p1 != p2)
    {
        string message = "The new password and the confirm password are not the same!!!\nPlease try again!!!";
        string title = "Change Password Failed";
        Message_Warning(message, title);
        goToXY(50, 25);
        cout << "                                              ";
        goToXY(50, 30);
        cout << "                                              ";
        p1 = Limit_Input(52, 25, 30, 63);
        p2 = Limit_Input(52, 30, 30, 63);
    }

    Account *cur = accHead;
    while (cur && cur->username != user) // Find the account
        cur = cur->next;
    cur->password = p1;
    WriteAccount(accHead);

    string message = "Change password successfully!!!";
    string title = "Change Password Success";
    Message_Warning(message, title);
    TextColor(7);

    return;
}

//? Account Alteration
bool AccountAlteration(Account *accHead, std::string &user, std::string &pass, int &role)
{
    system("cls");
    Render_Account();

    vector<string> menu;
    menu.push_back("Main Menu");
    menu.push_back("Change password");
    menu.push_back("Logout");
    menu.push_back("Quit");

    int opt = Draw_XY(menu, 60, 12, 4, 20, 63);

    switch (opt)
    {
    case 0:
        return false;

    case 1:
        ChangePass(accHead, user, pass);
        return AccountAlteration(accHead, user, pass, role);

    case 2:
        goToXY(50, 28);
        cout << "Returning to login page";
        for (int i = 0; i < 8; i++)
        {
            cout << ".";
            Sleep(200);
        }
        // system("cls");
        LoggingIn(accHead, user, pass, role);
        return AccountAlteration(accHead, user, pass, role);
    case 3:
        goToXY(50, 28);
        cout << "Thanks for ur usage!";
        Pause();
        return true;
    }
    return false;
}

bool LoggingMain(Account *&accHead, string &user, string &pass, int &role)
{
    // ReadAccount(accHead);
    LoggingIn(accHead, user, pass, role);
    if (AccountAlteration(accHead, user, pass, role))
        return true;
    return false;
}