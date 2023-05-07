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
        ScoreBoard_View(yearHead);
        break;
    case 1:
        ListStudent_View(yearHead);
        break;
    case 2:
        ViewClass(yearHead);
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
        Interface_ViewScoreBoardClass(yearHead);
        break;
    case 1:
        Interface_ViewScoreBoardCourse(yearHead);
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
        Interface_ViewStudentClass(yearHead);
        break;
    case 1:
        Interface_ViewStudentCourse(yearHead);
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
        break;
    case 2:
        return;
    }
    ListCourse_View(yearHead);
}
// View ScoreBoard
void Interface_ViewScoreBoardClass(Year *yearHead)
{
    int x = 60, y = 17;
    system("cls");
    Render_ScoreBoardClass();

    Class *ChooseClass = nullptr;
    Semester *ChooseSem = nullptr;
    Year *ChooseYear_Sem = nullptr;
    Year *year_cur = yearHead;
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
    cout << "Select the Class, in which you want to show scoreboard.";
    ChooseClass = chooseClass_inAllYear_byOption_XY(yearHead, x, y, 5);
    goToXY(45, y - 2);
    cout << setw(100) << " ";
    while (ChooseClass)
    {
        if (!ChooseClass->StudentClass)
            Message_Warning("There are no student in class " + ChooseClass->Name + ".", "Error not exist");
        else
        {
            goToXY(35, y - 2);
            cout << "Select the school year that contains the semester, in which you want to show list scoreboard";
            ChooseYear_Sem = chooseYearbyOption_XY(yearHead, x, y, 5);
            goToXY(35, y - 2);
            cout << setw(100) << " ";
            while (ChooseYear_Sem)
            {
                if (ChooseYear_Sem->NoSemester == nullptr)
                    Message_Warning("There is no semester in year " + to_string(ChooseYear_Sem->yearStart) + " " + to_string(ChooseYear_Sem->yearStart + 1), "Error");
                else
                {
                    goToXY(45, y - 2);
                    cout << "Select the Semester, in which you want to show scoreboard.";
                    ChooseSem = chooseSemesterbyOption_XY(ChooseYear_Sem->NoSemester, x, y, 5);
                    goToXY(45, y - 2);
                    cout << setw(100) << " ";
                    while (ChooseSem)
                    {
                        ViewScoreboardClass(ChooseClass, ChooseSem, 20, y);
                        system("cls");
                        Render_ScoreBoardClass();
                        goToXY(45, y - 2);
                        cout << "Select the Semester, in which you want to show scoreboard.";
                        ChooseSem = chooseSemesterbyOption_XY(ChooseYear_Sem->NoSemester, x, y, 5);
                        goToXY(45, y - 2);
                        cout << setw(100) << " ";
                    }
                }
                goToXY(35, y - 2);
                cout << "Select the school year that contains the semester, in which you want to show list scoreboard";
                ChooseYear_Sem = chooseYearbyOption_XY(yearHead, x, y, 5);
                goToXY(35, y - 2);
                cout << setw(100) << " ";
            }
        }
        goToXY(45, y - 2);
        cout << "Select the Class, in which you want to show scoreboard.";
        ChooseClass = chooseClass_inAllYear_byOption_XY(yearHead, x, y, 5);
        goToXY(45, y - 2);
        cout << setw(100) << " ";
    }
}
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
void Interface_ViewStudentClass(Year *yearHead) // task 16: view students in a class
{
    system("cls");
    int x = 60, y = 17;
    Render_StudentClass();
    Class *ChooseClass = nullptr;
    goToXY(42, y - 2);
    cout << "Select the Class, in which you want to show list student.";
    ChooseClass = chooseClass_inAllYear_byOption_XY(yearHead, x, y, 5);
    goToXY(42, y - 2);
    cout << setw(100) << " ";
    if (ChooseClass == nullptr)
        return;

    if (ChooseClass->StudentClass == nullptr)
        Message_Warning("There are no student in this class", "Error not Exist");
    else
    {
        goToXY(40, y - 1);
        cout << " The list of student of " << ChooseClass->Name << " class:";
        ViewStudentClass(ChooseClass, 40, y);
    }
    Interface_ViewStudentClass(yearHead);
}
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