#include "../Header/Utility.h"
#include "../Header/course.h"

void Interface_Import_Export(Year *yearHead)
{
    system("cls");
    Render_Import(40, 2);
    Render_Export(40, 8);
    vector<string> menu;
    menu.push_back("Import The ScoreBoard Of A Course");
    menu.push_back("Export The List Of Student In A Course");
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
    Interface_Import_Export(yearHead);
}