#include "../Header/Course.h"

bool checkFile(string name)
{
    fstream f;
    f.open(name);
    if (f.is_open())
        return true;
    return false;
}

// task 23
bool isDouble(string str)
{
    istringstream ss(str);
    double d;
    return (ss >> d) && (ss.eof());
}
CourseStudent *checkExistence_OfCourse(CourseStudent *courseCheck, CourseStudent *courseHead)
{
    while (courseHead)
    {
        if (courseCheck->course == courseHead->course)
            return courseCheck;
        courseHead = courseHead->next;
    }
    return nullptr;
}