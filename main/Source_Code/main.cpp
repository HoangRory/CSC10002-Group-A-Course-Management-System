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
    if (LoggingMain(accHead, user, pass, role))
        return;
    SyncInForStudent(yearHead, accHead);
    SyncFullName(yearHead, accHead);
    MainMenu(yearHead, accHead, user, pass, role);
}

int main()
{
    Account *accHead = nullptr;
    Year *yearHead = nullptr;

    initWindow(500, 500);
    // SetWindowSize(500,500);
    system("title Course Management System");

    Merge_year_sem(accHead, yearHead);

    ViewClass(yearHead);
    ViewStudentsClass(yearHead);
    ViewCourse(yearHead);
    ViewStudentCourse(yearHead);
    EradicateLL(accHead, yearHead);
    return 0;
}