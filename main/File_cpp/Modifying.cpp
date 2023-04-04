#include "../Header/Semester.h"

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

            cout << "Semster has been updated\n\n";
            Sleep(1000);
            return;
        }
        sem_cur = sem_cur->next;
    }
}
// todo: Can choose to remain some information
void modifyCourse(Semester *semHead, int year)
{
    viewCourse(semHead);
    Semester *sem_cur = semHead;
    Course *cour_cur;
    while (sem_cur)
    {
        if (sem_cur->Year == year)
        {
            cour_cur = sem_cur->course;
            break;
        }
        sem_cur = sem_cur->next;
    }

    string course_id;
    cout << "Enter the course ID that need to be modified: ";
    cin >> course_id;

    while (cour_cur)
    {
        if (cour_cur->CourseID == course_id)
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

    cout << "Course not found!\nRety? (Y/N)";
    char ch;
    cin >> ch;

    while (ch != 'Y' || ch != 'y' || ch != 'N' || ch != 'n')
    {
        cout << "Invalid respond, enter again!";
        cin >> ch;
    }

    if (ch == 'Y' || ch == 'y')
    {
        modifyCourse(semHead, year);
        return;
    }
    return;
}

void deleteCourse(Semester *semHead, int year)
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    system("cls");
    cout << "\n";
    Semester *sem_cur = semHead;
    Course *cour_cur, *cour_prev;

    while (sem_cur)
    {
        if (sem_cur->Year == year)
        {
            cour_cur = sem_cur->course;
            break;
        }
        sem_cur = sem_cur->next;
    }
    if (!sem_cur)
    {
        cout << "Semester not found!\n";
        Sleep(1000);
        return;
    }

    viewCourse(sem_cur);
    string course_id;
    SetConsoleTextAttribute(h, RED);
    cout << "Enter the course ID that need to be deleted: ";
    SetConsoleTextAttribute(h, WHITE);
    cin >> course_id;

    while (cour_cur)
    {
        if (cour_cur->CourseID == course_id)
        {
            SetConsoleTextAttribute(h, GREEN);
            cout << "\n";
            cout << cour_cur->Name << " has been deleted\n";
            SetConsoleTextAttribute(h, WHITE);
            if (cour_cur == sem_cur->course)
                sem_cur->course = cour_cur->next;
            else
                cour_prev->next = cour_cur->next;
            delete cour_cur;
            system("cls");
            viewCourse(sem_cur);
            return;
        }
        cour_prev = cour_cur;
        cour_cur = cour_cur->next;
    }

    cout << "Course not found!\nRety? (Y/N) ";
    char ch;
    cin >> ch;

    while (ch != 'Y' && ch != 'y' && ch != 'N' && ch != 'n')
    {
        cout << "Invalid respond, enter again: ";
        cin >> ch;
    }

    if (ch == 'Y' || ch == 'y')
    {
        deleteCourse(semHead, year);
        return;
    }
    return;
}

void addStudent(Course *courCurrent, string course_id)
{
    StudentCourse *stud_cur, *stud_prev;

    if (courCurrent->numStudents == courCurrent->maxStudents)
    {
        cout << "Course is full, cannot add more student\n";
        return;
    }
    cout << "Enter student ID: ";
    string ID;
    cin >> ID;
    stud_cur = courCurrent->studentCourse;
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
    stud_cur = new StudentCourse;
    stud_cur->ID = ID;
    stud_cur->next = nullptr;
    stud_cur->prev = stud_prev;
    if (stud_prev)
        stud_prev->next = stud_cur;
    else
        courCurrent->studentCourse = stud_cur;
    courCurrent->numStudents++;
    cout << "Student has been added\n";
    return;
}

void removeStudent(Course *courCurrent, string course_id)
{
    StudentCourse *stud_cur, *stud_prev;

    cout << "Enter student ID: ";
    string ID;
    cin >> ID;
    stud_cur = courCurrent->studentCourse;
    stud_prev = stud_cur;

    while (stud_cur)
    {
        if (stud_cur->ID == ID)
        {
            if (stud_cur == courCurrent->studentCourse)
                courCurrent->studentCourse = stud_cur->next;
            else
                stud_prev->next = stud_cur->next;
            delete stud_cur;
            courCurrent->numStudents--;
            cout << "Student has been removed\n";
            return;
        }
        stud_prev = stud_cur;
        stud_cur = stud_cur->next;
    }
    cout << "Student not found\n";
    return;
}

void addRemoveStudent(Semester *semHead, int year)
{
    bool stop = false;
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

    int choice = 1;
    string *menu = new string[3];
    menu[0] = "Choose to ADD or to REMOVE student from a course\n";
    menu[1] = "- Add student to a course                       \n";
    menu[2] = "- Remove student from a course                  \n";

    for (int i = 0; i < 3; i++)
    {
        if (i == choice)
        {
            SetConsoleTextAttribute(h, YELLOW);
            cout << menu[i];
            SetConsoleTextAttribute(h, WHITE);
        }
        else
            cout << menu[i];
    }
    SetConsoleTextAttribute(h, GREEN);
    cout << "\n\n(Using your arrow on the keyboard to move the choice and enter to select!)\n\n";
    SetConsoleTextAttribute(h, WHITE);
    ShowConsoleCursor(false);

    while (!stop)
    {
        if (_kbhit())
        {
            switch (_getch())
            {
            case UP:
                if (choice > 1)
                    choice--;
                break;
            case DOWN:
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

            SetConsoleTextAttribute(h, GREEN);
            cout << "\n(Using your arrow on the keyboard to move the choice and enter to select!)\n\n";
            SetConsoleTextAttribute(h, WHITE);

            for (int i = 1; i < 3; i++)
            {
                if (i == choice)
                {
                    SetConsoleTextAttribute(h, YELLOW);
                    cout << menu[i];
                    SetConsoleTextAttribute(h, WHITE);
                }
                else
                    cout << menu[i];
            }
        }
    }
    delete[] menu;
    ShowConsoleCursor(true);

    cout << "You chose to " << (choice == 1 ? "ADD" : "REMOVE") << " student from a course.\n";

    Semester *sem_cur = semHead;
    Course *cour_cur;

    while (sem_cur)
    {
        if (sem_cur->Year == year)
        {
            cour_cur = sem_cur->course;
            break;
        }
        sem_cur = sem_cur->next;
    }
    string course_id;
    cout << "Input the course id: ";
    cin >> course_id;

    while (cour_cur)
    {
        if (cour_cur->CourseID == course_id)
        {
            switch (choice)
            {
            case 1:
                addStudent(cour_cur, course_id);
                break;
            case 2:
                removeStudent(cour_cur, course_id);
                break;
            }
            return;
        }
        cour_cur = cour_cur->next;
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
    {
        addRemoveStudent(semHead, year);
        return;
    }
    return;
}