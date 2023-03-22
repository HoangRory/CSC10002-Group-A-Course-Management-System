#include <iostream>
#include "proto.h"

using namespace std;

Course *courseHead; // in a semester
Account *accHead; // after student run LoggingIn to login his/her acc

void viewCoursesOfAStudent()
{
    while (courseHead)
    {
        while (courseHead->StudentCourse)
        {
            if (courseHead->StudentCourse->ID == accHead->username)
            {
                cout << "Course's name: " << courseHead->Name << endl;
                cout << "ID: " << courseHead->CourseID << endl;
                cout << "Number of credits: " << courseHead->Credits << endl;
                cout << "Teacher's name: " << courseHead->TeacherName << endl;
                cout << "Room: " << courseHead->Room << endl;
                cout << "Number of students: " << courseHead->numStudents << endl;
                cout << "Day: " << courseHead->Day << endl;
                cout << "Session: " << courseHead->Session << endl;
                cout << "\n\n";
                break;
            }
            courseHead->StudentCourse = courseHead->StudentCourse->next;
        }
        courseHead = courseHead->next;
    }
}