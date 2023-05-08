#include "../Header/Class.h"

// View student
void Interface_ViewStudentClass(Year *yearHead) // task 16: view students in a class
{
    system("cls");
    int x = 60, y = 17;
    Render_StudentClass();
    Class *ChooseClass = nullptr;
    goToXY(42, y - 2);
    cout << "Select the Class, in which you want to show list student.";
    ChooseClass = chooseClass_inAllYear_byOption_XY(yearHead, x, y, 5);
    goToXY(42, y - 2);
    cout << setw(100) << " ";
    if (ChooseClass == nullptr)
        return;

    if (ChooseClass->StudentClass == nullptr)
        Message_Warning("There are no student in this class", "Error not Exist");
    else
    {
        goToXY(40, y - 1);
        cout << " The list of student of " << ChooseClass->Name << " class:";
        ViewStudentClass(ChooseClass, 40, y);
    }
    Interface_ViewStudentClass(yearHead);
}
// View ScoreBoard
void Interface_ViewScoreBoardClass(Year *yearHead)
{
    int x = 60, y = 17;
    system("cls");
    Render_ScoreBoardClass();

    Class *ChooseClass = nullptr;
    Semester *ChooseSem = nullptr;
    Year *ChooseYear_Sem = nullptr;
    Year *year_cur = yearHead;
    while (year_cur)
    {
        if (year_cur->Class)
            break;
        year_cur = year_cur->next;
    }
    if (!year_cur)
    {
        Message_Warning("There is no class in all school year ", "Error");
        return;
    }

    goToXY(45, y - 2);
    cout << "Select the Class, in which you want to show scoreboard.";
    ChooseClass = chooseClass_inAllYear_byOption_XY(yearHead, x, y, 5);
    goToXY(45, y - 2);
    cout << setw(100) << " ";
    while (ChooseClass)
    {
        if (!ChooseClass->StudentClass)
            Message_Warning("There are no student in class " + ChooseClass->Name + ".", "Error not exist");
        else
        {
            goToXY(35, y - 2);
            cout << "Select the school year that contains the semester, in which you want to show list scoreboard";
            ChooseYear_Sem = chooseYearbyOption_XY(yearHead, x, y, 5);
            goToXY(35, y - 2);
            cout << setw(100) << " ";
            while (ChooseYear_Sem)
            {
                if (ChooseYear_Sem->NoSemester == nullptr)
                    Message_Warning("There is no semester in year " + to_string(ChooseYear_Sem->yearStart) + " " + to_string(ChooseYear_Sem->yearStart + 1), "Error");
                else
                {
                    goToXY(45, y - 2);
                    cout << "Select the Semester, in which you want to show scoreboard.";
                    ChooseSem = chooseSemesterbyOption_XY(ChooseYear_Sem->NoSemester, x, y, 5);
                    goToXY(45, y - 2);
                    cout << setw(100) << " ";
                    while (ChooseSem)
                    {
                        ViewScoreboardClass(ChooseClass, ChooseSem, 20, y);
                        system("cls");
                        Render_ScoreBoardClass();
                        goToXY(45, y - 2);
                        cout << "Select the Semester, in which you want to show scoreboard.";
                        ChooseSem = chooseSemesterbyOption_XY(ChooseYear_Sem->NoSemester, x, y, 5);
                        goToXY(45, y - 2);
                        cout << setw(100) << " ";
                    }
                }
                goToXY(35, y - 2);
                cout << "Select the school year that contains the semester, in which you want to show list scoreboard";
                ChooseYear_Sem = chooseYearbyOption_XY(yearHead, x, y, 5);
                goToXY(35, y - 2);
                cout << setw(100) << " ";
            }
        }
        goToXY(45, y - 2);
        cout << "Select the Class, in which you want to show scoreboard.";
        ChooseClass = chooseClass_inAllYear_byOption_XY(yearHead, x, y, 5);
        goToXY(45, y - 2);
        cout << setw(100) << " ";
    }
}