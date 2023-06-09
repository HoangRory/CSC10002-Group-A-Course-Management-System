#include "../Header/Course.h"
#pragma warning(suppress : 4996)
string FormatMark(double Mark)
{
    string Format = "";
    if (Mark == 10)
        Format = to_string(Mark).substr(0, 5);
    else if (Mark < 0 || Mark > 10)
        Format = " X";
    else
        Format = " " + to_string(Mark).substr(0, 4);
    return Format;
}
string getFirstChar(string name)
{
    // char* c_name = new char[name.length()];
    // strcpy(c_name, name.c_str());
    char *c_name = (char *)name.c_str();
    int n = name.length();
    if (n == 0)
        return name;
    string tmp = "";
    char space = ' ';
    tmp += toupper(c_name[0]);
    for (int i = 0; i < n; i++)
        if ((int)c_name[i] == (int)space)
        {
            if (isdigit(c_name[i]))
                tmp += c_name[i];
            else
                tmp += toupper(c_name[i + 1]);
        }
    return tmp;
}

string createNameFile(int year, int no_smt)
{

    string s_year = to_string(year) + "_" + to_string(year + 1) + "\\";
    string s_smt = "smt" + to_string(no_smt) + "\\";
    string path = s_year + s_smt;
    return path;
}
CourseStudent *CourseOfAClass_InChooseSem(Student *studentHead, Semester *ChooseSem)
{
    CourseStudent *CourHead = nullptr, *tmp = nullptr;
    CourseStudent *courseCheck;
    CourseStudent *Course_in_Sem = nullptr;
    Course *course_cur = ChooseSem->course;
    while (course_cur)
    {
        tmp = new CourseStudent;
        tmp->course = course_cur;
        tmp->next = Course_in_Sem;
        Course_in_Sem = tmp;
        course_cur = course_cur->next;
    }
    while (studentHead)
    {
        courseCheck = studentHead->course;
        while (courseCheck)
        {
            if (!checkExistence_OfCourse(courseCheck, CourHead) && checkExistence_OfCourse(courseCheck, Course_in_Sem))
            {
                tmp = new CourseStudent;
                tmp->course = courseCheck->course;
                tmp->next = CourHead;
                CourHead = tmp;
            }
            courseCheck = courseCheck->next;
        }
        studentHead = studentHead->next;
    }
    return CourHead;
}
// nhập các final mark vào bảng điểm của lớp
void CreateSB_ofStudent_inClass(double *&SBC, CourseStudent *courseHead, Student *studentHead)
{
    StudentCourse *tmp;
    CourseStudent *courseCheck;
    int i = 0;
    while (courseHead)
    {
        courseCheck = checkExistence_OfCourse(courseHead, studentHead->course);
        if (courseCheck)
        {
            tmp = find_StudentOfCourse(studentHead->ID, courseHead->course->studentCourse);
            SBC[i++] = tmp->ScoreBoardCourse.finalMark;
        }
        else
            SBC[i++] = -1; // -1 là hs này không học môn đó
        courseHead = courseHead->next;
    }
}
void createSBC_ofClass(double **&SBC, CourseStudent *courseHead, Student *studentHead, int Col, int Row)
{
    SBC = new double *[Row];
    for (int i = 0; i < Row; i++)
    {
        SBC[i] = new double[Col + 1]; // +1 là + 1 cột cuối để lưu GPA của học sinh đó trong kì này
        CreateSB_ofStudent_inClass(SBC[i], courseHead, studentHead);
        SBC[i][Col] = CaculateGPA_1_Student(SBC[i], Col);
        studentHead = studentHead->next;
    }
}
