#include "../Header/Semester.h"

void initModify(Semester *&semHead)
{
    bool stop = false;
    int opt = 1;
    string s = "Options: ";
    string s1 = "Modify semester          ";
    string s2 = "Modify course            ";
    string s3 = "Delete a course          ";
    string s4 = "Add or remove a student  ";
    string s5 = "Quit                     ";

    cout << "\nUsing your arrow on the keyboard to move the choice and enter to select!\n\n";
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

    cout << s << "\n";
    SetConsoleTextAttribute(h, 6);
    cout << s1 << "<<--\n";
    SetConsoleTextAttribute(h, 7);
    cout << s2 << "\n";
    cout << s3 << "\n";
    cout << s4 << "\n";
    cout << s5 << "\n";

    while (!stop)
    {
        system("cls");
        std::cout << "\n";
        // viewCourse(semHead);
        if (_kbhit())
        {
            switch (_getch())
            {
            //? Up arrow
            case 72:
                if (opt > 1)
                    opt--;
                break;
            //? Down arrow
            case 80:
                if (opt < 5)
                    opt++;
                break;
            //? Quit choosing
            case 'x':
                stop = true;
                cout << "Quiting!";
                break;
            //? Enter
            case 13:
                stop = true;
                cout << "You have chosen to ";
                switch (opt)
                {
                case 1:
                    cout << s1;
                    break;
                case 2:
                    cout << s2;
                    break;
                case 3:
                    cout << s3;
                    break;
                case 4:
                    cout << s4;
                    break;
                case 5:
                    cout << s5;
                    break;
                }
                break;
                cout << "!\n";
                viewCourse(semHead);
            }
            if (stop)
                break;
        }
        cout << "\nUsing your arrow on the keyboard to move the choice and enter to select!\n\n";
        switch (opt)
        {
        case 1:
            cout << s << "\n";

            SetConsoleTextAttribute(h, 6);
            cout << s1 << "<<--\n";

            SetConsoleTextAttribute(h, 7);
            cout << s2 << "\n";
            cout << s3 << "\n";
            cout << s4 << "\n";
            cout << s5 << "\n";
            break;
        case 2:
            cout << s << "\n";
            cout << s1 << "\n";

            SetConsoleTextAttribute(h, 6);
            cout << s2 << "<<--\n";

            SetConsoleTextAttribute(h, 7);
            cout << s3 << "\n";
            cout << s4 << "\n";
            cout << s5 << "\n";
            break;
        case 3:
            cout << s << "\n";
            cout << s1 << "\n";
            cout << s2 << "\n";

            SetConsoleTextAttribute(h, 6);
            cout << s3 << "<<--\n";

            SetConsoleTextAttribute(h, 7);
            cout << s4 << "\n";
            cout << s5 << "\n";
            break;
        case 4:
            cout << s << "\n";
            cout << s1 << "\n";
            cout << s2 << "\n";
            cout << s3 << "\n";

            SetConsoleTextAttribute(h, 6);
            cout << s4 << "<<--\n";

            SetConsoleTextAttribute(h, 7);
            cout << s5 << "\n";
            break;
        case 5:
            cout << s << "\n";
            cout << s1 << "\n";
            cout << s2 << "\n";
            cout << s3 << "\n";
            cout << s4 << "\n";

            SetConsoleTextAttribute(h, 6);
            cout << s5 << "<<--\n";

            SetConsoleTextAttribute(h, 7);
            break;
        }
        Sleep(150);
    }
    RunModify(semHead, opt);
}

void RunModify(Semester *&semHead, int opt)
{
    string id;
    switch (opt)
    {
    case 1:
        int sem, year;
        cout << "\n==> Please choose the year: ";
        cin >> year;
        cout << "==> Please choose the semester: ";
        cin >> sem;
        cout << "\n";
        modifySemester(semHead, sem, year);
        break;
    case 2:
        cout << "\n==> Please choose the course ID: ";
        cin >> id;
        cout << "\n";
        modifyCourse(semHead, id);
        break;
    case 3:
        cout << "\n==> Please choose the course ID: ";
        cin >> id;
        cout << "\n";
        deleteCourse(semHead, id);
        break;
    case 4:
        cout << "\n==> Please choose the student ID: ";
        cin >> id;
        cout << "\n";
        //? Showing the list of students
        addRemoveStudent(semHead, id);
        break;
    case 5:
        cout << "\n";
        cout << "Cleaning up the system...\n";
        Sleep(1000);
        cout << "Saving completed\n";
        return;
    }
    initModify(semHead);
}