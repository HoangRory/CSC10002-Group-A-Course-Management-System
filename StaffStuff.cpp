#include "proto.h"

//! Run after the Login file to collect the ROLE
Semester* semHead;

void Read(){
    ifstream ifs("CSVFile/semester.txt");
    Semester * cur;
    while (!ifs.eof){
        if (!semHead)
        {
            semHead = new Semester;
            cur = semHead;
        }
        else
        {
            cur->next = new Semester;
            Semester *tmp = cur;
            cur = cur->next;
            cur->prev = tmp;
            cur->next = nullptr;
        }
        ifs >> cur->No >> cur->yearStartSchool >> cur->startDate >> cur->endDate;
        ifs >> cur->
    }
}