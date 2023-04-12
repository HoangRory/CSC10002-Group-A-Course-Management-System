#include "..\Header\View.h"

//task 14: view the list of courses of a stundent in a semester
void ViewCoursesOfAStudent(Account *accHead, Course *courseHead) //courseHead in a semester, accHead is current account after the student login
{
    for (int i = 1; i <= 112; i++)
        cout << "=";
    cout << "\n";
    cout << "|    ID" << setw(20) << "Name"<< setw(21) << "Credit" << setw(11) << "Day" << setw(15)  << "Session"  << setw(10) << "Room" << setw(15) << "Teacher" << setw(13) << "|" << endl; 
    for (int i = 1; i <= 112; i++)
        cout << "=";
    cout << "\n";
    while (courseHead)
    {
        StudentCourse *cur_stu = courseHead->studentCourse;
        while (cur_stu)
        {
            if (cur_stu->ID == accHead->username)
            {
                cout << "| " << courseHead->CourseID;
                cout << "       " << courseHead->Name;
                cout << setw(29 - courseHead->Name.length()) << right << courseHead->Credits;
                cout << setw(13) << right << courseHead->Day;
                cout << setw(12) << right << courseHead->Session;   
                cout << setw(12) << right << courseHead->Room;  
                cout << "         " << courseHead->TeacherName << setw(20 - courseHead->TeacherName.length()) << "|";       
                cout << "\n";
                break;
            }
            cur_stu = cur_stu->next;
        }
        courseHead = courseHead->next;
    }
    for (int i = 1; i <= 112; i++)
        cout << "=";
}

//task 24: view scoreboard of all course of a student in a semester
void ViewScoreboard(Account *accHead, Course *courseHead)
{
    for (int i = 1; i <= 85; i++)
        cout << "=";
    cout << "\n";
    cout << "|            Subject" << setw(24) << "| Mid mark"<< setw(13) << "| Final mark" << setw(13) << "| Other mark" << setw(15) << "| Total mark |" << endl; 
    for (int i = 1; i <= 85; i++)
        cout << "=";
    cout << "\n";
    while (courseHead)
    {
        StudentCourse *cur_stu = courseHead->studentCourse;
        while (cur_stu)
        {
            if (cur_stu->ID == accHead->username) //truy cập từng student trong từng course check ID 
            {
                cout <<  "| " << courseHead->Name;
                cout << setw(34 - courseHead->Name.length()) << "| " << setw(8) << cur_stu->ScoreBoardCourse.midMark;
                cout << " |" << setw(11) << cur_stu->ScoreBoardCourse.finalMark;
                cout << " |" << setw(11) << right << cur_stu->ScoreBoardCourse.otherMark;
                cout << " |" << setw(11) << right << cur_stu->ScoreBoardCourse.totalMark << " |";
                cout << "\n";
                for (int i = 1; i <= 85; i++)
                    cout << "=";
                cout << "\n";
            }
            cur_stu = cur_stu->next;
        }
        courseHead = courseHead->next;
    }
}