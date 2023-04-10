#include "../Header/newYearClass.h"
const string separator = "\\";

int main() {
    Year *headYear = nullptr;
    int numofYear = 0;

    // import existing years and classes
    loadingFile(headYear, numofYear);

    // create a new school year
    cout << "======ADDING NEW SCHOOL YEAR======" << endl;
    cout << "Enter start year: ";
    int yearStart = 0;
    cin >> yearStart; // stuarttttttt
    createSchoolYear(headYear, yearStart);

    // create a new class in the new school year
    Year *curYear = headYear;
    while (curYear && curYear->yearStart != 2024) curYear = curYear->next;
    int choice = 0;
    cout << "Do you want to create a new class?\n1. Yes\n2. No.\n3. Back" << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    if (choice == 1) {
        string className;
        cout << "Enter class name: ";
        cin.ignore();
        getline(cin, className);
        createClasses(curYear, className);
    } else if (choice == 2) {
        cout << "Thank you for using our program. Program ended." << endl;
    } else {
        cout << "Thank you for using our program. Program ended." << endl;
    }

    // add students to the new class
    choice = 0;
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
