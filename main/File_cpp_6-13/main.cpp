#include "../Header/Semester.h"
#include "../Header/Login.h"

int main()
{
    Account *accHead = nullptr;
    std::string user = "", pass = "";
    int role = -1;
    Semester *semHead = nullptr;
    int yr = 2022;
    int num_smt = 3, num_year = 1;

    LoggingMain(accHead, user, pass, role);
    cout << role << '\n';
    NewSemesterMain(semHead, yr, num_year, num_smt, accHead, role);

    DeleteSMT(semHead);
    DelAccount(accHead);
    system("pause");
    return 0;
}