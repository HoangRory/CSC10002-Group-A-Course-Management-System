#include "../Header/Semester.h"
#include "../Header/Year.h"
#include "../Header/Utility.h"
#include "../Header/course.h"
#include "../Header/Help.h"

void initModify(Year *yearHead)
{
    system("cls");

    Render_Menu(59, 3);
    vector<string> menu;
    menu.push_back("Modify semester");
    menu.push_back("Modify course");
    menu.push_back("Remove a course");
    menu.push_back("Add/Remove student");
    menu.push_back("Update Student's ScoreBoard");
    menu.push_back("Back");

    int opt = Draw_XY(menu, 60, 12, 6, 30, 63);

    RunModify(yearHead, opt); // Begin to do the chosen option
    return;
}

void RunModify(Year *yearHead, int opt)
{
    system("cls");
    Render_Menu(59, 3);
    switch (opt)
    {
    case 0: // Modify the semester follow year and no_sem
        modifySemester(yearHead);
        break;
    case 1: // View all the course and modify a course in the school year
        // ViewCourse(yearHead);
        modifyCourse(yearHead);
        break;
    case 2: // Remove out the course
        removeCourse(yearHead);
        break;
    case 3: // add or remove a student from a course
        // ViewCourse(yearHead);
        addRemoveStudent(yearHead);
        break;
    case 4:
        UpdateStudentResult(yearHead);
        break;
    case 5:
        string mess = "Modification completed!\nRemember to SAVE changes.";
        Message_Warning(mess, "Notice");
        return;
    }

    string mess = "Do you want to continue modifying?";
    if (Message_YesNo(mess, "Confirm"))
    {
        initModify(yearHead);
        return;
    }
    else
    {
        string mess = "Modification completed!\nRemember to SAVE changes.";
        Message_Warning(mess, "Notice");
        return;
    }
}