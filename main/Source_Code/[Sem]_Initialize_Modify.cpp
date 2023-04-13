#include "../Header/Semester.h"
#include "../Header/Year.h"
#include "../Header/Utility.h"

void initModify(Year *yearHead)
{
    system("cls");

    PrintMenu();
    vector<string> menu;
    menu.push_back("Modify semester");
    menu.push_back("Modify course");
    menu.push_back("Remove a course");
    menu.push_back("Add/Remove student");
    menu.push_back("Return");

    int opt = Draw(menu);

    RunModify(yearHead, opt - 1); // Begin to do the chosen option
    return;
}

void RunModify(Year *yearHead, int opt)
{
    string id, strYear;
    int sem, year;
    switch (opt)
    {
    case 1: // Modify the semester follow year and no_sem
        year = Get_CheckFormat_Existed_Year(yearHead);
        cout << "==> Please choose the semester (1, 2, 3): ";
        cin >> sem;

        cout << "\n";
        modifySemester(yearHead, year, sem);
        break;
    case 2: // View all the course and modify a course in the school year
        ViewAllCourse(yearHead);
        year = Get_CheckFormat_Existed_Year(yearHead);
        cout << "\n";
        modifyCourse(yearHead, year);
        break;
    case 3: // Remove out the course
        // viewCourse(semHead);
        year = Get_CheckFormat_Existed_Year(yearHead);
        cout << "\n";
        removeCourse(yearHead, year);
        break;
    case 4: // add or remove a student from a course
        ViewCourse(yearHead);
        year = Get_CheckFormat_Existed_Year(yearHead);
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