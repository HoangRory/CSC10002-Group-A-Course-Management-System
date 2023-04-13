#include "../Header/Year.h"
#include "../Header/Semester.h"
const string separator = "\\";

void Show_Year_List(Year *yearHead)
{
    Year *year_cur = yearHead;
    cout << "Year list: \n";
    while (year_cur)
    {
        int year_tmp = year_cur->yearStart;
        cout << year_tmp << '-' << year_tmp + 1 << "\n";
        year_cur = year_cur->next;
    }
}

//? Check if the year is in correct format and it is already existed
int Get_CheckFormat_Existed_Year(Year *yearHead)
{
    string strYear;
    Show_Year_List(yearHead);
    cout << "\n==> Please choose the year (yyyy-yyyy): ";
    cin >> strYear;
    strYear[4] = '_';

    while (!isValidYear(strYear) || !checkYear(yearHead, stoi(strYear.substr(0, 4))))
    {
        cout << "Invalid year format or already has, please retry.\n";
        cout << "Enter the year you want to create (yyyy-yyyy): ";
        cin.ignore();
        getline(cin, strYear);
        strYear[4] = '_';
    }
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
        yearTMP = yearTMP->next;
    }
    return headYear;
}

void Interface_New_Year(Year *yearHead)
{
    Year *year_cur = yearHead;
    system("cls");
    cout << "\n====== ADDING NEW SCHOOL YEAR ======\n";

    Show_Year_List(yearHead);

    cout << "Enter -1 to return.\n";
    cout << "Enter the year you want to create (yyyy-yyyy): ";
    string newyear;
    cin >> newyear;
    if (newyear == "-1")
        return;
    while (!isValidYear(newyear)) // check if the year is valid
    {
        cout << "Invalid year format, please retry.\n";
        cout << "Enter the year you want to create (yyyy-yyyy): ";
        cin.ignore();
        getline(cin, newyear);
    }
    int start = stoi(newyear.substr(0, 4));

    createSchoolYear(yearHead, start);
    return;
}
