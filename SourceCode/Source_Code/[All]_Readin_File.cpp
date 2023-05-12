#include "../Header/Year.h"
#include "../Header/Semester.h"
#include "../Header/Login.h"
#include "../Header/course.h"
#include "../Header/Utility.h"
using namespace std;
//? Account
void ReadAccount(Account *&accHead)
{
    std::ifstream ifs("../Data_file/account.csv");
    if (!ifs)
        return;

    Account *cur = nullptr;
    string str;
    getline(ifs, str, '\n'); // get the first title line in csv file
    while (!ifs.eof())
    {
        if (!accHead)
        {
            accHead = new Account;
            cur = accHead;
            cur->prev = nullptr;
        }
        else
        {
            cur->next = new Account;
            Account *tmp = cur;
            cur = cur->next;
            cur->prev = tmp;
        }
        cur->next = nullptr;

        // Read the username, pass, ... and put in the account linked list
        getline(ifs, cur->username, ',');
        getline(ifs, cur->password, ',');
        getline(ifs, str, ',');
        cur->role = stoi(str);
        getline(ifs, cur->lastName, ',');
        getline(ifs, cur->firstName, ',');
        getline(ifs, cur->Gender, ',');
        getline(ifs, cur->SocialID, ',');
        getline(ifs, cur->birth, '\n');

        // std::cout << cur->username << " || " << cur->password << " || " << cur->role << cur->lastName << " || " << cur->NationalID << " || " << cur->birth << '\n';
    }

    ifs.close();
    return;
}

//? Year
void loadingFile(Year *&yearHead, int &numofYear)
{
    cout << "Loading file" << endl;
    importYear(yearHead, numofYear); // Read the year's stored file
    for (int i = 0; i < 5; i++)
    {
        Sleep(200);
        cout << '.'; // The effect :)))
    }
    cout << "\nLoading file completed." << endl;
}
void importYear(Year *&yearHead, int &numofYear)
{
    // string in_year = to_string(yearStart);

    string path = "..\\Data_file\\years.txt";
    ifstream ifs(path);
    if (!ifs)
    {
        cerr << "Error: Cannot open file years.txt" << endl;
        return;
    }

    Year *curYear = nullptr;
    while (!ifs.eof()) // Create the year linked list according to the saved years
    {
        if (!yearHead)
        {
            yearHead = new Year;
            curYear = yearHead;
        }
        else
        {
            Year *tmp = new Year;
            curYear->next = tmp;
            tmp->prev = curYear;
            curYear = tmp;
        }

        numofYear++;
        ifs >> curYear->yearStart;                // Get the year starting year to generate
        importClass(curYear, curYear->yearStart); // Access the saved classes files
    }
}
void addClass(Year *curYear, string ClassName)
{
    if (!curYear->Class)
    {
        curYear->Class = new Class;
        curYear->Class->Name = ClassName;
    }
    else
    {
        Class *curClass = curYear->Class;
        while (curClass->next)
            curClass = curClass->next;

        curClass->next = new Class;
        curClass->next->Name = ClassName;
    }
}
void importClass(Year *curYear, int yearStart)
{
    // access the path to the directory
    string in_year = to_string(yearStart) + '_' + to_string(yearStart + 1);
    string path = "..\\Data_file" + separator + in_year + separator + "class.txt";

    ifstream ifs(path);
    if (!ifs)
    {
        cerr << "Error: Cannot open directory for year " << yearStart << endl;
        return;
    }
    // open class file
    string classFilePath = path;
    ifstream classFile(classFilePath);
    if (!classFile.is_open())
    {
        cerr << "Error: Cannot open class file for year " << yearStart << endl;
        return;
    }

    string line;
    getline(classFile, line); // read the first "class" line
    if (line.empty() || all_of(line.begin(), line.end(), [](unsigned char c)
                               { return std::isspace(c); }))
        return; // end of file

    // read each class from the file, add to the linked list
    Class *curClass = new Class;
    curClass->Name = line;
    addClass(curYear, curClass->Name);
    curClass = curYear->Class; // add new class to linked list

    Student *headStudent = nullptr;

    while (getline(classFile, line))
    {
        if (line.empty() || all_of(line.begin(), line.end(), [](unsigned char c)
                                   { return std::isspace(c); }))
            break; // end of file

        if (line == "-1")
        {
            // end of cur class, move to next class
            getline(classFile, line); // read the class line for the next class
            if (line.empty() || all_of(line.begin(), line.end(), [](unsigned char c)
                                       { return std::isspace(c); }))
                break; // end of file

            curClass = new Class;
            curClass->Name = line;
            addClass(curYear, curClass->Name);

            Class *tmp = curYear->Class;
            while (tmp->next)
            {
                tmp = tmp->next;
            }

            curClass = tmp;
            headStudent = nullptr;
        }
        else
        {
            if (!curClass)
            {
                cerr << "Error: class not found" << endl;
                return;
            }
            // Student *curStudent = nullptr;
            if (!headStudent)
            {
                curClass->StudentClass = new Student;
                headStudent = curClass->StudentClass;
                headStudent->ID = line;
            }
            else
            {
                Student *curStudent = new Student;
                curStudent->ID = line;
                curStudent->prev = headStudent;
                headStudent->next = curStudent;
                headStudent = curStudent;
            }
        }
    }

    curClass = curYear->Class;
    while (curClass)
    {
        Student *curStudent = curClass->StudentClass;
        while (curStudent && curStudent->next)
            curStudent = curStudent->next;
        if (curStudent)
            curStudent->next = nullptr;
        curClass = curClass->next;
    }

    classFile.close();
    ifs.close();
    // cout << "Class imported successfully" << endl;
}

//? Semester
Semester *Read_Sem(int year, int smt)
{
    // Generate the path
    string path = "..\\Data_file\\" + to_string(year) + '_' + to_string(year + 1);
    path += "\\smt" + to_string(smt) + "\\in4smt.txt";

    ifstream ifs(path); // Open file
    if (!ifs)
        return nullptr;

    Semester *newSem = new Semester;
    newSem->Year = year;
    newSem->No = smt;                            // Get the year and semester
    ifs >> newSem->startDate >> newSem->endDate; // Get the date

    Course *newCourse = nullptr;
    while (!ifs.eof())
    {
        if (!newSem->course) // Check whether to create a new head or continue create next
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
Semester *Read_All_Semester(int year)
{
    Semester *semHead = nullptr;
    for (int i = 1; i <= 3; i++) // Loop to read the 3 semester in the year, return null if there isn't
    {
        Semester *newSem = Read_Sem(year, i);
        if (!newSem) // continue if null
            continue;
        if (!semHead) // If there's not, set to head
        {
            semHead = newSem;
            continue;
        }
        Semester *tmp = semHead;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = newSem;
        newSem->prev = tmp;
    }
    return semHead;
}

void readScoreStudentCourse(ScoreBoardCourse &SBC, ifstream &in)
{
    string s_totalMark, s_finalMark, s_midMark, s_otherMark;
    getline(in, s_totalMark, ',');
    getline(in, s_finalMark, ',');
    getline(in, s_midMark, ',');
    getline(in, s_otherMark, '\n');

    SBC.totalMark = SBC.finalMark = SBC.midMark = SBC.otherMark = -1;
    if (s_totalMark != "X")
        SBC.totalMark = stod(s_totalMark);
    if (s_finalMark != "X")
        SBC.finalMark = stod(s_totalMark);
    if (s_midMark != "X")
        SBC.midMark = stod(s_midMark);
    if (s_otherMark != "X")
        SBC.otherMark = stod(s_otherMark);
}

void readStudentCourse(StudentCourse *&studentHead, ifstream &in)
{
    StudentCourse *cur = studentHead;
    string del = "";
    if (!in.eof())
        getline(in, del, '\n');
    while (!in.eof())
    {
        if (!cur)
            cur = studentHead = new StudentCourse;
        else
        {
            cur->next = new StudentCourse;
            cur->next->prev = cur;
            cur = cur->next;
        }
        getline(in, del, ',');
        getline(in, cur->ID, ',');
        getline(in, cur->FullName, ',');
        readScoreStudentCourse(cur->ScoreBoardCourse, in);
    }
}

// import data course
void readAllFileCourses(Semester *HeadSmt)
{
    ifstream in;
    Semester *curSmt = HeadSmt;
    Course *curCourse;
    while (curSmt)
    {
        curCourse = curSmt->course;
        while (curCourse)
        {
            string path = "..\\Data_file\\" + createNameFile(curSmt->Year, curSmt->No) + getFirstChar(curCourse->Name) + "score.csv";
            in.open(path);
            if (!in.is_open())
                Message_Warning(path + " is not exist.", "Error");
            else
                readStudentCourse(curCourse->studentCourse, in);
            in.close();
            curCourse = curCourse->next;
        }
        curSmt = curSmt->next;
    }
}

void importScoreBoardCourse(Year *yearHead)
{
    Year *ChooseYear = nullptr;
    Semester *ChooseSem = nullptr;
    Course *ChooseCourse = nullptr;
    system("cls");
    int x = 40, y = 2;
    Render_Import(x, y);
    x = 60, y = 15;
    if (yearHead == nullptr)
    {
        Message_Warning("There are no school year.", "Error not exist");
        // gọi lại hàm mainmenu
        return;
    }
    goToXY(40, 13);
    cout << "Select the year that contains the course you want to import";
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
    cout << "Select the semester that contains the course you want to import";
    ChooseSem = chooseSemesterbyOption_XY(ChooseYear->NoSemester, x, y, 5);
    cout << setw(70) << " ";
    while (ChooseSem)
    {
        if (ChooseSem->course == nullptr)
            Message_Warning("There are no course in this semester", "Error not Exist");
        else
        {
            goToXY(40, 10);
            cout << "You should save the file to folder ";
            goToXY(40, 11);
            cout << "../Data_file/ImportScoreBoard/"
                 << ChooseYear->yearStart << "_" << ChooseYear->yearStart + 1
                 << "/smt" << ChooseSem->No << "/<File Name> for easy implementation";
            goToXY(40, 12);
            cout << "Eg: Course's Name is Ky Nang Mem, File Name: KNMscore.csv";
            goToXY(40, 13);
            cout << "Select the course you want to import the scoreboard";
            ChooseCourse = chooseCoursebyOption_XY(ChooseSem->course, x, y, 5);
            while (ChooseCourse)
            {
                string path = "..\\Data_file\\Import_ScoreBoard\\" + createNameFile(ChooseSem->Year, ChooseSem->No) + getFirstChar(ChooseCourse->Name) + "score.csv";
                string mess = "Put data in the default path :\n" + path + "\n Would you like enter another path?";
                if (Message_YesNo(mess, "Notice"))
                {
                    goToXY(60, 14);
                    cout << "File name: ";
                    string tmp = Limit_Input(60 + 11, 14, 50, 7);
                    if (tmp == "0")
                        break;
                    path = tmp;
                    system("cls");
                    Render_Import(40, 2);
                }
                if (!checkFile(path))
                {
                    Message_Warning("The scoreboard file of this course does not exist.\n Please contact the teacher to get scoreboard and to try again.", " Error!");
                    if (!Message_YesNo("Would you like to retry?", "Notice"))
                        break;
                }
                else
                {
                    ifstream in;
                    in.open(path);
                    readStudentCourse(ChooseCourse->studentCourse, in);
                    in.close();
                    if (!Message_YesNo("Successful import \n Would you like to continue?", "Notification"))
                        return;
                    // goToXY(40, 11);
                    // cout << "Please import the CSV file to folder ../Data_file/"
                    //     << ChooseYear->yearStart << "_" << ChooseYear->yearStart + 1
                    //     << "/smt" << ChooseSem->No << "/<File Name>";
                    // goToXY(40, 12);
                    // cout << "Eg: Course's Name is Ky Nang Mem, File Name: KNMscore.csv";
                    // goToXY(40, 13);
                    // cout << "Select the course you want to import the scoreboard";
                    ChooseCourse = chooseCoursebyOption_XY(ChooseSem->course, x, y, 5);
                }
            }
            goToXY(40, 11);
            cout << setw(150) << " ";
            goToXY(40, 12);
            cout << setw(150) << " ";
            goToXY(40, 13);
            cout << setw(100) << " ";
        }
        goToXY(40, 13);
        cout << "Select the semester that contains the course you want to import";
        ChooseSem = chooseSemesterbyOption_XY(ChooseYear->NoSemester, x, y, 5);
        cout << setw(70) << " ";
    }
    importScoreBoardCourse(yearHead);
}