#include "../Header/Year.h"
#include "../Header/Semester.h"
#include "../Header/Utility.h"
#include "../Header/Help.h"

//? 1. Create a school year (2020-2021, for example)
//* lần đầu gọi hàm thì cho cin yearStart trong hàm main
void createSchoolYear(Year *&headYear, int yearStart, Account *accHead)
{
    Year *curYear = headYear;
    if (checkYear(headYear, yearStart))
    {
        string message = "Year " + to_string(yearStart) + "-" + to_string(yearStart + 1) + " already exists.\nDo you want to retry?";
        string title = "Error";
        if (Message_YesNo(message, title))
            Interface_New_Year(headYear, accHead); // Loop again
        return;
    }

    Year *newYear = new Year;
    newYear->yearStart = yearStart;
    newYear->next = headYear;
    if (headYear)
        headYear->prev = newYear;
    headYear = newYear;

    string path = "..\\Data_file\\" + to_string(yearStart) + "_" + to_string(yearStart + 1);
    path = "mkdir " + path;
    TextColor(7);
    goToXY(30, 30);
    system(path.c_str()); // Create a folder in the sys
    goToXY(30, 30);
    cout << "                                                                                                     ";

    string message = "Year " + to_string(yearStart) + "-" + to_string(yearStart + 1) + " has been added successfully.\nDo you want to add class to this year?";
    string title = "Success";
    if (Message_YesNo(message, title))
    {
        if (!Create_New_Classes(newYear, accHead))
            return;
    }
}

//? 2. Create several classes for 1st-year students.
//* For example: class 20APCS1, class 20APCS2, class 20CLC1..., class 20CLC11, class 20VP...
//* check if that class already exists.
bool Create_New_Classes(Year *newYear, Account *accHead)
{
    system("cls");
    Render_Class(50, 3);
    goToXY(63, 15);
    TextColor(0x0E);
    cout << "YEAR: " << newYear->yearStart << "_" << newYear->yearStart + 1;
    goToXY(60, 17);
    cout << "New Class (0 to go back)";
    Class *ClassTMP = newYear->Class;
    while (ClassTMP && ClassTMP->next != nullptr)
        ClassTMP = ClassTMP->next;
    string line;
    int i = 0;
    while (1)
    {
        if (i == 10) // 10 classes per page when input
        {
            i = 0;
            system("cls");
            Render_Class(50, 3);
            goToXY(63, 15);
            TextColor(0x0E);
            cout << "YEAR: " << newYear->yearStart << "_" << newYear->yearStart + 1;
            goToXY(60, 17);
            cout << "New Class (0 to stop)";
            TextColor(63);
            goToXY(58, 19 + i);
            cout << "                             ";
            goToXY(65, 19 + i);
            cout << line;
            i++;
        }

        TextColor(63);
        goToXY(58, 19 + i);
        cout << "                             ";
        line = Limit_Input(65, 19 + i, 8, 63);

        if (line == "-1")
            return false;
        if (line == "0")
            break;

        CapitalClassName(line); // Capitalize the first letter of each word
        if (checkClass(newYear, line))
        {
            string message = "Class " + line + " already exists.\nDo you want to retry?";
            string title = "Error";
            if (Message_YesNo(message, title))
                continue;
            else
                break;
        }
        if (line.substr(0, 2) != to_string(newYear->yearStart).substr(2, 2)) // Check if the class name is valid
        {
            string message = "Invalid class name.\nDo you want to retry?";
            string title = "Error";
            if (Message_YesNo(message, title))
                continue;
            else
                break;
        }
        i++;
        if (!newYear->Class)
        {
            ClassTMP = new Class;
            newYear->Class = ClassTMP;
        }
        else
        {
            ClassTMP->next = new Class;
            ClassTMP->next->prev = ClassTMP;
            ClassTMP = ClassTMP->next;
        }
        ClassTMP->Name = line;
        string message = "Added class " + line + " successfully.";
        Message_Warning(message, "Success");
        message = "Add student to class?";
        if (Message_YesNo(message, "Success"))
        {
            Method(accHead, ClassTMP);
            Create_New_Classes(newYear, accHead);
            break;
        }
    }
    return true;
}

//? Choose the class to add Student
void ChooseClassToAdd(Year *curYear, Account *accHead)
{
    system("cls");
    TextColor(7);

    Render_Class(50, 1);
    goToXY(60, 12);
    cout << "Classes in " << curYear->yearStart << "-" << curYear->yearStart + 1;

    Class *class_cur = chooseClassbyOption_XY(curYear->Class, 60, 12, 4);
    if (class_cur == nullptr)
        return;
    Method(accHead, class_cur);
    string mess = "Do you want to add student to another class?";
    if (Message_YesNo(mess, "Another student?"))
    {
        ChooseClassToAdd(curYear, accHead);
        return;
    }
}

//? Choose the method to add student
void Method(Account *accHead, Class *curClass)
{
    system("cls");
    Render_Student(35, 3);
    vector<string> menu;
    menu.push_back("Adding by hand");
    menu.push_back("Importing from file");
    menu.push_back("Return");

    TextColor(63);
    for (int i = 0; i < 3; i++)
    {
        goToXY(58, 11 + i);
        cout << "                                ";
    }
    goToXY(60, 12);
    cout << "Choose method to add student";

    int opt = Draw_ShortVer(menu, 60, 15);
    switch (opt)
    {
    case 0:
        inputStudent(accHead, curClass);
        break;
    case 1:
        importStudent(accHead, curClass);
        break;
    case 2:
        return;
    }
    Method(accHead, curClass);
}

//? Input student by hand one the cmd
void inputStudent(Account *accHead, Class *curClass)
{
    system("cls");
    Render_Student(45, 3);
    string ID, first, last, gen, birth, socialID;
    string yr = curClass->Name.substr(0, 2);

    if (!Draw_In_Stud(ID, first, last, gen, birth, socialID, yr))
        return;

    if (Check_Student(curClass, ID))
    {
        string message = "Student has already been added!!!\nDo you want to re-enter?";
        if (Message_YesNo(message, "Conitnue"))
            inputStudent(accHead, curClass);
        return;
    }
    //? Add here
    add1stYearStudents(accHead, curClass, ID, first, last, gen, birth, socialID); // add to class
    string message = "Student " + last + " " + first + " has been added to class " + curClass->Name + ".";
    message += "\nDo you want to add another one to this class?";

    string title = "Student added";
    if (Message_YesNo(message, title))
    {
        inputStudent(accHead, curClass);
        return;
    }
    return;
}

//? Import student from file
void importStudent(Account *accHead, Class *curClass)
{
    system("cls");
    int y = 3;
    Render_Student(45, y);
    goToXY(50, 12);
    cout << "Please import the CSV file to folder New_Enrolled_Student.\n";
    goToXY(50, 13);
    cout << "Please enter file name(default: studentlist.csv, 0: to choose default): ";

    string fileName = "studentlist.csv";
    string tmp;

    goToXY(60, 14);
    cout << "File name: ";
    tmp = Limit_Input(60 + 11, 14, 25, 7);
    if (tmp == "-1")
        return;
    if (tmp != "0")
        fileName = tmp;
    // Get the file name in4 and access the file
    string path = "..\\Data_file" + separator + "New_Enrolled_Student" + separator + fileName;
    goToXY(60, 16);
    cout << "Using file at: " << path;
    // check if the file exits
    ifstream studentList(path.c_str());

    if (!studentList.is_open())
    {
        string message = "File not found!!!\nDo you want to retry?";
        if (Message_YesNo(message, "Conitnue"))
            importStudent(accHead, curClass);
        return;
    }

    // read CSV file line by line
    string line;
    string delimiter = ",";
    int lineCount = 0;

    getline(studentList, line);
    while (getline(studentList, line))
    {
        // split the line by commas
        size_t position = 0;
        stringstream ss(line);
        string token;
        string fields[6];
        int i = 0;

        while (i < 6)
        {
            if (i < 5)
            {
                position = line.find(delimiter);
                token = line.substr(0, position);
                line.erase(0, position + delimiter.length());
            }
            else
                token = line;
            fields[i] = token;
            i++;
        }

        // save the student information
        string studentID = fields[0];
        string firstName = fields[1];
        string lastName = fields[2];
        string gender = fields[3];
        string dateofBirth = fields[4];
        string socialID = fields[5];

        lineCount++;
        // add the student to class
        if (Check_Student(curClass, studentID))
        {
            lineCount--;
            continue;
        }
        else
            add1stYearStudents(accHead, curClass, studentID, firstName, lastName, gender, dateofBirth, socialID);
    }
    string mess = "Imported " + to_string(lineCount) + " students to class " + curClass->Name + ".";
    Message_Warning(mess, "Success");
}

//? Add student one by one
void add1stYearStudents(Account *accHead, Class *curClass, string ID, string first, string last, string gen, string birth, string socialID)
{
    Student *headStudent = curClass->StudentClass;
    Student *newStud = new Student;

    newStud->ID = ID;
    newStud->accStudent = new Account;

    //? Set information to student
    Account *accTmp = newStud->accStudent;
    accTmp->role = 1; //? Set role for student
    accTmp->firstName = first;
    accTmp->lastName = last;
    accTmp->Gender = gen;
    accTmp->birth = birth;
    accTmp->SocialID = socialID;

    if (!headStudent)
        curClass->StudentClass = newStud;
    else
    {
        while (headStudent->next)
            headStudent = headStudent->next;
        headStudent->next = newStud;
        newStud->prev = headStudent;
    }
    NewAccount(accHead, ID, accTmp);
    return;

    // string message = "Student " + accTmp->firstName + " " + accTmp->lastName + " has been added to class " + curClass->Name + ".";
    // string title = "Success";
    // Message_Warning(message, title);
}

bool Draw_In_Stud(string &ID, string &first, string &last, string &gen, string &birth, string &socialID, string ye)
{
    system("cls");
    TextColor(3);
    Render_Student(45, 1);

    vector<string> menu;
    menu.push_back("Student ID:          ");
    menu.push_back("Student fullname:    ");
    menu.push_back("Student gender(M/F): ");
    menu.push_back("Student birth:       ");
    menu.push_back("Student socialID:    ");
    string space = "                                                 ";

    TextColor(7);
    int i;
    for (i = 0; i < menu.size(); i++)
    {
        goToXY(62, 10 + 4 * i);
        cout << menu[i];
    }

    string line, full;
    i = 0;
    while (i < menu.size())
    {
        TextColor(63);
        for (int j = 0; j < 3; j++)
        {
            goToXY(60, 9 + 4 * i + j);
            cout << space;
        }
        goToXY(62, 10 + 4 * i);
        cout << menu[i];

        if (i == 0) // ID
        {
            line = Limit_Input(62 + menu[i].length() - 1, 10 + 4 * i, 8, 63);
            while (!isValidStudentID(line, ye))
            {
                if (line == "-1")
                    return false;

                string mess = "Invalid student ID. Please enter again.";
                Message_Warning(mess, "Warning");
                TextColor(63);
                goToXY(60, 9 + 4 * i + 1);
                cout << space;
                goToXY(62, 10 + 4 * i);
                cout << menu[i];
                line = Limit_Input(62 + menu[i].length() - 1, 10 + 4 * i, 8, 63);
            }
            ID = line;
        }
        else if (i == 1) // fullname
        {
            line = Limit_Input(62 + menu[i].length() - 1, 10 + 4 * i, 25, 63);
            if (line == "-1")
                return false;

            full = line;
        }
        else if (i == 2) // Gender
        {
            line = Limit_Input(62 + menu[i].length() - 1, 10 + 4 * i, 1, 63);
            while (!isValidGender(line))
            {
                if (line == "-1")
                    return false;
                TextColor(63);
                string mess = "Invalid gender format (M: male, F:female).\n Please enter again.";
                Message_Warning(mess, "Warning");
                goToXY(60, 9 + 4 * i + 1);
                cout << space;
                goToXY(62, 10 + 4 * i);
                cout << menu[i];
                line = Limit_Input(62 + menu[i].length() - 1, 10 + 4 * i, 1, 63);
            }
            gen = line;
        }

        else if (i == 3) // birth
        {
            line = Limit_Input(62 + menu[i].length() - 1, 10 + 4 * i, 10, 63);
            while (!isValidDate(line))
            {
                if (line == "-1")
                    return false;

                TextColor(63);
                string mess = "Invalid date format (dd/mm/yyyy).\n Please enter again.";
                Message_Warning(mess, "Warning");
                goToXY(60, 9 + 4 * i + 1);
                cout << space;
                goToXY(62, 10 + 4 * i);
                cout << menu[i];
                line = Limit_Input(62 + menu[i].length() - 1, 10 + 4 * i, 10, 63);
            }
            birth = line;
        }
        else if (i == 4) // social ID
        {
            line = Limit_Input(62 + menu[i].length() - 1, 10 + 4 * i, 12, 63);
            if (line == "-1")
                return false;

            socialID = line;
        }

        TextColor(7);
        for (int j = 0; j < 3; j++)
        {
            goToXY(60, 9 + 4 * i + j);
            cout << space;
        }
        goToXY(62, 10 + 4 * i);
        cout << menu[i] << line;
        i++;
    }
    SeparateName(full, first, last);
    return true;
}