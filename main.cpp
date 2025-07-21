#include <iostream>
#include <cstdlib>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include "Tetris.h"
using namespace std;
int random_form=5,random_fall=8,random_color=15;
extern int punkty;
Peace *p1 /*= new Peace(40,1,10,4,"   X          a    ")*/;
Peace *p2 = new Peace(50,5,random_form,1,"                ",random_fall,random_color); ///obiekt pokazujacy jaka forma bedzie nastepna
void menu();
//void gotoxy(int x, int y);
int main()
{
    menu();
    create();
    //p2->show();
    //Peace p1(40,1,10,4,"   X          a    ");
    srand(time(NULL)); ///pobieramy losowa liczbe (ale dokladniej, ile uplynelo czasu od 1970)
    while(1)
    {
        p2->clear_frame();
        delete p2;
        gotoxy(50,20); cout << "Punktyy: " << punkty;
        p1= new Peace(21,1,random_form,1,"                   ",random_fall,random_color);
    ///losowanie ksztaltu
    random_form=rand()%16+1; ///odpowiednia losowa liczbe otrzymujemy z wyciagniecia reszty tej liczby i dodania 1
    ///losowanie szybkosci spadania
    random_fall=rand()%6+5+1;
    ///losowanie koloru
    random_color=rand()%7+8+1;

    p2 = new Peace(50,5,random_form,1,"                ",random_fall,random_color);
    p2->show();
      while(1)
      {
         if(p1->game_over()) {delete p1; delete p2; gotoxy(57,12); cout<<"Game Over !!!"; Sleep(10000);
         menu(); delete p2; create(); p2 = new Peace(50,5,random_form,1,"                ",random_fall,random_color);
         break;}
         p1->P_move();
         p1->show();
         if(p1->on_ground()==true) {delete p1; break;}
      }
      //if(p1->game_over()) {delete p1; return 0;}
    }
    return 0;
}

void menu()
{
    int option, key;
    system("cls");
    ///pisanie tytulu gry
    gotoxy(35,3); cout<<"* TETRIS *";
    gotoxy(35,12); cout<<"start";
    gotoxy(35,16); cout<<"tabela rekordow";
    p2 = new Peace(60,12,random_form,1);
    while(1)
    {
      p2->clear_frame();
      delete p2;
      random_form=rand()%16+1;
      p2 = new Peace(60,12,random_form,1);
      cout << *p2;
      if(kbhit())
      {
        key=0;
        key=getch();
        ///przestawianie wskaznika opcji
        if(key==115) option-=1;
        if(key==119) option+=1;
        if(option>1) option=0;
        if(option<0) option=1;
        if(option==0) {gotoxy(33,16); cout<<"  "; gotoxy(33,12); cout<<"->";} //gotoxy(40,10);
        if(option==1) {gotoxy(33,12); cout<<"  "; gotoxy(33,16); cout<<"->";} //gotoxy(50,14);
        Sleep(20);
        ///jezeli opcja jest ustawiona na start i wybrana
        if(key==13 && option==0) break;
      }
    }
    //delete p2;
}

/*void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}*/
