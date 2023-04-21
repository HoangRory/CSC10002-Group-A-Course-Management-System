#include "../Header/course.h"
#include "../Header/Utility.h"
//task 22

void enterMark(double &Mark) 
{
    // Mark = 2;
    cin >> Mark;
    while (Mark < 0 || Mark > 10) 
    {
        cout << "Please re-enter your score. 0 <= mark <= 10";
        cin  >> Mark;
    }
}
//return true = đã update, return false = không update
bool updateMark(ScoreBoardCourse &SBC, string Selection) {
    if( Selection == "1" || Selection == "MidMark" || Selection == "midmark") {
        cout << "MidMark = ";
        enterMark(SBC.midMark);
    } 
    else if( Selection == "2" || Selection == "FinalMark" || Selection == "finalmark") {
        cout << "FinalMark = ";
        enterMark(SBC.finalMark);
    }
    else if( Selection == "3" || Selection == "TotalMark" || Selection == "totalmark") {
        cout << "TotalMark = ";
        enterMark(SBC.totalMark);
    }
    else if( Selection == "4" || Selection == "OtherMark" || Selection == "othermark") {
        cout << "OtherMark = ";
        enterMark(SBC.otherMark);
    } else return false;

    return true;
}
void updateSBC (string ID, StudentCourse *stuUpdate) 
{
    //kẻ bảng điểm
    for(int i = 0; i < 69; i++) 
        cout << "=";
    cout << endl;
    cout << "| " << setw(15) << left << "Mid Mark ";
    cout << "| " << setw(15) << left << "Final Mark";
    cout << "| " << setw(15) << left << "Total Mark ";
    cout << "| " << setw(15) << left << "OtherMark";
    cout << "|"  << endl;
    for(int i = 0; i < 69; i++)
        cout << "=";
    cout << endl;
    cout << "| " << setw(15) << left << stuUpdate->ScoreBoardCourse.midMark;
    cout << "| " << setw(15) << left << stuUpdate->ScoreBoardCourse.finalMark;
    cout << "| " << setw(15) << left << stuUpdate->ScoreBoardCourse.totalMark;
    cout << "| " << setw(15) << left << stuUpdate->ScoreBoardCourse.otherMark;
    for(int i = 0; i < 69; i++)
        cout << "=";
    cout << endl;


    cout << "Select the mark you want to update. (eg: Enter 1 or MidMark to update MidMark)"
         << "Or enter X to end to update." << endl;
    string Selection = "";
    getline(cin,Selection);
    if(Selection == "X") return;

    if(updateMark(stuUpdate->ScoreBoardCourse, Selection)){
        cout << "Do you want to update more?"
                << "Selecion: Y (Yes) to continue or press any key to end to update.";
    } else {
        cout << "Your selection is not correct."
             << "Selecion: Y (Yes) to re-enter or press any key to end to update.";
    }
    cin >> Selection;
    cin.ignore();
    if (Selection != "Y") return;
    updateSBC(ID,stuUpdate);
}
void UpdateStudentResult(Year *Yhead) 
{
    // system ("cls");
    // //chọn 1 để nhập số bao danh học sinh cần sửa sau đó nhập khóa học
    // //chọn 2 để chọn khóa học có học sinh cần sửa điểm, sau đó chọn học sinh
    // vector <string> arrOption;
    // arrOption.push_back("Find by ID Student.");
    // arrOption.push_back("Find course.");
    // arrOption.push_back("To end to update.");
    
    // Print_Update();
    // int option  = Draw(arrOption);
    // string *arrOption = new string [nOption];
    // arrOption[1] = "2. ";
    // arrOption[2] = "3. ";
    
    // string title = "Using arrow keys to move and press enter to choose your option";
    // system("cls");
    // int option = view_chooseOption(arrOption,nOption, title);
    // int option = 1;
    // delete []arrOption;

    // system ("cls");
    // string IDStudent = "";
    // string CourseName = "";

    // if (option == 0) 
    // {
    //     system ("cls");
        

    //     cout << "Please enter ID: ";
    //     getline(cin, IDStudent);
    //     cin.ignore();
    //     Student *checkStudent = findStudentbyID(IDStudent, Yhead);

        // để khi nhập sai có thể báo ra
        // nOption = 2;
        // arrOption = new string [nOption];
        // arrOption[0] = "-To re-enter again.";
        // arrOption[1] = "-To end to update";

        // while (!checkStudent) 
        // {
            // title = "The ID you entered does not exist. Please, press enter to choose below option to continue:";
            // system ("pause");
            // system ("cls");
            // option = view_chooseOption(arrOption,nOption, title);
            // if(option == 1) 
            // {
            //     delete []arrOption;
            //     return;
            // }
            // cout << "Please re-enter ID: ";
            // getline(cin, IDStudent);
            // Student *checkStudent = findStudentbyID(IDStudent, Yhead);
        // }

        // system ("cls");
        // //in ra các khóa của học sinh đó (trong kì đó), cho user nhập tên hoặc ID của khóa học để ra bản điểm để chỉnh sửa
        // cout << "Please enter name course or ID course:"; 
        // getline(cin, CourseName);

        //select khóa học
        // CourseStudent *curCourse = checkStudent->course;
        // nOption = 0;
        // while (curCourse) 
        // {
        //     nOption ++;
        //     curCourse = curCourse->next;
        // }
        // arrOption = new string [nOption+1];
        // curCourse = checkStudent->course;
        // for(int i = 0; i < nOption; i++)
        // {
        // arrOption[i] = curCourse->course->Name;
        // curCourse = curCourse->next;
        // }
        // arrOption [nOption] = "<-";
        // title = "Please enter to select course:";
        // option = view_chooseOption(arrOption,nOption+1, title);
        // delete []arrOption;
        // if(option == nOption) return;

    //     Course *checkCourse = findCourse_ofStudent_byOption(checkStudent->course,option);
        
    //     //bắt đầu update
    //     updateSBC(IDStudent, checkCourse->studentCourse);
    // }


    //nếu chọn 2:
    // if (1 == option) 
    // {
        // Year *ChooseYear = nullptr;
        // Semester *ChooseSem = nullptr;
        // Course *ChooseCourse = nullptr;
        // if(Yhead == nullptr){
        //     Message_Warning("There are no school years at all", "Error not exist!");
        //     // gọi lại hàm mainmenu
        //     return;
        // } 
        //messbox
        int x, y;
        // do {
        //     Render_Update(40,1);
        //     Render_ScoreBoard(30, 7);
        //     Year *year_cur = Yhead;
        //     vector<string> menu;
        //     while (year_cur)
        //     {
        //         menu.push_back(to_string(year_cur->yearStart) + " - " + to_string(year_cur->yearStart + 1));
        //         year_cur = year_cur->next;
        //     }
        //     ChooseYear = chooseYearbyOption_XY(Yhead, 60, 15, 5);
        //     if(ChooseYear == nullptr)
        //         return;//quay lại main menu
        //     do {
        //         if(ChooseYear->NoSemester == nullptr) {
        //             Message_Warning("There are no semester in this school year.","Error not exist!");
        //            break;
        //         }
        //         ChooseSem = chooseSemesterbyOption_XY(ChooseYear->NoSemester, 60, 15, 5);
        //         if(ChooseSem)
        //             if(ChooseSem->course == nullptr) 
        //                 Message_Warning("There are no course in this semester", "Error not exist");
        //             else
        //                 ChooseCourse = chooseCoursebyOption_XY(ChooseSem->course, 60 ,15, 5);
                    
        //         else 
        //             break;
        //     }while(ChooseCourse == nullptr);
        // } while (ChooseSem == nullptr);
        // ChooseCourse = Yhead->NoSemester->course;
        // x = 10; y= 15;
        // StudentCourse *studentHead = ChooseCourse->studentCourse;
        
        // vector<vector<string>> table;
        // int height = 1, Row_eachTime = 8, Col_eachTime = 1, x_cur = 0, y_cur = 0;
        // bool edit_Col[6] = {false, false,true,true,true,true};
        // vector<int> width;
        // width.push_back(5);
        // width.push_back(12);
        // width.push_back(30);
        // width.push_back(15);
        // width.push_back(15);
        // width.push_back(15);
        // width.push_back(15);
        // vector<string> tmp;
        // for(int i = 0; studentHead != nullptr; i++){
            
        //     tmp.push_back(to_string(i+1));
        //     tmp.push_back(studentHead->ID);
        //     tmp.push_back(studentHead->FullName);
        //     tmp.push_back(to_string(studentHead->ScoreBoardCourse.midMark));
        //     tmp.push_back(to_string(studentHead->ScoreBoardCourse.finalMark));
        //     tmp.push_back(to_string(studentHead->ScoreBoardCourse.otherMark));
        //     tmp.push_back(to_string(studentHead->ScoreBoardCourse.totalMark));
        //     table.push_back(tmp);
        //     tmp.clear();
        //     studentHead = studentHead->next;
        // }

        // Draw_table(table, width,height,x,y,Row_eachTime,Col_eachTime,3,edit_Col, x_cur,y_cur);
    
        // system ("cls");
        //hàm xem danh sách sinh viên trong khóa học

        // cout << "Please enter ID: ";    
        // getline(cin, IDStudent);
        // StudentCourse *stuUpdate = find_SBC_ofStudent(IDStudent, ChooseCourse->studentCourse);
        // if(stuUpdate == nullptr) {
        //     cout << "student is not exist.\n";
        //     system("pause");
        //     return;
        // }
        // updateSBC(IDStudent, ChooseCourse->studentCourse);
        // return;
    // }
    //không phải 0 hoặc 1 thì se thoát


    Year *ChooseYear = nullptr;
        Semester *ChooseSem = nullptr;
        Course *ChooseCourse = nullptr;
        if(Yhead == nullptr){
            Message_Warning("There are no school years at all", "Error not exist!");
            // gọi lại hàm mainmenu
            return;
        } 
        do {
            Render_Update(40,1);
            Render_ScoreBoard(30, 7);
            Year *year_cur = Yhead;
            vector<string> menu;
            while (year_cur)
            {
                menu.push_back(to_string(year_cur->yearStart) + " - " + to_string(year_cur->yearStart + 1));
                year_cur = year_cur->next;
            }
            ChooseYear = chooseYearbyOption_XY(Yhead, 60, 15, 5);
            if(ChooseYear == nullptr)
                return;//quay lại main menu
            do {
                if(ChooseYear->NoSemester == nullptr) {
                    Message_Warning("There are no semester in this school year.","Error not exist!");
                   break;
                }
                ChooseSem = chooseSemesterbyOption_XY(ChooseYear->NoSemester, 60, 15, 5);
                if(ChooseSem)
                    if(ChooseSem->course == nullptr) 
                        Message_Warning("There are no course in this semester", "Error not exist");
                    else
                        ChooseCourse = chooseCoursebyOption_XY(ChooseSem->course, 60 ,15, 5);
                    
                else 
                    break;
            }while(ChooseCourse == nullptr);
        } while (ChooseSem == nullptr);
    

    x = 10;
    y= 15;
    StudentCourse *studentHead = ChooseCourse->studentCourse;

    int num_row = 0;
    while(studentHead) {
        num_row ++;
        studentHead = studentHead->next;
    }
    string **table = new string* [num_row];
    for(int i = 0; i < num_row; i++)
        table[i] = new string[7];
    
    int height = 1, Row_eachTime = 8, Col_eachTime = 7, x_cur = 0, y_cur = 0;
    bool edit_Col[7] = {false, false,false,true,true,true,true};
    int width[7];
    width[0] = 5;
    width[1] = 12;
    width[2] = 30;
    width[3] = 15;
    width[4] = 15;
    width[5] = 15;
    width[6] = 15;


    // vector<int> width;
    // width.push_back(5);
    // width.push_back(12);
    // width.push_back(30);
    // width.push_back(15);
    // width.push_back(15);
    // width.push_back(15);
    // width.push_back(15);
    studentHead = ChooseCourse->studentCourse;
    for(int i = 0; studentHead != nullptr; i++){
        int j = 0;
        table[i][j++] = to_string(i+1);
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
    Draw_table(table,num_row,7, width,height,x,y,Row_eachTime,Col_eachTime,3,edit_Col, x_cur,y_cur);
    // studentHead = yearHead->NoSemester->course->studentCourse;
    // for(int i = 0; studentHead!=nullptr; i++){
    //     for(int j = 0; j < 7; j ++){
    //         cout << table[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    for(int i = 0; i < num_row; i++)
        delete []table[i];
    delete []table;
} 