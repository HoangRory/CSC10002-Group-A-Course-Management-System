#include "../Header/course.h"
#include <iomanip>
//export the list student in course to file CSV
 //semester hiện tại, lấy từ việc tạo semester mới

//infor này chỉ gồm ID và họ tên
void exportInforStudent(StudentCourse *stuHead, ofstream &out) 
{
    int No = 1;
    out << "No,Student ID,Fullname" << endl;
    while (stuHead) 
    {
        out << No++ << ","
            << stuHead->ID << ","
            << stuHead->FullName ;
        stuHead = stuHead -> next;
    }
}

//task 19
//func export the list student of a course
void exportListStudentCourse(Semester *curSmt, ofstream &out )
 {
    system("cls"); //xóa màn hình
    string nameOrID;
    cout << "List of courses in the current semester." << endl;
    //hàm xuất các khóa học hiện tại
    cout << "Enter the name or the course ID to enter the score." << endl;
    cin  >> nameOrID;
    Course *curCourse = findCourse(nameOrID, curSmt->course);
    if (!curCourse)
     {
        cout << "The course name or course ID you entered does not exist for this semester." << endl;
        cout << "Choose 1 to re-enter." << endl;
        cout << "Or press any key to end to update." << endl;
        char choose;
        cin  >> choose;
        if (choose == '1') 
            exportListStudentCourse(curSmt, out);    
    }
    
    string path = createNameFile(curSmt->Year, curSmt->No, curCourse->Name, "studentCourse", "CSV");
    if (!checkFile(path)) 
        system(("mkdir " + path).c_str());
    out.open(path);
    exportInforStudent(curCourse->studentCourse, out);
    out.close();   
}// hàm này chỉ xuất chứ chưa xóa linked list



//task 20 call func task 19 và func dưới đây
void importScoreBoardCourse(Semester * curSmt, StudentCourse *stuHead,  ifstream &in) 
{
    system("cls"); //xóa màn hình
    string nameOrID;
    cout << "List of courses in the current semester." << endl;
    //hàm xuất các khóa học hiện tại
    cout << "Enter the name or the course ID to enter the score." << endl;
    cin  >> nameOrID;
    Course *curCourse = findCourse(nameOrID, curSmt->course);
    if (!curCourse) 
    {
        cout << "The course name or course ID you entered does not exist for this semester." << endl;
        cout << "Choose 1 to re-enter." << endl;
        cout << "Or press any key to end to update." << endl;
        char choose;
        cin  >> choose;
        if (choose == '1') 
        {
            importScoreBoardCourse(curSmt, stuHead, in);
        }
    }

    string path = createNameFile(curSmt->Year, curSmt->No, curCourse->Name, "Score", "CSV");
    if (!checkFile(path)) 
    {
        cout << "This file is not exist";
        return;
    }
    in.open (path);
    readStudentCourse(curCourse->studentCourse, in);
    in.close();
}

//task 21
void viewScoreCourseStudent(ScoreBoardCourse ScoreBoardCourse) 
{
    cout << ScoreBoardCourse.totalMark << "\t"
        << ScoreBoardCourse.finalMark << "\t"
        << ScoreBoardCourse.midMark   << "\t"
        << ScoreBoardCourse.otherMark << "\n";
}
void viewScoreBoardCourse(StudentCourse *stuHead) 
{
    while (stuHead) 
    {
        cout << stuHead->ID << "\t"
             << stuHead->FullName << "\t";
        viewScoreCourseStudent(stuHead->ScoreBoardCourse);
    }
}

//task 22
Student* findStudentbyID(string IDStudent, Year *Yhead) 
{
    Class *curClass;
    Student *curStudent;
    while ( Yhead ) 
    {
        curClass = Yhead -> Class;
        while ( curClass ) 
        {
            curStudent = curClass->StudentClass;
            while ( curStudent ) 
            {
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

Course* findCoursebyName_ID(string CourseName_ID, Year *Yhead) 
{
    Semester *curSmt;
    Course *curCourse;
    while ( Yhead ) 
    {
        curSmt = Yhead -> NoSemester;
        while ( curSmt )
         {
            curCourse = curSmt->course;
            while ( curCourse ) 
            {
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

ScoreBoardCourse find_SBC(string ID, StudentCourse *stuCourseHead) 
{
    while(stuCourseHead) 
    {
        if (stuCourseHead->ID == ID) 
            return stuCourseHead->ScoreBoardCourse;
        stuCourseHead = stuCourseHead->next;
    }
}

void viewScoreBoardCourse(ScoreBoardCourse SCB) 
{
    cout << SCB.midMark   << "\t|"
         << SCB.finalMark << "\t|"
         << SCB.totalMark << "\t|"
         << SCB.otherMark << "\t|" << endl;
}

void enterMark(double &Mark) 
{
    cin >> Mark;
    while (Mark < 0 || Mark > 10) 
    {
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

void updateSCB (string ID, StudentCourse *stuCourseHead) 
{
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
    if(updateMark(checkSCB, Selection)) 
    {
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

void UpdateStudentResult(Year *Yhead) 
{
    //chọn 1 để nhập số bao danh học sinh cần sửa sau đó nhập khóa học
    //chọn 2 để chọn khóa học có học sinh cần sửa điểm, sau đó chọn học sinh
    int flag = 1;
    cout << "Select search option. Enter:" << endl
         << "1. Find student who need to update by ID." << endl
         << "2. Find course which have score board need to update." << endl 
         << "3. To end to update."<< endl;
    // cin  >> flag;
    // cin.ignore();
    system ("cls");
    string IDStudent = "22157125";
    string CourseName = "";

    if (flag == 1) 
    {
        system ("cls");
        cout << "Please enter ID: ";
        // getline(cin, IDStudent);
        Student *checkStudent = findStudentbyID(IDStudent, Yhead);
        while (!checkStudent) 
        {
            system ("cls");
            cout << "The ID you entered does not exist. Enter:" << endl
                    << "1. To re-enter again." << endl
                    << "2. To end to update" << endl;
            cin >> flag;
            if ( flag != 1) return;
            cout << "Please enter ID: ";
            // getline(cin, IDStudent);
            Student *checkStudent = findStudentbyID(IDStudent, Yhead);
        }

        system ("cls");
        //in ra các khóa của học sinh đó (trong kì đó), cho user nhập tên hoặc ID của khóa học để ra bản điểm để chỉnh sửa
        cout << "Please enter name course or ID course:"; 
        // getline(cin, CourseName);
        Course *checkCourse = findCoursebyName_ID(CourseName,Yhead);
        while (!checkCourse) 
        {
            system ("cls");
            cout << "The ID or name you entered does not exist. Enter:" << endl
                    << "1. To re-enter again." << endl
                    << "2. To end to update" << endl;
            // cin >> flag;
            if ( flag != 1) return;
            // getline(cin, CourseName);
            Course *checkCourse = findCoursebyName_ID(CourseName,Yhead);
        }
        updateSCB(IDStudent, checkCourse->studentCourse);
        return;
    }


    //nếu chọn 2:
    if (flag == 2) 
    {
        system ("cls");
        //in ra các khóa của học sinh đó (trong kì đó), cho user nhập tên hoặc ID của khóa học để ra bản điểm để chỉnh sửa
        cout << "Please enter name course or ID course:"; 
        getline(cin, CourseName);
        Course *checkCourse = findCoursebyName_ID(CourseName,Yhead);
        while (!checkCourse) 
        {
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
        while (!checkStudent) 
        {
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

//task 23
CourseStudent* checkExistence_OfCourse(CourseStudent *courseCheck, CourseStudent *courseHead) 
{
    while(courseHead) 
    {
        if (courseCheck->course == courseHead->course) 
            return courseCheck;
        courseHead->next;
    }
    return nullptr;
}

CourseStudent* CourseOfAClass (Student *studentHead) 
{
    CourseStudent *CourHead = nullptr, *tmp = nullptr;
    CourseStudent *courseCheck;
    while(studentHead) 
    {
        courseCheck = studentHead->course;
        while (courseCheck) 
        {
            if( !checkExistence_OfCourse(courseCheck, CourHead) ) 
            {
                CourseStudent *tmp = new CourseStudent;
                tmp->course = courseCheck->course;
                tmp->next = CourHead;
                CourHead = tmp;
            }
            courseCheck = courseCheck->next;
        }
        studentHead = studentHead->next;
    }
    return CourHead;
}

int CaculateAmountStudentOfClass(Student *studentHead) 
{
    int count = 0;
    while (studentHead) 
    {
        studentHead = studentHead->next;
        count ++;
    }
    return count;
}

int CaculateAmountCourseOfClass(CourseStudent *courseHead) 
{
    int count = 0;
    while (courseHead) 
    {
        courseHead = courseHead->next;
        count ++;
    }
    return count;
}

void importSCB_ofStudent(double *&SCB, CourseStudent *courseHead, Student *studentHead) {
    ScoreBoardCourse scb_of_course;
    CourseStudent *courseCheck;
    int i = 0;
    while (courseHead) 
    {
        courseCheck = checkExistence_OfCourse(courseHead,studentHead->course);
        if (courseCheck) 
        {
            scb_of_course = find_SBC(studentHead->ID, courseHead->course->studentCourse);
                SCB[i++] = scb_of_course.finalMark;
        } else 
            SCB[i++] = -1; // -1 là hs này không học môn đó
        courseHead = courseHead->next;
    }
}

double CaculateGPA_1_Student(double *&SCB, int n) // n là số môn, tức là số cột của bảng SCB. n là số đã trừ cột cuối ra 
{
    double GPA = 0;
    int count = 0; // biến này để đếm xem học sinh này học bao nhiêu môn
    for(int i = 0; i < n; i++) 
    {
        if ( SCB[i] >= 0)
        {
            GPA += SCB[i];
            count ++;
        }        
    }
    if (count != 0) 
        GPA /= count;
    return GPA;
}

void createSCB_ofClass(double **&SCB, CourseStudent *courseHead, Student *studentHead, int Col, int Row )
{
    SCB = new double*[Col + 1] ;
    for(int i = 0; i<Row; i++)
    {
        SCB[i] = new double[Col+1]; // +1 là + 1 cột cuối để lưu GPA của học sinh đó trong kì này
        importSCB_ofStudent(SCB[i], courseHead, studentHead);
        SCB[i][Col] = CaculateGPA_1_Student(SCB[i], Col);
        studentHead = studentHead->next;
    }
}

// mảng này sẽ có dạng | môn A | môn B |....| môn Z | GPA |

void viewAllFinalMark_ofStudent(double *SCB, int Col)
{
    for( int i = 0; i < Col; i++) 
    {
        if(SCB[i] < 0)
            cout << setw(35) << left << "| X";
        else 
            cout << "| " << setw(35) << left  << setprecision(1) << fixed  << SCB[i];
    }                             
}

void viewScoreboardClass(Class *Class) 
{
    Student *studentHead = Class->StudentClass;
    CourseStudent *courseHead = CourseOfAClass(studentHead);
    int Col = CaculateAmountCourseOfClass(courseHead);
    int Row = CaculateAmountStudentOfClass(studentHead);
    double **SCB;
    createSCB_ofClass(SCB,courseHead,studentHead,Col,Row);

    cout << setw(12) << left << "| ID";
    cout << setw(27) << left << "| Full Name";
    while (courseHead)
    {
        cout <<"| " << setw(35) << left <<courseHead->course->Name;
        courseHead = courseHead->next;
    }
    cout << setw(7) << left << "| GPA"; 
    cout << "|" << endl;

    int i = 0;
    while (studentHead) 
    {
        cout << "| " << setw(10) << left  << studentHead->ID;
        cout << "| " << setw(25) << left << studentHead->accStudent->lastName + " " + studentHead->accStudent->firstName;
        viewAllFinalMark_ofStudent(SCB[i], Col);
        cout << "| "<< setw(5) << left  << setprecision(1) << fixed << CaculateGPA_1_Student(SCB[i++], Col); 
        cout << "|" << endl;
        studentHead = studentHead->next;
    }
    for(int i = 0; i<Row; i++)
        delete []SCB[i];
    delete []SCB;
}

int main() {
    Year *yr = new Year;
    yr->yearStart = 2022;

    yr->NoSemester = new Semester;
    yr->NoSemester->No = 2;

    yr->NoSemester->course = new Course;
    yr->NoSemester->course->Name = "CSC10002";
    yr->NoSemester->course->TeacherName = "Dinh Ba Tien";
    readAllFileCourses(yr);
    StudentCourse *stuHead = yr->NoSemester->course->studentCourse;
    while (stuHead) {
        cout << stuHead->ID << endl;
        stuHead = stuHead->next;
    }

    yr->Class = new Class;
    yr->Class->StudentClass = new Student;
    yr->Class->StudentClass->ID = "22127123";
    yr->Class->StudentClass->course = new CourseStudent;
    yr->Class->StudentClass->course->course = yr->NoSemester->course;
    yr->Class->StudentClass->accStudent = new Account;
    yr->Class->StudentClass->accStudent->firstName = "Hoang";
    yr->Class->StudentClass->accStudent->lastName = "Le Ho Phi";
    // 22127124,Nguyen Van A
    yr->Class->StudentClass->next = new Student;
    yr->Class->StudentClass->next->ID = "22127124";
    yr->Class->StudentClass->next->course = new CourseStudent;
    yr->Class->StudentClass->next->course->course = yr->NoSemester->course;
    yr->Class->StudentClass->next->accStudent = new Account;
    yr->Class->StudentClass->next->accStudent->firstName = "A";
    yr->Class->StudentClass->next->accStudent->lastName = "Nguyen Van";

    viewScoreboardClass(yr->Class);
    deleteAllCourse(yr);
    return 0;
}
