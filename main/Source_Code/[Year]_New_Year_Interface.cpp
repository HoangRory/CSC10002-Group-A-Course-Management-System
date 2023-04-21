#include "../Header/Year.h"
#include "../Header/Semester.h"
#include "../Header/course.h"
#include "../Header/Utility.h"
const string separator = "\\";

void Show_Year_List(Year *yearHead)
{
    Year *year_cur = yearHead;
    TextColor(0xF1);
    int i = 0;

    goToXY(67, 11);
    cout << "=====YEAR LIST=====";

    while (year_cur)
    {
        int year_tmp = year_cur->yearStart;
        goToXY(67, 12 + i++);
        cout << "   > " << year_tmp << '-' << year_tmp + 1 << "     ";
        year_cur = year_cur->next;
    }
    TextColor(WHITE);
}

//? Check if the year is in correct format and it is already existed
int Get_CheckFormat_Existed_Year(Year *yearHead)
{
    string strYear;
    Show_Year_List(yearHead);

    goToXY(60, 18);
    TextColor(0x0E);
    cout << "Choose year";
    TextColor(63);
    for (int i = 0; i < 3; i++)
    {
        goToXY(59, 19 + i);
        cout << "                                       ";
    }

    strYear = Limit_Input(61, 20, 9, 63);
    strYear[4] = '_';

    while (!isValidYear(strYear) || !checkYear(yearHead, stoi(strYear.substr(0, 4))))
    {
        string message = "Invalid year format or system hadn't had this year yet!\nPlease retry.";
        string title = "Error";
        Message_Warning(message, title);
        goToXY(59, 20);
        cout << "                                       ";
        strYear = Limit_Input(61, 20, 9, 63);
        strYear[4] = '_';
    }
    TextColor(7);
    return stoi(strYear.substr(0, 4));
}

Year *RecoverFile()
{
    Year *headYear = nullptr;
    int numofYear = 0;
    // import existing years and classes
    loadingFile(headYear, numofYear);

    Year *yearTMP = headYear;
    while (yearTMP)
    {
        yearTMP->NoSemester = Read_All_Semester(yearTMP->yearStart); // read the semesters in years
        readAllFileCourses(yearTMP->NoSemester);
        yearTMP = yearTMP->next;
    }
    return headYear;
}

void Interface_New_Year(Year *yearHead)
{
    Year *year_cur = yearHead;
    string strYear;
    system("cls");

    Render_NewYear();
    Show_Year_List(yearHead);

    goToXY(52, 18);
    TextColor(0x0E);
    cout << "Choose year (Enter -1 to back)";
    TextColor(63);
    for (int i = 0; i < 3; i++)
    {
        goToXY(50, 19 + i);
        cout << "                                                  ";
    }

    strYear = Limit_Input(52, 20, 9, 63);
    TextColor(7);
    if (strYear == "-1")
        return;
    strYear[4] = '_';

    while (!isValidYear(strYear))
    {
        string message = "Invalid year format or already has!\nPlease retry.";
        string title = "Error";
        Message_Warning(message, title);
        TextColor(63);
        goToXY(50, 20);
        cout << "                                                  ";
        strYear = Limit_Input(52, 20, 9, 63);
        strYear[4] = '_';
    }
    TextColor(7);
    int start = stoi(strYear.substr(0, 4));

    createSchoolYear(yearHead, start);
    return;
}
