#include "../Header/Semester.h"
#include "../Header/Year.h"
#include "../Header/Login.h"
#include "../Header/Utility.h"

Course *Part_Of_Course(Course *&curCourse, Semester *&sem_cur)
{
    Render_ViewCourse();

    int row = 8;
    goToXY(25, row++);
    for (int i = 0; i < 95; i++) // Display the table
        cout << '=';

    goToXY(25, row++);
    TextColor(0xF1);
    cout << setw(45) << "Year: " << sem_cur->Year << " - " << sem_cur->Year + 1 << setw(40) << '\n';
    TextColor(WHITE);

    goToXY(25, row++);
    for (int i = 0; i < 95; i++)
        cout << '=';

    goToXY(25, row++);
    cout << "|  Semester  |"
         << setw(14) << "Course ID" << setw(6) << '|'
         << setw(23) << "Course name" << setw(13) << '|'
         << setw(18) << "Teacher name" << setw(7) << '|';

    goToXY(25, row++);
    for (int i = 0; i < 95; i++)
        cout << '=';

    goToXY(25, row++);
    Course *cour = curCourse;
    Course *prev = nullptr;
    while (sem_cur)
    {
        while (cour)
        {
            cout << '|' << setw(6) << sem_cur->No << setw(7) << '|';

            cout << setw(13) << cour->CourseID << setw(7) << '|';
            int len = cour->Name.length();

            cout << setw(len + 2) << cour->Name << setw(36 - len - 2) << '|';

            len = cour->TeacherName.length();
            cout << setw(len + 3) << cour->TeacherName << setw(25 - len - 3) << '|';

            goToXY(25, row++);
            for (int i = 0; i < 95; i++)
                cout << '=';

            goToXY(25, row++);
            if (row >= 8 + 20)
                return cour;

            prev = cour;
            cour = cour->next;
        }
        if (!cour)
        {
            if (!sem_cur->next)
                return prev;
            sem_cur = sem_cur->next;
            cour = sem_cur->course;
        }
    }
    return prev; //!
}
//? View all the course in the school
void ViewCourse(Year *yearHead)
{
    ShowConsoleCursor(0);
    // string arrow = "<<-->>";
    Semester *sem_cur = yearHead->NoSemester;
    Course *curCourse = sem_cur->course;
    Course *cour = Part_Of_Course(curCourse, sem_cur);

    while (1)
    {
        int c = _getch();
        switch (c)
        {
        case UP:
            if (!cour)
                break;
            while (cour != curCourse)
            {
                cour = cour->prev;
                if (!cour)
                {
                    sem_cur = sem_cur->prev;
                    cour = sem_cur->course;
                    while (cour->next)
                        cour = cour->next;
                }
            }
            if (curCourse->prev || sem_cur->prev)
            {
                for (int i = 0; i < 7; i++)
                {

                    curCourse = curCourse->prev;
                    if (!curCourse)
                    {
                        sem_cur = sem_cur->prev;
                        curCourse = sem_cur->course;
                        while (curCourse->next)
                            curCourse = curCourse->next;
                    }
                }
                system("cls");
                cour = Part_Of_Course(curCourse, sem_cur);
            }
            break;
        case DOWN:
            if (!cour)
                break;
            if (cour->next || sem_cur->next)
            {
                if (!cour->next)
                {
                    sem_cur = sem_cur->next;
                    curCourse = sem_cur->course;
                }
                else
                    curCourse = cour->next;
                system("cls");
                cour = Part_Of_Course(curCourse, sem_cur);
            }
            break;
        case LEFT:
            if (yearHead->prev)
            {
                yearHead = yearHead->prev;
                system("cls");
                sem_cur = yearHead->NoSemester;
                curCourse = sem_cur->course;
                cour = Part_Of_Course(curCourse, sem_cur);
            }
            break;

        case RIGHT:
            if (yearHead->next)
            {
                yearHead = yearHead->next;
                system("cls");
                sem_cur = yearHead->NoSemester;
                curCourse = sem_cur->course;
                cour = Part_Of_Course(curCourse, sem_cur);
            }
            break;

        case ENTER:
            ShowConsoleCursor(1);
            return;
        case ESC:
            ShowConsoleCursor(1);
            return;
        }
    }
}

void StaffMain(Year *yearHead, Account *accHead, string &user, string &pass, int &role)
{
    system("cls");
    Render_Menu();

    vector<string> menu;
    menu.push_back("Account options");
    //! Merge 1 nùi view
    menu.push_back("View course");
    //! Merge 1 nùi add
    // menu.push_back("Add a new year");
    // menu.push_back("Add a new semester");
    // menu.push_back("Add a new course");
    menu.push_back("Add");
    //! 1 nùi modify
    menu.push_back("Modify");
    menu.push_back("Quit");

    int choice = Draw_XY(menu, 60, 12,5,20);
    int ye;
    Year *year_cur;
    string mess;

    switch (choice) // Do the choice
    {
    case 0:
        if (AccountAlteration(accHead, user, pass, role))
            return;
        StaffMain(yearHead, accHead, user, pass, role);
        return;
    case 1:
        //? View course
        system("cls");
        ViewCourse(yearHead);
        StaffMain(yearHead, accHead, user, pass, role); // Recursion back to the StaffMain function
        return;
    case 2:
        //? Adding year/semester/course
        New_Stuff(yearHead); // case 2:
        StaffMain(yearHead, accHead, user, pass, role);
        return;
    case 3:
        //? Modify year/semester/course
        system("cls");
        initModify(yearHead);
        // Recursion back to the StaffMain function
        StaffMain(yearHead, accHead, user, pass, role);
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

void MainMenu(Year *yearHead, Account *accHead, string &user, string &pass, int &role)
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
        StaffMain(yearHead, accHead, user, pass, role);
        break;
    }
    return;
}