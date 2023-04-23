#include "../Header/Utility.h"

int Draw_XY(vector<string> menu, int xStart, int yStart, int nOption_eachTime, int width, int color)
{
    if (nOption_eachTime > menu.size())
        nOption_eachTime = menu.size();
    vector<int> choice(menu.size(), 0);
    int cur = 0;
    int step = 0;
    bool stop = false;
    while (!stop)
    {
        if (step < (cur / nOption_eachTime) * nOption_eachTime)
        {
            for (int i = 0; i < nOption_eachTime; i++)
            {
                TextColor(7);
                for (int j = 0; j < 3; j++)
                {
                    goToXY(xStart, yStart + i * 3 + j);
                    cout << setw(width) << " ";
                }
            }
        }
        step = (cur / nOption_eachTime) * nOption_eachTime;
        choice[cur] = 1;
        for (int i = 0; i < nOption_eachTime && i + step < menu.size(); i++)
        {
            int tmp = (choice[i + step] ? color : 7);

            TextColor(tmp);
            for (int j = 0; j < 3; j++)
            {
                goToXY(xStart, yStart + i * 3 + j);
                cout << setw(width) << " ";
            }
            goToXY(xStart + 2, yStart + 1 + i * 3);
            cout << menu[i + step];
        }
        TextColor(07);
        int tmp;
        if (tmp = _getch())
        {
            switch (tmp)
            {
            case ENTER:
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
    for (int i = 0; i < nOption_eachTime; i++)
    {
        TextColor(7);
        for (int j = 0; j < 3; j++)
        {
            goToXY(xStart, yStart + i * 3 + j);
            cout << setw(width) << " ";
        }
    }
    return cur;
}

void Draw_table(string **table, string *title, int num_row, int num_col, int *width, int height,
                int x, int y, int Row_eachTime, int Col_eachTime,
                bool *edit_Col, int &x_cur, int &y_cur)
{
    if (Col_eachTime > num_col)
        Col_eachTime = num_col;
    if (Row_eachTime > num_row)
        Row_eachTime = num_row;
    int **choice = new int *[num_row];
    for (int i = 0; i < num_row; i++)
    {
        choice[i] = new int[num_col];
        for (int j = 0; j < num_col; j++)
            choice[i][j] = 0;
    }
    int *pos = new int[num_col]; // vị trí bắt đầu của các cột, bắt đầu từ cột đầu là 0
    pos[0] = 0;
    for (int i = 1; i < num_col; i++)
    {
        pos[i] = pos[i - 1] + width[i - 1];
    }

    int x_prev = x_cur, y_prev = y_cur;
    int x_step;
    int y_step;
    bool stop = false;

    x_step = (x_cur / Col_eachTime) * Col_eachTime;
    y_step = (y_cur / Row_eachTime) * Row_eachTime;
    choice[y_cur % Row_eachTime][x_cur % Col_eachTime] = 1;
    goToXY(x, y - 1);
    cout << char(218); // 218 is top left
    goToXY(x, y);
    cout << char(179);
    goToXY(x, y + 1);
    cout << char(195);
    for (int j = 0; j < Col_eachTime && j + x_step < num_col; j++)
    {
        for (int t = 0; t < width[j] - 1; t++)
        {
            goToXY(x + pos[j] + t + 1, y - 1);
            cout << char(196);
            goToXY(x + pos[j] + t + 1, y + 1);
            cout << char(196);
        }
        goToXY(x + pos[j] + 2, y);
        cout << title[j];
        if (j == Col_eachTime - 1 || j == num_col - x_step - 1)
        {
            goToXY(x + pos[j] + width[j], y - 1);
            cout << char(191);
            goToXY(x + pos[j] + width[j], y + 1);
            cout << char(180);
        }
        else
        {
            goToXY(x + pos[j] + width[j], y + -1);
            cout << char(194);
            goToXY(x + pos[j] + width[j], y + 1);
            cout << char(197);
        }
        goToXY(x + pos[j] + width[j], y);
        cout << char(179);
    }
    y += 2;

    for (int i = 0; i < Row_eachTime && i + y_step < num_row; i++)
    {
        for (int j = 0; j < Col_eachTime && j + x_step < num_col; j++)
        {
            goToXY(x + pos[j] + 1, y + i * (height + 1) + 1);
            for (int t = 0; t < width[j] - 1; t++)
                cout << char(196);
            goToXY(x + pos[j], y + i * (height + 1) + 1);
            if (i != Row_eachTime - 1 && i != num_row - 1 - y_step)
            {
                if (j == 0)
                    cout << char(195); // 195  is|-
                else
                    cout << char(197); // 197 is +
            }
            else
            {
                if (j == 0)
                    cout << char(192); // 192  is|_
                else if (j != Col_eachTime - 1 && j != num_col - x_step - 1)
                    cout << char(193); // 193 is _|_
            }

            goToXY(x + pos[j], y + i * (height + 1));
            cout << char(179);                            // 179 is |
            goToXY(x + 1 + pos[j], y + i * (height + 1)); // +1 để in background không bị đè

            int tmp = (choice[i][j] ? 0xF3 : 7);
            TextColor(tmp);
            cout << setw(width[j] - 1) << " ";
            goToXY(x + 2 + pos[j], y + i * (height + 1)); //+2 là để lùi vào trong một ít cho đẹp
            cout << table[i + y_step][j + x_step];

            TextColor(7);
            goToXY(x + pos[j] + width[j], y + i * (height + 1));
            cout << char(179); // 179 is |
            goToXY(x + pos[j] + width[j], y + i * (height + 1) + 1);
            if (i == Row_eachTime - 1 || i == num_row - 1 - y_step)
                cout << char(217); // 217 is _|
            else
                cout << char(180); // 180 -|
        }
    }
    while (stop != true)
    {
        if ((x_prev / Col_eachTime) != (x_cur / Col_eachTime) || (y_prev / Row_eachTime) != (y_cur / Row_eachTime))
        {
            TextColor(7);
            for (int i = 0; i < Row_eachTime && i + y_step < num_row; i++)
            {
                for (int j = 0; j < Col_eachTime && j + x_step < num_col; j++)
                {
                    goToXY(x + pos[j], y + i * (height + 1));
                    cout << setw(width[j] + 1) << " ";
                    goToXY(x + pos[j], y + i * (height + 1) + 1);
                    cout << setw(width[j] + 1) << " ";
                }
            }
            x_step = (x_cur / Col_eachTime) * Col_eachTime;
            y_step = (y_cur / Row_eachTime) * Row_eachTime;
            choice[y_cur % Row_eachTime][x_cur % Col_eachTime] = 1;
            for (int i = 0; i < Row_eachTime && i + y_step < num_row; i++)
            {
                for (int j = 0; j < Col_eachTime && j + x_step < num_col; j++)
                {
                    goToXY(x + pos[j] + 1, y + i * (height + 1) + 1);
                    for (int t = 0; t < width[j] - 1; t++)
                        cout << char(196);
                    goToXY(x + pos[j], y + i * (height + 1) + 1);
                    if (i != Row_eachTime - 1 && i != num_row - 1 - y_step)
                    {
                        if (j == 0)
                            cout << char(195); // 195  is|-
                        else
                            cout << char(197); // 197 is +
                    }
                    else
                    {
                        if (j == 0)
                            cout << char(192); // 192  is|_
                        else if (j != Col_eachTime - 1 && j != num_col - x_step - 1)
                            cout << char(193); // 193 is _|_
                    }

                    goToXY(x + pos[j], y + i * (height + 1));
                    cout << char(179);                            // 179 is |
                    goToXY(x + 1 + pos[j], y + i * (height + 1)); // +1 để in background không bị đè

                    int tmp = (choice[i][j] ? 0xF3 : 7);
                    TextColor(tmp);
                    cout << setw(width[j] - 1) << " ";
                    goToXY(x + 2 + pos[j], y + i * (height + 1)); //+3 là để lùi vào trong một ít cho đẹp
                    cout << table[i + y_step][j + x_step];

                    TextColor(7);
                    goToXY(x + pos[j] + width[j], y + i * (height + 1));
                    cout << char(179); // 179 is |
                    goToXY(x + pos[j] + width[j], y + i * (height + 1) + 1);
                    if (i == Row_eachTime - 1 || i == num_row - 1 - y_step)
                        cout << char(217); // 217 is _|
                    else
                        cout << char(180); // 180 -|
                }
            }
        }
        else
        {

            TextColor(7);
            goToXY(x + 1 + pos[x_prev % Col_eachTime], y + (y_prev % Row_eachTime) * (height + 1));
            cout << setw(width[x_prev % Col_eachTime] - 1) << " ";
            goToXY(x + 2 + pos[x_prev % Col_eachTime], y + (y_prev % Row_eachTime) * (height + 1));
            cout << table[y_prev % Row_eachTime + y_step][x_prev % Col_eachTime + x_step];

            TextColor(0xF3);
            goToXY(x + 1 + pos[x_cur % Col_eachTime], y + (y_cur % Row_eachTime) * (height + 1));
            cout << setw(width[x_cur % Col_eachTime] - 1) << " ";
            goToXY(x + 2 + pos[x_cur % Col_eachTime], y + (y_cur % Row_eachTime) * (height + 1));
            cout << table[y_cur % Row_eachTime + y_step][x_cur % Col_eachTime + x_step];
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
                if (edit_Col[x_cur] == false)
                    Message_Warning("This cell is not editable", "Error!");
                else
                    stop = true;
                break;
            case UP:
                choice[y_cur % Row_eachTime][x_cur % Col_eachTime] = 0;
                y_cur = (y_cur > 0 ? y_cur - 1 : num_row - 1);
                break;
            case DOWN:
                choice[y_cur % Row_eachTime][x_cur % Col_eachTime] = 0;
                y_cur = (y_cur < num_row - 1 ? y_cur + 1 : 0);
                break;
            case LEFT:
                choice[y_cur % Row_eachTime][x_cur % Col_eachTime] = 0;
                x_cur = (x_cur > 0 ? x_cur - 1 : num_col - 1);
                break;
            case RIGHT:
                choice[y_cur % Row_eachTime][x_cur % Col_eachTime] = 0;
                x_cur = (x_cur < num_col - 1 ? x_cur + 1 : 0);
            }
        }
    }
    for (int i = 0; i < num_row; i++)
        delete[] choice[i];
    delete[] choice;
    delete[] pos;
}
int Draw_Horizontal_XY(vector<string> menu, int x, int y, int &cur, int color)
{
    vector<int> choice(menu.size(), 0);
    while (1)
    {
        choice[cur] = 1;
        for (int i = 0; i < choice.size(); i++)
        {
            for (int j = 0; j < 3; j++)
            {
                int tmp = (choice[i] ? color : 7);
                TextColor(tmp);
                goToXY(x + 3 * i, y + j);
                cout << "   ";
                goToXY(x + 1 + 3 * i, y + 1);
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
    while (1)
    {
        choice[cur] = 1;
        for (int i = 0; i < choice.size(); i++)
        {
            int tmp = (choice[i] ? color : 7);

            TextColor(tmp);
            goToXY(x, y + i);
            cout << "                         ";
            goToXY(x + 2, y + i);
            cout << menu[i];
        }
        TextColor(07);
        int tmp;
        if (tmp = _getch())
        {
            switch (tmp)
            {
            case ENTER:
                system("cls");
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
