#include "../Header/Semester.h"

// todo Alternate to add more semesters at once
//! Adding semester 1 include in adding a year
Semester *AddSemester(Semester *semHead)
{
    Semester *sem_head = semHead;
    Semester *sem_cur = semHead;

    int Y, N;
    cout << "School year: ";
    cin >> Y;
    cout << "No. semester (1,2,3): ";
    cin >> N;
    Semester *prev = nullptr;

    while (sem_cur)
    {
        if (sem_cur->Year == Y && sem_cur->No == N)
        {
            std::cout << "*** Already has this semester, modify it? (Y/N) ***";
            char check;
            cin >> check;
            if (check == 'Y' || check == 'y')
                modifySemester(semHead, Y, N);
            return;
        }
        prev = sem_cur;
        if (!sem_cur->next)
            break;
        sem_cur = sem_cur->next;
    }

    if (N == 1)
    {
        //! Add in a new year
    }

    sem_cur->next = new Semester;
    sem_cur = sem_cur->next;
    sem_cur->prev = prev;
    sem_cur->No = N;
    sem_cur->Year = Y;
    cout << "Starting date (dd/mm/yyyy): ";
    cin >> sem_cur->startDate;
    cout << "Ending date (dd/mm/yyyy): ";
    cin >> sem_cur->endDate;

    string out_year = to_string(Y) + '_' + to_string(Y + 1);
    string outPath = "Data_file\\" + out_year + "\\smt" + to_string(N);
    string tmp_sys = "mkdir " + outPath;
    const char *cstr_path = tmp_sys.c_str();
    system(cstr_path);
    // AddCourse(semHead, sem_cur);

    // return sem_cur;
}

//! Write a course modification function here!!!
Course *AddCourse(Semester *semCurrent)
{
    cout << "\nEnter the course ID: ";
    string id;
    cin >> id;
    Course *courseCurrent = semCurrent, *prev = nullptr;
    while (courseCurrent)
    {
        if (courseCurrent->CourseID == id)
        {
            cout << "*** Already has this course, modify it? (Y/N) ***";
            char check;
            cin >> check;
            while (check != 'Y' && check != 'y' && check != 'N' && check != 'n')
            {
                cout << "Please enter Y or N: ";
                cin >> check;
            }
            if (check == 'Y' || check == 'y')
                modifyCourse(semCurrent, id);
            return;
        }
        prev = courseCurrent;
        courseCurrent = courseCurrent->next;
    }
    prev->next = new Course;
    courseCurrent = prev->next;
    courseCurrent->prev = prev;

    courseCurrent->CourseID = id;

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

    cout << "\nChoose the the session time of the course\nS1-(07:30)\tS2-(09:30)\tS3-(13:30)\tS4-(15:30) : ";
    cin >> courseCurrent->Session;

    return courseCurrent;
}

void ImportStudentFromFile(Course *courseCurrent)
{
    string str = courseCurrent->Name;
    int i = 0;
    while (i < str.size())
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
    string studList = "../Data_file/New_Enrolled_Student/" + str + ".csv";

    ifstream ifs(studList);
    if (!ifs)
        return;
    string tmp;
    StudentCourse *studCourse;

    int cnt = 0;
    if (ifs >> tmp)
    {
        courseCurrent->studentCourse = new StudentCourse;
        studCourse = courseCurrent->studentCourse;
        studCourse->ID = tmp;
        cnt++;
    }
    while (ifs >> tmp && tmp != '\n')
    {
        studCourse->next = new StudentCourse;
        StudentCourse *tmpStud = studCourse;
        studCourse = studCourse->next;
        studCourse->prev = tmpStud;
        studCourse->ID = tmp;
        cnt++;
    }
    courseCurrent->numStudents = cnt;
    ifs.close();
}

void AddStudentByHand(Course *courseCurrent)
{
    cout << "Enter the student ID one by one! (Enter -1 to stop)\n\n";

    string id;
    StudentCourse *studCourse;
    int cnt = 0;
    if (cin >> id && id != "-1")
    {
        courseCurrent->studentCourse = new StudentCourse;
        studCourse = courseCurrent->studentCourse;
        studCourse->ID = id;
        cnt++;
    }
    while (cin >> id && id != "-1")
    {
        studCourse->next = new StudentCourse;
        StudentCourse *tmpStud = studCourse;

        studCourse = studCourse->next;
        studCourse->prev = tmpStud;

        studCourse->ID = id;
        cnt++;
    }
    courseCurrent->numStudents = cnt;

    cout << "\nFinishing adding new student!\n";
}

void AddingCourse(Semester *semCurrent)
{
    Course *courseCurrent = AddCourse(semCurrent);
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

    system("cls");
    SetConsoleTextAttribute(h, RED);
    cout << "\nUsing your arrow on the keyboard to move the choice and enter to select!\n\n";
    SetConsoleTextAttribute(h, WHITE);

    cout << "Choose a method to import students: \n";
    SetConsoleTextAttribute(h, YELLOW);

    cout << "From a file\n";
    SetConsoleTextAttribute(h, WHITE);
    cout << "By typing one by one\n";

    int choice = 1;
    bool stop = false;
    while (!stop)
    {
        if (_kbhit())
        {
            switch (_getch())
            {
            case VK_UP:
                if (choice > 1)
                    choice--;
                break;
            case VK_DOWN:
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
            SetConsoleTextAttribute(h, RED);
            cout << "\nUsing your arrow on the keyboard to move the choice and enter to select!\n\n";
            SetConsoleTextAttribute(h, WHITE);
            cout << "Choose a method to import students: \n";

            switch (choice)
            {
            case 1:
                SetConsoleTextAttribute(h, YELLOW);
                cout << "From a file\n";

                SetConsoleTextAttribute(h, WHITE);
                cout << "By typing one by one\n";
                break;

            case 2:
                cout << "From a file\n";
                SetConsoleTextAttribute(h, YELLOW);
                cout << "By typing one by one\n";
                SetConsoleTextAttribute(h, WHITE);
                break;
            }
        }
    }
    switch (choice)
    {
    case 1:
        cout << "You chose to import student from a file!\n";
        ImportStudent(courseCurrent);
        break;
    case 2:
        cout << "You're adding student by hand!\n";
        AddStudentByHand(courseCurrent);
        break;
    }

    cout << "\nDo you want to add a new course to this semester? (Y/N)";
    char ch;
    cin >> ch;
    while (ch != 'Y' || ch != 'y' || ch != 'N' || ch != 'n')
    {
        cout << "Invalid respond, enter again!";
        cin >> ch;
    }

    if (ch == 'Y' || ch == 'y')
        AddingCourse(semCurrent);
    return;
}

//! when merge, change to yearHead
void Interface_New_Sem(Semester *&semHead)
{
    Semester *semCurrent = AddSemester(semHead);
    AddingCourse(semCurrent);
    //? Add another semester???
}