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
    // if (LoggingMain(accHead, user, pass, role))
    //     return;
    LoggingIn(accHead, user, pass, role);
    Main_Menu(yearHead, accHead, user, pass, role);
    ViewCourse(yearHead);
}

int main()
{
    Account *accHead = nullptr;
    Year *yearHead = nullptr;
    ShowConsoleCursor(false);

    initWindow(1200, 600);
    // SetWindowSize(1500,1000);
    system("title Course Management System");

    Merge_year_sem(accHead, yearHead);

    system("mode 1000, 5000");
    // task 14
    //  ViewCoursesOfAStudent(yearHead->Class->StudentClass->accStudent->next, yearHead);
    //  ViewClass(yearHead);
    // Interface_ViewStudentClass(yearHead);
    //  ViewCourse(yearHead);

    // Interface_ViewStudentCourse(yearHead);

    // system("cls");

    // task 19
    //  exportListStudentCourse(yearHead->NoSemester);

    // Semester *curSem = chooseSemesterbyOption_XY(yearHead->NoSemester, 60, 15, 5);
    // viewScoreBoardCourse(curSem->course);
    // task 22
    // UpdateStudentResult(yearHead);
    // task 23
    // Class *Class = yearHead->Class;
    // viewScoreboardClass(Class);
    // //task 24
    // ViewScoreboard(yearHead->Class->StudentClass->accStudent->next, yearHead->NoSemester->course);

    EradicateLL(accHead, yearHead);
    return 0;
}