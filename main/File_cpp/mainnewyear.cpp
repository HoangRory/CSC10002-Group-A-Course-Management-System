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
    int choice = -1;
    while (choice != 2) {
        cout << "Do you want to add student to class?\n1. Yes\n2. No." << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1: 
                addStudenttoClass(curYear);
                break;
            case 2: 
                cout << "Thank you for using our program. Program ended." << endl;
        }
    }

    return 0;
}
