#include "../Header/course.h"
#include "../Header/Utility.h"
// task 22
void updateSBC(Course* ChooseCourse, int x, int y)
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
    for (int i = 0; i < num_row; i++)
        table[i] = new string[7];

    int height = 1, Row_eachTime = 8, Col_eachTime = 7, x_cur = 0, y_cur = 0;
    bool edit_Col[7] = {false, false, false, true, true, true, true};

    studentHead = ChooseCourse->studentCourse;
    for (int i = 0; studentHead != nullptr; i++)
    {
        int j = 0;
        table[i][j++] = to_string(i + 1);
        table[i][j++] = studentHead->ID;
        table[i][j++] = studentHead->FullName;
        if(studentHead->ScoreBoardCourse.midMark == 10)
            table[i][j++] = to_string(studentHead->ScoreBoardCourse.midMark).substr(0,5);
        else 
            table[i][j++] = " " + to_string(studentHead->ScoreBoardCourse.midMark).substr(0,4);
        if(studentHead->ScoreBoardCourse.finalMark == 10)
            table[i][j++] = to_string(studentHead->ScoreBoardCourse.finalMark).substr(0,5);
        else 
            table[i][j++] = " " + to_string(studentHead->ScoreBoardCourse.finalMark).substr(0,4);        
        if(studentHead->ScoreBoardCourse.otherMark == 10)
            table[i][j++] = to_string(studentHead->ScoreBoardCourse.otherMark).substr(0,5);
        else 
            table[i][j++] = " " + to_string(studentHead->ScoreBoardCourse.otherMark).substr(0,4);
        if(studentHead->ScoreBoardCourse.midMark == 10)
            table[i][j++] = to_string(studentHead->ScoreBoardCourse.totalMark).substr(0,5);
        else 
            table[i][j++] = " " + to_string(studentHead->ScoreBoardCourse.totalMark).substr(0,4);
        
        studentHead = studentHead->next;
    }
    Draw_table(table,num_row,7, width, height, pos ,x,y,Row_eachTime,Col_eachTime,edit_Col, x_cur,y_cur);
    if(x_cur == -1){
        for(int i = 0; i < num_row; i++)
            delete []table[i];
        delete []table;        
        delete []pos;
        return;
    }
    studentHead = ChooseCourse->studentCourse;
    for(int i = 0; i< y_cur; i++)
        studentHead = studentHead->next;
    int mark = 1;
    bool stop = false;
    switch (x_cur)
    {
    case 3:
        while (!stop) {
            mark = studentHead->ScoreBoardCourse.midMark = stod( Limit_Input(x + pos[x_cur%Col_eachTime], y + (y_cur%Row_eachTime) * height, 15,0xFF) );
            if(mark < 0 || mark > 10)
                stop = !Message_YesNo("Please re-enter your score. 0 <= mark <= 10\n Press yes to re-enter or no to stop.", "Errol!");
        }         
        break;
    case 4:
        while (!stop) {
            mark = studentHead->ScoreBoardCourse.finalMark = stod( Limit_Input(x + pos[x_cur%Col_eachTime], y + (y_cur%Row_eachTime) * height, 15,0xFF) );
            if(mark < 0 || mark > 10)
                stop = !Message_YesNo("Please re-enter your score. 0 <= mark <= 10\n Press yes to re-enter or no to stop.", "Errol!");
        }     
        break;
    case 5:
        while (!stop) {
            mark = studentHead->ScoreBoardCourse.otherMark = stod( Limit_Input(x + pos[x_cur%Col_eachTime], y + (y_cur%Row_eachTime) * height, 15,0xFF) );
            if(mark < 0 || mark > 10)
                stop = !Message_YesNo("Please re-enter your score. 0 <= mark <= 10\n Press yes to re-enter or no to stop.", "Errol!");
        }     
        break;
    case 6:
        while (!stop) {
            mark = studentHead->ScoreBoardCourse.totalMark = stod( Limit_Input(x + pos[x_cur%Col_eachTime], y + (y_cur%Row_eachTime) * height, 15,0xFF) );
            if(mark < 0 || mark > 10)
                stop = !Message_YesNo("Please re-enter your score. 0 <= mark <= 10\n Press yes to re-enter or no to stop.", "Errol!");
        }     
        break;
    default:
        break;
    }
    updateSBC(ChooseCourse, x, y);
}

void UpdateStudentResult(Year *Yhead)
{
    Year *ChooseYear = nullptr;
    Semester *ChooseSem = nullptr;
    Course *ChooseCourse = nullptr;
    if (Yhead == nullptr)
    {
        Message_Warning("There are no school years at all", "Error not exist!");
        // gọi lại hàm mainmenu
        return;
    }
    do
    {
        Render_Update(40, 1);
        Render_ScoreBoard(30, 7);
        Year *year_cur = Yhead;
        vector<string> menu;
        while (year_cur)
        {
            menu.push_back(to_string(year_cur->yearStart) + " - " + to_string(year_cur->yearStart + 1));
            year_cur = year_cur->next;
        }
        ChooseYear = chooseYearbyOption_XY(Yhead, 60, 15, 5);
        if (ChooseYear == nullptr)
            return; // quay lại main menu
        do
        {
            if (ChooseYear->NoSemester == nullptr)
            {
                Message_Warning("There are no semester in this school year.", "Error not exist!");
                break;
            }
            ChooseSem = chooseSemesterbyOption_XY(ChooseYear->NoSemester, 60, 15, 5);
            if (ChooseSem)
                if (ChooseSem->course == nullptr)
                    Message_Warning("There are no course in this semester", "Error not exist");
                else
                    ChooseCourse = chooseCoursebyOption_XY(ChooseSem->course, 60, 15, 5);

            else
                break;
        } while (ChooseCourse == nullptr);
    } while (ChooseSem == nullptr);
    int x = 20, y = 15;
    updateSBC(ChooseCourse, x, y);
}
