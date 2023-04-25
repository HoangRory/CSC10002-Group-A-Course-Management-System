#include "../Header/Semester.h"
#include "../Header/Login.h"
#include "../Header/Year.h"
#include "../Header/Utility.h"
#include "../Header/course.h"

void EradicateLL(Account *&accHead, Year *&yearHead)
{
    DelAccount(accHead);
    DeleteYear(yearHead);
}
void Merge_year_sem(Account *&accHead, Year *&yearHead)
{
    yearHead = RecoverFile();
    string user = "", pass = "";
    int role;
    ReadAccount(accHead);
    SyncInForStudent(yearHead, accHead);
    SyncFullName(yearHead, accHead);
    SyncCourse(yearHead);
    LoggingIn(accHead, user, pass, role);
    Main_Menu(yearHead, accHead, user, pass, role);
}

int main()
{
    Account *accHead = nullptr;
    Year *yearHead = nullptr;
    ShowConsoleCursor(false);

    initWindow(1200, 600);
    system("title Course Management System");
    Merge_year_sem(accHead, yearHead);
    // ViewScoreboardClass(yearHead->next->Class->next->next->next, yearHead->next->NoSemester, 10, 10);
    system("mode 1000, 5000");
    EradicateLL(accHead, yearHead);
    return 0;
}