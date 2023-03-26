#include "proto.h"
#include "Task6_13.h"
#include "Login.cpp"

//! Run after the Login file to collect the ROLE
Semester *semHead = nullptr;
Semester *cur = nullptr;

int yr = 2022;
string strYear = to_string(yr) + '_' + to_string(yr + 1);
string smtPath = "Data_file\\" + strYear + "\\smt";
int smt = 1;
int num_smt = 2;

void Read_SMT()
{
    string path = smtPath + to_string(smt) + "\\in4smt.txt";
    smt++;
    // cout << path;
    ifstream ifs(path);
    Semester *sem_cur;
    while (!ifs.eof())
    {
        if (!semHead)
        {
            semHead = new Semester;
            sem_cur = semHead;
        }
        else
        {
            sem_cur->next = new Semester;
            Semester *tmp = sem_cur;
            sem_cur = sem_cur->next;
            sem_cur->prev = tmp;
        }

        sem_cur->No = (smt > 4 ? 2 : smt) - 1;
        sem_cur->Year = yr;
        ifs >> sem_cur->startDate >> sem_cur->endDate;

        Course *tmp_C;
        while (!ifs.eof())
        {
            if (!sem_cur->course)
            {
                sem_cur->course = new Course;
                tmp_C = sem_cur->course;
            }
            else
            {
                tmp_C->next = new Course;
                Course *temp = tmp_C;
                tmp_C = tmp_C->next;
                tmp_C->prev = temp;
            }
            ifs.ignore();
            getline(ifs, tmp_C->Name);
            ifs >> tmp_C->CourseID >> tmp_C->Credits >> tmp_C->maxStudents >> tmp_C->numStudents >> tmp_C->Room;
            ifs.ignore();
            getline(ifs, tmp_C->TeacherName);
            ifs >> tmp_C->Day >> tmp_C->Session;

            StudentCourse *tmp_S;
            string ID;
            while (ifs >> ID)
            {
                if (ID == "-1")
                    break;
                if (!tmp_C->studentCourse)
                {
                    tmp_C->studentCourse = new StudentCourse;
                    tmp_S = tmp_C->studentCourse;
                }
                else
                {
                    tmp_S->next = new StudentCourse;
                    StudentCourse *temp = tmp_S;
                    tmp_S = tmp_S->next;
                    tmp_S->prev = temp;
                }
                tmp_S->ID = ID;
            }
        }
    }
    path = "";
}
void Read_multi_SMT()
{
    for (int time = 0; time < num_smt; time++)
        Read_SMT();
}

//! Need to be more efficient (sync only at the empty studentCourse that has ID but no name)
void SyncFullName()
{
    Semester *sem_cur = semHead;
    while (sem_cur)
    {
        Course *cse = sem_cur->course;
        while (cse)
        {
            StudentCourse *stcse = cse->studentCourse;
            while (stcse)
            {
                Account *acc_cur = accHead;
                while (acc_cur)
                {
                    if (acc_cur->username == stcse->ID)
                    {
                        stcse->FullName = acc_cur->lastName + ' ' + acc_cur->firstName;
                        break;
                    }
                    acc_cur = acc_cur->next;
                }
                stcse = stcse->next;
            }
            cse = cse->next;
        }
        sem_cur = sem_cur->next;
    }
}

void DeleteStudent(StudentCourse *stud_head)
{
    if (!stud_head)
        return;
    DeleteStudent(stud_head->next);
    delete stud_head;
    stud_head = nullptr;
}
void DeleteCourse(Course *course_head)
{
    if (!course_head)
        return;
    DeleteCourse(course_head->next);
    DeleteStudent(course_head->studentCourse);
    delete course_head;
    course_head = nullptr;
}
void DeleteSMT()
{
    if (!semHead)
        return;
    DeleteCourse(semHead->course);
    Semester *tmp = semHead->next;
    delete semHead;
    semHead = tmp;
    DeleteSMT();
    semHead = nullptr;
}

void OutStudent(StudentCourse *stud_head, ofstream &ofs)
{
    if (!stud_head)
        return;
    while (stud_head)
    {
        ofs << stud_head->ID << '\n';
        stud_head = stud_head->next;
    }
    ofs << -1 << '\n';
    return;
}
void OutCourse(Course *course_head, ofstream &ofs)
{
    if (!course_head)
        return;
    while (course_head)
    {
        ofs << course_head->Name << '\n'
            << course_head->CourseID << ' ' << course_head->Credits << ' '
            << course_head->maxStudents << ' ' << course_head->numStudents
            << ' ' << course_head->Room << '\n'
            << course_head->TeacherName
            << '\n'
            << course_head->Day << '\n'
            << course_head->Session << '\n';
        OutStudent(course_head->studentCourse, ofs);
        course_head = course_head->next;
    }
}
void Output()
{
    if (!semHead)
        return;
    ofstream ofs("TestOnly.txt");
    if (!ofs)
        return;
    Semester *sem_cur = semHead;
    while (sem_cur)
    {
        ofs << sem_cur->No << '\n';
        ofs << sem_cur->startDate << ' ' << sem_cur->endDate << '\n';
        OutCourse(sem_cur->course, ofs);
        sem_cur = sem_cur->next;
    }
    ofs.close();
}

void AddSemester()
{
    cur = semHead;
    cout << "School year: ";
    unsigned int Y;
    unsigned short N;
    cin >> Y;
    cout << "No. semester (1,2,3): ";
    cin >> N;
    Semester *prev = nullptr;
    while (cur)
    {
        if (cur->Year == Y && cur->No == N)
        {
            std::cout << "Already has this semester, modify it?";
            // ModifySem();
            break;
        }
        prev = cur;
        cur = cur->next;
    }
    cur = new Semester;
    cur->prev = prev;
    cur->No = N;
    cur->Year = Y;
    cout << "Starting date (dd/mm/yyyy): ";
    cin >> cur->startDate;
    cout << "Ending date (dd/mm/yyyy): ";
    cin >> cur->endDate;
}

void AddCourse(Semester *&sem)
{
    cout << "Enter the course ID: ";
    string id;
    cin >> id;
    cur = semHead;
    while (cur)
    {
        Course *cour = cur->course;
        while (cour)
        {
            if (cour->CourseID == id)
            {
                cout << "Already have this course, please enter a new course!";
                AddCourse(sem);
                return;
            }
            cour = cour->next;
        }
        cur = cur->next;
    }
    sem->course = new Course;
    Course *new_course = sem->course;
    new_course->CourseID = id;
    cout << "Course name: ";
    cin >> new_course->Name;
    //! Class name?????
    cout << "Enter the teacher name: ";
    cin >> new_course->TeacherName;
    cout << "Enter the number of credits: ";
    cin >> new_course->Credits;
    cout << "Enter the maximum of students: ";
    cin >> new_course->maxStudents;
    cout << "Note: The course will be taught only one session per week!!!";
    cout << "Choose the day of week the course will be taught\n(MON/TUE/WED/THU/FRI/SAT): ";
    cin >> new_course->Day;
    cout << "Choose the the session time of the course\nS1-(07:30)\tS2-(09:30)\tS3-(13:30)\tS4-(15:30) : ";
    cin >> new_course->Session;
    AddStudent(new_course->studentCourse, sem);
}

void AddStudent(Course *&new_course, Semester *sem)
{
    string yearPath = to_string(sem->Year) + '_' + to_string(sem->Year + 1);
    string studList = "Data_file\\" + yearPath + "\\smt" + to_string(sem->No) + "\\";

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
    studList += str + ".csv";

    ifstream ifs(studList);
    if (!ifs)
        return;
    string tmp;
    StudentCourse *studCourse;

    if (ifs >> tmp)
    {
        new_course->studentCourse = new StudentCourse;
        studCourse = new_course->studentCourse;
        studCourse->ID = tmp;
    }
    while (ifs >> tmp)
    {
        studCourse->next = new StudentCourse;
        studCourse = studCourse->next;
        studCourse->ID = tmp;
    }
    SyncFullName();

    ifs.close();
}

int main()
{
    system("cls");
    ReadAccount();
    Read_multi_SMT();
    SyncFullName();
    // LoggingIn();

    // AddSemester();
    // Output();

    DelAccount();
    DeleteSMT();

    return 0;
}