#include "../Header/Semester.h"
#include "../Header/Utility.h"

void initModify(Year *yearHead)
{
    bool stop = false;
    system("cls");
    int opt = 1;
    string *ListOption = new string[6]; // Actions menu
    ListOption[0] = "\nOptions to modify:\n";
    ListOption[1] = "- Modify semester                      \n";
    ListOption[2] = "- Modify course                        \n";
    ListOption[3] = "- Remove a course                      \n";
    ListOption[4] = "- Add or remove a student from a course\n";
    ListOption[5] = "- Return                               \n";

    for (int i = 0; i < 6; i++)
    {
        if (i == opt) // change color to fit the cursor
        {
            TextColor(LIGHT_YELLOW);
            cout << ListOption[i];
            TextColor(WHITE);
        }
        else
            cout << ListOption[i];
    }

    TextColor(LIGHT_GREEN);
    cout << "\n\n(Using your arrow on the keyboard to move the choice and enter to select!)\n\n";
    TextColor(WHITE);

    ShowConsoleCursor(false);
    while (!stop)
    {
        if (_kbhit()) // get the input from arrow buttons
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
                    TextColor(LIGHT_YELLOW);
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
    ShowConsoleCursor(true); // show back the cursor

    RunModify(yearHead, opt); // Begin to do the chosen option
    return;
}

void RunModify(Year *yearHead, int opt)
{
    string id;
    int sem, year;
    switch (opt)
    {
    case 1: // Modify the semester follow year and no_sem
        // viewCourse(semHead);
        //! Showing the list of semester
        cout << "\n==> Please choose the year (yyyy): ";
        cin >> year;
        cout << "==> Please choose the semester (1, 2, 3): ";
        cin >> sem;
        cout << "\n";
        modifySemester(yearHead, year, sem);
        break;
    case 2: // View all the course and modify a course in the school year
        ViewAllCourse(yearHead);
        cout << "\n==> Please choose the year that you want to review? (yyyy): ";
        cin >> year;
        cout << "\n";
        modifyCourse(yearHead, year);
        break;
    case 3: // Remove out the course
        // viewCourse(semHead);
        cout << "\n==> Please choose the year (yyyy): ";
        cin >> year;
        cout << "\n";
        removeCourse(yearHead, year);
        break;
    case 4: // add or remove a student from a course
        ViewCourse(yearHead);
        cout << "\n==> Please choose the year (yyyy): ";
        cin >> year;
        cout << "\n";
        //! Showing the list of students
        addRemoveStudent(yearHead, year);
        break;
    case 5:
        cout << "\n\n";
        TextColor(LIGHT_RED); // RED for better noticing
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