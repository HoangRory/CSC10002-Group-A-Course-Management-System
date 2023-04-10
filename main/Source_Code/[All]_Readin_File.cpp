#include "../Header/Year.h"
#include "../Header/Semester.h"
#include "../Header/Login.h"

//? Account
void ReadAccount(Account *&accHead)
{
    std::ifstream ifs("../Data_file/account.csv");
    if (!ifs)
        return;

    Account *cur;
    string str;
    getline(ifs, str, '\n');
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
    cout << "Loading file..." << endl;
    importYear(yearHead, numofYear);
    _sleep(3000);
    cout << "Loading file completed." << endl;
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

    Year *curYear;
    while (!ifs.eof())
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
            curYear = tmp;
        }

        numofYear++;
        ifs >> curYear->yearStart;
        importClass(curYear, curYear->yearStart);
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
        {
            curClass = curClass->next;
        }
        curClass->next = new Class;
        curClass->next->Name = ClassName;
    }
}
void importClass(Year *curYear, int yearStart)
{
    // create the path to the directory
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

    // cout << "Class imported successfully" << endl;
}

//? Semester
Semester *Read_Sem(int year, int smt)
{
    string path = "..\\Data_file\\" + to_string(year) + '_' + to_string(year + 1);
    path += "\\smt" + to_string(smt) + "\\in4smt.txt";

    ifstream ifs(path);
    if (!ifs)
        return nullptr;

    Semester *newSem = new Semester;
    newSem->Year = year;
    newSem->No = smt;
    ifs >> newSem->startDate >> newSem->endDate;

    Course *newCourse = nullptr;
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
Semester *Read_All_Semester(int year)
{
    Semester *semHead = nullptr;
    for (int i = 1; i <= 3; i++)
    {
        Semester *newSem = Read_Sem(year, i);
        if (!newSem)
            continue;
        if (!semHead)
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
