#include "../Header/Semester.h"

// todo: Can choose to remain some information
void modifyCourse(Semester *semHead, string id)
{
    system("cls");
    cout << "\n";
    cout << "Modifying course " << id << "\n\n";
    Semester *sem_cur = semHead;
    Course *cour_cur;

    while (sem_cur)
    {
        cour_cur = sem_cur->course;

        while (cour_cur)
        {
            if (cour_cur->CourseID == id)
            {
                cout << "Enter the new course name: ";
                cin.ignore();
                getline(cin, cour_cur->Name);

                cout << "Enter the new teacher name: ";
                getline(cin, cour_cur->TeacherName);

                cout << "Enter the new number of credits: ";
                cin >> cour_cur->Credits;

                cout << "\nEnter the new maximum of students: ";
                cin >> cour_cur->maxStudents;

                cout << "Choose the room of the course: ";
                cin >> cour_cur->Room;

                cout << "Teaching day\n(MON/TUE/WED/THU/FRI/SAT): ";
                cin >> cour_cur->Day;

                cout << "Course section\nS1-(07:30)\tS2-(09:30)\nS3-(13:30)\tS4-(15:30)\n==> ";
                cin >> cour_cur->Session;

                cout << "\nCourse has been updated\n";
                Sleep(1000);
                return;
            }
            cour_cur = cour_cur->next;
        }
        sem_cur = sem_cur->next;
    }
}

void modifySemester(Semester *semHead, int year, int sem)
{
    system("cls");
    cout << "\n";
    viewCourse(semHead);

    Semester *sem_cur = semHead;
    Course *cour_cur;

    while (sem_cur)
    {
        if (sem_cur->Year == year && sem_cur->No == sem)
        {
            cout << "Semester's new start date: ";
            cin >> sem_cur->startDate;

            cout << "Semester's end date: ";
            cin >> sem_cur->endDate;

            cout << "Semster has been updated\n";
            Sleep(1000);
            return;
        }
        sem_cur = sem_cur->next;
    }
}

void deleteCourse(Semester *semHead, string id)
{
    Semester *sem_cur = semHead;
    Course *cour_cur, *cour_prev;

    while (sem_cur)
    {
        cour_cur = sem_cur->course;
        cour_prev = cour_cur;

        while (cour_cur)
        {
            if (cour_cur->CourseID == id)
            {
                cout << cour_cur->Name << " has been deleted\n";
                if (cour_cur == sem_cur->course)
                    sem_cur->course = cour_cur->next;
                else
                    cour_prev->next = cour_cur->next;
                delete cour_cur;
                return;
            }
            cour_prev = cour_cur;
            cour_cur = cour_cur->next;
        }
        sem_cur = sem_cur->next;
    }
    cout << "\nXXX Cannot find course XXX\n";
    Sleep(1000);
}