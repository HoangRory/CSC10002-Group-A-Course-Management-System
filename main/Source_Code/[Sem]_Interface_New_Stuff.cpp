#include "../Header/Utility.h"
#include "../Header/Semester.h"
#include "../Header/Year.h"
#include "../Header/Help.h"

void New_Stuff(Year *yearHead, Account *accHead)
{
    system("cls");
    Render_NewInfo(55, 3);

    vector<string> menu;
    menu.push_back("Add a new year");
    menu.push_back("Add class");
    menu.push_back("Add a new semester");
    menu.push_back("Add a new course");
    menu.push_back("Back to main menu");

    int ye;
    Year *year_cur = nullptr;

    int opt = Draw_XY(menu, 60, 12, 5, 24, 63);
    switch (opt)
    {
    case 0:
        //? Add a new year
        Interface_New_Year(yearHead, accHead);
        break;
    case 1:
        //? Add class
        AddClass(yearHead, accHead);
        break;
    case 2:
        //? Add a new semester
        system("cls");
        Interface_New_Sem(yearHead);
        // Recursion back to the StaffMain function
        break;
    case 3:
        //? Add a new course
        year_cur = chooseYearbyOption_XY(yearHead, 60, 12, 5);
        if (!year_cur)
            break;

        AddingCourse(year_cur->NoSemester, yearHead);
        // Recursion back to the StaffMain function
        break;
    case 4:
        return;
    }
    New_Stuff(yearHead, accHead);
    return;
}

//? Run to begin the new semester
Semester *Interface_New_Sem(Year *yearHead)
{
    Semester *semCurrent = AddSemester(yearHead); // New semester and return the default for next actions
    string mess;
    if (!semCurrent)
        return Interface_New_Sem(yearHead);

    mess = "Do you want to add a course to this semester?";
    if (Message_YesNo(mess, "Notice"))
        AddingCourse(semCurrent, yearHead);

    system("cls");
    mess = "Do you want to add another semester?";
    if (Message_YesNo(mess, "Notice"))
        Interface_New_Sem(yearHead);
    return semCurrent;
}
