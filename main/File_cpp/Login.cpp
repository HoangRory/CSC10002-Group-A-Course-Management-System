#include "../Header/Login.h"

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

void LoggingIn(Account *accHead, std::string &user, std::string &pass, int &role)
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
            LoggingIn(accHead, user, pass, role);
        else
            return;
    }
    role = cur->role;
    std::cout << "\nLogged in successfully!!\n";
    std::cout << "Hello, " << cur->lastName << ' ' << cur->firstName << "!\n";
    Main_interface(accHead, user, pass, role);
}

void ChangePass(Account *accHead, std::string &user, std::string &pass)
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
    WriteAccount(accHead);
    std::cout << "\nChange password successfully.";
}

void Main_interface(Account *accHead, std::string &user, std::string &pass, int &role)
{
    std::cout << "Option: \n1. Change your password.\n2. Logout\n3. Quit\nYour choice: ";
    int check = -1;
    std::cin >> check;
    if (check == 1)
        ChangePass(accHead, user, pass);
    else if (check == 2)
        LoggingIn(accHead, user, pass, role);
    else
    {
        std::cout << "Thanks for ur usage!";
        return;
    }

    Main_interface(accHead, user, pass, role);
}