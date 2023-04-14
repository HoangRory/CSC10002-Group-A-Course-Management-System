#include "../Header/Year.h"
#include "../Header/Semester.h"
#include "../Header/course.h"
#include "../Header/help.h"
#include "../Header/Login.h"

//? Output the course information
// 

void OutCourse(Course *course_head, ofstream &ofs)
{
    if (!course_head)
        return;
    while (course_head) // Output the information follows name, course ID, credits,... to file
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
void outScoreboard_StudentCourse (ofstream &ofs, ScoreBoardCourse SBC) 
{
    if(SBC.totalMark < 0) ofs << "X" << ",";
    else ofs << SBC.totalMark << ",";
    if(SBC.finalMark < 0) ofs << "X" << ",";
    else ofs << SBC.finalMark << ",";
    if(SBC.midMark < 0) ofs << "X" << ",";
    else ofs << SBC.midMark << ",";
    if(SBC.otherMark < 0) ofs << "X" << endl;
    else ofs << SBC.otherMark << endl;
}
void OutStudent_Course(ofstream &ofs, StudentCourse *curStudent)
{
    int no = 1;
    while (curStudent) 
    {
        ofs << no++ << ","
            << curStudent->ID << ","
            << curStudent->FullName;
        outScoreboard_StudentCourse(ofs,curStudent->ScoreBoardCourse);
    }
}
void Output(Year *yearHead)
{
    if (!yearHead->NoSemester)
        return;

    Semester *sem_cur = yearHead->NoSemester;
    string out_year = to_string(yearHead->yearStart) + '_' + to_string(yearHead->yearStart + 1);

    while (sem_cur)
    {
        // Path changes according to the current year-semester
        string outPath = "..\\Data_file\\" + out_year + "\\smt" + to_string(sem_cur->No) + "\\in4smt.txt";
        ofstream ofs(outPath);
        if (!ofs)
            return;
        // ofs << sem_cur->No << '\n';
        ofs << sem_cur->startDate << ' ' << sem_cur->endDate; // Output the date
        OutCourse(sem_cur->course, ofs);
        ofs.close();
        Course *courseHead = sem_cur->course;
        while(courseHead) {
            string path = createNameFile(sem_cur->Year, sem_cur->No,courseHead->Name,"score","csv");
            if (!checkFile(path)) 
                system(("mkdir " + path).c_str());
            ofs.open(path);
            ofs << courseHead->Name << endl;
            OutStudent_Course(ofs,courseHead->studentCourse);
            ofs.close(); 

        }

        sem_cur = sem_cur->next;
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

    ofs << "Username,PassWord,Role,LastName,FirstName,Gender,SocialID,Birthday\n";
    Account *cur = accHead;
    while (cur) // follows username, pass, role, lastname, firstname, gender, social ID, birthday
    {
        ofs << cur->username << ',' << cur->password << ','
            << cur->role << ',' << cur->lastName << ','
            << cur->firstName << ',' << cur->Gender << ','
            << cur->SocialID << ',' << cur->birth;
        cur = cur->next;
        if (cur)
            ofs << "\n";
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
    accTmp->username = ID;         //? Set the default username to student ID
    accTmp->password = "11111111"; //? Set default password to 8 1
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

        // Path changes according the the current year
        string path = "..\\Data_file\\" + to_string(yearTMP->yearStart) + '_' + to_string(yearTMP->yearStart + 1) + "\\class.txt";
        ofstream ofs(path);
        if (!ofs)
            return;

        // Scan throught the list class with its students
        while (ClassTMP)
        {
            ofs << ClassTMP->Name;
            Student *StudentTMP = ClassTMP->StudentClass;
            while (StudentTMP)
            {
                ofs << "\n"
                    << StudentTMP->ID;
                StudentTMP = StudentTMP->next;
            }
            ClassTMP = ClassTMP->next;
            if (ClassTMP)
                ofs << "\n-1\n"; // Output -1 to divide out between classes
        }
        yearTMP = yearTMP->next;
        if (yearTMP)
            outyear << '\n';
    }
    outyear.close();
}

//task 19
//func export the list student of a course to sent to teacher
//hàm này lấy 
void exportListStudentCourse(Semester *curSmt)
 {
    system("cls");
    cout << "Please select course for which you want to show scoreboard. Or select close <- to come back Main Menu" << endl;
    cout << "Using arrow keys to move and press enter to select your option." << endl;
    system("pause");
    system("cls");

    //nếu muốn hàm chọn
    Course *curCourse = chooseCoursebyOption(curSmt->course);
    if(!curCourse) {
        //quay lại menu
        return;
    }


    string path = createNameFile(curSmt->Year, curSmt->No, curCourse->Name, "score", "CSV");
    if (!checkFile(path)) 
        system(("mkdir " + path).c_str());
    ofstream out;
    out.open(path);
    outStudentCourse(curCourse->studentCourse, out);
    out.close();   
}// hàm này chỉ xuất chứ chưa xóa linked list