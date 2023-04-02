#include "..\Header\proto.h"

void ViewCoursesOfAStudent(Account *accHead, Course *courseHead) //courseHead in a semester, accHead is current account after the student login
{
    while (courseHead)
    {
        while (courseHead->studentCourse)
        {
            if (courseHead->studentCourse->ID == accHead->username)
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
            courseHead->studentCourse = courseHead->studentCourse->next;
        }
        courseHead = courseHead->next;
    }
}