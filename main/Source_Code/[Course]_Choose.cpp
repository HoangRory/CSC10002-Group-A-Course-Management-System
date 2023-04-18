#include "../Header/course.h"
#include "../Header/Utility.h"

Year* chooseYearbyOption(Year* yearHead) 
{
    Year *year_cur = yearHead;
    vector<string> menu;
    while (year_cur)
    {
        menu.push_back(" " + to_string(year_cur->yearStart) + " - " + to_string(year_cur->yearStart + 1));
        year_cur = year_cur->next;
    }
    menu.push_back(" BACK");
    int option = Draw(menu);
    while(yearHead && option--) {
        yearHead = yearHead->next;
    }
    return yearHead;
}

Class* chooseClassbyOption(Class *classHead) 
{
    vector<string> menu;
    Class *class_cur = classHead;
    while(class_cur) {
        menu.push_back(" " + class_cur->Name);
        class_cur = class_cur->next;
    }
    menu.push_back(" BACK");
    int option = Draw_XY(menu,10, 10);

    while(classHead && option--)
        classHead = classHead->next;
    return classHead;
}
Semester* chooseSemesterbyOption(Semester* semHead) 
{
    vector<string> menu;
    Semester *sem_cur = semHead;
    while(sem_cur) {
        menu.push_back(" Semester " + to_string(sem_cur->No));
        sem_cur = sem_cur->next;
    }
    menu.push_back(" BACK");
    int option = Draw(menu);
    
    while (semHead && option--) {
        semHead = semHead->next;
    }
    return semHead;
}
Course* chooseCoursebyOption(Course* courseHead) 
{
    vector<string> menu;
    Course *course_cur = courseHead;
    while(course_cur) {
        menu.push_back("  " + course_cur->Name);
        course_cur = course_cur->next;
    }
    menu.push_back(" BACK ");
    int option = Draw(menu);
    while(courseHead && option--) {
        courseHead = courseHead->next;
    }
    return courseHead;
}

Year* chooseYearbyOption_XY(Year* yearHead, int x, int y) 
{
    Year *year_cur = yearHead;
    vector<string> menu;
    while (year_cur)
    {
        menu.push_back(" " + to_string(year_cur->yearStart) + " - " + to_string(year_cur->yearStart + 1));
        year_cur = year_cur->next;
    }
    menu.push_back(" BACK");
    int option = Draw_XY(menu, x, y);
    while(yearHead && option--) {
        yearHead = yearHead->next;
    }
    return yearHead;
}
Class* chooseClassbyOption_XY(Class *classHead, int x, int y) 
{
    vector<string> menu;
    Class *class_cur = classHead;
    while(class_cur) {
        menu.push_back(" " + class_cur->Name);
        class_cur = class_cur->next;
    }
    menu.push_back(" BACK");
    int option = Draw_XY(menu,x,y);

    while(classHead && option--)
        classHead = classHead->next;
    return classHead;
}
Semester* chooseSemesterbyOption_XY(Semester* semHead, int x, int y) 
{
    vector<string> menu;
    Semester *sem_cur = semHead;
    while(sem_cur) {
        menu.push_back(" Semester " + to_string(sem_cur->No));
        sem_cur = sem_cur->next;
    }
    menu.push_back(" BACK");
    int option = Draw_XY(menu, x, y);
    
    while (semHead && option--) {
        semHead = semHead->next;
    }
    return semHead;
}


Course* chooseCoursebyOption_XY(Course* courseHead, int x, int y) 
{
    vector<string> menu;
    Course *course_cur = courseHead;
    while(course_cur) {
        menu.push_back("  " + course_cur->Name);
        course_cur = course_cur->next;
    }
    menu.push_back(" BACK ");
    int option = Draw_XY(menu, x, y);
    while(courseHead && option--) {
        courseHead = courseHead->next;
    }
    return courseHead;
}