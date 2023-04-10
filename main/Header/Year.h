#pragma once
#include "proto.h"

// #include <filesystem> //doc folder
#include <sstream>
#include <cstring>
#include <cctype>
#include <algorithm>

#ifdef _WIN32
#define PATH_SEPARATOR '\\'
#else
#define PATH_SEPARATOR '/'
#endif

extern const string separator;

//* Read year file
void loadingFile(Year *&yearHead, int &numofYear);
void importYear(Year *&yearHead, int &numofYear);
void addClass(Year *curYear, string ClassName);
void importClass(Year *curYear, int yearStart);

//* Output year
void Outyear(Year *yearHead);

//* New year
void createSchoolYear(Year *&headYear, int yearStart);
void Create_New_Classes(Year *newYear);
void ChooseClassToAdd(Year *curYear);
void Method(Class *curClass);
void inputStudent(Class *curClass);
void importStudent(Class *curClass);
void add1stYearStudents(Class *curClass, string ID, string first, string last, string gen, string birth, string socialID);
void NewAccount(Account *accHead, string ID, Account *accTmp);

//* Validate the input
bool checkClass(Year *curYear, string className);
bool Check_Student(Class *curClass, string studentID);
void CapitalClassName(string &name);
bool isLeap(int year);
bool isValidDate(const std::string &dateOfBirth);
bool isValidGender(const std::string &gender);

//* Interface
Year *RecoverFile();
void Interface_New_Year(year *yearHead);