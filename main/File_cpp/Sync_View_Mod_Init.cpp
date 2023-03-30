// #include "Header/proto.h"
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
    for (int i = 0; i < 100; i++)
        cout << '-';

    while (sem_cur)
    {
        Course *cour = sem_cur->course;

        cout << "\nSemester " << sem_cur->No << " - " << sem_cur->Year << " - " << sem_cur->Year + 1 << '\n';

        while (cour)
        {
            cout << '\n';
            cout << "Course ID: " << cour->CourseID;
            cout << "\nCourse name: " << cour->Name;
            cout << "\nTeacher name: " << cour->TeacherName << "\n";

            cour = cour->next;
        }
        sem_cur = sem_cur->next;
    }
    for (int i = 0; i < 100; i++)
        cout << '-';
}

void initModify(Semester *&semHead)
{
    for (int i = 0; i < 100; i++)
        cout << '-';
    cout << "\nOptions:\n";
    cout << "1. Modify semester\n";
    cout << "2. Modify course\n";
    cout << "3. Delete a course\n";
    cout << "4. Add or remove a student\n";
    cout << "5. Quit\n";

    int opt;
    cout << "\n==> Your option: ";
    cin >> opt;
    string id;
    switch (opt)
    {
    case 1:
        int sem, year;
        cout << "Choose the year: ";
        cin >> year;
        cout << "Choose the semester: ";
        cin >> sem;
        modifySemester(semHead, sem, year);
        break;
    case 2:
        cout << "Choose the course ID: ";
        cin >> id;
        modifyCourse(semHead, id);
        break;
    case 3:
        cout << "Choose the course ID: ";
        cin >> id;
        deleteCourse(semHead, id);
        break;
    case 4:
        cout << "Choose the course ID: ";
        cin >> id;
        addRemoveStudent(semHead, id);
        break;
    case 5:
        cout << "Goodbye!";
        return;
    }
    initModify(semHead);
}