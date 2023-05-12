#include "../Header/Course.h"

// task 22
Student *findStudentbyID(string IDStudent, Year *Yhead)
{
    Class *curClass;
    Student *curStudent;
    while (Yhead)
    {
        curClass = Yhead->Class;
        while (curClass)
        {
            curStudent = curClass->StudentClass;
            while (curStudent)
            {
                if (curStudent->ID == IDStudent)
                    return curStudent;
                curStudent = curStudent->next;
            }
            curClass = curClass->next;
        }
        Yhead = Yhead->next;
    }
    return nullptr;
}
StudentCourse *find_StudentOfCourse(string ID, StudentCourse *stuCourseHead)
{
    while (stuCourseHead)
    {
        if (stuCourseHead->ID == ID)
            return stuCourseHead;
        stuCourseHead = stuCourseHead->next;
    }
    return nullptr;
}