#include "../Header/course.h"

bool checkFile(string name) {
    fstream f;
    f.open(name);
    if(f.is_open()) return true;
    return false;
}

Year* findYear(int yearStart, Year* YrHead) {
    while (YrHead) {
        if (YrHead->yearStart == yearStart)
            return YrHead;
    }
    return YrHead;
}

Semester* findSemester (int no_smt, Semester *SmtHead) {
    while (SmtHead) {
        if(SmtHead->No = no_smt)
            return SmtHead;
    }
    return SmtHead;
}

Course* findCourse(string nameOrID, Course *CourseHead) {
    while (CourseHead) {
        if (CourseHead->CourseID == nameOrID || CourseHead->Name == nameOrID)
            return CourseHead;
        else CourseHead = CourseHead->next;
    }
    return CourseHead;
}


string createNameFile(int year, int no_smt, string course, string file, string type) {
    string s_year = to_string(year) + "_" + to_string(year + 1) + "\\";
    string s_smt = "smt" + to_string(no_smt) + "\\";
    string path = "Data_file\\" + s_year + s_smt + course + "\\" + file + "." + type;
    return path;
}

void readScoreStudentCourse(ScoreBoardCourse &SBC, ifstream &in) {
    string s_totalMark, s_finalMark, s_midMark, s_otherMark;
    getline(in,s_totalMark,',');
    getline(in,s_finalMark,',');
    getline(in,s_midMark,',');
    getline(in,s_otherMark,'\n');
    SBC.totalMark = stod(s_totalMark);
    SBC.finalMark = stod(s_totalMark);
    SBC.midMark = stod(s_midMark);
    SBC.otherMark = stod(s_otherMark); 
}

void readStudentCourse(StudentCourse *&studentHead, ifstream &in){
    StudentCourse *cur = studentHead;
    while (!in.eof()) {
        if (!cur) cur = studentHead = new StudentCourse;
        else {
            cur -> next = new StudentCourse;
            cur = cur -> next;
        }
        getline(in,cur->ID,',');
        getline(in,cur->FullName,',');
        readScoreStudentCourse(cur->ScoreBoardCourse, in);    
    }
}

//import data course
void readAllFileCourses(ifstream &in, Year *Yhead) {
    Semester *curSmt;
    Course *curCourse;
    while (Yhead) {
        curSmt = Yhead->NoSemester;
        while(curSmt) {
            curCourse = curSmt->course;
            while(curCourse) {
                string path = createNameFile(Yhead->yearStart, curSmt->No, curCourse->Name, "Score", "CSV"); 
                if(!checkFile(path))
                    break;
                in.open(path);
                readStudentCourse(curCourse->studentCourse, in); 
                curCourse = curCourse->next;
            }
            curSmt = curSmt->next;
        }
        Yhead = Yhead->next;
    }
}