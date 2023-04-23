#pragma once
#include "proto.h"

// #include <filesystem> //doc folder


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
void NewAccount(Account *accHead, string ID, Account *accTmp);

//* Delete the year linked list
void DeleteYear(Year *&yearHead);

//* New year
void createSchoolYear(Year *&headYear, int yearStart);
void Create_New_Classes(Year *newYear);

void ChooseClassToAdd(Year *curYear);
void Method(Class *curClass);

void inputStudent(Class *curClass);
void importStudent(Class *curClass);

void add1stYearStudents(Class *curClass, string ID, string first, string last, string gen, string birth, string socialID);

//* Validate the input
void CapitalClassName(string &name);
bool isValidStudentID(string studentID, string year);
bool checkYear(Year *curYear, int year);
bool checkClass(Year *curYear, string className);
bool Check_Student(Class *curClass, string studentID);
bool isLeap(int year);
bool isValidDate(const string &dateOfBirth);
bool isDay(string day);
bool isSession(string ss);

bool isValidGender(const string &gender);
bool isValidYear(string year);

void SeparateName(string full, string &first, string &last);
void Draw_In_Stud(string &ID, string &first, string &last, string &gen, string &birth, string &socialID, string yr);

//* Interface
Year *RecoverFile();
void Interface_New_Year(Year *yearHead);
void Show_Year_List(Year *yearHead);
int Get_CheckFormat_Existed_Year(Year *yearHead);
