#pragma once
#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <vector>
#include <conio.h>
#include <Windows.h>
#include <sstream>
#include <cctype>
#include <algorithm>

#define BLACK 0
#define BLUE 1
#define GREEN 2
#define AQUA 3
#define RED 4
#define PURPLE 5
#define YELLOW 6
#define WHITE 7
#define GRAY 8
#define LIGHT_BLUE 9
#define LIGHT_GREEN 10
#define LIGHT_AQUA 11
#define LIGHT_RED 12
#define LIGHT_PURPLE 13
#define LIGHT_YELLOW 14
#define BRIGHT_WHITE 15

#define ENTER 13
#define ESC 27
#define UP 72
#define LEFT 75
#define RIGHT 77
#define DOWN 80

using namespace std;

struct Account
{
    string username = "", password = "";
    string firstName = "", lastName = "";
    string Gender = ""; // M is male, F is female
    string SocialID = "";
    string birth = "";
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
struct CourseStudent
{
    Course *course = nullptr;
    CourseStudent *next = nullptr;
};

struct Student
{
    Account *accStudent = nullptr;
    string ID = "";
    CourseStudent *course = nullptr;
    Student *next = nullptr, *prev = nullptr;
};

struct Class
{
    string Name; // eg 22CLC02
    Student *StudentClass = nullptr;
    Class *next = nullptr, *prev = nullptr;
};

struct Semester
{
    int No;   // eg semester 1 then No = 1
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
    Year *prev = nullptr;
};

/*
1 file lưa toàn bộ sinh sinh viên trường
1 file lưu tên các số kì, số lớp và số khóa, tên kì, tên lớp
*/
/*
1 file lưa toàn bộ sinh sinh viên trường
1 file lưu tên các số kì, số lớp và số khóa, tên kì, tên lớp
*/