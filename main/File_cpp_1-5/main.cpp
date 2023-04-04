#include "..\\Header\\Year.h"

Year *Create_NewYear(Year *yearHead)
{
    Year *yearTMP = yearHead;
    while (yearTMP->next)
        yearTMP = yearTMP->next;

    int year;
    int current = yearTMP->yearStart;
    cout << "Current year: " << current << "-" << current + 1 << "\nCreating year: " << current + 1 << "-" << current + 2 << "?\n";
    int yr_choice;
    cout << "1. Yes\n2. Enter a 'something year :))))'\n";
    cin >> yr_choice;

    if (yr_choice == 1)
        year = current + 1;
    else
    {
        cout << "Enter the year: ";
        cin >> year;
    }

    Year *newYear = new Year;
    newYear->yearStart = year;
    yearTMP->next = newYear;

    //? return the new year for further inputing 1st year student
    return newYear;
}

void Adding_New_Classes(Year *newYear)
{
    cout << "Enter -1 to stop adding new classes\n";
    cout << "Adding new classes to year " << newYear->yearStart << "_" << newYear->yearStart + 1 << ":\n";
    Class *ClassTMP = newYear->Class;

    string line;
    while (cin >> line)
    {
        if (line == "-1")
            break;
        
        if (!ClassTMP)
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
    }
}
void Adding_1st_Student(Year *newYear)
{
}

int main()
{
    Year *yearHead = nullptr;
    yearHead = Read_Multi_year();

    DeleteYear(yearHead);
    return 0;
}

Year *Read_Year_Class(int year)
{
    string yr = to_string(year) + '_' + to_string(year + 1);
    string path = "..\\Data_file\\" + yr + "\\class.txt";

    ifstream ifs(path);
    if (!ifs)
        return nullptr;

    Year *yearTMP = new Year;
    yearTMP->yearStart = year;
    // yearTMP->Class = new Class;
    Class *ClassTMP = yearTMP->Class;

    while (!ifs.eof())
    {
        string line;

        if (!ClassTMP)
        {
            ClassTMP = new Class;
            yearTMP->Class = ClassTMP;
        }
        else
        {
            ClassTMP->next = new Class;
            ClassTMP->next->prev = ClassTMP;
            ClassTMP = ClassTMP->next;
        }

        ifs >> ClassTMP->Name;

        Student *StudentTMP;
        while (ifs >> line)
        {
            if (line == "-1")
                break;

            if (!ClassTMP->StudentClass)
            {
                ClassTMP->StudentClass = new Student;
                StudentTMP = ClassTMP->StudentClass;
            }
            else
            {
                StudentTMP->next = new Student;
                StudentTMP->next->prev = StudentTMP;
                StudentTMP = StudentTMP->next;
            }
            StudentTMP->ID = line;
        }
    }

    ifs.close();
    return yearTMP;
}

Year *Read_Multi_year()
{
    string path = "..\\Data_file\\year.txt";

    ifstream ifs(path);
    if (!ifs)
        return nullptr;

    Year *yearHead = nullptr;
    while (!ifs.eof())
    {
        string tmp_year;
        ifs >> tmp_year;
        if (!yearHead)
            yearHead = Read_Year_Class(stoi(tmp_year));
        else
        {
            Year *yearTMP = yearHead;
            while (yearTMP->next)
                yearTMP = yearTMP->next;
            yearTMP->next = Read_Year_Class(stoi(tmp_year));
        }
    }

    ifs.close();
    return yearHead;
}

void DeleteYear(Year *&yearHead)
{
    Year *yearTMP = yearHead;
    while (yearTMP)
    {
        Class *ClassTMP = yearTMP->Class;
        while (ClassTMP)
        {
            Student *StudentTMP = ClassTMP->StudentClass;
            while (StudentTMP)
            {
                Student *StudentTMP2 = StudentTMP;
                StudentTMP = StudentTMP->next;
                delete StudentTMP2;
            }
            Class *ClassTMP2 = ClassTMP;
            ClassTMP = ClassTMP->next;
            delete ClassTMP2;
        }
        Year *yearTMP2 = yearTMP;
        yearTMP = yearTMP->next;
        delete yearTMP2;
    }
    yearHead = nullptr;
}
