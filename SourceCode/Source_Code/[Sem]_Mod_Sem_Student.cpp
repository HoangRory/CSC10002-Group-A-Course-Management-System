#include "../Header/Semester.h"
#include "../Header/Year.h"
#include "../Header/Utility.h"
#include "../Header/Help.h"

//? Modify semester date detail
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

    if (sem == 4)
        return;

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

            string tmp, date;
            tmp = Limit_Input(80, 14, 10, 63);
            if (tmp == "-1")
                return;

            while (!isValidDate(tmp))
            {
                if (tmp == "-1")
                    return;
                if (!Message_YesNo("Invalid date, enter again\n(dd/mm/yyyy)", "Error!"))
                    return;
                TextColor(63);
                goToXY(50, 14);
                cout << "                                             ";
                goToXY(52, 14);
                cout << "Semester's new start date: ";
                tmp = Limit_Input(80, 14, 10, 63);
            }
            date = tmp;

            tmp = Limit_Input(80, 18, 10, 63);
            while (!isValidDate(tmp) || compareDate(date, tmp) != -1)
            {
                if (tmp == "-1")
                    return;

                if (isValidDate(tmp) && compareDate(date, tmp) != -1)
                    Message_Warning("End date must be after start date", "Error!");
                else
                {
                    if (!Message_YesNo("Invalid date, enter again\n(dd/mm/yyyy)", "Error!"))
                        return;
                }
                TextColor(63);
                goToXY(50, 18);
                cout << "                                             ";
                goToXY(52, 18);
                cout << "Semester's new end date:   ";
                tmp = Limit_Input(80, 18, 10, 63);
            }
            sem_cur->startDate = date;
            sem_cur->endDate = tmp;

            Message_Warning("Semester has been updated", "Sucess!");
            return;
        }
        sem_cur = sem_cur->next;
    }

    Message_Warning("Semester not found!", "Notice");
    modifySemester(yearHead);
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
    cout << "Student ID (ESC to stop)";
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
    if (ID == "-1")
        return;

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
    goToXY(48, 22);
    cout << "Input the course id that you want to add/remove student(s)";
    course_id = Limit_Input(52, 24, 10, 63);
    if (course_id == "-1")
        return;

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
