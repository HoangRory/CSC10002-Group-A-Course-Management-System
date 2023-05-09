#include "../Header/Utility.h"
#include "../Header/Semester.h"
#include "../Header/Year.h"
#include "../Header/Help.h"

// todo Alternate to add more semesters at once
//! Adding semester 1 include in adding a year
Semester *AddSemester(Year *yearHead)
{
    system("cls");
    // Print the list of year
    Year *year_cur = yearHead;
    // Get the year and semester
    year_cur = chooseYearbyOption_XY(yearHead, 60, 12, 5);
    if (!year_cur)
        return nullptr;
    string tmp;

    vector<string> small_menu;
    small_menu.push_back("1st semester");
    small_menu.push_back("2nd semester");
    small_menu.push_back("3rd semester");
    small_menu.push_back("Back");
    int N = 0;
    N = Draw_XY(small_menu, 60, 12, 20, 63) + 1;
    if (N == 4)
        return nullptr;

    Semester *sem_cur = year_cur->NoSemester;
    Semester *prev = sem_cur;
    while (sem_cur)
    {
        if (sem_cur->No == N) // If already had, ask to modify
        {
            string mess = "This semester already exists, do you want to modify it?";
            if (Message_YesNo(mess, "Notice"))
            {
                // To modify the semester
                modifySemester(yearHead);
                return nullptr;
            }
            return AddSemester(yearHead);
        }
        prev = sem_cur;
        if (!sem_cur->next)
            break;
        sem_cur = sem_cur->next;
    }

    if (!prev) // if there is no semester to begin with, create a new head
    {
        year_cur->NoSemester = new Semester;
        sem_cur = year_cur->NoSemester;
    }
    else // create a new semester at the last position
    {
        prev->next = new Semester;
        sem_cur = prev->next;
        sem_cur->prev = prev;
    }

    sem_cur->No = N;
    sem_cur->Year = year_cur->yearStart;

    system("cls");

    Render_NewYear(50, 3);
    TextColor(63);
    for (int i = 0; i < 3; i++)
    {
        goToXY(50, 13 + i);
        cout << "                                              ";
    }
    goToXY(52, 14);
    cout << "Starting date (dd/mm/yyyy): "; // Get the date and ensure its format

    tmp = Limit_Input(80, 14, 10, 63);

    while (!isValidDate(tmp))
    {
        if (tmp == "-1")
            return nullptr;
        Message_Warning("Invalid date format!\nEnter again!", "Error");
        goToXY(50, 14);
        TextColor(63);
        cout << "                                              ";
        goToXY(52, 14);
        cout << "Starting date (dd/mm/yyyy): "; // Get the date and ensure its format
        tmp = Limit_Input(80, 14, 10, 63);
    }
    sem_cur->startDate = tmp;

    TextColor(63);
    for (int i = 0; i < 3; i++)
    {
        goToXY(50, 17 + i);
        cout << "                                              ";
    }
    goToXY(52, 18);
    cout << "Ending date (dd/mm/yyyy): ";
    tmp = Limit_Input(78, 18, 10, 63);

    while (!isValidDate(sem_cur->endDate))
    {
        if (tmp == "-1")
            return nullptr;
        Message_Warning("Invalid date format!\nEnter again!", "Error");
        goToXY(50, 18);
        TextColor(63);
        cout << "                                              ";
        goToXY(52, 18);
        cout << "Starting date (dd/mm/yyyy): "; // Get the date and ensure its format
        tmp = Limit_Input(78, 18, 10, 63);
    }
    sem_cur->endDate = tmp;

    int Y = year_cur->yearStart;
    string out_year = to_string(Y) + '_' + to_string(Y + 1);
    string outPath = "..\\Data_file\\" + out_year + "\\smt" + to_string(N);
    string tmp_sys = "mkdir " + outPath;
    // Create a folder to store its information
    const char *cstr_path = tmp_sys.c_str();
    TextColor(7);
    goToXY(30, 25);
    system(cstr_path);
    goToXY(30, 25);
    cout << "                                                                    ";
    return sem_cur;
}

//! Write a course modification function here!!!
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
        return nullptr;
    courseCurrent->Name = tmp;

    tmp = Limit_Input(52, 21, 30, 63);
    if (tmp == "-1")
        return nullptr;
    courseCurrent->TeacherName = tmp;

    string c = Limit_Input(64, 25, 1, 63);
    while (c[0] < '0' || c[0] > '4')
    {
        if (c == "-1")
            return nullptr;
        Message_Warning("Invalid credit format or exceed the credits limit (0-4)!", "Error");
        TextColor(63);
        goToXY(59, 25);
        cout << "          "; // Credit
        c = Limit_Input(64, 25, 1, 63);
    }
    courseCurrent->Credits = stoi(c);

    tmp = Limit_Input(86, 25, 3, 63);
    if (tmp == "-1")
        return nullptr;
    courseCurrent->maxStudents = stoi(tmp);

    tmp = Limit_Input(59, 29, 3, 63);
    if (tmp == "-1")
        return nullptr;
    courseCurrent->Room = tmp;

    tmp = Limit_Input(73, 29, 3, 63);
    while (!isDay(tmp))
    {
        if (tmp == "-1")
            return nullptr;
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
            return nullptr;
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
    cout << "Enter student ID (-1 to stop)";
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

void New_Stuff(Year *yearHead, Account *accHead)
{
    system("cls");
    Render_NewInfo(55, 3);

    vector<string> menu;
    menu.push_back("Add a new year");
    menu.push_back("Add a new semester");
    menu.push_back("Add a new course");
    menu.push_back("Back to main menu");

    int ye;
    Year *year_cur = nullptr;

    int opt = Draw_XY(menu, 60, 12, 4, 24, 63);
    switch (opt)
    {
    case 0:
        //? Add a new year
        Interface_New_Year(yearHead, accHead);
        return;
    case 1:
        //? Add a new semester
        system("cls");
        Interface_New_Sem(yearHead);
        // Recursion back to the StaffMain function
        return;
    case 2:
        //? Add a new course
        year_cur = chooseYearbyOption_XY(yearHead, 60, 12, 5);
        if (!year_cur)
            return;

        AddingCourse(year_cur->NoSemester, yearHead);
        // Recursion back to the StaffMain function
        return;
    case 3:
        return;
    }
}

//? Run to begin the new semester
Semester *Interface_New_Sem(Year *yearHead)
{
    Semester *semCurrent = AddSemester(yearHead); // New semester and return the default for next actions
    string mess;
    if (!semCurrent)
        return Interface_New_Sem(yearHead);

    mess = "Do you want to add a course to this semester?";
    if (Message_YesNo(mess, "Notice"))
        AddingCourse(semCurrent, yearHead);

    system("cls");
    mess = "Do you want to add another semester?";
    if (Message_YesNo(mess, "Notice"))
        Interface_New_Sem(yearHead);
    return semCurrent;
}