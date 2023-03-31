#include "proto.h"

Course *courseHead;

void ViewStudentsClass(Year *yearHead)
{   
    string class_name;
    cout << "Input the class's name: "; // eg 20APCS1
    cin >> class_name;
    while (yearHead)
    {
        if (to_string(yearHead->yearStart % 100) == class_name.substr(0, 2))
            break;
        yearHead = yearHead->next;
    }
    if (!yearHead)
    {
        cout << "Not found!" << endl;
        return;
    }
    while (yearHead->Class)
    {
        if (yearHead->Class->Name == class_name)
        {
            while (yearHead->Class->StudentClass)
            {
                cout << yearHead->Class->StudentClass->ID << "\t" << yearHead->Class->StudentClass->accStudent->firstName << " " << classHead->StudentClass->accStudent->lastName << endl;
                yearHead->Class->StudentClass = yearHead->Class->StudentClass->next;
            }
            break;
        }
        yearHead->Class = yearHead->Class->next;
    }
    if (!yearHead->Class)
        cout << "Not found!" << endl;
}

//này chưa hoàn chỉnh
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