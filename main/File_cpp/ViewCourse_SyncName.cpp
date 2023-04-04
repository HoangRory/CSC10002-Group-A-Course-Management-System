#include "../Header/Semester.h"

// todo Alternate to sync more efficiently
void SyncFullName(Semester *semHead, Account *accHead)
{
    Semester *sem_cur = semHead;
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
}

void viewCourse(Semester *semHead)
{
    Semester *sem_cur = semHead;
    cout << "List of courses: \n";
    for (int i = 0; i < 88; i++)
        cout << '=';

    cout << '\n'
         << setw(13) << "|     Year   "
         << setw(15) << " | Semester | "
         << setw(15) << " Course ID   | "
         << setw(25) << "    Course name        | "
         << setw(21) << "Teacher name   | " << '\n';

    for (int i = 0; i < 88; i++)
        cout << '=';
    cout << "\n";

    while (sem_cur)
    {
        Course *cour = sem_cur->course;
        while (cour)
        {
            cout << "| " << sem_cur->Year << " - " << sem_cur->Year + 1 << "  |";
            cout << "     " << sem_cur->No << "    |";

            cout << setw(11) << cour->CourseID << "   | ";

            cout << setw(20) << cour->Name << setw(5) << "| ";

            cout << setw(16) << cour->TeacherName << setw(5) << "|\n";

            for (int i = 0; i < 88; i++)
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
                if (choice < 4)
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

void NewSemesterMain(Semester *&semHead, int yr, int num_year, int num_smt, Account *accHead, int role)
{
    system("cls");
    cout << "\n";
    Read_multi_SMT(semHead, yr, num_year, num_smt);
    SyncFullName(semHead, accHead);
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