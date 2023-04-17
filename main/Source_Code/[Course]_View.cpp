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
    Render_View();
    Year *ChooseYear = chooseYearbyOption(yearHead);
    if(ChooseYear == nullptr)
        return;
        //gọi lại hàm mainmenu
    system("cls");
    Render_View();
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
    Render_View();
    Year *ChooseYear = chooseYearbyOption(yearHead);
    if(ChooseYear == nullptr)
        return;
        //gọi lại hàm mainmenu
    system("cls");
    Render_View();
    Class *ChooseClass = chooseClassbyOption(ChooseYear->Class);
    if(ChooseClass == nullptr) {
        ViewStudentsClass(yearHead);
        return;
    }

    system("cls");
    Render_View();
    Student *currStudent = ChooseClass->StudentClass;
    int x = 50,y = 10;
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
    Render_StudentClass();
    //in ra chư studentcourse
    Year *ChooseYear = nullptr;
    Semester *ChooseSem = nullptr;
    Course *ChooseCourse = nullptr;
    Render_StudentCourse();
    if(yearHead == nullptr){
        Message_Warning("There are no school year.","Error not exist");
        // gọi lại hàm mainmenu
        return;
    }
    do {
        ChooseYear = chooseYearbyOption(yearHead);
        if(ChooseYear == nullptr){
            //quay lại main menu
            return;
        }
        system("cls");
        Render_StudentCourse();
        do {
            if(ChooseYear->NoSemester == nullptr) {
                Message_Warning("There are no semester in this school year.","Error not exist");
                break;
            }
            ChooseSem = chooseSemesterbyOption(ChooseYear->NoSemester);
            system("cls");
            Render_StudentCourse();
            if(ChooseSem){
                if(ChooseSem->course == nullptr) {
                    Message_Warning("There are no course in this semester", "Error not Exist");
                } else{
                    ChooseCourse = chooseCoursebyOption(ChooseSem->course);
                }
                system("cls"); 
                Render_StudentClass();
            } else 
                break;
        }while(ChooseCourse == nullptr);
        
    } while (ChooseSem == nullptr);

    //này là để chọn được course
    system("cls");
    Render_StudentClass();
    StudentCourse *currStudent = ChooseCourse->studentCourse;
    if(!currStudent) {
        Message_Warning(" There is no student in course " + ChooseCourse->Name, "Error not exist");
        system("cls");
        return;
    }
    
    int x = 50, y = 10;
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
    // system("cls");
    // cout << "Please select course for which you want to show scoreboard. Or select close <- to come back Main Menu" << endl;
    // cout << "Using arrow keys to move and press enter to select your option." << endl;
    // system("pause");
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
    int Col = amountCourseOfClass(courseHead);
    int Row = amountStudentOfClass(studentHead);
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