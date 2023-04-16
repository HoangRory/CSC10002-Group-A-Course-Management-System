#include "../Header/Semester.h"
#include "../Header/Year.h"
#include "../Header/Utility.h"

void initModify(Year *yearHead)
{
    system("cls");

    Render_Menu();
    vector<string> menu;
    menu.push_back("Modify semester");
    menu.push_back("Modify course");
    menu.push_back("Remove a course");
    menu.push_back("Add/Remove student");
    menu.push_back("Return");

    int opt = Draw(menu);

    RunModify(yearHead, opt); // Begin to do the chosen option
    return;
}

void RunModify(Year *yearHead, int opt)
{
    string id, strYear;
    int sem, year;
    vector<string> small_menu;
    switch (opt)
    {
    case 0: // Modify the semester follow year and no_sem
        year = Get_CheckFormat_Existed_Year(yearHead);
        small_menu.push_back("1st semester");
        small_menu.push_back("2nd semester");
        small_menu.push_back("3rd semester");

        sem = Draw(small_menu) + 1;

        modifySemester(yearHead, year, sem);
        break;
    case 1: // View all the course and modify a course in the school year
        ViewAllCourse(yearHead);
        year = Get_CheckFormat_Existed_Year(yearHead);
        modifyCourse(yearHead, year);
        break;
    case 2: // Remove out the course
        // viewCourse(semHead);
        year = Get_CheckFormat_Existed_Year(yearHead);
        removeCourse(yearHead, year);
        break;
    case 3: // add or remove a student from a course
        ViewCourse(yearHead);
        year = Get_CheckFormat_Existed_Year(yearHead);
        //! Showing the list of students
        addRemoveStudent(yearHead, year);
        break;
    case 4:
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