#include "..\Header\proto.h"

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