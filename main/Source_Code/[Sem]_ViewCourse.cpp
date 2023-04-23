#include "../Header/Semester.h"
#include "../Header/Year.h"
#include "../Header/Login.h"
#include "../Header/Utility.h"

// x: 0 for head, 1 for body, 2 for tail
void Tablize(int x)
{
    int c, l, r;
    if (x == 0)
    {
        c = 194;
        l = 195;
        r = 180;
    }
    else if (x == 1)
    {
        c = 197;
        l = 195;
        r = 180;
    }
    else
    {
        c = 193;
        l = 192;
        r = 217;
    }
    cout << char(l);
    for (int i = 0; i < 12; i++)
        cout << char(196);
    cout << char(c);
    for (int i = 0; i < 19; i++)
        cout << char(196);
    cout << char(c);
    for (int i = 0; i < 35; i++)
        cout << char(196);
    cout << char(c);
    for (int i = 0; i < 24; i++)
        cout << char(196);
    cout << char(r);
}

Course *Part_Of_Course(Course *&curCourse, Semester *&sem_cur)
{
    Render_ViewCourse(50, 1);

    int row = 10;
    char line = char(179);

    goToXY(25, row++);
    TextColor(7);
    cout << char(218);
    for (int i = 0; i < 93; i++)
        cout << char(196);
    cout << char(191);

    goToXY(25, row++);
    cout << line;
    TextColor(0xF1);
    cout << setw(44) << "Year: " << sem_cur->Year << " - " << sem_cur->Year + 1 << setw(38) << " ";
    TextColor(WHITE);
    cout << line;

    goToXY(25, row++);
    Tablize(0);

    goToXY(25, row++);
    cout << line << "  Semester  " << line
         << setw(14) << "Course ID" << setw(6) << line
         << setw(23) << "Course name" << setw(13) << line
         << setw(18) << "Teacher name" << setw(7) << line;

    goToXY(25, row++);
    Tablize(1);

    Course *cour = curCourse;
    Course *prev = nullptr;
    while (sem_cur)
    {
        while (cour)
        {
            goToXY(25, row++);
            cout << line << setw(6) << sem_cur->No << setw(7) << line;

            cout << setw(13) << cour->CourseID << setw(7) << line;
            int len = cour->Name.length();

            cout << setw(len + 2) << cour->Name << setw(36 - len - 2) << line;

            len = cour->TeacherName.length();
            cout << setw(len + 3) << cour->TeacherName << setw(25 - len - 3) << line;

            goToXY(25, row++);
            if (row >= 8 + 19)
            {
                Tablize(2);
                return cour;
            }
            // goToXY(25, row++);
            if (!cour->next && !sem_cur->next)
                Tablize(2);
            else
                Tablize(1);

            prev = cour;
            cour = cour->next;
        }
        if (!cour)
        {
            if (!sem_cur->next)
                return prev;
            sem_cur = sem_cur->next;
            cour = sem_cur->course;
        }
    }
    return prev; //!
}
//? View all the course in the school
void ViewCourse(Year *yearHead)
{
    // string arrow = "<<-->>";
    Semester *sem_cur = yearHead->NoSemester;
    Course *curCourse = sem_cur->course;
    Course *cour = Part_Of_Course(curCourse, sem_cur);

    while (1)
    {
        int c = _getch();
        switch (c)
        {
        case UP:
            if (!cour)
                break;
            while (cour != curCourse)
            {
                cour = cour->prev;
                if (!cour)
                {
                    sem_cur = sem_cur->prev;
                    cour = sem_cur->course;
                    while (cour->next)
                        cour = cour->next;
                }
            }
            if (curCourse->prev || sem_cur->prev)
            {
                for (int i = 0; i < 7; i++)
                {

                    curCourse = curCourse->prev;
                    if (!curCourse)
                    {
                        sem_cur = sem_cur->prev;
                        curCourse = sem_cur->course;
                        while (curCourse->next)
                            curCourse = curCourse->next;
                    }
                }
                system("cls");
                cour = Part_Of_Course(curCourse, sem_cur);
            }
            break;
        case DOWN:
            if (!cour)
                break;
            if (cour->next || sem_cur->next)
            {
                if (!cour->next)
                {
                    sem_cur = sem_cur->next;
                    curCourse = sem_cur->course;
                }
                else
                    curCourse = cour->next;
                system("cls");
                cour = Part_Of_Course(curCourse, sem_cur);
            }
            break;
        case LEFT:
            if (yearHead->prev)
            {
                yearHead = yearHead->prev;
                system("cls");
                sem_cur = yearHead->NoSemester;
                curCourse = sem_cur->course;
                cour = Part_Of_Course(curCourse, sem_cur);
            }
            break;

        case RIGHT:
            if (yearHead->next)
            {
                yearHead = yearHead->next;
                system("cls");
                sem_cur = yearHead->NoSemester;
                curCourse = sem_cur->course;
                cour = Part_Of_Course(curCourse, sem_cur);
            }
            break;

        case ENTER:
            return;
        case ESC:
            return;
        }
    }
}
