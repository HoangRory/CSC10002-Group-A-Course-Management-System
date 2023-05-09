#include "../Header/Semester.h"
#include "../Header/Year.h"
#include "../Header/Utility.h"
#include "../Header/Help.h"

//! Merge: change to yearHead
void modifySemester(Year *yearHead)
{
    system("cls");
    Year *year_cur = chooseYearbyOption_XY(yearHead, 60, 12, 5);
    system("cls");
    if (!year_cur)
        return;

    vector<string> small_menu;
    small_menu.push_back("1st semester");
    small_menu.push_back("2nd semester");
    small_menu.push_back("3rd semester");
    small_menu.push_back("Back");
    system("cls");
    Render_Semester(59, 3);

    int sem = Draw_XY(small_menu, 60, 12, 4, 20, 63) + 1;
    system("cls");

    Semester *sem_cur = year_cur->NoSemester;

    while (sem_cur)
    {
        if (sem_cur->No == sem)
        {
            // Show the current
            TextColor(63);
            for (int i = 0; i < 4; i++)
            {
                goToXY(50, 8 + i);
                cout << "                                             ";
            }
            goToXY(52, 9);
            cout << "Current semester's start date: " << sem_cur->startDate;
            goToXY(52, 10);
            cout << "Current semester's end date:   " << sem_cur->endDate;

            for (int i = 0; i < 3; i++)
            {
                goToXY(50, 13 + i);
                cout << "                                             ";
                goToXY(50, 17 + i);
                cout << "                                             ";
            }
            goToXY(52, 14);
            cout << "Semester's new start date: ";
            goToXY(52, 18);
            cout << "Semester's new end date:   ";

            sem_cur->startDate = Limit_Input(80, 14, 10, 63);

            while (!isValidDate(sem_cur->startDate))
            {
                if (!Message_YesNo("Invalid date, enter again: ", "Error!"))
                    return;
                TextColor(63);
                goToXY(50, 14);
                cout << "                                             ";
                sem_cur->startDate = Limit_Input(80, 14, 10, 63);
            }

            sem_cur->endDate = Limit_Input(80, 18, 10, 63);
            while (!isValidDate(sem_cur->endDate))
            {
                if (!Message_YesNo("Invalid date, enter again: ", "Error!"))
                    return;
                TextColor(63);
                goToXY(50, 18);
                cout << "                                             ";
                sem_cur->endDate = Limit_Input(80, 18, 10, 63);
            }

            Message_Warning("Semester has been updated", "Sucess!");
            return;
        }
        sem_cur = sem_cur->next;
    }

    Message_Warning("Semester not found!", "Notice");
    return;
}

void modifyCourse(Year *yearHead)
{
    system("cls");
    Render_ViewCourse(50, 1);
    Year *year_cur = chooseYearbyOption_XY(yearHead, 60, 12, 5);
    system("cls");
    if (!year_cur)
        return;

    Semester *sem_cur = year_cur->NoSemester;
    Course *cour_cur = sem_cur->course;

    string course_id;
    TextColor(7);
    goToXY(52, 7);
    cout << "Course ID";
    TextColor(63);
    for (int i = 0; i < 3; i++)
    {
        goToXY(50, 8 + i);
        cout << "                   ";
    }
    course_id = Limit_Input(54, 9, 10, 63);

    while (cour_cur)
    {
        if (cour_cur->CourseID == course_id)
        {
            ChangeCourseInfo(cour_cur); // Change the course in4
            Message_Warning("Course has been updated", "Sucess!");
            return;
        }
        cour_cur = cour_cur->next;
    }

    if (Message_YesNo("Course not found!\nRetry?", "Notice"))
        modifyCourse(yearHead); // Loop again
    return;
}

void ChangeCourseInfo(Course *cour_cur)
{
    system("cls");
    Render_ViewCourse(50, 1);

    vector<string> menu;
    menu.push_back("Course ID: " + cour_cur->CourseID);
    menu.push_back("Course Name: " + cour_cur->Name);
    menu.push_back("Teacher Name: " + cour_cur->TeacherName);
    menu.push_back("Number of credits: " + to_string(cour_cur->Credits));
    menu.push_back("Maximum of students: " + to_string(cour_cur->maxStudents));
    menu.push_back("Room: " + cour_cur->Room);
    menu.push_back("Teaching day: " + cour_cur->Day);
    menu.push_back("Course section: " + cour_cur->Session);

    //! Line 9
    vector<int> choice(menu.size(), 0);
    int cur = 0;
    bool stop = false;
    while (!stop)
    {
        choice[cur] = 1;
        for (int i = 0; i < menu.size(); i++)
        {
            int tmp_color = (choice[i] == 1 ? 63 : 7);

            TextColor(tmp_color);
            for (int j = 0; j < 3; j++)
            {
                goToXY(50, 9 + i * 3 + j);
                cout << "                                                  ";
            }
            goToXY(50 + 2, 9 + i * 3 + 1);
            cout << menu[i];
        }
        int tmp;
        if (tmp = _getch())
        {
            switch (tmp)
            {
            case 72:
                choice[cur] = 0;
                cur = (cur > 0 ? cur - 1 : menu.size() - 1);
                break;
            case 80:
                choice[cur] = 0;
                cur = (cur < menu.size() - 1 ? cur + 1 : 0);
                break;
            case 13:
                stop = true;
                break;
            }
        }
    }
    for (int i = 0; i < menu.size(); i++)
    {
        if (i == cur)
        {
            TextColor(0x9F);
            for (int j = 0; j < 3; j++)
            {
                goToXY(50, 9 + i * 3 + j);
                for (int k = 0; k < 50; k++)
                    cout << " ";
            }
            goToXY(50 + 2, 9 + i * 3);
            cout << menu[i].substr(0, 14);
        }
        else
        {
            TextColor(7);
            goToXY(50 + 2, 9 + i * 3 + 1);
            cout << menu[i];
        }
    }
    string tmp;
    switch (cur)
    {
    case 0:
        cour_cur->CourseID = Limit_Input(50 + 4, 9 + cur * 3 + 1, 10, 71);
        menu[0] = "Course ID: " + cour_cur->CourseID;
        break;
    case 1:
        cour_cur->Name = Limit_Input(50 + 4, 9 + cur * 3 + 1, 35, 71);
        menu[1] = "Course Name: " + cour_cur->Name;
        break;
    case 2:
        cour_cur->TeacherName = Limit_Input(50 + 4, 9 + cur * 3 + 1, 35, 71);
        menu[2] = "Teacher Name: " + cour_cur->TeacherName;
        break;
    case 3:
        cour_cur->Credits = stoi(Limit_Input(50 + 4, 9 + cur * 3 + 1, 1, 71));
        menu[3] = "Number of credits: " + to_string(cour_cur->Credits);
        break;
    case 4:
        cour_cur->maxStudents = stoi(Limit_Input(50 + 4, 9 + cur * 3 + 1, 3, 71));
        menu[4] = "Maximum of students: " + to_string(cour_cur->maxStudents);
        break;
    case 5:
        cour_cur->Room = Limit_Input(50 + 4, 9 + cur * 3 + 1, 3, 71);
        menu[5] = "Room: " + cour_cur->Room;
        break;
    case 6:
        cour_cur->Day = Limit_Input(50 + 4, 9 + cur * 3 + 1, 3, 71);
        while (!isDay(cour_cur->Day))
        {
            Message_Warning("Invalid day!\n(MON/TUE/WED/THU/FRI/SAT/SUN)", "Notice");
            goToXY(50, 9 + cur * 3 + 1);
            cout << "                                                  ";
            cour_cur->Day = Limit_Input(50 + 4, 9 + cur * 3 + 1, 3, 71);
        }
        menu[6] = "Teaching day: " + cour_cur->Day;
        break;
    case 7:
        cour_cur->Session = Limit_Input(50 + 4, 9 + cur * 3 + 1, 2, 71);
        while (!isSession(cour_cur->Session))
        {
            Message_Warning("Invalid session!\n(S1/S2/S3/S4)", "Notice");
            goToXY(50, 9 + cur * 3 + 1);
            cout << "                                                  ";
            cour_cur->Session = Limit_Input(50 + 4, 9 + cur * 3 + 1, 2, 71);
        }
        menu[7] = "Course section: " + cour_cur->Session;
        break;
    }

    if (Message_YesNo("Do you want to change another information?", "Notice"))
        ChangeCourseInfo(cour_cur); // Loop again
    return;
}

//? Remove a course in semester
void removeCourse(Year *yearHead)
{
    system("cls");
    Year *year_cur = chooseYearbyOption_XY(yearHead, 50, 12, 5);
    system("cls");

    if (!year_cur)
        return;

    Semester *sem_cur = year_cur->NoSemester;

    if (!sem_cur) // Check if the year has any semester
    {
        string mess = "There is no semester in this year";
        Message_Warning(mess, "Notice");
        return;
    }

    Course *cour_cur = sem_cur->course, *cour_prev = nullptr;
    // ViewCourseInYear(sem_cur);
    ViewCourse(year_cur);
    string course_id;
    TextColor(71);
    for (int i = 0; i < 3; i++)
    {
        goToXY(52, 9 + i);
        cout << "                                     ";
    }
    goToXY(54, 9);
    cout << "Enter the Course ID to be deleted";
    course_id = Limit_Input(54, 10, 10, 71);

    Semester *tmp = sem_cur;
    while (sem_cur)
    {
        while (cour_cur)
        {
            if (cour_cur->CourseID == course_id)
            {
                string mess = cour_cur->Name + " has been deleted";
                Message_Warning(mess, "Success");

                if (cour_cur == sem_cur->course)
                    sem_cur->course = cour_cur->next;
                else
                    cour_prev->next = cour_cur->next;
                delete cour_cur;

                system("cls");
                goToXY(0, 0);
                ViewCourse(year_cur);
                return;
            }
            cour_prev = cour_cur;
            cour_cur = cour_cur->next;
        }
        sem_cur = sem_cur->next;
        cour_cur = sem_cur->course;
    }

    if (Message_YesNo("Course not found, do you want to rety?", "Notice"))
        removeCourse(yearHead); // Loop again
    return;
}

//? Add a student to a course
void addStudent(Course *courCurrent, string course_id)
{
    StudentCourse *stud_cur;

    if (courCurrent->numStudents == courCurrent->maxStudents)
    {
        Message_Warning("Course is full, cannot add more student", "Notice");
        return;
    }

    TextColor(14);
    goToXY(60, 17);
    cout << "Student ID (-1 to stop)";
    string line;
    int i = 0;

    stud_cur = courCurrent->studentCourse;
    while (stud_cur && stud_cur->next)
        stud_cur = stud_cur->next;
    while (1)
    {
        TextColor(63);
        goToXY(58, 19 + i);
        cout << "                             ";
        line = Limit_Input(60, 19 + i, 8, 63);
        if (line == "-1")
            break;
        for (auto i : line)
            if (!isdigit(i))
            {
                Message_Warning("Invalid ID", "Notice");
                continue;
            }
        i++;
        if (!stud_cur)
        {
            stud_cur = new StudentCourse;
            courCurrent->studentCourse = stud_cur;
        }
        else
        {
            stud_cur->next = new StudentCourse;
            stud_cur->next->prev = stud_cur;
            stud_cur = stud_cur->next;
        }
        stud_cur->ID = line;
        courCurrent->numStudents++;
    }
    Message_Warning("Finished adding student", "Success");
    return;
}

//? Remove a student from a course
void removeStudent(Course *courCurrent, string course_id)
{
    //! Show the current student in the course
    StudentCourse *stud_cur, *stud_prev;
    stud_cur = courCurrent->studentCourse;
    if (!stud_cur)
    {
        Message_Warning("There is no student in this course", "Notice");
        return;
    }
    stud_prev = stud_cur;

    string ID;
    TextColor(71);
    for (int i = 0; i < 3; i++)
    {
        goToXY(52, 9 + i);
        cout << "                                     ";
    }
    ID = Limit_Input(54, 10, 10, 71);

    while (stud_cur)
    {
        if (stud_cur->ID == ID)
        {
            if (stud_cur == courCurrent->studentCourse)
                courCurrent->studentCourse = stud_cur->next;
            else
                stud_prev->next = stud_cur->next;
            delete stud_cur;
            courCurrent->numStudents--; // Decline down the number
            if (Message_YesNo("Student id " + ID + " has been removed", "Notice"))
                removeStudent(courCurrent, course_id);
            return;
        }
        stud_prev = stud_cur;
        stud_cur = stud_cur->next;
    }
    Message_Warning("Student not found, try again.", "Notice");
    return;
}

//? Option to choose to add or remove student
void addRemoveStudent(Year *yearHead)
{
    system("cls");
    Year *year_cur = chooseYearbyOption_XY(yearHead, 50, 12, 5);
    system("cls");
    if (!year_cur)
        return;

    Semester *sem_cur = year_cur->NoSemester;
    if (!sem_cur)
    {
        Message_Warning("No semester in this year yet!", "Notice");
        return;
    }

    vector<string> menu;
    menu.push_back("Add student to a course");
    menu.push_back("Remove student from a course");
    menu.push_back("Back to menu");

    int choice = Draw_XY(menu, 50, 10, 3, 30, 63);
    if (choice == 2)
        return;
    Message_Warning("You chose to " + string(choice == 0 ? "ADD" : "REMOVE") + " student from a course", "Notice");

    Course *cour_cur = sem_cur->course;

    string course_id;
    TextColor(63);
    for (int i = 0; i < 3; i++)
    {
        goToXY(50, 23 + i);
        cout << "                                                 ";
    }
    cout << "Input the course id that you want to add/remove student(s): ";
    course_id = Limit_Input(52, 24, 10, 63);

    while (cour_cur) // Find the course
    {
        if (cour_cur->CourseID == course_id)
        {
            system("cls");
            switch (choice) // Run the chosen option
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

    if (Message_YesNo("Course not found!\nRetry?", "Notice"))
        addRemoveStudent(yearHead); // Loop again
    return;
}