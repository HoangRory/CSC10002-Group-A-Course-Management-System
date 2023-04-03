#include "../Header/Semester.h"

void ShowConsoleCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}

void initModify(Semester *&semHead)
{
    bool stop = false;
    system("cls");
    int opt = 1;
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    string *ListOption = new string[6];
    ListOption[0] = "Options: ";
    ListOption[1] = "- Modify semester                      \n";
    ListOption[2] = "- Modify course                        \n";
    ListOption[3] = "- Delete a course                      \n";
    ListOption[4] = "- Add or remove a student from a course\n";
    ListOption[5] = "- Return                               \n";

    cout << "\n(Using your arrow on the keyboard to move the choice and enter to select!)\n\n";

    for (int i = 0; i < 6; i++)
    {
        if (i == opt)
        {
            SetConsoleTextAttribute(h, YELLOW);
            cout << ListOption[i];
            SetConsoleTextAttribute(h, WHITE);
        }
        else
            cout << ListOption[i];
    }

    while (!stop)
    {
        if (_kbhit())
        {
            system("cls");
            switch (_getch())
            {
            case UP:
                if (opt > 1)
                    opt--;
                break;
            case DOWN:
                if (opt < 5)
                    opt++;
                break;
            case ENTER:
                stop = true;
                break;
            }
            if (stop)
                break;

            SetConsoleTextAttribute(h, GREEN);
            cout << "\n(Using your arrow on the keyboard to move the choice and enter to select!)\n\n";
            SetConsoleTextAttribute(h, WHITE);

            for (int i = 0; i < 6; i++)
            {
                if (i == opt)
                {
                    SetConsoleTextAttribute(h, YELLOW);
                    cout << ListOption[i] << "<--\n";
                    SetConsoleTextAttribute(h, WHITE);
                }
                else
                    cout << ListOption[i] << "\n";
            }
        }
    }
    delete[] ListOption;

    RunModify(semHead, opt);
    return;
}

void RunModify(Semester *&semHead, int opt)
{
    string id;
    int sem, year;
    switch (opt)
    {
    case 1:
        viewCourse(semHead);
        cout << "\n==> Please choose the year (yyyy): ";
        cin >> year;
        cout << "==> Please choose the semester (1, 2, 3): ";
        cin >> sem;
        cout << "\n";
        modifySemester(semHead, sem, year);
        break;
    case 2:
        viewCourse(semHead);
        cout << "\n==> Please choose the year (yyyy): ";
        cin >> year;
        cout << "\n";
        modifyCourse(semHead, year);
        break;
    case 3:
        viewCourse(semHead);
        cout << "\n==> Please choose the year (yyyy): ";
        cin >> year;
        cout << "\n";
        deleteCourse(semHead, year);
        break;
    case 4:
        viewCourse(semHead);
        cout << "\n==> Please choose the year (yyyy): ";
        cin >> year;
        cout << "\n";
        //? Showing the list of students
        addRemoveStudent(semHead, year);
        break;
    case 5:
        cout << "\n";
        cout << "Modification completed, remember to save the changes!\n";
        return;
    }

    cout << "Modification completed!\n";
    viewCourse(semHead);
    Sleep(1000);
    cout << "Do you want to continue modifying? (Y/N): ";
    char c;
    cin >> c;
    while (c != 'y' && c != 'Y' && c != 'n' && c != 'N')
    {
        cout << "Invalid input! Please enter again: ";
        cin >> c;
    }
    if (c == 'y' || c == 'Y')
    {
        initModify(semHead);
        return;
    }

    else
    {
        cout << "\n";
        cout << "Modification completed, remember to save the changes!\n";
        return;
    }
}