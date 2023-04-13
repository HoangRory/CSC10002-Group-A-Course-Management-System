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
    for (int i = 1; i <= 84; i++)
        cout << "=";
    cout << "\n";
    cout << "| Subject" << setw(28) << "Mid mark"<< setw(15) << "Final mark" << setw(15) << "Other mark" << setw(17) << "Total mark |" << endl; 
    for (int i = 1; i <= 84; i++)
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
                cout << setw(35 - courseHead->Name.length()) << right << cur_stu->ScoreBoardCourse.midMark;
                cout << setw(23 - to_string(cur_stu->ScoreBoardCourse.midMark).length()) << right << cur_stu->ScoreBoardCourse.finalMark;
                cout << setw(15) << right << cur_stu->ScoreBoardCourse.otherMark;
                cout << setw(15) << right << cur_stu->ScoreBoardCourse.totalMark << " |";
                cout << "\n";
            }
            cur_stu = cur_stu->next;
        }
        courseHead = courseHead->next;
    }
    for (int i = 1; i <= 84; i++)
        cout << "=";
}
// int main()
// {
//     Account *accHead = new Account;
//     accHead->username = "22127026";

//     Course *courseHead = new Course;
//     courseHead->CourseID = "CSC10001";
//     courseHead->Name = "Nhap mon lap trinh";
//     courseHead->studentCourse = new StudentCourse;
//     courseHead->studentCourse->ID = "22127001";
//     courseHead->studentCourse->FullName = "Nguyen Van A";
//     courseHead->studentCourse->next = new StudentCourse;
//     courseHead->studentCourse->next->ID = "22127026";
//     courseHead->studentCourse->next->ScoreBoardCourse.midMark = 9;
//     courseHead->studentCourse->next->ScoreBoardCourse.finalMark = 10;
//     courseHead->studentCourse->next->ScoreBoardCourse.otherMark = 8;
//     courseHead->studentCourse->next->ScoreBoardCourse.totalMark = 9.9;

//     courseHead->next = new Course;
//     courseHead->next->CourseID = "BAA0010";
//     courseHead->next->Name = "Triet hoc Mac Le-nin";
//     courseHead->next->studentCourse = new StudentCourse;
//     courseHead->next->studentCourse->ID = "22127001";
//     courseHead->next->studentCourse->FullName = "Nguyen Van A";
//     courseHead->next->studentCourse->next = new StudentCourse;
//     courseHead->next->studentCourse->next->ID = "22127020";
//     courseHead->next->studentCourse->next->FullName = "Le thi C";
//     courseHead->next->studentCourse->next->ScoreBoardCourse.midMark = 5;
//     courseHead->next->studentCourse->next->ScoreBoardCourse.finalMark = 6.5;
//     courseHead->next->studentCourse->next->ScoreBoardCourse.otherMark = 8;
//     courseHead->next->studentCourse->next->ScoreBoardCourse.totalMark = 7;

//     courseHead->next->next = new Course;
//     courseHead->next->next->CourseID = "CSC10002";
//     courseHead->next->next->Name = "Ky thuat lap trinh";
//     courseHead->next->next->studentCourse = new StudentCourse;
//     courseHead->next->next->studentCourse->ID = "22127026";
//     courseHead->next->next->studentCourse->FullName = "On Gia Bao";
//     courseHead->next->next->studentCourse->ScoreBoardCourse.midMark = 6;
//     courseHead->next->next->studentCourse->ScoreBoardCourse.finalMark = 7;
//     courseHead->next->next->studentCourse->ScoreBoardCourse.otherMark = 8;
//     courseHead->next->next->studentCourse->ScoreBoardCourse.totalMark = 9;
//     courseHead->next->next->studentCourse->next = new StudentCourse;
//     courseHead->next->next->studentCourse->next->ID = "22127275";
//     courseHead->next->next->studentCourse->next->FullName = "Tran Anh Minh";
//     courseHead->next->next->studentCourse->next->ScoreBoardCourse.midMark = 10;
//     courseHead->next->next->studentCourse->next->ScoreBoardCourse.finalMark = 10;
//     courseHead->next->next->studentCourse->next->ScoreBoardCourse.otherMark = 10;
//     courseHead->next->next->studentCourse->next->ScoreBoardCourse.totalMark = 10;

//     ViewScoreboard(accHead, courseHead);
//     return 0;
// }