#include "../Header/Student.h"

// View Course
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
// Menu Student
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