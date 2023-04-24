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
    // Main_Menu(yearHead, accHead, user, pass, role);
    // ViewCourse(yearHead);
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
    // ViewCoursesOfAStudent(yearHead->Class->StudentClass->accStudent, yearHead);
    // ViewStudentCourse(yearHead->NoSemester->course->next, 15, 15);
    // ViewScoreBoardCourse(yearHead->NoSemester->course, 15, 15);
    // ViewScoreboardClass(yearHead->Class, 10, 15);
    ViewCourse(yearHead);
    EradicateLL(accHead, yearHead);
    return 0;
}