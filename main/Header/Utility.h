#pragma once
#include "proto.h"

void ShowConsoleCursor(bool showFlag);
void TextColor(int x);
void goToXY(int x, int y);
void resizeWindow(int x, int y);
void hideScrollBar();
void initWindow(int width, int length);

//? Pause the program
void Pause();
//? Popup message box
void Message_Warning(string message, string title);
bool Message_YesNo(string message, string title);

//? Draw Word Art
void Render_Login();
void Render_Menu();
void Render_ViewCourse();
void Render_Account();
void Render_NewYear();
void Render_Semester();
void Render_View();
void Render_Class(int x, int y);
void Render_Course(int x, int y);
void Render_Student(int x, int y);
void Render_Export(int x, int y);
void Render_Import(int x, int y);
void Render_ScoreBoard(int x, int y);
void Render_Update(int x, int y);
void Render_StudentClass();
void Render_StudentCourse();
void Render_ScoreBoardCourse();
void Render_ScoreBoardClass(); 
//? Draw the option
int Draw(vector<string> menu);
int Draw_XY(vector<string> menu, int xStart, int yStart, int nOption_eachTime, int width);
int Draw_ShortVer(vector<string> menu);
int Draw_Horizontal_XY(vector<string> menu, int x , int y, int &cur);