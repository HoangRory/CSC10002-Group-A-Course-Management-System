#include "../Header/Utility.h"
#include "../Header/Semester.h"
#include "../Header/Year.h"

// todo Alternate to add more semesters at once
//! Adding semester 1 include in adding a year
Semester *AddSemester(Year *yearHead)
{
    // Print the list of year
    Year *year_cur = yearHead;
    int Y, N;
    string ye;
    // Get the year and semester
    Y = Get_CheckFormat_Existed_Year(yearHead);

    year_cur = yearHead;

    while (year_cur && year_cur->yearStart != Y) // Move the current to the exact year
        year_cur = year_cur->next;

    vector<string> small_menu;
    small_menu.push_back("1st semester");
    small_menu.push_back("2nd semester");
    small_menu.push_back("3rd semester");

    N = Draw(small_menu) + 1;

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
                modifySemester(yearHead, Y, N);
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
    sem_cur->Year = Y;
    //! Check validity
    system("cls");
    TextColor(63);
    for (int i = 0; i < 3; i++)
    {
        goToXY(50, 13 + i);
        cout << "                                              ";
    }
    goToXY(52, 14);
    cout << "Starting date (dd/mm/yyyy): "; // Get the date and ensure its format
    getline(cin, sem_cur->startDate);

    while (!isValidDate(sem_cur->startDate))
    {
        Message_Warning("Invalid date format!\nEnter again!", "Error");
        goToXY(50, 14);
        cout << "                                              ";
        goToXY(52, 14);
        cout << "Starting date (dd/mm/yyyy): "; // Get the date and ensure its format
        getline(cin, sem_cur->startDate);
    }
    for (int i = 0; i < 3; i++)
    {
        goToXY(50, 17 + i);
        cout << "                                              ";
    }
    goToXY(52, 18);
    cout << "Ending date (dd/mm/yyyy): ";
    getline(cin, sem_cur->endDate);
    
    while (!isValidDate(sem_cur->endDate))
    {
        Message_Warning("Invalid date format!\nEnter again!", "Error");
        goToXY(50, 18);
        cout << "                                              ";
        goToXY(52, 18);
        cout << "Starting date (dd/mm/yyyy): "; // Get the date and ensure its format
        getline(cin, sem_cur->endDate);
    }

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
    cout << "\nEnter the course ID: "; // Get the in4
    string id;
    cin >> id;
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
                    modifyCourse(yearHead, semCurrent->Year);
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

    // Get all the necessary in4
    cout << "\nCourse name: ";
    cin.ignore();
    getline(cin, courseCurrent->Name);

    //! Class name?????
    cout << "\nEnter the teacher name: ";
    // cin.ignore();
    getline(cin, courseCurrent->TeacherName);
    cout << "\nEnter the number of credits: ";
    cin >> courseCurrent->Credits;

    cout << "\nEnter the maximum of students: ";
    cin >> courseCurrent->maxStudents;

    cout << "\nChoose the room of the course: ";
    cin >> courseCurrent->Room;

    cout << "\nNote: The course will be taught only one session per week!!!\n";
    cout << "Choose the day of week the course will be taught\n(MON/TUE/WED/THU/FRI/SAT): ";
    cin >> courseCurrent->Day;

    cout << "\nChoose the the session time of the course\nS1-(07:30)\tS2-(09:30)\nS3-(13:30)\tS4-(15:30) : ";
    cin >> courseCurrent->Session;

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
    cout << "Enter the student ID one by one! (Enter -1 to stop)\n\n";

    string id;
    StudentCourse *studCourse;
    int cnt = 0;
    if (cin >> id)
    {
        if (id == "-1")
            return; // end the process
        courseCurrent->studentCourse = new StudentCourse;
        studCourse = courseCurrent->studentCourse;
        studCourse->ID = id;
        cnt++;
        while (cin >> id)
        {
            if (id == "-1")
                break;
            studCourse->next = new StudentCourse;
            StudentCourse *tmpStud = studCourse;

            studCourse = studCourse->next;
            studCourse->prev = tmpStud;

            studCourse->ID = id;
            cnt++;
        }
    }
    courseCurrent->numStudents = cnt;

    cout << "\nDone adding new student!\n";
}
//? Generate the option to add student
void AddingCourse(Semester *semCurrent, Year *yearHead)
{
    if (!semCurrent)
        return;
    Course *courseCurrent = AddNewCourse(semCurrent, yearHead);

    vector<string> menu;
    //! add a title
    menu.push_back("Import student from file");
    menu.push_back("Add student by hand");
    
    int choice = Draw(menu);

    switch (choice) // Access according to the choice
    {
    case 1:
        cout << "==> You chose to import student from a file!\n";
        ImportStudentFromFile(courseCurrent);
        break;
    case 2:
        cout << "==> You're adding student by hand!\n";
        AddStudentByHand(courseCurrent);
        break;
    }

    string mess = "Do you want to add another course to this semester?";
    if (Message_YesNo(mess, "Notice"))
        AddingCourse(semCurrent, yearHead);
    return;
}

//? Run to begin the new semester
Semester* Interface_New_Sem(Year *yearHead)
{
    Semester *semCurrent = AddSemester(yearHead); // New semester and return the default for next actions
    string mess;
    mess = "Do you want to add a course to this semester?";
    if (Message_YesNo(mess, "Notice"))
        AddingCourse(semCurrent, yearHead);
        
    system("cls");
    mess = "Do you want to add another semester?";
    if (Message_YesNo(mess, "Notice"))
        Interface_New_Sem(yearHead);
    return semCurrent;
}