#include "proto.h"

//export the list student in course to file CSV
Year curYear;
Semester curSemester;
Course curCourse;
ofstream out;

void openScoreFile() {
    string path;
    path = to_string(curYear.yearStart) + "_" + to_string(curYear.yearStart)+ "/" + to_string(curSemester.No) + "/" + curCourse.Name + ".CSV"; 
    out.open (path);
}

void exportScoreBoardCourse(ScoreBoardCourse ScoreBoardCourse) {
    out << ScoreBoardCourse.totalMark << ","
        << ScoreBoardCourse.finalMark << ","
        << ScoreBoardCourse.midMark   << ","
        << ScoreBoardCourse.otherMark << ","
        << endl;
}

void exportStudent(StudentCourse *stuHead) {
    int No = 1;
    while (stuHead) {
        out << No++ << ","
            << stuHead->ID << ","
            << stuHead->FullName << ",";
        exportScoreBoardCourse(stuHead->ScoreBoardCourse);
    }
}

