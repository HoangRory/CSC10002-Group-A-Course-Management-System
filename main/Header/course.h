#pragma once
#include "../Header/proto.h"
///////////////////////////////////////////////////////////
//                   Readin                              //
///////////////////////////////////////////////////////////
void readScoreStudentCourse(ScoreBoardCourse &SBC, ifstream &in);
void readStudentCourse(StudentCourse *&studentHead, ifstream &in);
void readAllFileCourses(Semester *HeadSmt);
void importScoreBoardCourse(Year *yearHead);

///////////////////////////////////////////////////////////
//                     OUT                               //
///////////////////////////////////////////////////////////
void outScoreboard_StudentCourse(ofstream &ofs, ScoreBoardCourse SBC);
void outStudentCourse(StudentCourse *stuHead, ofstream &ofs);
void exportListStudentCourse(Year *yearHead);

//////////////////////////////////////////////////////////
//                 Update                               //
//////////////////////////////////////////////////////////
void updateSBC(Course *ChooseCourse, int x, int y, int x_cur, int y_cur); // x y là tọa độ của cái bảng
void UpdateStudentResult(Year *Yhead);

//////////////////////////////////////////////////////////
//                  CREATE                              //
//////////////////////////////////////////////////////////
string FormatMark(double Mark);
string getFirstChar(string name);
string createNameFile(int year, int no_smt, string course, string file, string type);
CourseStudent *CourseOfAClass_InChooseSem(Student *studentHead, Semester *ChooseSem);
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
int amountStudentOfClass(Student *studentHead);
int amountCourseOfClass(CourseStudent *courseHead);
int amountStudentOfCourse(StudentCourse *studentHead);
int amountYear(Year *yearHead);
int amountClass(Class *classHead);
int amountCourse(Course *courseHead);
int amountCourseOf_aStudent(CourseStudent *courseHead);

/////////////////////////////////////////////////////////////
//                     CHOOSE                              //
/////////////////////////////////////////////////////////////
Year *chooseYearbyOption_XY(Year *yearHead, int x, int y, int nOption_eachTime);
Class *chooseClassbyOption_XY(Class *classHead, int x, int y, int nOption_eachTime);
Class *chooseClass_inAllYear_byOption_XY(Year *yearHead, int x, int y, int nOption_eachTime);
Semester *chooseSemesterbyOption_XY(Semester *semHead, int x, int y, int nOption_eachTime);
Course *chooseCoursebyOption_XY(Course *courseHead, int x, int y, int nOption_eachTime);
Student *chooseStudentOfClass(Class *ChooseClass, int x, int y);

///////////////////////////////////////////////////////////
//                INTERFACE - VIEW                       //
///////////////////////////////////////////////////////////
//? for staff view
//? student
void Interface_ViewStudentClass(Year *yearHead);            //? task 16
void ViewStudentClass(Class *ChooseClass, int x, int y);    //? task 16
void Interface_ViewStudentCourse(Year *yearHead);           //? task 18
void ViewStudentCourse(Course *ChooseCourse, int x, int y); //? task 18
//? scoreboard
void Interface_ViewScoreBoardCourse(Year *ChooseCourse);                   //? task 21
void ViewScoreBoardCourse(Course *ChooseCourse, int x, int y);             //? task 21
void Interface_ViewScoreBoardClass(Year *yearHead);                        //? task 23
void ViewScoreboardClass(Class *Class, Semester *ChooseSem, int x, int y); //? task 23
//? view all class
void ViewClass(Year *yearHead); //? task 15

//?
void Interface_Import_Export(Year *yearHead);
void Interface_ViewCourseOfAStudent(Year *yearHead);
//? for student
void ViewCoursesOfAStudent(Account *accHead, Year *yearHead);
void Interface_ViewCoursesOfUser(Student *student_cur, Year *yearHead); // task 14
void ViewCoursesOfUser(Student *student_cur, Course *courseHead);       //? task 14
void Interface_ViewScoreBoardOfUser(Student *student_cur, Year *yearHead);
void ViewScoreboard(Account *accHead, Course *courseHead); //? task 24

//? View Menu
void Staff_View(Year *yearHead);
void ScoreBoard_View(Year *yearHead);
void ListStudent_View(Year *yearHead);
void ListCourse_View(Year *yearHead);