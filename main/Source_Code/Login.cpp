#include "../Header/Login.h"
#include "../Header/Utility.h"
#include "../UICourseManagementSystem/UICourseManagementSystem/x64/MyForm.h" // Include the header file for your WinForms form

using namespace System;
using namespace System::Windows::Forms;

void LoggingIn(Account* accHead, std::string& user, std::string& pass, int& role)
{
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);

    // Create an instance of your WinForms form
    UICourseManagementSystem::MyForm form(accHead, user, pass, role);

    // Run the form and handle the login process inside the form
    Application::Run(% form);
}

//void LoggingIn(Account *accHead, std::string &user, std::string &pass, int &role)
//{
//    system("cls");
//    cout << "\n";
//
//    TextColor(LIGHT_AQUA);
//    cout << "WELCOME TO THE STUDENT MANAGEMENT SYSTEM\n\n";
//    cout << "PLEASE ENTER YOUR USERNAME AND PASSWORD TO LOGIN\n\n";
//
//    TextColor(LIGHT_GREEN);
//    std::cout << "\nUsername: ";
//    std::cin >> user;
//
//    TextColor(LIGHT_RED);
//    std::cout << "Password: ";
//    std::cin >> pass;
//    TextColor(WHITE);
//
//    Account *cur = accHead;
//    bool loggedIn = false;
//    while (cur)
//    {
//        if (cur->username == user && cur->password == pass)
//        {
//            loggedIn = true;
//            break;
//        }
//        cur = cur->next;
//    }
//
//    if (!loggedIn)
//    {
//        TextColor(LIGHT_RED);
//        std::cout << "\nWrong username or password\n";
//        std::cout << "Try again!!!\n\n\n";
//        TextColor(WHITE);
//
//        system("pause");
//        LoggingIn(accHead, user, pass, role);
//        return;
//    }
//    role = cur->role;
//    std::cout << "\nLogged in successfully!!\n";
//    std::cout << "Hello, " << cur->lastName << ' ' << cur->firstName << "!\n";
//    return;
//    // Main_interface(accHead, user, pass, role);
//    // AccountAlteration(accHead, user, pass, role);
//}

void ChangePass(Account *accHead, std::string &user, std::string &pass)
{
    std::cout << "\nEnter your current password: ";
    std::string tmp;
    std::cin >> tmp;

    while (tmp != pass) // If the password is wrong
    {
        TextColor(LIGHT_RED);
        std::cout << "Wrong Password!!!\nEnter password again: ";
        TextColor(WHITE);
        std::cin >> tmp;
    }
    bool assem = true;
    system("cls");
    cout << "\n";
    std::cout << "Account confirm, enter your new password: ";
    do
    {
        if (assem == false) // If the 2 passwords are different
            std::cout << "\nThe 2 passwords u enter are different\nEnter your new password: ";
        std::cin >> tmp;
        std::string newPass;
        std::cout << "Re-enter: ";
        std::cin >> newPass;
        assem = (tmp == newPass ? true : false); // If the 2 passwords are the same
    } while (!assem);

    Account *cur = accHead;
    while (cur && cur->username != user) // Find the account
        cur = cur->next;
    cur->password = tmp;
    WriteAccount(accHead);

    TextColor(LIGHT_GREEN);
    std::cout << "\nChange password successfully.";
    TextColor(WHITE);

    return;
}

bool Main_interface(Account *accHead, std::string &user, std::string &pass, int &role)
{
    bool stop = false;

    int opt = 1, prev_opt = 1;
    string *ListOption = new string[4]; // List of options
    ListOption[0] = "\nAccount Options:\n";
    ListOption[1] = "- Change your password\n";
    ListOption[2] = "- Logout              \n";
    ListOption[3] = "- Quit                \n";

    ShowConsoleCursor(false);
    for (int i = 0; i < 4; i++)
    {
        if (i == opt)
        {
            TextColor(LIGHT_YELLOW);
            cout << ListOption[i];
            TextColor(WHITE);
        }
        else
            cout << ListOption[i];
    }
    TextColor(LIGHT_GREEN);
    cout << "\n\n(Using your arrow on the keyboard to move the choice and enter to select!)\n\n";
    TextColor(WHITE);

    while (!stop)
    {
        if (_kbhit())
        {
            switch (_getch())
            {
            case UP:
                if (opt > 0)
                {
                    prev_opt = opt;
                    opt--;
                }
                break;
            case DOWN:
                if (opt < 3)
                {
                    prev_opt = opt;
                    opt++;
                }
                break;
            case ENTER:
                stop = true;
                break;
            }
            if (stop)
                break;

            if (prev_opt != opt)
            {
                system("cls");

                for (int i = 0; i < 4; i++)
                {
                    if (i == opt)
                    {
                        TextColor(LIGHT_YELLOW);
                        cout << ListOption[i];
                        TextColor(WHITE);
                    }
                    else
                        cout << ListOption[i];
                }
                TextColor(LIGHT_GREEN);
                cout << "\n\n(Using your arrow on the keyboard to move the choice and enter to select!)\n\n";
                TextColor(WHITE);
            }
        }
    }
    delete[] ListOption;
    ShowConsoleCursor(true);

    switch (opt)
    {
    case 1:
        ChangePass(accHead, user, pass);
        break;
    case 2:
        cout << "Returning to login page";
        for (int i = 0; i < 8; i++)
        {
            cout << ".";
            Sleep(200);
        }
        system("cls");
        LoggingIn(accHead, user, pass, role);
        break;
    case 3:
        std::cout << "Thanks for ur usage!\n\n";
        system("pause");
        return true;
    }
    // Main_interface(accHead, user, pass, role);
    AccountAlteration(accHead, user, pass, role);
    return false;
}

//? Account Alteration
bool AccountAlteration(Account *accHead, std::string &user, std::string &pass, int &role)
{
    bool stop = false;

    int opt = 1, prev = -1;
    string *ListOption = new string[3];
    ListOption[0] = "\nAccount Alteration\n";
    ListOption[1] = "- Manage your account or Logout\n";
    ListOption[2] = "- Continue to use the program  \n";

    for (int i = 0; i < 3; i++)
    {
        if (i == opt)
        {
            TextColor(LIGHT_YELLOW);
            cout << ListOption[i];
            TextColor(WHITE);
        }
        else
            cout << ListOption[i];
    }
    TextColor(LIGHT_GREEN);
    cout << "\n\n(Using your arrow on the keyboard to move the choice and enter to select!)\n\n";
    TextColor(WHITE);

    ShowConsoleCursor(false);

    while (!stop)
    {
        if (_kbhit())
        {
            switch (_getch())
            {
            case UP:
                if (opt > 1)
                {
                    prev = opt;
                    opt--;
                }
                break;
            case DOWN:
                if (opt < 2)
                {
                    prev = opt;
                    opt++;
                }
                break;
            case ENTER:
                stop = true;
                break;
            }
            if (stop)
                break;

            if (prev != opt)
            {
                system("cls");

                for (int i = 0; i < 3; i++)
                {
                    if (i == opt)
                    {
                        TextColor(LIGHT_YELLOW);
                        cout << ListOption[i];
                        TextColor(WHITE);
                    }
                    else
                        cout << ListOption[i];
                }

                TextColor(LIGHT_GREEN);
                cout << "\n\n(Using your arrow on the keyboard to move the choice and enter to select!)\n\n";
                TextColor(WHITE);
            }
        }
    }
    delete[] ListOption;
    ShowConsoleCursor(true);

    switch (opt)
    {
    case 1:
        if (Main_interface(accHead, user, pass, role))
            return true;
        break;
    case 2:
        return false;
        break;
    }
    return false;
}

bool LoggingMain(Account *&accHead, string &user, string &pass, int &role)
{
    ReadAccount(accHead);
    LoggingIn(accHead, user, pass, role);
    if (AccountAlteration(accHead, user, pass, role))
        return true;
    return false;
}