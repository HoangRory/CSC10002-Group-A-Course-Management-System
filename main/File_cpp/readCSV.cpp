#include "../Header/newYearClass.h"

void importYear(Year *&yearHead, int &numofYear) {
    //string in_year = to_string(yearStart);

    string path = "Data_file\\years.txt";
    ifstream ifs(path);
    if(!ifs) {
        cout << "Cannot open file years.txt" << endl;
        return;
    }

    Year *curYear;
    while (!ifs.eof()) {
        if (!yearHead){
            yearHead = new Year;
            curYear = yearHead;
        } else {
            Year *tmp = new Year;
            curYear->next = tmp;
            curYear = tmp;
        }

        numofYear++;
        ifs >> curYear->yearStart;
        importClass(curYear, curYear->yearStart);
    }
}

void addClass(Year *curYear, string ClassName) {
    if (!curYear->Class) {
        curYear->Class = new Class;
        curYear->Class->Name = ClassName;
    }
    else {
        Class* curClass = curYear->Class;
        while (curClass->next) {
            curClass = curClass->next;
        }
        curClass->next = new Class;
        curClass->next->Name = ClassName;
    }
}

void importClass(Year *curYear, int yearStart) {
    //create the path to the directory
    string in_year = to_string(yearStart) + '_' + to_string(yearStart + 1);
    string path = "Data_file" + separator + in_year + separator + "class.txt";

    ifstream ifs(path);
    if (!ifs) {
        cout << "Cannot open directory for year " << yearStart << endl;
        return;
    }

    //open class file
    string classFilePath = path;
    ifstream classFile(classFilePath);
    if (!classFile.is_open()) {
        cout << "Cannot open class file for year " << yearStart << endl;
        return;
    }

    string line;
    getline(classFile, line); //read the first "class" line
    if (line.empty() || all_of(line.begin(), line.end(), [](unsigned char c) { return std::isspace(c); })) return; //end of file

    //read each class from the file, add to the linked list
    Class *curClass = new Class;
    curClass->Name = line;
    addClass(curYear, curClass->Name);
    curClass = curYear->Class; // add new class to linked list

    Student *headStudent = nullptr;
    
    while (getline(classFile, line)) {
        if (line.empty() || all_of(line.begin(), line.end(), [](unsigned char c) { return std::isspace(c); })) break; //end of file
        
        if (line == "-1") {
            //end of cur class, move to next class
            getline(classFile, line); //read the class line for the next class
            if (line.empty() || all_of(line.begin(), line.end(), [](unsigned char c) { return std::isspace(c); })) break; //end of file

            curClass = new Class;
            curClass->Name = line;
            addClass(curYear, curClass->Name);

            Class *tmp = curYear->Class;
            while (tmp->next) {
                tmp = tmp->next;
            }      

            curClass = tmp;
            headStudent = nullptr;
        } else {
            if(!curClass) {
                cerr << "Error: class not found" << endl;
                return;
            }
            //Student *curStudent = nullptr;
            if (!headStudent) {
                curClass->StudentClass = new Student;
                headStudent = curClass->StudentClass;
                headStudent->ID = line;
            } else {
                Student *curStudent = new Student;
                curStudent->ID = line;
                curStudent->prev = headStudent;
                headStudent->next = curStudent;
                headStudent = curStudent;
            }
        }
    }

    curClass = curYear->Class;
    while (curClass) {
        Student *curStudent = curClass->StudentClass;
        while (curStudent && curStudent->next) {
            curStudent = curStudent->next;
        }
        if (curStudent) curStudent->next = nullptr;
        curClass = curClass->next;
    } 

    cout << "Class imported successfully" << endl;
}
