#pragma once
#include "proto.h"

void ShowConsoleCursor(bool showFlag);
void TextColor(int x);
void goToXY(int x, int y);
void resizeWindow(int x, int y);
void hideScrollBar();
void initWindow(int width, int length);

//? Draw the menu word
void PrintMenu();

//? Draw the option
int Draw(vector<string> menu);
void PrintView_Course();