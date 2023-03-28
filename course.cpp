#include "proto.h"

//export the list student in course to file CSV
Year *Yhead;
Semester *curSmt; //semester hiện tại, lấy từ việc tạo semester mới

ofstream out;
ifstream in;

string path;
bool checkFile(string name) {
    fstream f;
    f.open(name);
    if(f.is_open()) return true;
    return false;
}

Year* findYear(int yearStart);
Semester* findSemester (int no_smt, Semester *SmtHead);
Course* findCourse(string nameOrID, Course *CourseHead);
void createNameFile(int year, int no_smt, string course, string file, string type);

void readScoreStudentCourse(ScoreBoardCourse &SBC);
void readStudentCourse(StudentCourse *&studentHead);
void readAllFileCourses();

void exportInforStudent(StudentCourse *stuHead);
void exportListStudentCourse();

void exportScoreCourseStudent(ScoreBoardCourse ScoreBoardCourse);

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
            return curSmt;
    }
    return curSmt;
}

Course* findCourse(string nameOrID, Course *CourseHead) {
    Course *CourseHead = curSmt->Course;
    while (CourseHead) {
        if (CourseHead->CourseID == nameOrID || CourseHead->Name == nameOrID)
            return CourseHead;
        else CourseHead = CourseHead->next;
    }
    return CourseHead;
}


void createNameFile(int year, int no_smt, string course, string file, string type) {
    string s_year = to_string(year) + "_" + to_string(year + 1) + "\\";
    string s_smt = "smt" + to_string(3) + "\\";
    path = s_year + s_smt + course + "\\" + file + "." + type;
}

void readScoreStudentCourse(ScoreBoardCourse &SBC) {
    string s_totalMark, s_finalMark, s_midMark, s_otherMark;
    getline(in,s_totalMark,',');
    getline(in,s_finalMark,',');
    getline(in,s_midMark,',');
    getline(in,s_otherMark,',');
    SBC.totalMark = stoi(s_totalMark);
    SBC.finalMark = stoi(s_totalMark);
    SBC.midMark = stoi(s_midMark);
    SBC.otherMark = stoi(s_otherMark); 
}

void readStudentCourse(StudentCourse *&studentHead){
    StudentCourse *cur = studentHead;
    while (!in.eof()) {
        if (!cur) cur = new StudentCourse;
        else {
            cur -> next = new StudentCourse;
            cur = cur -> next;
        }
        getline(in,cur->ID,',');
        getline(in,cur->FullName,',');
        readScoreStudentCourse(cur->ScoreBoardCourse);    
    }
}

//import data course
void readAllFileCourses() {
    Year *YrHeadr = Yhead;
    Semester *curSmt;
    Course *curCourse;
    while (YrHeadr) {
        curSmt = YrHeadr->NoSemester;
        while(curSmt) {
            curCourse = curSmt->Course;
            while(curCourse) {
                createNameFile(YrHeadr->yearStart, curSmt->No, curCourse->Name, "Score", "CSV"); 
                if(!checkFile(path))
                    break;
                in.open(path);
                readStudentCourse(curCourse->StudentCourse); 
                curCourse = curCourse->next;
            }
            curSmt = curSmt->next;
        }
        YrHeadr = YrHeadr->next;
    }
}

//infor này chỉ gồm ID và họ tên
void exportInforStudent(StudentCourse *stuHead) {
    int No = 1;
    out << "No,Student ID,Fullname" << endl;
    while (stuHead) {
        out << No++ << ","
            << stuHead->ID << ","
            << stuHead->FullName ;
        stuHead = stuHead -> next;
    }
}


//task 16
//func export the list student of a course
void exportListStudentCourse() {
    system("cls"); //xóa màn hình
    string nameOrID;
    cout << "Danh sach khoa hoc trong hoc ki hien tai" << endl;
    //hàm xuất các khóa học hiện tại
    cout << "Moi nhap ten hoac ID khoa hoc can xuat danh sach hoc sinh." << endl;
    cin  >> nameOrID;
    Course *curCourse = findCourse(nameOrID, curSmt->Course);
    if (!curCourse) {
        cout << "Ten hoac ID khoa hoc ban nhap khong chinh xac hoac khoa hoc khong thuoc ky nay." << endl;
        cout << "Chon 1 de nhap lai." << endl;
        cout << "Nhan bat ki phim nao khac de thoat chuong trinh." << endl;
        char choose;
        cin  >> choose;
        if (choose == '1') {
            exportListStudentCourse();
        }            
    }
    
    createNameFile(curSmt->Year, curSmt->No, curCourse->Name, "studentCourse", "CSV");
    if (!checkFile(path)) 
        system(("mkdir " + path).c_str());
    out.open(path);
    exportInforStudent(curCourse->StudentCourse);
    out.close();   
}// hàm này chỉ xuất chứ chưa xóa linked list

//task 17
void exportScoreCourseStudent(ScoreBoardCourse ScoreBoardCourse) {
    out << ScoreBoardCourse.totalMark << ","
        << ScoreBoardCourse.finalMark << ","
        << ScoreBoardCourse.midMark   << ","
        << ScoreBoardCourse.otherMark ;
}