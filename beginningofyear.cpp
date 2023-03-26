#include "proto.h"

void createSchoolYear(Year *&curYear, int yearStart) {
    Year *newYear = new Year;
    newYear->yearStart = yearStart;
    // add the new year to the beginning of the linked list of years
    newYear->next = curYear;
    curYear = newYear; //cur point to the head (current year)
}

void createClasses(Class *&Classes, string preClasses) {
    Class *newClass = new Class;
    newClass->Name = preClasses;
    // add the new class to the beginning of the linked list of classes
    newClass->next = Classes; 
    Classes = newClass; //classes point to the head of the linked list
}

bool findClass(Class *curClass, string ClassID) {
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

void add1stYearStudents(Class *addStudent) {
    string ClassID;

    Class *curClass = addStudent;
    cout << "Enter Class name: ";
    getline(cin, ClassID);

    if (!findClass(curClass, ClassID)) {
        cout << "Class not found." << endl;
        return;
    } //check student id

    Student *newStudent = new Student;
    //No, Student ID, First name, Last name, Gender, Date of Birth, and Social ID.
    cout << "- Student information -\n";
    cout << "Student ID: ";
    getline(cin, newStudent->ID);
    cin.ignore();

    if (!checkStudent) {
        cout << "This student has already been added. Please retry." << endl;
        return;
    }

    newStudent->accStu->role = 1;
    cout << "First Name: ";
    getline(cin, newStudent->accStu->firstName);
    cin.ignore();
    cout << "Last Name: ";
    getline(cin, newStudent->accStu->lastName);
    cin.ignore();
    cout << "Gender: (M: male   F: female)";
    cin >> newStudent->accStu->Gender;
    cin.ignore();
    cout << "Date of Birth: (yy/mm/dd)";
    getline(cin, newStudent->accStu->DateofBirth);
    cin.ignore();
}