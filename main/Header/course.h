#pragma once
#include "../Header/proto.h"
//////////////////////////////////////////////////
//                   Readin                     //
//////////////////////////////////////////////////
void readScoreStudentCourse(ScoreBoardCourse &SBC, ifstream &in);
void readStudentCourse(StudentCourse *&studentHead, ifstream &in);
void readAllFileCourses(Semester *HeadSmt);

void importScoreBoardCourse(Semester *curSmt, StudentCourse *stuHead);

/////////////////////////////////////////////////
//                     OUT                     //
/////////////////////////////////////////////////
void outScoreboard_StudentCourse(ofstream &ofs, ScoreBoardCourse SBC);
void outStudentCourse(StudentCourse *stuHead, ofstream &ofs);

void exportListStudentCourse(Semester *curSmt);
////////////////////////////////////////////////////////
//                 Update                             //
////////////////////////////////////////////////////////
void updateSBC(Course *ChooseCourse, int x, int y, int x_cur, int y_cur); // x y là tọa độ của cái bảng
void UpdateStudentResult(Year *Yhead);

///////////////////////////////////////////////////////
//                  CREATE                           //
///////////////////////////////////////////////////////
string getFirstChar(string name);
string createNameFile(int year, int no_smt, string course, string file, string type);

CourseStudent *CourseOfAClass(Student *studentHead);
void CreateSB_ofStudent_inClass(double *&SBC, CourseStudent *courseHead, Student *studentHead);
void createSBC_ofClass(double **&SBC, CourseStudent *courseHead, Student *studentHead, int Col, int Row);

//////////////////////////////////////////////////////////
//                       CHECK                          //
//////////////////////////////////////////////////////////
bool isDouble(string str);
bool checkFile(string name);
CourseStudent *checkExistence_OfCourse(CourseStudent *courseCheck, CourseStudent *courseHead);

/////////////////////////////////////////////////////////////
//                      FIND                               //
/////////////////////////////////////////////////////////////

Student *findStudentbyID(string IDStudent, Year *Yhead);
StudentCourse *find_SBC_ofStudent(string ID, StudentCourse *stuCourseHead);

Course *findCourse_ofStudent_byOption(CourseStudent *courseHead, int option);

//////////////////////////////////////////////////////////////
//                     CACULATE-AMOUNT                      //
//////////////////////////////////////////////////////////////
double CaculateGPA_1_Student(double *&SBC, int n);

int amountOfCourse(Course *courseHead);

int amountStudentOfClass(Student *studentHead);
int amountCourseOfClass(CourseStudent *courseHead);

int amountYear(Year *yearHead);
int amountClass(Class *classHead);
int amountCourse(Course *courseHead);
int amountCourseOf_aStudent(CourseStudent *courseHead);

/////////////////////////////////////////////////////////////
//                     CHOOSE                              //
/////////////////////////////////////////////////////////////

Year *chooseYearbyOption_XY(Year *yearHead, int x, int y, int nOption_eachTime);
Class *chooseClassbyOption_XY(Class *classHead, int x, int y, int nOption_eachTime);
Semester *chooseSemesterbyOption_XY(Semester *semHead, int x, int y, int nOption_eachTime);
Course *chooseCoursebyOption_XY(Course *courseHead, int x, int y, int nOption_eachTime);

///////////////////////////////////////////////////////////
//                      VIEW                             //
///////////////////////////////////////////////////////////

int view_chooseOption(string *arrOption, int nOption, string title);
// for staff //
// task 15 //
void ViewClass(Year *yearHead);
// task 16 //
void Interface_ViewStudentClass(Year *yearHead);
void ViewStudentClass(Class *ChooseClass, int x, int y);
// task 17 //
// void ViewCourse(Year *yearHead);
// task 18 //
void Interface_ViewStudentCourse(Year *yearHead);
void ViewStudentCourse(Course *ChooseCourse, int x, int y);
// task 21 //
void viewScoreBoardCourse(Course *courseHead);
// task 23 //
void viewScoreboardClass(Class *Class);

// for student //
// task 14 //
void ViewCoursesOfAStudent(Account *accHead, Year *yearHead);
// task 24 //
void ViewScoreboard(Account *accHead, Course *courseHead);
