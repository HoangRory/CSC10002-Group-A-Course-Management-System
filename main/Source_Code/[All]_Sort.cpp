#include "../Header/Year.h"

void SwapYear(Year *year1, Year *year2)
{
    Year *next2 = year2->next, *prev2 = year2->prev;
    year2->next = year1->next;
    year2->prev = year1->prev;
    if (year2->next)
        year2->next->prev = year2;
    if (year2->prev)
        year2->prev->next = year2;

    year1->next = next2;
    year1->prev = prev2;
    if (year1->next)
        year1->next->prev = year1;
    if (year1->prev)
        year1->prev->next = year1;
}
Year *SortYear_Descending(Year *yearHead)
{
    Year *year_i;
    Year *year_j;
    for (year_i = yearHead; year_i->next != nullptr; year_i = year_i->next)
        for (year_j = year_i->next; year_j != nullptr; year_j = year_j->next)
            if (year_i->yearStart < year_j->yearStart)
                SwapYear(year_i, year_j);
    return yearHead;
}