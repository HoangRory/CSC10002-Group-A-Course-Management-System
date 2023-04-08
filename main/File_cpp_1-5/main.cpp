#include "..\\Header\\Year.h"

Year *Create_NewYear(Year *yearHead)
{
    Year *yearTMP = yearHead;
    while (yearTMP->next)
        yearTMP = yearTMP->next;

    int year;
    int current = yearTMP->yearStart;
    cout << "Current year: " << current << "-" << current + 1 << "\nCreating year: " << current + 1 << "-" << current + 2 << "?\n";
    int yr_choice;
    cout << "1. Yes\n2. Enter a new year :))))'\n";
    cin >> yr_choice;

    if (yr_choice == 1)
        year = current + 1;
    else
    {
        cout << "Enter the year: ";
        cin >> year;
    }

    Year *year_cur = yearHead;
    while (year_cur)
    {
        if (year_cur->yearStart == year)
        {
            cout << "Year " << year << " already exists.\n";
            cout << "Do you want to re-enter?(Y/N) ";
            char choice;
            cin >> choice;
            while (choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n')
            {
                cout << "Invalid input. Please re-enter: ";
                cin >> choice;
            }
            if (choice == 'Y' || choice == 'y')
            {
                cout << "Enter the year: ";
                cin >> year;
            }
            else
                return nullptr;
        }
        year_cur = year_cur->next;
    }

    Year *newYear = new Year;
    newYear->yearStart = year;
    yearTMP->next = newYear;

    // todo return the new year for further inputing 1st year student
    return newYear;
}

//? Return true if the class already exists
bool checkClass(Year *curYear, string className)
{
    Class *curClass = curYear->Class;
    while (curClass)
    {
        if (curClass->Name == className)
            return true;
        curClass = curClass->next;
    }
    return false;
}

void Create_New_Classes(Year *newYear)
{
    cout << "Enter -1 to stop adding new classes\n";
    cout << "Adding new classes to year " << newYear->yearStart << "_" << newYear->yearStart + 1 << ":\n";
    Class *ClassTMP = newYear->Class;

    string line;
    while (cin >> line)
    {
        if (line == "-1")
            break;
        CapitalClassName(line);
        if (checkClass(newYear, line))
        {
            cout << "Class " << line << " already exists.\nPlease re-enter: ";
            continue;
        }
        if (line.substr(0, 2) != to_string(newYear->yearStart).substr(2, 2))
        {
            cout << "Invalid class name. Please re-enter: ";
            continue;
        }
        if (!ClassTMP)
        {
            ClassTMP = new Class;
            newYear->Class = ClassTMP;
        }
        else
        {
            ClassTMP->next = new Class;
            ClassTMP->next->prev = ClassTMP;
            ClassTMP = ClassTMP->next;
        }
        ClassTMP->Name = line;
    }
}

//? Return true if the student already exists
bool Check_Student(Class *curClass, string studentID)
{
    Student *curStudent = curClass->StudentClass;
    while (curStudent)
    {
        if (curStudent->ID == studentID)
            return true;
        curStudent = curStudent->next;
    }
    return false;
}

//? Turn the classname to uppercase
void CapitalClassName(string &name)
{
    for (int i = 0; i < name.length(); i++)
        name[i] = toupper(name[i]);
}

void addStudentToClass(Year *curYear)
{
    string className;
    cout << "Enter -1 to quit!!!\n\n";
    cout << "Enter the class that you want to add student: ";
    cin >> className;
    if (className == "-1")
        return;
    CapitalClassName(className);
    if (!checkClass(curYear, className))
    {
        cout << "Class " << className << " does not exist!!!\n";
        addStudentToClass(curYear);
        return;
    }
    Class *curClass = curYear->Class;
    while (curClass)
    {
        if (curClass->Name == className)
            break;
        curClass = curClass->next;
    }
    Method(curClass);
    return;
}

void Method(Class *curClass)
{
    int choice = -1;
    cout << "Choosing a method to add student:\n";
    cout << "1. Adding by hand\n2. Importing from file\n3. Return\n";
    cout << "==> Enter your choice: ";
    cin >> choice;
    // todo convert into conio để khỏi check đúng sai cái này
    switch (choice)
    {
    case 1:
        inputStudent(curClass);
        break;
    case 2:
        importStudent(curClass);
        break;
    }
}

void inputStudent(Class *curClass)
{
    string ID, first, last, gen, birth, socialID;
    cout << "Adding student by hand one by one\n";
    cout << "Enter the student information: \n";
    for (int i = 0; i < 88; i++)
        cout << "=";
    cout << "\n";
    cin.ignore();
    cout << "- Student ID: ";
    getline(cin, ID);

    cout << "- First name: ";
    getline(cin, first);

    cout << "- Last name: ";
    getline(cin, last);

    cout << "- Gender (M: male, F: female): )";
    getline(cin, gen);

    cout << "- Date of birth (dd/mm/yyyy): ";
    getline(cin, birth);

    cout << "- Social ID: ";
    getline(cin, socialID);

    if (Check_Student(curClass, ID))
    {
        cout << "Student has already been added!!!\n";
        char ch;
        cout << "Do you want to re-enter?(Y/N) ";
        cin >> ch;
        while (ch != 'Y' && ch != 'y' && ch != 'N' && ch != 'n')
        {
            cout << "Invalid input. Please re-enter: ";
            cin >> ch;
        }
        if (ch == 'Y' || ch == 'y')
            inputStudent(curClass);
        return;
    }
    add1stYearStudents(curClass, ID, first, last, gen, birth, socialID);
    //? Add here
}
void add1stYearStudents(Class* curClass, string ID, string first, string last, string gen, string birth, string socialID)
{
    Student * headStudent = curClass->StudentClass;
    Student* newStud = new Student;

    newStud->ID = ID;
    newStud->accStudent = new Account;

    //? Set information to student
    Account* accTmp = newStud->accStudent;
    accTmp->role = 1; //? Set role for student
    accTmp->firstName = first;
    accTmp->lastName = last;
    accTmp->Gender = gen;
    accTmp->birth = birth;
    accTmp->SocialID = socialID;

    if (!headStudent)
        curClass->StudentClass = newStud;
    else
    {
        while (headStudent->next)
            headStudent = headStudent->next;
        headStudent->next = newStud;
        newStud->prev = headStudent;
    }

    cout << "Student " << accTmp->firstName << " " << accTmp->lastName 
         << " has been added to class " << curClass->Name << "\n";
}

void NewAccount(Account* accHead, string ID, Account* accTmp)
{
    Account* acc_cur = accHead;
    while(acc_cur->next)
        acc_cur = acc_cur->next;
    acc_cur->next = accTmp;
    accTmp->prev = acc_cur;
    accTmp->username = ID; //? Set the default username to student ID
    accTmp->password = "11111111" //? Set default password to 8 1
    return;
}

int main()
{
    Year *yearHead = nullptr;
    yearHead = Read_Multi_year();

    DeleteYear(yearHead);
    return 0;
}

Year *Read_Year_Class(int year)
{
    string yr = to_string(year) + '_' + to_string(year + 1);
    string path = "..\\Data_file\\" + yr + "\\class.txt";

    ifstream ifs(path);
    if (!ifs)
        return nullptr;

    Year *yearTMP = new Year;
    yearTMP->yearStart = year;
    // yearTMP->Class = new Class;
    Class *ClassTMP = yearTMP->Class;

    while (!ifs.eof())
    {
        string line;

        if (!ClassTMP)
        {
            ClassTMP = new Class;
            yearTMP->Class = ClassTMP;
        }
        else
        {
            ClassTMP->next = new Class;
            ClassTMP->next->prev = ClassTMP;
            ClassTMP = ClassTMP->next;
        }

        ifs >> ClassTMP->Name;

        Student *StudentTMP;
        while (ifs >> line)
        {
            if (line == "-1")
                break;

            if (!ClassTMP->StudentClass)
            {
                ClassTMP->StudentClass = new Student;
                StudentTMP = ClassTMP->StudentClass;
            }
            else
            {
                StudentTMP->next = new Student;
                StudentTMP->next->prev = StudentTMP;
                StudentTMP = StudentTMP->next;
            }
            StudentTMP->ID = line;
        }
    }

    ifs.close();
    return yearTMP;
}

Year *Read_Multi_year()
{
    string path = "..\\Data_file\\year.txt";

    ifstream ifs(path);
    if (!ifs)
        return nullptr;

    Year *yearHead = nullptr;
    while (!ifs.eof())
    {
        string tmp_year;
        ifs >> tmp_year;
        if (!yearHead)
            yearHead = Read_Year_Class(stoi(tmp_year));
        else
        {
            Year *yearTMP = yearHead;
            while (yearTMP->next)
                yearTMP = yearTMP->next;
            yearTMP->next = Read_Year_Class(stoi(tmp_year));
        }
    }

    ifs.close();
    return yearHead;
}

void DeleteYear(Year *&yearHead)
{
    Year *yearTMP = yearHead;
    while (yearTMP)
    {
        Class *ClassTMP = yearTMP->Class;
        while (ClassTMP)
        {
            Student *StudentTMP = ClassTMP->StudentClass;
            while (StudentTMP)
            {
                Student *StudentTMP2 = StudentTMP;
                StudentTMP = StudentTMP->next;
                delete StudentTMP2;
            }
            Class *ClassTMP2 = ClassTMP;
            ClassTMP = ClassTMP->next;
            delete ClassTMP2;
        }
        Year *yearTMP2 = yearTMP;
        yearTMP = yearTMP->next;
        delete yearTMP2;
    }
    yearHead = nullptr;
}
