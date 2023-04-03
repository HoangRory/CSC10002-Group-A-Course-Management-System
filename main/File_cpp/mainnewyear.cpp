/* #include "Header/newYearClass.h
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
} */