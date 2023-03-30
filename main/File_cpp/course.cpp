#include "course.h"

//export the list student in course to file CSV
Semester *curSmt; //semester hiện tại, lấy từ việc tạo semester mới
ofstream out;

string path;

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
            return curSmt;
    }
    return curSmt;
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
            curCourse = curSmt->Course;
            while(curCourse) {
                createNameFile(Yhead->yearStart, curSmt->No, curCourse->Name, "Score", "CSV"); 
                if(!checkFile(path))
                    break;
                in.open(path);
                readStudentCourse(curCourse->StudentCourse, in); 
                curCourse = curCourse->next;
            }
            curSmt = curSmt->next;
        }
        Yhead = Yhead->next;
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

//task 19
//func export the list student of a course
void exportListStudentCourse(Course *CourseHead, ofstream &out ) {
    system("cls"); //xóa màn hình
    string nameOrID;
    cout << "List of courses in the current semester." << endl;
    //hàm xuất các khóa học hiện tại
    cout << "Enter the name or the course ID to enter the score." << endl;
    cin  >> nameOrID;
    Course *curCourse = findCourse(nameOrID, CourseHead);
    if (!curCourse) {
        cout << "The course name or course ID you entered does not exist for this semester." << endl;
        cout << "Choose 1 to re-enter." << endl;
        cout << "Or press any key to exit the program." << endl;
        char choose;
        cin  >> choose;
        if (choose == '1') {
            exportListStudentCourse(CourseHead, out);
        }            
    }
    
    path = createNameFile(curSmt->Year, curSmt->No, curCourse->Name, "studentCourse", "CSV");
    if (!checkFile(path)) 
        system(("mkdir " + path).c_str());
    out.open(path);
    exportInforStudent(curCourse->StudentCourse);
    out.close();   
}// hàm này chỉ xuất chứ chưa xóa linked list



//task 20 call func task 19 và func dưới đây
void importScoreBoardCourse(StudentCourse *stuHead,  ifstream &in, Course *CourseHead) {
    system("cls"); //xóa màn hình
    string nameOrID;
    cout << "List of courses in the current semester." << endl;
    //hàm xuất các khóa học hiện tại
    cout << "Enter the name or the course ID to enter the score." << endl;
    cin  >> nameOrID;
    Course *curCourse = findCourse(nameOrID, CourseHead);
    if (!curCourse) {
        cout << "The course name or course ID you entered does not exist for this semester." << endl;
        cout << "Choose 1 to re-enter." << endl;
        cout << "Or press any key to exit the program." << endl;
        char choose;
        cin  >> choose;
        if (choose == '1') {
            importScoreBoardCourse(stuHead, in, CourseHead);
        }            
    }

    path = createNameFile(curSmt->Year, curSmt->No, curCourse->Name, "Score", "CSV");
    if (!checkFile(path)) {
        cout << "This file is not exist";
        return;
    }
    in.open (path);
    readStudentCourse(curCourse->StudentCourse);
    in.close();
}


//task 21
void viewScoreCourseStudent(ScoreBoardCourse ScoreBoardCourse) {
    cout << ScoreBoardCourse.totalMark << "\t"
        << ScoreBoardCourse.finalMark << "\t"
        << ScoreBoardCourse.midMark   << "\t"
        << ScoreBoardCourse.otherMark << "\n";
}
void viewScoreBoardCourse(StudentCourse *stuHead) {
    while (stuHead) {
        cout << stuHead->ID << "\t"
             << stuHead->FullName << "\t";
        viewScoreCourseStudent(stuHead->ScoreBoardCourse);
    }
}

//task 22
Student* findStudentbyID(string IDStudent, Year *Yhead) {
    Class *curClass;
    Student *curStudent;
    while ( Yhead ) {
        curClass = Yhead -> Class;
        while ( curClass ) {
            curStudent = curClass->StudentClass;
            while ( curStudent ) {
                if ( curStudent->ID == IDStudent)
                    return curStudent;
                curStudent = curStudent->next;
            }
            curClass = curClass->next;            
        }
        Yhead = Yhead->next;
    }
}
void UpdateStudentResult(string IDStudent, string CourseName, Year *Yhead) {
    Student *checkStudent = findStudentbyID(IDStudent, Yhead);
} 

int main () {
    // StudentCourse *StudentCourse = nullptr;
    // int y= 2022;
    // int smt = 1;
    // string path = createNameFile(y, smt,"KNM", "Score", "CSV") ; 
    //     if(!checkFile(path))
    //         return 0;
    //     in.open(path);
    //     readStudentCourse(StudentCourse);
    // while (StudentCourse) {
    //     cout << StudentCourse->ID << endl;
    //     StudentCourse = StudentCourse->next;
    // }
    // cout << path;
    return 0;
}