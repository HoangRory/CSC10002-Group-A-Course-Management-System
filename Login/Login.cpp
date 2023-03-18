#include <iostream>
#include <fstream>

struct Account
{
    std::string username, password;
    int role;
    Account *accNext, *accPrev;
} *accHead;

int role = -1;

void DelAccount()
{
    if (!accHead)
        return;
    while (accHead)
    {
        Account *tmp = accHead->accNext;
        delete accHead;
        accHead = tmp;
    }
    accHead = nullptr;
}

void ReadAccount()
{
    std::ifstream ifs("account.csv");
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
            cur->accNext = nullptr;
            cur->accPrev = nullptr;
        }
        else
        {
            cur->accNext = new Account;
            Account *prev = cur;
            cur = cur->accNext;
            cur->accPrev = prev;
            cur->accNext = nullptr;
        }

        getline(ifs, str);
        int cnt = 0;
        std::string tmp;
        for (int i = 0; i < str.size(); i++)
        {
            if (str[i] == ',')
            {
                cnt++;
                if (cnt == 1)
                    cur->username = tmp;
                else if (cnt == 2)
                {
                    cur->password = tmp;
                    cur->role = std::stoi(str.substr(i + 1, str.size() - i));
                }
                tmp = "";
            }
            else
                tmp += str[i];
        }
        //? std::cout << cur->username << " || " << cur->password << " || " << cur->role << '\n';
    }

    ifs.close();
    return;
}

void WriteAccount()
{
    if (!accHead)
        return;
    std::ofstream ofs("account.csv");
    if (!ofs)
        return;

    Account *cur = accHead;
    while (cur)
    {
        ofs << cur->username << ',' << cur->password << ',' << cur->role << '\n';
        cur = cur->accNext;
    }
    ofs.close();
}

void LoggingIn()
{
    std::string user, pass;
    std::cout << "\nUsername: ";
    std::cin >> user;
    std::cout << "Password: ";
    std::cin >> pass;

    Account *cur = accHead;
    bool loggedIn = false;
    while (cur)
    {
        if (cur->username == user && cur->password == pass)
        {
            loggedIn = true;
            break;
        }
        cur = cur->accNext;
    }

    if (!loggedIn)
    {
        std::cout << "Wrong username or password\n";
        LoggingIn();
        return;
    }
    role = cur->role;
    //? std::cout << "\nLogged in successfully!!\n";
}

void ChangePass() {}

// int main()
// {
//     ReadAccount();
//     WriteAccount();
//     LoggingIn();
//     DelAccount();
//     return 0;
// }