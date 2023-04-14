#include "../Header/course.h"
#include "../Header/help.h"

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
    viewScoreCourseStudent(stuUpdate->ScoreBoardCourse);
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
    system ("cls");
    // //chọn 1 để nhập số bao danh học sinh cần sửa sau đó nhập khóa học
    // //chọn 2 để chọn khóa học có học sinh cần sửa điểm, sau đó chọn học sinh
    int nOption = 3;
    string *arrOption = new string [nOption];
    arrOption[0] = "1. Find student who need to update by ID.";
    arrOption[1] = "2. Find course which has score board need to update.";
    arrOption[2] = "3. To end to update.";
    
    string title = "Using arrow keys to move and press enter to choose your option";
    system("cls");
    int option = view_chooseOption(arrOption,nOption, title);
    // int option = 1;
    delete []arrOption;

    system ("cls");
    string IDStudent = "22127123";
    string CourseName = "CSC10002";

    if (option == 0) 
    {
        system ("cls");
        cout << "Please enter ID: ";
        getline(cin, IDStudent);
        Student *checkStudent = findStudentbyID(IDStudent, Yhead);

        // để khi nhập sai có thể báo ra
        nOption = 2;
        arrOption = new string [nOption];
        arrOption[0] = "-To re-enter again.";
        arrOption[1] = "-To end to update";

        while (!checkStudent) 
        {
            title = "The ID you entered does not exist. Please, press enter to choose below option to continue:";
            system ("pause");
            system ("cls");
            option = view_chooseOption(arrOption,nOption, title);
            if(option == 1) 
            {
                delete []arrOption;
                return;
            }
            cout << "Please re-enter ID: ";
            getline(cin, IDStudent);
            Student *checkStudent = findStudentbyID(IDStudent, Yhead);
        }

        // system ("cls");
        // //in ra các khóa của học sinh đó (trong kì đó), cho user nhập tên hoặc ID của khóa học để ra bản điểm để chỉnh sửa
        // cout << "Please enter name course or ID course:"; 
        // getline(cin, CourseName);

        //select khóa học
        CourseStudent *curCourse = checkStudent->course;
        nOption = 0;
        while (curCourse) 
        {
            nOption ++;
            curCourse = curCourse->next;
        }
        arrOption = new string [nOption+1];
        curCourse = checkStudent->course;
        for(int i = 0; i < nOption; i++)
        {
        arrOption[i] = curCourse->course->Name;
        curCourse = curCourse->next;
        }
        arrOption [nOption] = "<-";
        title = "Please enter to select course:";
        option = view_chooseOption(arrOption,nOption+1, title);
        delete []arrOption;
        if(option == nOption) return;

        Course *checkCourse = findCourse_ofStudent_byOption(checkStudent->course,option);
        
        //bắt đầu update
        updateSBC(IDStudent, checkCourse->studentCourse);
    }


    //nếu chọn 2:
    if (1 == option) 
    {
        Year *ChooseYear = nullptr;
        Semester *ChooseSem = nullptr;
        Course *ChooseCourse = nullptr;
        if(Yhead == nullptr){
            cout << "There are no school year.";
            system("pause");
            // gọi lại hàm mainmenu
            return;
        }
        do {
            ChooseYear = chooseYearbyOption(Yhead);
            if(ChooseYear == nullptr){
                //quay lại main menu
                return;
            }
            system("cls");
            do {
                if(ChooseYear->NoSemester == nullptr) {
                    cout << "There are no semester in this school year."  << endl;
                    system("pause");
                    break;
                }
                ChooseSem = chooseSemesterbyOption(ChooseYear->NoSemester);
                system("cls");

                if(ChooseSem){
                    if(ChooseSem->course == nullptr) {
                        cout << "There are no course in this semester" << endl;
                        system("pause");

                    } else{
                        ChooseCourse = chooseCoursebyOption(ChooseSem->course);
                    }
                    system("cls"); 
                } else 
                    break;
            }while(ChooseCourse == nullptr);
            
        } while (ChooseSem == nullptr);

        
        system ("cls");
        //hàm xem danh sách sinh viên trong khóa học

        cout << "Please enter ID: ";    
        getline(cin, IDStudent);
        StudentCourse *stuUpdate = find_SBC_ofStudent(IDStudent, ChooseCourse->studentCourse);
        if(stuUpdate == nullptr) {
            cout << "student is not exist.\n";
            system("pause");
            return;
        }
        updateSBC(IDStudent, ChooseCourse->studentCourse);
        return;
    }
    //không phải 0 hoặc 1 thì se thoát
} 