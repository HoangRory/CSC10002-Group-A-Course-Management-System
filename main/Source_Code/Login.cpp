#include "../Header/Login.h"
#include "../Header/Utility.h"

void LoggingIn(Account *accHead, std::string &user, std::string &pass, int &role)
{
    system("cls");

    TextColor(LIGHT_AQUA);
    goToXY(14, 1);
    cout << " ___  ___  ___   _   _   ___   _____  _____ ___  ___ _____  _   _  _____   _____ __   __ _____  _____  _____ ___  ___";
    goToXY(14, 2);
    cout << " |  \\/  | / _ \\ | \\ | | / _ \\ |  __ \\|  ___||  \\/  ||  ___|| \\ | ||_   _| /  ___|\\ \\ / //  ___||_   _||  ___||  \\/  |";
    goToXY(14, 3);
    cout << " | .  . |/ /_\\ \\|  \\| |/ /_\\ \\| |  \\/| |__  | .  . || |__  |  \\| |  | |   \\ `--.  \\ V / \\ `--.   | |  | |__  | .  . |";
    goToXY(14, 4);
    cout << " | |\\/| ||  _  || . ` ||  _  || | __ |  __| | |\\/| ||  __| | . ` |  | |    `--. \\  \\ /   `--. \\  | |  |  __| | |\\/| |";
    goToXY(14, 5);
    cout << " | |  | || | | || |\\  || | | || |_\\ \\| |___ | |  | || |___ | |\\  |  | |   /\\__/ /  | |  /\\__/ /  | |  | |___ | |  | |";
    goToXY(14, 6);
    cout << " \\_|  |_/\\_| |_/\\_| \\_/\\_| |_/ \\____/\\____/ \\_|  |_/\\____/ \\_| \\_/  \\_/   \\____/   \\_/  \\____/   \\_/  \\____/ \\_|  |_/";

    TextColor(LIGHT_GREEN);
    goToXY(60, 8);
    cout << " _     ___    ___ ___  _  _";
    goToXY(60, 9);
    cout << "| |   / _ \\  / __|_ _|| \\| |";
    goToXY(60, 10);
    cout << "| |__| (_) || (_ || | | .` |";
    goToXY(60, 11);
    cout << "|____|\\___/  \\___|___||_|\\_|";

    goToXY(50, 16);
    TextColor(0x0E);
    cout << "Username";

    TextColor(63);
    for (int i = 0; i < 3; i++)
    {
        goToXY(50, 17 + i);
        cout << "                                              ";
    }
    // TextColor(73);

    goToXY(50, 21);
    TextColor(0x0E);
    cout << "Password";
    TextColor(63);
    for (int i = 0; i < 3; i++)
    {
        goToXY(50, 22 + i);
        cout << "                                              ";
    }

    TextColor(63);
    goToXY(52, 18);
    cin >> user;
    goToXY(52, 23);
    cin >> pass;
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
        TextColor(LIGHT_RED);

        goToXY(60, 26);
        cout << "Wrong username or password";
        goToXY(66, 27);

        cout << "Try again!!!";
        TextColor(WHITE);

        Pause();
        LoggingIn(accHead, user, pass, role);
        return;
    }
    role = cur->role;
    TextColor(LIGHT_YELLOW);
    goToXY(60, 26);
    cout << "Logged in successfully!!";
    goToXY(60, 27);
    cout << "Hello, " << cur->lastName << ' ' << cur->firstName << "!";

    Pause();
    return;
}

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