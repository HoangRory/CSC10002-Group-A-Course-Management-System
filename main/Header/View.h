#pragma once

#include "proto.h"

// for staff
void ViewStudentsClass(Year *yearHead);
void ViewStudentCourse(Year *yearHead);
void ViewCourse(Year *yearHead);
void ViewClass(Year* yearHead);

// for student 
void ViewCoursesOfAStudent(Account *accHead, Course *courseHead);
void ViewScoreboard(Account *accHead, Course *courseHead);