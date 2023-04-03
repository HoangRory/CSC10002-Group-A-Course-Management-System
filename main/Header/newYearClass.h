/* #ifdef _BEGINNINGOFYEAR_H
#define _BEGINNINGOFYEAR_H */
#pragma once
#include "proto.h"

#include <sstream>
#include <cerrno>
#include <sys/stat.h>

/* #ifdef _WIN32
    #include <Windows.h>
    #define mkdir(a, b) CreateDirectory(a, NULL)
#else
    #include <sys/stat.h>
#endif */

void createSchoolYear(Year *&curYear, int yearStart);
void createClasses(Class *&Classes, int &setOfClass, string preClasses, ofstream &outFile);

bool checkClass(Class *curClass, string ClassID);
bool checkStudent(Year *schoolYear, string StudentID);

void inputStudent(Class *classPtr); //add student one by one
void importStudent(Class *classPtr, string studentList); //import csv file

void add1stYearStudents(Class *addStudent, string studentID, string firstName, string lastName, string gender, string dateofBirth, string socialID);
void addStudent1_CSV();

/* #endif */