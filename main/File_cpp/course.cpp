#include "../Header/course.h"

//export the list student in course to file CSV
 //semester hiện tại, lấy từ việc tạo semester mới

//infor này chỉ gồm ID và họ tên
void exportInforStudent(StudentCourse *stuHead, ofstream &out) {
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
void exportListStudentCourse(Semester *curSmt, ofstream &out ) {
    system("cls"); //xóa màn hình
    string nameOrID;
    cout << "List of courses in the current semester." << endl;
    //hàm xuất các khóa học hiện tại
    cout << "Enter the name or the course ID to enter the score." << endl;
    cin  >> nameOrID;
    Course *curCourse = findCourse(nameOrID, curSmt->course);
    if (!curCourse) {
        cout << "The course name or course ID you entered does not exist for this semester." << endl;
        cout << "Choose 1 to re-enter." << endl;
        cout << "Or press any key to end to update." << endl;
        char choose;
        cin  >> choose;
        if (choose == '1') {
            exportListStudentCourse(curSmt, out);
        }            
    }
    
    string path = createNameFile(curSmt->Year, curSmt->No, curCourse->Name, "studentCourse", "CSV");
    if (!checkFile(path)) 
        system(("mkdir " + path).c_str());
    out.open(path);
    exportInforStudent(curCourse->studentCourse, out);
    out.close();   
}// hàm này chỉ xuất chứ chưa xóa linked list



//task 20 call func task 19 và func dưới đây
void importScoreBoardCourse(Semester * curSmt, StudentCourse *stuHead,  ifstream &in) {
    system("cls"); //xóa màn hình
    string nameOrID;
    cout << "List of courses in the current semester." << endl;
    //hàm xuất các khóa học hiện tại
    cout << "Enter the name or the course ID to enter the score." << endl;
    cin  >> nameOrID;
    Course *curCourse = findCourse(nameOrID, curSmt->course);
    if (!curCourse) {
        cout << "The course name or course ID you entered does not exist for this semester." << endl;
        cout << "Choose 1 to re-enter." << endl;
        cout << "Or press any key to end to update." << endl;
        char choose;
        cin  >> choose;
        if (choose == '1') {
            importScoreBoardCourse(curSmt, stuHead, in);
        }
    }

    string path = createNameFile(curSmt->Year, curSmt->No, curCourse->Name, "Score", "CSV");
    if (!checkFile(path)) {
        cout << "This file is not exist";
        return;
    }
    in.open (path);
    readStudentCourse(curCourse->studentCourse, in);
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
    return nullptr;
}

Course* findCoursebyName_ID(string CourseName_ID, Year *Yhead) {
    Semester *curSmt;
    Course *curCourse;
    while ( Yhead ) {
        curSmt = Yhead -> NoSemester;
        while ( curSmt ) {
            curCourse = curSmt->course;
            while ( curCourse ) {
                if ( curCourse->Name == CourseName_ID)
                    return curCourse;
                curCourse = curCourse->next;
            }
            curSmt = curSmt->next;            
        }
        Yhead = Yhead->next;
    }
    return nullptr;
}

ScoreBoardCourse find_SBC(string ID, StudentCourse *stuCourseHead) {
    while(stuCourseHead) {
        if (stuCourseHead->ID == ID) 
            return stuCourseHead->ScoreBoardCourse;
        stuCourseHead = stuCourseHead->next;
    }
}

void viewScoreBoardCourse(ScoreBoardCourse SCB) {
    cout << SCB.midMark   << "\t|"
         << SCB.finalMark << "\t|"
         << SCB.totalMark << "\t|"
         << SCB.otherMark << "\t|" << endl;
}

void enterMark(double &Mark) {
    cin >> Mark;
    while (Mark < 0 || Mark > 10) {
        cout << "Please re-enter your score. 0 <= mark <= 10";
        cin  >> Mark;
    }
}

//return true = đã update, return false = không update
bool updateMark(ScoreBoardCourse &SCB, string Selection) {
    if( Selection == "1" || Selection == "MidMark" || Selection == "midmark") {
        cout << "MidMark = ";
        enterMark(SCB.midMark);
    } 
    else if( Selection == "2" || Selection == "FinalMark" || Selection == "finalmark") {
        cout << "FinalMark = ";
        enterMark(SCB.finalMark);
    }
    else if( Selection == "3" || Selection == "TotalMark" || Selection == "totalmark") {
        cout << "TotalMark = ";
        enterMark(SCB.totalMark);
    }
    else if( Selection == "4" || Selection == "OtherMark" || Selection == "othermark") {
        cout << "OtherMark = ";
        enterMark(SCB.otherMark);
    } else return false;

    return true;
}

void updateSCB (string ID, StudentCourse *stuCourseHead) {
    system ("cls");
    ScoreBoardCourse checkSCB = find_SBC(ID, stuCourseHead);
    cout << "1.MidMark"   << "\t|"
         << "2.FinalMark" << "\t|"
         << "3.TotalMark "<< "\t|"
         << "4.OtherMark" << "\t|" << endl;
    viewScoreBoardCourse(checkSCB);
    cout << "Select the mark you want to update. (eg: Enter 1 or MidMark to update MidMark)"
         << "Or enter X to end to update.";
    string Selection = "";
    getline(cin,Selection);
    if(Selection == "X") return;
    if(updateMark(checkSCB, Selection)) {
        cout << "Do you want to update more?"
                << "Selecion: Y (Yes) to continue or press any key to end to update.";
    } else {
        cout << "Your selection is not correct."
             << "Selecion: Y (Yes) to re-enter or press any key to end to update.";
    }
    cin >> Selection;
    if (Selection == "Y") 
        updateSCB(ID,stuCourseHead);
}

void UpdateStudentResult( Year *Yhead) {
    //chọn 1 để nhập số bao danh học sinh cần sửa sau đó nhập khóa học
    //chọn 2 để chọn khóa học có học sinh cần sửa điểm, sau đó chọn học sinh
    int flag = 0;
    cout << "Select search option. Enter:" << endl
         << "1. Find student who need to update by ID." << endl
         << "2. Find course which have score board need to update." << endl 
         << "3. To end to update."<< endl;
    cin  >> flag;
    system ("cls");
    string IDStudent = "";
    string CourseName = "";

    if (flag == 1) {
        system ("cls");
        cout << "Please enter ID: ";
        getline(cin, IDStudent);
        Student *checkStudent = findStudentbyID(IDStudent, Yhead);
        while (!checkStudent) {
            system ("cls");
            cout << "The ID you entered does not exist. Enter:" << endl
                    << "1. To re-enter again." << endl
                    << "2. To end to update" << endl;
            cin >> flag;
            if ( flag == 2) return;
            getline(cin, IDStudent);
            Student *checkStudent = findStudentbyID(IDStudent, Yhead);
        }

        system ("cls");
        //in ra các khóa của học sinh đó (trong kì đó), cho user nhập tên hoặc ID của khóa học để ra bản điểm để chỉnh sửa
        cout << "Please enter name course or ID course:"; 
        getline(cin, CourseName);
        Course *checkCourse = findCoursebyName_ID(CourseName,Yhead);
        while (!checkCourse) {
            system ("cls");
            cout << "The ID or name you entered does not exist. Enter:" << endl
                    << "1. To re-enter again." << endl
                    << "2. To end to update" << endl;
            cin >> flag;
            if ( flag != 1) return;
            getline(cin, CourseName);
            Course *checkCourse = findCoursebyName_ID(CourseName,Yhead);
        }
        updateSCB(IDStudent, checkCourse->studentCourse);
        return;
    }


    //nếu chọn 2:
    if (flag == 2) {
        system ("cls");
        //in ra các khóa của học sinh đó (trong kì đó), cho user nhập tên hoặc ID của khóa học để ra bản điểm để chỉnh sửa
        cout << "Please enter name course or ID course:"; 
        getline(cin, CourseName);
        Course *checkCourse = findCoursebyName_ID(CourseName,Yhead);
        while (!checkCourse) {
            system ("cls");
            cout << "The ID or name you entered does not exist. Enter:" << endl
                    << "1. To re-enter again." << endl
                    << "2. To end to update" << endl;
            cin >> flag;
            if ( flag == 2) return;
            getline(cin, CourseName);
            Course *checkCourse = findCoursebyName_ID(CourseName,Yhead);
        }

        system ("cls");
        cout << "Please enter ID: ";
        getline(cin, IDStudent);
        Student *checkStudent = findStudentbyID(IDStudent, Yhead);
        while (!checkStudent) {
            system ("cls");
            cout << "The ID you entered does not exist. Enter:" << endl
                    << "1. To re-enter again." << endl
                    << "2. To end to update" << endl;
            cin >> flag;
            if ( flag != 1) return;
            getline(cin, IDStudent);
            Student *checkStudent = findStudentbyID(IDStudent, Yhead);
        }
        updateSCB(IDStudent, checkCourse->studentCourse);
        return;
    }
} 



// int main () {
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
//     return 0;
// }