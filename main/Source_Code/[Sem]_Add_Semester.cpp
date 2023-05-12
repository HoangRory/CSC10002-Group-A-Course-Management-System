#include "../Header/Utility.h"
#include "../Header/Semester.h"
#include "../Header/Year.h"
#include "../Header/Help.h"

//? Return -1 if date1 < date2, 1 if date1 > date2, 0 if date1 = date2
int compareDate(string date1, string date2)
{
    // Extract day, month, and year from date1
    int day1 = std::stoi(date1.substr(0, 2));
    int month1 = std::stoi(date1.substr(3, 2));
    int year1 = std::stoi(date1.substr(6, 4));

    // Extract day, month, and year from date2
    int day2 = std::stoi(date2.substr(0, 2));
    int month2 = std::stoi(date2.substr(3, 2));
    int year2 = std::stoi(date2.substr(6, 4));

    // Compare the years
    if (year1 < year2)
        return -1;
    else if (year1 > year2)
        return 1;

    // Compare the months
    if (month1 < month2)
        return -1;
    else if (month1 > month2)
        return 1;

    // Compare the days
    if (day1 < day2)
        return -1;
    else if (day1 > day2)
        return 1;

    // The dates are equal
    return 0;
}

//? Adding a semester and return its pointer
Semester *AddSemester(Year *yearHead)
{
    system("cls");
    Render_Semester(50, 3);
    // Print the list of year
    Year *year_cur = yearHead;
    // Get the year and semester
    year_cur = chooseYearbyOption_XY(yearHead, 60, 12, 5);
    if (!year_cur)
        return nullptr;
    string tmp;

    vector<string> small_menu;
    small_menu.push_back("1st semester");
    small_menu.push_back("2nd semester");
    small_menu.push_back("3rd semester");
    small_menu.push_back("Back");
    int N = 0;
    N = Draw_XY(small_menu, 60, 12, 4, 20, 63) + 1;
    if (N == 4)
    {
        AddSemester(yearHead);
        return nullptr;
    }

    Semester *sem_cur = year_cur->NoSemester;
    Semester *prev = sem_cur;
    while (sem_cur)
    {
        if (sem_cur->No == N) // If already had, ask to modify
        {
            string mess = "This semester already exists!";
            Message_Warning(mess, "Notice");
            return AddSemester(yearHead);
        }
        prev = sem_cur;
        if (!sem_cur->next)
            break;
        sem_cur = sem_cur->next;
    }

    if (!prev) // if there is no semester to begin with, create a new head
    {
        year_cur->NoSemester = new Semester;
        sem_cur = year_cur->NoSemester;
    }
    else // create a new semester at the last position
    {
        prev->next = new Semester;
        sem_cur = prev->next;
        sem_cur->prev = prev;
    }

    sem_cur->No = N;
    sem_cur->Year = year_cur->yearStart;

    system("cls");
    string date1, date2;

    Render_Semester(50, 3);
    TextColor(63);
    for (int i = 0; i < 3; i++)
    {
        goToXY(50, 13 + i);
        cout << "                                              ";
    }
    goToXY(52, 14);
    cout << "Starting date (dd/mm/yyyy): "; // Get the date and ensure its format

    tmp = Limit_Input(80, 14, 10, 63);

    while (!isValidDate(tmp))
    {
        if (tmp == "-1")
        {
            if (sem_cur->prev)
                sem_cur->prev->next = nullptr;
            else
                year_cur->NoSemester = nullptr;
            delete sem_cur;
            return nullptr;
        }
        Message_Warning("Invalid date format!\nEnter again!", "Error");
        goToXY(50, 14);
        TextColor(63);
        cout << "                                              ";
        goToXY(52, 14);
        cout << "Starting date (dd/mm/yyyy): "; // Get the date and ensure its format
        tmp = Limit_Input(80, 14, 10, 63);
    }
    // sem_cur->startDate = tmp;
    date1 = tmp;

    TextColor(63);
    for (int i = 0; i < 3; i++)
    {
        goToXY(50, 17 + i);
        cout << "                                              ";
    }
    goToXY(52, 18);
    cout << "Ending date (dd/mm/yyyy): ";
    tmp = Limit_Input(80, 18, 10, 63);

    while (!isValidDate(tmp) || compareDate(date1, tmp) != -1)
    {
        if (tmp == "-1")
        {
            if (sem_cur->prev)
                sem_cur->prev->next = nullptr;
            else
                year_cur->NoSemester = nullptr;
            delete sem_cur;
            return nullptr;
        }

        if (isValidDate(tmp) && compareDate(date1, tmp) != -1)
            Message_Warning("Invalid date!\nEnding date must be after starting date!", "Error");
        else
            Message_Warning("Invalid date format!\nEnter again!", "Error");
        goToXY(50, 18);
        TextColor(63);
        cout << "                                              ";
        goToXY(52, 18);
        cout << "Ending date (dd/mm/yyyy): "; // Get the date and ensure its format
        tmp = Limit_Input(80, 18, 10, 63);
    }
    // sem_cur->endDate = tmp;
    date2 = tmp;
    sem_cur->startDate = date1;
    sem_cur->endDate = date2;
    // if (compareDate(date1, date2) == 1)
    // {
    //     Message_Warning("Invalid date!\nEnding date must be after starting date!", "Error");
    //     return AddSemester(yearHead);
    // }

    int Y = year_cur->yearStart;
    string out_year = to_string(Y) + '_' + to_string(Y + 1);
    string outPath = "..\\Data_file\\" + out_year + "\\smt" + to_string(N);
    string tmp_sys = "mkdir " + outPath;
    // Create a folder to store its information
    const char *cstr_path = tmp_sys.c_str();
    TextColor(7);
    goToXY(30, 25);
    system(cstr_path);
    goToXY(30, 25);
    cout << "                                                                    ";
    return sem_cur;
}

bool isStringDigits(string str)
{
    for (char ch : str)
        if (!std::isdigit(ch))
            return false;
    return true;
}
