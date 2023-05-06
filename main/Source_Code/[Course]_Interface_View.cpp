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

    int opt = Draw_XY(menu, 60, 12, 4, 25);
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

void Interface_ViewCoursesOfUser(Student *student_cur, Year *yearHead)
{
    if (student_cur->course == nullptr)
    {
        Message_Warning("This student is not taking any courses.", "Error not exist");
        return;
    }
    if (yearHead == nullptr)
    {
        Message_Warning("There are no school year.", "Error not exist");
        // gọi lại hàm mainmenu
        return;
    }
    int x = 60, y = 15;
    Year *ChooseYear = nullptr;
    Semester *ChooseSem = nullptr;
    if (yearHead == nullptr)
    {
        Message_Warning("There are no school year.", "Error not exist");
        // gọi lại hàm mainmenu
        return;
    }
    goToXY(40, 13);
    cout << "Select the year that contains the semester you want to show all course";
    ChooseYear = chooseYearbyOption_XY(yearHead, x, y, 5);
    cout << setw(70) << " ";
    if (ChooseYear == nullptr)
        // quay lại main menu
        return;
    if (ChooseYear->NoSemester == nullptr)
    {
        Message_Warning("There are no semester in this school year.", "Error not exist");
        Interface_ViewCoursesOfUser(student_cur, yearHead);
        return;
    }
    goToXY(40, 13);
    cout << "Select the semester that contains the course you want to show all course";
    ChooseSem = chooseSemesterbyOption_XY(ChooseYear->NoSemester, x, y, 5);
    cout << setw(70) << " ";
    while (ChooseSem)
    {
        ViewCoursesOfUser(student_cur, ChooseSem->course);
        system("cls");
        Render_Course(40, 1);
        Render_Student(35, 7);
        goToXY(40, 13);
        cout << "Select the semester that contains the course you want to show all course";
        ChooseSem = chooseSemesterbyOption_XY(ChooseYear->NoSemester, x, y, 5);
    }
    Interface_ViewCoursesOfUser(student_cur, yearHead);
}
void Interface_ViewScoreBoardOfUser(Student *student_cur, Year *yearHead) //? task 14
{
    Year *ChooseYear = nullptr;
    Semester *ChooseSem = nullptr;
    system("cls");
    int x = 20, y = 2;
    Render_ScoreBoard(x, y);
    x = 60, y = 15;
    if (yearHead == nullptr)
    {
        Message_Warning("There are no school year.", "Error not exist");
        // gọi lại hàm mainmenu
        return;
    }
    goToXY(40, 13);
    cout << "Select the year that contains the semester you want to show scoreboard";
    ChooseYear = chooseYearbyOption_XY(yearHead, x, y, 5);
    cout << setw(70) << " ";
    if (ChooseYear == nullptr)
        // quay lại main menu
        return;
    if (ChooseYear->NoSemester == nullptr)
    {
        Message_Warning("There are no semester in this school year.", "Error not exist");
        Interface_ViewScoreBoardOfUser(student_cur, yearHead);
        return;
    }
    goToXY(40, 13);
    cout << "Select the semester that contains the course you want to show scoreboard";
    ChooseSem = chooseSemesterbyOption_XY(ChooseYear->NoSemester, x, y, 5);
    cout << setw(70) << " ";
    while (ChooseSem)
    {
        if (ChooseSem->course == nullptr)
            Message_Warning("There are no course in this semester", "Error not Exist");
        else
            ViewScoreboard(student_cur->accStudent, ChooseSem->course);
        system("cls");
        Render_ScoreBoard(20, 2);
        goToXY(40, 13);
        cout << "Select the semester that contains the course you want to show scoreboard";
        ChooseSem = chooseSemesterbyOption_XY(ChooseYear->NoSemester, x, y, 5);
        cout << setw(70) << " ";
    }
    Interface_ViewScoreBoardOfUser(student_cur, yearHead);
}
void Interface_ViewCourseOfAStudent(Year *yearHead)
{
    system("cls");
    Render_Course(40, 1);
    Render_Student(35, 7);
    int x = 60, y = 16;
    Year *year_cur = yearHead;
    Class *ChooseClass = nullptr;
    Student *ChooseStudent = nullptr;
    while (year_cur)
    {
        if (year_cur->Class)
            break;
        year_cur = year_cur->next;
    }
    if (!year_cur)
    {
        Message_Warning("There is no class in all school year ", "Error");
        return;
    }

    goToXY(45, y - 2);
    cout << "Select the student's class for which you want to show the course list.";
    ChooseClass = chooseClass_inAllYear_byOption_XY(yearHead, x, y, 5);
    goToXY(45, y - 2);
    cout << setw(100) << " ";
    if (ChooseClass == nullptr)
        return;
    if (!ChooseClass->StudentClass)
        Message_Warning("There is no student in " + ChooseClass->Name, "Error");
    else
        do
        {
            goToXY(45, y - 2);
            cout << "Select the student for whom you want to show the course list.";
            ChooseStudent = chooseStudentOfClass(ChooseClass, 45, y);
            goToXY(45, y - 2);
            cout << setw(100) << " ";
            if (ChooseStudent != nullptr)
                ViewCoursesOfAStudent(ChooseStudent->accStudent, yearHead);
            system("cls");
            Render_Course(40, 1);
            Render_Student(35, 7);
        } while (ChooseStudent != nullptr);
    Interface_ViewCourseOfAStudent(yearHead);
}