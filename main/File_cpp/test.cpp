#include<iostream>
#include<conio.h>
#include<windows.h>
using namespace std;
void ShowConsoleCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}

// int view_chooseOption(string *arrOption, int nOption) {
//     HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
//     bool stop = false;
//     int option = 0;
//     system ("cls");
//     cout << "Select search option. Enter:" << endl;

//     for(int i = 0; i < nOption; i++) {
//         if(i == option) {
//             SetConsoleTextAttribute(color, 6);
//             cout << arrOption[i] << endl;
//             SetConsoleTextAttribute(color, 7);
//         } else cout << arrOption[i] << endl;
//     }
//     while(!stop) {
//         if (_kbhit()) {
//             switch(_getch()) {
//                 case 72 : 
//                     option--;
//                     if(option < 0) 
//                         option = nOption - 1;
//                 break;
//                 case 80:
//                     option ++;
//                     if(option == nOption)
//                         option = 0; 
//                 break;
//                 case 13:
//                     stop = true;
//                 break;
//             }
//             if(stop) 
//                 break;
//             system ("cls");
//             cout << "Select search option. Enter:" << endl;
//             for(int i = 0; i < nOption; i++) {
//                 if(i == option) {
//                     SetConsoleTextAttribute(color, 6);
//                     cout << arrOption[i] << endl;
//                     SetConsoleTextAttribute(color, 7);
//                 } else cout << arrOption[i] << endl;
//             }
//         }
//     }
//     return option;
// }

// int main() {
//     int nOption = 3;
//     string *arrOption = new string [nOption];
//     arrOption[0] = "- Find student who need to update by ID.";
//     arrOption[1] = "- Find course which have score board need to update.";
//     arrOption[2] = "- To end to update.";
//     ShowConsoleCursor(false);
//     view_chooseOption(arrOption,nOption);
//     ShowConsoleCursor(true);
//     delete []arrOption;
//     return 0;
// }