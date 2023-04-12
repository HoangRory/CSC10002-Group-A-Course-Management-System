#include "../Header/View.h"
#include "../Header/course.h"
#include "../Header/help.h"
//sub of 4task
int amountYear(Year *yearHead)
{
    int n = 0;
    while (yearHead) {
        n++;
        yearHead = yearHead->next;
    }
    return n;
}
Year* chooseYearbyOption(Year* yearHead) 
{
    int nOption, option;
    string *arrOption;
    Year *curYear = yearHead;

    nOption = amountYear (yearHead);
    arrOption = new string [nOption + 1];
    for (int i = 0; i < nOption; i++) {
        arrOption[i] = to_string(curYear->yearStart) + "-" + to_string(curYear->yearStart +1);
        curYear = curYear->next;
    }
    arrOption[nOption] =  "<-";
    system("cls");
    string title = "Select Year: ";
    option = view_chooseOption(arrOption,nOption+1,title);
    delete []arrOption;
    while(yearHead && option--)
        yearHead = yearHead->next;
    return yearHead;
}
int amountClass(Class *classHead) 
{
    int n = 0;
    while (classHead) {
        n++;
        classHead = classHead->next;
    }
    return n;
}
Class* chooseClassbyOption(Class *classHead) 
{
    Class *curClass = classHead;

    int nOption = amountClass(classHead);
    string *arrOption = new string [nOption + 1];
    for (int i = 0; i < nOption; i++) {
        arrOption[i] = curClass->Name;
        curClass = curClass->next;
    }
    arrOption[nOption] =  "<-";
    system("cls");
    string title = "Select Class: ";
    int option = view_chooseOption(arrOption,nOption+1,title);
    delete []arrOption;
    while(classHead && option--)
        classHead = classHead->next;
    return classHead;
}
Semester* chooseSemesterbyOption(Semester* semHead) 
{
    string *arrOption = new string [4];
    int nOption = 0;
    Semester *curSem = semHead;
    while(curSem) {
        nOption++;
        curSem = curSem->next;
    }
    for(int i = 0; i < nOption; i++) {
        arrOption[i] = "Semester " + to_string(i+1);
    }
    arrOption[nOption] = "<-";
    string title = "Select Semester:";
    int option = view_chooseOption(arrOption, nOption + 1, title);
    while (semHead && option--) {
        semHead = semHead->next;
    }
    return semHead;
}
int amountCourse(Course* courseHead) 
{
    int n = 0;
    while (courseHead) {
        courseHead = courseHead->next;
        n++;
    }
    return n;
}
Course* chooseCoursebyOption(Course* courseHead) 
{
    int nOption = amountCourse(courseHead);
    string *arrOption = new string [nOption+1];
    Course *curCourse = courseHead;
    for(int i = 0; i < nOption; i++) {
        arrOption[i] = curCourse->Name;
        curCourse = curCourse->next;
    }
    arrOption[nOption] = "<-";
    string title = "Select Course: ";
    int option = view_chooseOption(arrOption, nOption + 1,title);
    while(courseHead && option--) {
        courseHead = courseHead->next;
    }
    return courseHead;
}

//task 16: view students in a class 
void ViewStudentsClass(Year *yearHead) 
{   
    Year *ChooseYear = chooseYearbyOption(yearHead);
    if(ChooseYear == nullptr)
        return;
        //gọi lại hàm mainmenu
    Class *ChooseClass = chooseClassbyOption(ChooseYear->Class);
    if(ChooseClass == nullptr) {
        ViewStudentsClass(yearHead);
        return;
    }

    system("cls");
    Student *currStudent = ChooseClass->StudentClass;
    if(currStudent) 
    {
        cout <<  "\nList of students in " << ChooseClass->Name << ":" << endl;
        for (int i = 1; i <= 36; ++i)
            cout << "=";
        cout << "\n";
        cout << "|    ID" << setw(5) << "|" << setw(15) << "Full name" << setw(9) << "|" << endl;
        for (int i = 1; i <= 36; ++i)
            cout << "=";
        cout << "\n";
    }
    else 
        cout << "\nThere is no student in " << ChooseClass->Name<< endl;
    while (currStudent)
    {
        cout << "| " << currStudent->ID  << " |" << "\t"; 
        cout << currStudent->accStudent->firstName << " " 
            << currStudent->accStudent->lastName << setw(20 - currStudent->accStudent->firstName.length() - currStudent->accStudent->lastName.length()) << "|\n";
        for (int i = 1; i <= 36; ++i)
            cout << "=";
        cout << "\n";
        currStudent = currStudent->next;
    }
}



//task 18: view students in a course 
void ViewStudentCourse(Year *yearHead)
{
    Year *ChooseYear = nullptr;
    Semester *ChooseSem = nullptr;
    Course *ChooseCourse = nullptr;
    if(yearHead == nullptr){
        cout << "There are no school year.";
        system("pause");
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

    //này là để chọn được course



    StudentCourse *currStudent = ChooseCourse->studentCourse;
    if(!currStudent) {
        cout << "\nThere is no student in course " << ChooseCourse->Name << endl;
        system("pause");
        system("cls");
        return;
    }
    
    cout << "\nList of students in course " << ChooseCourse->Name << ":" << endl;
    for (int i = 1; i <= 36; ++i)
        cout << "=";
    cout << "\n";
    cout << "|    ID" << setw(5) << "|" << setw(15) << "Full name" << setw(9) << "|" << endl;
    for (int i = 1; i <= 36; ++i)
        cout << "=";
    cout << "\n";

    while (currStudent)
    {
        cout << "| " << currStudent->ID  << " |" << "\t"; 
        cout << currStudent->FullName << setw(21 - currStudent->FullName.length()) << "|\n";
        for (int i = 1; i <= 36; ++i)
            cout << "=";
        cout << "\n";
        currStudent = currStudent->next;
    }

}

//task 17: view the list of courses in a semester of a school year, different with view course in task 9
void ViewCourse(Year *yearHead)
{
// mới viết
    Year *ChooseYear = nullptr;
    Semester *ChooseSem = nullptr;
    Course *ChooseCourse = nullptr;
    if(yearHead == nullptr){
        cout << "There are no school year.";
        system("pause");
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
// phía trên là để chọn được course

//xóa này đi
    // Year *ChooseYear = chooseYearbyOption(yearHead);
    // if(ChooseYear == nullptr){
    //     //gọi lại hàm mainmenu
    //     return;
    // }
    // Semester *ChooseSem;
    // Course *ChooseCourse;
    // do {
    //     ChooseSem = chooseSemesterbyOption(ChooseYear->NoSemester);
    //     if(ChooseSem == nullptr) 
    //     {
    //         ViewCourse(yearHead);
    //         return;
    //     }
    //     ChooseCourse = chooseCoursebyOption(ChooseSem->course);
    // } while (ChooseCourse == nullptr);


    cout << "\nList of courses in the semester " << ChooseSem->No << " of the " << ChooseSem->Year << "-" << ChooseSem->Year + 1 << " school year:" << endl;
    for (int i = 1; i <= 70; ++i)
        cout << "=";
    cout << "\n";
    cout << "|    ID" << setw(18) << "|         Name" << setw(33) << "|       Teacher" << setw(13) << "|\n"; 
    for (int i = 1; i <= 70; ++i)
        cout << "=";
    cout << "\n";
    while (ChooseCourse)
    {
        cout << "| " << ChooseCourse->CourseID << " | ";
        cout << ChooseCourse->Name << setw(32 - ChooseCourse->Name.length()) << "| ";  
        cout << ChooseCourse->TeacherName << setw(26 - ChooseCourse->TeacherName.length()) << "|\n";
        for (int i = 1; i <= 70; ++i)
            cout << "=";
        cout << "\n";
        ChooseCourse = ChooseCourse->next;
    }
}

//task 15: view all classes which are existed
void ViewClass(Year* yearHead)
{
    Year *yr_cur = yearHead;
    cout << "List of classes:\n";
    for (int i = 0; i < 50; i++)
        cout << '-';
    while (yr_cur)
    {
        Class *cls_cur = yr_cur->Class;
        cout << "\nSchool year " << yr_cur->yearStart << "-" << yr_cur->yearStart + 1 << ":" << endl; // seperate the list into many parts by the school year
        while (cls_cur)
        {
            cout << cls_cur->Name << endl;
            cls_cur = cls_cur->next;
        }
        yr_cur = yr_cur->next;
    }
    for (int i = 0; i < 50; i++)
        cout << '-';
}

// int main()
// {
//     Year* yearHead = new Year;
//     yearHead->yearStart = 2021;
//     yearHead->next = new Year;
//     yearHead->next->yearStart = 2022;
//     yearHead->next->NoSemester = new Semester;
//     yearHead->next->NoSemester->No = 1;
//     yearHead->next->NoSemester->next = new Semester;
//     yearHead->next->NoSemester->next->No = 2;
//     yearHead->next->NoSemester->next->course = new Course;
//     yearHead->next->NoSemester->next->course->CourseID = "CSC10002";
//     yearHead->next->NoSemester->next->course->Name = "Ky thuat lap trinh";
//     yearHead->next->NoSemester->next->course->next = new Course;
//     yearHead->next->NoSemester->next->course->next->CourseID = "BAA00101";
//     yearHead->next->NoSemester->next->course->next->Name = "Triet hoc Mac Lenin";
//     // ViewCourse(yearHead);
//     yearHead->next->NoSemester->next->course->studentCourse = new StudentCourse;
//     yearHead->next->NoSemester->next->course->studentCourse->ID = "22127026";
//     yearHead->next->NoSemester->next->course->studentCourse->FullName = "On Gia Bao";
//     yearHead->next->NoSemester->next->course->studentCourse->next = new StudentCourse;
//     yearHead->next->NoSemester->next->course->studentCourse->next->ID = "22127275";
//     yearHead->next->NoSemester->next->course->studentCourse->next->FullName = "Tran Anh Minh";
//     // ViewStudentCourse(yearHead);

//     yearHead->next->Class = new Class;
//     yearHead->next->Class->Name = "22CLC02";
//     yearHead->next->Class->StudentClass = new Student;
//     yearHead->next->Class->StudentClass->ID = "22127026";
//     yearHead->next->Class->StudentClass->accStudent = new Account;
//     yearHead->next->Class->StudentClass->accStudent->firstName = "On Gia";
//     yearHead->next->Class->StudentClass->accStudent->lastName = "Bao";
//     yearHead->next->Class->StudentClass->next = new Student;
//     yearHead->next->Class->StudentClass->next->ID = "22127275";
//     yearHead->next->Class->StudentClass->next->accStudent = new Account;
//     yearHead->next->Class->StudentClass->next->accStudent->firstName = "Tran Anh";
//     yearHead->next->Class->StudentClass->next->accStudent->lastName = "Minh";
//     // ViewStudentsClass(yearHead);
//     // ViewClass(yearHead);
    
//     return 0;
// }