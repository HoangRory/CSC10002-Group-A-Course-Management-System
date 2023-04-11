#include "../Header/Year.h"
#include "../Header/Semester.h"
const string separator = "\\";

Year *RecoverFile()
{
    Year *headYear = nullptr;
    int numofYear = 0;
    // import existing years and classes
    loadingFile(headYear, numofYear);

    Year *yearTMP = headYear;
    while (yearTMP)
    {
        yearTMP->NoSemester = Read_All_Semester(yearTMP->yearStart);
        yearTMP = yearTMP->next;
    }
    return headYear;
}

void Interface_New_Year(Year *yearHead)
{
    Year *year_cur = yearHead;
    system("cls");
    cout << "\n======ADDING NEW SCHOOL YEAR======\n";
    cout << "Year list: \n";
    while (year_cur)
    {
        int year_tmp = year_cur->yearStart;
        cout << year_tmp << '-' << year_tmp + 1 << "\n";
        year_cur = year_cur->next;
    }

    cout << "Enter -1 to return.\n";
    cout << "Enter the year you want to create (yyyy-yyyy): ";
    string newyear;
    cin >> newyear;
    if (newyear == "-1")
        return;
    while (!isValidYear(newyear))
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
