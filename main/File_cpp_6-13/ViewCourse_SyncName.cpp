#include "../Header/Semester.h"

// todo Alternate to sync more efficiently
// void SyncFullName(Semester *semHead, Account *accHead)
// {
//     Semester *sem_cur = semHead;
//     while (sem_cur)
//     {
//         Course *cse = sem_cur->course;
//         while (cse)
//         {
//             StudentCourse *stcse = cse->studentCourse;
//             while (stcse)
//             {
//                 Account *acc_cur = accHead;
//                 while (acc_cur)
//                 {
//                     if (stcse->FullName != "")
//                         break;
//                     if (acc_cur->username == stcse->ID)
//                     {
//                         stcse->FullName = acc_cur->lastName + ' ' + acc_cur->firstName;
//                         break;
//                     }
//                     acc_cur = acc_cur->next;
//                 }
//                 stcse = stcse->next;
//             }
//             cse = cse->next;
//         }
//         sem_cur = sem_cur->next;
//     }
// }

void SyncFullName(Year *yearHead, Account *accHead)
{
    Year *year_cur = yearHead;
    while (year_cur)
    {
        Semester *sem_cur = yearcur->semester;
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

void ViewCourse(Year *yearHead)
{
    Year *year_cur = yearHead;
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    int cnt = 0;
    while (year_cur)
    {
        cnt++;
        year_cur = year_cur->next;
    }
    string *menu = new string[cnt + 2];
    menu[0] = "List of year\n";
    menu[cnt + 1] = "\n\n(Using your arrow on the keyboard to move the choice and enter to select!)\n\n";
    year_cur = yearHead;
    for (int i = 1; i <= cnt; i++)
    {
        menu[i] = "+ " + to_string(year_cur->Year) + " - " + to_string(year_cur->Year + 1) + "\n";
        year_cur = year_cur->next;
    }
    int opt = 1;
    bool stop = false;
    cout << "Choose the year you want to view the course: \n";
    for (int i = 0; i < cnt + 2; i++)
    {
        if (i == opt)
        {
            SetConsoleTextAttribute(h, LIGHT_GREEN);
            cout << menu[i];
            SetConsoleTextAttribute(h, WHITE);
        }
        else
            cout << menu[i];
    }

    while (!stop)
        if (_kbhit())
        {
            switch (_getch())
            {
            case UP:
                if (opt > 1)
                    opt--;
                break;
            case DOWN:
                if (opt < cnt + 1)
                    opt++;
                break;
            case ENTER:
                stop = true;
                break;
            }
            system("cls");
            if (stop)
                break;
            cout << "Choose the year you want to view the course: \n";
            for (int i = 0; i < cnt + 2; i++)
            {
                if (i == opt)
                {
                    SetConsoleTextAttribute(h, LIGHT_GREEN);
                    cout << menu[i];
                    SetConsoleTextAttribute(h, WHITE);
                }
                else
                    cout << menu[i];
            }
        }
    int choice = stoi(menu[opt].substr(2, 4));
    delete[] menu;
    year_cur = yearHead;
    while (year_cur)
    {
        if (year_cur->Year == choice)
            break;
        year_cur = year_cur->next;
    }
    viewCourseInYear(year_cur->semester);
}
void viewCourseInYear(Semester *semHead)
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    Semester *sem_cur = semHead;
    // cout << "List of courses: \n";
    for (int i = 0; i < 86; i++)
        cout << '=';
    SetConsoleTextAttribute(h, 0xF8);
    cout << '\n';
    cout << setw(40) << "Year: " << sem_cur->Year << " - " << sem_cur->Year + 1 << setw(36) << '\n';
    SetConsoleTextAttribute(h, 15);
    for (int i = 0; i < 86; i++)
        cout << '=';

    cout << "\n|  Semester  |"
         << setw(14) << "Course ID" << setw(6) << '|'
         << setw(20) << "Course name" << setw(10) << '|'
         << setw(17) << "Teacher name" << setw(5) << '|' << '\n';

    for (int i = 0; i < 86; i++)
        cout << '=';
    cout << "\n";

    while (sem_cur)
    {
        Course *cour = sem_cur->course;
        while (cour)
        {
            cout << '|' << setw(6) << sem_cur->No << setw(7) << '|';

            cout << setw(13) << cour->CourseID << setw(7) << '|';
            int len = cour->Name.length();
            cout << setw(len + 5) << cour->Name << setw(30 - len - 5) << '|';

            len = cour->TeacherName.length();
            cout << setw(len + 3) << cour->TeacherName << setw(22 - len - 3) << '|' << '\n';

            for (int i = 0; i < 86; i++)
                cout << '=';
            cout << "\n";

            cour = cour->next;
        }
        sem_cur = sem_cur->next;
    }
    cout << "\n";
}

void StaffMain(Semester *&semHead)
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, 240);
    cout << "Welcome to Staff mode!\n";
    SetConsoleTextAttribute(h, WHITE);
    string *menu = new string[6];
    menu[0] = "\nStaff privilege      \n";
    menu[1] = "- View course          \n";
    menu[2] = "- Add new semester     \n";
    menu[3] = "- Modify               \n";
    menu[4] = "- Save changes and quit\n";
    menu[5] = "- Exit                 \n";

    int choice = 1;
    bool stop = false;

    for (int i = 0; i < 6; i++)
    {
        if (i == choice)
        {
            SetConsoleTextAttribute(h, YELLOW);
            cout << menu[i];
            SetConsoleTextAttribute(h, WHITE);
        }
        else
            cout << menu[i];
    }
    SetConsoleTextAttribute(h, GREEN);
    cout << "\n\n(Using your arrow on the keyboard to move the choice and enter to select!)\n\n";
    SetConsoleTextAttribute(h, WHITE);

    ShowConsoleCursor(false);
    while (!stop)
    {
        if (_kbhit())
        {
            switch (_getch())
            {
            case UP:
                if (choice > 1)
                    choice--;
                break;
            case DOWN:
                if (choice < 5)
                    choice++;
                break;
            case ENTER:
                stop = true;
                break;
            }
            if (stop)
                break;

            system("cls");
            for (int i = 0; i < 6; i++)
            {
                if (i == choice)
                {
                    SetConsoleTextAttribute(h, YELLOW);
                    cout << menu[i];
                    SetConsoleTextAttribute(h, WHITE);
                }
                else
                    cout << menu[i];
            }
            SetConsoleTextAttribute(h, GREEN);
            cout << "\n\n(Using your arrow on the keyboard to move the choice and enter to select!)\n\n";
            SetConsoleTextAttribute(h, WHITE);
        }
    }
    delete[] menu;
    ShowConsoleCursor(true);

    switch (choice)
    {
    case 1:
        system("cls");
        cout << "\n";
        viewCourse(semHead);
        StaffMain(semHead);
        return;
    case 2:
        system("cls");
        cout << "\n";
        Interface_New_Sem(semHead);
        // Recursion back to the StaffMain function
        StaffMain(semHead);
        return;
    case 3:
        system("cls");
        cout << "\n";
        initModify(semHead);
        // Recursion back to the StaffMain function
        StaffMain(semHead);
        return;
    case 4:
        cout << "\n";
        Output(semHead);

        cout << "Cleaning up the system";
        for (int i = 0; i < 8; i++)
        {
            cout << '.';
            Sleep(200);
        }
        cout << "\nSaving completed\n";
        return;

    case 5:
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
    SyncFullName(yearHead, accHead);
    viewCourse(semHead);
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
        StaffMain(semHead);
        break;
    }
}