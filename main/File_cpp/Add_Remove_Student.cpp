#include "../Header/Semester.h"

void addStudent(Semester *semHead, string id)
{
    Semester *sem_cur = semHead;
    Course *cour_cur;
    StudentCourse *stud_cur, *stud_prev;

    while (sem_cur)
    {
        cour_cur = sem_cur->course;

        while (cour_cur)
        {
            if (cour_cur->CourseID == id)
            {
                cout << "Enter student ID: ";
                string ID;
                cin >> ID;
                stud_cur = cour_cur->studentCourse;
                stud_prev = stud_cur;

                while (stud_cur)
                {
                    if (stud_cur->ID == ID)
                    {
                        cout << "Student already exists\n";
                        return;
                    }
                    stud_prev = stud_cur;
                    stud_cur = stud_cur->next;
                }
                stud_prev->next = new StudentCourse;
                stud_prev->next->ID = ID;
                cour_cur->numStudents++;
                cout << "Student has been added\n";
                return;
            }
            cour_cur = cour_cur->next;
        }
        sem_cur = sem_cur->next;
    }
}

void removeStudent(Semester *semHead, string id)
{
    Semester *sem_cur = semHead;
    Course *cour_cur;
    StudentCourse *stud_cur, *stud_prev;

    while (sem_cur)
    {
        cour_cur = sem_cur->course;

        while (cour_cur)
        {
            if (cour_cur->CourseID == id)
            {
                cout << "Enter student ID: ";
                string ID;
                cin >> ID;
                stud_cur = cour_cur->studentCourse;
                stud_prev = stud_cur;

                while (stud_cur)
                {
                    if (stud_cur->ID == ID)
                    {
                        if (stud_cur == cour_cur->studentCourse)
                            cour_cur->studentCourse = stud_cur->next;
                        else
                            stud_prev->next = stud_cur->next;
                        cour_cur->numStudents--;
                        cout << "Student has been removed\n";
                        return;
                    }
                    stud_prev = stud_cur;
                    stud_cur = stud_cur->next;
                }
                cout << "Student does not exist\n";
                return;
            }
            cour_cur = cour_cur->next;
        }
        sem_cur = sem_cur->next;
    }
}

void addRemoveStudent(Semester *semHead, string id)
{
    cout << "1. Add student\n2. Remove student\n";
    int choice;
    cout << "==> Enter your choice: ";
    cin >> choice;
    switch (choice)
    {
    case 1:
        addStudent(semHead, id);
        break;
    case 2:
        removeStudent(semHead, id);
        break;
    }
}