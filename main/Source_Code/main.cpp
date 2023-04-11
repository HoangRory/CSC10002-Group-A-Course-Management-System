#include "../Header/Semester.h"
#include "../Header/Login.h"
#include "../Header/Year.h"

void Merge_year_sem(Account *&accHead, Year *&yearHead)
{
    yearHead = RecoverFile();
    string user = "", pass = "";
    int role;
    LoggingMain(accHead, user, pass, role);
    SyncFullName(yearHead, accHead);
    NewYearMain(yearHead, accHead, role);
}

void EradicateLL(Account *&accHead, Year *&yearHead)
{
    DelAccount(accHead);
    DeleteYear(yearHead);
}

int main()
{
    Account *accHead = nullptr;
    Year *yearHead = nullptr;
    Merge_year_sem(accHead, yearHead);

    EradicateLL(accHead, yearHead);
    return 0;
}