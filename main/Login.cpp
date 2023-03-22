#include "proto.h"
#include "Login.h"

Account *accHead = nullptr;
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
    std::ifstream ifs("Data_file/account.csv");
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
        }
        else
        {
            cur->next = new Account;
            Account *tmp = cur;
            cur = cur->next;
            cur->prev = tmp;
        }

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

void WriteAccount()
{
    if (!accHead)
        return;
    std::ofstream ofs("Data_file/account.csv");
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
        char check;
        std::cout << "Try again? (Y/N) ";
        std::cin >> check;
        if (check == 'Y')
            LoggingIn();
        else
            return;
    }
    role = cur->role;
    std::cout << "\nLogged in successfully!!\n";
    std::cout << "Hello, " << cur->lastName << ' ' << cur->firstName << "!\n";
    Main_interface();
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
    Main_interface();
}

void Main_interface()
{
    std::cout << "Option: \n1. Change your password.\n2. Logout\n3. Quit\nYour choice: ";
    int check = -1;
    std::cin >> check;
    if (check == 1)
        ChangePass();
    else if (check == 2)
        LoggingIn();
    else
        std::cout << "Thanks for ur usage!";
}

int main()
{
    ReadAccount();
    LoggingIn();
    DelAccount();
    return 0;
}