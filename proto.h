#include <fstream>
#include <string>
#include <iostream>

using namespace std;

struct Account {
    string username = "", password = "";
    string firstName = "", lastName = "";
    char Gender; //M is male, F is female
    int SociaID[12];
    int role; // role = 1 Student, role = 2 staff or teacher
    Account *next, *prev;
    Account () {
        next = prev = nullptr;
    } 
};

struct ScoreBoard { 
    double totalMark, finalMark, midMark, otherMark;
};

//student của một course
struct StudentCourse {
    int ID[8];
    string ClassName = "";
    StudentCourse *next;
    StudentCourse *prev;
    StudentCourse() {
        next = prev = nullptr;
    }
    ScoreBoard ScoreBoard;
};

struct Course {
    int noSemester; // eg this course is in semester 1 thì noSemester = 1
    int CourseID; //
    int Credits = 0, maxStudents = 50, numStudents = 0;
    string Room = "";
    string Name = ""; // eg CSC10002
    string TeacherName = "";
    string Day = ""; //eg MON TUE...
    int Session; // eg S1 then session = 1
    StudentCourse *StudentCourse;
    Course *next, *prev;
    Course() {
        next = prev = nullptr;
    }
};

//student của toàn trường, được lưu trong từng lớp
struct Student {
    int ID[8];
    string ClassName = "";
    Course *Course1st;
    Student *next;
    Student *prev;
    Student() {
        next = prev = nullptr;
    }
    ScoreBoard ScoreBoard;
};

struct Class {
    string Name; // eg 22CLC02
    Student *StudentClass;
    Class *next, *prev;
    Class() {
        next = prev = nullptr;
    }
};



struct Semester {
    int No; // eg semester 1 thì No = 1
    int yearStartSchool; 
    string startDate, endDate;
    Semester *next, *prev;
    Semester() {
        next = prev = nullptr;
    }
};

struct Year {
    int yearStart, yearEnd;
    Class *Class;
    Semester *NoSemester;    
};


/* 
1 file lưa toàn bộ sinh sinh viên trường
1 file lưu tên các số kì, số lớp và số khóa, tên kì, tên lớp
*/