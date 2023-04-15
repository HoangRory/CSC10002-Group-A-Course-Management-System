#include "../Header/course.h"

Year* chooseYearbyOption(Year* yearHead, int option) 
{
    int index = 0;
    while(yearHead && index != option) {
        yearHead = yearHead->next;
    }
    return yearHead;
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