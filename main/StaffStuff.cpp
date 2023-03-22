#include "proto.h"
#include "Task6_13.h"

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
    semHead->next = new Semester;
    cur = semHead->next;
    cout << "No. semester (1,2,3): ";
    cin >> cur->No;
    cout << "School year: ";
    cin >> cur->Year;
    cout << "Starting date (dd/mm/yyyy): ";
    cin >> cur->startDate;
    cout << "Ending date (dd/mm/yyyy): ";
    cin >> cur->endDate;
}

int main()
{
    Read_multi_SMT();
    AddSemester();
    Output();
    DeleteSMT();
    return 0;
}