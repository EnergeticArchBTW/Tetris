#include <iostream>
#include <windows.h>
#include <conio.h>
#include "Tetris.h"
using namespace std;
string tlo[25]; /// zapisuje miedzy innymi spadniete klocki oraz ogolnie cala mape
short color[25][44];
int punkty = 0;
// void Peace::clear_frame(/*int &x,int &y,int &rotation,string &form*/);
// bool fit(int &x,int &y,int &rotation,string &form);

void changecol(int numofcol) /// funkcja ktora upraszcza zmiane koloru czcionki w konsoli
{
    HANDLE hwyj;
    hwyj = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hwyj, numofcol);
}

void create()
{
    system("cls");
    punkty = 0;
    /// resetowanie kolorow
    for (int y = 0; y < 25; y++)
    {
        for (int x = 0; x < 44; x++)
            color[y][x] = 7;
    }
    /// resetowanie mapy
    for (int i = 0; i < 22; i++)
        tlo[i] = "  #                                      #  "; ///-30
    tlo[22] = "  ########################################  ";
    tlo[23] = "                                            ";
    tlo[24] = "                                            ";
    for (int i = 0; i < 25; i++)
        cout << tlo[i] << endl;
    gotoxy(50, 4);
    cout << "Next:"; /// pisze "Next:" nad obiektem, ktory bedzie nastepny
    // cout<<tlo[24];
}
void gotoxy(int x, int y)
{
    COORD c;
    c.X = x - 1;
    c.Y = y - 1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void disapear(int x, int y) /// na razie ta funkcja jest niepotrzebna
{
    for (int yy = 0; yy < 4; yy++)
    {
        for (int xx = 0; xx < 4; xx++)
        {
            tlo[y + yy][x + xx] = ' ';
            gotoxy(x + xx + 1, y + yy + 1);
            cout << " ";
        }
    }
}

/// konstruktory, destruktory, metody i funkcje zaprzyjaznione klasy Peace
ostream &operator<<(ostream &os, const Peace x)
{
    x.show();
    return os;
}
Peace::Peace(int xx, int yy, int c_nr_form, int c_rotation, string c_form, int c_fuse_count, short c_color)
{
    x = xx;
    y = yy;
    fuse_count = c_fuse_count;
    nr_form = c_nr_form;
    rotation = c_rotation;
    fuse_y = 0;
    Color = c_color;
    /// ksztalty klockow do dyspozycji:
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

Peace::~Peace() /// przed zniszczeniem obiektu...
{
    /// licznik punktow
    if (x <= 40)
    {
        for (int yy = 0; yy < 4; yy++) /// za kazda literke upadnieta na ziemie: 100 pkt
        {
            for (int xx = 0; xx < 4; xx++)
            {
                if (tlo[y + yy + 1][x + xx] == '#' && form[i(xx, yy, rotation)] != ' ')
                    punkty += 10;
            }
        }
        for (int yy = 0; yy < 4; yy++) /// za kazda literke upadnieta na inny spadniety obiekt: 10 pkt
        {
            for (int xx = 0; xx < 4; xx++)
            {
                if (tlo[y + yy + 1][x + xx] != '#' && tlo[y + yy + 1][x + xx] != ' ' && form[i(xx, yy, rotation)] != ' ')
                    punkty += 1;
            }
        }
    }

    /// stawianie klocka na mapie
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
    /*for(int yy=0;yy<y+3;yy++)
    {
        for(int xx=0;xx<?;xx++)
        {

        }
    }*/
    int filled = 0; /// ile literek jest wypelnionych na danej linii
    if (x <= 40)
    {
        for (int yy = 0; yy < 4; yy++)
        {
            for (int xx = 0; xx < 38; xx++)
            {
                if (tlo[y + yy][3 + xx] != ' ' && tlo[y + yy][3 + xx] != '#')
                    filled++;
            }
            /// jezeli cala linia jest wypelniona literkami...
            if (filled == 38)
            {
                /*bo kordynaty gotoxy sie liczy od jednego*/ gotoxy(4, y + yy + 1);
                cout << "--------------------------------------"; /// cout ma tyle myslnikow dlatego, bo tyle ma linia gdzie mozna wstawic
                Sleep(500);
                punkty += 100;
                /// przez linijke opadniecie gornej czesci mapy
                for (int n = y + yy; n > 1; n--)
                    tlo[n] = tlo[n - 1];
                /// takze opadaja kolory
                for (int yyy = y + yy; yyy > 1; yyy--)
                {
                    for (int xxx = 0; xxx < 44; xxx++)
                        color[yyy][xxx] = color[yyy - 1][xxx];
                }
                /// najwyzsza linijka mapy sie resetuje
                for (int xxx = 0; xxx < 44; xxx++)
                    color[0][xxx] = 7;
                tlo[0] = "  #                                      #  ";
                /// wyswietlenie zaktualizowanej mapy
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
    /// wszystkie czworki to szerokosc obiektu
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
    }
}

void Peace::P_move()
{
    clear_frame(/*x,y,rotation,form*/);
    int key = 0;
    fuse_y++;
    /*if(fuse_y==5) ///odliczanie do kolejnego przemieszczenia sie w dol
    {
    fuse_y=0; y++;
    }*/
    if (fuse_y >= fuse_count)
    {
        fuse_y = 0;
        y++;
    }
    if (kbhit())
        key = getch();
    if (key == 32)
        fuse_count = 1; /// jezeli kliknieto spacje, to wlaczamy turbo-spadanie

    if (key == 97 && fit(x - 1, rotation)) /// przycisk a wcisniety..
        x--;
    if (key == 100 && fit(/*x,y,rotation,form)*/ x + 1, rotation)) /// przycisk d wcisniety...
        x++;
    if (key == 107 && fit(x, rotation - 1)) /// przycisk k wcisniety...
        rotation--;
    if (key == 108 && fit(x, rotation + 1)) /// przycisk l wcisniety...
        rotation++;
    // gotoxy(2,1); cout<<rotation;
    if (rotation == 5)
        rotation = 1;
    if (rotation == 0)
        rotation = 4;
    gotoxy(1, 1); // cout<<fit(/*x,y,rotation,form*/x,rotation);
    // gotoxy(2,1); cout<<on_ground();
}

bool Peace::on_ground()
{
    for (int yy = 0; yy < 4; yy++)
    {
        for (int xx = 0; xx < 4; xx++) // n jest jako xx
        {
            // gotoxy(2,1); cout<<tlo[y+yy+1][x+n];
            // gotoxy(1,2); cout<<form[i(n,yy,rotation)];
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

bool Peace::fit(/*int &x,int &y,int &rotation,string &form*/ int xxx, int r)
{
    const int w = 4;
    // int xx=0;
    if (r == 5)
        r = 1;
    if (r == 0)
        r = 4;
    for (int yy = 0; yy < 4; yy++)
    {
        /*switch(rotation)
        {
            case 1: if(form[yy*w+3]==' ' && tlo[yy+y][3+x]==' ') xx++; break;
            case 2: if(form[12+yy-(3*w)]==' ' && tlo[yy+y][3+x]==' ') xx++; break;
            case 3: if(form[15-(yy*w)-3]==' ' && tlo[yy+y][3+x]==' ') xx++; break;
            case 4: if(form[3-yy+(3*w)]==' ' && tlo[yy+y][3+x]==' ') xx++; break;
        }*/
        for (int xx = 0; xx < 4; xx++)
        {
            if (form[i(xx, yy, r)] != ' ' && tlo[yy + y][xx + xxx] != ' ')
                return false;
        }
    }
    return true;
    /*if(xx%4==0 && xx!=0)
    return true;
    else return false;*/
}

void Peace::clear_frame(/*int &x,int &y,int &rotation,string &form*/)
{
    const int w = 4;
    for (int yy = 0; yy < 4; yy++)
    {
        for (int xx = 0; xx < 4; xx++)
        {
            /*if(tlo[y+yy][x+xx]==' ')*/ if (/*tlo[yy+y][xx+x]!=' ' &&*/ form[i(xx, yy, rotation)] != ' ')
            {
                /*switch(rotation)
                {
                case 1: if(form[yy*w+xx]!=' ')
                gotoxy(x+xx+1,y+yy+1); cout<<" "; break;
                case 2: if(form[12+yy-(xx*w)]!=' ')
                gotoxy(x+xx+1,y+yy+1); cout<<" "; break;
                case 3: if(form[15-(yy*w)-xx]!=' ')
                gotoxy(x+xx+1,y+yy+1); cout<<" "; break;
                case 4: if(form[3-yy+(xx*w)]!=' ')
                gotoxy(x+xx+1,y+yy+1); cout<<" "; break;
                }*/
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
    for (int yy = 0; yy < 4; yy++)
    {
        for (int xx = 0; xx < 4; xx++)
        {
            if (/*(rotation==1 && form[yy*w+xx]!=' ') || (rotation==2 &&
                form[12+yy-(xx*w)]!=' ') || (rotation==3 && form[15-(yy*w)-xx]!=' ') ||
                (rotation==4 && form[3-yy+(xx*w)]!=' ')*/
                form[i(xx, yy, rotation)] != ' ' /*&& tlo[yy+y][xx+x]==' ' (nie wiadomo czy to jest niezbedne)*/)
            {
                gotoxy(x + xx + 1, y + yy + 1);
                /* if(rotation==1) ///jezeli 0 stopni...
                 cout<<form[yy*w+xx];
                 if(rotation==2) ///jezeli 90 stopni...
                 cout<<form[12+yy-(xx*w)];
                 if(rotation==3) ///jezeli 180 stopni...
                 cout<<form[15-(yy*w)-xx];
                 if(rotation==4) ///jezeli 270 stopni...
                 cout<<form[3-yy+(xx*w)]; */
                changecol(Color);
                cout << form[i(xx, yy, rotation)];
            }
        }
    }
    changecol(7);
    Sleep(100);
}
