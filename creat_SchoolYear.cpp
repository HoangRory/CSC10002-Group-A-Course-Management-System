#include "proto.h"

Year *createSchoolYear(int yearStart) {
    Year *newYear = new Year;
    newYear->yearStart = yearStart;
    newYear->Class = nullptr;
    newYear->NoSemester = nullptr;
    return newYear;
}

// Create a new class for 1st-year students
Class *createClass(string name) {
    Class *newClass = new Class;
    newClass->Name = name;
    newClass->StudentClass = nullptr;
    newClass->next = nullptr;
    newClass->prev = nullptr;
    return newClass;
}

