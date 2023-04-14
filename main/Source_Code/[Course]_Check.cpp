#include "../Header/course.h"

bool checkFile(string name) {
    fstream f;
    f.open(name);
    if(f.is_open()) return true;
    return false;
}

//task 23
CourseStudent* checkExistence_OfCourse(CourseStudent *courseCheck, CourseStudent *courseHead) 
{
    while(courseHead) 
    {
        if (courseCheck->course == courseHead->course) 
            return courseCheck;
        courseHead->next;
    }
    return nullptr;
}