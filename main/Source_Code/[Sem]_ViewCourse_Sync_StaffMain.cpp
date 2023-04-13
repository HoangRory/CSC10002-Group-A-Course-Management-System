#include "../Header/Semester.h"
#include "../Header/Year.h"
#include "../Header/Login.h"
#include "../Header/Utility.h"

// todo Alternate to sync more efficiently

//? get the fullname from account linked list
void SyncFullName(Year *yearHead, Account *accHead)
{
    Year *year_cur = yearHead;
    while (year_cur)
    {
        Semester *sem_cur = year_cur->NoSemester;
        while (sem_cur)
        {
            Course *cse = sem_cur->course;
            while (cse)
            {
                StudentCourse *stcse = cse->studentCourse;
                while (stcse)
                {
                    Account *acc_cur = accHead;
                    while (acc_cur)
                    {
                        if (stcse->FullName != "")
                            break;
                        if (acc_cur->username == stcse->ID)
                        {
                            stcse->FullName = acc_cur->lastName + ' ' + acc_cur->firstName;
                            break;
                        }
                        acc_cur = acc_cur->next;
                    }
                    stcse = stcse->next;
                }
                cse = cse->next;
            }
            sem_cur = sem_cur->next;
        }
        year_cur = year_cur->next;
    }
}

//? Show option to view course
void ViewCourse(Year *yearHead)
{
    Year *year_cur = yearHead;

    vector<string> menu;
    menu.push_back("All year");
    while (year_cur)
    {
        menu.push_back(to_string(year_cur->yearStart) + " - " + to_string(year_cur->yearStart + 1));
        year_cur = year_cur->next;
    }

    PrintView_Course();

    int opt = Draw(menu);
    system("cls");

    if (opt == 0)
    {
        ViewAllCourse(yearHead);
        cout << "\n";
        system("pause");
        return;
    }

    int choice = stoi(menu[opt].substr(0, 4)); // Get the start year of the year

    year_cur = yearHead;
    while (year_cur) // move to the year
    {
        if (year_cur->yearStart == choice)
            break;
        year_cur = year_cur->next;
    }
    int i = 8;
    PrintView_Course();
    ViewCourseInYear(year_cur->NoSemester, i); // View the course in the certain year
    cout << "\n";
    system("pause");
    return;
}

//? View course in a given year
void ViewCourseInYear(Semester *semHead, int &i)
{
    if (!semHead)
        return;
    Semester *sem_cur = semHead;
    // cout << "List of courses: \n";
    goToXY(30, i++);
    for (int i = 0; i < 92; i++) // Display the table
        cout << '=';
    TextColor(0xF8);
    goToXY(30, i++);
    cout << setw(44) << "Year: " << sem_cur->Year << " - " << sem_cur->Year + 1 << setw(38) << '\n';
    TextColor(WHITE);
    goToXY(30, i++);
    for (int i = 0; i < 92; i++)
        cout << '=';

    goToXY(30, i++);

    cout << "|  Semester  |"
         << setw(14) << "Course ID" << setw(6) << '|'
         << setw(20) << "Course name" << setw(13) << '|'
         << setw(18) << "Teacher name" << setw(7) << '|';

    goToXY(30, i++);

    for (int i = 0; i < 92; i++)
        cout << '=';
    goToXY(30, i++);

    while (sem_cur)
    {
        Course *cour = sem_cur->course;
        while (cour)
        {
            cout << '|' << setw(6) << sem_cur->No << setw(7) << '|';

            cout << setw(13) << cour->CourseID << setw(7) << '|';
            int len = cour->Name.length();
            cout << setw(len + 5) << cour->Name << setw(33 - len - 5) << '|';

            len = cour->TeacherName.length();
            cout << setw(len + 3) << cour->TeacherName << setw(25 - len - 3) << '|';
            goToXY(30, i++);

            for (int i = 0; i < 92; i++)
                cout << '=';
            goToXY(30, i++);

            cour = cour->next;
        }
        sem_cur = sem_cur->next;
    }
}

//? View all the course in the school
void ViewAllCourse(Year *yearHead)
{
    PrintView_Course();
    Year *year_cur = yearHead;
    int i = 8;
    while (year_cur)
    {
        // show the year
        ViewCourseInYear(year_cur->NoSemester, i);
        year_cur = year_cur->next;
    }
}

void StaffMain(Year *yearHead)
{
    system("cls");
    PrintMenu();

    vector<string> menu;
    menu.push_back("View course");
    menu.push_back("Add a new year");
    menu.push_back("Add a new semester");
    menu.push_back("Add a new course");
    menu.push_back("Modify");
    menu.push_back("Save changes and quit");
    menu.push_back("Quit");

    int choice = Draw(menu);

    switch (choice) // Do the choice
    {
    case 0:
        //? View course
        system("cls");
        cout << "\n";
        ViewCourse(yearHead);
        StaffMain(yearHead); // Recursion back to the StaffMain function
        return;
    case 1:
        //? Add a new year
        Interface_New_Year(yearHead);
        StaffMain(yearHead); // Recursion back to the StaffMain function
        return;
    case 2:
        //? Add a new semester
        system("cls");
        cout << "\n";
        Interface_New_Sem(yearHead);
        // Recursion back to the StaffMain function
        StaffMain(yearHead);
        return;
    case 3:
        //? Add a new course
        break;
    case 4:
        //? Modify year/semester/course
        system("cls");
        cout << "\n";
        initModify(yearHead);
        // Recursion back to the StaffMain function
        StaffMain(yearHead);
        return;
    case 5:
        //? Save changes and quit
        cout << "\n";
        Output(yearHead);  // write down all the year
        Outyear(yearHead); // write down each year in4

        cout << "Cleaning up the system";
        for (int i = 0; i < 8; i++) // Show the loading
        {
            cout << '.';
            Sleep(200);
        }
        cout << "\nSaving completed\n";
        return;

    case 6:
        //? Exit
        cout << "\n";
        cout << "Cleaning up the system";
        for (int i = 0; i < 8; i++)
        {
            cout << '.';
            Sleep(200);
        }
        cout << "\nClosing system\n";
        return;
    }
}

void NewYearMain(Year *&yearHead, Account *accHead, int role)
{
    system("cls");
    cout << "\n";
    //! Read year
    //! In add the semester in each read year
    Year *year_cur = yearHead;
    yearHead->NoSemester = Read_All_Semester(yearHead->yearStart);
    // SyncFullName(yearHead, accHead);
    switch (role)
    {
    case 1:
        //? StudentMain
        cout << "You've entered the student main menu\n";
        break;
    case 2:
        //? TeacherMain
        cout << "You've entered the teacher main menu\n";
        break;
    case 3:
        //? StaffMain
        StaffMain(yearHead);
        break;
    }
    return;
}