#include "../Header/course.h"
#include "../Header/Utility.h"

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
    for (int i = 1; i <= 112; i++)
        cout << "=";
    cout << "\n";
    cout << "|    ID" << setw(20) << "Name"<< setw(21) << "Credit" << setw(11) << "Day" << setw(15)  << "Session"  << setw(10) << "Room" << setw(15) << "Teacher" << setw(13) << "|" << endl; 
    for (int i = 1; i <= 112; i++)
        cout << "=";
    cout << "\n";
    
    while (courseHead)
    {
        StudentCourse *cur_stu = courseHead->studentCourse;
        while (cur_stu)
        {
            if (cur_stu->ID == accHead->username)
            {
                cout << "| " << courseHead->CourseID;
                cout << "       " << courseHead->Name;
                cout << setw(29 - courseHead->Name.length()) << right << courseHead->Credits;
                cout << setw(13) << right << courseHead->Day;
                cout << setw(12) << right << courseHead->Session;   
                cout << setw(12) << right << courseHead->Room;  
                cout << "         " << courseHead->TeacherName << setw(20 - courseHead->TeacherName.length()) << "|";       
                cout << "\n";
                break;
            }
            cur_stu = cur_stu->next;
        }
        courseHead = courseHead->next;
    }
    for (int i = 1; i <= 112; i++)
        cout << "=";
}
//task 15: view all classes which are existed
void ViewClass(Year* yearHead)
{
    system("cls");
    // Render_View();
    Render_Class();
    Year *ChooseYear = chooseYearbyOption(yearHead);
    if(ChooseYear == nullptr)
        return;
        //gọi lại hàm mainmenu
    system("cls");
    // Render_View();
    Render_Class();
    int x = 55, y = 15;
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
    Year *ChooseYear = chooseYearbyOption_XY(yearHead, x, y);
    if(ChooseYear == nullptr)
        return;
        //gọi lại hàm mainmenu
    system("cls");
    // Render_View();
    Render_StudentClass();
    Class *ChooseClass = chooseClassbyOption_XY(ChooseYear->Class, x,y);
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
        ChooseYear = chooseYearbyOption_XY(yearHead, x, y);
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
            ChooseSem = chooseSemesterbyOption_XY(ChooseYear->NoSemester,x,y);
            Render_StudentCourse();
            if(ChooseSem){
                if(ChooseSem->course == nullptr) {
                    Message_Warning("There are no course in this semester", "Error not Exist");
                } else{
                    ChooseCourse = chooseCoursebyOption_XY(ChooseSem->course,x,y);
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
    Course *curCourse = chooseCoursebyOption_XY(courseHead, 65, 20);
    if(!curCourse) {
        Message_Warning("There aren't any courses for the current semester.", "Error not exist");
        //quay lại menu chính
        return;
    }
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
        if(SBC[i] < 0)
            cout << setw(27) << left << "| X";
        else 
            cout << "| " << setw(25) << left  << setprecision(1) << fixed  << SBC[i];
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

    int Col_cur = 0, Row_cur = 0;
    int x , y ;

    bool stop = false;
    while(!stop) {
        x = 15; y = 15;
        system ("cls");
        Render_ScoreBoardClass();
        goToXY(x,y++);
        for(int i = 0; i < 47 + 27* min(3, Col-Col_cur) ; i++) {
            cout << "=";
        }
        goToXY(x,y++);
        cout << setw(12) << left << "| ID";
        cout << setw(27) << left << "| Full Name";
        
        for(int i = 0; i < min (3,Col-Col_cur); i++)
        {
            cout <<"| " << setw(25) << left <<course_cur->course->Name;
            course_cur = course_cur->next;
        }
        cout << setw(7) << left << "| GPA"; 
        cout << "|" ;
        int i = 0;
        for(int i = 0; i < min(8,Row-Row_cur); i++){
            goToXY(x,y++);
            for(int i = 0; i < 47 + 27*min(3,Col-Col_cur) ; i++) 
            cout <<"=";
            goToXY(x,y++);
            cout << "| " << setw(10) << left  << student_cur->ID;
            cout << "| " << setw(25) << left << student_cur->accStudent->lastName + " " + student_cur->accStudent->firstName;
            viewAllFinalMark_ofStudent(SBC[Row_cur + i], Col, Col_cur);
            cout << "| "<< setw(5) << left  << setprecision(1) << fixed << CaculateGPA_1_Student(SBC[Row_cur + i], Col); 
            cout << "|" << endl;
            student_cur = student_cur->next;
        }
        goToXY(x,y++);
        for(int i = 0; i < 47 + 27*min (3, Col-Col_cur) ; i++) 
            cout <<"=";
        int option = Draw_Horizontal_XY(move, x + 47, y);
        // int option = 1;
        if(key == 0) stop = true;
        else if(key == 1) {
            student_cur = Class->StudentClass;
            switch (option)
            {
            case 0:
                if(Col_cur - 3 < 0) 
                    Message_Warning("This is the front page", "Error"); 
                else 
                    Col_cur -= 3;
                course_cur = courseHead;   
                for( int i = 0;  i < Col_cur; i ++)
                    course_cur = course_cur->next;
                break;
            case 1:
                if(Col_cur + 3 >= Col){
                    Message_Warning("This is the last page", "Error");
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
                if(Row_cur - 8 < 0) {
                    Message_Warning("This is the front page", "Error");
                } else Row_cur -= 8;   
                student_cur = Class->StudentClass;
                for( int i = 0; i < Row_cur; i ++) 
                    student_cur = student_cur->next;
                break;
            case 1:
                if(Row_cur + 8 >= Row){
                    Message_Warning("This is the last page", "Error");
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
                for( int i = 0; i < min(8,Row-Row_cur); i ++) 
                    student_cur = student_cur->prev;
                if(Col_cur - 3 < 0) 
                    Message_Warning("This is the front page", "Error"); 
                else 
                    Col_cur -= 3;
                course_cur = courseHead;
                for( int i = 0;  i < Col_cur; i ++)
                    course_cur = course_cur->next;
                break;
            case 1:
                for( int i = 0; i < min(8,Row-Row_cur); i ++) 
                    student_cur = student_cur->prev;
                if(Col_cur + 3 >= Col){
                    Message_Warning("This is the last page", "Error");
                    course_cur = courseHead;
                    for( int i = 0; i < Col_cur; i ++) 
                        course_cur = course_cur->next;
                } else 
                    Col_cur += 3;
                break;
            case 2:
                for(int i = 0; i < min(3,Col-Col_cur); i++)
                    course_cur = course_cur->prev;
                if(Row_cur - 8 < 0) {
                    Message_Warning("This is the front page", "Error");
                } else
                     Row_cur -= 8;   
                student_cur = Class->StudentClass;
                for( int i = 0; i < Row_cur; i ++) 
                    student_cur = student_cur->next;  
                break;
            case 3:
                for(int i = 0; i < min(3,Col-Col_cur); i++)
                    course_cur = course_cur->prev;
                if(Row_cur + 8 >= Row){
                    Message_Warning("This is the last page", "Error");
                    student_cur = Class->StudentClass;
                    for( int i = 0; i < Row_cur; i ++) 
                        student_cur = student_cur->next;
                } else 
                    Row_cur += 8;
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
    for (int i = 1; i <= 84; i++)
        cout << "=";
    cout << "\n";
    cout << "| Subject" << setw(28) << "Mid mark"<< setw(15) << "Final mark" << setw(15) << "Other mark" << setw(17) << "Total mark |" << endl; 
    for (int i = 1; i <= 84; i++)
        cout << "=";
    cout << "\n";
    while (courseHead)
    {
        StudentCourse *cur_stu = courseHead->studentCourse;
        while (cur_stu)
        {
            if (cur_stu->ID == accHead->username) //truy cập từng student trong từng course check ID 
            {
                cout <<  "| " << courseHead->Name;
                cout << setw(35 - courseHead->Name.length()) << right << cur_stu->ScoreBoardCourse.midMark;
                cout << setw(23 - to_string(cur_stu->ScoreBoardCourse.midMark).length()) << right << cur_stu->ScoreBoardCourse.finalMark;
                cout << setw(15) << right << cur_stu->ScoreBoardCourse.otherMark;
                cout << setw(15) << right << cur_stu->ScoreBoardCourse.totalMark << " |";
                cout << "\n";
            }
            cur_stu = cur_stu->next;
        }
        courseHead = courseHead->next;
    }
    for (int i = 1; i <= 84; i++)
        cout << "=";
}