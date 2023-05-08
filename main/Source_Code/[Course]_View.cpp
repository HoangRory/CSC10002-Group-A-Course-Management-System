#include "../Header/course.h"
#include "../Header/Utility.h"

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
    int num_row = amountCourseOf_aStudent(stu_cur->course);
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
// task 15: view all classes which are existed
void ViewClass(Year *yearHead)
{
    system("cls");
    int x = 40, y = 3;
    Render_Class(x, y);
    goToXY(45, 10);
    cout << "Select the Year, in which you want to show all class.";
    Year *ChooseYear = chooseYearbyOption_XY(yearHead, 60, 12, 5);
    goToXY(45, 10);
    cout << setw(100) << " ";
    if (ChooseYear == nullptr)
        return;
    x = 50, y = 10; //? đặt lại vị trí dòng chữ tại đây
    Class *cls_cur = ChooseYear->Class;
    goToXY(x, y++);
    cout << "List of class in school year " << ChooseYear->yearStart << "-" << ChooseYear->yearStart + 1; // seperate the list into many parts by the school year
    goToXY(x, y++);
    x = 50; //? đặt lại vị trí bảng tại đây
    int width[2];
    width[0] = 10; // chiều rộng cột NO
    width[1] = 25; // chiều rộng cột Class name
    string *title = new string[2];
    title[0] = "   No";
    title[1] = "   Class Name";
    int num_row = amountClass(cls_cur);
    int num_col = 2;
    string **table = new string *[num_row];
    for (int i = 0; i < num_row; i++)
        table[i] = new string[num_col];

    int height = 1, Row_eachTime = 8, Col_eachTime = 2;
    bool edit_Col[7] = {false, false};
    for (int i = 0; i < num_row; i++)
    {
        int j = 0;
        table[i][j++] = "   " + to_string(i + 1);
        table[i][j++] = "   " + cls_cur->Name;
        cls_cur = cls_cur->next;
    }
    int x_cur = 0, y_cur = 0;
    Draw_table(table, title, num_row, num_col, width, height, x, y, Row_eachTime, Col_eachTime, edit_Col, x_cur, y_cur);
    ViewClass(yearHead);
}
void ViewStudentClass(Class *ChooseClass, int x, int y)
{
    Student *student_cur = ChooseClass->StudentClass;
    goToXY(x, y++);
    cout << "List of students in " << ChooseClass->Name;
    int width[3];
    width[0] = 10; // chiều rộng cột NO
    width[1] = 15; // chiều rộng cột ID
    width[2] = 35; // chiểu rộng Student Name;

    string *title = new string[3];
    title[0] = "No";
    title[1] = "ID";
    title[2] = "Student Name";

    int num_row = amountStudentOfClass(ChooseClass->StudentClass);
    int num_col = 3;

    string **table = new string *[num_row];
    for (int i = 0; i < num_row; i++)
        table[i] = new string[num_col];

    int height = 1, Row_eachTime = 6, Col_eachTime = 8;
    bool edit_Col[3] = {false, false, false};

    for (int i = 0; student_cur != nullptr; i++)
    {
        int j = 0;
        table[i][j++] = to_string(i + 1);
        table[i][j++] = student_cur->ID;
        table[i][j++] = student_cur->accStudent->lastName + " " + student_cur->accStudent->firstName;
        student_cur = student_cur->next;
    }
    int x_cur = 0, y_cur = 0;
    Draw_table(table, title, num_row, num_col, width, height, x, y, Row_eachTime, Col_eachTime, edit_Col, x_cur, y_cur);
}
void ViewStudentCourse(Course *ChooseCourse, int x, int y)
{
    int width[7];
    width[0] = 10; // chiều rộng cột NO
    width[1] = 15; // chiều rộng cột ID
    width[2] = 35; // chiểu rộng Student Name;

    string *title = new string[3];
    title[0] = "No";
    title[1] = "ID";
    title[2] = "Student Name";

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
// task 23
//  mảng này sẽ có dạng | môn A | môn B |....| môn Z | GPA |
void ViewScoreboardClass(Class *Class, Semester *ChooseSem, int x, int y)
{
    Render_ScoreBoardClass();
    Student *student_cur = Class->StudentClass;
    CourseStudent *courseHead = CourseOfAClass_InChooseSem(student_cur, ChooseSem);
    if (courseHead == nullptr)
    {
        Message_Warning(Class->Name + " class has no subjects this semester", "Error not exist");
        return;
    }

    int num_col = amountCourseOfClass(courseHead);
    int num_row = amountStudentOfClass(student_cur);
    double **SBC;
    createSBC_ofClass(SBC, courseHead, student_cur, num_col, num_row);
    num_col += 4;

    string *title = new string[num_col];
    CourseStudent *course_cur = courseHead;
    title[0] = "No";
    title[1] = "ID";
    title[2] = "Full Name";
    for (int i = 3; course_cur != nullptr; i++, course_cur = course_cur->next)
    {
        title[i] = course_cur->course->Name;
    }
    title[num_col - 1] = "GPA";
    string **table = new string *[num_row];
    for (int i = 0; i < num_row; i++)
        table[i] = new string[num_col];

    int height = 1, Row_eachTime = 7, Col_eachTime = 7;
    bool *edit_Col = new bool[num_col];
    for (int i = 0; i < num_col; i++)
        edit_Col[i] = false;
    for (int i = 0; student_cur != nullptr; i++)
    {
        int j = 0;
        table[i][j++] = to_string(i + 1);
        table[i][j++] = student_cur->ID;
        table[i][j++] = student_cur->accStudent->lastName + " " + student_cur->accStudent->firstName;
        while (j < num_col)
        {
            table[i][j] = FormatMark(SBC[i][j - 3]);
            j++;
        }
        student_cur = student_cur->next;
    }
    int *width = new int[num_col];
    width[0] = 5;  // chiều rộng cột NO
    width[1] = 12; // chiều rộng cột ID
    width[2] = 30; // chiểu rộng Student Name;
    for (int i = 3; i < num_col - 1; i++)
        width[i] = title[i].length() + 2;
    width[num_col - 1] = 10;
    int x_cur = 0, y_cur = 0;
    Draw_table(table, title, num_row, num_col, width, height, x, y, Row_eachTime, Col_eachTime, edit_Col, x_cur, y_cur);

    for (int i = 0; i < num_row; i++)
        delete[] SBC[i];
    delete[] SBC;
    delete[] title;
    delete[] width;
    delete[] edit_Col;
}

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
        cur_stu = find_SBC_ofStudent(accHead->username, tmp->course->studentCourse);
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
