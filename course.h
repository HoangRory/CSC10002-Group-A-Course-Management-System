#include "proto.h"
Year* findYear(int yearStart);
Semester* findSemester (int no_smt, Semester *SmtHead);
Course* findCourse(string nameOrID, Course *CourseHead);
string createNameFile(int year, int no_smt, string course, string file, string type);

void readScoreStudentCourse(ScoreBoardCourse &SBC);
void readStudentCourse(StudentCourse *&studentHead);
void readAllFileCourses();

void exportInforStudent(StudentCourse *stuHead);
void exportListStudentCourse();

void exportScoreCourseStudent(ScoreBoardCourse ScoreBoardCourse);