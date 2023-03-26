#include <fstream>
#include <string>
#include <iostream>

using namespace std;

struct Account {
    string username = "", password = "";
    string firstName = "", lastName = "";
    char Gender; //M is male, F is female
    int SociaID[12];
    string DateofBirth; // (yy/mm/dd)
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
    string ID;
    string ClassName = "";
    StudentCourse *next;
    StudentCourse *prev;
    StudentCourse() {
        next = prev = nullptr;
    }
    ScoreBoard ScoreBoard;
};

struct Course {
    string Name = ""; 
    int CourseID; //eg CSC10002
    int Credits = 0, maxStudents = 70, numStudents = 0;
    string Room = "";
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
    string ID;
    Account *accStu;
    string ClassName = "";
    Course *Course1st;
    ScoreBoard ScoreBoard;
    Student *next;
    Student *prev;
    Student() {
        accStu = nullptr;
        Course1st = nullptr;
        next = prev = nullptr;
    }
};

struct Class {
    string Name; // eg 22CLC02
    Student *StudentClass;
    Class *next, *prev;
    Class() {
        StudentClass = nullptr;
        next = prev = nullptr;
    }
};

struct Semester {
    int No; // eg semester 1 thì No = 1
    int Year; // only the start year, when cout put the end year in by adding 1 
    string startDate, endDate;
    Course *Course;
    Semester *next, *prev;
    Semester() {
        next = prev = nullptr;
    }
};

struct Year {
    int yearStart;
    Class *Class;
    Semester *NoSemester;   
    Year *next;
    Year () {
        next = nullptr;
    } 
};


/* 
1 file lưa toàn bộ sinh sinh viên trường
1 file lưu tên các số kì, số lớp và số khóa, tên kì, tên lớp
*/