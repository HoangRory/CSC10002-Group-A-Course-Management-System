#pragma once
#include "proto.h"
bool checkFile(string name);
Year* findYear(int yearStart, Year* YrHead);
Semester* findSemester (int no_smt, Semester *SmtHead);
Course* findCourse(string nameOrID, Course *CourseHead);
ScoreBoardCourse find_SBC(string ID, StudentCourse *stuCourseHead);

string createNameFile(int year, int no_smt, string course, string file, string type);

void readScoreStudentCourse(ScoreBoardCourse &SBC, ifstream &in);
void readStudentCourse(StudentCourse *&studentHead, ifstream &in);
void readAllFileCourses(Year *YHead);

void exportInforStudent(StudentCourse *stuHead, ofstream &out);
void exportListStudentCourse(Semester *curSmt, ofstream &out);

void exportScoreCourseStudent(ScoreBoardCourse ScoreBoardCourse);

//task 23
CourseStudent* checkExistence_OfCourse(CourseStudent *courseCheck, CourseStudent *courseHead);
CourseStudent* CourseOfAClass (Student *studentHead);
int CaculateAmountStudentOfClass(Student *studentHead);
int CaculateAmountCourseOfClass(CourseStudent *courseHead);
void importSCB_ofStudent(double *&SCB, CourseStudent *courseHead, Student *studentHead);
double CaculateGPA_1_Student(double *&SCB, int n); 
void createSCB_ofClass(double **&SCB, CourseStudent *courseHead, Student *studentHead, int Col, int Row );
void viewAllFinalMark_ofStudent(double *SCB, int Col);
void viewScoreboardClass(Class *Class);


void deleteAllCourse(Year *Yhead);