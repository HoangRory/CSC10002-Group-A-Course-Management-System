#include"../Header/course.h"
//lấy kí

string createNameFile(int year, int no_smt, string course, string file, string type) {
    string s_year = to_string(year) + "_" + to_string(year + 1) + "/";
    string s_smt = "smt" + to_string(no_smt) + "/";
    string path = "../Data_file/" + s_year + s_smt + course + file + "." + type;
    return path;
}

CourseStudent* CourseOfAClass (Student *studentHead) 
{
    CourseStudent *CourHead = nullptr, *tmp = nullptr;
    CourseStudent *courseCheck;
    while(studentHead) 
    {
        courseCheck = studentHead->course;
        while (courseCheck) 
        {
            if( !checkExistence_OfCourse(courseCheck, CourHead) ) 
            {
                CourseStudent *tmp = new CourseStudent;
                tmp->course = courseCheck->course;
                tmp->next = CourHead;
                CourHead = tmp;
            }
            courseCheck = courseCheck->next;
        }
        studentHead = studentHead->next;
    }
    return CourHead;
}
// nhập các final mark vào bảng điểm của lớp 
void CreateSB_ofStudent_inClass(double *&SBC, CourseStudent *courseHead, Student *studentHead) {
    StudentCourse *tmp;
    CourseStudent *courseCheck;
    int i = 0;
    while (courseHead) 
    {
        courseCheck = checkExistence_OfCourse(courseHead,studentHead->course);
        if (courseCheck) 
        {
            tmp = find_SBC_ofStudent(studentHead->ID, courseHead->course->studentCourse);
                SBC[i++] = tmp->ScoreBoardCourse.finalMark;
        } else 
            SBC[i++] = -1; // -1 là hs này không học môn đó
        courseHead = courseHead->next;
    }
}
void createSBC_ofClass(double **&SBC, CourseStudent *courseHead, Student *studentHead, int Col, int Row )
{
    SBC = new double*[Col + 1] ;
    for(int i = 0; i<Row; i++)
    {
        SBC[i] = new double[Col+1]; // +1 là + 1 cột cuối để lưu GPA của học sinh đó trong kì này
        CreateSB_ofStudent_inClass(SBC[i], courseHead, studentHead);
        SBC[i][Col] = CaculateGPA_1_Student(SBC[i], Col);
        studentHead = studentHead->next;
    }
}

