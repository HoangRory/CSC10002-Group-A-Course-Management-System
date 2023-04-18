#include "../Header/Utility.h"
using namespace std;
int Draw_XY(vector<string> menu, int xStart, int yStart)
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
                    goToXY(xStart, yStart + i * 3 + j);
                    cout << "                         ";
                }
                goToXY(xStart+2, yStart + 1 + i * 3);
                TextColor(0xF3);
                cout << menu[i];
            }
            else
            {
                TextColor(7);
                for (int j = 0; j < 3; j++)
                {
                    goToXY(xStart, yStart + i * 3 + j);
                    cout << "                         ";
                }
                goToXY(xStart+2, yStart+1 + i * 3);
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

int Draw_Horizontal_XY(vector<string> menu, int x , int y)
{
    vector<int> choice(menu.size(), 0);
    int cur = 0;
    ShowConsoleCursor(0);
    while (1)
    {
        choice[cur] = 1;
        for (int i = 0; i < choice.size(); i++)
        {
            for (int j = 0; j < 3; j ++)
            {
                if (choice[i])
                {
                    TextColor(0xFF);
                    goToXY(x + 3 * i, y + j);
                    cout << "   ";
                    goToXY(x + 1 + 3 * i, y + 1);
                    TextColor(0xF3);
                    cout << menu[i];
                }
                else
                {
                    TextColor(7);
                    goToXY(x + 3 * i, y + j);
                    cout << "   ";
                    goToXY(x + 1 + 3 * i, y + 1);
                    TextColor(7);
                    cout << menu[i];
                }
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
            case LEFT:
                choice[cur] = 0;
                cur = (cur > 0 ? cur - 1 : menu.size() - 1);
                break;
            case RIGHT:
                choice[cur] = 0;
                cur = (cur < menu.size() - 1 ? cur + 1 : 0);
                break;
            }
        }
    }   
}

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
                TextColor(0xF3);
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



int Draw_ShortVer(vector<string> menu)
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
                goToXY(60, 14 + i);
                cout << "                         ";
                goToXY(62, 14 + i);
                TextColor(0xF3);
                cout << menu[i];
            }
            else
            {
                TextColor(7);
                goToXY(60, 14 + i);
                cout << "                         ";
                goToXY(62, 14 + i);
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

void Render_Login()
{
    TextColor(11);
    goToXY(15, 1);
    cout << " ___  ___  ___   _   _   ___   _____  _____ ___  ___ _____  _   _  _____   _____ __   __ _____  _____  _____ ___  ___";
    goToXY(15, 2);
    cout << " |  \\/  | / _ \\ | \\ | | / _ \\ |  __ \\|  ___||  \\/  ||  ___|| \\ | ||_   _| /  ___|\\ \\ / //  ___||_   _||  ___||  \\/  |";
    goToXY(15, 3);
    cout << " | .  . |/ /_\\ \\|  \\| |/ /_\\ \\| |  \\/| |__  | .  . || |__  |  \\| |  | |   \\ `--.  \\ V / \\ `--.   | |  | |__  | .  . |";
    goToXY(15, 4);
    cout << " | |\\/| ||  _  || . ` ||  _  || | __ |  __| | |\\/| ||  __| | . ` |  | |    `--. \\  \\ /   `--. \\  | |  |  __| | |\\/| |";
    goToXY(15, 5);
    cout << " | |  | || | | || |\\  || | | || |_\\ \\| |___ | |  | || |___ | |\\  |  | |   /\\__/ /  | |  /\\__/ /  | |  | |___ | |  | |";
    goToXY(15, 6);
    cout << " \\_|  |_/\\_| |_/\\_| \\_/\\_| |_/ \\____/\\____/ \\_|  |_/\\____/ \\_| \\_/  \\_/   \\____/   \\_/  \\____/   \\_/  \\____/ \\_|  |_/";

    TextColor(10);
    goToXY(60, 10);
    cout << " _     ___    ___ ___  _  _";
    goToXY(60, 11);
    cout << "| |   / _ \\  / __|_ _|| \\| |";
    goToXY(60, 12);
    cout << "| |__| (_) || (_ || | | .` |";
    goToXY(60, 13);
    cout << "|____|\\___/  \\___|___||_|\\_|";
    TextColor(7);
}

void Render_Menu()
{
    goToXY(58, 2);
    TextColor(0x0A);
    cout << "___  ___ _____  _   _  _   _";
    goToXY(58, 3);
    TextColor(0x0B);
    cout << "|  \\/  ||  ___|| \\ | || | | |";
    goToXY(58, 4);
    TextColor(0x0C);
    cout << "| .  . || |__  |  \\| || | | |";
    goToXY(58, 5);
    TextColor(0x0D);
    cout << "| |\\/| ||  __| | . ` || | | |";
    goToXY(58, 6);
    TextColor(0x0E);
    cout << "| |  | || |___ | |\\  || |_| |";
    goToXY(58, 7);
    TextColor(0x0F);
    cout << "\\_|  |_/\\____/ \\_| \\_/ \\___/";
    TextColor(7);
}

void Render_ViewCourse()
{
    int x = 50, y = 1;
    goToXY(x, y++);
    TextColor(0x0A);
    cout << "   _____  _____  _   _ ______  _____  _____";
    goToXY(x, y++);
    TextColor(0x0C);
    cout << "  /  __ \\|  _  || | | || ___ \\/  ___||  ___|";
    goToXY(x, y++);
    TextColor(0x0E);
    cout << "  | |    | | | || | | ||    /  `--. \\|  __|";
    goToXY(x, y++);
    TextColor(0x0D);
    cout << "  | \\__/\\\\ \\_/ /| |_| || |\\ \\ /\\__/ /| |__";
    goToXY(x, y++);
    TextColor(0x0B);
    cout << "   \\____/ \\___/  \\___/ \\_| \\_|\\____/ \\____/";
    TextColor(6);
}


void Print_Update()
{
    int i = 1;
    goToXY(54,i++);
    TextColor(0x0A);
    cout <<   " _   _  _____ ______   ___   _____  _____ ";
    goToXY(54,i++);
    TextColor(0x0A);
    cout <<   "| | | || ___ \\|  _  \\ / _ \\ |_   _||  ___|";
    goToXY(54,i++);
    TextColor(0x0A);
    cout <<   "| | | || |_/ /| | | |/ /_\\ \\  | |  | |__";
    goToXY(54,i++);
    TextColor(0x0A);
    cout <<   "| | | ||  __/ | | | ||  _  |  | |  |  __|";
    goToXY(54,i++);
    TextColor(0x0A);
    cout <<   "| |_| || |    | |/ / | | | |  | |  | |___ ";
    goToXY(54,i++);
    TextColor(0x0A);
    cout <<   "\\___/ \\_|    |___/  \\_| |_/  \\_/  \\____/ ";
}  


void Render_Account()
{
    goToXY(52, 3);
    TextColor(0x0A);
    cout << "     ___  ______________  __  ___  ________";
    goToXY(52, 4);
    TextColor(0x0D);
    cout << "    / _ |/ ___/ ___/ __ \\/ / / / |/ /_  __/";
    goToXY(52, 5);
    TextColor(0x09);
    cout << "   / __ / /__/ /__/ /_/ / /_/ /    / / /";
    goToXY(52, 6);
    TextColor(0x0C);
    cout << "  /_/ |_\\___/\\___/\\____/\\____/_/|_/ /_/";
    TextColor(7);
}

void Render_NewYear()
{
    goToXY(50, 3);
    cout << "   _____ _____ _ _ _    __ __ _____ _____ _____";
    goToXY(50, 4);
    cout << "  |   | |   __| | | |  |  |  |   __|  _  | __  |";
    goToXY(50, 5);
    cout << "  | | | |   __| | | |  |_   _|   __|     |    -|";
    goToXY(50, 6);
    cout << "  |_|___|_____|_____|    |_| |_____|__|__|__|__|";
}

void Render_Semester()
{
    goToXY(55, 3);
    cout << " ___ ___ __  __ ___ ___ _____ ___ ___";
    goToXY(55, 4);
    cout << "/ __| __|  \\/  | __/ __|_   _| __| _ \\";
    goToXY(55, 5);
    cout << "\\__ \\ _|| |\\/| | _|\\__ \\ | | | _||   /";
    goToXY(55, 6);
    cout << "|___/___|_|  |_|___|___/ |_| |___|_|_\\";
}

void Render_Class()
{
    goToXY(60, 3);
    cout << "  ___ _      _   ___ ___";
    goToXY(60, 4);
    cout << " / __| |    /_\\ / __/ __|";
    goToXY(60, 5);
    cout << "| (__| |__ / _ \\\\__ \\__ \\";
    goToXY(60, 6);
    cout << " \\___|____/_/ \\_\\___/___/";
}

void Render_Student()
{
    goToXY(60, 3);
    cout << " ___  _____ _   _  _ _  ___ _  _  _____";
    goToXY(60, 4);
    cout << "/ __||_   _| | | ||   \\| __| \\| ||_   _|";
    goToXY(60, 5);
    cout << "\\__ \\  | | | |_| || |) | _|| .` |  | |";
    goToXY(60, 6);
    cout << "|___/  |_|  \\___/ |___/|___|_|\\_|  |_|";
}

void Render_View()
{
    int x = 50, y = 3;
    goToXY(x,y++);
    cout << " ____   ____   _____   ________   ____      ____  ";
    goToXY(x,y++);
    cout << "|_  _| |_  _| |_   _| |_   __  | |_  _|    |_  _|";
    goToXY(x,y++);
    cout << "  \\ \\   / /     | |     | |_ \\_|   \\ \\  /\\  / /  ";
    goToXY(x,y++);
    cout << "   \\ \\ / /      | |     |  _| _     \\ \\/  \\/ /";
    goToXY(x,y++);
    cout << "    \\ ' /      _| |_   _| |__/ |     \\  /\\  / ";
    goToXY(x,y++);
    cout << "     \\_/      |_____| |________|      \\/  \\/";


//   ____   ____   _____   ________   ____      ____      ______    _________   _____  _____   ______     ________   ____  _____   _________      ______ _____         _      ______   ______    
//  |_  _| |_  _| |_   _| |_   __  | |_  _|    |_  _|   .' ____ \  |  _   _  | |_   _||_   _| |_   _ `.  |_   __  | |_   \|_   _| |  _   _  |   .' ___  |_   _|       / \   .' ____ \.' ____ \   
//    \ \   / /     | |     | |_ \_|   \ \  /\  / /     | (___ \_| |_/ | | \_|   | |    | |     | | `. \   | |_ \_|   |   \ | |   |_/ | | \_|  / .'   \_| | |        / _ \  | (___ \_| (___ \_|  
//     \ \ / /      | |     |  _| _     \ \/  \/ /       _.____`.      | |       | '    ' |     | |  | |   |  _| _    | |\ \| |       | |      | |        | |   _   / ___ \  _.____`. _.____`.   
//      \ ' /      _| |_   _| |__/ |     \  /\  /       | \____) |    _| |_       \ \__/ /     _| |_.' /  _| |__/ |  _| |_\   |_     _| |_     \ `.___.'\_| |__/ |_/ /   \ \| \____) | \____) |  
//       \_/      |_____| |________|      \/  \/         \______.'   |_____|       `.__.'     |______.'  |________| |_____|\____|   |_____|     `.____ .|________|____| |____\______.'\______.'  
//                                                                                                                                                                                               

}

void Render_StudentClass()
{
    int x = 10, y = 3;
    goToXY(x,y++);
    cout << "  ______    _________   _____  _____   ______     ________   ____  _____   _________           ______   _____           _         ______     ______  ";
    goToXY(x,y++);
    cout << ".' ____ \\  |  _   _  | |_   _||_   _| |_   _ `.  |_   __  | |_   \\|_   _| |  _   _  |        .' ___  | |_   _|         / \\      .' ____ \\  .' ____ \\ ";
    goToXY(x,y++);
    cout << "| (___ \\_| |_/ | | \\_|   | |    | |     | | `. \\   | |_ \\_|   |   \\ | |   |_/ | | \\_|       / .'   \\_|   | |          / _ \\     | (___ \\_| | (___ \\_|";
    goToXY(x,y++);
    cout << " _.____`.      | |       | '    ' |     | |  | |   |  _| _    | |\\ \\| |       | |           | |          | |   _     / ___ \\     _.____`.   _.____`. ";
    goToXY(x,y++);
    cout << "| \\____) |    _| |_       \\ \\__/ /     _| |_.' /  _| |__/ |  _| |_\\   |_     _| |_          \\ `.___.'\\  _| |__/ |  _/ /   \\ \\_  | \\____) | | \\____) |";
    goToXY(x,y++);
    cout << " \\______.'   |_____|       `.__.'     |______.'  |________| |_____|\\____|   |_____|          `.____ .' |________| |____| |____|  \\______.'  \\______.";
}

void Render_StudentCourse() 
{
    int x = 35, y = 1;
    goToXY(x,y++);
    cout << "   ______    _________   _____  _____   ______     ________   ____  _____   _________         ";
    goToXY(x,y++);
    cout << " .' ____ \\  |  _   _  | |_   _||_   _| |_   _ `.  |_   __  | |_   \\|_   _| |  _   _  |      ";
    goToXY(x,y++);
    cout << " | (___ \\_| |_/ | | \\_|   | |    | |     | | `. \\   | |_ \\_|   |   \\ | |   |_/ | | \\_|  ";
    goToXY(x,y++);
    cout << "  _.____`.      | |       | '    ' |     | |  | |   |  _| _    | |\\ \\| |       | |           ";
    goToXY(x,y++);
    cout << " | \\____) |    _| |_       \\ \\__/ /     _| |_.' /  _| |__/ |  _| |_\\   |_     _| |_       ";
    goToXY(x,y++);
    cout << "  \\______.'   |_____|       `.__.'     |______.'  |________| |_____|\\____|   |_____|   ";
    y+=2;
    x= 35;
    goToXY(x,y++);
    cout << "          ______     ___    _____  _____   _______      ______    ________";
    goToXY(x,y++);
    cout << "        .' ___  |  .'   `. |_   _||_   _| |_   __ \\   .' ____ \\  |_   __  |";
    goToXY(x,y++);
    cout << "       / .'   \\_| /  .-.  \\  | |    | |     | |__) |  | (___ \\_|   | |_ \\_|";
    goToXY(x,y++);
    cout << "       | |        | |   | |  | '    ' |     |  __ /    _.____`.    |  _| _  ";
    goToXY(x,y++);
    cout << "       \\ `.___.'  \\  `-'  /   \\ \\__/ /     _| |  \\ \\_ | \\____) |  _| |__/ |";
    goToXY(x,y++);
    cout << "        `.____ .'  `.___.'     `.__.'     |____| |___| \\______.' |________|";
} 

void Render_ScoreBoardCourse() 
{
    int x = 25, y = 1;
    goToXY(x,y++);
    cout << "   ______      ______     ___     _______      ________   ______       ___          _        _______      ______           ";
    goToXY(x,y++);
    cout << " .' ____ \\   .' ___  |  .'   `.  |_   __ \\    |_   __  | |_   _ \\    .'   `.       / \\      |_   __ \\    |_   _ `.    ";
    goToXY(x,y++);
    cout << " | (___ \\_| / .'   \\_| /  .-.  \\   | |__) |     | |_ \\_|   | |_) |  /  .-.  \\     / _ \\       | |__) |     | | `. \\     ";
    goToXY(x,y++);
    cout << "  _.____`.  | |        | |   | |   |  __ /      |  _| _    |  __'.  | |   | |    / ___ \\      |  __ /      | |  | |   ";
    goToXY(x,y++);
    cout << " | \\____) | \\ `.___.'\\ \\  `-'  /  _| |  \\ \\_   _| |__/ |  _| |__) | \\  `-'  /  _/ /   \\ \\_   _| |  \\ \\_   _| |_.' /    ";
    goToXY(x,y++);
    cout << "  \\______.'  `.____ .'  `.___.'  |____| |___| |________| |_______/   `.___.'  |____| |____| |____| |___| |______.'         ";
    y+=2;
    x = 45;
    goToXY(x,y++);
    cout << "    ______     ___     _____  _____   _______       ______    ________    ";
    goToXY(x,y++); 
    cout << "  .' ___  |  .'   `.  |_   _||_   _| |_   __ \\    .' ____ \\  |_   __  |   ";
    goToXY(x,y++);
    cout << " / .'   \\_| /  .-.  \\   | |    | |     | |__) |   | (___ \\_|   | |_ \\_|   ";
    goToXY(x,y++);
    cout << " | |        | |   | |   | '    ' |     |  __ /     _.____`.    |  _| _    ";
    goToXY(x,y++);
    cout << " \\ `.___.'\\ \\  `-'  /    \\ \\__/ /     _| |  \\ \\_  | \\____) |  _| |__/ |   ";
    goToXY(x, y++);
    cout << "  `.____ .'  `.___.'      `.__.'     |____| |___|  \\______.' |________|   ";
}

void Render_ScoreBoardClass() 
{
    int x = 25, y = 1;
    goToXY(x,y++);
    cout << "   ______      ______     ___     _______      ________   ______       ___          _        _______      ______           ";
    goToXY(x,y++);
    cout << " .' ____ \\   .' ___  |  .'   `.  |_   __ \\    |_   __  | |_   _ \\    .'   `.       / \\      |_   __ \\    |_   _ `.    ";
    goToXY(x,y++);
    cout << " | (___ \\_| / .'   \\_| /  .-.  \\   | |__) |     | |_ \\_|   | |_) |  /  .-.  \\     / _ \\       | |__) |     | | `. \\     ";
    goToXY(x,y++);
    cout << "  _.____`.  | |        | |   | |   |  __ /      |  _| _    |  __'.  | |   | |    / ___ \\      |  __ /      | |  | |   ";
    goToXY(x,y++);
    cout << " | \\____) | \\ `.___.'\\ \\  `-'  /  _| |  \\ \\_   _| |__/ |  _| |__) | \\  `-'  /  _/ /   \\ \\_   _| |  \\ \\_   _| |_.' /    ";
    goToXY(x,y++);
    cout << "  \\______.'  `.____ .'  `.___.'  |____| |___| |________| |_______/   `.___.'  |____| |____| |____| |___| |______.'         ";
    y+=2;
    x = 45;
    goToXY(x,y++);
    cout << "    ______   _____           _         ______     ______   ";
    goToXY(x,y++); 
    cout << "  .' ___  | |_   _|         / \\      .' ____ \\  .' ____ \\  ";
    goToXY(x,y++);
    cout << " / .'   \\_|   | |          / _ \\     | (___ \\_| | (___ \\_| ";
    goToXY(x,y++);
    cout << " | |          | |   _     / ___ \\     _.____`.   _.____`.  ";
    goToXY(x,y++);
    cout << " \\ `.___.'\\  _| |__/ |  _/ /   \\ \\_  | \\____) | | \\____) | ";
    goToXY(x, y++);
    cout << "  `.____ .' |________| |____| |____|  \\______.'  \\______.' ";
                                                            

}