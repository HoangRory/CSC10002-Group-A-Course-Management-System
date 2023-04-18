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
    if (LoggingMain(accHead, user, pass, role))
        return;
    MainMenu(yearHead, accHead, user, pass, role);
}

int main()
{
    Account *accHead = nullptr;
    Year *yearHead = nullptr;

    initWindow(1200,600);
    // SetWindowSize(1500,1000);
    system("title Course Management System");

    Merge_year_sem(accHead, yearHead);

    // ViewClass(yearHead);

    ViewStudentsClass(yearHead);
    
    // ViewCourse(yearHead);
    
    // ViewStudentCourse(yearHead);
    
    // system("cls");

    // Semester *curSem = chooseSemesterbyOption(yearHead->NoSemester);
    // viewScoreBoardCourse(curSem->course);

    Class *Class = yearHead->Class;
    viewScoreboardClass(Class);

    EradicateLL(accHead, yearHead);
    return 0;
}