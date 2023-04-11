#pragma once
#include "proto.h"
bool checkFile(string name);
Year* findYear(int yearStart, Year* YrHead);
Semester* findSemester (int no_smt, Semester *SmtHead);
Course* findCourse(string nameOrID, Course *CourseHead);

string createNameFile(int year, int no_smt, string course, string file, string type);

void importScoreBoardCourse(Semester * curSmt, StudentCourse *stuHead);

void readScoreStudentCourse(ScoreBoardCourse &SBC, ifstream &in);
void readStudentCourse(StudentCourse *&studentHead, ifstream &in);
void readAllFileCourses(Year *Yhead);

void exportInforStudent(StudentCourse *stuHead, ofstream &out);
void exportListStudentCourse(Semester *curSmt);

void exportScoreCourseStudent(ScoreBoardCourse ScoreBoardCourse);


int view_chooseOption(string *arrOption, int nOption); //task 21 & 22
//task 21
void viewScoreCourseStudent(ScoreBoardCourse SBC);
int AmountOfCourse(Course *courseHead);
Course* findCoursebyIndexOption(Course *courseHead, int index);
void viewScoreBoardCourse(Course *courseHead); 

//task 22
Student* findStudentbyID(string IDStudent, Year *Yhead);
Course* findCoursebyName_ID(string CourseName_ID, Year *Yhead);
StudentCourse* find_SBC(string ID, StudentCourse *stuCourseHead);
void enterMark(double &Mark);
bool updateMark(ScoreBoardCourse &SCB, string Selection);
void updateSCB (string ID, StudentCourse *stuCourseHead);
void UpdateStudentResult(Year *Yhead) ;


//task 23
CourseStudent* checkExistence_OfCourse(CourseStudent *courseCheck, CourseStudent *courseHead);
CourseStudent* CourseOfAClass (Student *studentHead);
int CaculateAmountStudentOfClass(Student *studentHead);
int CaculateAmountCourseOfClass(CourseStudent *courseHead);
void importSB_ofStudent_inClass(double *&SBC, CourseStudent *courseHead, Student *studentHead);
double CaculateGPA_1_Student(double *&SBC, int n); 
void createSCB_ofClass(double **&SCB, CourseStudent *courseHead, Student *studentHead, int Col, int Row );
void viewAllFinalMark_ofStudent(double *SCB, int Col);
void viewScoreboardClass(Class *Class);


void deleteAllCourse(Year *Yhead);