#include "../Header/Semester.h"
#include "../Header/Year.h"
#include "../Header/Utility.h"
#include "../Header/Help.h"

//? Modifying course
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
    goToXY(51, 7);
    cout << "Enter the course ID";
    TextColor(63);
    for (int i = 0; i < 3; i++)
    {
        goToXY(50, 8 + i);
        cout << "                   ";
    }
    course_id = Limit_Input(54, 9, 10, 63);
    if (course_id == "-1")
        return;

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

//? Choose course information to modify
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
        tmp = Limit_Input(50 + 4, 9 + cur * 3 + 1, 10, 71);
        if (tmp == "-1")
            return;
        cour_cur->CourseID = tmp;
        menu[0] = "Course ID: " + cour_cur->CourseID;
        break;
    case 1:
        tmp = Limit_Input(50 + 4, 9 + cur * 3 + 1, 35, 71);
        if (tmp == "-1")
            return;
        cour_cur->Name = tmp;
        menu[1] = "Course Name: " + cour_cur->Name;
        break;
    case 2:
        tmp = Limit_Input(50 + 4, 9 + cur * 3 + 1, 35, 71);
        if (tmp == "-1")
            return;
        cour_cur->TeacherName = tmp;
        menu[2] = "Teacher Name: " + cour_cur->TeacherName;
        break;
    case 3:
        tmp = Limit_Input(50 + 4, 9 + cur * 3 + 1, 1, 71);
        while (tmp[0] < '0' || tmp[0] > '4')
        {
            if (tmp == "-1")
                return;
            Message_Warning("Invalid credit format or exceed the credits limit (0-4)!", "Error");
            TextColor(63);
            goToXY(50 + 4, 9 + cur * 3 + 1);
            cout << " ";
            tmp = Limit_Input(50 + 4, 9 + cur * 3 + 1, 1, 71);
        }
        cour_cur->Credits = stoi(tmp);
        menu[3] = "Number of credits: " + to_string(cour_cur->Credits);
        break;
    case 4:
        tmp = Limit_Input(50 + 4, 9 + cur * 3 + 1, 3, 71);
        if (tmp == "-1")
            return;
        while (!isStringDigits(tmp))
        {
            Message_Warning("Invalid max student format!", "Error");
            TextColor(63);
            goToXY(50 + 4, 9 + cur * 3 + 1);
            cout << "   ";
            tmp = Limit_Input(50 + 4, 9 + cur * 3 + 1, 3, 71);
            if (tmp == "-1")
                return;
        }
        cour_cur->maxStudents = stoi(tmp);
        menu[4] = "Maximum of students: " + to_string(cour_cur->maxStudents);
        break;
    case 5:
        tmp = Limit_Input(50 + 4, 9 + cur * 3 + 1, 3, 71);
        if (tmp == "-1")
            return;
        cour_cur->Room = tmp;
        menu[5] = "Room: " + cour_cur->Room;
        break;
    case 6:
        tmp = Limit_Input(50 + 4, 9 + cur * 3 + 1, 3, 71);
        while (!isDay(tmp))
        {
            if (tmp == "-1")
                return;
            Message_Warning("Invalid day!\n(MON/TUE/WED/THU/FRI/SAT/SUN)", "Notice");
            goToXY(50, 9 + cur * 3 + 1);
            cout << "                                                  ";
            tmp = Limit_Input(50 + 4, 9 + cur * 3 + 1, 3, 71);
        }
        cour_cur->Day = tmp;
        menu[6] = "Teaching day: " + cour_cur->Day;
        break;
    case 7:
        tmp = Limit_Input(50 + 4, 9 + cur * 3 + 1, 2, 71);
        while (!isSession(tmp))
        {
            if (tmp == "-1")
                return;
            Message_Warning("Invalid session!\n(S1/S2/S3/S4)", "Notice");
            goToXY(50, 9 + cur * 3 + 1);
            cout << "                                                  ";
            tmp = Limit_Input(50 + 4, 9 + cur * 3 + 1, 2, 71);
        }
        cour_cur->Session = tmp;
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
    if (course_id == "-1")
        return;

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
