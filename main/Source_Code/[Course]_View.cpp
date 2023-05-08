#include "../Header/Utility.h"
#include "../Header/Course.h"
void ViewStudentCourse(Course *ChooseCourse, int x, int y)
{
    int width[7];
    width[0] = 10; // chiều rộng cột NO
    width[1] = 15; // chiều rộng cột ID
    width[2] = 35; // chiểu rộng Student Name;

    string *title = new string[3];
    title[0] = "No";
    title[1] = "ID";
    title[2] = "Student's Name";

    int num_row = amountStudentOfCourse(ChooseCourse->studentCourse);
    int num_col = 3;

    string **table = new string *[num_row];
    for (int i = 0; i < num_row; i++)
        table[i] = new string[num_col];

    int height = 1, Row_eachTime = 7, Col_eachTime = 8;
    bool edit_Col[3] = {false, false, false};
    StudentCourse *student_cur = ChooseCourse->studentCourse;
    for (int i = 0; i < num_row; i++)
    {
        int j = 0;
        table[i][j++] = to_string(i + 1);
        table[i][j++] = student_cur->ID;
        table[i][j++] = student_cur->FullName;
        student_cur = student_cur->next;
    }
    int x_cur = 0, y_cur = 0;
    Draw_table(table, title, num_row, num_col, width, height, x, y, Row_eachTime, Col_eachTime, edit_Col, x_cur, y_cur);
    // này là để chọn được course

    StudentCourse *curStudent = ChooseCourse->studentCourse;
    if (!curStudent)
    {
        Message_Warning(" There is no student in course " + ChooseCourse->Name, "Error not exist");
        system("cls");
        return;
    }
}
void ViewScoreBoardCourse(Course *ChooseCourse, int x, int y)
{
    int width[7];
    width[0] = 5;  // chiều rộng cột NO
    width[1] = 12; // chiều rộng cột ID
    width[2] = 30; // chiểu rộng Name Course;
    width[3] = 15; // chiều rộng Credits
    width[4] = 15; // chiểu rộng Days
    width[5] = 15; // chiểu rộng Session
    width[6] = 15; // chiểu rộng Room

    string *title = new string[8];
    title[0] = "No";
    title[1] = "ID";
    title[2] = "Name Student";
    title[3] = "Mid Mark";
    title[4] = "Final Mark";
    title[5] = "Other Mark";
    title[6] = "Total Mark";

    StudentCourse *student_cur = ChooseCourse->studentCourse;
    int num_row = amountStudentOfCourse(student_cur);
    int num_col = 7;
    string **table = new string *[num_row];
    for (int i = 0; i < num_row; i++)
        table[i] = new string[num_col];

    int height = 1, Row_eachTime = 7, Col_eachTime = 7;
    bool edit_Col[7] = {false, false, false, false, false, false, false};
    for (int i = 0; student_cur != nullptr; i++)
    {
        int j = 0;
        table[i][j++] = to_string(i + 1);
        table[i][j++] = student_cur->ID;
        table[i][j++] = student_cur->FullName;
        table[i][j++] = FormatMark(student_cur->ScoreBoardCourse.midMark);
        table[i][j++] = FormatMark(student_cur->ScoreBoardCourse.finalMark);
        table[i][j++] = FormatMark(student_cur->ScoreBoardCourse.otherMark);
        table[i][j++] = FormatMark(student_cur->ScoreBoardCourse.totalMark);
        student_cur = student_cur->next;
    }
    int x_cur = 0, y_cur = 0;
    Draw_table(table, title, num_row, num_col, width, height, x, y, Row_eachTime, Col_eachTime, edit_Col, x_cur, y_cur);
}
void ViewCoursesOfAStudent(Account *accHead, Year *yearHead) // courseHead in a semester, accHead is curent account after the student login
{
    system("cls");
    Render_Course(40, 1);
    Render_Student(35, 7);
    int x = 20, y = 15;

    int width[8];
    width[0] = 5;  // chiều rộng cột NO
    width[1] = 12; // chiều rộng cột ID
    width[2] = 30; // chiểu rộng Name Course;
    width[3] = 10; // chiều rộng Credits
    width[4] = 10; // chiểu rộng Days
    width[5] = 10; // chiểu rộng Session
    width[6] = 10; // chiểu rộng Room
    width[7] = 25; // chiều rộng Teacher Name

    string *title = new string[8];
    title[0] = "No";
    title[1] = "ID";
    title[2] = "Name";
    title[3] = "Credits";
    title[4] = "Day";
    title[5] = "Session";
    title[6] = "Room";
    title[7] = "TeacherName ";

    Student *stu_cur = findStudentbyID(accHead->username, yearHead);
    if (stu_cur->course == nullptr)
    {
        Message_Warning("This student is not taking any courses.", "Error not exist");
        return;
    }
    int num_row = amountCourseOfStudent(stu_cur->course);
    int num_col = 8;

    string **table = new string *[num_row];
    for (int i = 0; i < num_row; i++)
        table[i] = new string[num_col];

    CourseStudent *course_cur = stu_cur->course;
    int height = 1, Row_eachTime = 7, Col_eachTime = 8;
    bool edit_Col[8] = {false, false, false, false, false, false, false, false};
    for (int i = 0; i < num_row; i++)
    {
        int j = 0;
        table[i][j++] = to_string(i + 1);
        table[i][j++] = course_cur->course->CourseID;
        table[i][j++] = course_cur->course->Name;
        table[i][j++] = to_string(course_cur->course->Credits);
        table[i][j++] = course_cur->course->Day;
        table[i][j++] = course_cur->course->Session;
        table[i][j++] = course_cur->course->Room;
        table[i][j++] = course_cur->course->TeacherName;
        course_cur = course_cur->next;
    }
    int x_cur = 0, y_cur = 0;
    // bắt đầu in
    goToXY(x, y++);
    cout << "All course of " << accHead->lastName + " " + accHead->firstName << ". MSSV: " << accHead->username;
    Draw_table(table, title, num_row, num_col, width, height, x, y, Row_eachTime, Col_eachTime, edit_Col, x_cur, y_cur);
}