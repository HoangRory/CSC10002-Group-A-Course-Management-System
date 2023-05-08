#include "../Header/Year.h"
#include "../Header/Semester.h"
#include "../Header/Login.h"
#include "../Header/course.h"
#include "../Header/Utility.h"

void Staff_Main(Year *yearHead, Account *accHead, string &user, string &pass, int &role)
{
    system("cls");
    Render_Menu(59, 3);

    vector<string> menu;
    menu.push_back("Account");
    menu.push_back("View");   //! 1 nui` view j do
    menu.push_back("Add");    //! 1 nui` add j do
    menu.push_back("Modify"); //! 1 nui` modify j do
    menu.push_back("Import / Export");
    menu.push_back("Quit");

    int choice = Draw_XY(menu, 60, 12, 7, 25);
    int ye;
    Year *year_cur;
    string mess;
    Student *student_cur = nullptr;
    Semester *curSem;
    switch (choice) // Do the choice
    {
    case 0: //? Account
        if (AccountAlteration(yearHead, accHead, user, pass, role))
            return;
        if (role == 1)
        {
            student_cur = findStudentbyID(user, yearHead);
            Student_Main(yearHead, accHead, student_cur, user, pass, role);
            return;
        }
        break;
    case 1:
        //? View
        Staff_View(yearHead);
        break;
    case 2:
        //? Adding year/semester/course
        New_Stuff(yearHead, accHead); // case 2:
        SyncFullName(yearHead, accHead);
        break;
    case 3:
        //? Modify year/semester/course
        system("cls");
        initModify(yearHead);
        SyncFullName(yearHead, accHead);
        // Recursion back to the StaffMain function
        break;
    case 4:
        //? Import/ Export
        Interface_Import_Export(yearHead);
        break;
    case 5:
        //? Save changes and quit
        mess = "Do you want to save all the changes?";
        if (Message_YesNo(mess, "Notice!"))
        {
            Output(yearHead);  // write down all the year
            Outyear(yearHead); // write down each year in4
            mess = "File save!\nNow clean up and close!";
            Message_Warning(mess, "Quit");
        }

        cout << "Cleaned up the system";
        Pause();
        return;
    }
    Staff_Main(yearHead, accHead, user, pass, role);
    return;
}

void Teacher_Main()
{
    system("cls");
    Render_Menu(59, 3);

    vector<string> menu;
    menu.push_back("Account");
    //? push command here

    int choice = Draw_XY(menu, 66, 12, 5, 20);
    int ye;
    Year *year_cur;
    string mess;
    // todo Teacher co the xem khoa, xem hoc sinh,...
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

void Student_Main(Year *yearHead, Account *accHead, Student *student_cur, string &user, string &pass, int &role)
{
    system("cls");
    Render_Student(35, 3);

    vector<string> menu;
    menu.push_back("Account");
    menu.push_back("Your Course");
    menu.push_back("Your ScoreBoard");
    menu.push_back("Quit");

    int opt = Draw_XY(menu, 60, 12, 4, 24);
    switch (opt)
    {
    case 0:
        //?
        if (AccountAlteration(yearHead, accHead, user, pass, role))
            return;
        if (role == 3 || role == 2)
        {
            Staff_Main(yearHead, accHead, user, pass, role);
            return;
        }
        break;
    case 1:
        //? Add a new semester
        Interface_ViewCoursesOfUser(student_cur, yearHead);
        // Recursion back to the StaffMain function
        break;
    case 2:
        //? Add a new course
        Interface_ViewScoreBoardOfUser(student_cur, yearHead);
        // Recursion back to the StaffMain function
        break;
    case 3:
        return;
    }
    Student_Main(yearHead, accHead, student_cur, user, pass, role);
}

void Main_Menu(Year *yearHead, Account *accHead, string &user, string &pass, int &role)
{
    system("cls");
    if (role == 2)
        role = 3;
    Student *student_cur = nullptr;

    //! Read year
    //! In add the semester in each read year
    // SyncFullName(yearHead, accHead);
    switch (role)
    {
    case 1:
        //? StudentMain
        student_cur = findStudentbyID(user, yearHead);
        Student_Main(yearHead, accHead, student_cur, user, pass, role);
        break;
    case 3:
        //? StaffMain
        Staff_Main(yearHead, accHead, user, pass, role);
        break;
    }

    return;
}