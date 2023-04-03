#include "../Header/Semester.h"
#include "../Header/Login.h"

int main()
{
    Account *accHead = nullptr;
    std::string user = "", pass = "";
    int role = -1;
    LoggingMain(accHead, user, pass, role);
    Semester *semHead = nullptr;
    int yr = 2022;
    int num_smt = 3, num_year = 1;
    NewSemesterMain(semHead, yr, num_year, num_smt, accHead, role);
    // viewCourse(semHead);
    // system("pause");
    // // AddSemester(semHead);
    // // cout << "Do you want to modify the semester? (Y/N): ";
    // // char ch;
    // // cin >> ch;
    // // if (ch == 'Y' || ch == 'y')
    // ShowConsoleCursor(false);

    // initModify(semHead);
    // ShowConsoleCursor(true);
    // // Output(semHead);
    // // SyncFullName(semHead, accHead);
    // // viewCourse(semHead);

    // DeleteSMT(semHead);
    DelAccount(accHead);
    system("pause");
    return 0;
}