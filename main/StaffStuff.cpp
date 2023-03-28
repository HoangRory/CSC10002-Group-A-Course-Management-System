#include "proto.h"
#include "Task6_13.h"
#include "Login.cpp"

//! Run after the Login file to collect the ROLE
Semester *semHead = nullptr;
Semester *cur = nullptr;

int yr = 2022;
// string smtPath = "Data_file\\" + strYear + "\\smt";
int num_smt = 3, num_year = 1;

//todo make it more efficient
void Read_SMT(int y, int smt)
{
    string in_year = to_string(y) + '_' + to_string(y + 1);
    string path = "Data_file\\" + in_year + "\\smt" + to_string(smt) + "\\in4smt.txt";

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
    for (int y = yr; y < yr + num_year; y++)
        for (int smt = 1; smt < num_smt; smt++)
            Read_SMT(y, smt);
}

//todo Need to be more efficient (sync only at the empty studentCourse that has ID but no name)
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
                    if (stcse->FullName != "")
                        break;
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
    ofs << -1;
    return;
}
void OutCourse(Course *course_head, ofstream &ofs)
{
    if (!course_head)
        return;
    while (course_head)
    {
        ofs << '\n';
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
    Semester *sem_cur = semHead;

    while (sem_cur)
    {
        string out_year = to_string(sem_cur->Year) + '_' + to_string(sem_cur->Year + 1);
        string outPath = "Data_file\\" + out_year + "\\smt" + to_string(sem_cur->No) + "\\";
        outPath += "in4smt.txt";
        // string tmp_sys = "mkdir " + outPath;
        // const char *cstr_path = tmp_sys.c_str();
        // system(cstr_path);

        ofstream ofs(outPath);
        if (!ofs)
            return;
        // ofs << sem_cur->No << '\n';
        ofs << sem_cur->startDate << ' ' << sem_cur->endDate;
        OutCourse(sem_cur->course, ofs);
        sem_cur = sem_cur->next;
        ofs.close();
    }
}

//! Alternate to add more semesters
//! Modify the semester
void AddSemester()
{
    Semester *sem_head = semHead;
    Semester *sem_cur = semHead;

    unsigned int Y;
    unsigned short N;
    cout << "School year: ";
    cin >> Y;
    cout << "No. semester (1,2,3): ";
    cin >> N;
    Semester *prev = nullptr;
    while (sem_cur)
    {
        if (sem_cur->Year == Y && sem_cur->No == N)
        {
            std::cout << "Already has this semester, modify it?";
            // ModifySem();
            return;
        }
        prev = sem_cur;
        if (!sem_cur->next)
            break;
        sem_cur = sem_cur->next;
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
    // outPath += "in4smt.txt";
    string tmp_sys = "mkdir " + outPath;
    const char *cstr_path = tmp_sys.c_str();
    system(cstr_path);
    AddCourse(sem_cur);
}

//! Has the modify function here!!!
void AddCourse(Semester *&sem)
{
    cout << "\nEnter the course ID: ";
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
                cout << "Already have this course, please enter a new course or modify it!";
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
    // string yearPath = to_string(sem->Year) + '_' + to_string(sem->Year + 1);
    // string studList = "Data_file\\" + yearPath + "\\smt" + to_string(sem->No) + "\\";

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
    string studList = str + ".csv";

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
    SyncFullName();

    ifs.close();
}

void viewCourse()
{
    Semester *sem_cur = semHead;
    cout << "List of courses: \n";
    for (int i = 0; i < 100; i++)
        cout << '-';

    while (sem_cur)
    {
        Course *cour = sem_cur->course;

        cout << "\nSemester " << sem_cur->No << " - " << sem_cur->Year << " - " << sem_cur->Year + 1 << '\n';

        while (cour)
        {
            cout << '\n';
            cout << "Course ID: " << cour->CourseID;
            cout << "\nCourse name: " << cour->Name;
            cout << "\nTeacher name: " << cour->TeacherName << "\n";

            cour = cour->next;
        }
        sem_cur = sem_cur->next;
    }
    for (int i = 0; i < 100; i++)
        cout << '-';
}

void modifyCourse(string id)
{
    Semester *sem_cur = semHead;
    Course *cour_cur;

    while (sem_cur)
    {
        cour_cur = sem_cur->course;

        while (cour_cur)
        {
            if (cour_cur->CourseID == id)
            {
                cout << "New course name: ";
                cin.ignore();
                getline(cin, cour_cur->Name);
                cout << "\nEnter the new teacher name: ";
                getline(cin, cour_cur->TeacherName);
                cout << "\nEnter the new number of credits: ";
                cin >> cour_cur->Credits;

                cout << "\nEnter the new maximum of students: ";
                cin >> cour_cur->maxStudents;

                cout << "\nChoose the room of the course: ";
                cin >> cour_cur->Room;

                cout << "Teaching day\n(MON/TUE/WED/THU/FRI/SAT): ";
                cin >> cour_cur->Day;

                cout << "\nCourse section\nS1-(07:30)\tS2-(09:30)\tS3-(13:30)\tS4-(15:30) : ";
                cin >> cour_cur->Session;

                cout << "Course has been updated\n";
                return;
            }
            cour_cur = cour_cur->next;
        }
        sem_cur = sem_cur->next;
    }
}

void modifySemester(int year, int sem)
{
    Semester *sem_cur = semHead;
    Course *cour_cur;

    while (sem_cur)
    {
        if (sem_cur->Year == year && sem_cur->No == sem)
        {
            // cout << "New semester: ";
            // cin >> sem_cur->No;

            // cout << "New year: ";
            // cin >> sem_cur->Year;

            cout << "New semester start date: ";
            cin >> sem_cur->startDate;

            cout << "New semester end date: ";
            cin >> sem_cur->endDate;

            cout << "Semster has been updated\n";
            return;
        }
        sem_cur = sem_cur->next;
    }
}

void addStudent(string id)
{
    Semester *sem_cur = semHead;
    Course *cour_cur;
    StudentCourse *stud_cur, *stud_prev;

    while (sem_cur)
    {
        cour_cur = sem_cur->course;

        while (cour_cur)
        {
            if (cour_cur->CourseID == id)
            {
                cout << "Enter student ID: ";
                string ID;
                cin >> ID;
                stud_cur = cour_cur->studentCourse;
                stud_prev = stud_cur;

                while (stud_cur)
                {
                    if (stud_cur->ID == ID)
                    {
                        cout << "Student already exists\n";
                        return;
                    }
                    stud_prev = stud_cur;
                    stud_cur = stud_cur->next;
                }
                stud_prev->next = new StudentCourse;
                stud_prev->next->ID = ID;
                cour_cur->numStudents++;
                cout << "Student has been added\n";
                return;
            }
            cour_cur = cour_cur->next;
        }
        sem_cur = sem_cur->next;
    }
}
void removeStudent(string id)
{
    Semester *sem_cur = semHead;
    Course *cour_cur;
    StudentCourse *stud_cur, *stud_prev;

    while (sem_cur)
    {
        cour_cur = sem_cur->course;

        while (cour_cur)
        {
            if (cour_cur->CourseID == id)
            {
                cout << "Enter student ID: ";
                string ID;
                cin >> ID;
                stud_cur = cour_cur->studentCourse;
                stud_prev = stud_cur;

                while (stud_cur)
                {
                    if (stud_cur->ID == ID)
                    {
                        if (stud_cur == cour_cur->studentCourse)
                            cour_cur->studentCourse = stud_cur->next;
                        else
                            stud_prev->next = stud_cur->next;
                        cour_cur->numStudents--;
                        cout << "Student has been removed\n";
                        return;
                    }
                    stud_prev = stud_cur;
                    stud_cur = stud_cur->next;
                }
                cout << "Student does not exist\n";
                return;
            }
            cour_cur = cour_cur->next;
        }
        sem_cur = sem_cur->next;
    }
}
void addRemoveStudent(string id)
{
    cout << "1. Add student\n2. Remove student\n";
    int choice;
    cin >> choice;
    switch (choice)
    {
    case 1:
        addStudent(id);
        break;
    case 2:
        removeStudent(id);
        break;
    }
}
void deleteCourse(string id)
{
    Semester *sem_cur = semHead;
    Course *cour_cur, *cour_prev;

    while (sem_cur)
    {
        cour_cur = sem_cur->course;
        cour_prev = cour_cur;

        while (cour_cur)
        {
            if (cour_cur->CourseID == id)
            {
                cout << cour_cur->Name << " has been deleted\n";
                if (cour_cur == sem_cur->course)
                    sem_cur->course = cour_cur->next;
                else
                    cour_prev->next = cour_cur->next;
                delete cour_cur;
                return;
            }
            cour_prev = cour_cur;
            cour_cur = cour_cur->next;
        }
        sem_cur = sem_cur->next;
    }
    cout << "\nXXX Cannot find course XXX\n";
}

void initModify()
{
    for (int i = 0; i < 100; i++)
        cout << '-';
    cout << "\nOptions:\n";
    cout << "1. Modify semester\n";
    cout << "2. Modify course\n";
    cout << "3. Delete a course\n";
    cout << "4. Add or remove a student\n";
    cout << "5. Quit\n";

    int opt;
    cout << "\n==> Your option: ";
    cin >> opt;
    string id;
    switch (opt)
    {
    case 1:
        int sem, year;
        cout << "Choose the year: ";
        cin >> year;
        cout << "Choose the semester: ";
        cin >> sem;
        modifySemester(year, sem);
        break;
    case 2:
        cout << "Choose the course ID: ";
        cin >> id;
        modifyCourse(id);
        break;
    case 3:
        cout << "Choose the course ID: ";
        cin >> id;
        deleteCourse(id);
        break;
    case 4:
        cout << "Choose the course ID: ";
        cin >> id;
        addRemoveStudent(id);
        break;
    case 5:
        cout << "Goodbye!";
        return;
    }
    initModify();
}

int main()
{
    // system("cls");
    // ReadAccount();
    Read_multi_SMT();
    // SyncFullName();
    // LoggingIn();
    Semester *tmp = semHead;
    // AddSemester();
    initModify();
    // viewCourse();
    Output();

    // DelAccount();
    DeleteSMT();

    return 0;
}