#include "../Header/Semester.h"

// todo Alternate to sync more efficiently
void SyncFullName(Semester *semHead, Account *accHead)
{
    Semester *sem_cur = semHead;
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
                    if (stcse->FullName != "")
                        break;
                    if (acc_cur->username == stcse->ID)
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
}

void viewCourse(Semester *semHead)
{
    Semester *sem_cur = semHead;
    cout << "List of courses: \n";
    for (int i = 0; i < 88; i++)
        cout << '=';

    cout << '\n'
         << setw(13) << "|     Year   "
         << setw(15) << " | Semester | "
         << setw(15) << " Course ID   | "
         << setw(25) << "    Course name        | "
         << setw(21) << "Teacher name   | " << '\n';

    for (int i = 0; i < 88; i++)
        cout << '=';
    cout << "\n";

    while (sem_cur)
    {
        Course *cour = sem_cur->course;
        while (cour)
        {
            cout << "| " << sem_cur->Year << " - " << sem_cur->Year + 1 << "  |";
            cout << "     " << sem_cur->No << "    |";

            cout << setw(11) << cour->CourseID << "   | ";

            cout << setw(20) << cour->Name << setw(5) << "| ";

            cout << setw(16) << cour->TeacherName << setw(5) << "|\n";

            for (int i = 0; i < 88; i++)
                cout << '=';
            cout << "\n";

            cour = cour->next;
        }
        sem_cur = sem_cur->next;
    }

    cout << "\n";
}