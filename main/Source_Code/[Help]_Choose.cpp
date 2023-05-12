#include "../Header/Course.h"
#include "../Header/Utility.h"

Year *chooseYearbyOption_XY(Year *yearHead, int x, int y, int nOption_eachTime)
{
    Year *year_cur = yearHead;
    vector<string> menu;
    while (year_cur)
    {
        menu.push_back(to_string(year_cur->yearStart) + " - " + to_string(year_cur->yearStart + 1));
        year_cur = year_cur->next;
    }
    int width = 20;
    menu.push_back("BACK");
    int option = Draw_XY(menu, x, y, nOption_eachTime, width, 63);

    while (yearHead && option--)
        yearHead = yearHead->next;
    return yearHead;
}
Class *chooseClassbyOption_XY(Class *classHead, int x, int y, int nOption_eachTime)
{
    vector<string> menu;
    Class *class_cur = classHead;
    while (class_cur)
    {
        menu.push_back("   " + class_cur->Name);
        class_cur = class_cur->next;
    }
    int width = 20;
    menu.push_back("   BACK");
    int option = Draw_XY(menu, x, y, nOption_eachTime, width, 63);

    while (classHead && option--)
        classHead = classHead->next;
    return classHead;
}
Class *chooseClass_inAllYear_byOption_XY(Year *yearHead, int x, int y, int nOption_eachTime)
{
    vector<string> menu;
    Class *class_cur = nullptr;
    Year *year_cur = yearHead;
    while (year_cur)
    {
        class_cur = year_cur->Class;
        while (class_cur)
        {
            menu.push_back("   " + class_cur->Name);
            class_cur = class_cur->next;
        }
        year_cur = year_cur->next;
    }
    int width = 20;
    menu.push_back("   BACK");
    if (menu.size() == 0)
        return nullptr;
    int option = Draw_XY(menu, x, y, nOption_eachTime, width, 63);
    year_cur = yearHead;
    while (year_cur)
    {
        class_cur = year_cur->Class;
        while (class_cur)
        {
            if (option == 0)
                return class_cur;
            class_cur = class_cur->next;
            option--;
        }
        year_cur = year_cur->next;
    }
    return class_cur;
}
Semester *chooseSemesterbyOption_XY(Semester *semHead, int x, int y, int nOption_eachTime)
{
    vector<string> menu;
    Semester *sem_cur = semHead;
    while (sem_cur)
    {
        menu.push_back("Semester " + to_string(sem_cur->No));
        sem_cur = sem_cur->next;
    }
    int width = 15;
    menu.push_back("BACK");
    int option = Draw_XY(menu, x, y, nOption_eachTime, width, 63);

    while (semHead && option--)
    {
        semHead = semHead->next;
    }
    return semHead;
}
Course *chooseCoursebyOption_XY(Course *courseHead, int x, int y, int nOption_eachTime)
{
    vector<string> menu;
    Course *course_cur = courseHead;
    while (course_cur)
    {
        menu.push_back(course_cur->Name);
        course_cur = course_cur->next;
    }
    int width = 35;
    menu.push_back("BACK");
    int option = Draw_XY(menu, x, y, nOption_eachTime, width, 63);

    while (courseHead && option--)
        courseHead = courseHead->next;
    return courseHead;
}
Student *chooseStudentOfClass(Class *ChooseClass, int x, int y)
{
    Student *student_cur = ChooseClass->StudentClass;
    goToXY(x, y++);
    cout << "List of students in " << ChooseClass->Name;
    int width[7];
    width[0] = 10; // chiều rộng cột NO
    width[1] = 15; // chiều rộng cột ID
    width[2] = 30; // chiểu rộng Student Name;

    string *title = new string[3];
    title[0] = "   No";
    title[1] = " ID";
    title[2] = "   Student Name";

    int num_row = amountStudentOfClass(ChooseClass->StudentClass);
    int num_col = 3;

    string **table = new string *[num_row];
    for (int i = 0; i < num_row; i++)
        table[i] = new string[num_col];

    int height = 1, Row_eachTime = 7, Col_eachTime = 8;
    bool edit_Col[3] = {true, true, true};

    for (int i = 0; i < num_row; i++)
    {
        int j = 0;
        table[i][j++] = "   " + to_string(i + 1);
        table[i][j++] = " " + student_cur->ID;
        table[i][j++] = "   " + student_cur->accStudent->lastName + " " + student_cur->accStudent->firstName;
        student_cur = student_cur->next;
    }
    int x_cur = 0, y_cur = 0;

    Draw_table(table, title, num_row, num_col, width, height, x, y, Row_eachTime, Col_eachTime, edit_Col, x_cur, y_cur);

    Student *ChooseStudent = nullptr;
    if (y_cur == -1)
        return ChooseStudent;
    ChooseStudent = ChooseClass->StudentClass;
    while (y_cur--)
        ChooseStudent = ChooseStudent->next;
    return ChooseStudent;
}