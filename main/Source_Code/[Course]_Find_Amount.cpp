#include "../Header/course.h"

Course* findCoursebyIndexOption(Course *courseHead, int index) 
{
    for(int i = 0; courseHead != nullptr; i++) {
        if(i == index) 
            break;
        courseHead = courseHead->next;
    }
    return courseHead;
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
StudentCourse* find_SBC_ofStudent(string ID, StudentCourse *stuCourseHead) 
{
    while(stuCourseHead) 
    {
        if (stuCourseHead->ID == ID) 
            return stuCourseHead;
        stuCourseHead = stuCourseHead->next;
    }
    return nullptr;
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

int amountOfCourse(Course *courseHead)
{
    int n = 0; 
    while(courseHead) {
        n++;
        courseHead = courseHead->next;
    }
    return n;
}
//task 23
int amountStudentOfClass(Student *studentHead) 
{
    int count = 0;
    while (studentHead) 
    {
        studentHead = studentHead->next;
        count ++;
    }
    return count;
}
int amountCourseOfClass(CourseStudent *courseHead) 
{
    int count = 0;
    while (courseHead) 
    {
        courseHead = courseHead->next;
        count ++;
    }
    return count;
}
