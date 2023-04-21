#include "../Header/Utility.h"

int Draw_XY(vector<string> menu, int xStart, int yStart, int nOption_eachTime, int width, int color)
{
    if(nOption_eachTime > menu.size()) 
        nOption_eachTime = menu.size();
    vector<int> choice(menu.size(), 0);
    int cur = 0;
    int step = 0;
    bool stop = false;
    ShowConsoleCursor(0);
    while (!stop)
    {
        if(step < (cur/nOption_eachTime) * nOption_eachTime){
            for( int i= 0; i < nOption_eachTime; i++) {
                TextColor(7);
                for (int j = 0; j < 3; j++)
                {
                    goToXY(xStart, yStart + i * 3 + j);
                    cout << setw(width) << " ";
                }
            }
        }
        step = (cur/nOption_eachTime) * nOption_eachTime;
        choice[cur] = 1;
        for (int i = 0; i < nOption_eachTime && i + step < menu.size(); i++)
        {
            if (choice[i+step])
            {
                TextColor(color);
                for (int j = 0; j < 3; j++)
                {
                    goToXY(xStart, yStart + i * 3 + j);
                    cout << setw(width) << " ";
                }
                goToXY(xStart + 2, yStart + 1 + i * 3);
                TextColor(color);
                cout << menu[i + step];
            }
            else
            {
                TextColor(7);
                for (int j = 0; j < 3; j++)
                {
                    goToXY(xStart, yStart + i * 3 + j);
                    cout << setw(width) << " ";
                }
                goToXY(xStart + 2, yStart + 1 + i * 3);
                TextColor(7);
                cout << menu[i+ step];
            }
        }
        TextColor(07);
        int tmp;
        if (tmp = _getch())
        {
            switch (tmp)
            {
            case ENTER:
                ShowConsoleCursor(1);
                stop = true;
                break;
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
    for( int i= 0; i < nOption_eachTime; i++) {
        TextColor(7);
        for (int j = 0; j < 3; j++)
        {
            goToXY(xStart, yStart + i * 3 + j);
            cout << setw(width) << " ";
        }
    }
    return cur;
}

int Draw_table
(    string **table,int num_row, int num_col, int width[], int pos[], int height,
    int x, int y, int Row_eachTime, int Col_eachTime, int always_show,
    bool edit_Col[], int &x_cur, int &y_cur         )
{

    if(Col_eachTime > num_col) 
        Col_eachTime = num_col;
    if(Row_eachTime > num_row) 
        Row_eachTime = num_row;
    int **choice = new int* [num_row];
    for(int i = 0; i < num_row; i++){
        choice[i] = new int [num_col];
        for(int j = 0; j < num_col; j++)
            choice[i][j] = 0;
    }

    int x_prev = x_cur, y_prev = y_cur;
    int x_step;
    int y_step;
    ShowConsoleCursor(0);
    bool stop = false;

    x_step = (x_cur/Col_eachTime) * Col_eachTime;
    y_step = (y_cur/Row_eachTime) * Row_eachTime;
    choice[y_cur%Row_eachTime][x_cur%Col_eachTime] = 1;
    for (int i = 0; i < Row_eachTime && i + y_step < num_row; i++)
    {
        for(int j = 0; j < Col_eachTime && j + x_step < num_col; j++)
        {
            if (choice[i][j])
            {
                goToXY(x + pos[j], y + i * height);
                TextColor(0xFF);
                cout << setw(width[j]) << " ";
                goToXY(x + 2 + pos[j], y + i * height);
                TextColor(0xF3);
                cout << table[i + y_step][j + x_step];
            }
            else
            {
                TextColor(7);
                goToXY(x + pos[j], y + i * height);
                cout << setw(width[j]) << " ";

                goToXY(x + 2 + pos[j], y + i * height);
                TextColor(7);
                cout << table[i + y_step][j + x_step];
            }
        }
    }

    while (stop != true)
    {
        if((x_prev/Col_eachTime) != (x_cur/Col_eachTime) || (y_prev/Row_eachTime) != (y_cur/Row_eachTime) ) {
            for (int i = 0; i < Row_eachTime && i + y_step < num_row; i++)
            {
                for(int j = 0; j < Col_eachTime && j + x_step < num_col; j++)
                {
                    TextColor(7);
                    goToXY(x + pos[j], y + i * height);
                    cout << setw(width[j]) << " ";
                }
            }
            x_step = (x_cur/Col_eachTime) * Col_eachTime;
            y_step = (y_cur/Row_eachTime) * Row_eachTime;
            choice[y_cur%Row_eachTime][x_cur%Col_eachTime] = 1;
            for (int i = 0; i < Row_eachTime && i + y_step < num_row; i++)
            {
                for(int j = 0; j < Col_eachTime && j + x_step < num_col; j++)
                {
                    if (choice[i][j])
                    {
                        TextColor(0xFF);
                        goToXY(x + pos[j], y + i * height);
                        cout << setw(width[j]) << " ";
                        goToXY(x + 2 + pos[j], y + i * height);
                        TextColor(0xF3);
                        cout << table[i + y_step][j + x_step];
                    }
                    else
                    {
                        TextColor(7);
                        goToXY(x + pos[j], y + i * height);
                        cout << setw(width[j]) << " ";

                        goToXY(x + 2 + pos[j], y + i * height);
                        TextColor(7);
                        cout << table[i + y_step][j + x_step];
                    }
                }
            }
        }
        else {

            TextColor(7);
            goToXY(x + pos[x_prev%Col_eachTime], y + (y_prev%Row_eachTime) * height);
            cout << setw(width[x_prev%Col_eachTime]) << " ";
            TextColor(7);
            goToXY(x + 2 + pos[x_prev%Col_eachTime], y + (y_prev%Row_eachTime) * height);
            cout << table[y_prev%Row_eachTime + y_step][x_prev%Col_eachTime + x_step];

            TextColor(0xFF);
            goToXY(x + pos[x_cur%Col_eachTime], y + (y_cur%Row_eachTime) * height);
            cout << setw(width[x_cur%Col_eachTime]) << " ";
            TextColor(0xF3);
            goToXY(x + 2 + pos[x_cur%Col_eachTime], y + (y_cur%Row_eachTime) * height);
            cout << table[y_cur%Row_eachTime + y_step][x_cur%Col_eachTime + x_step];
        }
        
        x_prev = x_cur;
        y_prev = y_cur;
        TextColor(7);
        int tmp;
        if (tmp = _getch())
        {
            switch (tmp)
            {
            case 27:
                x_cur = -1;
                y_cur = -1;
                stop = true;
                break;
            case ENTER:
                ShowConsoleCursor(1);
                if(edit_Col[x_cur] == false)
                    Message_Warning("This cell is not editable", "Error!");
                else
                    stop = true;
                break;
            case UP:
                choice[y_cur%Row_eachTime][x_cur%Col_eachTime] = 0;
                y_cur = (y_cur > 0 ? y_cur - 1 : num_row - 1);
                break;
            case DOWN:
                choice[y_cur%Row_eachTime][x_cur%Col_eachTime] = 0;
                y_cur = (y_cur < num_row - 1 ? y_cur + 1 : 0);
                break;
            case LEFT:
                choice[y_cur%Row_eachTime][x_cur%Col_eachTime] = 0;
                x_cur = (x_cur > 0 ? x_cur - 1 : num_col - 1);
                break;
            case RIGHT:
                choice[y_cur%Row_eachTime][x_cur%Col_eachTime] = 0;
                x_cur = (x_cur < num_col - 1 ? x_cur + 1 : 0);
            }
        }
    }  
    for(int i = 0; i < num_row; i++)
        delete []choice[i];
    delete choice;
}
int Draw_Horizontal_XY(vector<string> menu, int x , int y, int &cur, int color)
{
    vector<int> choice(menu.size(), 0);
    ShowConsoleCursor(0);
    while (1)
    {
        choice[cur] = 1;
        for (int i = 0; i < choice.size(); i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (choice[i])
                {
                    TextColor(color);
                    goToXY(x + 3 * i, y + j);
                    cout << "   ";
                    goToXY(x + 1 + 3 * i, y + 1);
                    TextColor(color);
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

int Draw_ShortVer(vector<string> menu, int x, int y, int color)
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
                TextColor(color);
                goToXY(x, y + i);
                cout << "                         ";
                goToXY(x + 2, y + i);
                TextColor(color);
                cout << menu[i];
            }
            else
            {
                TextColor(7);
                goToXY(x, y + i);
                cout << "                         ";
                goToXY(x + 2, y + i);
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
    goToXY(54, i++);
    TextColor(0x0A);
    cout << " _   _  _____ ______   ___   _____  _____ ";
    goToXY(54, i++);
    TextColor(0x0A);
    cout << "| | | || ___ \\|  _  \\ / _ \\ |_   _||  ___|";
    goToXY(54, i++);
    TextColor(0x0A);
    cout << "| | | || |_/ /| | | |/ /_\\ \\  | |  | |__";
    goToXY(54, i++);
    TextColor(0x0A);
    cout << "| | | ||  __/ | | | ||  _  |  | |  |  __|";
    goToXY(54, i++);
    TextColor(0x0A);
    cout << "| |_| || |    | |/ / | | | |  | |  | |___ ";
    goToXY(54, i++);
    TextColor(0x0A);
    cout << "\\___/ \\_|    |___/  \\_| |_/  \\_/  \\____/ ";
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

void Render_Class(int x, int y)
{
    goToXY(x,y++);
    cout << "   ______   _____           _         ______     ______  ";
    goToXY(x,y++);
    cout << " .' ___  | |_   _|         / \\      .' ____ \\  .' ____ \\ ";
    goToXY(x,y++);
    cout << "/ .'   \\_|   | |          / _ \\     | (___ \\_| | (___ \\_|";
    goToXY(x,y++);
    cout << "| |          | |   _     / ___ \\     _.____`.   _.____`. ";
    goToXY(x,y++);
    cout << "\\ `.___.'\\  _| |__/ |  _/ /   \\ \\_  | \\____) | | \\____) |";
    goToXY(x,y++);
    cout << " `.____ .' |________| |____| |____|  \\______.'  \\______.";
}
void Render_Course(int x, int y)
{
    goToXY(x,y++);
    cout << "   ______     ___    _____  _____   _______      ______    ________";
    goToXY(x,y++);
    cout << " .' ___  |  .'   `. |_   _||_   _| |_   __ \\   .' ____ \\  |_   __  |";
    goToXY(x,y++);
    cout << "/ .'   \\_| /  .-.  \\  | |    | |     | |__) |  | (___ \\_|   | |_ \\_|";
    goToXY(x,y++);
    cout << "| |        | |   | |  | '    ' |     |  __ /    _.____`.    |  _| _  ";
    goToXY(x,y++);
    cout << "\\ `.___.'  \\  `-'  /   \\ \\__/ /     _| |  \\ \\_ | \\____) |  _| |__/ |";
    goToXY(x,y++);
    cout << " `.____ .'  `.___.'     `.__.'     |____| |___| \\______.' |________|";
}

void Render_Student(int x, int y)
{
    goToXY(x,y++);
    cout << "  ______    _________   _____  _____   ______     ________   ____  _____   _________        ";
    goToXY(x,y++);
    cout << ".' ____ \\  |  _   _  | |_   _||_   _| |_   _ `.  |_   __  | |_   \\|_   _| |  _   _  |      ";
    goToXY(x,y++);
    cout << "| (___ \\_| |_/ | | \\_|   | |    | |     | | `. \\   | |_ \\_|   |   \\ | |   |_/ | | \\_| ";
    goToXY(x,y++);
    cout << " _.____`.      | |       | '    ' |     | |  | |   |  _| _    | |\\ \\| |       | |         ";
    goToXY(x,y++);
    cout << "| \\____) |    _| |_       \\ \\__/ /     _| |_.' /  _| |__/ |  _| |_\\   |_     _| |_      ";
    goToXY(x,y++);
    cout << " \\______.'   |_____|       `.__.'     |______.'  |________| |_____|\\____|   |_____|       ";
}

void Render_View()
{
    int x = 50, y = 3;
    goToXY(x, y++);
    cout << " ____   ____   _____   ________   ____      ____  ";
    goToXY(x, y++);
    cout << "|_  _| |_  _| |_   _| |_   __  | |_  _|    |_  _|";
    goToXY(x, y++);
    cout << "  \\ \\   / /     | |     | |_ \\_|   \\ \\  /\\  / /  ";
    goToXY(x, y++);
    cout << "   \\ \\ / /      | |     |  _| _     \\ \\/  \\/ /";
    goToXY(x, y++);
    cout << "    \\ ' /      _| |_   _| |__/ |     \\  /\\  / ";
    goToXY(x,y++);
    cout << "     \\_/      |_____| |________|      \\/  \\/";                                                                                                                                                                                          
}



void Render_StudentCourse()
{
    int x = 30, y = 1;
    Render_Student(x,y);
    y = 7;
    x= 35;
    Render_Course(x,y);
} 

void Render_ScoreBoard(int x, int y)
{
    goToXY(x,y++);
    cout << "   ______      ______     ___     _______      ________   ______       ___          _        _______      ______           ";
    goToXY(x, y++);
    cout << " .' ____ \\   .' ___  |  .'   `.  |_   __ \\    |_   __  | |_   _ \\    .'   `.       / \\      |_   __ \\    |_   _ `.    ";
    goToXY(x, y++);
    cout << " | (___ \\_| / .'   \\_| /  .-.  \\   | |__) |     | |_ \\_|   | |_) |  /  .-.  \\     / _ \\       | |__) |     | | `. \\     ";
    goToXY(x, y++);
    cout << "  _.____`.  | |        | |   | |   |  __ /      |  _| _    |  __'.  | |   | |    / ___ \\      |  __ /      | |  | |   ";
    goToXY(x, y++);
    cout << " | \\____) | \\ `.___.'\\ \\  `-'  /  _| |  \\ \\_   _| |__/ |  _| |__) | \\  `-'  /  _/ /   \\ \\_   _| |  \\ \\_   _| |_.' /    ";
    goToXY(x, y++);
    cout << "  \\______.'  `.____ .'  `.___.'  |____| |___| |________| |_______/   `.___.'  |____| |____| |____| |___| |______.'         ";
}
void Render_Update(int x, int y)
{
    goToXY(x,y++);
    cout << "  _____  _____   _______    ______          _        _________   ________  ";
    goToXY(x,y++);
    cout << " |_   _||_   _| |_   __ \\  |_   _ `.       / \\      |  _   _  | |_   __  | ";
    goToXY(x,y++);
    cout << "   | |    | |     | |__) |   | | `. \\     / _ \\     |_/ | | \\_|   | |_ \\_| ";
    goToXY(x,y++);
    cout << "   | '    ' |     |  ___/    | |  | |    / ___ \\        | |       |  _| _  ";
    goToXY(x,y++);
    cout << "    \\ \\__/ /     _| |_      _| |_.' /  _/ /   \\ \\_     _| |_     _| |__/ | ";
    goToXY(x,y++);
    cout << "     `.__.'     |_____|    |______.'  |____| |____|   |_____|   |________| ";
}
void Render_Export(int x, int y) 
{
    goToXY(x,y++);
    cout << "  ________   ____  ____   _______      ___     _______      _________  ";
    goToXY(x,y++);
    cout << " |_   __  | |_  _||_  _| |_   __ \\   .'   `.  |_   __ \\    |  _   _  | ";
    goToXY(x,y++);
    cout << "   | |_ \\_|   \\ \\  / /     | |__) | /  .-.  \\   | |__) |   |_/ | | \\_| ";
    goToXY(x,y++);
    cout << "   |  _| _     > `' <      |  ___/  | |   | |   |  __ /        | |     ";
    goToXY(x,y++);
    cout << "  _| |__/ |  _/ /'`\\ \\_   _| |_     \\  `-'  /  _| |  \\ \\_     _| |_    ";
    goToXY(x,y++);
    cout << " |________| |____||____| |_____|     `.___.'  |____| |___|   |_____|   ";
}
void Render_Import(int x, int y) 
{
    goToXY(x,y++);
    cout << "  _____   ____    ____   _______      ___     _______      _________  ";
    goToXY(x,y++);
    cout << " |_   _| |_   \\  /   _| |_   __ \\   .'   `.  |_   __ \\    |  _   _  | ";
    goToXY(x,y++);
    cout << "   | |     |   \\/   |     | |__) | /  .-.  \\   | |__) |   |_/ | | \\_| ";
    goToXY(x,y++);
    cout << "   | |     | |\\  /| |     |  ___/  | |   | |   |  __ /        | |     ";
    goToXY(x,y++);
    cout << "  _| |_   _| |_\\/_| |_   _| |_     \\  `-'  /  _| |  \\ \\_     _| |_    ";
    goToXY(x,y++);
    cout << " |_____| |_____||_____| |_____|     `.___.'  |____| |___|   |_____|   ";
}
void Render_ScoreBoardCourse() 
{
    int x = 25, y = 1;
    Render_ScoreBoard(x,y);
    y = 7;
    x = 45;
    Render_Course(x,y);
}

void Render_ScoreBoardClass()
{
    int x = 25, y = 1;
    Render_ScoreBoard(x,y);
    x = 45; y = 7;
    Render_Class(x,y);                                                         

}

void Render_StudentClass()
{
    int x = 30, y = 1;
    Render_Student(x,y);
    x = 40; y = 7;
    Render_Class(x,y);
}