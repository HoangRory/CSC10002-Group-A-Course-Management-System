#include "../Header/newYearClass.h"

//1. Create a school year (2020-2021, for example)
void createSchoolYear(Year *&headYear, int yearStart) {
    Year *curYear = headYear;
    while (curYear) {
        if (curYear->yearStart == yearStart) {
            cout << "Year " << yearStart << " already exists." << endl;
            return;
        }
        curYear = curYear->next;
    }

    Year *newYear = new Year;
    newYear->yearStart = yearStart;

    if (!headYear) headYear = newYear;
    else {
        Year *lastYear = headYear;
        while (lastYear->next) lastYear = lastYear->next;
        lastYear->next = newYear;
    }
    cout << "Year " << yearStart << " has been added successfully." << endl;
}

//2. Create several classes for 1st-year students. For example: class 20APCS1, class 20APCS2, class 20CLC1..., class 20CLC11, class 20VP...
bool checkClass(Year *curYear, string className) {
    Class *curClass = curYear->Class;
    while(curClass) {
        if (curClass->Name == className) return true;
        curClass = curClass->next;
    }
    return false;
}

void createClasses(Year *&curYear, string className) {
    if (checkClass(curYear, className)) {
        cout << "Class " << className << " already exists." << endl;
        return;
    }

    Class *newClass = new Class;
    newClass->Name = className;
    newClass->StudentClass = nullptr;
    
    if (!curYear->Class) curYear->Class = newClass;
    else {
        Class *prevClass = curYear->Class;
        while (prevClass->next) prevClass = prevClass->next;
        prevClass->next = newClass;
    }
    cout << "Class " << className << " has been added successfully!" << endl;
}

//3. Add new 1st year students to 1st-year classes.
//check if that student already exists.
bool checkStudent(Class *curClass, string StudentID) {
    Student *curStudent = curClass->StudentClass;
    while(curStudent->next) {
        if (curStudent->ID == StudentID) return true;
        curStudent = curStudent->next;
    }
    return false;
}

//access to the class
void addStudenttoClass(Year *curYear) {
    string className;
    cout << "Enter class name: ";
    getline(cin, className);

    if (!checkClass(curYear, className)) {
        cout << "Class not found." << endl;
        return;
    } // check class id

    Class *curClass = curYear->Class;
    while (curClass->next) {
        if (curClass->Name == className) break;
        curClass = curClass->next;
    }
    AddStudent_method(curClass);

}

//choose add student method
void AddStudent_method(Class *curClass) {
    int choice = 0;
    cout << "ADD STUDENT" << endl;
    for (int i = 0; i < 88; i++) {
        cout << "=";
    }
    cout << endl;
    cout << "1. Add one by one.\n2. Import CSV file.\nEnter your choice: ";
    cin >> choice;
    cin.ignore();
    switch (choice) {
    case 1:
        inputStudent(curClass);
        break;
    
    case 2:
        importStudent(curClass);
        break;

    default:
        cout << "Invalid choice." << endl;
        break;
    }
}

//add student one by one
void add1stYearStudents(Class *addStudent, string studentID, string firstName, string lastName, string gender, string dateofBirth, string socialID) {
    Student *curStudent = addStudent->StudentClass;

    Student *newStudent = new Student;
    //No, Student ID, First name, Last name, Gender, Date of Birth, and Social ID.
    newStudent->ID = studentID;
    newStudent->accStudent = new Account;

    newStudent->accStudent->role = 1; //set role for student
    newStudent->accStudent->firstName = firstName;
    newStudent->accStudent->lastName = lastName;
    newStudent->accStudent->Gender = gender;
    newStudent->accStudent->birth = dateofBirth;
    newStudent->accStudent->SocialID = socialID;

    if (!curStudent) {
        addStudent->StudentClass = newStudent;
    } else {
        while (curStudent->next) {
            curStudent = curStudent->next;
        }
        curStudent->next = newStudent;
        newStudent->prev = curStudent;
    }

    cout << "Student " << newStudent->accStudent->firstName << " " << newStudent->accStudent->lastName << " has been added to class " << addStudent->Name << endl;
}

//import student information
void inputStudent(Class *classPtr) {
    string studentID;
    string firstName;
    string lastName;
    string gender;
    string dateofBirth;
    string socialID;

    cout << "- Student information -\n";
    for (int i = 0; i < 88; i++) {
        cout << "=";
    }
    cout << endl;

    cout << "Student ID: ";
    getline(cin, studentID);

    //cin.ignore();
    cout << "First Name: ";
    getline(cin, firstName);
    //cin.ignore();
    cout << "Last Name: ";
    getline(cin, lastName);
    //cin.ignore();
    cout << "Gender (M: male   F: female): ";
    cin >> gender;
    cin.ignore();
    cout << "Date of Birth (dd/mm/yyyy):";
    getline(cin, dateofBirth);
    //cin.ignore();
    cout << "Social ID: ";
    getline(cin, socialID);
    //cin.ignore();

    if (checkStudent(classPtr, studentID)) {
        cout << "This student has already been added. Please retry." << endl;
    } else {
        add1stYearStudents(classPtr, studentID, firstName, lastName, gender, dateofBirth, socialID);
    }
}

void importStudent(Class *classPtr) {
    string CSV_path = "";
    cout << "Enter file path: ";
    getline(cin, CSV_path);

    //check if the file exits
    ifstream studentList(CSV_path.c_str());
    if (!studentList.is_open()) {
        cout << "File does not exit." << endl;
        return;
    }

    //read CSV file line by line
    string line;
    string delimiter = ",";
    int lineCount = 0;
    while (getline(studentList, line)) {
        //split the line by commas
        size_t position = 0;
        stringstream ss(line);
        string token;
        string fields[6];
        int i = 0;
        while ((position = line.find(delimiter)) != string::npos) {
            token = line.substr(0, position);
            fields[i] = token;
            line.erase(0, position + delimiter.length());
            i++;
            lineCount++;
        }

        //check if the line have the correct num of fields
        if (i != 5) {
            cout << "Invalid line format in CSV file. Please import another.\n";
        }

        //save the student information
        string studentID = fields[0];
        string firstName = fields[1];
        string lastName = fields[2];
        string gender = fields[3];
        string dateofBirth = fields[4];
        string socialID = fields[5];

        //add the student to class
        if (checkStudent(classPtr, studentID)) {
            cout << "This student has already been added. Please retry." << endl;
        } else {
            add1stYearStudents(classPtr, studentID, firstName, lastName, gender, dateofBirth, socialID);
        }
    }
    cout << "Imported " << lineCount << " students to class " << classPtr->Name << ". \n";
}