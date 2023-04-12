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
        while (courseHead->studentCourse)
        {
            if (courseHead->studentCourse->ID == accHead->username)
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
            courseHead->studentCourse = courseHead->studentCourse->next;
        }
        courseHead = courseHead->next;
    }
    for (int i = 1; i <= 112; i++)
        cout << "=";
}

//task 24: view scoreboard of all course of a student in a semester
void ViewScoreboard(Account *accHead, Course *courseHead)
{
    for (int i = 1; i <= 84; i++)
        cout << "=";
    cout << "\n";
    cout << "| Subject" << setw(28) << "Mid mark"<< setw(15) << "Final mark" << setw(15) << "Other mark" << setw(17) << "Total mark |" << endl; 
    for (int i = 1; i <= 84; i++)
        cout << "=";
    cout << "\n";
    while (courseHead)
    {
        while (courseHead->studentCourse)
        {
            if (courseHead->studentCourse->ID == accHead->username) //truy cập từng student trong từng course check ID 
            {
                cout <<  "| " << courseHead->Name;
                cout << setw(35 - courseHead->Name.length()) << right << courseHead->studentCourse->ScoreBoardCourse.midMark;
                cout << setw(23 - to_string(courseHead->studentCourse->ScoreBoardCourse.midMark).length()) << right << courseHead->studentCourse->ScoreBoardCourse.finalMark;
                cout << setw(15) << right << courseHead->studentCourse->ScoreBoardCourse.otherMark;
                cout << setw(15) << right << courseHead->studentCourse->ScoreBoardCourse.totalMark << " |";
                cout << "\n";
            }
            courseHead->studentCourse = courseHead->studentCourse->next;
        }
        courseHead = courseHead->next;
    }
    for (int i = 1; i <= 84; i++)
        cout << "=";
}