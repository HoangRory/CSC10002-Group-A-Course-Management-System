#include "main/Header/newYearClass.h"
/* 
int main() {
    Class *classes = nullptr;
    ofstream outFile("Data_file/classes.txt");
    int setOfClasses = -1;

    createClasses(classes, setOfClasses, "22CLC02", outFile);
    add1stYearStudents(classes, "22127026", "John", "Doe", "M", "01/01/2000", "123456789");
    add1stYearStudents(classes, "22127123", "Jane", "Doe", "F", "02/02/2000", "987654321");
    add1stYearStudents(classes, "22127275", "Bob", "Smith", "M", "03/03/2000", "456789123");
    outFile << setOfClasses << endl;

    createClasses(classes, setOfClasses, "22CLC03", outFile);
    add1stYearStudents(classes, "22127333", "Alice", "Smith", "F", "04/04/2000", "789123456");
    add1stYearStudents(classes, "22127475", "Tom", "Johnson", "M", "05/05/2000", "321654987");
    outFile << setOfClasses << endl;

    outFile.close();
    return 0;
}
 */
int main() {
    int choice;
    Year *curYear = nullptr;
    Class *Classes = nullptr;
    int setOfClass = -1;
    ofstream outFile("Data_file/classes.txt");

    // Create a new school year
    createSchoolYear(curYear, 2023);

    // Add new classes
    createClasses(Classes, setOfClass, "22CLC01", outFile);
    createClasses(Classes, setOfClass, "22CLC02", outFile);

    // Add students
    cout << "Do you want to add new 1st year students to 1st-year classes?" << endl;
    cout << "1. Yes\n2. No" << endl;
    cin >> choice;
    cin.ignore();

    if (choice == 1) {
        addStudent1_CSV();
    }

    return 0;
}