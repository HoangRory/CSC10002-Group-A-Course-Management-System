#pragma once
#include "proto.h"

//? Add new semester, new course and import student
Semester *AddSemester(Year *yearHead);
Course *AddNewCourse(Semester *semCurrent, Year *yearHead);
void ImportStudentFromFile(Course *courseCurrent);
void AddStudentByHand(Course *courseCurrent);
void AddingCourse(Semester *semCurrent, Year *yearHead);

Semester* Interface_New_Sem(Year *yearHead);

//? Initialize Modification
void initModify(Year *yearHead);
void RunModify(Year *yearHead, int opt);

//? Modifying
void modifySemester(Year *yearHead, int year, int sem);
void modifyCourse(Year *yearHead, int year);
void ChangeCourseInfo(Course *cour_cur);
void removeCourse(Year *yearHead, int year);

void addStudent(Course *courCurrent, string course_id);
void removeStudent(Course *courCurrent, string course_id);
void addRemoveStudent(Year *yearHead, int year);

//? Read Semester from file
Semester *Read_Sem(int year, int smt);
Semester *Read_All_Semester(int year);

void DeleteStudent(StudentCourse *&stud_head);
void DeleteCourse(Course *&course_head);
void DeleteSMT(Year *yearHead);

void OutCourse(Course *course_head, ofstream &ofs);
void Output(Year *yearHead);

//? View Course, Sync name from Account linked list
void SyncFullName(Year *yearHead, Account *accHead);
void SyncInForStudent(Year *yearHead, Account *accHead);
void SyncCourse(Year *yearHead);
void ViewCourse(Year *yearHead);
void ViewCourseInYear(Semester *semHead, int &i);
void ViewAllCourse(Year *yearHead);

//? Main
void StaffMain(Year *yearHead, Account *accHead, string &user, string &pass, int &role);
void MainMenu(Year *yearHead, Account *accHead, string &user, string &pass, int &role);
