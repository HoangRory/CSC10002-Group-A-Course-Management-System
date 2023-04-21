#include "../Header/course.h"
#include "../Header/Utility.h"
#include <math.h>
//all
int view_chooseOption(string *arrOption, int nOption, string title) 
{
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
//task 14: view the list of courses of a stundent in a semester
void ViewCoursesOfAStudent(Account *accHead, Course *courseHead) //courseHead in a semester, accHead is current account after the student login
{
    system("cls");
    Render_Course(40,1);
    Render_Student(35,7);
    int x = 20, y = 15;
    goToXY(x,y++);
    cout << "All course of " << accHead->lastName+" "+accHead->firstName << ". MSSV: " << accHead->username;
    goToXY(x, y++);
    for (int i = 1; i <= 115; i++)
        cout << "=";
    goToXY(x, y++);
    cout << "| " << setw(10) << left << "ID";
    cout << "| " << setw(28) << left << "Name";
    cout << "| " << setw(9)  << left << "Credits";
    cout << " | " << setw(9) << left<< "Day";
    cout << " | " << setw(9) << left<< "Session";   
    cout << " | " << setw(9) << left << "Room";  
    cout << " | " << setw(22) << left << "TeacherName ";
    cout << "|";   
    goToXY(x, y++);
    for (int i = 1; i <= 115; i++)
        cout << "=";
    
    
    while (courseHead)
    {
        StudentCourse *cur_stu = courseHead->studentCourse;
        while (cur_stu)
        {
            if (cur_stu->ID == accHead->username)
            {
                goToXY(x, y++);
                cout << "| " << setw(10) << left << courseHead->CourseID;
                cout << "| " << setw(28) << left << courseHead->Name;
                cout << "| " << setw(9)  << right << courseHead->Credits;
                cout << " | " << setw(9) << left << courseHead->Day;
                cout << " | " << setw(9) << left << courseHead->Session;   
                cout << " | " << setw(9) << left << courseHead->Room;  
                cout << " | " << setw(22) << left << courseHead->TeacherName;
                cout << "|";       
                goToXY(x, y++);
                for (int i = 1; i <= 115; i++)
                    cout << "=";
                break;
            }
            cur_stu = cur_stu->next;
        }
        courseHead = courseHead->next;
    }
}
//task 15: view all classes which are existed
void ViewClass(Year* yearHead)
{
    system("cls");
    int x = 40, y = 2;  
    Render_Class(x, y);
    Year *ChooseYear = chooseYearbyOption_XY(yearHead, 60, 15, 5);
    if(ChooseYear == nullptr)
        return;
        //gọi lại hàm mainmenu
    system("cls");
    x= 40, y = 2;
    Render_Class(x, y);
    y = 10;
    Class *cls_cur = ChooseYear->Class;
    goToXY(x,y++);
    cout << "List of class in school year " << ChooseYear->yearStart << "-" << ChooseYear->yearStart + 1 ; // seperate the list into many parts by the school year
    goToXY(x,y++);
    for (int i = 0; i < 38 ; i++)
        cout << '=';
    while (cls_cur)
    {
        goToXY(x,y++);
        cout  << setw(14) << left << "|"  << setw(10) << cls_cur->Name << setw(14) << right << "|";
        cls_cur = cls_cur->next;
        goToXY(x,y++);
        for (int i = 0; i < 38; i++)
            cout << '=';
    }
    Pause();
}
//task 16: view students in a class 
void ViewStudentsClass(Year *yearHead)
{   
    system("cls");
    // Render_View();
    int x = 60, y = 16;
    Render_StudentClass();
    Year *ChooseYear = chooseYearbyOption_XY(yearHead, x, y,5);
    if(ChooseYear == nullptr)
        return;
        //gọi lại hàm mainmenu
    system("cls");
    // Render_View();
    Render_StudentClass();
    Class *ChooseClass = chooseClassbyOption_XY(ChooseYear->Class, x,y,5);
    if(ChooseClass == nullptr) {
        ViewStudentsClass(yearHead);
        return;
    }

    system("cls");
    // Render_View();
    Render_StudentClass();
    Student *currStudent = ChooseClass->StudentClass;
    x = 50,y = 16;
    if(currStudent) 
    {
        goToXY(x,y++);
        cout <<  "List of students in " << ChooseClass->Name;
        goToXY(x,y++);
        for (int i = 1; i <= 57; ++i)
            cout << "=";
        goToXY(x,y++);
        cout << setw(8) << left << "|" << setw(12) << "ID" << "|";
        cout << setw(10) << " " << setw(25) << "Full Name " << "|";
        goToXY(x,y++);
        for (int i = 1; i <= 57; ++i)
            cout << "=";
    }
    else 
        Message_Warning("There is no student in " + ChooseClass->Name, "Error");
    while (currStudent)
    {
        string fullname = currStudent->accStudent->lastName +" "+ currStudent->accStudent->firstName;
        goToXY(x,y++);
        cout << setw(5) << left << "|" << setw(15) << currStudent->ID << "|"; 
        cout << setw(8) << " " << setw(27) << left  << fullname << "|" ;
        goToXY(x,y++);
        for (int i = 1; i <= 57; ++i)
            cout << "=";
        currStudent = currStudent->next;
    }
    Pause();
}
// task 17: view the list of courses in a semester of a school year, different with view course in task 9
// void ViewCourse(Year *yearHead)
// {
// // mới viết
//     Year *ChooseYear = nullptr;
//     Semester *ChooseSem = nullptr;
//     Course *ChooseCourse = nullptr;
//     if(yearHead == nullptr){
//         Message_Warning("There are no school year.", "Error not exist");
//         // gọi lại hàm mainmenu
//         return;
//     }
//     do {
//         ChooseYear = chooseYearbyOption(yearHead);
//         if(ChooseYear == nullptr){
//             //quay lại main menu
//             return;
//         }
//         system("cls");
//         do {
//             if(ChooseYear->NoSemester == nullptr) {
//                 Message_Warning("There are no semester in this school year.", "Error not exist");
//                 break;
//             }
//             ChooseSem = chooseSemesterbyOption(ChooseYear->NoSemester);
//             system("cls");

//             if(ChooseSem){
//                 if(ChooseSem->course == nullptr) {
//                     Message_Warning("There are no course in this semester","Error not exist");
//                 } else{
//                     ChooseCourse = chooseCoursebyOption(ChooseSem->course);
//                 }
//                 system("cls"); 
//             } else 
//                 break;
//         }while(ChooseCourse == nullptr);
        
//     } while (ChooseSem == nullptr);
// // phía trên là để chọn được course
//     cout << "\nList of courses in the semester " << ChooseSem->No << " of the " << ChooseSem->Year << "-" << ChooseSem->Year + 1 << " school year:" << endl;
//     for (int i = 1; i <= 70; ++i)
//         cout << "=";
//     cout << "\n";
//     cout << "|    ID" << setw(18) << "|         Name" << setw(33) << "|       Teacher" << setw(13) << "|\n"; 
//     for (int i = 1; i <= 70; ++i)
//         cout << "=";
//     cout << "\n";
//     while (ChooseCourse)
//     {
//         cout << "| " << ChooseCourse->CourseID << " | ";
//         cout << ChooseCourse->Name << setw(32 - ChooseCourse->Name.length()) << "| ";  
//         cout << ChooseCourse->TeacherName << setw(26 - ChooseCourse->TeacherName.length()) << "|\n";
//         for (int i = 1; i <= 70; ++i)
//             cout << "=";
//         cout << "\n";
//         ChooseCourse = ChooseCourse->next;
//     }
// }
// //task 18: view students in a course 
void ViewStudentCourse(Year *yearHead)
{
    system("cls");
    //in ra chư studentcourse
    Year *ChooseYear = nullptr;
    Semester *ChooseSem = nullptr;
    Course *ChooseCourse = nullptr;
    Render_StudentCourse();
    int x = 60, y = 20;
    if(yearHead == nullptr){
        Message_Warning("There are no school year.","Error not exist");
        // gọi lại hàm mainmenu
        return;
    }
    do {
        ChooseYear = chooseYearbyOption_XY(yearHead, x, y,5);
        if(ChooseYear == nullptr){
            //quay lại main menu
            return;
        }
        Render_StudentCourse();
        do {
            if(ChooseYear->NoSemester == nullptr) {
                Message_Warning("There are no semester in this school year.","Error not exist");
                break;
            }
            ChooseSem = chooseSemesterbyOption_XY(ChooseYear->NoSemester,x,y,5);
            Render_StudentCourse();
            if(ChooseSem){
                if(ChooseSem->course == nullptr) {
                    Message_Warning("There are no course in this semester", "Error not Exist");
                } else{
                    ChooseCourse = chooseCoursebyOption_XY(ChooseSem->course,x,y,5);
                }
                Render_StudentCourse();
            } else 
                break;
        }while(ChooseCourse == nullptr);
        
    } while (ChooseSem == nullptr);

    //này là để chọn được course
    system("cls");
    Render_StudentCourse();
    StudentCourse *currStudent = ChooseCourse->studentCourse;
    if(!currStudent) {
        Message_Warning(" There is no student in course " + ChooseCourse->Name, "Error not exist");
        system("cls");
        return;
    }
    
    x = 50;
    goToXY(x,y++);
    cout <<  "List of students in " << ChooseCourse->Name;
    goToXY(x,y++);
    for (int i = 1; i <= 57; ++i)
        cout << "=";
    goToXY(x,y++);
    cout << setw(8) << left << "|" << setw(12) << "ID" << "|";
    cout << setw(10) << " " << setw(25) << "Full Name " << "|";
    goToXY(x,y++);
    for (int i = 1; i <= 57; ++i)
        cout << "=";

    while (currStudent)
    {

        goToXY(x,y++);
        cout << setw(5) << left << "|" << setw(15) << currStudent->ID << "|"; 
        cout << setw(8) << " " << setw(27) << left  << currStudent->FullName << "|" ;
        goToXY(x,y++);
        for (int i = 1; i <= 57; ++i)
            cout << "=";
        currStudent = currStudent->next;
    }
    Pause();
}
//này của task 21
void viewScoreBoardCourse(Course *courseHead) 
{
    system("cls");
    Render_ScoreBoardCourse();
    Course *curCourse = chooseCoursebyOption_XY(courseHead, 65, 20,5);
    if(!curCourse) {
        Message_Warning("There aren't any courses for the current semester.", "Error not exist");
        //quay lại menu chính
        return;
    }
    //? đem cái đống trên ra ngoài
    Render_ScoreBoardCourse();
    StudentCourse *stuHead = curCourse->studentCourse;
    int x = 25, y = 18;
    goToXY(x,y++);
    cout <<  "ScoreBoard of students in " << curCourse->Name;
    goToXY(x,y++);
    for(int i = 0; i < 110 ; i++)
        cout <<"=";
    goToXY(x,y++);
    cout << "| " << setw(12) << left << "ID";
    cout << "| " << setw(25) << left << "Full Name";
    cout << "| " << setw(15) << left << "Mid Mark"; 
    cout << "| " << setw(15) << left << "Final Mark";
    cout << "| " << setw(15) << left << "Total Mark" ; 
    cout << "| " << setw(15) << left << "Other Mark" ;
    cout << "| ";
    while (stuHead) 
    {
        goToXY(x,y++);
        for(int i = 0; i < 110 ; i++)
            cout <<"=";
        goToXY(x,y++);
        cout << "| " << setw(12) << left << stuHead->ID;
        cout << "| " << setw(25) << left<< stuHead->FullName;
        cout << "| " << setw(15) << left << stuHead->ScoreBoardCourse.midMark; 
        cout << "| " << setw(15) << left << stuHead->ScoreBoardCourse.finalMark;
        cout << "| " << setw(15) << left << stuHead->ScoreBoardCourse.totalMark; 
        cout << "| " << setw(15) << left << stuHead->ScoreBoardCourse.otherMark << right << "|";
        stuHead = stuHead->next;
    }
    goToXY(x,y++);
    for(int i = 0; i < 110 ; i++)
        cout <<"=";
    Pause();
}
//task 23 
// mảng này sẽ có dạng | môn A | môn B |....| môn Z | GPA |
void viewAllFinalMark_ofStudent(double *SBC, int Col, int Col_cur)
{
    for( int i = 0; i < min (3,Col-Col_cur); i++) 
    {
        if(SBC[i + Col_cur] < 0)
            cout << setw(32) << left << "| X";
        else 
            cout << "| " << setw(30) << left  << setprecision(1) << fixed  << SBC[i +Col_cur];
    }                             
}
void viewScoreboardClass(Class *Class) 
{
    Student *student_cur = Class->StudentClass;
    // Student *student_back = Class->StudentClass;
    if(student_cur == nullptr) {
        Message_Warning(" There is no student in course " + Class->Name, "Error not exist");
        return;
    }
    CourseStudent *courseHead = CourseOfAClass(student_cur);
    if(courseHead == nullptr) {
        Message_Warning("There are no course", "Error not exist");
        return;
    }
    CourseStudent *course_cur = courseHead;
    // CourseStudent *course_back = courseHead;
    int Col = amountCourseOfClass(courseHead);
    int Row = amountStudentOfClass(student_cur);
    double **SBC;
    createSBC_ofClass(SBC,courseHead,student_cur,Col,Row);
    
    int key = 0;
    vector<string> move;
    if(Col >3 && Row <= 8) {
        move.push_back("<");
        move.push_back(">");
        key = 1;
    } else if( Col <= 3 && Row >8) {
        move.push_back("^");
        move.push_back("v");
        key = 2;
    } else if(Col >3 && Row > 8) {
        move.push_back("^");
        move.push_back("v");
        move.push_back("<");
        move.push_back(">");
        key = 3;
    }
    move.push_back("X");

    int Col_cur = 0, Row_cur = 0,
        cur = 0,
        x, y;
    bool stop = false;
    while(!stop) {
        x = 5; y = 14;
        system ("cls");
        Render_ScoreBoardClass();
        goToXY(x,y++);
        for(int i = 0; i < 47 + 32* min(3, Col-Col_cur) ; i++) {
            cout << "=";
        }
        goToXY(x,y++);
        cout << setw(12) << left << "| ID";
        cout << setw(27) << left << "| Full Name";
        
        for(int i = 0; i < min (3,Col-Col_cur); i++)
        {
            cout <<"| " << setw(30) << left <<course_cur->course->Name;
            course_cur = course_cur->next;
        }
        if(Col - Col_cur <= 3)
            cout << setw(7) << left << "| GPA"; 
        cout << "|" ;
        int i = 0;
        for(int i = 0; i < min(8,Row-Row_cur); i++){
            goToXY(x,y++);
            for(int i = 0; i < 47 + 32*min(3,Col-Col_cur) ; i++) 
            cout <<"=";
            goToXY(x,y++);
            cout << "| " << setw(10) << left  << student_cur->ID;
            cout << "| " << setw(25) << left << student_cur->accStudent->lastName + " " + student_cur->accStudent->firstName;
            viewAllFinalMark_ofStudent(SBC[Row_cur + i], Col, Col_cur);
            if(Col - Col_cur <= 3)
                cout << "| "<< setw(5) << left  << setprecision(1) << fixed << CaculateGPA_1_Student(SBC[Row_cur + i], Col); 
            cout << "|";
            student_cur = student_cur->next;
        }
        goToXY(x,y++);
        for(int i = 0; i < 47 + 32*min (3, Col-Col_cur) ; i++) 
            cout <<"=";
        goToXY(x,y);
        cout << "Page " << (int) ceil(1.0*(Col_cur + 1) / 3) << "/" << (int) ceil((1.0*Col) / 3);
        int option = Draw_Horizontal_XY(move, x + 47, y, cur);
        // int option = 2;
        if(key == 0) stop = true;
        else if(key == 1) {
            student_cur = Class->StudentClass;
            switch (option)
            {
            case 0:
                if(Col_cur >= 3) 
                    Col_cur -= 3;
                course_cur = courseHead;   
                for( int i = 0;  i < Col_cur; i ++)
                    course_cur = course_cur->next;
                break;
            case 1:
                if(Col_cur + 3 >= Col){
                    course_cur = courseHead;
                    for( int i = 0; i < Col_cur; i ++) 
                        course_cur = course_cur->next;
                } else 
                    Col_cur += 3;
                break;
            case 2:
                stop = true;
                break;
            default:
                break;
            }
        }
        else if(key == 2) {
            course_cur = courseHead;
            switch (option)
            {
            case 0:
                if(Row_cur >= 8) 
                    Row_cur -= 8;   
                student_cur = Class->StudentClass;
                for( int i = 0; i < Row_cur; i ++) 
                    student_cur = student_cur->next;
                break;
            case 1:
                if(Row_cur + 8 >= Row){
                    student_cur = Class->StudentClass;
                    for( int i = 0; i < Row_cur; i ++) 
                        student_cur = student_cur->next;
                } else Row_cur += 8;
                break;
            case 2:
                stop = true;
                break;
            default:
                break;
            }
        }
        else if(key == 3) {
            switch (option)
            {
            case 0:
                course_cur = courseHead;
                for(int i = 0; i < Col_cur; i++)
                    course_cur = course_cur->next;
                if(Row_cur >= 8)
                     Row_cur -= 8;   
                student_cur = Class->StudentClass;
                for( int i = 0; i < Row_cur; i ++) 
                    student_cur = student_cur->next;  
                break;
            case 1:
                course_cur = courseHead;
                for(int i = 0; i < Col_cur; i++)
                    course_cur = course_cur->next;
                if(Row_cur + 8 >= Row){
                    student_cur = Class->StudentClass;
                    for( int i = 0; i < Row_cur; i ++) 
                        student_cur = student_cur->next;
                } else 
                    Row_cur += 8;
                break;
            case 2:
                student_cur = Class->StudentClass;
                for( int i = 0; i < Row_cur; i ++) 
                    student_cur = student_cur->next;
                if(Col_cur >= 3) 
                    Col_cur -= 3;
                course_cur = courseHead;
                for( int i = 0;  i < Col_cur; i ++)
                    course_cur = course_cur->next;
                break;
            case 3:
                student_cur = Class->StudentClass;
                for( int i = 0; i < Row_cur; i ++) 
                    student_cur = student_cur->next;
                if(Col_cur + 3 >= Col){
                    course_cur = courseHead;
                    for( int i = 0; i < Col_cur; i ++) 
                        course_cur = course_cur->next;
                } else 
                    Col_cur += 3;
                break;
            case 4:
                stop = true;
                break;
            default:
                break;
            }
        }    
    }

    for(int i = 0; i<Row; i++)
        delete []SBC[i];
    delete []SBC;  
}
//task 24: view scoreboard of all course of a student in a semester
void ViewScoreboard(Account *accHead, Course *courseHead)
{
    system("cls");
    Render_ScoreBoard(25,1);
    int x = 35, y = 8;
    
    goToXY(x,y++);
        cout << "ScoreBoard of " << accHead->lastName+" "+accHead->firstName << ". MSSV: " << accHead->username;
    goToXY(x,y++);
    for (int i = 1; i <= 89; i++)
        cout << "=";
    goToXY(x,y++);
    cout << setw(28) << left  << "| Subject" << setw(15)<< "| Mid mark" << setw(15) << "| Final mark" << setw(15) << "| Other mark"  << setw(15) << "| Total mark" << "|" ;
    goToXY(x,y++); 
    for (int i = 1; i <= 89; i++)
        cout << "=";
    while (courseHead)
    {
        StudentCourse *cur_stu = courseHead->studentCourse;
        while (cur_stu)
        {
            
            if (cur_stu->ID == accHead->username) //truy cập từng student trong từng course check ID 
            {
                goToXY(x,y++);
                cout <<  "| " << setw(25) << courseHead->Name;
                cout <<  " | " << setw(12) << right << cur_stu->ScoreBoardCourse.midMark;
                cout <<  " | " << setw(12) << right << cur_stu->ScoreBoardCourse.finalMark;
                cout <<  " | " << setw(12) << right << cur_stu->ScoreBoardCourse.otherMark;
                cout <<  " | " << setw(12) << right << cur_stu->ScoreBoardCourse.totalMark << " |";
                goToXY(x,y++);
                for (int i = 1; i <= 89; i++)
                    cout << "=";
            }
            cur_stu = cur_stu->next;
        }
        courseHead = courseHead->next;
    }
}