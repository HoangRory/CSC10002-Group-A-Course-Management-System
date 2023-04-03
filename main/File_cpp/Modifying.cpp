#include "Header/Semester.h"

//! Merge: change to yearHead
void modifySemester(Semester *semHead, int year, int sem)
{
    cout << "\n";

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
// todo: Can choose to remain some information
void modifyCourse(Semester *semHead)
{
    viewCourse(semHead);
    string course_id;

    cin >> course_id;

    cout << "\n";
    cout << "\nModifying course " << id << "\n\n";
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
    cout << "Course not found!\nRety? (Y/N)";
    char ch;
        cin >> ch;
    while (ch != 'Y' || ch != 'y' || ch != 'N' || ch != 'n')
    {
        cout << "Invalid respond, enter again!";
        cin >> ch;
    }

    if (ch == 'Y' || ch == 'y')
        modifyCourse(semHead);
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

void addStudent(Semester *semHead, string course_id = "")
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

void addRemoveStudent(Semester *semCurrent)
{
    bool stop = false;
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(h, RED);
    cout << "\nUsing your arrow on the keyboard to move the choice and enter to select!\n\n";

    SetConsoleTextAttribute(h, YELLOW);
    cout << "Add student to a course\n";
    SetConsoleTextAttribute(h, WHITE);
    cout << "Remove student from a course\n";
    int choice = 1;

    while (!stop)
    {
        if (_kbhhit())
        {
            switch (_getch())
            {
            case VK_UP:
                if (choice > 1)
                    choice--;
                break;
            case VK_DOWN:
                if (choice < 2)
                    choice++;
                break;
            case ENTER:
                stop = true;
                break;
            }
            if (stop)
                break;
            system("cls");

            SetConsoleTextAttribute(h, RED);
            cout << "\nUsing your arrow on the keyboard to move the choice and enter to select!\n\n";
            SetConsoleTextAttribute(h, WHITE);
            switch (choice)
            {
            case 1:
                SetConsoleTextAttribute(h, YELLOW);
                cout << "Add student to a course\n";
                SetConsoleTextAttribute(h, WHITE);
                cout << "Remove student from a course\n";
                break;
            case 2:
                cout << "Add student to a course\n";
                SetConsoleTextAttribute(h, YELLOW);
                cout << "Remove student from a course\n";
                SetConsoleTextAttribute(h, WHITE);
                break;
            }
        }
    }
    cout << "You chose to " << (choice == 1 ? "add" : "remove") << " student from a course.\n";
    switch (choice)
    {
    case 1:
        addStudent(semCurrent);
        break;
    case 2:
        removeStudent(semCurrent);
        break;
    }
    return;
}