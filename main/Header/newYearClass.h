#pragma once
#include "proto.h"

#include <sstream>
//#include <filesystem> //doc folder
#include <cstring>
#include <cctype>
#include <algorithm>

#ifdef _WIN32
#define PATH_SEPARATOR '\\'
#else
#define PATH_SEPARATOR '/'
#endif

/* void createSchoolYear(Year *&curYear, int yearStart);
void createClasses(Class *&Classes, int &setOfClass, string preClasses, ofstream &outFile);

bool checkClass(Class *curClass, string ClassID);
bool checkStudent(Year *schoolYear, string StudentID);

void inputStudent(Class *classPtr); //add student one by one
void importStudent(Class *classPtr, string studentList); //import csv file

void add1stYearStudents(Class *addStudent, string studentID, string firstName, string lastName, string gender, string dateofBirth, string socialID);
void addStudent1_CSV(); */

std::string path_separator(2, PATH_SEPARATOR);

void addClass(Year *curYear, string ClassName);

void importYear(Year *&yearHead, int &numofYear);
void importClass(Year *curYear, int yearStart);
void importClass1(Year *curYear, int yearStart);