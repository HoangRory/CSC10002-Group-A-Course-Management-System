#include "../Header/Login.h"
#include "../Header/Semester.h"

void DelAccount(Account *&accHead)
{
    if (!accHead)
        return;
    while (accHead)
    {
        Account *tmp = accHead->next;
        delete accHead;
        accHead = tmp;
    }
    accHead = nullptr;
}

void ReadAccount(Account *&accHead)
{
    std::ifstream ifs("../Data_file/account.csv");
    if (!ifs)
        return;

    Account *cur;
    std::string str;
    while (!ifs.eof())
    {
        if (!accHead)
        {
            accHead = new Account;
            cur = accHead;
            cur->prev = nullptr;
        }
        else
        {
            cur->next = new Account;
            Account *tmp = cur;
            cur = cur->next;
            cur->prev = tmp;
        }
        cur->next = nullptr;

        getline(ifs, cur->username, ',');
        getline(ifs, cur->password, ',');
        getline(ifs, str, ',');
        cur->role = stoi(str);
        getline(ifs, cur->lastName, ',');
        getline(ifs, cur->firstName, ',');
        getline(ifs, cur->Gender, ',');
        getline(ifs, cur->SocialID, ',');
        getline(ifs, cur->birth, '\n');

        // std::cout << cur->username << " || " << cur->password << " || " << cur->role << cur->lastName << " || " << cur->NationalID << " || " << cur->birth << '\n';
    }

    ifs.close();
    return;
}

void WriteAccount(Account *accHead)
{
    if (!accHead)
        return;
    std::ofstream ofs("../Data_file/account.csv");
    if (!ofs)
        return;

    Account *cur = accHead;
    while (cur)
    {
        ofs << cur->username << ',' << cur->password << ','
            << cur->role << ',' << cur->lastName << ','
            << cur->firstName << ',' << cur->Gender << ','
            << cur->SocialID << ',' << cur->birth << '\n';
        cur = cur->next;
    }
    ofs.close();
}

void LoggingIn(Account *accHead, std::string &user, std::string &pass, int &role)
{
    system("cls");
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(h, BLUE);
    cout << "WELCOME TO THE STUDENT MANAGEMENT SYSTEM\n\n";
    SetConsoleTextAttribute(h, LIGHT_AQUA);
    cout << "PLEASE ENTER YOUR USERNAME AND PASSWORD TO LOGIN\n\n";

    SetConsoleTextAttribute(h, LIGHT_GREEN);
    std::cout << "\nUsername: ";
    std::cin >> user;

    SetConsoleTextAttribute(h, LIGHT_RED);
    std::cout << "Password: ";
    std::cin >> pass;
    SetConsoleTextAttribute(h, WHITE);

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
        std::cout << "Wrong username or password\n";
        std::cout << "Try again?\n\n\n";
        system("pause");
        LoggingIn(accHead, user, pass, role);
        return;
    }
    role = cur->role;
    std::cout << "\nLogged in successfully!!\n";
    std::cout << "Hello, " << cur->lastName << ' ' << cur->firstName << "!\n";
    return;
    // Main_interface(accHead, user, pass, role);
    // AccountAlteration(accHead, user, pass, role);
}

void ChangePass(Account *accHead, std::string &user, std::string &pass)
{
    std::cout << "\nEnter your current password: ";
    std::string tmp = "";
    std::cin >> tmp;
    while (tmp != pass)
    {
        std::cout << "Wrong Password!!!\nEnter password again: ";
        std::cin >> tmp;
    }
    bool assem = true;
    system("cls");
    cout << "\n";
    std::cout << "Account confirm, enter your new password: ";
    do
    {
        if (assem == false)
            std::cout << "\nThe 2 passwords u enter are different\nEnter your new password: ";
        std::cin >> tmp;
        std::string newPass;
        std::cout << "Re-enter: ";
        std::cin >> newPass;
        assem = (tmp == newPass ? true : false);
    } while (!assem);

    Account *cur = accHead;
    while (cur && cur->username != user)
        cur = cur->next;
    cur->password = tmp;
    WriteAccount(accHead);
    std::cout << "\nChange password successfully.";
    return;
}

void Main_interface(Account *accHead, std::string &user, std::string &pass, int &role)
{
    bool stop = false;
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

    int opt = 1;
    string *ListOption = new string[4];
    ListOption[0] = "\nAccount Options:\n";
    ListOption[1] = "- Change your password\n";
    ListOption[2] = "- Logout              \n";
    ListOption[3] = "- Quit                \n";

    ShowConsoleCursor(false);
    for (int i = 0; i < 4; i++)
    {
        if (i == opt)
        {
            SetConsoleTextAttribute(h, YELLOW);
            cout << ListOption[i];
            SetConsoleTextAttribute(h, WHITE);
        }
        else
            cout << ListOption[i];
    }
    SetConsoleTextAttribute(h, GREEN);
    cout << "\n\n(Using your arrow on the keyboard to move the choice and enter to select!)\n\n";
    SetConsoleTextAttribute(h, WHITE);

    while (!stop)
    {
        if (_kbhit())
        {
            switch (_getch())
            {
            case UP:
                if (opt > 0)
                    opt--;
                break;
            case DOWN:
                if (opt < 3)
                    opt++;
                break;
            case ENTER:
                stop = true;
                break;
            }
            if (stop)
                break;

            system("cls");

            for (int i = 0; i < 4; i++)
            {
                if (i == opt)
                {
                    SetConsoleTextAttribute(h, YELLOW);
                    cout << ListOption[i];
                    SetConsoleTextAttribute(h, WHITE);
                }
                else
                    cout << ListOption[i];
            }
            SetConsoleTextAttribute(h, GREEN);
            cout << "\n\n(Using your arrow on the keyboard to move the choice and enter to select!)\n\n";
            SetConsoleTextAttribute(h, WHITE);
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
        return;
    }
    // Main_interface(accHead, user, pass, role);
    AccountAlteration(accHead, user, pass, role);
    return;
}

void AccountAlteration(Account *accHead, std::string &user, std::string &pass, int &role)
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    bool stop = false;

    int opt = 1;
    string *ListOption = new string[3];
    ListOption[0] = "\nAccount Alteration\n";
    ListOption[1] = "- Manage your account or Logout\n";
    ListOption[2] = "- Continue to use the program  \n";

    for (int i = 0; i < 3; i++)
    {
        if (i == opt)
        {
            SetConsoleTextAttribute(h, YELLOW);
            cout << ListOption[i];
            SetConsoleTextAttribute(h, WHITE);
        }
        else
            cout << ListOption[i];
    }
    SetConsoleTextAttribute(h, GREEN);
    cout << "\n\n(Using your arrow on the keyboard to move the choice and enter to select!)\n\n";
    SetConsoleTextAttribute(h, WHITE);

    ShowConsoleCursor(false);

    while (!stop)
    {
        if (_kbhit())
        {
            switch (_getch())
            {
            case UP:
                if (opt > 1)
                    opt--;
                break;
            case DOWN:
                if (opt < 2)
                    opt++;
                break;
            case ENTER:
                stop = true;
                break;
            }
            if (stop)
                break;
            system("cls");

            for (int i = 0; i < 3; i++)
            {
                if (i == opt)
                {
                    SetConsoleTextAttribute(h, YELLOW);
                    cout << ListOption[i];
                    SetConsoleTextAttribute(h, WHITE);
                }
                else
                    cout << ListOption[i];
            }

            SetConsoleTextAttribute(h, GREEN);
            cout << "\n\n(Using your arrow on the keyboard to move the choice and enter to select!)\n\n";
            SetConsoleTextAttribute(h, WHITE);
        }
    }
    delete[] ListOption;
    ShowConsoleCursor(true);

    switch (opt)
    {
    case 1:
        Main_interface(accHead, user, pass, role);
        return;
    case 2:
        return;
        // break;
    }
    return;
}

void LoggingMain(Account *&accHead, string &user, string &pass, int &role)
{
    ReadAccount(accHead);
    LoggingIn(accHead, user, pass, role);
    AccountAlteration(accHead, user, pass, role);
    return;
}