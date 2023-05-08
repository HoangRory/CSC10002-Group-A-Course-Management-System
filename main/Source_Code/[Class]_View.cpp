#include "../Header/Class.h"

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

    int num_col = amountCourseOfStudent(courseHead);
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