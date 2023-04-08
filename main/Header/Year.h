#pragma once

#include "proto.h"

//? Read-in the class from each year
Year *Read_Year_Class(int year);
Year *Read_Multi_year();
void DeleteYear(Year *&yearHead);

//? Create a new school year
Year *Create_NewYear(Year *yearHead);
bool checkClass(Year *curYear, string className);
void Create_New_Classes(Year *newYear);
bool Check_Student(Class *curClass, string studentID);
void CapitalClassName(string &name);

void addStudentToClass(Year *curYear);
void Method(Class *curClass);
void inputStudent(Class *curClass);
void add1stYearStudents(Class* curClass, string ID, string first, string last, string gen, string birth, string socialID);

void NewAccount(Account* accHead, string ID, Account* accTmp);
