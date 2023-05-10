#include "../Header/Year.h"
#include "../Header/Semester.h"
#include "../Header/Login.h"
#include "../Header/course.h"
#include "../Header/Utility.h"

//? Output the course information
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
        while (courseHead)
        {
            string path = "..\\Data_file\\" + createNameFile(sem_cur->Year, sem_cur->No);
            if (!checkFile(path))
                system(("mkdir " + path).c_str());
            path += getFirstChar(courseHead->Name) + "score.csv";
            ofs.open(path);
            outStudentCourse(courseHead->studentCourse, ofs);
            ofs.close();
            courseHead = courseHead->next;
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

void outScoreboard_StudentCourse(ofstream &ofs, ScoreBoardCourse SBC)
{
    if (SBC.totalMark < 0)
        ofs << "X"
            << ",";
    else
        ofs << SBC.totalMark << ",";
    if (SBC.finalMark < 0)
        ofs << "X"
            << ",";
    else
        ofs << SBC.finalMark << ",";
    if (SBC.midMark < 0)
        ofs << "X"
            << ",";
    else
        ofs << SBC.midMark << ",";
    if (SBC.otherMark < 0)
        ofs << "X";
    else
        ofs << SBC.otherMark;
}
void outStudentCourse(StudentCourse *stuHead, ofstream &ofs)
{
    int No = 1;
    ofs << "No,Student ID,Fullname,Total Mark,Final Mark,Mid Mark,Other Mark";
    while (stuHead)
    {
        ofs << "\n"
            << No++ << ","
            << stuHead->ID << ","
            << stuHead->FullName << ",";
        outScoreboard_StudentCourse(ofs, stuHead->ScoreBoardCourse);
        stuHead = stuHead->next;
    }
}
//?task 19
void exportListStudentCourse(Year *yearHead)
{
    Year *ChooseYear = nullptr;
    Semester *ChooseSem = nullptr;
    Course *ChooseCourse = nullptr;
    system("cls");
    int x = 40, y = 2;
    Render_Export(x, y);
    x = 60, y = 15;
    if (yearHead == nullptr)
    {
        Message_Warning("There are no school year.", "Error not exist");
        // gọi lại hàm mainmenu
        return;
    }
    goToXY(40, 13);
    cout << "Select the year that contains the course you want to Export";
    ChooseYear = chooseYearbyOption_XY(yearHead, x, y, 5);
    cout << setw(70) << " ";
    if (ChooseYear == nullptr)
    {
        // quay lại main menu
        return;
    }
    if (ChooseYear->NoSemester == nullptr)
    {
        Message_Warning("There are no semester in this school year.", "Error not exist");
    }
    goToXY(40, 13);
    cout << "Select the semester that contains the course you want to Export";
    ChooseSem = chooseSemesterbyOption_XY(ChooseYear->NoSemester, x, y, 5);
    cout << setw(70) << " ";
    while (ChooseSem)
    {
        if (ChooseSem->course == nullptr)
            Message_Warning("There are no course in this semester", "Error not Exist");
        else
        {
            goToXY(40, 13);
            cout << "Select the course you want to Export the scoreboard";
            ChooseCourse = chooseCoursebyOption_XY(ChooseSem->course, x, y, 5);
            cout << setw(70) << " ";
            while (ChooseCourse)
            {
                // string path = "..\\Data_file\\Import_ScoreBoard\\" + createNameFile(ChooseSem->Year, ChooseSem->No);
                // system(("mkdir " + path).c_str());
                string path = "..\\Data_file\\Export_Student\\" + createNameFile(ChooseSem->Year, ChooseSem->No);
                if (!checkFile(path))
                    system(("mkdir " + path).c_str());
                ofstream out;
                path += getFirstChar(ChooseCourse->Name) + "score.csv";
                out.open(path);
                outStudentCourse(ChooseCourse->studentCourse, out);
                out.close();
                if (!Message_YesNo("File export successful with path :" + path + " \n Would you like to continue?", "Success"))
                    return;

                ChooseCourse = chooseCoursebyOption_XY(ChooseSem->course, x, y, 5);
            }
        }
        ChooseSem = chooseSemesterbyOption_XY(ChooseYear->NoSemester, x, y, 5);
    }
    exportListStudentCourse(yearHead);
}