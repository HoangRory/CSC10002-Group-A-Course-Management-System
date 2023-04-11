#include "../Header/Semester.h"
#include "../Header/Year.h"
#include "../Header/Utility.h"

// todo Alternate to add more semesters at once
//! Adding semester 1 include in adding a year
Semester *AddSemester(Year *yearHead)
{
    int Y, N;
    // Get the year and semester
    cout << "School year: ";
    cin >> Y;
    cout << "No. semester (1,2,3): ";
    cin >> N;

    Year *year_cur = yearHead;
    while (year_cur && year_cur->yearStart != Y) // Move the current to the exact year
        year_cur = year_cur->next;
    if (!year_cur) // Loop again the function if null
    {
        cout << "Year not found! Enter again: ";
        return AddSemester(yearHead);
    }

    Semester *sem_cur = year_cur->NoSemester;
    Semester *prev = sem_cur;
    while (sem_cur)
    {
        if (sem_cur->No == N) // If already had, ask to modify
        {
            cout << "*** Already has this semester, modify it? (Y/N) ***\n==> ";
            char check;
            cin >> check;

            while (check != 'Y' && check != 'y' && check != 'N' && check != 'n')
            {
                cout << "Invalid input! Enter again: ";
                cin >> check;
            }
            if (check == 'Y' || check == 'y')
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
    cout << "Starting date (dd/mm/yyyy): "; // Get the date and ensure its format
    cin >> sem_cur->startDate;
    cout << "Ending date (dd/mm/yyyy): ";
    cin >> sem_cur->endDate;

    string out_year = to_string(Y) + '_' + to_string(Y + 1);
    string outPath = "..\\Data_file\\" + out_year + "\\smt" + to_string(N);
    string tmp_sys = "mkdir " + outPath;
    // Create a folder to store its information
    const char *cstr_path = tmp_sys.c_str();
    system(cstr_path);
    system("cls");

    return sem_cur;
}

//! Write a course modification function here!!!
Course *AddNewCourse(Semester *semCurrent, Year* yearHead)
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
                cout << "*** Already has this course, modify it? (Y/N) ***\n==> ";
                char check;
                cin >> check;
                while (check != 'Y' && check != 'y' && check != 'N' && check != 'n')
                {
                    cout << "Please enter Y or N: ";
                    cin >> check;
                }
                if (check == 'Y' || check == 'y')
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
void AddingCourse(Semester *semCurrent, Year* yearHead)
{
    if (!semCurrent)
        return;
    Course *courseCurrent = AddNewCourse(semCurrent, yearHead);

    int choice = 1;
    bool stop = false;
    string menu[3]; // All allow actions
    menu[0] = "\nMethod to import student to the course:\n";
    menu[1] = "- Import student from file\n";
    menu[2] = "- Add student by hand     \n";
    system("cls");
    for (int i = 0; i < 3; i++)
    {
        if (i == choice) // Change color according to the current cursor
        {
            TextColor(LIGHT_YELLOW);
            cout << menu[i];
            TextColor(WHITE);
        }
        else
            cout << menu[i];
    }

    TextColor(LIGHT_GREEN);
    cout << "\n\nUsing your arrow on the keyboard to move the choice and enter to select!\n\n";
    TextColor(WHITE);

    ShowConsoleCursor(false); // Disable the cursor
    while (!stop)
    {
        if (_kbhit()) // get the input from arrow buttons
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
            cout << "\n\nUsing your arrow on the keyboard to move the choice and enter to select!\n\n";
            TextColor(WHITE);
        }
    }
    ShowConsoleCursor(true);

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

    cout << "\nDo you want to add a new course to this semester? (Y/N) ";
    char ch;
    cin >> ch;
    while (ch != 'Y' && ch != 'y' && ch != 'N' && ch != 'n')
    {
        cout << "Invalid respond, enter again: ";
        cin >> ch;
    }

    if (ch == 'Y' || ch == 'y')
        AddingCourse(semCurrent, yearHead);
    return;
}

//? Run to begin the new semester
void Interface_New_Sem(Year *yearHead)
{
    Semester *semCurrent = AddSemester(yearHead); // New semester and return the default for next actions
    AddingCourse(semCurrent, yearHead);

    cout << "Do you want to add another semester? (Y/N) ";
    char ch;
    cin >> ch;
    while (ch != 'Y' && ch != 'y' && ch != 'N' && ch != 'n')
    {
        cout << "Invalid respond, enter again: ";
        cin >> ch;
    }
    if (ch == 'Y' || ch == 'y')
        Interface_New_Sem(yearHead);
    return;
}