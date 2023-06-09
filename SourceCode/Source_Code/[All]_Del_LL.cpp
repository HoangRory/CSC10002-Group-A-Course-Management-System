#include "../Header/Year.h"
#include "../Header/Semester.h"
#include "../Header/Login.h"

//? Delete the year linked list
//! Lồng delete student course vô trong lun
void DeleteYear(Year *&yearHead)
{
    Year *yearTMP = yearHead;
    while (yearTMP)
    {
        // Class in the year
        Class *ClassTMP = yearTMP->Class;
        while (ClassTMP)
        {
            // Delete all the slots for student in linked list
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
        // Delete all semesters in the year
        DeleteSMT(yearTMP);
        Year *yearTMP2 = yearTMP;
        yearTMP = yearTMP->next;
        delete yearTMP2;
    }
    yearHead = nullptr; // Set the head to nullptr
}

//? Delete the linked list in the semester
void DeleteStudent(StudentCourse *&stud_head)
{
    if (!stud_head)
        return;
    DeleteStudent(stud_head->next); // Recursion to delete the next student slot
    delete stud_head;
    stud_head = nullptr;
}
void DeleteCourse(Course *&course_head)
{
    if (!course_head)
        return;
    DeleteCourse(course_head->next); // Recursion to delete the next course inside
    DeleteStudent(course_head->studentCourse); // Delete the linked list that store student in4
    delete course_head;
    course_head = nullptr; // return the head to nullptr
}
void DeleteSMT(Year *yearHead)
{
    if (!yearHead->NoSemester)
        return;
    Semester *semHead = yearHead->NoSemester;
    while (semHead)
    {
        DeleteCourse(semHead->course); // Call the delete the course inside semester
        Semester *tmp = semHead->next;
        delete semHead;
        semHead = tmp;
    }
    yearHead->NoSemester = nullptr; // Return the semester to nullptr
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