#include "../Header/newYearClass.h"
const string separator = "\\";

int main() {
    Year *headYear = nullptr;
    int numofYear = 0;

    // import existing years and classes
    importYear(headYear, numofYear);

    // create a new school year
    createSchoolYear(headYear, 2024);

    // create a new class in the new school year
    Year *curYear = headYear;
    while (curYear && curYear->yearStart != 2024) curYear = curYear->next;
    createClasses(curYear, "23APCS1");

    // add students to the new class
    addStudenttoClass(curYear);

    return 0;
}
