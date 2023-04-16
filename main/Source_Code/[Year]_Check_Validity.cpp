#include "../Header/Year.h"

//? Turn the classname to uppercase
void CapitalClassName(string &name)
{
    for (int i = 0; i < name.length(); i++)
        name[i] = toupper(name[i]);
}

//? Return true if the year existed
bool checkYear(Year *curYear, int year)
{
    while (curYear)
    {
        if (curYear->yearStart == year)
            return true;
        curYear = curYear->next;
    }
    return false;
}

//? Return true if the class already exists
bool checkClass(Year *curYear, string className)
{
    Class *curClass = curYear->Class;
    while (curClass)
    {
        if (curClass->Name == className)
            return true;
        curClass = curClass->next;
    }
    return false;
}

//? Return true if the student already exists
bool Check_Student(Class *curClass, string studentID)
{
    Student *curStudent = curClass->StudentClass;
    while (curStudent)
    {
        if (curStudent->ID == studentID)
            return true;
        curStudent = curStudent->next;
    }
    return false;
}

//? return true if it is a leap year
bool isLeap(int year)
{
    return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}

//? return true if the date is valid
bool isValidDate(const string &dateOfBirth)
{
    if (dateOfBirth.length() != 10)
        return false;

    if (dateOfBirth[2] != '/' || dateOfBirth[5] != '/')
        return false;

    int dd = stoi(dateOfBirth.substr(0, 2));
    int mm = stoi(dateOfBirth.substr(3, 2));
    int yyyy = stoi(dateOfBirth.substr(6, 4));

    if (mm < 1 || mm > 12)
        return false;

    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (isLeap(yyyy))
        daysInMonth[1] = 29;

    if (dd < 1 || dd > daysInMonth[mm - 1])
        return false;

    return true;
}

//? true if it is in the correct format
bool isValidGender(const string &gender)
{
    return (gender == "F" || gender == "M");
}

//? true if it is correct format (yyyy_yyyy)
bool isValidYear(string year)
{
    if (year.size() != 9)
        return false;
    else if (year[4] != '-' && year[4] != '_')
        return false;
    int y1 = stoi(year.substr(0, 4));
    int y2 = stoi(year.substr(5, 4));
    return (y2 - y1 == 1);
}

void SeparateName(string full, string &first, string &last)
{
    size_t pos = full.find_last_of(" ");
    first = full.substr(0, pos);
    last = full.substr(pos + 1);
}