#include "../Header/Utility.h"
#include "../Header/Semester.h"
#include "../Header/Year.h"
#include "../Header/Help.h"

//? Adding a course
Course *AddNewCourse(Semester *semCurrent, Year *yearHead)
{
    system("cls");
    Render_NewInfo(50, 3);

    TextColor(14);
    goToXY(52, 9);
    cout << "Course ID";
    goToXY(52, 14);
    cout << "Course name";
    goToXY(52, 19);
    cout << "Teacher name";

    goToXY(51, 25);
    cout << "Credit";
    goToXY(73, 25);
    cout << "Max student";
    goToXY(51, 29);
    cout << "Room";
    goToXY(66, 29);
    cout << "Day";
    goToXY(80, 29);
    cout << "Session";

    TextColor(63);
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            goToXY(50, 10 + 5 * i + j);
            cout << "                                              ";
        }
        goToXY(59, 24 + i);
        cout << "          "; // Credit
        goToXY(86, 24 + i);
        cout << "          "; // Max stud

        goToXY(57, 28 + i);
        cout << "       "; // Room
        goToXY(71, 28 + i);
        cout << "       "; // Day
        goToXY(89, 28 + i);
        cout << "       "; // Session
    }

    string tmp;
    tmp = Limit_Input(52, 11, 10, 63);
    if (tmp == "-1")
        return nullptr;
    string id = tmp;
    Course *courseCurrent, *prev = nullptr;
    if (!semCurrent->course) // Generate the head if there is not
    {
        semCurrent->course = new Course;
        courseCurrent = semCurrent->course;
    }
    else
    {
        courseCurrent = semCurrent->course;
        while (courseCurrent->next)
        {
            if (courseCurrent->CourseID == id)
            {
                // ask if they want to change its in4
                string mess = "This course already exists, do you want to modify it?";
                if (Message_YesNo(mess, "Notice"))
                    // Modify the semester
                    modifyCourse(yearHead);
                return nullptr;
            }
            courseCurrent = courseCurrent->next;
        }
        // create a new node at last pos
        prev = courseCurrent;
        courseCurrent->next = new Course;
        courseCurrent = courseCurrent->next;
        courseCurrent->prev = prev;
    }

    courseCurrent->CourseID = id;

    tmp = Limit_Input(52, 16, 30, 63);
    if (tmp == "-1")
    {
        if (courseCurrent->prev)
            courseCurrent->prev->next = nullptr;
        else
            semCurrent->course = nullptr;
        delete courseCurrent;
        return nullptr;
    }
    courseCurrent->Name = tmp;

    tmp = Limit_Input(52, 21, 30, 63);
    if (tmp == "-1")
    {
        if (courseCurrent->prev)
            courseCurrent->prev->next = nullptr;
        else
            semCurrent->course = nullptr;
        delete courseCurrent;
        return nullptr;
    }
    courseCurrent->TeacherName = tmp;

    string c = Limit_Input(64, 25, 1, 63);
    while (c[0] < '0' || c[0] > '4')
    {
        if (c == "-1")
        {
            if (courseCurrent->prev)
                courseCurrent->prev->next = nullptr;
            else
                semCurrent->course = nullptr;
            delete courseCurrent;
            return nullptr;
        }
        Message_Warning("Invalid credit format or exceed the credits limit (0-4)!", "Error");
        TextColor(63);
        goToXY(59, 25);
        cout << "          "; // Credit
        c = Limit_Input(64, 25, 1, 63);
    }
    courseCurrent->Credits = stoi(c);

    tmp = Limit_Input(86, 25, 3, 63);
    if (tmp == "-1")
    {
        if (courseCurrent->prev)
            courseCurrent->prev->next = nullptr;
        else
            semCurrent->course = nullptr;
        delete courseCurrent;
        return nullptr;
    }
    while (!isStringDigits(tmp))
    {
        Message_Warning("Invalid max student format!", "Error");
        TextColor(63);
        goToXY(86, 25);
        cout << "          "; // Max stud
        tmp = Limit_Input(86, 25, 3, 63);
        if (tmp == "-1")
        {
            if (courseCurrent->prev)
                courseCurrent->prev->next = nullptr;
            else
                semCurrent->course = nullptr;
            delete courseCurrent;
            return nullptr;
        }
    }
    courseCurrent->maxStudents = stoi(tmp);

    tmp = Limit_Input(59, 29, 3, 63);
    if (tmp == "-1")
    {
        if (courseCurrent->prev)
            courseCurrent->prev->next = nullptr;
        else
            semCurrent->course = nullptr;
        delete courseCurrent;
        return nullptr;
    }
    courseCurrent->Room = tmp;

    tmp = Limit_Input(73, 29, 3, 63);
    while (!isDay(tmp))
    {
        if (tmp == "-1")
        {
            if (courseCurrent->prev)
                courseCurrent->prev->next = nullptr;
            else
                semCurrent->course = nullptr;
            delete courseCurrent;
            return nullptr;
        }
        Message_Warning("Invalid day format!\n(MON/TUE/WED/THU/FRI/SAT/SUN)", "Error");
        goToXY(71, 29);
        TextColor(63);
        cout << "       ";
        tmp = Limit_Input(73, 29, 3, 63);
    }
    courseCurrent->Day = tmp;

    tmp = Limit_Input(91, 29, 2, 63);
    while (!isSession(tmp))
    {
        if (tmp == "-1")
        {
            if (courseCurrent->prev)
                courseCurrent->prev->next = nullptr;
            else
                semCurrent->course = nullptr;
            delete courseCurrent;
            return nullptr;
        }
        Message_Warning("Invalid session format!\n(S1/S2/S3/S4)", "Error");
        goToXY(89, 29);
        TextColor(63);
        cout << "       ";
        tmp = Limit_Input(91, 29, 2, 63);
    }
    courseCurrent->Session = tmp;

    return courseCurrent;
}

//? Add student using file
void ImportStudentFromFile(Course *courseCurrent)
{
    string str = courseCurrent->Name;
    int i = 0;
    while (i < str.size()) // Shortten the name for the path in system file
    {
        if (i == 0 && str[i] > 90)
            str[i] -= 32;
        if (str[i] == ' ')
            if (str[i + 1] > 90)
                str[i + 1] -= 32;
        if (str[i] >= 97 || str[i] == ' ')
            str.erase(str.begin() + i);
        else
            i++;
    }
    string studList = "../Data_file/New_Enrolled_Student/" + str + ".txt";
    string mess = "Put data in the New_Enrolled_Student folder\nName it with format: chữ cái đầu in hoa.txt\nOK to continue when finish";
    Message_Warning(mess, "Notice");

    // Open the file that has been put is the folder
    ifstream ifs(studList);
    if (!ifs)
        return;
    string tmp;
    StudentCourse *studCourse;

    int cnt = 0; // count the number of student
    if (ifs >> tmp)
    {
        courseCurrent->studentCourse = new StudentCourse;
        studCourse = courseCurrent->studentCourse;
        studCourse->ID = tmp;
        cnt++;
        while (ifs >> tmp) // read til the end
        {
            if (tmp == "\n")
                break;
            studCourse->next = new StudentCourse;
            StudentCourse *tmpStud = studCourse;
            studCourse = studCourse->next;
            studCourse->prev = tmpStud;
            studCourse->ID = tmp;
            cnt++;
        }
    }
    courseCurrent->numStudents = cnt;
    ifs.close();
}

//? Add student by hand inputing one by one
void AddStudentByHand(Course *courseCurrent)
{
    // cout << "Enter the student ID one by one! (Enter -1 to stop)\n\n";

    StudentCourse *studCourse = courseCurrent->studentCourse;
    goToXY(60, 17);
    cout << "Enter student ID (ESC to stop)";
    int cnt = 0, i = 0;
    string line;
    while (1)
    {
        TextColor(63);
        goToXY(58, 19 + i);
        cout << "                             ";
        goToXY(65, 19 + i);
        line = Limit_Input(65, 19 + i, 8, 63);

        if (line == "-1")
            break;
        if (line.size() != 8)
        {
            if (Message_YesNo("Invalid ID format!", "Error"))
                continue;
            else
                break;
        }
        i++;
        if (!studCourse)
        {
            studCourse = new StudentCourse;
            courseCurrent->studentCourse = studCourse;
        }
        else
        {
            studCourse->next = new StudentCourse;
            studCourse->next->prev = studCourse;
            studCourse = studCourse->next;
        }
        studCourse->ID = line;
        cnt++;
    }
    courseCurrent->numStudents = cnt;

    Message_Warning("Done adding new student to course!", "Success");
    return;
}
//? Generate the option to add student

void AddingCourse(Semester *semCurrent, Year *yearHead)
{
    if (!semCurrent)
        return;
    Course *courseCurrent = AddNewCourse(semCurrent, yearHead);
    if (!courseCurrent)
        return;

    vector<string> menu;
    system("cls");
    Render_Class(50, 2);
    //! add a title
    menu.push_back("Import student from file");
    menu.push_back("Add student by hand");
    menu.push_back("Back");

    int choice = Draw_XY(menu, 55, 12, 3, 30, 63);

    switch (choice) // Access according to the choice
    {
    case 0:
        Message_Warning("Importing student from file!", "Notice");
        ImportStudentFromFile(courseCurrent);
        break;
    case 1:
        Message_Warning("Adding student by hand!", "Notice");
        AddStudentByHand(courseCurrent);
        break;
    case 2:
        return;
    }

    string mess = "Do you want to add another course to this semester?";
    if (Message_YesNo(mess, "Notice"))
        AddingCourse(semCurrent, yearHead);
    return;
}
