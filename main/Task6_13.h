#pragma once

void Read_SMT();
void Read_multi_SMT();
void DeleteStudent(StudentCourse *stud_head);
void DeleteCourse(Course *course_head);
void DeleteSMT();
void OutStudent(StudentCourse *stud_head, ofstream &ofs);
void OutCourse(Course *course_head, ofstream &ofs);
void Output();

void AddSemester();