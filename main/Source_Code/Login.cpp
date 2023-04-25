#include "../Header/Login.h"
#include "../Header/Utility.h"
#include "../Header/Year.h"
#include "../Header/Semester.h"
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
    Render_Account(50, 1);
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
        if (!Message_YesNo(message, title))
            return;
        TextColor(63);
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
    pass = cur->password = p1;
    WriteAccount(accHead);

    string message = "Change password successfully!!!";
    string title = "Change Password Success";
    Message_Warning(message, title);
    TextColor(7);

    return;
}

void Profiling(Account *accHead, string user, string pass, int role)
{
    // Name, birth, gender, social ID, username, password = ********, role
    system("cls");
    Render_Account(50, 1);
    Account *cur = accHead;
    while (cur && (cur->username != user || cur->password != pass))
        cur = cur->next;

    TextColor(63);
    for (int i = 0; i < 3; i++)
    {
        goToXY(50, 9 + i);
        cout << "                                                    "; // username
        goToXY(50, 13 + i);
        cout << "                                 "; // password
        goToXY(85, 13 + i);
        cout << "                 "; // Role
        goToXY(50, 17 + i);
        cout << "                                                    "; // Full name
        goToXY(50, 21 + i);
        cout << "                                 "; // Birthday
        goToXY(85, 21 + i);
        cout << "                 "; // Gender
        goToXY(50, 25 + i);
        cout << "                                                    "; // Social ID
    }
    goToXY(52, 10);
    cout << "Username: " << cur->username;

    goToXY(52, 14);
    cout << "Password: " << cur->password.substr(0, 2);
    for (int i = 2; i < cur->password.length(); i++)
        cout << '*';
    goToXY(88, 14);
    cout << "Role: ";
    if (cur->role == 1)
        cout << "Student";
    else
        cout << "Staff";

    goToXY(52, 18);
    cout << "Full name: " << cur->lastName << ' ' << cur->firstName;

    goToXY(52, 22);
    cout << "Birthday: " << cur->birth;

    goToXY(88, 22);
    cout << "Gender: " << (cur->Gender == "M" ? "Male" : "Female");
    goToXY(52, 26);
    cout << "Social ID: " << cur->SocialID;

    TextColor(7);
    Pause();
}

//? Account Alteration
bool AccountAlteration(Year *yearHead, Account *accHead, std::string &user, std::string &pass, int &role)
{
    system("cls");
    Render_Account(50, 1);

    vector<string> menu;
    menu.push_back("Main Menu");
    menu.push_back("Profile");
    menu.push_back("Change password");
    menu.push_back("Logout");
    menu.push_back("Quit");

    int opt = Draw_XY(menu, 60, 12, 5, 20, 63);

    switch (opt)
    {
    case 0:
        return false;

    case 1:
        Profiling(accHead, user, pass, role);
        return AccountAlteration(yearHead, accHead, user, pass, role);

    case 2:
        ChangePass(accHead, user, pass);
        return AccountAlteration(yearHead, accHead, user, pass, role);

    case 3:
        goToXY(50, 28);
        cout << "Returning to login page";
        for (int i = 0; i < 8; i++)
        {
            cout << ".";
            Sleep(200);
        }
        // system("cls");
        if (Message_YesNo("Do you want to save all the changes?", "Notice!"))
        {
            Output(yearHead);  // write down all the year
            Outyear(yearHead); // write down each year in4
            Message_Warning("File save!\nNow clean up and close!", "Quit");
        }
        LoggingIn(accHead, user, pass, role);
        return false;
        // return AccountAlteration(accHead, user, pass, role);
    case 4:
        goToXY(50, 28);
        cout << "Thanks for ur usage!";
        Pause();
        return true;
    }
    return false;
}

bool LoggingMain(Year *yearHead, Account *&accHead, string &user, string &pass, int &role)
{
    // ReadAccount(accHead);
    LoggingIn(accHead, user, pass, role);
    if (AccountAlteration(yearHead, accHead, user, pass, role))
        return true;
    return false;
}