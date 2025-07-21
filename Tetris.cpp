#include <iostream>
#include <windows.h>
#include <conio.h>
#include "Tetris.h"

using namespace std;

// zapisuje miedzy innymi spadniete klocki oraz ogolnie cala mape linia po linii
string tlo[25];
//jaki kolor ma każde miejsce na mapie
short color[25][44];
//ilość zdobytych punktów
int punkty = 0;

void changecol(int numofcol) // funkcja ktora upraszcza zmiane koloru czcionki w konsoli
{
    HANDLE hwyj;
    hwyj = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hwyj, numofcol);
}

//ustawia kursor na konkretnej współrzędnej w konsoli
void gotoxy(int x, int y)
{
    COORD c;
    c.X = x - 1;
    c.Y = y - 1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

//resetowanie globalnych zmiennych przed następną rozgrywką i rysowanie planszy
void create()
{
    system("cls");
    punkty = 0;
    // resetowanie kolorow
    for (int y = 0; y < 25; y++)
    {
        for (int x = 0; x < 44; x++)
            color[y][x] = 7;
    }
    // resetowanie mapy
    for (int i = 0; i < 22; i++)
        tlo[i] = "  #                                      #  "; ///-30
    tlo[22] = "  ########################################  ";
    tlo[23] = "                                            ";
    tlo[24] = "                                            ";
    for (int i = 0; i < 25; i++)
        cout << tlo[i] << endl;
    gotoxy(50, 4);
    cout << "Next:"; // pisze "Next:" nad obiektem, ktory bedzie nastepny
}

// konstruktory, destruktory, metody i funkcje zaprzyjaznione klasy Peace
ostream &operator<<(ostream &os, const Peace x)
{
    x.show();
    return os;
}

Peace::Peace(int xx, int yy, int c_nr_form, int c_rotation, int c_fuse_count, short c_color, string c_form)
{
    x = xx;
    y = yy;
    fuse_count = c_fuse_count;
    nr_form = c_nr_form;
    rotation = c_rotation;
    fuse_y = 0;
    Color = c_color;
    /*
    ksztalty klockow do dyspozycji (max szerokość 4 max wysokość: 4):
    np. [ ][ ][C][ ] (0-3)
        [ ][ ][C][ ] (4-7)
        [ ][ ][C][ ] (8-11)
        [ ][ ][C][ ] (12-15)*/
    switch (c_nr_form)
    {
    case 1:
        form = "  X   X  XXX    ";
        break;
    case 2:
        form = "  C   C   C   C ";
        break;
    case 3:
        form = "     DD  DD     ";
        break;
    case 4:
        form = "  S  SS  S      ";
        break;
    case 5:
        form = " H   H   HH     ";
        break;
    case 6:
        form = "MMM M M         ";
        break;
    case 7:
        form = " K  KKK  K      ";
        break;
    case 8:
        form = " NN  NN   N     ";
        break;
    case 9:
        form = "T   TT   TT   TT";
        break;
    case 10:
        form = " GG  GG  G      ";
        break;
    case 11:
        form = "     V   VV     ";
        break;
    case 12:
        form = "QQQ Q Q Q Q     ";
        break;
    case 13:
        form = "  R   RR   R    ";
        break;
    case 14:
        form = "ZZZZZ  Z        ";
        break;
    case 15:
        form = "YYYYY  YY  Y    ";
        break;
    case 16:
        form = " U   U  UU      ";
        break;
    default:
        form = c_form;
    }
}

Peace::~Peace()
{
    // licznik punktow
    if (x <= 40)
    {
        for (int yy = 0; yy < 4; yy++) // za kazda literke upadnieta na ziemie: 10 pkt
        {
            for (int xx = 0; xx < 4; xx++)
            {
                if (tlo[y + yy + 1][x + xx] == '#' && form[i(xx, yy, rotation)] != ' ')
                    punkty += 10;
            }
        }
        for (int yy = 0; yy < 4; yy++) // za kazda literke upadnieta na inny spadniety obiekt: 1 pkt
        {
            for (int xx = 0; xx < 4; xx++)
            {
                if (tlo[y + yy + 1][x + xx] != '#' && tlo[y + yy + 1][x + xx] != ' ' && form[i(xx, yy, rotation)] != ' ')
                    punkty += 1;
            }
        }
    }

    // stawianie klocka na mapie
    for (int yy = 0; yy < 4; yy++)
    {
        for (int xx = 0; xx < 4; xx++)
        {
            if (tlo[y + yy][x + xx] == ' ')
            { /*zapisywanie koloru klocka na mapie*/
                color[y + yy][x + xx] = Color;
                tlo[y + yy][x + xx] = form[i(xx, yy, rotation)];
            }
        }
    }

    int filled = 0; // ile literek jest wypelnionych na danej linii
    if (x <= 40)
    {
        for (int yy = 0; yy < 4; yy++)
        {
            for (int xx = 0; xx < 38; xx++)
            {
                if (tlo[y + yy][3 + xx] != ' ' && tlo[y + yy][3 + xx] != '#')
                    filled++;
            }
            // jezeli cala linia jest wypelniona literkami... dajemy 100 pkt
            if (filled == 38)
            {
                /*bo kordynaty gotoxy sie liczy od jednego*/ gotoxy(4, y + yy + 1);
                cout << "--------------------------------------"; // cout ma tyle myslnikow dlatego, bo tyle ma linia gdzie mozna wstawic
                Sleep(500);
                punkty += 100;
                // przez linijke opadniecie gornej czesci mapy
                for (int n = y + yy; n > 1; n--)
                    tlo[n] = tlo[n - 1];
                // takze opadaja kolory
                for (int yyy = y + yy; yyy > 1; yyy--)
                {
                    for (int xxx = 0; xxx < 44; xxx++)
                        color[yyy][xxx] = color[yyy - 1][xxx];
                }
                // najwyzsza linijka mapy sie resetuje
                for (int xxx = 0; xxx < 44; xxx++)
                    color[0][xxx] = 7;
                tlo[0] = "  #                                      #  ";
                // wyswietlenie zaktualizowanej mapy
                for (int yyy = 0; yyy < 25; yyy++)
                {
                    for (int xx = 0; xx < 44; xx++)
                    {
                        gotoxy(xx + 1, yyy + 1);
                        changecol(color[yyy][xx]);
                        cout << tlo[yyy][xx];
                    }
                }
            }
            filled = 0;
        }
    }
    changecol(7);
}

int Peace::i(int xx, int yy, int r) const
{
    // wszystkie czworki to szerokosc obiektu
    switch (r)
    {
    case 1:
        return yy * 4 + xx;
    case 2:
        return 12 + yy - (xx * 4);
    case 3:
        return 15 - (yy * 4) - xx;
    case 4:
        return 3 - yy + (xx * 4);
    default:
        return -1;
    }
}

void Peace::P_move()
{
    clear_frame();
    int key = 0;
    fuse_y++;
    if (fuse_y >= fuse_count)
    {
        fuse_y = 0;
        y++;
    }
    if (kbhit())
        key = getch();
    if (key == 32)
        fuse_count = 1; // jezeli kliknieto spacje, to wlaczamy turbo-spadanie

    if (key == 97 && fit(x - 1, rotation)) // przycisk a wcisniety..
        x--;
    if (key == 100 && fit(x + 1, rotation)) // przycisk d wcisniety...
        x++;
    if (key == 107 && fit(x, rotation - 1)) // przycisk k wcisniety...
        rotation--;
    if (key == 108 && fit(x, rotation + 1)) // przycisk l wcisniety...
        rotation++;

    if (rotation == 5)
        rotation = 1;
    if (rotation == 0)
        rotation = 4;
    gotoxy(1, 1);
}

bool Peace::on_ground()
{
    for (int yy = 0; yy < 4; yy++)
    {
        for (int xx = 0; xx < 4; xx++) // n jest jako xx
        {
            if (form[i(xx, yy, rotation)] != ' ' && tlo[y + yy + 1][x + xx] != ' ')
                return true;
        }
    }
    return false;
}

bool Peace::game_over()
{
    for (int yy = 0; yy < 4; yy++)
    {
        for (int xx = 0; xx < 4; xx++)
        {
            if (form[i(xx, yy, rotation)] != ' ' && tlo[y + yy][x + xx] != ' ')
                return true;
        }
    }
    return false;
}

bool Peace::fit(int xxx, int r)
{
    const int w = 4;
    if (r == 5)
        r = 1;
    if (r == 0)
        r = 4;
    for (int yy = 0; yy < w; yy++)
    {
        for (int xx = 0; xx < w; xx++)
        {
            if (form[i(xx, yy, r)] != ' ' && tlo[yy + y][xx + xxx] != ' ')
                return false;
        }
    }
    return true;
}

void Peace::clear_frame()
{
    const int w = 4;
    for (int yy = 0; yy < w; yy++)
    {
        for (int xx = 0; xx < w; xx++)
        {
            if (form[i(xx, yy, rotation)] != ' ')
            {
                if (form[i(xx, yy, rotation)] != ' ')
                {
                    gotoxy(x + xx + 1, y + yy + 1);
                    cout << " ";
                }
            }
        }
    }
}

void Peace::show() const
{
    const int w = 4;
    for (int yy = 0; yy < w; yy++)
    {
        for (int xx = 0; xx < w; xx++)
        {
            if (form[i(xx, yy, rotation)] != ' ')
            {
                gotoxy(x + xx + 1, y + yy + 1);
                changecol(Color);
                cout << form[i(xx, yy, rotation)];
            }
        }
    }
    changecol(7);
    Sleep(100);
}
