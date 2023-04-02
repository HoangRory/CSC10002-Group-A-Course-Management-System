#include "proto.h"
#include "beginningofyear.h"

void createSchoolYear(Year *&curYear, int yearStart) {
    Year *newYear = new Year;
    newYear->yearStart = yearStart;

    // Add the new year to the beginning of the linked list of years
    newYear->next = curYear;
    curYear = newYear;

    // Create a new folder for the year
 // Create a new directory with the name of yearStart
    string folderName = to_string(yearStart) + "_" + to_string(yearStart + 1);
    const int dir_err = mkdir(folderName.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    if (dir_err == -1) {
        cerr << "Error creating directory: " << strerror(errno) << endl;
    } else {
        cout << "Directory created successfully!" << endl;
    }
}

void createClasses(Class *&Classes, string preClasses) {
    Class *newClass = new Class;
    newClass->Name = preClasses;
    // add the new class to the beginning of the linked list of classes
    newClass->next = Classes; 
    Classes = newClass; //classes point to the head of the linked list
}

bool checkClass(Class *curClass, string ClassID) {
    while(curClass) {
        if (curClass->Name == ClassID) return true;
        else curClass = curClass->next;
    }

    return false;
}

bool checkStudent(Year *schoolYear, string StudentID) {
    for(Class* curClass = schoolYear->Class; curClass; curClass = curClass->next) {
        for (Student *curStudent = schoolYear->Class->StudentClass; curStudent; curStudent = curStudent->next) {
            if (curStudent->ID == StudentID) {
                return true;
            }
        }
    }

    return false;
}

void inputStudent(Class *classPtr) { //input information of a student (add one by one)
    string studentID;
    string firstName;
    string lastName;
    string gender;
    string dateofBirth;
    string socialID;

    cout << "- Student information -\n";
    cout << "Student ID: ";
    getline(cin, studentID);
    //cin.ignore();
    cout << "First Name: ";
    getline(cin, firstName);
    //cin.ignore();
    cout << "Last Name: ";
    getline(cin, lastName);
    //cin.ignore();
    cout << "Gender: (M: male   F: female)";
    cin >> gender;
    //cin.ignore();
    cout << "Date of Birth: (yy/mm/dd)";
    getline(cin, dateofBirth);
    //cin.ignore();
    cout << "Social ID: ";
    getline(cin, socialID);
    //cin.ignore();

    add1stYearStudents(classPtr, studentID, firstName, lastName, gender, dateofBirth, socialID);

}

void add1stYearStudents(Class *addStudent, string studentID, string firstName, string lastName, string gender, string dateofBirth, string socialID) {
    string ClassID;

    Class *curClass = addStudent;
    cout << "Enter Class name: ";
    getline(cin, ClassID);

    if (!checkClass(curClass, ClassID)) {
        cout << "Class not found." << endl;
        return;
    } //check class id

    Student *newStudent = new Student;
    //No, Student ID, First name, Last name, Gender, Date of Birth, and Social ID.
    newStudent->ID = studentID;

    if (!checkStudent) {
        cout << "This student has already been added. Please retry." << endl;
        return;
    }

    newStudent->accStudent->role = 1; //set role for student
    newStudent->accStudent->firstName = firstName;
    newStudent->accStudent->lastName = lastName;
    newStudent->accStudent->Gender = gender;
    newStudent->accStudent->birth = dateofBirth;
    newStudent->accStudent->SocialID = socialID;

    curClass->StudentClass = newStudent;
    curClass->StudentClass = curClass->StudentClass->next;

    if (!addStudent->StudentClass) {
        addStudent->StudentClass = newStudent;
    } else {
        Student *curStudent = addStudent->StudentClass;

        while (curStudent->next != nullptr) {
            curStudent = curStudent->next;
        }
        curStudent->next = newStudent;
        newStudent->prev = curStudent;
    }

    cout << "Student " << newStudent->accStudent->firstName << " " << newStudent->accStudent->lastName << " has been added to class " << curClass->Name << endl;
}

void importStudent(Class *classPtr, string studentList) {
    //check if the file exits
    ifstream file(studentList.c_str());
    if (!file.is_open()) {
        cout << "File does not exit." << endl;
        return;
    }

    //read CSV file line by line
    string line;
    string delimiter = ",";
    int lineCount = 0;
    while (getline(file, line)) {
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
        }

        //check ì the line have the correct num of fields
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
        add1stYearStudents(classPtr, studentID, firstName, lastName, gender, dateofBirth, socialID);
    }
    cout << "Imported " << lineCount << " students to class " << classPtr->Name << ". \n";
}