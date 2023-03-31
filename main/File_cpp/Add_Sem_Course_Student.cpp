#include "../Header/Semester.h"

// todo Alternate to add more semesters at once
//! Adding semester 1 include in adding a year
void AddSemester(Semester *semHead)
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

    if (N == 1){
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
    AddCourse(semHead, sem_cur);
}

//! Write a course modification function here!!!
void AddCourse(Semester *semHead, Semester *&sem)
{
    cout << "\nEnter the course ID: ";
    string id;
    cin >> id;
    Semester *cur = semHead;
    while (cur)
    {
        Course *cour = cur->course;
        while (cour)
        {
            if (cour->CourseID == id)
            {
                cout << "Already have this course, please enter a new course or modify it!";
                AddCourse(semHead, sem);
                return;
            }
            cour = cour->next;
        }
        cur = cur->next;
    }
    sem->course = new Course;
    Course *new_course = sem->course;
    new_course->CourseID = id;
    cout << "\nCourse name: ";
    cin.ignore();
    getline(cin, new_course->Name);
    //! Class name?????
    cout << "\nEnter the teacher name: ";
    // cin.ignore();
    getline(cin, new_course->TeacherName);
    cout << "\nEnter the number of credits: ";
    cin >> new_course->Credits;

    cout << "\nEnter the maximum of students: ";
    cin >> new_course->maxStudents;

    cout << "\nChoose the room of the course: ";
    cin >> new_course->Room;

    cout << "\nNote: The course will be taught only one session per week!!!\n";
    cout << "Choose the day of week the course will be taught\n(MON/TUE/WED/THU/FRI/SAT): ";
    cin >> new_course->Day;
    cout << "\nChoose the the session time of the course\nS1-(07:30)\tS2-(09:30)\tS3-(13:30)\tS4-(15:30) : ";
    cin >> new_course->Session;
    AddStudent(new_course, sem);
}
void AddStudent(Course *&new_course, Semester *sem)
{
    string str = new_course->Name;
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
        new_course->studentCourse = new StudentCourse;
        studCourse = new_course->studentCourse;
        studCourse->ID = tmp;
        cnt++;
    }
    while (ifs >> tmp)
    {
        studCourse->next = new StudentCourse;
        studCourse = studCourse->next;
        studCourse->ID = tmp;
        cnt++;
    }
    new_course->numStudents = cnt;
    ifs.close();
}