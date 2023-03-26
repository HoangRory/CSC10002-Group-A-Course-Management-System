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

void add1stYearStudents(string ClassID) {
    Class *curClass = findClass(ID); //find the class

    //check class if it exists or not
    if (!curClass) {
        cout << "Class does not exit. Please try again." << endl;
        return;
    }

    Student *newStudent = new Student; //create a new student

    //get student information
    cout << "Enter student information.\n";
    cout << "Student ID: ";
    cin >> newStudent->ID;
    cout << ""
}