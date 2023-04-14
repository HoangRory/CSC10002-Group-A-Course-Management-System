#include "../Header/Utility.h"

int Draw(vector<string> menu)
{
    vector<int> choice(menu.size(), 0);
    int cur = 0;
    ShowConsoleCursor(0);
    while (1)
    {
        choice[cur] = 1;
        for (int i = 0; i < choice.size(); i++)
        {
            if (choice[i])
            {
                TextColor(0xFF);
                for (int j = 0; j < 3; j++)
                {
                    goToXY(60, 12 + i * 3 + j);
                    cout << "                         ";
                }
                goToXY(62, 13 + i * 3);
                TextColor(0xFC);
                cout << menu[i];
            }
            else
            {
                TextColor(7);
                for (int j = 0; j < 3; j++)
                {
                    goToXY(60, 12 + i * 3 + j);
                    cout << "                         ";
                }
                goToXY(62, 13 + i * 3);
                TextColor(7);
                cout << menu[i];
            }
        }
        TextColor(07);
        int tmp;
        if (tmp = _getch())
        {
            switch (tmp)
            {
            case ENTER:
                system("cls");
                ShowConsoleCursor(1);
                return cur;
            case UP:
                choice[cur] = 0;
                cur = (cur > 0 ? cur - 1 : menu.size() - 1);
                break;
            case DOWN:
                choice[cur] = 0;
                cur = (cur < menu.size() - 1 ? cur + 1 : 0);
                break;
            }
        }
    }
}

void PrintMenu()
{
    goToXY(58, 2);
    TextColor(0x0A);
    cout << "___  ___ _____  _   _  _   _\n";
    goToXY(58, 3);
    TextColor(0x0B);
    cout << "|  \\/  ||  ___|| \\ | || | | |\n";
    goToXY(58, 4);
    TextColor(0x0C);
    cout << "| .  . || |__  |  \\| || | | |\n";
    goToXY(58, 5);
    TextColor(0x0D);
    cout << "| |\\/| ||  __| | . ` || | | |\n";
    goToXY(58, 6);
    TextColor(0x0E);
    cout << "| |  | || |___ | |\\  || |_| |\n";
    goToXY(58, 7);
    TextColor(0x0F);
    cout << "\\_|  |_/\\____/ \\_| \\_/ \\___/\n";
}

void PrintView_Course()
{
    goToXY(54, 1);
    TextColor(0x0A);
    cout << "   _____  _____  _   _ ______  _____  _____\n";
    goToXY(54, 2);
    TextColor(0x0B);
    cout << "  /  __ \\|  _  || | | || ___ \\/  ___||  ___|\n";
    goToXY(54, 3);
    TextColor(0x0C);
    cout << "  | /  \\/| | | || | | || |_/ /\\ `--. | |__\n";
    goToXY(54, 4);
    TextColor(0x0D);
    cout << "  | |    | | | || | | ||    /  `--. \\|  __|\n";
    goToXY(54, 5);
    TextColor(0x0E);
    cout << "  | \\__/\\\\ \\_/ /| |_| || |\\ \\ /\\__/ /| |__\n";
    goToXY(54, 6);
    TextColor(0x0F);
    cout << "   \\____/ \\___/  \\___/ \\_| \\_|\\____/ \\____/\n";
}