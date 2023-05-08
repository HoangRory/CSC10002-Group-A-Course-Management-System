#include "../Header/Course.h"

double CaculateGPA_1_Student(double *&SBC, int n) // n là số môn, tức là số cột của bảng SBC. n là số đã trừ cột cuối ra
{
    double GPA = 0;
    int count = 0; // biến này để đếm xem học sinh này học bao nhiêu môn
    for (int i = 0; i < n; i++)
    {
        if (SBC[i] >= 0)
        {
            GPA += SBC[i];
            count++;
        }
    }
    if (count != 0)
        GPA /= count;
    return GPA;
}
int amountClass(Class *classHead)
{
    int n = 0;
    while (classHead)
    {
        n++;
        classHead = classHead->next;
    }
    return n;
}
int amountCourseOfStudent(CourseStudent *courseHead)
{
    int n = 0;
    while (courseHead)
    {
        courseHead = courseHead->next;
        n++;
    }
    return n;
}
int amountStudentOfCourse(StudentCourse *studentHead)
{
    int n = 0;
    while (studentHead)
    {
        n++;
        studentHead = studentHead->next;
    }
    return n;
}
// task 23
int amountStudentOfClass(Student *studentHead)
{
    int count = 0;
    while (studentHead)
    {
        studentHead = studentHead->next;
        count++;
    }
    return count;
}