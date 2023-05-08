#include "../Header/Course.h"

// View ScoreBoard
void Interface_ViewScoreBoardCourse(Year *yearHead) // này của task 21
{
    system("cls");

    Year *ChooseYear = nullptr;
    Semester *ChooseSem = nullptr;
    Course *ChooseCourse = nullptr;
    Render_ScoreBoardCourse();
    int x = 60, y = 17;
    if (yearHead == nullptr)
    {
        Message_Warning("There are no school year.", "Error not exist");
        // gọi lại hàm mainmenu
        return;
    }
    do
    {
        ChooseYear = chooseYearbyOption_XY(yearHead, x, y, 5);
        if (ChooseYear == nullptr)
            // quay lại main menu
            return;
        if (ChooseYear->NoSemester == nullptr)
        {
            Message_Warning("There are no semester in this school year.", "Error not exist");
            Interface_ViewCourseOfAStudent(yearHead);
            return;
        }
        ChooseSem = chooseSemesterbyOption_XY(ChooseYear->NoSemester, x, y, 5);
        if (ChooseSem == nullptr)
        {
            Interface_ViewStudentCourse(yearHead);
            return;
        }
        do
        {
            if (ChooseSem->course == nullptr)
            {
                Message_Warning("There are no course in this semester", "Error not Exist");
                break;
            }

            ChooseCourse = chooseCoursebyOption_XY(ChooseSem->course, x, y, 5);
            if (ChooseCourse == nullptr)
                break;
            if (ChooseCourse->studentCourse == nullptr)
                Message_Warning(" There is no student in course " + ChooseCourse->Name, "Error not exist");
            else
            {
                ViewScoreBoardCourse(ChooseCourse, 15, 15); // 15 15 là tọa độ x y của vị trí bắt đầu bảng
                system("cls");
                Render_ScoreBoardCourse();
            }
        } while (ChooseCourse != nullptr);
    } while (ChooseSem != nullptr);
}
// View Student
void Interface_ViewStudentCourse(Year *yearHead) // task 18: view students in a course
{
    system("cls");
    // in ra chư studentcourse
    Year *ChooseYear = nullptr;
    Semester *ChooseSem = nullptr;
    Course *ChooseCourse = nullptr;
    Render_StudentCourse();
    int x = 60, y = 17;
    if (yearHead == nullptr)
    {
        Message_Warning("There are no school year.", "Error not exist");
        // gọi lại hàm mainmenu
        return;
    }

    goToXY(30, y - 2);
    cout << "Select the year that contains the course, in which you want to show list student";
    ChooseYear = chooseYearbyOption_XY(yearHead, x, y, 5);
    goToXY(30, y - 2);
    cout << setw(100) << " ";
    if (ChooseYear == nullptr) // quay lại main menu
        return;
    if (ChooseYear->NoSemester == nullptr)
    {
        Message_Warning("There are no semester in this school year.", "Error not exist");
        Interface_ViewStudentCourse(yearHead);
        return;
    }
    do
    {
        goToXY(30, y - 2);
        cout << "Select the semester that contains the course, in which you want to show list student";
        ChooseSem = chooseSemesterbyOption_XY(ChooseYear->NoSemester, x, y, 5);
        goToXY(30, y - 2);
        cout << setw(100) << " ";
        if (ChooseSem == nullptr)
        {
            Interface_ViewStudentCourse(yearHead);
            return;
        }
        do
        {
            if (ChooseSem->course == nullptr)
            {
                Message_Warning("There are no course in this semester", "Error not Exist");
                break;
            }
            goToXY(30, y - 2);
            cout << "Select the course for which you want to show list student";
            ChooseCourse = chooseCoursebyOption_XY(ChooseSem->course, x, y, 5);
            goToXY(30, y - 2);
            cout << setw(100) << " ";
            if (ChooseCourse != nullptr)
            {
                if (ChooseCourse->studentCourse == nullptr)
                    Message_Warning(" There is no student in course " + ChooseCourse->Name, "Error not exist");
                else
                {
                    goToXY(40, y - 2);
                    cout << " The list of student of " << ChooseCourse->Name << " course:";
                    ViewStudentCourse(ChooseCourse, 40, y);
                }
                system("cls");
                Render_StudentCourse();
            }
        } while (ChooseCourse != nullptr);
    } while (ChooseSem != nullptr);
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