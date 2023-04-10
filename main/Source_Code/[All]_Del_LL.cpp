#include "../Header/Year.h"
#include "../Header/Semester.h"
#include "../Header/Login.h"

//? Delete the year linked list
void DeleteYear(Year *&yearHead)
{
    Year *yearTMP = yearHead;
    while (yearTMP)
    {
        Class *ClassTMP = yearTMP->Class;
        while (ClassTMP)
        {
            Student *StudentTMP = ClassTMP->StudentClass;
            while (StudentTMP)
            {
                Student *StudentTMP2 = StudentTMP;
                StudentTMP = StudentTMP->next;
                delete StudentTMP2;
            }
            Class *ClassTMP2 = ClassTMP;
            ClassTMP = ClassTMP->next;
            delete ClassTMP2;
        }
        Year *yearTMP2 = yearTMP;
        yearTMP = yearTMP->next;
        delete yearTMP2;
    }
    yearHead = nullptr;
}

//? Delete the linked list in the semester
void DeleteStudent(StudentCourse *&stud_head)
{
    if (!stud_head)
        return;
    DeleteStudent(stud_head->next);
    delete stud_head;
    stud_head = nullptr;
}
void DeleteCourse(Course *&course_head)
{
    if (!course_head)
        return;
    DeleteCourse(course_head->next);
    DeleteStudent(course_head->studentCourse);
    delete course_head;
    course_head = nullptr;
}
void DeleteSMT(Year *yearHead)
{
    if (!yearHead->NoSemester)
        return;
    Semester *semHead = yearHead->semester;
    while (semHead)
    {
        DeleteCourse(semHead->course);
        Semester *tmp = semHead->next;
        delete semHead;
        semHead = tmp;
    }
    yearHead->NoSemester = nullptr;
}

//? Delete the account linked list
void DelAccount(Account *&accHead)
{
    if (!accHead)
        return;
    while (accHead)
    {
        Account *tmp = accHead->next;
        delete accHead;
        accHead = tmp;
    }
    accHead = nullptr;
}