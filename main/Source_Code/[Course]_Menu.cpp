#include "../Header/Course.h"

void Menu_Staff_View(Year *yearHead)
{
    system("cls");
    Render_View(50, 3);

    vector<string> menu;
    menu.push_back("ScoreBoard");
    menu.push_back("List Student");
    menu.push_back("List Class");
    menu.push_back("List Course");
    menu.push_back("Back to Main Menu");

    int opt = Draw_XY(menu, 60, 12, 5, 25);
    switch (opt)
    {
    case 0:
        Menu_ScoreBoard_View(yearHead);
        break;
    case 1:
        Menu_ListStudent_View(yearHead);
        break;
    case 2:
        ViewClass(yearHead);
        break;
    case 3:
        Menu_ListCourse_View(yearHead);
        break;
    case 4:
        return;
    }
    Menu_Staff_View(yearHead);
}
void Menu_ScoreBoard_View(Year *yearHead)
{
    system("cls");
    Render_ScoreBoard(20, 3);

    vector<string> menu;
    menu.push_back("ScoreBoard Of Class");
    menu.push_back("ScoreBoard Of Course");
    menu.push_back("Back to View Menu");

    int opt = Draw_XY(menu, 60, 12, 4, 24);
    system("cls");
    switch (opt)
    {
    case 0:
        Interface_ViewScoreBoardClass(yearHead);
        break;
    case 1:
        Interface_ViewScoreBoardCourse(yearHead);
        break;
    case 2:
        return;
    }
    Menu_ScoreBoard_View(yearHead);
}
void Menu_ListStudent_View(Year *yearHead)
{
    system("cls");
    Render_Student(30, 3);

    vector<string> menu;
    menu.push_back("All Student Of Class");
    menu.push_back("All Student Of Course");
    menu.push_back("Back to View Menu");

    int opt = Draw_XY(menu, 60, 12, 4, 25);
    system("cls");
    switch (opt)
    {
    case 0:
        Interface_ViewStudentClass(yearHead);
        break;
    case 1:
        Interface_ViewStudentCourse(yearHead);
        break;
        ;
    case 2:
        return;
    }
    Menu_ListStudent_View(yearHead);
}
void Menu_ListCourse_View(Year *yearHead)
{
    system("cls");
    Render_Course(40, 3);

    vector<string> menu;
    menu.push_back("All Course");
    menu.push_back("Student's Course");
    menu.push_back("Back to View Menu");

    int opt = Draw_XY(menu, 60, 12, 4, 20);
    system("cls");
    switch (opt)
    {
    case 0:
        //?
        ViewCourse(yearHead);
        break;
    case 1:
        //?
        Interface_ViewCourseOfAStudent(yearHead);
        break;
    case 2:
        return;
    }
    Menu_ListCourse_View(yearHead);
}
void Menu_Import_Export(Year *yearHead)
{
    system("cls");
    Render_Import(40, 2);
    Render_Export(40, 8);
    vector<string> menu;
    menu.push_back("Import The ScoreBoard Of A Course");
    menu.push_back("Export The List Of Students In A Course");
    menu.push_back("Back to View Menu");

    int opt = Draw_XY(menu, 55, 15, 4, 42);
    system("cls");
    switch (opt)
    {
    case 0:
        importScoreBoardCourse(yearHead);
        break;
    case 1:
        exportListStudentCourse(yearHead);
        break;
    case 2:
        return;
    }
    Menu_Import_Export(yearHead);
}