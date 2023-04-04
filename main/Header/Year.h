#pragma once

#include "proto.h"

//? Read-in the class from each year
Year *Read_Year_Class(int year);
Year *Read_Multi_year();
void DeleteYear(Year *&yearHead);

//? Create a new school year
Year *Create_NewYear(Year *yearHead);
void Adding_New_Classes(Year *newYear);
void Adding_1st_Student(Year *newYear);