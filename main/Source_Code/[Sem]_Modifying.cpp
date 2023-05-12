#include "../Header/Semester.h"
#include "../Header/Year.h"
#include "../Header/Utility.h"
#include "../Header/Help.h"

//! Merge: change to yearHead
void modifySemester(Year *yearHead)
{
    system("cls");
    Render_Semester(59, 3);
    Year *year_cur = chooseYearbyOption_XY(yearHead, 60, 12, 5);
    if (!year_cur)
        return;

    Semester *sem_cur = chooseSemesterbyOption_XY(year_cur->NoSemester, 60, 12, 4);
    string tmp, date;
    while (sem_cur)
    {
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

        tmp = Limit_Input(80, 14, 10, 63);
        if (tmp == "-1")
            return;

        while (!isValidDate(tmp))
        {
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
        date = tmp;

        tmp = Limit_Input(80, 18, 10, 63);
        while (!isValidDate(tmp))
        {
            if (tmp == "-1")
                return;
            if (!Message_YesNo("Invalid date, enter again: ", "Error!"))
                return;
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
        system("cls");
        Render_Semester(59, 3);
        sem_cur = chooseSemesterbyOption_XY(year_cur->NoSemester, 60, 12, 4);
    }
    modifySemester(yearHead);
}

void modifyCourse(Year *yearHead)
{
    system("cls");
    Render_ViewCourse(50, 1);
    Year *year_cur = chooseYearbyOption_XY(yearHead, 60, 12, 5);
    if (!year_cur)
        return;

    Semester *sem_cur = chooseSemesterbyOption_XY(year_cur->NoSemester, 60, 12, 4);
    Course *cour_cur;
    while (sem_cur && sem_cur->course != nullptr)
    {
        cour_cur = chooseCoursebyOption_XY(sem_cur->course, 60, 12, 5);
        while (cour_cur)
        {
            ChangeCourseInfo(cour_cur); // Change the course in4
            // Message_Warning("Course has been updated", "Sucess!");
            system("cls");
            Render_ViewCourse(50, 1);
            cour_cur = chooseCoursebyOption_XY(sem_cur->course, 60, 12, 5);
        }
        sem_cur = chooseSemesterbyOption_XY(year_cur->NoSemester, 60, 12, 4);
    }
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
    menu.push_back("Back");

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
                goToXY(50, 6 + i * 3 + j);
                cout << "                                                  ";
            }
            goToXY(50 + 2, 6 + i * 3 + 1);
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
                goToXY(50, 6 + i * 3 + j);
                for (int k = 0; k < 50; k++)
                    cout << " ";
            }
            goToXY(50 + 2, 6 + i * 3);
            cout << menu[i].substr(0, 14);
        }
        else
        {
            TextColor(7);
            goToXY(50 + 2, 6 + i * 3 + 1);
            cout << menu[i];
        }
    }
    TextColor(7);
    string tmp;
    switch (cur)
    {
    case 0:
        tmp = Limit_Input(50 + 4, 6 + cur * 3 + 1, 10, 63);
        if (tmp == "-1")
            return;
        cour_cur->CourseID = tmp;
        menu[0] = "Course ID: " + cour_cur->CourseID;
        break;
    case 1:
        tmp = Limit_Input(50 + 4, 6 + cur * 3 + 1, 35, 63);
        if (tmp == "-1")
            return;
        cour_cur->Name = tmp;
        menu[1] = "Course Name: " + cour_cur->Name;
        break;
    case 2:
        tmp = Limit_Input(50 + 4, 6 + cur * 3 + 1, 35, 63);
        if (tmp == "-1")
            return;
        cour_cur->TeacherName = tmp;
        menu[2] = "Teacher Name: " + cour_cur->TeacherName;
        break;
    case 3:
        tmp = Limit_Input(50 + 4, 6 + cur * 3 + 1, 1, 63);
        while (tmp[0] < '0' || tmp[0] > '4')
        {
            if (tmp == "-1")
                return;
            Message_Warning("Invalid credit format or exceed the credits limit (0-4)!", "Error");
            TextColor(63);
            goToXY(50 + 4, 6 + cur * 3 + 1);
            cout << " ";
            tmp = Limit_Input(50 + 4, 6 + cur * 3 + 1, 1, 63);
        }
        cour_cur->Credits = stoi(tmp);
        menu[3] = "Number of credits: " + to_string(cour_cur->Credits);
        break;
    case 4:
        tmp = Limit_Input(50 + 4, 6 + cur * 3 + 1, 3, 63);
        if (tmp == "-1")
            return;
        while (!isStringDigits(tmp))
        {
            Message_Warning("Invalid max student format!", "Error");
            TextColor(63);
            goToXY(50 + 4, 6 + cur * 3 + 1);
            cout << "   ";
            tmp = Limit_Input(50 + 4, 6 + cur * 3 + 1, 3, 63);
            if (tmp == "-1")
                return;
        }
        cour_cur->maxStudents = stoi(tmp);
        menu[4] = "Maximum of students: " + to_string(cour_cur->maxStudents);
        break;
    case 5:
        tmp = Limit_Input(50 + 4, 6 + cur * 3 + 1, 3, 63);
        if (tmp == "-1")
            return;
        cour_cur->Room = tmp;
        menu[5] = "Room: " + cour_cur->Room;
        break;
    case 6:
        tmp = Limit_Input(50 + 4, 6 + cur * 3 + 1, 3, 63);
        while (!isDay(tmp))
        {
            if (tmp == "-1")
                return;
            Message_Warning("Invalid day!\n(MON/TUE/WED/THU/FRI/SAT/SUN)", "Notice");
            goToXY(50, 6 + cur * 3 + 1);
            cout << "                                                  ";
            tmp = Limit_Input(50 + 4, 6 + cur * 3 + 1, 3, 63);
        }
        cour_cur->Day = tmp;
        menu[6] = "Teaching day: " + cour_cur->Day;
        break;
    case 7:
        tmp = Limit_Input(50 + 4, 6 + cur * 3 + 1, 2, 63);
        while (!isSession(tmp))
        {
            if (tmp == "-1")
                return;
            Message_Warning("Invalid session!\n(S1/S2/S3/S4)", "Notice");
            goToXY(50, 6 + cur * 3 + 1);
            cout << "                                                  ";
            tmp = Limit_Input(50 + 4, 6 + cur * 3 + 1, 2, 63);
        }
        cour_cur->Session = tmp;
        menu[7] = "Course section: " + cour_cur->Session;
        break;
    case 8:
        return;
    }

    if (Message_YesNo("Do you want to change another information?", "Notice"))
        ChangeCourseInfo(cour_cur); // Loop again
    return;
}

//? Remove a course in semester
void removeCourse(Year *yearHead)
{
    system("cls");
    Render_ViewCourse(50, 1);
    Year *year_cur = chooseYearbyOption_XY(yearHead, 60, 12, 5);
    if (!year_cur)
        return;

    Semester *sem_cur = chooseSemesterbyOption_XY(year_cur->NoSemester, 60, 12, 4);
    Course *cour_cur;
    while (sem_cur && sem_cur->course != nullptr)
    {
        cour_cur = chooseCoursebyOption_XY(sem_cur->course, 60, 12, 5);
        while (cour_cur)
        {
            string mess = cour_cur->Name + " has been deleted";
            Message_Warning(mess, "Success");
            if (cour_cur->prev)
                cour_cur->prev->next = cour_cur->next;
            if (cour_cur->next)
                cour_cur->next->prev = cour_cur->prev;
            if (cour_cur = sem_cur->course)
                sem_cur->course = cour_cur->next;
            delete cour_cur;
            system("cls");
            Render_ViewCourse(50, 1);
            cour_cur = chooseCoursebyOption_XY(sem_cur->course, 60, 12, 5);
        }
        sem_cur = chooseSemesterbyOption_XY(year_cur->NoSemester, 60, 12, 4);
    }
    removeCourse(yearHead); // Loop again
}

//? Add a student to a course
void addStudent(Course *courCurrent)
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
void removeStudent(Course *courCurrent)
{
    system("cls");
    Render_ViewCourse(50, 1);
    int width[7];
    width[0] = 10; // chiều rộng cột NO
    width[1] = 15; // chiều rộng cột ID
    width[2] = 35; // chiểu rộng Student Name;

    string *title = new string[3];
    title[0] = "No";
    title[1] = "ID";
    title[2] = "Student's Name";

    int num_row = amountStudentOfCourse(courCurrent->studentCourse);
    int num_col = 3;
    if (num_row == 0)
    {
        Message_Warning("There is no student in this course", "Noice");
        return;
    }
    string **table = new string *[num_row];
    for (int i = 0; i < num_row; i++)
        table[i] = new string[num_col];

    int height = 1, Row_eachTime = 7, Col_eachTime = 8, x = 45, y = 12;
    bool edit_Col[3] = {true, true, true};
    StudentCourse *student_cur = courCurrent->studentCourse;
    for (int i = 0; i < num_row; i++)
    {
        int j = 0;
        table[i][j++] = to_string(i + 1);
        table[i][j++] = student_cur->ID;
        table[i][j++] = student_cur->FullName;
        student_cur = student_cur->next;
    }
    int x_cur = 0, y_cur = 0;
    goToXY(x, y - 2);
    cout << "Press Enter to choose student";
    Draw_table(table, title, num_row, num_col, width, height, x, y, Row_eachTime, Col_eachTime, edit_Col, x_cur, y_cur);

    // search and del student
    for (int i = 0; i < num_row; i++)
        delete[] table[i];
    delete[] table;
    if (x_cur == -1)
        return;
    StudentCourse *curStudent = courCurrent->studentCourse;
    for (int i = 0; i < y_cur; i++)
        curStudent = curStudent->next;
    string ID = curStudent->ID;
    if (curStudent->next)
        curStudent->next->prev = curStudent->prev;
    if (curStudent->prev)
        curStudent->prev->next = curStudent->next;
    if (curStudent == courCurrent->studentCourse)
        courCurrent->studentCourse = curStudent->next;
    delete curStudent;
    courCurrent->numStudents--; // Decline down the number
}

//? Option to choose to add or remove student
void addRemoveStudent(Year *yearHead)
{
    system("cls");
    Render_ViewCourse(50, 1);
    Year *year_cur = chooseYearbyOption_XY(yearHead, 60, 12, 5);
    if (!year_cur)
        return;
    Semester *sem_cur = chooseSemesterbyOption_XY(year_cur->NoSemester, 60, 12, 4);
    Course *cour_cur;
    // while (year_cur)
    // {
    while (sem_cur && sem_cur->course != nullptr)
    {
        cour_cur = chooseCoursebyOption_XY(sem_cur->course, 60, 12, 5);
        while (cour_cur)
        {
            int choice = -1;
            while (choice != 2)
            {
                vector<string> menu;
                menu.push_back("Add student to a course");
                menu.push_back("Remove student from a course");
                menu.push_back("Back");

                choice = Draw_XY(menu, 50, 10, 3, 30, 63);
                switch (choice) // Run the chosen option
                {
                case 0:
                    addStudent(cour_cur);
                    break;
                case 1:
                    removeStudent(cour_cur);
                    break;
                }
                system("cls");
                Render_ViewCourse(50, 1);
            }
            cour_cur = chooseCoursebyOption_XY(sem_cur->course, 60, 12, 5);
        }
        sem_cur = chooseSemesterbyOption_XY(year_cur->NoSemester, 60, 12, 4);
    }
    addRemoveStudent(yearHead); // Loop again
    // return;
}