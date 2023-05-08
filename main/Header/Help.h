#include "proto.h"

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
StudentCourse *find_StudentOfCourse(string ID, StudentCourse *stuCourseHead);

//////////////////////////////////////////////////////////////
//                     CACULATE-AMOUNT                      //
//////////////////////////////////////////////////////////////
double CaculateGPA_1_Student(double *&SBC, int n);
int amountStudentOfClass(Student *studentHead);
int amountStudentOfCourse(StudentCourse *studentHead);
int amountClass(Class *classHead);
int amountCourseOfStudent(CourseStudent *courseHead);

/////////////////////////////////////////////////////////////
//                     CHOOSE                              //
/////////////////////////////////////////////////////////////
Year *chooseYearbyOption_XY(Year *yearHead, int x, int y, int nOption_eachTime);
Class *chooseClassbyOption_XY(Class *classHead, int x, int y, int nOption_eachTime);
Class *chooseClass_inAllYear_byOption_XY(Year *yearHead, int x, int y, int nOption_eachTime);
Semester *chooseSemesterbyOption_XY(Semester *semHead, int x, int y, int nOption_eachTime);
Course *chooseCoursebyOption_XY(Course *courseHead, int x, int y, int nOption_eachTime);
Student *chooseStudentOfClass(Class *ChooseClass, int x, int y);
//////////////////////////////////////////////////////////
//                  CREATE                              //
//////////////////////////////////////////////////////////
string FormatMark(double Mark);
string getFirstChar(string name);
string createNameFile(int year, int no_smt, string course, string file, string type);
CourseStudent *CourseOfAClass_InChooseSem(Student *studentHead, Semester *ChooseSem);
void CreateSB_ofStudent_inClass(double *&SBC, CourseStudent *courseHead, Student *studentHead);
void createSBC_ofClass(double **&SBC, CourseStudent *courseHead, Student *studentHead, int Col, int Row);