#include<iostream>
#include<conio.h>
#include<windows.h>
using namespace std;
int main() {
    bool stop = false;
    HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);



    system("cls");
    cout << "Select search option. Enter:" << endl;
    SetConsoleTextAttribute(color, 2);
    cout << " Find student who need to update by ID." << endl;
    SetConsoleTextAttribute(color, 7);
    cout << " Find course which have score board need to update." << endl 
         << " To end to update."<< endl;

    int option = 1;
    while (!stop) {
        if (_kbhit()) {
            switch(_getch()) {
                case 72 :
                    if(option > 1) 
                        option--;
                break;
                case 80:
                    if(option < 3) 
                        option ++;
                break;
                case 13:
                    stop = true;
                break;
            }
            if(stop) 
                break;

            system("cls");
            cout << "Select search option. Enter:" << endl;
            switch (option)
            {
            case 1:
                SetConsoleTextAttribute(color, 2);
                cout << " Find student who need to update by ID." << endl;
                SetConsoleTextAttribute(color, 7);
                cout << " Find course which have score board need to update." << endl 
                    << " To end to update."<< endl;
                break;
            case 2:
                cout << " Find student who need to update by ID." << endl;
                SetConsoleTextAttribute(color, 2);
                cout << " Find course which have score board need to update." << endl;
                SetConsoleTextAttribute(color, 7);
                cout << " To end to update."<< endl;   
                break;  
            case 3:
                cout << " Find student who need to update by ID." << endl;
                cout << " Find course which have score board need to update." << endl;
                SetConsoleTextAttribute(color, 2);
                cout << " To end to update."<< endl;                         
                SetConsoleTextAttribute(color, 7);
                break;
            }
        }
    }

    return 0;
}