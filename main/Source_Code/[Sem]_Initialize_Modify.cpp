#include "../Header/Semester.h"

void initModify(Year *yearHead)
{
    bool stop = false;
    system("cls");
    int opt = 1;
    string *ListOption = new string[6];
    ListOption[0] = "\nOptions to modify:\n";
    ListOption[1] = "- Modify semester                      \n";
    ListOption[2] = "- Modify course                        \n";
    ListOption[3] = "- Delete a course                      \n";
    ListOption[4] = "- Add or remove a student from a course\n";
    ListOption[5] = "- Return                               \n";

    for (int i = 0; i < 6; i++)
    {
        if (i == opt)
        {
            TextColor(LIGHT_YELLOW);
            cout << ListOption[i];
            TextColor(WHITE);
        }
        else
            cout << ListOption[i];
    }
    SetConsoleTextAttribute(h, GREEN);
    TextColor(LIGHT_GREEN);
    cout << "\n\n(Using your arrow on the keyboard to move the choice and enter to select!)\n\n";
    TextColor(WHITE);

    ShowConsoleCursor(false);
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

            for (int i = 0; i < 6; i++)
            {
                if (i == opt)
                {
                    extColor(LIGHT_YELLOW);
                    cout << ListOption[i];
                    TextColor(WHITE);
                }
                else
                    cout << ListOption[i];
            }

            TextColor(LIGHT_GREEN);
            cout << "\n\n(Using your arrow on the keyboard to move the choice and enter to select!)\n\n";
            TextColor(WHITE);
        }
    }
    delete[] ListOption;
    ShowConsoleCursor(true);

    RunModify(yearHead, opt);
    return;
}

void RunModify(Year *yearHead, int opt)
{
    string id;
    int sem, year;
    switch (opt)
    {
    case 1:
        // viewCourse(semHead);
        //! Showing the list of semester
        cout << "\n==> Please choose the year (yyyy): ";
        cin >> year;
        cout << "==> Please choose the semester (1, 2, 3): ";
        cin >> sem;
        cout << "\n";
        modifySemester(yearHead, year, sem);
        break;
    case 2:
        ViewAllCourse(yearHead);
        cout << "\n==> Please choose the year that you want to review? (yyyy): ";
        cin >> year;
        cout << "\n";
        modifyCourse(yearHead, year);
        break;
    case 3:
        // viewCourse(semHead);
        cout << "\n==> Please choose the year (yyyy): ";
        cin >> year;
        cout << "\n";
        deleteCourse(yearHead, year);
        break;
    case 4:
        viewCourse(yearHead);
        cout << "\n==> Please choose the year (yyyy): ";
        cin >> year;
        cout << "\n";
        //? Showing the list of students
        addRemoveStudent(yearHead, year);
        break;
    case 5:
        cout << "\n\n";
        TextColor(LIGHT_RED);
        cout << "Modification completed, remember to SAVE the changes!\n";
        TextColor(WHITE);
        return;
    }

    cout << "\nDo you want to continue modifying? (Y/N): ";
    char c;
    cin >> c;
    while (c != 'y' && c != 'Y' && c != 'n' && c != 'N')
    {
        cout << "Invalid input! Please enter again: ";
        cin >> c;
    }

    if (c == 'y' || c == 'Y')
    {
        initModify(yearHead);
        return;
    }

    else
    {
        cout << "\nModification completed, remember to save the changes!\n";
        return;
    }
}