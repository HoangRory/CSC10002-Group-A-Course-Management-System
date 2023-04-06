#include "..\Header\View.h"

//task 14: view the list of courses of a stundent in a semester
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

//task 24: view scoreboard of all course of a student in a semester
void ViewScoreboard(Account *accHead, Course *courseHead)
{
    //cout << "Subject\tMid mark\tFinal mark\tOther mark\tTotal mark"; 
    while (courseHead)
    {
        while (courseHead->studentCourse)
        {
            if (courseHead->studentCourse->ID == accHead->username) //truy cập từng student trong từng course check ID 
            {
                cout << courseHead->Name << endl;
                cout << "\tMid mark: " << courseHead->studentCourse->ScoreBoardCourse.midMark << endl;
                cout << "\tFinal mark: " << courseHead->studentCourse->ScoreBoardCourse.finalMark << endl;
                cout << "\tOther mark: " << courseHead->studentCourse->ScoreBoardCourse.otherMark << endl;
                cout << "\tTotal mark: " << courseHead->studentCourse->ScoreBoardCourse.totalMark << endl;
                cout << "\n";
            }
            courseHead->studentCourse = courseHead->studentCourse->next;
        }
        courseHead = courseHead->next;
    }
}