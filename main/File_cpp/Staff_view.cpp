#include "../Header/View.h"

//task 16: view students in a class 
void ViewStudentClass(Year *yearHead) 
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
    Class *cur_class = yearHead->Class;
    while (cur_class)
    {
        if (cur_class->Name == class_name) //find the class and print students in that class
        {
            Student *cur_stu = cur_class->StudentClass;
            if(cur_stu) 
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
            else 
                cout << "\nThere is no student in " << class_name << endl;
            while (cur_stu)
            {
                cout << "| " << cur_stu->ID  << " |" << "\t"; 
                cout << cur_stu->accStudent->firstName << " " 
                    << cur_stu->accStudent->lastName << setw(20 - cur_stu->accStudent->firstName.length() - cur_stu->accStudent->lastName.length()) << "|\n";
                for (int i = 1; i <= 36; ++i)
                    cout << "=";
                cout << "\n";
                cur_stu = cur_stu->next;
            }
            return;
        }
        cur_class = cur_class->next;
    }
    if (!cur_class)
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
        Semester *cur_sem = yearHead->NoSemester;
        while (cur_sem)
        {
            Course *cur_cour = cur_sem->course;
            while (cur_cour)
            {
                if (cur_cour->Name == course_name)
                {
                    if (cur_cour->studentCourse)
                    { 
                        cout << "\nList of students in course " << course_name << ":" << endl;
                        for (int i = 1; i <= 36; ++i)
                            cout << "=";
                        cout << "\n";
                        cout << "|    ID" << setw(5) << "|" << setw(15) << "Full name" << setw(9) << "|" << endl;
                        for (int i = 1; i <= 36; ++i)
                            cout << "=";
                        cout << "\n";
                    }
                    else 
                        cout << "\nThere is no student in course " << course_name << endl;
                    StudentCourse *cur_stu = cur_cour->studentCourse;
                    while (cur_stu)
                    {
                        cout << "| " << cur_stu->ID  << " |" << "\t"; 
                        cout << cur_stu->FullName << setw(21 - cur_stu->FullName.length()) << "|\n";
                        for (int i = 1; i <= 36; ++i)
                            cout << "=";
                        cout << "\n";
                        cur_stu = cur_stu->next;
                    }
                    return;
                }
                cur_cour = cur_cour->next;
            }
            cur_sem = cur_sem->next;
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
    Semester *cur_sem = yearHead->NoSemester;
    while (cur_sem)
    {
        if (cur_sem->No == no_smt)
            break;
        cur_sem = cur_sem->next;
    }
    if (!cur_sem)
    {
        cout << "Can't find the semester. Try again!" << endl;
        return;
    }

    Course *cur_cour = cur_sem->course;
    if (cur_cour) 
    {
        cout << "\nList of courses in the semester " << no_smt << " of the " << school_year << " school year:" << endl;
        for (int i = 1; i <= 70; ++i)
            cout << "=";
        cout << "\n";
        cout << "|    ID" << setw(18) << "|         Name" << setw(33) << "|       Teacher" << setw(13) << "|\n"; 
        for (int i = 1; i <= 70; ++i)
            cout << "=";
        cout << "\n";
    }
    else 
        cout << "\nThere is no course in the semester " << no_smt << " of the " << school_year << " school year." << endl;
    while (cur_cour)
    {
        cout << "| " << cur_cour->CourseID << " | ";
        cout << cur_cour->Name << setw(32 - cur_cour->Name.length()) << "| ";  
        cout << cur_cour->TeacherName << setw(26 - cur_cour->TeacherName.length()) << "|\n";
        for (int i = 1; i <= 70; ++i)
            cout << "=";
        cout << "\n";
        cur_cour = cur_cour->next;
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