#include "proto.h"

Class *classHead;
Course *courseHead;
//string class_name = "", course_name = "";

void ViewStudentsClass(string class_name)
{   
    while (classHead)
    {
        if (classHead->Name == class_name)
        {
            while (classHead->StudentClass)
            {
                cout << classHead->StudentClass->accStudent->username << "\t" << classHead->StudentClass->accStudent->firstName << " " << classHead->StudentClass->accStudent->lastName << endl;
                classHead->StudentClass = classHead->StudentClass->next;
            }
            break;
        }
        classHead = classHead->next;
    }
    if (!classHead)
        cout << "Not found!" << endl;
}

void ViewStudentCourse(string course_name)
{
    while (courseHead)
    {
        if (courseHead->Name == course_name)
        {
            while (courseHead->StudentCourse)
            {
                cout << courseHead->StudentCourse->ID << "\t" << courseHead->StudentCourse->FullName << endl;
                courseHead->StudentCourse = courseHead->StudentCourse->next;
            }
            break;
        }
        courseHead = courseHead->next;
    }
    if (!courseHead)
        cout << "Not found!" << endl;
}