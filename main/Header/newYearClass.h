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

extern const string separator;

void loadingFile(Year *&yearHead, int &numofYear);

void createSchoolYear(Year *&headYear, int yearStart);
void createClasses(Year *curYear, string className);

bool checkClass(Year *curYear, string className);
bool checkStudent(Class *curClass, string StudentID);
bool isLeap(int year);
bool isValidDate(const std::string& dateOfBirth);
bool isValidGender(const std::string& gender);

void addClass(Year *curYear, string ClassName);
void addStudenttoClass(Year *curYear);
void AddStudent_method(Class *curClass);
void add1stYearStudents(Class *addStudent, string studentID, string firstName, string lastName, string gender, string dateofBirth, string socialID);

void inputStudent(Class *classPtr);
void importStudent(Class *classPtr);
void importYear(Year *&yearHead, int &numofYear);
void importClass(Year *curYear, int yearStart);
