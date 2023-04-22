#include "../Header/course.h"
#include "../Header/Utility.h"

//! xóa hết cái trên
Year *chooseYearbyOption_XY(Year *yearHead, int x, int y, int nOption_eachTime)
{
    Year *year_cur = yearHead;
    vector<string> menu(10);
    while (year_cur)
    {
        menu.push_back(to_string(year_cur->yearStart) + " - " + to_string(year_cur->yearStart + 1));
        year_cur = year_cur->next;
    }
    int width = 20;
    menu.push_back("BACK");
    int option = Draw_XY(menu, x, y, nOption_eachTime, width);

    while (yearHead && option--)
        yearHead = yearHead->next;
    return yearHead;
}
Class *chooseClassbyOption_XY(Class *classHead, int x, int y, int nOption_eachTime)
{
    vector<string> menu(10);
    Class *class_cur = classHead;
    while (class_cur)
    {
        menu.push_back(class_cur->Name);
        class_cur = class_cur->next;
    }
    int width = 20;
    menu.push_back("BACK");
    int option = Draw_XY(menu, x, y, nOption_eachTime, width);

    while (classHead && option--)
        classHead = classHead->next;
    return classHead;
}
Semester *chooseSemesterbyOption_XY(Semester *semHead, int x, int y, int nOption_eachTime)
{
    vector<string> menu(10);
    Semester *sem_cur = semHead;
    while (sem_cur)
    {
        menu.push_back("Semester " + to_string(sem_cur->No));
        sem_cur = sem_cur->next;
    }
    int width = 15;
    menu.push_back("BACK");
    int option = Draw_XY(menu, x, y, nOption_eachTime, width);

    while (semHead && option--)
    {
        semHead = semHead->next;
    }
    return semHead;
}

Course *chooseCoursebyOption_XY(Course *courseHead, int x, int y, int nOption_eachTime)
{
    vector<string> menu(10);
    Course *course_cur = courseHead;
    while (course_cur)
    {
        menu.push_back(course_cur->Name);
        course_cur = course_cur->next;
    }
    int width = 35;
    menu.push_back("BACK");
    int option = Draw_XY(menu, x, y, nOption_eachTime, width);

    while (courseHead && option--)
        courseHead = courseHead->next;
    return courseHead;
}