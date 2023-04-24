#include "../Header/course.h"
#include "../Header/Semester.h"
#include "../Header/Login.h"
#include "../Header/Utility.h"
void Staff_View(Year *yearHead)
{
    system("cls");
    Render_View(50, 3);

    vector<string> menu;
    menu.push_back("ScoreBoard");
    menu.push_back("List Student");
    menu.push_back("List Class");
    menu.push_back("List Course");
    menu.push_back("Back to Main Menu");

    system("cls");
    int opt = Draw_XY(menu, 60, 12, 5, 25);
    switch (opt)
    {
    case 0:
        //?
        ScoreBoard_View(yearHead);
        break;
    case 1:
        //?
        ListStudent_View(yearHead);
        // Recursion back to the StaffMain function
        break;
    case 2:
        //?
        ViewClass(yearHead);
        // Recursion back to the StaffMain function
        break;
    case 3:
        ListCourse_View(yearHead);
        break;
    case 4:
        return;
    }
    Staff_View(yearHead);
}
void ScoreBoard_View(Year *yearHead)
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
        //?
        Interface_ViewScoreBoardClass(yearHead);
        break;
        ;
    case 1:
        //?
        Interface_ViewScoreBoardCourse(yearHead);
        // Recursion back to the Staff_View function
        break;
    case 2:
        return;
    }
    ScoreBoard_View(yearHead);
}
void ListStudent_View(Year *yearHead)
{
    system("cls");
    Render_Student(30, 3);

    vector<string> menu;
    menu.push_back("All Student Of Class");
    menu.push_back("All Student Of Course");
    menu.push_back("Back to View Menu");

    int opt = Draw_XY(menu, 50, 12, 4, 30);
    system("cls");
    switch (opt)
    {
    case 0:
        //? Add a new year
        Interface_ViewStudentClass(yearHead);
        break;
    case 1:
        //? Add a new semester
        Interface_ViewStudentCourse(yearHead);
        // Recursion back to the StaffMain function
        break;
        ;
    case 2:
        return;
    }
    ListStudent_View(yearHead);
}
void ListCourse_View(Year *yearHead)
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
        // Recursion back to the StaffMain function
        break;
    case 2:
        return;
    }
    ListCourse_View(yearHead);
}

void Student_Main(Year *yearHead, Account *accHead, string &user, string &pass, int &role)
{
    system("cls");
    Render_View(50, 3);

    vector<string> menu;
    menu.push_back("Account");
    menu.push_back("Your Course");
    menu.push_back("Your ScoreBoard");
    menu.push_back("Quit");

    int opt = Draw_XY(menu, 50, 12, 4, 24);
    switch (opt)
    {
    case 0:
        //?
        if (AccountAlteration(accHead, user, pass, role))
            break;
        break;
    case 1:
        //? Add a new semester
        system("cls");
        ViewCoursesOfAStudent(accHead, yearHead);
        // Recursion back to the StaffMain function
        break;
    case 2:
        //? Add a new course
        ListCourse_View(yearHead);
        // Recursion back to the StaffMain function
        break;
    case 3:
        return;
    }
    Student_Main(yearHead, accHead, user, pass, role);
}

void Interface_ViewCourseOfAStudent(Year *yearHead)
{
    system("cls");
    Render_Course(40, 1);
    Render_Student(35, 7);
    int x = 60, y = 16;

    Year *ChooseYear = nullptr;
    Class *ChooseClass = nullptr;
    Student *ChooseStudent = nullptr;
    ChooseYear = chooseYearbyOption_XY(yearHead, x, y, 5);
    if (ChooseYear == nullptr)
        return;
    do
    {
        if (ChooseYear->Class == nullptr)
        {
            Message_Warning("There is no student in year " + to_string(ChooseYear->yearStart) + " " + to_string(ChooseYear->yearStart + 1), "Error");
            Interface_ViewCourseOfAStudent(yearHead);
            return;
        }
        ChooseClass = chooseClassbyOption_XY(ChooseYear->Class, x, y, 5);
        if (ChooseClass == nullptr)
        {
            Interface_ViewCourseOfAStudent(yearHead);
            return;
        }
        Student *student_cur = ChooseClass->StudentClass;
        if (!student_cur)
        {
            Message_Warning("There is no student in " + ChooseClass->Name, "Error");
        }
        else
            do
            {
                ChooseStudent = chooseStudentOfClass(ChooseClass, 45, y);
                if (ChooseStudent != nullptr)
                    ViewCoursesOfAStudent(ChooseStudent->accStudent, yearHead);
                system("cls");
                Render_Course(40, 1);
                Render_Student(35, 7);
            } while (ChooseStudent != nullptr);
        system("cls");
        Render_Course(40, 1);
        Render_Student(35, 7);
    } while (ChooseClass != nullptr);
}