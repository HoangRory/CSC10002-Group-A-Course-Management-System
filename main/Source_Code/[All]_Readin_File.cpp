#include "../Header/Year.h"
#include "../Header/Semester.h"
#include "../Header/Login.h"
#include "../Header/AccReader.h"

//? Account
WinFormAccount^ ConvertToWinFormAccount(Account* account)
{
    if (account == nullptr)
        return nullptr;

    WinFormAccount^ winFormAccount = gcnew WinFormAccount();
    winFormAccount->username = gcnew String(account->username.c_str());
    winFormAccount->password = gcnew String(account->password.c_str());
    winFormAccount->firstName = gcnew String(account->firstName.c_str());
    winFormAccount->lastName = gcnew String(account->lastName.c_str());
    winFormAccount->Gender = gcnew String(account->Gender.c_str());
    winFormAccount->SocialID = gcnew String(account->SocialID.c_str());
    winFormAccount->birth = gcnew String(account->birth.c_str());
    winFormAccount->role = account->role;
    winFormAccount->next = ConvertToWinFormAccount(account->next);
    winFormAccount->prev = nullptr;

    if (winFormAccount->next != nullptr)
        winFormAccount->next->prev = winFormAccount;

    return winFormAccount;
}

void ReadAccount(WinFormAccount^% accHead)
{
    Account* accountHead = nullptr;

    std::ifstream ifs("../Data_file/account.csv");
    if (!ifs)
        return;

    Account *cur;
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

    // Convert the Account structure to WinFormAccount structure
    accHead = ConvertToWinFormAccount(accountHead);
}

//? Year
void loadingFile(Year *&yearHead, int &numofYear)
{
    cout << "Loading file" << endl;
    importYear(yearHead, numofYear); // Read the year's stored file
    for (int i = 0; i < 5; i++)
    {
        Sleep(400);
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

    Year *curYear;
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
            curYear = tmp;
        }

        numofYear++;
        ifs >> curYear->yearStart; // Get the year starting year to generate
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
    newSem->No = smt; // Get the year and semester
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
        ifs >> newCourse->CourseID >> newCourse->Credits >> newCourse->maxStudents 
            >> newCourse->numStudents >> newCourse->Room;
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
