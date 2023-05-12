#include "../Header/Semester.h"
#include "../Header/Year.h"
#include "../Header/Login.h"
#include "../Header/Utility.h"

// todo Alternate to sync more efficiently
//? get infor student from account linklist
void SyncInForStudent(Year *yearHead, Account *accHead)
{
    Year *year_cur;
    Class *class_cur;
    Student *student_cur;
    Account *account_cur;
    year_cur = yearHead;
    while (year_cur)
    {
        class_cur = year_cur->Class;
        while (class_cur)
        {
            student_cur = class_cur->StudentClass;
            while (student_cur)
            {
                account_cur = accHead;
                while (account_cur && student_cur->ID != account_cur->username)
                    account_cur = account_cur->next;
                if (account_cur == nullptr)
                {
                    Message_Warning("Student information with ID: " + student_cur->ID + " does not exist.", "error import");
                }
                else
                {
                    student_cur->accStudent = account_cur;
                }
                student_cur = student_cur->next;
            }
            class_cur = class_cur->next;
        }
        year_cur = year_cur->next;
    }
}

void SyncCourse(Year *yearHead)
{
    Year *year_cur1 = yearHead;
    Year *year_cur2;
    while (year_cur1)
    {
        Semester *sem_cur = year_cur1->NoSemester;
        while (sem_cur)
        {
            Course *cse = sem_cur->course;
            while (cse)
            {
                StudentCourse *stcse = cse->studentCourse;
                while (stcse)
                {
                    year_cur2 = yearHead;
                    while (year_cur2)
                    {
                        Class *class_cur = year_cur2->Class;
                        while (class_cur)
                        {
                            Student *stclass = class_cur->StudentClass;
                            while (stclass && stclass->ID != stcse->ID)
                                stclass = stclass->next;
                            if (stclass != nullptr)
                            {
                                if (stclass->course == nullptr)
                                    stclass->course = new CourseStudent;
                                else
                                {
                                    CourseStudent *tmp = new CourseStudent;
                                    tmp->next = stclass->course;
                                    stclass->course = tmp;
                                }
                                stclass->course->course = cse;
                                break;
                            }
                            class_cur = class_cur->next;
                        }
                        year_cur2 = year_cur2->next;
                    }
                    stcse = stcse->next;
                }
                cse = cse->next;
            }
            sem_cur = sem_cur->next;
        }
        year_cur1 = year_cur1->next;
    }
}

//? get the fullname from account linked list
void SyncFullName(Year *yearHead, Account *accHead)
{
    Year *year_cur = yearHead;
    while (year_cur)
    {
        Semester *sem_cur = year_cur->NoSemester;
        while (sem_cur)
        {
            Course *cse = sem_cur->course;
            while (cse)
            {
                StudentCourse *stcse = cse->studentCourse;
                while (stcse)
                {
                    Account *acc_cur = accHead;
                    while (acc_cur)
                    {
                        if (stcse->FullName == "" && acc_cur->username == stcse->ID)
                        {
                            stcse->FullName = acc_cur->lastName + ' ' + acc_cur->firstName;
                            break;
                        }
                        acc_cur = acc_cur->next;
                    }
                    stcse = stcse->next;
                }
                cse = cse->next;
            }
            sem_cur = sem_cur->next;
        }
        year_cur = year_cur->next;
    }
}