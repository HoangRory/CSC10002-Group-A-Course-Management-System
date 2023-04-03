#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <windows.h>
#include <conio.h>

#define RED 4
#define YELLOW 6
#define WHITE 7

#define VK_UP 72
#define VK_DOWN 80
#define ENTER 13

using namespace std;

struct Account
{
    string username = "", password = "";
    string firstName = "", lastName = "";
    string Gender; // M is male, F is female
    string SocialID;
    string birth;
    int role; // 1 student, 2 teacher, 3 staff.
    Account *next = nullptr, *prev = nullptr;
};

struct ScoreBoardCourse
{
    double totalMark = 0, finalMark = 0, midMark = 0, otherMark = 0;
};

// student của một course
struct StudentCourse
{
    string ID = "";
    string FullName = "";
    StudentCourse *next = nullptr, *prev = nullptr;
    ScoreBoardCourse ScoreBoardCourse;
};

struct Course
{
    string Name = "";
    string CourseID = ""; // eg CSC10002
    int Credits = 0, maxStudents = 70, numStudents = 0;
    string Room = "";
    string TeacherName = "";
    string Day = "";     // eg MON TUE...
    string Session = ""; // eg S1 then session = 1
    StudentCourse *studentCourse = nullptr;
    Course *next = nullptr, *prev = nullptr;
};
// student của toàn trường, được lưu trong từng lớp
struct Student
{
    Account *accStudent = nullptr;
    string ID;
    string ClassName = "";
    Course *Course1st = nullptr;
    Student *next = nullptr, *prev = nullptr;
};

struct Class
{
    string Name; // eg 22CLC02
    Student *StudentClass;
    Class *next = nullptr, *prev = nullptr;
};

// hết -1 một môn, -2 kì, -3 năm
struct Semester
{
    int No;   // eg semester 1 thì No = 1
    int Year; // only the start year, when cout put the end year in by adding 1
    string startDate, endDate;
    Course *course = nullptr;
    Semester *next = nullptr, *prev = nullptr;
};

struct Year
{
    int yearStart;
    Class *Class = nullptr;
    Semester *NoSemester = nullptr;
    Year *next = nullptr;
};

/*
1 file lưa toàn bộ sinh sinh viên trường
1 file lưu tên các số kì, số lớp và số khóa, tên kì, tên lớp
*/