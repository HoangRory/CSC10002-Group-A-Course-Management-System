#include "../Header/Semester.h"

//! Merge: change to yearHead
void modifySemester(Year *yearHead, int year, int sem)
{
    cout << "\n";

    Year *year_cur = yearHead;
    while (year_cur && year_cur->yearStart != year)
        year_cur = year_cur->next;

    Semester *sem_cur = year_cur->NoSemester;

    while (sem_cur)
    {
        if (sem_cur->No == sem)
        {
            cout << "Current semester's start date: " << sem_cur->startDate << "\n";
            cout << "Current semester's end date: " << sem_cur->endDate << "\n\n";

            cout << "Semester's new start date: ";
            cin >> sem_cur->startDate;

            cout << "Semester's end date: ";
            cin >> sem_cur->endDate;

            TextColor(GREEN);
            cout << "Semster has been updated\n\n";
            TextColor(WHITE);
            Sleep(1000);
            return;
        }
        sem_cur = sem_cur->next;
    }

    cout << "Semester not found!\n";
    return;
}

void modifyCourse(Year *yearHead, int year)
{
    Year *year_cur = yearHead;
    while (year_cur && year_cur->yearStart != year)
        year_cur = year_cur->next;

    Semester *sem_cur = year_cur->NoSemester;
    Course *cour_cur = sem_cur->course;

    string course_id;
    TextColor(LIGHT_BLUE);
    cout << "Enter the course ID that need to be modified: ";
    TextColor(WHITE);

    cin >> course_id;

    while (cour_cur)
    {
        if (cour_cur->CourseID == course_id)
        {
            ChangeCourseInfo(cour_cur);

            TextColor(GREEN);
            cout << "\nCourse has been updated\n";
            TextColor(WHITE);
            Sleep(500);
            return;
        }
        cour_cur = cour_cur->next;
    }

    cout << "Course not found!\nRety? (Y/N)";
    char ch;
    cin >> ch;

    while (ch != 'Y' && ch != 'y' && ch != 'N' && ch != 'n')
    {
        cout << "Invalid respond, enter again!";
        cin >> ch;
    }

    if (ch == 'Y' || ch == 'y')
    {
        modifyCourse(yearHead, year);
        return;
    }
    return;
}

void ChangeCourseInfo(Course *cour_cur)
{
    string *menu = new string[8];
    menu[0] = "\nChoose the information that need to be changed: \n";
    menu[1] = "- Course Name: " + cour_cur->Name + "\n";
    menu[2] = "- Teacher Name: " + cour_cur->TeacherName + "\n";
    menu[3] = "- Number of credits: " + to_string(cour_cur->Credits) + "\n";
    menu[4] = "- Maximum of students: " + to_string(cour_cur->maxStudents) + "\n";
    menu[5] = "- Room: " + cour_cur->Room + "\n";
    menu[6] = "- Teaching day: " + cour_cur->Day + "\n";
    menu[7] = "- Course section: " + cour_cur->Session + "\n";

    int opt = 1;
    bool stop = false;
    for (int i = 0; i < 8; i++)
    {
        if (i == opt)
        {
            TextColor(LIGHT_PURPLE);
            cout << menu[i];
            TextColor(WHITE);
        }
        else
            cout << menu[i];
    }

    TextColor(GREEN);
    cout << "\n\n(Using your arrow on the keyboard to move the choice and enter to select!)\n\n";
    TextColor(WHITE);
    ShowConsoleCursor(false);
    while (!stop)
    {
        if (_kbhit())
        {
            switch (_getch())
            {
            case UP:
                if (opt > 1)
                    opt--;
                break;
            case DOWN:
                if (opt < 7)
                    opt++;
                break;
            case ENTER:
                stop = true;
                break;
            }
            if (stop)
                break;
            system("cls");
            for (int i = 0; i < 8; i++)
            {
                if (i == opt)
                {
                    TextColor(LIGHT_PURPLE);
                    cout << menu[i];
                    TextColor(WHITE);
                }
                else
                    cout << menu[i];
            }
            TextColor(GREEN);
            cout << "\n\nUsing your arrow on the keyboard to move the choice and enter to select!\n\n";
            TextColor(WHITE);
        }
    }
    delete[] menu;
    // system("cls");
    ShowConsoleCursor(true);
    TextColor(LIGHT_BLUE);
    switch (opt)
    {
    case 1:
        cout << "\nEnter the new course name: ";
        cin.ignore();
        getline(cin, cour_cur->Name);
        break;
    case 2:
        cout << "\nEnter the new teacher name: ";
        getline(cin, cour_cur->TeacherName);
        break;
    case 3:
        cout << "\nEnter the new number of credits: ";
        cin >> cour_cur->Credits;
        break;
    case 4:
        cout << "\nEnter the new maximum of students: ";
        cin >> cour_cur->maxStudents;
        break;
    case 5:
        cout << "\nChoose the room of the course: ";
        cin >> cour_cur->Room;
        break;
    case 6:
        cout << "\nTeaching day\n(MON/TUE/WED/THU/FRI/SAT): ";
        cin >> cour_cur->Day;
        break;
    case 7:
        cout << "\nCourse section\nS1-(07:30)\tS2-(09:30)\nS3-(13:30)\tS4-(15:30)\n==> ";
        cin >> cour_cur->Session;
        break;
    }
    TextColor(WHITE);
    cout << "\nReviewing the course information";
    for (int i = 0; i < 5; i++)
    {
        Sleep(300);
        cout << ".";
    }

    system("cls");
    cout << "\n";
    TextColor(LIGHT_BLUE);
    cout << "\n\tNew information for the course " << cour_cur->CourseID << ":\n";
    cout << "- Course name: " << cour_cur->Name << "\n";
    cout << "- Teacher name: " << cour_cur->TeacherName << "\n";
    cout << "- Number of credits: " << cour_cur->Credits << "\n";
    cout << "- Maximum of students: " << cour_cur->maxStudents << "\n";
    cout << "- Room: " << cour_cur->Room << "\n";
    cout << "- Teaching day: " << cour_cur->Day << "\n";
    cout << "- Course section: " << cour_cur->Session << "\n";
    Sleep(1000);
    TextColor(WHITE);

    cout << "Do you want to change another information? (Y/N): ";
    char ch;
    cin >> ch;
    while (ch != 'Y' && ch != 'y' && ch != 'N' && ch != 'n')
    {
        cout << "Invalid respond, enter again: ";
        cin >> ch;
    }
    if (ch == 'Y' || ch == 'y')
        ChangeCourseInfo(cour_cur);
    return;
}

void deleteCourse(Year *yearHead, int year)
{
    system("cls");
    cout << "\n";
    Year *year_cur = yearHead;

    while (year_cur)
    {
        if (year_cur->yearStart == year)
            break;
        year_cur = year_cur->next;
    }

    Semester *sem_cur = year_cur->semester;

    if (!sem_cur)
    {
        cout << "This year hasn't had any semester yet!\n";
        Sleep(400);
        return;
    }

    Course *cour_cur = sem_cur->course, *cour_prev = nullptr;

    ViewCourseInYear(sem_cur);
    string course_id;

    TextColor(LIGHT_RED);
    cout << "Enter the course ID that need to be deleted: ";
    TextColor(WHITE);

    cin >> course_id;
    Semester *tmp = sem_cur;
    while (sem_cur)
    {
        while (cour_cur)
        {
            if (cour_cur->CourseID == course_id)
            {
                TextColor(LIGHT_GREEN);
                cout << "\n";
                cout << cour_cur->Name << " has been deleted\n";
                TextColor(WHITE);

                if (cour_cur == sem_cur->course)
                    sem_cur->course = cour_cur->next;
                else
                    cour_prev->next = cour_cur->next;
                delete cour_cur;

                system("cls");
                cout << "\nAfter deleting the course:\n";
                ViewCourseInYear(tmp);
                return;
            }
            cour_prev = cour_cur;
            cour_cur = cour_cur->next;
        }
        sem_cur = sem_cur->next;
        cour_cur = sem_cur->course;
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
        deleteCourse(yearHead, year);
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
    cout << "Enter student ID (Enter -1 to stop): ";
    string ID;
    cin >> ID;
    if (ID == "-1")
        return;
    
    stud_cur = courCurrent->studentCourse;
    stud_prev = stud_cur;

    while (stud_cur)
    {
        if (stud_cur->ID == ID)
        {
            cout << "Student already exists\n";
            addStudent(courCurrent, course_id);
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
    addStudent(courCurrent, course_id);
    return;
}

void removeStudent(Course *courCurrent, string course_id)
{
    //! Show the current student in the course
    StudentCourse *stud_cur, *stud_prev;

    string ID;

    cout << "Enter student ID (Enter -1 to stop): ";
    cin >> ID;

    if (ID == "-1")
        return;

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
            removeStudent(courCurrent, course_id);
            return;
        }
        stud_prev = stud_cur;
        stud_cur = stud_cur->next;
    }
    cout << "Student not found, try again.\n";
    return;
}

void addRemoveStudent(Year *yearHead, int year)
{
    system("cls");
    Year *year_cur = yearHead;
    while (year_cur && year_cur->yearStart != year)
        year_cur = year_cur->next;

    bool stop = false;

    int choice = 1;
    string *menu = new string[3];
    menu[0] = "Choose to ADD or to REMOVE student from a course\n";
    menu[1] = "- ADD student to a course                       \n";
    menu[2] = "- REMOVE student from a course                  \n";

    for (int i = 0; i < 3; i++)
    {
        if (i == choice)
        {
            TextColor(LIGHT_YELLOW);
            cout << menu[i];
            TextColor(WHITE);
        }
        else
            cout << menu[i];
    }
    TextColor(LIGHT_GREEN);
    cout << "\n\n(Using your arrow on the keyboard to move the choice and enter to select!)\n\n";
    TextColor(WHITE);
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

            TextColor(LIGHT_GREEN);
            cout << "\n(Using your arrow on the keyboard to move the choice and enter to select!)\n\n";
            TextColor(WHITE);

            for (int i = 1; i < 3; i++)
            {
                if (i == choice)
                {
                    TextColor(LIGHT_YELLOW);
                    cout << menu[i];
                    TextColor(WHITE);
                }
                else
                    cout << menu[i];
            }
        }
    }
    delete[] menu;
    ShowConsoleCursor(true);

    cout << "You chose to " << (choice == 1 ? "ADD" : "REMOVE") << " student from a course.\n";

    Semester *sem_cur = year_cur->NoSemester;
    if (!sem_cur)
    {
        cout << "No semester in this year yet!\n";
        return;
    }
    Course *cour_cur = sem_cur->course;

    string course_id;
    cout << "Input the course id that you want to add/remove student(s): ";
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
        addRemoveStudent(yearHead, year);
        return;
    }
    return;
}