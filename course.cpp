#include "proto.h"

//export the list student in course to file CSV
int curYear;



void exportScoreBoard(ScoreBoard ScoreBoard, ofstream &out) {
    out << ScoreBoard.totalMark << ","
        << ScoreBoard.finalMark << ","
        << ScoreBoard.midMark   << ","
        << ScoreBoard.otherMark << ","
        << endl;
}

void exportStudent(StudentCourse *stuHead, ofstream &out) {
    int No = 1;
    while (stuHead) {

        out << No++ << ","
            << stuHead->ID << ","
            << stuHead->FullName << ",";
        exportScoreBoard(stuHead->ScoreBoard, out);
    }
}

