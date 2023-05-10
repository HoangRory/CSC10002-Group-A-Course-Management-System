#include "../Header/Course.h"
// task 22
void updateSBC(Course *ChooseCourse, int x, int y, int x_cur, int y_cur)
{
    int width[7];
    width[0] = 5;
    width[1] = 12;
    width[2] = 30;
    width[3] = 15;
    width[4] = 15;
    width[5] = 15;
    width[6] = 15;
    int *pos = new int[7]; // vị trí bắt đầu của các cột, bắt đầu từ cột đầu là 0
    pos[0] = 0;
    for (int i = 1; i < 7; i++)
    {
        pos[i] = pos[i - 1] + width[i - 1];
    }
    x = 10;
    y = 15;
    StudentCourse *studentHead = ChooseCourse->studentCourse;

    int num_row = 0;
    while (studentHead)
    {
        num_row++;
        studentHead = studentHead->next;
    }
    string **table = new string *[num_row];
    for (int i = 0; i <= num_row; i++)
        table[i] = new string[7];

    int height = 1, Row_eachTime = 7, Col_eachTime = 7;
    bool edit_Col[7] = {false, false, false, true, true, true, true};
    int t = 0;
    string *title = new string[7];
    title[t++] = "NO";
    title[t++] = "ID";
    title[t++] = "Full Name";
    title[t++] = "Mid Mark";
    title[t++] = "Final Mark";
    title[t++] = "Other Mark";
    title[t++] = "Total Mark";

    studentHead = ChooseCourse->studentCourse;
    for (int i = 0; studentHead != nullptr; i++)
    {
        int j = 0;
        table[i][j++] = to_string(i + 1);
        table[i][j++] = studentHead->ID;
        table[i][j++] = studentHead->FullName;
        table[i][j++] = FormatMark(studentHead->ScoreBoardCourse.midMark);
        table[i][j++] = FormatMark(studentHead->ScoreBoardCourse.finalMark);
        table[i][j++] = FormatMark(studentHead->ScoreBoardCourse.otherMark);
        table[i][j++] = FormatMark(studentHead->ScoreBoardCourse.totalMark);
        studentHead = studentHead->next;
    }
    goToXY(x, y - 2);
    cout << "Press Enter to select";
    Draw_table(table, title, num_row, 7, width, height, x, y, Row_eachTime, Col_eachTime, edit_Col, x_cur, y_cur);
    if (x_cur == -1)
    {
        for (int i = 0; i < num_row; i++)
            delete[] table[i];
        delete[] table;
        return;
    }
    studentHead = ChooseCourse->studentCourse;
    for (int i = 0; i < y_cur; i++)
        studentHead = studentHead->next;
    int mark = 1;
    bool stop = false;
    string s_mark;
    do
    {
        goToXY(x + pos[x_cur % Col_eachTime] + 1, y + (y_cur % Row_eachTime) * (height + 1) + 2);
        TextColor(0xF3);
        cout << setw(13) << " ";
        s_mark = Limit_Input(x + pos[x_cur % Col_eachTime] + 3, y + (y_cur % Row_eachTime) * (height + 1) + 2, 11, 0xF3); // +2 để bỏ qua title
        if (isDouble(s_mark))
        {
            mark = stod(s_mark);
            if (mark < 0 || mark > 10)
                stop = !Message_YesNo("Please re-enter your score. 0 <= mark <= 10\n Press yes to re-enter or no to stop.", "Errol!");
            else
            {
                switch (x_cur)
                {
                case 3:
                    studentHead->ScoreBoardCourse.midMark = mark;
                    break;
                case 4:
                    studentHead->ScoreBoardCourse.finalMark = mark;
                    break;
                case 5:
                    studentHead->ScoreBoardCourse.otherMark = mark;
                    break;
                case 6:
                    studentHead->ScoreBoardCourse.totalMark = mark;
                    break;
                default:
                    break;
                }
                stop = true;
            }
        }
        else
            stop = !Message_YesNo("Please re-enter your score. 0 <= mark <= 10\n Press yes to re-enter or no to stop.", "Errol!");
    } while (!stop);
    updateSBC(ChooseCourse, x, y, x_cur, y_cur);
}
void UpdateStudentResult(Year *Yhead)
{
    system("cls");
    Render_Update(40, 3);
    Semester *ChooseSem = nullptr;
    Course *ChooseCourse = nullptr;
    if (Yhead == nullptr)
    {
        Message_Warning("There are no school years at all", "Error not exist!");
        // gọi lại hàm mainmenu
        return;
    }
    Semester *sem_cur = Yhead->NoSemester;
    // lấy học kì hiện tại của năm hiện tại
    if (sem_cur == nullptr)
    {
        Message_Warning("There are no semester in current school year.", "Error not exist!");
        return;
    }
    while (sem_cur && sem_cur->next)
        sem_cur = sem_cur->next;
    if (sem_cur->course == nullptr)
    {
        Message_Warning("There are no course in current semester.", "Error not exist!");
        return;
    }
    goToXY(45, 15);
    cout << "Select the student's course, in which you want to update scoreboard.";
    ChooseCourse = chooseCoursebyOption_XY(sem_cur->course, 60, 17, 5);
    goToXY(45, 15);
    cout << setw(100) << " ";
    if (!ChooseCourse)
        return;
    int x = 30, y = 17, x_cur = 0, y_cur = 0;
    goToXY(20, 14);
    cout << "Select the student for whom you want to update scoreboard.";
    updateSBC(ChooseCourse, x, y, x_cur, y_cur);
    UpdateStudentResult(Yhead);
}