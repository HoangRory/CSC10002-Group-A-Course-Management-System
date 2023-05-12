#include "../Header/Student.h"

// task 24: view scoreboard of all course of a student in a semester
void ViewScoreboard(Account *accHead, Course *courseHead)
{
    system("cls");
    Render_ScoreBoard(25, 1); // in ra chữ scoreboard bắt đầu từ ngang 25 dọc 1

    int width[7];  // chiều rộng của các cột
    width[0] = 8;  // chiều rộng cột NO
    width[1] = 14; // chiều rộng cột ID
    width[2] = 30; // chiểu rộng Name Course;
    width[3] = 15; // chiều rộng Mid
    width[4] = 15; // chiểu rộng Final
    width[5] = 15; // chiểu rộng Other
    width[6] = 15; // chiểu rộng Total

    string *title = new string[8];
    title[0] = "No";
    title[1] = "ID";
    title[2] = "Subject";
    title[3] = "Mid Mark";
    title[4] = "Final Mark";
    title[5] = "Other Mark";
    title[6] = "Total Mark";

    int num_row = 0;
    int num_col = 7;
    CourseStudent *list_course_of_student = nullptr; // danh sách khóa học của học sinh này trong học kì này
    CourseStudent *tmp = nullptr;
    StudentCourse *cur_stu = nullptr;
    // đếm số course của học sinh trong ki này và tạo list course mà student này học trong kì này
    while (courseHead)
    {
        cur_stu = courseHead->studentCourse;
        while (cur_stu)
        {

            if (cur_stu->ID == accHead->username) // truy cập từng student trong từng course check ID
            {
                num_row++;
                if (!list_course_of_student)
                    list_course_of_student = new CourseStudent;
                else
                {
                    tmp = new CourseStudent;
                    tmp->next = list_course_of_student;
                    list_course_of_student = tmp;
                }
                list_course_of_student->course = courseHead;
            }
            cur_stu = cur_stu->next;
        }
        courseHead = courseHead->next;
    }
    if (list_course_of_student == nullptr)
    {
        Message_Warning("This student is not taking any courses in this semester.", "Error not exist");
        return;
    }
    int height = 1, Row_eachTime = 8, Col_eachTime = 7;
    bool edit_Col[7] = {false, false, false, false, false, false, false}; // không có cột nào được sửa nhen
    tmp = list_course_of_student;
    // tạo table điểm để in ra ở draw table
    string **table = new string *[num_row];
    for (int i = 0; i < num_row; i++)
        table[i] = new string[num_col];
    for (int i = 0; tmp != nullptr; i++)
    {
        int j = 0;
        table[i][j++] = to_string(i + 1); // No
        table[i][j++] = tmp->course->CourseID;
        table[i][j++] = tmp->course->Name;
        cur_stu = find_StudentOfCourse(accHead->username, tmp->course->studentCourse);
        table[i][j++] = FormatMark(cur_stu->ScoreBoardCourse.midMark);
        table[i][j++] = FormatMark(cur_stu->ScoreBoardCourse.finalMark);
        table[i][j++] = FormatMark(cur_stu->ScoreBoardCourse.otherMark);
        table[i][j++] = FormatMark(cur_stu->ScoreBoardCourse.totalMark);
        tmp = tmp->next;
    }
    int x_cur = 0, y_cur = 0;
    int x = 25, y = 8;
    goToXY(x, y++);
    cout << "ScoreBoard of " << accHead->lastName + " " + accHead->firstName << ". MSSV: " << accHead->username;
    goToXY(x, y++);

    Draw_table(table, title, num_row, num_col, width, height, x, y, Row_eachTime, Col_eachTime, edit_Col, x_cur, y_cur);
    // dưới này là delete linked list và mảng động
    while (list_course_of_student)
    {
        tmp = list_course_of_student;
        list_course_of_student = list_course_of_student->next;
        delete tmp;
    }
    for (int i = 0; i < num_row; i++)
        delete[] table[i];
    delete[] table;
}
// task 14: view the list of courses of a stundent in a semester
void ViewCoursesOfUser(Student *student_cur, Course *courseHead) // courseHead in a semester, accHead is curent account after the student login
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

    int num_row = 0;
    CourseStudent *listcourse = nullptr;
    while (courseHead)
    {
        CourseStudent *course_cur = student_cur->course;
        while (course_cur)
        {
            if (course_cur->course == courseHead)
            {
                CourseStudent *tmp = new CourseStudent;
                tmp->next = listcourse;
                tmp->course = course_cur->course;
                listcourse = tmp;
                num_row++;
            }
            course_cur = course_cur->next;
        }
        courseHead = courseHead->next;
    }
    if (listcourse == nullptr)
    {
        Message_Warning("This student is not taking any courses in this Semester.", "Error not exist");
        return;
    }
    int num_col = 8;

    string **table = new string *[num_row];
    for (int i = 0; i < num_row; i++)
        table[i] = new string[num_col];

    CourseStudent *course_cur = listcourse;
    int height = 1, Row_eachTime = 8, Col_eachTime = 8;
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
    cout << "All course of " << student_cur->accStudent->lastName + " " + student_cur->accStudent->firstName << ". MSSV: " << student_cur->accStudent->username;
    Draw_table(table, title, num_row, num_col, width, height, x, y, Row_eachTime, Col_eachTime, edit_Col, x_cur, y_cur);
}