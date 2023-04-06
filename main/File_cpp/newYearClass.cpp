#include "../Header/newYearClass.h"

// 1. Create a school year (2020-2021, for example)
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
            switch (choice) {
                case 1: 
                    cout << "Enter start year: ";
                    cin >> yearStart;
                    createSchoolYear(headYear, yearStart);
                    break;
                case 2: 
                    cout << "Program ended." << endl;
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
        //! Reuse the curYear
        curYear = headYear;
        while (curYear->next)
            curYear = curYear->next;
        curYear->next = newYear;
    }
    cout << "Year " << yearStart << " has been added successfully." << endl;
}

// 2. Create several classes for 1st-year students. For example: class 20APCS1, class 20APCS2, class 20CLC1..., class 20CLC11, class 20VP...
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

//? khỏi & cx đc
void createClasses(Year *curYear, string className)
{
    if (!checkClass(curYear, className) && to_string(curYear->yearStart%100) == className.substr(0,2)) {
        cout << "Adding class " << className << "..." << endl;
    } else {
        cout << "Class " << className << " already exists or invalid class name. Please retry." << endl;

        cout << "Do you want to re-enter?\n1. Yes.\n2. No." << endl;
            int choice =-1;
            while (choice != 2) {
                cout << "Enter your choice: ";
                cin >> choice;
                switch (choice) {
                    case 1: 
                        cout << "Enter class name: ";
                        cin >> className;
                        createClasses(curYear, className);
                        break;
                    case 2: 
                        cout << "Program ended." << endl;
                        return;
                }
            }
    }

    //! Can check the syntax of a class name: kiểu lớp của năm 22 có dạng là 22 + .... giống là 22CLC02 22APCS2 kiểu z
    //? to_string(curYear->yearStart%100) so sánh với className.substr(0,2)
    Class *newClass = new Class;
    newClass->Name = className;
    newClass->StudentClass = nullptr;

    if (!curYear->Class)
        curYear->Class = newClass;
    else {
        Class *prevClass = curYear->Class;
        while (prevClass->next)
            prevClass = prevClass->next;
        prevClass->next = newClass;
        //? thêm cái link ngược về nữa
        prevClass->next->prev = prevClass;
    }
    cout << "Class " << className << " has been added successfully!" << endl;
}

// 3. Add new 1st year students to 1st-year classes.
// check if that student already exists.
bool checkStudent(Class *curClass, string StudentID)
{
    Student *curStudent = curClass->StudentClass;
    while (curStudent->next) {
        if (curStudent->ID == StudentID)
            return true;
        curStudent = curStudent->next;
    }
    //? Thiếu check thằng student cuối nè
    if (curStudent->ID == StudentID)
        return true;

    return false;
}

// access to the class
void addStudenttoClass(Year *curYear)
{
    string className;
    cout << "Enter class name: ";
    cin.ignore();
    getline(cin, className);

    if (!checkClass(curYear, className))
    {
        cout << "Class not found." << endl;
        return;
    } // check class id

    Class *curClass = curYear->Class;
    while (curClass->next)
    {
        if (curClass->Name == className)
            break;
        curClass = curClass->next;
    }
    AddStudent_method(curClass);
}

// choose add student method
void AddStudent_method(Class *curClass)
{
    int choice = -1;
    while (choice != 0) {
        cout << "ADD STUDENT" << endl;
        for (int i = 0; i < 88; i++)
            cout << "=";
        cout << endl;
        cout << "1. Add one by one.\n2. Import CSV file.\n0. Exit.\nEnter your choice: ";
        cin >> choice;
        cin.ignore();
        switch (choice)
        {
        case 1:
            inputStudent(curClass);
            break;

        case 2:
            importStudent(curClass);
            break;
        //? Này để thành vòng while để sai nhập lại cho tiện chớ nó văng
        case 0:
            cout << "Program ended." << endl;
            return;
        }
    }
}

// add student one by one
void add1stYearStudents(Class *addStudent, string studentID, string firstName, string lastName, string gender, string dateofBirth, string socialID)
{
    Student *curStudent = addStudent->StudentClass;

    Student *newStudent = new Student;
    // No, Student ID, First name, Last name, Gender, Date of Birth, and Social ID.
    newStudent->ID = studentID;
    newStudent->accStudent = new Account;

    newStudent->accStudent->role = 1; // set role for student
    newStudent->accStudent->firstName = firstName;
    newStudent->accStudent->lastName = lastName;
    newStudent->accStudent->Gender = gender;
    newStudent->accStudent->birth = dateofBirth;
    newStudent->accStudent->SocialID = socialID;

    if (!curStudent)
        addStudent->StudentClass = newStudent;
    else
    {
        while (curStudent->next) {
            curStudent = curStudent->next;
        }
        curStudent->next = newStudent;
        newStudent->prev = curStudent;
    }

    cout << "Student " << newStudent->accStudent->firstName << " " << newStudent->accStudent->lastName << " has been added to class " << addStudent->Name << endl;
}

// import student information
void inputStudent(Class *classPtr)
{
    string studentID, firstName, lastName, gender, dateofBirth, socialID;

    cout << "- Student information -\n";
    for (int i = 0; i < 88; i++)
        cout << "=";
    cout << endl;

    //! cin.ignore()
    cout << "Student ID: ";
    getline(cin, studentID);

    // cin.ignore();
    cout << "First Name: ";
    getline(cin, firstName);
    // cin.ignore();
    cout << "Last Name: ";
    getline(cin, lastName);
    // cin.ignore();
    cout << "Gender (M: male   F: female): ";
    cin >> gender;
    cin.ignore();
    cout << "Date of Birth (dd/mm/yyyy):";
    getline(cin, dateofBirth);
    // cin.ignore();
    cout << "Social ID: ";
    getline(cin, socialID);
    // cin.ignore();

    if (checkStudent(classPtr, studentID))
        cout << "This student has already been added. Please retry." << endl;
    else
        add1stYearStudents(classPtr, studentID, firstName, lastName, gender, dateofBirth, socialID);
}

void importStudent(Class *classPtr)
{
    //? Này mình nên mặc định cho ngta quăng file vô cái thư mục New-Enrolled_Student lun ấy nhờ, tại ngta đâu biết cái path của máy mình
    cout << "Please import the CSV file to folder New_Enrolled_Student." << endl;
    cout << "Please enter file name: ";
    string fileName;
    getline(cin, fileName);

    string path = "New_Enrolled_Student" + separator + fileName + ".csv";
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

    //? Cái này dùng sstream chi khó zị, mình biết trc đc số lượng thông tin thì mình cứ getline(studentList, line, ',') là đc rùi
    //? Còn thằng cuối cùng của dòng thì mình getline(studentList, line) là oke :))))

    while (getline(studentList, line))
    {
        // split the line by commas
        size_t position = 0;
        stringstream ss(line);
        string token;
        string fields[6];
        int i = 0;
        while ((position = line.find(delimiter)) != string::npos)
        {
            token = line.substr(0, position);
            fields[i] = token;
            line.erase(0, position + delimiter.length());
            i++;
            lineCount++;
        }

        // check if the line have the correct num of fields
        if (i != 5)
        {
            cout << "Invalid line format in CSV file. Please import another.\n";
        }

        // save the student information
        string studentID = fields[0];
        string firstName = fields[1];
        string lastName = fields[2];
        string gender = fields[3];
        string dateofBirth = fields[4];
        string socialID = fields[5];

        // add the student to class
        if (checkStudent(classPtr, studentID))
        {
            cout << "This student has already been added. Please retry." << endl;
        }
        else
        {
            add1stYearStudents(classPtr, studentID, firstName, lastName, gender, dateofBirth, socialID);
        }
    }
    cout << "Imported " << lineCount << " students to class " << classPtr->Name << ". \n";
}
