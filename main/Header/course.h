#pragma once
#include "proto.h"
bool checkFile(string name);
Year* findYear(int yearStart, Year* YrHead);
Semester* findSemester (int no_smt, Semester *SmtHead);
Course* findCourse(string nameOrID, Course *CourseHead);
string createNameFile(int year, int no_smt, string course, string file, string type);

void readScoreStudentCourse(ScoreBoardCourse &SBC, ifstream &in);
void readStudentCourse(StudentCourse *&studentHead, ifstream &in);
void readAllFileCourses(Semester *smtHead);

void exportInforStudent(StudentCourse *stuHead, ofstream &out);
void exportListStudentCourse(Semester *curSmt, ofstream &out);

void exportScoreCourseStudent(ScoreBoardCourse ScoreBoardCourse);