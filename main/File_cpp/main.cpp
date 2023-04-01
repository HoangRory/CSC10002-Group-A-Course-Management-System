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
    // ReadAccount(accHead);
    Read_multi_SMT(semHead, yr, num_year, num_smt);
    // LoggingIn(accHead, user, pass, role);
    // cout << "Logged in!\n";
    // cout << "Add semester: \n";
    viewCourse(semHead);
    // AddSemester(semHead);
    // cout << "Do you want to modify the semester? (Y/N): ";
    // char ch;
    // cin >> ch;
    // if (ch == 'Y' || ch == 'y')
    ShowConsoleCursor(false);

    initModify(semHead);
    ShowConsoleCursor(true);
    // Output(semHead);
    // SyncFullName(semHead, accHead);
    // viewCourse(semHead);

    DeleteSMT(semHead);
    // DelAccount(accHead);
    system("pause");
    return 0;
}