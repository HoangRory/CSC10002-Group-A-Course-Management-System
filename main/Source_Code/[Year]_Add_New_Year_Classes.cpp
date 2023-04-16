#include "../Header/Year.h"
#include "../Header/Semester.h"
#include "../Header/Utility.h"

//? 1. Create a school year (2020-2021, for example)
//* lần đầu gọi hàm thì cho cin yearStart trong hàm main
void createSchoolYear(Year *&headYear, int yearStart)
{
    Year *curYear = headYear;
    if (checkYear(headYear, yearStart))
    {
        string message = "Year " + to_string(yearStart) + "-" + to_string(yearStart + 1) + " already exists.\nDo you want to retry?";
        string title = "Error";
        if (Message_YesNo(message, title))
            Interface_New_Year(headYear); // Loop again
        return;
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
    string path = "..\\Data_file\\" + to_string(yearStart) + "_" + to_string(yearStart + 1);
    path = "mkdir " + path;
    system(path.c_str()); // Create a folder in the sys

    string message = "Year " + to_string(yearStart) + "-" + to_string(yearStart + 1) + " has been added successfully.\nDo you want to add class to this year?";
    string title = "Success";
    if (Message_YesNo(message, title))
    {
        Create_New_Classes(newYear);

        message = "Add student to class?";
        if (Message_YesNo(message, title))
        {
            ChooseClassToAdd(newYear);
        }
        return;
    }
    return;
}

//? 2. Create several classes for 1st-year students.
//* For example: class 20APCS1, class 20APCS2, class 20CLC1..., class 20CLC11, class 20VP...
//* check if that class already exists.
void Create_New_Classes(Year *newYear)
{
    system("cls");
    Render_Class();
    goToXY(50, 18);
    TextColor(0x0E);
    cout << "YEAR: " << newYear->yearStart << "_" << newYear->yearStart + 1;
    cout << "New Class(-1 to stop)";
    Class *ClassTMP = newYear->Class;
    string line;
    int i = 0;
    while (1)
    {
        TextColor(63);
        goToXY(50, 19 + i);
        cout << "               ";
        goToXY(52, 19 + i);

        cin >> line;
        if (line == "-1")
            break;
        CapitalClassName(line); // Capitalize the first letter of each word
        if (checkClass(newYear, line))
        {
            string message = "Class " + line + " already exists.\nDo you want to retry?";
            string title = "Error";
            if (Message_YesNo(message, title))
                continue;
            else
                break;
        }
        if (line.substr(0, 2) != to_string(newYear->yearStart).substr(2, 2)) // Check if the class name is valid
        {
            string message = "Invalid class name.\nDo you want to retry?";
            string title = "Error";
            if (Message_YesNo(message, title))
                continue;
            else
                break;
        }
        i++;
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
        string message = "Added class " + line + " successfully.";
        Message_Warning(message, "Success");
    }
    return;
}

//? Choose the class to add Student
void ChooseClassToAdd(Year *curYear)
{
    system("cls");
    vector<string> listClass;
    Class *class_cur = curYear->Class;
    while (class_cur)
    {
        listClass.push_back(class_cur->Name);
        class_cur = class_cur->next;
    }
    goToXY(60, 12);
    cout << "Classes in " << curYear->yearStart << "-" << curYear->yearStart + 1;

    int opt = Draw_ShortVer(listClass);
    string className = listClass[opt];

    class_cur = curYear->Class;
    while (class_cur)
    {
        if (class_cur->Name == className)
            break;
        class_cur = class_cur->next;
    }
    Method(class_cur);
    return;
}

//? Choose the method to add student
void Method(Class *curClass)
{
    system("cls");
    vector<string> menu;
    menu.push_back("Adding by hand");
    menu.push_back("Importing from file");
    menu.push_back("Return");

    goToXY(60, 12);
    cout << "Choose method to add student";

    int opt = Draw_ShortVer(menu);
    switch (opt)
    {
    case 0:
        inputStudent(curClass);
        return;
    case 1:
        importStudent(curClass);
        return;
    }
    return;
}

//? Input student by hand one the cmd
void inputStudent(Class *curClass)
{
    system("cls");
    string ID, full, first, last, gen, birth, socialID;
    cin.ignore();
    goToXY(60, 12);
    cout << "Student information";

    goToXY(60, 13);
    TextColor(63);
    cout << "  Student ID:                    ";
    goToXY(75, 13);
    getline(cin, ID);
    TextColor(7);
    goToXY(60, 13);
    cout << "  Student ID: " << ID << "                                 ";

    cin.ignore();
    goToXY(60, 14);
    TextColor(63);
    cout << "  Full name:                                       ";
    goToXY(74, 14);
    getline(cin, full);
    TextColor(7);
    goToXY(60, 14);
    cout << "  Full name: " << full << "                                 ";

    SeparateName(full, first, last);

    cin.ignore();
    goToXY(60, 15);
    TextColor(63);
    cout << "  Gender (M: male, F: female):          ";
    goToXY(92, 15);
    getline(cin, gen);
    while (!isValidGender(gen))
    {
        string message = "Invalid gender format!\nPlease retry.";
        string title = "Error";
        Message_Warning(message, title);
        goToXY(60, 15);
        cout << "  Gender (M: male, F: female):          ";
        goToXY(92, 15);
        getline(cin, gen);
    }
    TextColor(7);
    cout << "  Gender (M: male, F: female): " << gen << "                                 ";

    cin.ignore();
    goToXY(60, 15);
    TextColor(63);
    cout << "  Date of Birth (dd/mm/yyyy):                ";
    goToXY(91, 15);
    getline(cin, birth);
    while (!isValidDate(birth))
    {
        string message = "Invalid Date of Birth. Please retry.";
        string title = "Error";
        Message_Warning(message, title);
        goToXY(60, 15);
        cout << "  Date of Birth (dd/mm/yyyy):                ";
        goToXY(91, 15);
        getline(cin, birth);
    }
    TextColor(7);
    cout << "  Date of Birth (dd/mm/yyyy): " << birth << "                                 ";

    goToXY(60, 16);
    cout << "  Social ID:                ";
    goToXY(74, 16);
    getline(cin, socialID);
    TextColor(7);
    goToXY(60, 16);
    cout << "  Social ID: " << socialID << "                                 ";

    if (Check_Student(curClass, ID))
    {
        string message = "Student has already been added!!!\nDo you want to re-enter?";
        if (Message_YesNo(message, "Conitnue"))
            inputStudent(curClass);
        return;
    }
    //? Add here
    add1stYearStudents(curClass, ID, first, last, gen, birth, socialID); // add to class
}

//? Import student from file
void importStudent(Class *curClass)
{
    cout << "Please import the CSV file to folder New_Enrolled_Student.\n";
    cout << "Please enter file name(default is studentlist.csv, enter 0 to choose the default): ";
    string fileName = "studentlist.csv";
    string tmp;
    getline(cin, tmp);
    if (tmp != "0")
        fileName = tmp;
    // Get the file name in4 and access the file
    string path = "..\\Data_file" + separator + "New_Enrolled_Student" + separator + fileName;
    cout << path << endl;
    // check if the file exits
    ifstream studentList(path.c_str());
    if (!studentList.is_open())
    {
        cout << "File does not exit." << endl;
        importStudent(curClass);
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
        if (Check_Student(curClass, studentID))
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