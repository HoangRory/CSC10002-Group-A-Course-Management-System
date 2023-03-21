#include "proto.h"


Account *accHead;
std::string user = "", pass = "";
int role = -1;

void DelAccount()
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

void ReadAccount()
{
    std::ifstream ifs("CSVFile/account.csv");
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
    std::ofstream ofs("CSVFile/account.csv");
    if (!ofs)
        return;

    Account *cur = accHead;
    while (cur)
    {
        ofs << cur->username << ',' << cur->password << ',' << cur->role << '\n';
        cur = cur->next;
    }
    ofs.close();
}

void LoggingIn()
{
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
        cur = cur->next;
    }

    if (!loggedIn)
    {
        std::cout << "Wrong username or password\n";
        LoggingIn();
        return;
    }
    role = cur->role;
    std::cout << "\nLogged in successfully!!\n";
}

void ChangePass()
{
    std::cout << "Enter your current password: ";
    std::string tmp = "";
    std::cin >> tmp;
    while (tmp != pass)
    {
        std::cout << "Wrong Password!!!\nEnter password again: ";
        std::cin >> tmp;
    }
    bool assem = true;
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
    WriteAccount();
    std::cout << "\nChange password successfully.";
}

void Main_interface()
{
    std::cout << "\nChange your password (Y/N): ";
    char check;
    std::cin >> check;
    if (check == 'Y')
        ChangePass();
    else
        std::cout << "Thanks for ur usage!";
}

int main()
{
    ReadAccount();
    LoggingIn();
    Main_interface();
    DelAccount();
    return 0;
}