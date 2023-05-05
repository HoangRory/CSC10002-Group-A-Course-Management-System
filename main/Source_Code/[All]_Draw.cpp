#include "../Header/Utility.h"
#include <math.h>
int Draw_XY(vector<string> menu, int xStart, int yStart, int nOption_eachTime, int width, int color)
{
    if (nOption_eachTime > menu.size())
        nOption_eachTime = menu.size();
    int amount_page = ceil(menu.size() * 1.0 / nOption_eachTime), num_page = 1, tmp;
    char arrow;
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
        goToXY(xStart, yStart + nOption_eachTime * 3 + 1);
        cout << setw(20) << " ";
        tmp = min((int)(menu.size() - step), nOption_eachTime);

        num_page = ceil((cur + 1) * 1.0 / nOption_eachTime);
        goToXY(xStart, yStart + tmp * 3 + 1);
        if (amount_page > 1)
        {
            cout << "  " << (num_page > 1 ? char(30) : char(32))
                 << " " << num_page << "/" << amount_page
                 << " " << (num_page < amount_page ? char(31) : char(32));
        }
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
    goToXY(xStart, yStart + nOption_eachTime * 3 + 1);
    cout << setw(20) << " ";
    tmp = min((int)(menu.size() - step), nOption_eachTime);
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
        if (i % Col_eachTime == 0)
            pos[i] = 0;
        else
            pos[i] = pos[i - 1] + width[i - 1];
    }

    int x_prev = num_col, y_prev = num_row,
        x_step, y_step,
        num_page_hor, num_page_ver,
        amount_page_hor = ceil(num_col * 1.0 / Col_eachTime), amount_page_ver = ceil(num_row * 1.0 / Row_eachTime);
    bool stop = false;

    x_step = (x_cur / Col_eachTime) * Col_eachTime;
    y_step = (y_cur / Row_eachTime) * Row_eachTime;
    choice[y_cur][x_cur] = 1;
    while (stop != true)
    {
        if (y_prev / Row_eachTime != y_cur / Row_eachTime || x_prev / Col_eachTime != x_cur / Col_eachTime)
        {
            TextColor(7);
            // xóa kẻ đầu tiên
            for (int j = 0; j < Col_eachTime && j + x_step < num_col; j++)
            {
                goToXY(x + pos[j + x_step], y - 1);
                cout << setw(width[j + x_step] + 1) << " ";
            }
            // xóa ô tiêu đề và các ô trước
            for (int i = 0; i <= Row_eachTime && i + y_step <= num_row; i++)
            {
                for (int j = 0; j < Col_eachTime && j + x_step < num_col; j++)
                {

                    goToXY(x + pos[j + x_step], y + i * (height + 1));
                    cout << setw(width[j + x_step] + 1) << " ";
                    goToXY(x + pos[j + x_step], y + i * (height + 1) + 1);
                    cout << setw(width[j + x_step] + 1) << " ";
                }
            }
            goToXY(x, y + 2 + min(Row_eachTime, num_row - y_step) * (height + 1));
            cout << setw(20) << " ";
            x_step = (x_cur / Col_eachTime) * Col_eachTime;
            y_step = (y_cur / Row_eachTime) * Row_eachTime;
            goToXY(x, y - 1);
            cout << char(218); // 218 is top left
            goToXY(x, y);
            cout << char(179);
            goToXY(x, y + 1);
            cout << char(195);
            for (int j = 0; j < Col_eachTime && j + x_step < num_col; j++)
            {
                for (int t = 0; t < width[j + x_step] - 1; t++)
                {
                    goToXY(x + pos[j + x_step] + t + 1, y - 1);
                    cout << char(196);
                    goToXY(x + pos[j + x_step] + t + 1, y + 1);
                    cout << char(196);
                }
                goToXY(x + pos[j + x_step] + 2, y);
                cout << title[j + x_step];
                if (j == Col_eachTime - 1 || j == num_col - x_step - 1)
                {
                    goToXY(x + pos[j + x_step] + width[j + x_step], y - 1);
                    cout << char(191);
                    goToXY(x + pos[j + x_step] + width[j + x_step], y + 1);
                    cout << char(180);
                }
                else
                {
                    goToXY(x + pos[j + x_step] + width[j + x_step], y + -1);
                    cout << char(194);
                    goToXY(x + pos[j + x_step] + width[j + x_step], y + 1);
                    cout << char(197);
                }
                goToXY(x + pos[j + x_step] + width[j + x_step], y);
                cout << char(179);
            }

            y += 2;
            choice[y_cur][x_cur] = 1;
            for (int i = 0; i < Row_eachTime && i + y_step < num_row; i++)
            {
                for (int j = 0; j < Col_eachTime && j + x_step < num_col; j++)
                {
                    goToXY(x + pos[j + x_step] + 1, y + i * (height + 1) + 1);
                    for (int t = 0; t < width[j + x_step] - 1; t++)
                        cout << char(196);
                    goToXY(x + pos[j + x_step], y + i * (height + 1) + 1);
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
                        {
                            cout << char(192); // 192  is|_

                            // đếm số trang cho bảng
                            goToXY(x, y + i * (height + 1) + 2);
                            if (amount_page_hor > 1)
                            {
                                num_page_hor = ceil((x_cur + 1) * 1.0 / Col_eachTime);
                                cout << "  " << (num_page_hor > 1 ? char(17) : char(32))
                                     << " " << num_page_hor << "/" << amount_page_hor
                                     << " " << (num_page_hor < amount_page_hor ? char(16) : char(32));
                            }
                            if (amount_page_ver > 1)
                            {
                                num_page_ver = ceil((y_cur + 1) * 1.0 / Row_eachTime);
                                cout << "  " << (num_page_ver > 1 ? char(30) : char(32))
                                     << " " << num_page_ver << "/" << amount_page_ver
                                     << " " << (num_page_ver < amount_page_ver ? char(31) : char(32));
                            }
                        }
                        else if (j != Col_eachTime - 1 && j != num_col - x_step - 1)
                            cout << char(193); // 193 is _|_
                        // in số trang ở cuối bảng
                    }

                    goToXY(x + pos[j + x_step], y + i * (height + 1));
                    cout << char(179); // 179 is |

                    int tmp = (choice[i + y_step][j + x_step] ? 0xF3 : 7);
                    TextColor(tmp);
                    goToXY(x + 1 + pos[j + x_step], y + i * (height + 1)); // +1 để in background không bị đè
                    cout << setw(width[j + x_step] - 1) << " ";
                    goToXY(x + 2 + pos[j + x_step], y + i * (height + 1)); //+3 là để lùi vào trong một ít cho đẹp
                    cout << table[i + y_step][j + x_step];

                    TextColor(7);
                    goToXY(x + pos[j + x_step] + width[j + x_step], y + i * (height + 1));
                    cout << char(179); // 179 is |
                    goToXY(x + pos[j + x_step] + width[j + x_step], y + i * (height + 1) + 1);
                    if (i == Row_eachTime - 1 || i == num_row - 1 - y_step)
                        cout << char(217); // 217 is _|
                    else
                        cout << char(180); // 180 -|
                }
            }
        }
        else
        {
            y += 2;
            TextColor(7);
            goToXY(x + 1 + pos[x_prev], y + (y_prev % Row_eachTime) * (height + 1));
            cout << setw(width[x_prev] - 1) << " ";
            goToXY(x + 2 + pos[x_prev], y + (y_prev % Row_eachTime) * (height + 1));
            cout << table[y_prev][x_prev];

            TextColor(0xF3);
            goToXY(x + 1 + pos[x_cur], y + (y_cur % Row_eachTime) * (height + 1));
            cout << setw(width[x_cur] - 1) << " ";
            goToXY(x + 2 + pos[x_cur], y + (y_cur % Row_eachTime) * (height + 1));
            cout << table[y_cur][x_cur];
        }

        y -= 2;
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
                choice[y_cur][x_cur] = 0;
                y_cur = (y_cur > 0 ? y_cur - 1 : num_row - 1);
                break;
            case DOWN:
                choice[y_cur][x_cur] = 0;
                y_cur = (y_cur < num_row - 1 ? y_cur + 1 : 0);
                break;
            case LEFT:
                choice[y_cur][x_cur] = 0;
                x_cur = (x_cur > 0 ? x_cur - 1 : num_col - 1);
                break;
            case RIGHT:
                choice[y_cur][x_cur] = 0;
                x_cur = (x_cur < num_col - 1 ? x_cur + 1 : 0);
            }
        }
    }
    for (int i = 0; i < num_row; i++)
        delete[] choice[i];
    delete[] choice;
    delete[] pos;
}
// int Draw_Horizontal_XY(vector<string> menu, int x, int y, int &cur, int color)
// {
//     vector<int> choice(menu.size(), 0);
//     while (1)
//     {
//         choice[cur] = 1;
//         for (int i = 0; i < choice.size(); i++)
//         {
//             for (int j = 0; j < 3; j++)
//             {
//                 int tmp = (choice[i] ? color : 7);
//                 TextColor(tmp);
//                 goToXY(x + 3 * i, y + j);
//                 cout << "   ";
//                 goToXY(x + 1 + 3 * i, y + 1);
//                 cout << menu[i];
//             }
//         }
//         TextColor(07);
//         int tmp;
//         if (tmp = _getch())
//         {
//             switch (tmp)
//             {
//             case ENTER:
//                 system("cls");
//                 return cur;
//             case LEFT:
//                 choice[cur] = 0;
//                 cur = (cur > 0 ? cur - 1 : menu.size() - 1);
//                 break;
//             case RIGHT:
//                 choice[cur] = 0;
//                 cur = (cur < menu.size() - 1 ? cur + 1 : 0);
//                 break;
//             }
//         }
//     }
// }

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
