#pragma once

#include "proto.h"

void Read_SMT(Semester *&semHead, int y, int smt);
void Read_multi_SMT(Semester *&semHead, int yr, int num_year, int num_smt);
void SyncFullName(Semester *semHead, Account *accHead);

void DeleteStudent(StudentCourse *&stud_head);
void DeleteCourse(Course *&course_head);
void DeleteSMT(Semester *&semHead);

void OutStudent(StudentCourse *stud_head, ofstream &ofs);
void OutCourse(Course *course_head, ofstream &ofs);
void Output(Semester *semHead);

void AddSemester(Semester *semHead);
void AddCourse(Semester *semHead, Semester *&sem);
void AddStudent(Course *&new_course, Semester *sem);

void viewCourse(Semester *semHead);
void modifyCourse(Semester *semHead, string id);
void modifySemester(Semester *semHead, int year, int sem);

void addStudent(Semester *semHead, string id);
void removeStudent(Semester *semHead, string id);
void addRemoveStudent(Semester *semHead, string id);

void deleteCourse(Semester *semHead, string id);

void initModify(Semester *&semHead);
