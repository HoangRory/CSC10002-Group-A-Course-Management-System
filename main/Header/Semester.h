#pragma once
#include "proto.h"

//? Add new semester, new course and import student
Semester *AddSemester(Semester *&semHead);
Course *AddCourse(Semester *semCurrent);
void ImportStudentFromFile(Course *courseCurrent);
void AddStudentByHand(Course *courseCurrent);
void AddingCourse(Semester *semCurrent);
void Interface_New_Sem(Semester *&semHead);

//? Initialize Modification
void ShowConsoleCursor(bool showFlag);
void initModify(Semester *&semHead);
void RunModify(Semester *&semHead, int opt);

//? Modifying
void modifySemester(Semester *semHead, int year, int sem);
void modifyCourse(Semester *semHead, int year);
void ChangeCourseInfo(Course *cour_cur);
void deleteCourse(Semester *semHead, int year);
void addStudent(Course *courCurrent, string course_id);
void removeStudent(Course *courCurrent, string course_id);
void addRemoveStudent(Semester *semHead, int year);

//? Read Semester from file
void Read_SMT(Semester *&semHead, int y, int smt);
void Read_multi_SMT(Semester *&semHead, int yr, int num_year, int num_smt);

void DeleteStudent(StudentCourse *&stud_head);
void DeleteCourse(Course *&course_head);
void DeleteSMT(Semester *&semHead);

void OutCourse(Course *course_head, ofstream &ofs);
void Output(Semester *semHead);

//? View Course, Sync name from Account linked list
void SyncFullName(Semester *semHead, Account *accHead);
void viewCourse(Semester *semHead);
void StaffMain(Semester *&semHead);
void NewSemesterMain(Semester *&semHead, int yr, int num_year, int num_smt, Account *accHead, int role);