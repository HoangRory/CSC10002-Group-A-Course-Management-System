#include "../Header/Year.h"
#include "../Header/Semester.h"
#include "../Header/Login.h"

//? Output the course information
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
void Output(Year *yearHead)
{
    if (!yearHead->NoSemester)
        return;

    Semester *sem_cur = yearHead->NoSemester;
    string out_year = to_string(yearHead->Year) + '_' + to_string(yearHead->Year + 1);

    while (sem_cur)
    {
        string outPath = "..\\Data_file\\" + out_year + "\\smt" + to_string(sem_cur->No) + "\\in4smt.txt";
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

//? Output the account information
void WriteAccount(Account *accHead)
{
    if (!accHead)
        return;
    std::ofstream ofs("../Data_file/account.csv");
    if (!ofs)
        return;

    Account *cur = accHead;
    while (cur)
    {
        ofs << cur->username << ',' << cur->password << ','
            << cur->role << ',' << cur->lastName << ','
            << cur->firstName << ',' << cur->Gender << ','
            << cur->SocialID << ',' << cur->birth << '\n';
        cur = cur->next;
    }
    ofs.close();
}

//? Year
//? Create an account for new student
void NewAccount(Account *accHead, string ID, Account *accTmp)
{
    Account *acc_cur = accHead;
    while (acc_cur->next)
        acc_cur = acc_cur->next;
    acc_cur->next = accTmp;
    accTmp->prev = acc_cur;
    accTmp->username = ID;        //? Set the default username to student ID
    accTmp->password = "11111111" //? Set default password to 8 1
        return;
}
//? Output the year information
void Outyear(Year *yearHead)
{
    string no_year_path = "..\\Data_file\\years.txt";
    ofstream outyear(no_year_path);
    if (!outyear)
        return;

    Year *yearTMP = yearHead;
    while (yearTMP)
    {
        outyear << yearTMP->yearStart;
        Class *ClassTMP = yearTMP->Class;

        string path = "..\\Data_file\\" + to_string(yearTMP->yearStart) + '_' + to_string(yearTMP->yearStart + 1) + "\\class.txt";
        ofstream ofs(path);
        if (!ofs)
            return;

        while (ClassTMP)
        {
            ofs << ClassTMP->Name << '\n';
            Student *StudentTMP = ClassTMP->StudentClass;
            while (StudentTMP)
            {
                ofs << StudentTMP->ID << '\n';
                StudentTMP = StudentTMP->next;
            }
            ofs << "-1";
            ClassTMP = ClassTMP->next;
            if (ClassTMP)
                ofs << '\n';
        }
        yearTMP = yearTMP->next;
        if (yearTMP)
            outyear << '\n';
    }
    outyear.close();
}