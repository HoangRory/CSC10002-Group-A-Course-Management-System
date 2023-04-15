#include "../Header/Semester.h"
#include "../Header/Login.h"
#include "../Header/Year.h"
#include "../Header/Utility.h"

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
    if (LoggingMain(accHead, user, pass, role))
        return;
    SyncFullName(yearHead, accHead);
    NewYearMain(yearHead, accHead, role);
}

int main()
{
    Account *accHead = nullptr;
    Year *yearHead = nullptr;

    initWindow(500, 500);
    // SetWindowSize(500,500);
    system("title Course Management System");

    Merge_year_sem(accHead, yearHead);

    EradicateLL(accHead, yearHead);
    return 0;
}