#include "proto.h"

void creat_SchoolYear() {
    Year *new_Year;
    Year *cur = new_Year;

    cout << "School Year: ";
    cin >> cur->yearStart;

    new_Year->yearStart = cur->yearStart;

    cur = cur->next;
}

void creat_Classes(Year *&new_Year) {
    Year *cur = new_Year;
    string name;

    cout << "Class Name: ";
    getline(cin, name);


    cur->Class->Name = name;
    //ghi vao file?


    //ham doc file csv danh sach student 
}