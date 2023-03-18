#include<iostream>

using namespace std;

struct Year {
    int yearStart, yearEnd;
    Class *Class;
    Semester *NoSemester;    
};

struct Semester {
    int No; // eg semester 1 thì No = 1
    int yearStartSchool; 
    int startDate, endDate;
    Semester *next, *prev;
    Semester() {
        next = prev = nullptr;
    }
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
    Student *StudentCourse;
    Course *next, *prev;
    Course() {
        next = prev = nullptr;
    }
};

struct Class {
    string Name; // eg 22CLC02
    Student *StudentClass;
    Class *next, *prev;
    Class() {
        next = prev = nullptr;
    }
};

struct Student {
    int ID[8], SocialID[12]; 
    string firstName = "", lastName = "";
    char Gender; //M is male, F is female
    string ClassName = "";
    string CourseName = "";
    Student *next;
    Student *prev;
    Student() {
        next = prev = nullptr;
    }
    ScoreBoard ScoreBoard;
};

struct ScoreBoard { 
    double totalMark, finalMark, midMark, otherMark;
};

struct Account {
    string username = "", password = "";
    int role; // role = 1 Student, role = 2 staff or teacher
    Account *next, *prev;
    Account () {
        next = prev = nullptr;
    } 
};

/* 
1 file lưa toàn bộ sinh sinh viên trường
1 file lưu tên các số kì, số lớp và số khóa, tên kì, tên lớp
*/