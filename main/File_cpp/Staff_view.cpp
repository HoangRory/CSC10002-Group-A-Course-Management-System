#include "../Header/View.h"

//task 16: view students in a class 
void ViewStudentsClass(Year *yearHead) 
{   
    string class_name;
    cout << "Enter the class's name: "; // eg 20APCS1
    cin >> class_name;
    while (yearHead)
    {
        if (to_string(yearHead->yearStart % 100) == class_name.substr(0, 2)) //check the school year of the class => move the yearHead to that school year
            break;
        yearHead = yearHead->next;
    }
    if (!yearHead)
    {
        cout << "Not found!" << endl;
        return;
    }
    while (yearHead->Class)
    {
        if (yearHead->Class->Name == class_name) //find the class and print students in that class
        {
            if(yearHead->Class->StudentClass) 
            {
                cout << "\nList of students in " << class_name << ":" << endl;
                for (int i = 1; i <= 36; ++i)
                    cout << "=";
                cout << "\n";
                cout << "|    ID" << setw(5) << "|" << setw(15) << "Full name" << setw(9) << "|" << endl;
                for (int i = 1; i <= 36; ++i)
                    cout << "=";
                cout << "\n";
            }
            else cout << "\nThere is no student in " << class_name << endl;
            while (yearHead->Class->StudentClass)
            {
                cout << "| " << yearHead->Class->StudentClass->ID  << " |" << "\t"; 
                cout << yearHead->Class->StudentClass->accStudent->firstName << " " 
                    << yearHead->Class->StudentClass->accStudent->lastName << setw(20 - yearHead->Class->StudentClass->accStudent->firstName.length() - yearHead->Class->StudentClass->accStudent->lastName.length()) << "|\n";
                yearHead->Class->StudentClass = yearHead->Class->StudentClass->next;
                for (int i = 1; i <= 36; ++i)
                    cout << "=";
                cout << "\n";
            }
            return;
        }
        yearHead->Class = yearHead->Class->next;
    }
    if (!yearHead->Class)
        cout << "Not found!" << endl;
}

//task 18: view students in a course 
void ViewStudentCourse(Year *yearHead)
{
    string course_name;
    cout << "Enter the course's name: ";
    getline(cin, course_name);
    //find the course in 3 while-loop: year->semester->course
    while (yearHead)
    {
        while (yearHead->NoSemester)
        {
            while (yearHead->NoSemester->course)
            {
                if (yearHead->NoSemester->course->Name == course_name)
                {
                    if (yearHead->NoSemester->course->studentCourse) cout << "\nList of students in course " << course_name << ":" << endl;
                    else cout << "\nThere is no student in course " << course_name << endl;
                    while (yearHead->NoSemester->course->studentCourse)
                    {
                        cout << yearHead->NoSemester->course->studentCourse->ID << "\t" 
                            << yearHead->NoSemester->course->studentCourse->FullName << endl;
                        yearHead->NoSemester->course->studentCourse = yearHead->NoSemester->course->studentCourse->next;
                    }
                    return;
                }
                yearHead->NoSemester->course = yearHead->NoSemester->course->next;
            }
            yearHead->NoSemester = yearHead->NoSemester->next;
        }
        yearHead = yearHead->next;
    }
    if (!yearHead)
        cout << "Not found!" << endl;
}

//task 17: view the list of courses in a semester of a school year, different with view course in task 9
void ViewCourse(Year *yearHead)
{
    string school_year;
    cout << "Enter the school year (eg 2022-2023): ";
    getline(cin, school_year);
    while (yearHead)
    {
        if (yearHead->yearStart == stoi(school_year.substr(0, 4)))
            break;
        yearHead = yearHead->next;
    }
    if (!yearHead)
    {
        cout << "Can't find the school year. Try again!" << endl;
        return;
    }

    int no_smt;
    cout << "Enter the semester: ";
    cin >> no_smt;
    while (yearHead->NoSemester)
    {
        if (yearHead->NoSemester->No == no_smt)
            break;
        yearHead->NoSemester = yearHead->NoSemester->next;
    }
    if (!yearHead->NoSemester)
    {
        cout << "Can't find the semester. Try again!" << endl;
        return;
    }

    if(yearHead->NoSemester->course) cout << "\nHere is the list of courses in the semester " << no_smt << " of the " << school_year << " school year:" << endl;
    else cout << "\nThere is no course in the semester " << no_smt << " of the " << school_year << " school year." << endl;
    while (yearHead->NoSemester->course)
    {
        cout << yearHead->NoSemester->course->CourseID 
            << " - " << yearHead->NoSemester->course->Name  
            << " - Teacher: " << yearHead->NoSemester->course->TeacherName 
            << " - Room: " << yearHead->NoSemester->course->Room << endl;
        yearHead->NoSemester->course = yearHead->NoSemester->course->next;
    }
}

//task 15: view all classes which are existed
void ViewClass(Year* yearHead)
{
    Year *yr_cur = yearHead;
    cout << "List of classes:\n";
    for (int i = 0; i < 100; i++)
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
    for (int i = 0; i < 100; i++)
        cout << '-';
}

// int main()
// {
//     Year* yearHead = new Year;
//     yearHead->yearStart = 2021;
//     yearHead->next = new Year;
//     yearHead->next->yearStart = 2022;
//     // yearHead->next->NoSemester = new Semester;
//     // yearHead->next->NoSemester->No = 1;
//     // yearHead->next->NoSemester->next = new Semester;
//     // yearHead->next->NoSemester->next->No = 2;
//     // yearHead->next->NoSemester->next->course = new Course;
//     // yearHead->next->NoSemester->next->course->CourseID = "CSC10002";
//     // yearHead->next->NoSemester->next->course->Name = "Ky thuat lap trinh";
//     // yearHead->next->NoSemester->next->course->next = new Course;
//     // yearHead->next->NoSemester->next->course->next->CourseID = "BAA00101";
//     // yearHead->next->NoSemester->next->course->next->Name = "Triet hoc Mac Lenin";
//     // // ViewCourse(yearHead);
//     // yearHead->next->NoSemester->next->course->studentCourse = new StudentCourse;
//     // yearHead->next->NoSemester->next->course->studentCourse->ID = "22127026";
//     // yearHead->next->NoSemester->next->course->studentCourse->FullName = "On Gia Bao";
//     // yearHead->next->NoSemester->next->course->studentCourse->next = new StudentCourse;
//     // yearHead->next->NoSemester->next->course->studentCourse->next->ID = "22127275";
//     // yearHead->next->NoSemester->next->course->studentCourse->next->FullName = "Tran Anh Minh";
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
//     yearHead->next->Class->StudentClass->next->accStudent->firstName = "Le Ho Phi";
//     yearHead->next->Class->StudentClass->next->accStudent->lastName = "Hoang";
//     ViewStudentsClass(yearHead);
    
//     return 0;
// }