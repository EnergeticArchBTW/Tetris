#include <iostream>
using namespace std;
void create();
void gotoxy(int, int);
class Peace // definicja typu obiektu pelniaca role klocka w tetrisie
{
    string form;    // ksztalt
    short Color;    // zapisuje kolor klocka
    int nr_form;    // wersja obiektu
    int fuse_y;     // ilosc czekania do przemieszczenia obiektu w dol (aktualna ilosc czekania)
    int fuse_count; // ile obiekt musi czekac co kazde spadniecie
    int rotation;   // rotacja obiektu
    int x, y;       // kordynaty
public:
    int i(int, int, int) const;
    bool on_ground();
    void clear_frame(/*int &x,int &y,int &rotation,string &form*/);
    bool fit(/*int &x,int &y,int &rotation,string &form*/ int, int);
    bool game_over();
    Peace() = delete; // usuwamy domyslny konstruktor
    Peace(int = 40, int = 1, int = 0, int = 1, string = "                ", int = 5, short = 7);
    ~Peace();
    void P_move();
    void show() const;
    friend ostream &operator<<(ostream &os, const Peace x);
};
