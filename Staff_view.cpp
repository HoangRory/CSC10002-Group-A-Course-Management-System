#include "proto.h"

void ViewStudentsClass(Year *yearHead) 
{   
    string class_name;
    cout << "Enter the class's name: "; // eg 20APCS1
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
                cout << yearHead->Class->StudentClass->ID << "\t" << yearHead->Class->StudentClass->accStudent->firstName << " " << yearHead->Class->StudentClass->accStudent->lastName << endl;
                yearHead->Class->StudentClass = yearHead->Class->StudentClass->next;
            }
            break;
        }
        yearHead->Class = yearHead->Class->next;
    }
    if (!yearHead->Class)
        cout << "Not found!" << endl;
}

void ViewStudentCourse(Year *yearHead)
{
    string course_name;
    cout << "Enter the class name: ";
    getline(cin, course_name);
    while (yearHead)
    {
        while (yearHead->NoSemester)
        {
            while (yearHead->NoSemester->course)
            {
                if (yearHead->NoSemester->course->Name == course_name)
                {
                    while (yearHead->NoSemester->course->StudentCourse)
                    {
                        cout << courseHead->StudentCourse->ID << "\t" << courseHead->StudentCourse->FullName << endl;
                        yearHead->NoSemester->course->StudentCourse = yearHead->NoSemester->course->StudentCourse->next;
                    }
                    return;
                }
                yearHead->NoSemester->course = yearHead->NoSemester->course->next;
            }
            yearHead->NoSemester = yearHead->NoSemester->next;
        }
        yearHead = yearHead->next;
    }
    if (!yearHead)
        cout << "Not found!" << endl;
}