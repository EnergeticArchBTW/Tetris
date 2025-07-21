#include <iostream>
#include <cstdlib>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include "Tetris.h"
using namespace std;
// kształt
int random_form = 5,
    // szybkość spadania
    random_fall = 8,
    // kolor
    random_color = 15;
extern int punkty;
Peace *p1;
// obiekt pokazujacy jaka forma bedzie nastepna
Peace *p2 = new Peace(50, 5, random_form, 1, random_fall, random_color);
void menu();

int main()
{
  //ustawienie polskiego kodowania
  SetConsoleOutputCP(65001);

  menu();
  create();
  srand(time(NULL)); // pobieramy losowa liczbe (ale dokladniej, ile uplynelo czasu od 1970)
  while (1)
  {
    p2->clear_frame();
    delete p2;
    gotoxy(50, 20);
    cout << "Punkty: " << punkty;
    p1 = new Peace(21, 1, random_form, 1, random_fall, random_color);
    // losowanie ksztaltu
    random_form = rand() % 16 + 1; // odpowiednia losowa liczbe otrzymujemy z wyciagniecia reszty tej liczby i dodania 1
    // losowanie szybkosci spadania
    random_fall = rand() % 6 + 5 + 1;
    // losowanie koloru
    random_color = rand() % 7 + 8 + 1;

    p2 = new Peace(50, 5, random_form, 1, random_fall, random_color);
    p2->show();
    while (1)
    {
      if (p1->game_over())
      {
        delete p1;
        delete p2;
        gotoxy(57, 12);
        cout << "Game Over !!!";
        Sleep(10000);
        menu();
        delete p2;
        create();
        p2 = new Peace(50, 5, random_form, 1, random_fall, random_color);
        break;
      }
      p1->P_move();
      p1->show();
      if (p1->on_ground() == true)
      {
        delete p1;
        break;
      }
    }
  }
  return 0;
}

// pisanie głównego menu
void main_menu()
{
  // pisanie tytulu gry
  gotoxy(35, 3);
  cout << "* TETRIS *";
  gotoxy(35, 12);
  cout << "start";
  gotoxy(35, 16);
  cout << "sterowanie";
}

void menu()
{
  // option to na jakiej opcji aktualnie jest wskaźnik
  // a key przechowuje wartość o wciśniętym przycisku
  int option, key;
  // czyszczenie zawartości całej konsoli
  system("cls");

  p2 = new Peace(60, 12, random_form, 1);
  main_menu();

  while (true)
  {
    p2->clear_frame();
    delete p2;
    random_form = rand() % 16 + 1;
    p2 = new Peace(60, 12, random_form, 1);
    cout << *p2;
    if (kbhit())
    {
      key = getch();
      // przestawianie wskaznika opcji
      if (key == 115)
        option -= 1;
      if (key == 119)
        option += 1;
      if (option > 1)
        option = 0;
      if (option < 0)
        option = 1;
      if (option == 0)
      {
        gotoxy(33, 16);
        cout << "  ";
        gotoxy(33, 12);
        cout << "->";
      }
      if (option == 1)
      {
        gotoxy(33, 12);
        cout << "  ";
        gotoxy(33, 16);
        cout << "->";
      }
      Sleep(20);
      // jezeli opcja jest ustawiona na start i wybrana
      if (key == 13 && option == 0)
        break;

      // jeżeli opcja jest ustawiona na sterowanie i wybrana
      if (key == 13 && option == 1)
      {
        system("cls");

        // rysowanie instrukcji jak się steruje
        gotoxy(25, 10);
        cout << "By przesuwać klocek w prawo lub lewo, trzeba kliknąć na klawiaturze A lub D";

        gotoxy(25, 12);
        cout << "By obrócić klocek w prawo, naciśnij L, a kiedy chcesz w prawo, to K";

        gotoxy(25, 14);
        cout << "By klocek zaczął szybciej spadać, to naciśnij spację";

        gotoxy(33, 18);
        cout << "<Kliknij ENTER by powrócić do głównego Menu>";

        while (true)
        {
          key = getch();
          if (key == 13)
          {
            system("cls");
            main_menu();
            break;
          }
        }
      }
    }
  }
}
