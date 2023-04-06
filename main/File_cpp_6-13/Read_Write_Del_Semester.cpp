#include "../Header/Semester.h"

// todo make it more efficient
Semester* Read_Sem(int year, int smt)
{
    string path = "..\\Data_file\\" + to_string(year) + '_' + to_string(year + 1);
    path += "\\smt" + to_string(smt) + "\\in4smt.txt";

    ifstream ifs(path);
    if (!ifs)
        return nullptr;
    
    Semester* newSem = new Semester;
    newSem->Year = year;
    newSem->No = smt;
    ifs >> newSem->startDate >> newSem->endDate;

    Course* newCourse = nullptr;
    while (!ifs.eof())
    {
        if (!newSem->course)
        {
            newSem->course = new Course;
            newCourse = newSem->course;
        }
        else
        {
            newCourse->next = new Course;
            newCourse->next->prev = newCourse;
            newCourse = newCourse->next;
        }
        ifs.ignore();
        getline(ifs, newCourse->Name);
        ifs >> newCourse->CourseID >> newCourse->Credits >> newCourse->maxStudents >> newCourse->numStudents >> newCourse->Room;
        ifs.ignore();
        getline(ifs, newCourse->TeacherName);
        ifs >> newCourse->Day >> newCourse->Session;
    }

    ifs.close();
    return newSem;    
}
Semester* Read_All_Semester(int year)
{
    Semester* semHead = nullptr;
    for (int i = 1; i <= 3; i++)
    {
        Semester* newSem = Read_Sem(year, i);
        if (!newSem)
            continue;
        if (!semHead)
        {
            semHead = newSem;
            continue;
        }
        Semester* tmp = semHead;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = newSem;
        newSem->prev = tmp;
    }
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
            << course_head->Session;
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
        string outPath = "..\\Data_file\\" + out_year + "\\smt" + to_string(sem_cur->No) + "\\in4smt.txt";
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