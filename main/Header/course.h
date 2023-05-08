#pragma once
#include "../Header/proto.h"
#include "../Header/Help.h"
#include "../Header/Semester.h"
#include "../Header/Login.h"
#include "../Header/Utility.h"
#include "../Header/Class.h"
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

///////////////////////////////////////////////////////////
//                INTERFACE - VIEW                       //
///////////////////////////////////////////////////////////
//? for staff view
//? student
void Interface_ViewStudentCourse(Year *yearHead);           //? task 18
void ViewStudentCourse(Course *ChooseCourse, int x, int y); //? task 18
//? scoreboard
void Interface_ViewScoreBoardCourse(Year *ChooseCourse);       //? task 21
void ViewScoreBoardCourse(Course *ChooseCourse, int x, int y); //? task 21

//?
void Interface_ViewCourseOfAStudent(Year *yearHead);
void ViewCoursesOfAStudent(Account *accHead, Year *yearHead);
//? View Menu
void Menu_Import_Export(Year *yearHead);
void Menu_Staff_View(Year *yearHead);
void Menu_ScoreBoard_View(Year *yearHead);
void Menu_ListStudent_View(Year *yearHead);
void Menu_ListCourse_View(Year *yearHead);