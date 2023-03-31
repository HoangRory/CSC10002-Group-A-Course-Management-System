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

void initModify(Semester *&semHead)
{
    system("cls");
    cout << "\n";
    viewCourse(semHead);

    cout << "Options:\n";
    cout << "1. Modify semester\n";
    cout << "2. Modify course\n";
    cout << "3. Delete a course\n";
    cout << "4. Add or remove a student\n";
    cout << "5. Quit\n";

    int opt;
    cout << "\n==> Your option: ";
    cin >> opt;
    while (opt < 1 || opt > 5)
    {
        cout << "Please choose the correct option: ";
        cin >> opt;
    }
    cout << "\n";
    string id;
    switch (opt)
    {
    case 1:
        cout << "\nYour choice is to modify the semester!\n";
        int sem, year;
        cout << "==> Please choose the year: ";
        cin >> year;
        cout << "==> Please choose the semester: ";
        cin >> sem;
        cout << "\n";
        modifySemester(semHead, sem, year);
        break;
    case 2:
        cout << "Your choice is to modify a course\n==> Please choose the course ID: ";
        cin >> id;
        cout << "\n";
        modifyCourse(semHead, id);
        break;
    case 3:
        cout << "Your choice is to delete a course\n==> Please choose the course ID: ";
        cin >> id;
        cout << "\n";
        deleteCourse(semHead, id);
        break;
    case 4:
        cout << "Your choice is to manage a student\n==> Please choose the student ID: ";
        cin >> id;
        cout << "\n";
        //? Showing the list of students
        addRemoveStudent(semHead, id);
        break;
    case 5:
        cout << "You choose to quit!\n";
        cout << "Cleaning up the system...\n";
        Sleep(1000);
        cout << "Saving completed\n";
        return;
    }
    initModify(semHead);
}