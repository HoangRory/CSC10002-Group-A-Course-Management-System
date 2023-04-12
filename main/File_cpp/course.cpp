#include "../Header/course.h"
#include "../Header/help.h"
// #include "Staff_view.cpp"
// #include "Read_Write_Del_Course.cpp"
#include <iomanip>

//export the list student in course to file CSV
 //semester hiện tại, lấy từ việc tạo semester mới

//task 19

void exportInforStudent(StudentCourse *stuHead, ofstream &out) 
{
    int No = 1;
    out << "No,Student ID,Fullname,Total Mark,Final Mark,Mid Mark,Other Mark" ;
    while (stuHead) 
    {
        out << "\n"
            << No++ << ","
            << stuHead->ID << ","
            << stuHead->FullName << ","
            << stuHead->ScoreBoardCourse.totalMark << ","
            << stuHead->ScoreBoardCourse.finalMark << ","
            << stuHead->ScoreBoardCourse.midMark << ","
            << stuHead->ScoreBoardCourse.otherMark;
        stuHead = stuHead -> next;
    }
}
//func export the list student of a course to sent to teacher
void exportListStudentCourse(Semester *curSmt)
 {
    system("cls");
    cout << "Please select course for which you want to show scoreboard. Or select close <- to come back Main Menu" << endl;
    cout << "Using arrow keys to move and press enter to select your option." << endl;
    system("pause");
    system("cls");

    // int nOption = AmountOfCourse(curSmt->course);
    // string *arrOption = new string [nOption+1];
    // Course *cur = curSmt->course;
    // for(int i = 0; i < nOption; i++) {
    //     arrOption[i] = cur->Name;
    //     cur = cur->next;
    // }
    // arrOption[nOption] = "<-";
    // string title = "List of courses in the current semester. Your option:" ;
    // int option = view_chooseOption(arrOption,nOption + 1, title);
    // delete []arrOption;

    // if (option == nOption) {
    //     return;
    // }
    // system("cls");
    // Course *curCourse = findCoursebyIndexOption(curSmt->course, option);
    // if (!curCourse) 
    // {
    //     system ("cls");
    //     cout << "The course you selected does not exist for this semester." << endl;
    //     nOption = 2;
    //     string *arrOption = new string [nOption];
    //     arrOption[0] = "-To re-enter.";
    //     arrOption[1] = "-To end to import";
    //     option = view_chooseOption(arrOption,nOption);
    //     delete []arrOption;
    //     if(option == 0) return; 
    //     exportListStudentCourse(curSmt);    
    // }
    Course *curCourse = chooseCoursebyOption(curSmt->course);
    if(!curCourse) {
        //quay lại menu
        return;
    }
    string path = createNameFile(curSmt->Year, curSmt->No, curCourse->Name, "score", "CSV");
    if (!checkFile(path)) 
        system(("mkdir " + path).c_str());
    ofstream out;
    out.open(path);
    exportInforStudent(curCourse->studentCourse, out);
    out.close();   
}// hàm này chỉ xuất chứ chưa xóa linked list

//task 20 call func task 19 và func dưới đây
void importScoreBoardCourse(Semester * curSmt, StudentCourse *stuHead) 
{
    // int nOption = AmountOfCourse(curSmt->course);
    // string *arrOption = new string [nOption+1];
    // Course *cur = curSmt->course;
    // for(int i = 0; i < nOption; i++) {
    //     arrOption[i] = cur->Name;
    //     cur = cur->next;
    // }
    // arrOption[nOption] = "<-";
    system("cls");
    cout << "Please select course for which you want to show scoreboard. Or select close <- to come back Main Menu" << endl;
    cout << "Using arrow keys to move and press enter to select your option." << endl;
    system("pause");
    system("cls");
    Course *curCourse = chooseCoursebyOption(curSmt->course);
    if(!curCourse) {
        //quay lại menu
        return;
    }
    // cout << "List of courses in the current semester." << endl;
    // int option = view_chooseOption(arrOption,nOption + 1);
    // delete []arrOption;

    // if (option == nOption) {
    //     return;
    // }

    // system("cls"); //xóa màn hình
    // Course *curCourse = findCoursebyIndexOption(curSmt->course, option);
    // if (!curCourse) 
    // {
    //     system ("cls");
    //     nOption = 2;
    //     string *arrOption = new string [nOption];
    //     arrOption[0] = "-To re-enter.";
    //     arrOption[1] = "-To end to import";
    //     option = view_chooseOption(arrOption,nOption);
    //     delete []arrOption;
    //     if(option == 1) 
    //         importScoreBoardCourse(curSmt,stuHead)    ;    
    // }

    string path = createNameFile(curSmt->Year, curSmt->No, curCourse->Name, "score", "csv");
    if (!checkFile(path)) 
    {
        cout << "The scoreboard of this course does not exist." << endl
             << "Please contact the teacher to get scoreboard and to try again.";
        return;
    }
    ifstream in;
    in.open (path);
    readStudentCourse(curCourse->studentCourse, in);
    in.close();
}

//task 21
void viewScoreCourseStudent(ScoreBoardCourse SBC) 
{
    cout << "| " << setw(15) << left << SBC.midMark; 
    cout << "| " << setw(15) << left << SBC.finalMark;
    cout << "| " << setw(15) << left << SBC.totalMark ; 
    cout << "| " << setw(15) << left << SBC.otherMark ;
    cout << "| " << endl;
}
int AmountOfCourse(Course *courseHead) 
{
    int n = 0;
    while (courseHead) {
        courseHead = courseHead->next;
        n++;
    }
    return n;
}
Course* findCoursebyIndexOption(Course *courseHead, int index) 
{
    for(int i = 0; courseHead != nullptr; i++) {
        if(i == index) 
            break;
        courseHead = courseHead->next;
    }
    return courseHead;
}
void viewScoreBoardCourse(Course *courseHead) 
{
    // int nOption = AmountOfCourse(courseHead);
    // string *arrOption = new string [nOption+1];
    // for(int i = 0; i < nOption; i++) {
    //     arrOption[i] = cur->Name;
    //     cur = cur->next;
    // }
    // arrOption[nOption] = "<-";
    system("cls");
    cout << "Please select course for which you want to show scoreboard. Or select close <- to come back Main Menu" << endl;
    cout << "Using arrow keys to move and press enter to select your option." << endl;
    system("pause");
    system("cls");

    // int option = view_chooseOption(arrOption,nOption + 1);
    // delete []arrOption;
    // // int option = 0;
    // if (option == nOption) {
    //     cout << 1;
    //     return;
    // }
    // cur = findCoursebyIndexOption(courseHead,option);
    Course *curCourse = chooseCoursebyOption(courseHead);
    if(!curCourse) {
        //quay lại menu chính
        return;
    }
    StudentCourse *stuHead = curCourse->studentCourse;
    for(int i = 0; i < 110 ; i++)
        cout <<"=";
    cout << endl;
    cout << "| " << setw(12) << left << "ID";
    cout << "| " << setw(25) << left << "Full Name";
    cout << "| " << setw(15) << left << "Mid Mark"; 
    cout << "| " << setw(15) << left << "Final Mark";
    cout << "| " << setw(15) << left << "Total Mark" ; 
    cout << "| " << setw(15) << left << "Other Mark" ;
    cout << "| " << endl;
    while (stuHead) 
    {
        for(int i = 0; i < 110 ; i++)
            cout <<"=";
        cout << endl;
        cout << "| " << setw(12) << left << stuHead->ID ;
        cout << "| " << setw(25) << left<< stuHead->FullName;
        viewScoreCourseStudent(stuHead->ScoreBoardCourse);
        stuHead = stuHead->next;
    }
    for(int i = 0; i < 110 ; i++)
        cout <<"=";
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
StudentCourse* find_SBC(string ID, StudentCourse *stuCourseHead) 
{
    while(stuCourseHead) 
    {
        if (stuCourseHead->ID == ID) 
            return stuCourseHead;
        stuCourseHead = stuCourseHead->next;
    }
    return nullptr;
}
void enterMark(double &Mark) 
{
    // Mark = 2;
    cin >> Mark;
    while (Mark < 0 || Mark > 10) 
    {
        cout << "Please re-enter your score. 0 <= mark <= 10";
        cin  >> Mark;
    }
}
//return true = đã update, return false = không update
bool updateMark(ScoreBoardCourse &SBC, string Selection) {
    if( Selection == "1" || Selection == "MidMark" || Selection == "midmark") {
        cout << "MidMark = ";
        enterMark(SBC.midMark);
    } 
    else if( Selection == "2" || Selection == "FinalMark" || Selection == "finalmark") {
        cout << "FinalMark = ";
        enterMark(SBC.finalMark);
    }
    else if( Selection == "3" || Selection == "TotalMark" || Selection == "totalmark") {
        cout << "TotalMark = ";
        enterMark(SBC.totalMark);
    }
    else if( Selection == "4" || Selection == "OtherMark" || Selection == "othermark") {
        cout << "OtherMark = ";
        enterMark(SBC.otherMark);
    } else return false;

    return true;
}
void updateSBC (string ID, StudentCourse *stuUpdate) 
{
    //kẻ bảng điểm
    for(int i = 0; i < 69; i++) 
        cout << "=";
    cout << endl;
    cout << "| " << setw(15) << left << "Mid Mark ";
    cout << "| " << setw(15) << left << "Final Mark";
    cout << "| " << setw(15) << left << "Total Mark ";
    cout << "| " << setw(15) << left << "OtherMark";
    cout << "|"  << endl;
    for(int i = 0; i < 69; i++)
        cout << "=";
    cout << endl;
    viewScoreCourseStudent(stuUpdate->ScoreBoardCourse);
    for(int i = 0; i < 69; i++)
        cout << "=";
    cout << endl;


    cout << "Select the mark you want to update. (eg: Enter 1 or MidMark to update MidMark)"
         << "Or enter X to end to update." << endl;
    string Selection = "";
    getline(cin,Selection);
    if(Selection == "X") return;

    if(updateMark(stuUpdate->ScoreBoardCourse, Selection)){
        cout << "Do you want to update more?"
                << "Selecion: Y (Yes) to continue or press any key to end to update.";
    } else {
        cout << "Your selection is not correct."
             << "Selecion: Y (Yes) to re-enter or press any key to end to update.";
    }
    cin >> Selection;
    cin.ignore();
    if (Selection != "Y") return;
    updateSBC(ID,stuUpdate);
}
int view_chooseOption(string *arrOption, int nOption, string title) {
    HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
    bool stop = false;
    int option = 0;
    cout << title << endl;

    for(int i = 0; i < nOption; i++) {
        if(i == option) {
            SetConsoleTextAttribute(color, 2);
            cout << arrOption[i] << endl;
            SetConsoleTextAttribute(color, 7);
        } else cout << arrOption[i] << endl;
    }
    while(!stop) {
        if (_kbhit()) {
            switch(_getch()) {
                case 72 : 
                    option--;
                    if(option < 0) 
                        option = nOption - 1;
                break;
                case 80:
                    option ++;
                    if(option == nOption)
                        option = 0; 
                break;
                case 13:
                    stop = true;
                break;
            }
            if(stop) 
                break;
            system ("cls");
            cout << title << endl;
            for(int i = 0; i < nOption; i++) {
                if(i == option) {
                    SetConsoleTextAttribute(color, 2);
                    cout << arrOption[i] << endl;
                    SetConsoleTextAttribute(color, 7);
                } else cout << arrOption[i] << endl;
            }
        }
    }
    return option;
}
Course* findCourse_ofStudent_byOption(CourseStudent *courseHead, int option) 
{
    int index = 0;
    while(courseHead) 
    {
        if(index == option)
            return courseHead->course;
        courseHead = courseHead->next;
    }
    return nullptr;
}
void UpdateStudentResult(Year *Yhead) 
{
    system ("cls");
    // //chọn 1 để nhập số bao danh học sinh cần sửa sau đó nhập khóa học
    // //chọn 2 để chọn khóa học có học sinh cần sửa điểm, sau đó chọn học sinh
    int nOption = 3;
    string *arrOption = new string [nOption];
    arrOption[0] = "1. Find student who need to update by ID.";
    arrOption[1] = "2. Find course which have score board need to update.";
    arrOption[2] = "3. To end to update.";
    
    string title = "Using arrow keys to move and press enter to choose your option";
    system("cls");
    int option = view_chooseOption(arrOption,nOption, title);
    // int option = 1;
    delete []arrOption;

    system ("cls");
    string IDStudent = "22127123";
    string CourseName = "CSC10002";

    if (option == 0) 
    {
        system ("cls");
        cout << "Please enter ID: ";
        getline(cin, IDStudent);
        Student *checkStudent = findStudentbyID(IDStudent, Yhead);

        // để khi nhập sai có thể báo ra
        nOption = 2;
        arrOption = new string [nOption];
        arrOption[0] = "-To re-enter again.";
        arrOption[1] = "-To end to update";

        while (!checkStudent) 
        {
            title = "The ID you entered does not exist. Please, press enter to choose below option to continue:";
            system ("pause");
            system ("cls");
            option = view_chooseOption(arrOption,nOption, title);
            if(option == 1) 
            {
                delete []arrOption;
                return;
            }
            cout << "Please re-enter ID: ";
            getline(cin, IDStudent);
            Student *checkStudent = findStudentbyID(IDStudent, Yhead);
        }

        // system ("cls");
        // //in ra các khóa của học sinh đó (trong kì đó), cho user nhập tên hoặc ID của khóa học để ra bản điểm để chỉnh sửa
        // cout << "Please enter name course or ID course:"; 
        // getline(cin, CourseName);

        //select khóa học
        CourseStudent *curCourse = checkStudent->course;
        nOption = 0;
        while (curCourse) 
        {
            nOption ++;
            curCourse = curCourse->next;
        }
        arrOption = new string [nOption+1];
        curCourse = checkStudent->course;
        for(int i = 0; i < nOption; i++)
        {
        arrOption[i] = curCourse->course->Name;
        curCourse = curCourse->next;
        }
        arrOption [nOption] = "<-";
        title = "Please enter to select course:";
        option = view_chooseOption(arrOption,nOption+1, title);
        delete []arrOption;
        if(option == nOption) return;

        Course *checkCourse = findCourse_ofStudent_byOption(checkStudent->course,option);
        
        //bắt đầu update
        updateSBC(IDStudent, checkCourse->studentCourse);
    }


    //nếu chọn 2:
    if (1 == option) 
    {
        // system ("cls");

        // //in ra các khóa của học sinh đó (trong kì đó), cho user nhập tên hoặc ID của khóa học để ra bản điểm để chỉnh sửa
        // title =  "Please enter name course or ID course:"; 
        // getline(cin, CourseName);
        // Course *checkCourse = findCoursebyName_ID(CourseName,Yhead);
        // while (!checkCourse) 
        // {
        //     system ("cls");
        //     title = "The ID or name you entered does not exist. Enter:";
        //     option = view_chooseOption(arrOption,nOption, title);
        //     delete []arrOption;
        //     if(option == 1) {
        //         delete []arrOption;
        //         return;
        //     }
        //     getline(cin, CourseName);
        //     Course *checkCourse = findCoursebyName_ID(CourseName,Yhead);
        // }

        Year *ChooseYear = nullptr;
        Semester *ChooseSem = nullptr;
        Course *ChooseCourse = nullptr;
        if(Yhead == nullptr){
            cout << "There are no school year.";
            system("pause");
            // gọi lại hàm mainmenu
            return;
        }
        do {
            ChooseYear = chooseYearbyOption(Yhead);
            if(ChooseYear == nullptr){
                //quay lại main menu
                return;
            }
            system("cls");
            do {
                if(ChooseYear->NoSemester == nullptr) {
                    cout << "There are no semester in this school year."  << endl;
                    system("pause");
                    break;
                }
                ChooseSem = chooseSemesterbyOption(ChooseYear->NoSemester);
                system("cls");

                if(ChooseSem){
                    if(ChooseSem->course == nullptr) {
                        cout << "There are no course in this semester" << endl;
                        system("pause");

                    } else{
                        ChooseCourse = chooseCoursebyOption(ChooseSem->course);
                    }
                    system("cls"); 
                } else 
                    break;
            }while(ChooseCourse == nullptr);
            
        } while (ChooseSem == nullptr);

        
        system ("cls");
        //hàm xem danh sách sinh viên trong khóa học

        cout << "Please enter ID: ";    
        getline(cin, IDStudent);
        StudentCourse *stuUpdate = find_SBC(IDStudent, ChooseCourse->studentCourse);
        if(stuUpdate == nullptr) {
            cout << "student is not exist.\n";
            system("pause");
            return;
        }
        // while (!checkStudent) 
        // {
        //     system ("cls");
        //     nOption = 2;
        //     string *arrOption = new string [nOption];
        //     arrOption[0] = "-To re-enter again.";
        //     arrOption[1] = "-To end to update";
        //     title = "The ID you entered does not exist. Would you want:";
        //     option = view_chooseOption(arrOption,nOption, title);
        //     delete []arrOption;
        //     if(option == 1) {
        //         delete []arrOption;
        //         return;
        //     }
        //     getline(cin, IDStudent);
        //     Student *checkStudent = findStudentbyID(IDStudent, Yhead);
        // }
        // delete []arrOption;
        updateSBC(IDStudent, ChooseCourse->studentCourse);
        return;
    }
    //không phải 0 hoặc 1 thì se thoát
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
// nhập các final mark vào bảng điểm của lớp 
void importSB_ofStudent_inClass(double *&SBC, CourseStudent *courseHead, Student *studentHead) {
    StudentCourse *tmp;
    CourseStudent *courseCheck;
    int i = 0;
    while (courseHead) 
    {
        courseCheck = checkExistence_OfCourse(courseHead,studentHead->course);
        if (courseCheck) 
        {
            tmp = find_SBC(studentHead->ID, courseHead->course->studentCourse);
                SBC[i++] = tmp->ScoreBoardCourse.finalMark;
        } else 
            SBC[i++] = -1; // -1 là hs này không học môn đó
        courseHead = courseHead->next;
    }
}
double CaculateGPA_1_Student(double *&SBC, int n) // n là số môn, tức là số cột của bảng SBC. n là số đã trừ cột cuối ra 
{
    double GPA = 0;
    int count = 0; // biến này để đếm xem học sinh này học bao nhiêu môn
    for(int i = 0; i < n; i++) 
    {
        if ( SBC[i] >= 0)
        {
            GPA += SBC[i];
            count ++;
        }        
    }
    if (count != 0) 
        GPA /= count;
    return GPA;
}
void createSBC_ofClass(double **&SBC, CourseStudent *courseHead, Student *studentHead, int Col, int Row )
{
    SBC = new double*[Col + 1] ;
    for(int i = 0; i<Row; i++)
    {
        SBC[i] = new double[Col+1]; // +1 là + 1 cột cuối để lưu GPA của học sinh đó trong kì này
        importSB_ofStudent_inClass(SBC[i], courseHead, studentHead);
        SBC[i][Col] = CaculateGPA_1_Student(SBC[i], Col);
        studentHead = studentHead->next;
    }
}
// mảng này sẽ có dạng | môn A | môn B |....| môn Z | GPA |
void viewAllFinalMark_ofStudent(double *SBC, int Col)
{
    for( int i = 0; i < Col; i++) 
    {
        if(SBC[i] < 0)
            cout << setw(30) << left << "| X";
        else 
            cout << "| " << setw(30) << left  << setprecision(1) << fixed  << SBC[i];
    }                             
}
void viewScoreboardClass(Class *Class) 
{
    Student *studentHead = Class->StudentClass;
    CourseStudent *courseHead = CourseOfAClass(studentHead);
    int Col = CaculateAmountCourseOfClass(courseHead);
    int Row = CaculateAmountStudentOfClass(studentHead);
    double **SBC;
    createSBC_ofClass(SBC,courseHead,studentHead,Col,Row);
    for(int i = 0; i < 79 ; i++) {
        cout <<"_";
    }
    cout << endl;
    cout << setw(12) << left << "| ID";
    cout << setw(27) << left << "| Full Name";
    while (courseHead)
    {
        cout <<"| " << setw(30) << left <<courseHead->course->Name;
        courseHead = courseHead->next;
    }
    cout << setw(7) << left << "| GPA"; 
    cout << "|" << endl;

    int i = 0;
    while (studentHead) 
    {
        for(int i = 0; i < 79 ; i++) {
        cout <<"=";
        }
        cout << endl;
        cout << "| " << setw(10) << left  << studentHead->ID;
        cout << "| " << setw(25) << left << studentHead->accStudent->lastName + " " + studentHead->accStudent->firstName;
        viewAllFinalMark_ofStudent(SBC[i], Col);
        cout << "| "<< setw(5) << left  << setprecision(1) << fixed << CaculateGPA_1_Student(SBC[i++], Col); 
        cout << "|" << endl;
        studentHead = studentHead->next;
    }
    for(int i = 0; i<Row; i++)
        delete []SBC[i];
    delete []SBC;
}




// test task 21
// int main() {
//     Year *yr = new Year;
//     yr->yearStart = 2022;

//     yr->NoSemester = new Semester;
//     yr->NoSemester->No = 2;

//     yr->NoSemester->course = new Course;
//     yr->NoSemester->course->Name = "CSC10002";
//     yr->NoSemester->course->next = new Course;
//     yr->NoSemester->course->next->Name = "BBA00101";
//     readAllFileCourses(yr);
//     StudentCourse *stuHead = yr->NoSemester->course->studentCourse;


//     viewScoreBoardCourse(yr->NoSemester->course);

//     deleteAllCourse(yr);
//     return 0;
// }

//test task 22 + 19
// int main() {
//     Year *yr = new Year;
//     yr->yearStart = 2022;

//     yr->NoSemester = new Semester;
//     yr->NoSemester->Year = 2022;
//     yr->NoSemester->No = 2;
//     yr->NoSemester->next = new Semester;
//     yr->NoSemester->next->Year = 2022;
//     yr->NoSemester->next->No = 1;

//     yr->NoSemester->course = new Course;
//     yr->NoSemester->course->Name = "CSC10002";
//     yr->NoSemester->course->TeacherName = "Dinh Ba Tien";
//     readAllFileCourses(yr);
//     StudentCourse *stuHead = yr->NoSemester->course->studentCourse;
//     // while (stuHead) {
//     //     cout << stuHead->ID << endl;
//     //     stuHead = stuHead->next;
//     // }

//     yr->Class = new Class;
//     yr->Class->StudentClass = new Student;
//     yr->Class->StudentClass->ID = "22127123";
//     yr->Class->StudentClass->course = new CourseStudent;
//     yr->Class->StudentClass->course->course = yr->NoSemester->course;
//     yr->Class->StudentClass->accStudent = new Account;
//     yr->Class->StudentClass->accStudent->firstName = "Hoang";
//     yr->Class->StudentClass->accStudent->lastName = "Le Ho Phi";
//     // 22127124,Nguyen Van A
//     yr->Class->StudentClass->next = new Student;
//     yr->Class->StudentClass->next->ID = "22127124";
//     yr->Class->StudentClass->next->course = new CourseStudent;
//     yr->Class->StudentClass->next->course->course = yr->NoSemester->course;
//     yr->Class->StudentClass->next->accStudent = new Account;
//     yr->Class->StudentClass->next->accStudent->firstName = "A";
//     yr->Class->StudentClass->next->accStudent->lastName = "Nguyen Van";

//     UpdateStudentResult(yr);
//     exportListStudentCourse(yr->NoSemester);
//     // viewScoreboardClass(yr->Class);
//     // UpdateStudentResult(yr);
//     delete yr->Class->StudentClass->next->accStudent;
//     delete yr->Class->StudentClass->accStudent;
//     delete yr->Class->StudentClass->next->course;
//     delete yr->Class->StudentClass->course;
//     delete yr->Class->StudentClass->next;
//     delete yr->Class->StudentClass;
//     delete yr->Class;
//     deleteAllCourse(yr);
//     return 0;
// }

//test task 23
// int main() {
//     Year *yr = new Year;
//     yr->yearStart = 2022;

//     yr->NoSemester = new Semester;
//     yr->NoSemester->No = 2;

//     yr->NoSemester->course = new Course;
//     yr->NoSemester->course->Name = "CSC10002";
//     yr->NoSemester->course->TeacherName = "Dinh Ba Tien";
//     readAllFileCourses(yr);
//     StudentCourse *stuHead = yr->NoSemester->course->studentCourse;
//     while (stuHead) {
//         cout << stuHead->ID << endl;
//         stuHead = stuHead->next;
//     }

//     yr->Class = new Class;
//     yr->Class->StudentClass = new Student;
//     yr->Class->StudentClass->ID = "22127123";
//     yr->Class->StudentClass->course = new CourseStudent;
//     yr->Class->StudentClass->course->course = yr->NoSemester->course;
//     yr->Class->StudentClass->accStudent = new Account;
//     yr->Class->StudentClass->accStudent->firstName = "Hoang";
//     yr->Class->StudentClass->accStudent->lastName = "Le Ho Phi";
//     // 22127124,Nguyen Van A
//     yr->Class->StudentClass->next = new Student;
//     yr->Class->StudentClass->next->ID = "22127124";
//     yr->Class->StudentClass->next->course = new CourseStudent;
//     yr->Class->StudentClass->next->course->course = yr->NoSemester->course;
//     yr->Class->StudentClass->next->accStudent = new Account;
//     yr->Class->StudentClass->next->accStudent->firstName = "A";
//     yr->Class->StudentClass->next->accStudent->lastName = "Nguyen Van";

//     viewScoreboardClass(yr->Class);
//     deleteAllCourse(yr);
//     return 0;
// }