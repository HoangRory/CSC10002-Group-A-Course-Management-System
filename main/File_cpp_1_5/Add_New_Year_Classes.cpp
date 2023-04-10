#include "../Header/year.h"

//? 1. Create a school year (2020-2021, for example)
//* lần đầu gọi hàm thì cho cin yearStart trong hàm main
void createSchoolYear(Year *&headYear, int yearStart)
{
    Year *curYear = headYear;
    while (curYear)
    {
        //! if the year already exists, it stops, so let it an option to enter again
        if (curYear->yearStart == yearStart)
        {
            cout << "Year " << yearStart << " already exists." << endl;
            cout << "Do you want to re-enter?\n1. Yes.\n2. No." << endl;
            cout << "Enter your choice: ";
            int choice = 0;
            cin >> choice;
            switch (choice)
            {
            case 1:
                cout << "Enter start year: ";
                cin >> yearStart;
                createSchoolYear(headYear, yearStart);
                return;
            case 2:
                cout << "Finish adding to the new school year. Thank you!" << endl;
                return;
            }
        }
        curYear = curYear->next;
    }

    Year *newYear = new Year;
    newYear->yearStart = yearStart;

    if (!headYear)
        headYear = newYear;
    else
    {
        curYear = headYear;
        while (curYear->next)
            curYear = curYear->next;
        curYear->next = newYear;
    }
    cout << "Year " << yearStart << " has been added successfully." << endl;

    for (int i = 0; i < 38; i++)
        cout << "-";
    cout << endl;

    cout << "Do you want to add a new year?\n1. Yes.\n2. No." << endl;
    cout << "Enter your choice: ";
    int choice = 0;
    cin >> choice;
    switch (choice)
    {
    case 1:
        cout << "Enter start year: ";
        cin >> yearStart;
        createSchoolYear(headYear, yearStart);
        break;
    case 2:
        cout << "Finish adding to the new school year. Thank you!" << endl;
        return;
    }
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

//? 2. Create several classes for 1st-year students.
//* For example: class 20APCS1, class 20APCS2, class 20CLC1..., class 20CLC11, class 20VP...
//* check if that class already exists.
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
        cout << "Added class " << line << " successfully.\n";
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

//? Choose the class to add Student
void ChooseClassToAdd(Year *curYear)
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
        ChooseClassToAdd(curYear);
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

//? Choose the method to add student
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

//? return true if it is a leap year
bool isLeap(int year)
{
    return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}

//? return true if the date is valid
bool isValidDate(const std::string &dateOfBirth)
{
    if (dateOfBirth.length() != 10)
        return false;

    if (dateOfBirth[2] != '/' || dateOfBirth[5] != '/')
        return false;

    int dd = std::stoi(dateOfBirth.substr(0, 2));
    int mm = std::stoi(dateOfBirth.substr(3, 2));
    int yyyy = std::stoi(dateOfBirth.substr(6, 4));

    if (mm < 1 || mm > 12)
        return false;

    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (isLeap(yyyy))
        daysInMonth[1] = 29;

    if (dd < 1 || dd > daysInMonth[mm - 1])
        return false;

    return true;
}

//? true if it is in the correct format
bool isValidGender(const std::string &gender)
{
    return (gender == "F" || gender == "M");
}

//? Input student by hand one the cmd
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
    while (!isValidGender(gen))
    {
        cout << "Invalid Gender. Please retry."
             << "\n";
        cout << "Gender (M: male   F: female): ";
        getline(cin, gen);
    }

    cout << "- Date of birth (dd/mm/yyyy): ";
    getline(cin, birth);
    while (!isValidDate(birth))
    {
        cout << "Invalid Date of Birth. Please retry." << endl;
        cout << "Date of Birth (dd/mm/yyyy):";
        getline(cin, birth);
    }

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

//? Import student from file
void importStudent(Class *curClass)
{
    cout << "Please import the CSV file to folder New_Enrolled_Student." << endl;
    cout << "Please enter file name: ";
    string fileName;
    getline(cin, fileName);

    string path = "..\\Data_file" + separator + "New_Enrolled_Student" + separator + fileName;
    cout << path << endl;
    // check if the file exits
    ifstream studentList(path.c_str());
    if (!studentList.is_open())
    {
        cout << "File does not exit." << endl;
        return;
    }

    // read CSV file line by line
    string line;
    string delimiter = ",";
    int lineCount = 0;
    
    getline(studentList, line);
    while (getline(studentList, line))
    {
        // split the line by commas
        size_t position = 0;
        stringstream ss(line);
        string token;
        string fields[6];
        int i = 0;

        while (i < 6)
        {
            if (i < 5)
            {
                position = line.find(delimiter);
                token = line.substr(0, position);
                line.erase(0, position + delimiter.length());
            }
            else
                token = line;
            fields[i] = token;
            i++;
        }

        // check if the line have the correct num of fields
        if (i != 6)
            cout << "Invalid line format in CSV file. Please import another.\n";

        // save the student information
        string studentID = fields[0];
        string firstName = fields[1];
        string lastName = fields[2];
        string gender = fields[3];
        string dateofBirth = fields[4];
        string socialID = fields[5];

        lineCount++;
        // add the student to class
        if (checkStudent(curClass, studentID))
            cout << "This student has already been added. Please retry." << endl;
        else
            add1stYearStudents(curClass, studentID, firstName, lastName, gender, dateofBirth, socialID);
    }
    cout << "Imported " << lineCount << " students to class " << curClass->Name << ".\n";
}

//? Add student one by one
void add1stYearStudents(Class *curClass, string ID, string first, string last, string gen, string birth, string socialID)
{
    Student *headStudent = curClass->StudentClass;
    Student *newStud = new Student;

    newStud->ID = ID;
    newStud->accStudent = new Account;

    //? Set information to student
    Account *accTmp = newStud->accStudent;
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

//? Create new account for new student
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

//? Delete the year linked list
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

// lần đầu gọi hàm thì cho cin className trong hàm main
//!
/*
void createClasses(Year *curYear, string className)
{
    if (checkClass(curYear, className) && to_string(curYear->yearStart % 100) == className.substr(0, 2))
    {
        cout << "Class " << className << " already exists or invalid class name. Please retry." << endl;
        int choice = -1;
        while (choice != 2)
        {
            cout << "Do you want to enter a new class?\n1. Yes.\n2. No.\n3. Back" << endl;
            cout << "Enter your choice: ";
            cin >> choice;
            switch (choice)
            {
            case 1:
                cout << "Enter class name: ";
                cin >> className;
                createClasses(curYear, className);
                break;
            case 2:
                cout << "Finish adding to the new class. Thank you!" << endl;
                return;
            case 3:
                cout << "======ADDING NEW SCHOOL YEAR======" << endl;
                cout << "Enter start year: ";
                int yearStart = 0;
                cin >> yearStart;
                createSchoolYear(curYear, yearStart);
            }
        }
    }

    Class *newClass = new Class;
    newClass->Name = className;
    newClass->StudentClass = nullptr;

    if (!curYear->Class)
        curYear->Class = newClass;
    else
    {
        Class *prevClass = curYear->Class;
        while (prevClass->next)
            prevClass = prevClass->next;
        prevClass->next = newClass;
        //? thêm cái link ngược về nữa
        prevClass->next->prev = prevClass;
    }
    cout << "Class " << className << " has been added successfully!" << endl;
}
*/