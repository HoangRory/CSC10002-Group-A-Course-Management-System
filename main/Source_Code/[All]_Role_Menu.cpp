#include "../Header/Year.h"
#include "../Header/Semester.h"
#include "../Header/Login.h"
#include "../Header/course.h"
#include "../Header/Utility.h"

void Staff_Main(Year *yearHead, Account *accHead, string &user, string &pass, int &role)
{
    system("cls");
    Render_Menu();

    vector<string> menu;
    menu.push_back("Account options");
    //! Merge 1 nùi view
    menu.push_back("View course");
    //! Merge 1 nùi add
    menu.push_back("Add");
    //! 1 nùi modify
    menu.push_back("Modify");
    menu.push_back("Quit");

    int choice = Draw_XY(menu, 60, 12, 5, 20);
    int ye;
    Year *year_cur;
    string mess;

    switch (choice) // Do the choice
    {
    case 0:
        if (AccountAlteration(accHead, user, pass, role))
            return;
        Staff_Main(yearHead, accHead, user, pass, role);
        return;
    case 1:
        //? View course
        system("cls");
        ViewCourse(yearHead);
        Staff_Main(yearHead, accHead, user, pass, role); // Recursion back to the StaffMain function
        return;
    case 2:
        //? Adding year/semester/course
        New_Stuff(yearHead); // case 2:
        Staff_Main(yearHead, accHead, user, pass, role);
        return;
    case 3:
        //? Modify year/semester/course
        system("cls");
        initModify(yearHead);
        // Recursion back to the StaffMain function
        Staff_Main(yearHead, accHead, user, pass, role);
        return;
    case 4:
        //? Save changes and quit
        Output(yearHead);  // write down all the year
        Outyear(yearHead); // write down each year in4

        mess = "File save!\nNow clean up and close!";
        Message_Warning(mess, "Quit");
        cout << "Cleaning up the system";
        return;
    }
}

void Teacher_Main()
{
    system("cls");
    Render_Menu();

    vector<string> menu;
    menu.push_back("Account options");
    //? push command here

    int choice = Draw_XY(menu, 60, 12, 5, 20);
    int ye;
    Year *year_cur;
    string mess;
    //todo Teacher co the xem khoa, xem hoc sinh,...
    switch (choice) // Do the choice
    {
    case 0:
        //? Account options
        // AccountAlteration();
        break;
    case 1:
        //? 
        // ViewCourse();
        break;
    case 2:
        //? Adding year/semester/course
        // New_Stuff();
        break;
    case 3:
        //? Modify year/semester/course
        // initModify();
        break;
    case 4:
        //? Save changes and quit

        break;
    }
}

void Student_Main()
{
    system("cls");
    Render_Menu();

    vector<string> menu;
    menu.push_back("Account options");
}

void Main_Menu(Year *yearHead, Account *accHead, string &user, string &pass, int &role)
{
    system("cls");
    //! Read year
    //! In add the semester in each read year
    // SyncFullName(yearHead, accHead);
    switch (role)
    {
    case 1:
        //? StudentMain
        // cout << "You've entered the student main menu\n";
        break;
    case 2:
        //? TeacherMain
        // cout << "You've entered the teacher main menu\n";
        break;
    case 3:
        //? StaffMain
        Staff_Main(yearHead, accHead, user, pass, role);
        break;
    }
    return;
}