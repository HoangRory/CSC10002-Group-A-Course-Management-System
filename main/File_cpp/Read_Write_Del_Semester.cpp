// #include "Header/proto.h"
#include "../Header/Semester.h"

// todo make it more efficient
void Read_SMT(Semester *&semHead, int y, int smt)
{
    string in_year = to_string(y) + '_' + to_string(y + 1);
    string path = "..\\Data_file\\" + in_year + "\\smt" + to_string(smt) + "\\in4smt.txt";

    ifstream ifs(path);
    if (!ifs)
        return;

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

        sem_cur->No = smt;
        sem_cur->Year = y;
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
void Read_multi_SMT(Semester *&semHead, int yr, int num_year, int num_smt)
{
    for (int y = yr; y < yr + num_year; y++)
        for (int smt = 1; smt <= num_smt; smt++)
            Read_SMT(semHead, y, smt);
}


void DeleteStudent(StudentCourse *&stud_head)
{
    if (!stud_head)
        return;
    DeleteStudent(stud_head->next);
    delete stud_head;
    stud_head = nullptr;
}
void DeleteCourse(Course *&course_head)
{
    if (!course_head)
        return;
    DeleteCourse(course_head->next);
    DeleteStudent(course_head->studentCourse);
    delete course_head;
    course_head = nullptr;
}
void DeleteSMT(Semester *&semHead)
{
    if (!semHead)
        return;
    DeleteCourse(semHead->course);
    Semester *tmp = semHead->next;
    delete semHead;
    semHead = tmp;
    DeleteSMT(semHead);
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
void Output(Semester *semHead)
{
    if (!semHead)
        return;
    Semester *sem_cur = semHead;

    while (sem_cur)
    {
        string out_year = to_string(sem_cur->Year) + '_' + to_string(sem_cur->Year + 1);
        string outPath = "..\\Data_file\\" + out_year + "\\smt" + to_string(sem_cur->No) + "\\";
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

//? Path in the output and read Semester function