#include "../Header/proto.h"
#include "../Header/Utility.h"
#include "../Header/Help.h"

///////////////////////////////////////////////////////////
//                INTERFACE - VIEW                       //
///////////////////////////////////////////////////////////
//? for staff view
//? student
void Interface_ViewStudentClass(Year *yearHead);         //? task 16
void ViewStudentClass(Class *ChooseClass, int x, int y); //? task 16
//? scoreboard
void Interface_ViewScoreBoardClass(Year *yearHead);                        //? task 23
void ViewScoreboardClass(Class *Class, Semester *ChooseSem, int x, int y); //? task 23
//? view all class
void ViewClass(Year *yearHead); //? task 15