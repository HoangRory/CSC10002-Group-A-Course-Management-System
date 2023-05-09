#pragma once
#include "proto.h"

//? Add new semester, new course and import student
void New_Stuff(Year *yearHead, Account *accHead);

Semester *AddSemester(Year *yearHead);

Course *AddNewCourse(Semester *semCurrent, Year *yearHead);
void ImportStudentFromFile(Course *courseCurrent);
void AddStudentByHand(Course *courseCurrent);
void AddingCourse(Semester *semCurrent, Year *yearHead);

Semester *Interface_New_Sem(Year *yearHead);

//? Initialize Modification
void initModify(Year *yearHead);
void RunModify(Year *yearHead, int opt);

//? Modifying
void modifySemester(Year *yearHead);
void modifyCourse(Year *yearHead);
void ChangeCourseInfo(Course *cour_cur);
void removeCourse(Year *yearHead);

void addStudent(Course *courCurrent, string course_id);
void removeStudent(Course *courCurrent, string course_id);
void addRemoveStudent(Year *yearHead);

//? Read Semester from file
Semester *Read_Sem(int year, int smt);
Semester *Read_All_Semester(int year);

void DeleteStudent(StudentCourse *&stud_head);
void DeleteCourse(Course *&course_head);
void DeleteSMT(Year *yearHead);

void OutCourse(Course *course_head, ofstream &ofs);
void Output(Year *yearHead);

//? Sync name from Account linked list
void SyncFullName(Year *yearHead, Account *accHead);
void SyncInForStudent(Year *yearHead, Account *accHead);
void SyncCourse(Year *yearHead);

//? View course
void ViewCourse(Year *yearHead);
Course *Part_Of_Course(Course *&curCourse, Semester *&sem_cur);
// void ViewCourseInYear(Semester *semHead);

//? Main
void Student_Main(Year *yearHead, Account *accHead, Student *student_cur, string &user, string &pass, int &role);
void Staff_Main(Year *yearHead, Account *accHead, string &user, string &pass, int &role);
void Main_Menu(Year *yearHead, Account *accHead, string &user, string &pass, int &role);
