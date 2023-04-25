#include "../Header/Year.h"

void SwapYear(Year *year1, Year *year2)
{
    year1->yearStart = year1->yearStart + year2->yearStart;
    year2->yearStart = year1->yearStart - year2->yearStart;
    year1->yearStart = year1->yearStart - year2->yearStart;

    Class *tmp_Class = year1->Class;
    year1->Class = year2->Class;
    year2->Class = tmp_Class;

    Semester *tmp_Sem = year1->NoSemester;
    year1->NoSemester = year1->NoSemester;
    year2->NoSemester = tmp_Sem;
}
Year *SortYear_Descending(Year *yearHead)
{
    Year *year_i;
    Year *year_j;
    for (year_i = yearHead; year_i && year_i->next != nullptr; year_i = year_i->next)
        for (year_j = year_i->next; year_j != nullptr; year_j = year_j->next)
            if (year_i->yearStart < year_j->yearStart)
                SwapYear(year_i, year_j);
    while (year_i && year_i->prev)
        year_i = year_i->prev;
    return year_i;
}