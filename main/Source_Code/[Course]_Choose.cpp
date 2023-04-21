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
    int option = Draw_XY(menu, 60, 12);
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
    int option = Draw(menu);

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
    int option = Draw_XY(menu, 60, 12);
    
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
    int option = Draw_XY(menu, 60, 12);
    while(courseHead && option--) {
        courseHead = courseHead->next;
    }
    return courseHead;
}


//? xóa hết cái trên
Year* chooseYearbyOption_XY(Year* yearHead, int x, int y, int nOption_eachTime) 
{
    Year *year_cur = yearHead;
    vector<string> menu;
    while (year_cur)
    {
        menu.push_back(" " + to_string(year_cur->yearStart) + " - " + to_string(year_cur->yearStart + 1));
        year_cur = year_cur->next;
    }
    int width = 20;
    menu.push_back(" BACK");
    int option = Draw_XY(menu, x, y,nOption_eachTime,width);
    while(yearHead && option--) {
        yearHead = yearHead->next;
    }
    return yearHead;
}
Class* chooseClassbyOption_XY(Class *classHead, int x, int y, int nOption_eachTime) 
{
    vector<string> menu;
    Class *class_cur = classHead;
    while(class_cur) {
        menu.push_back(" " + class_cur->Name);
        class_cur = class_cur->next;
    }
    int width = 20;
    menu.push_back(" BACK");
    int option = Draw_XY(menu,x,y,nOption_eachTime,width);

    while(classHead && option--)
        classHead = classHead->next;
    return classHead;
}
Semester* chooseSemesterbyOption_XY(Semester* semHead, int x, int y, int nOption_eachTime) 
{
    vector<string> menu;
    Semester *sem_cur = semHead;
    while(sem_cur) {
        menu.push_back("   Semester " + to_string(sem_cur->No));
        sem_cur = sem_cur->next;
    }
    int width = 25;
    menu.push_back("   BACK");
    int option = Draw_XY(menu, x, y,nOption_eachTime, width);
    
    while (semHead && option--) {
        semHead = semHead->next;
    }
    return semHead;
}


Course* chooseCoursebyOption_XY(Course* courseHead, int x, int y, int nOption_eachTime) 
{
    vector<string> menu;
    Course *course_cur = courseHead;
    while(course_cur) {
        menu.push_back(" " + course_cur->Name);
        course_cur = course_cur->next;
    }
    int width = 35;
    menu.push_back(" BACK ");
    int option = Draw_XY(menu, x, y, nOption_eachTime, width);
    while(courseHead && option--) {
        courseHead = courseHead->next;
    }
    return courseHead;
}