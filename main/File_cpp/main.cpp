// #include "Header/proto.h"
#include "../Header/Semester.h"
#include "../Header/Login.h"

int main()
{
    Semester *semHead = nullptr;
    Account *accHead = nullptr;
    std::string user = "", pass = "";
    int role = -1;

    int yr = 2022;
    int num_smt = 3, num_year = 1;
    system("cls");
    cout << '\n';
    // ReadAccount();
    ReadAccount(accHead);
    Read_multi_SMT(semHead, yr, num_year, num_smt);
    LoggingIn(accHead, user, pass, role);
    // AddSemester(semHead);
    // initModify(semHead);
    // Output(semHead);
    SyncFullName(semHead, accHead);
    viewCourse(semHead);

    DeleteSMT(semHead);
    DelAccount(accHead);

    return 0;
}