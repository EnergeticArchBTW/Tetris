#include <iostream>
using namespace std;
void create();
void gotoxy(int, int);
class Peace // definicja typu obiektu pelniaca role klocka w tetrisie
{
    string form;    // ksztalt
    /* zapisuje kolor klocka
       0 - czarny
       1 - niebieski
       2 - zielony
       3 - błękitny
       4 - czerwony
       5 - purpurowy
       6 - żółty
       7 - biały
       8 - szary
       9 - jasnoniebieski
       10 - jasnozielony
       11 - jasnobłękitny
       12 - jasnoczerwony
       13 - jasnopurpurowy
       14 - jasnożółty
       15 - jaskrawobiały */
    short Color;
    int nr_form;    // wersja obiektu
    int fuse_y;     // ilosc czekania do przemieszczenia obiektu w dol (aktualna ilosc czekania)
    int fuse_count; // ile obiekt musi czekac co kazde spadniecie
    int rotation;   // rotacja obiektu
    int x, y;       // kordynaty
public:
    /*zwraca index atrybutu form, który spełnia
    podane współrzędne i uwzględnia dodatkowo
    rotację obiektu. domyślnie, gdy nic nie znajdzie
    zwraca -1
    */
    int i(int, int, int) const;

    //sprawdza, czy klocek nie dotknął gruntu
    bool on_ground();

    // znikanie obiektu z konsoli
    void clear_frame();

    /* sprawdza, czy się zmieści na danym x i danej rotacji
    podanych w argumentach */
    bool fit(int, int);

    //sprawdza, czy gra się skończyła
    bool game_over();

    // usuwamy domyslny konstruktor
    Peace() = delete;

    /* współrzędne x, y, wersja obiektu, jaka rotacja, fuse_count, kolor, form */
    Peace(int = 40, int = 1, int = 0, int = 1, int = 5, short = 7, string = "                ");

    // przed zniszczeniem obiektu...
    ~Peace();

    //usuwa obiekt i go wirtualnie przemieszcza, ale nie pokazuje z powrotem
    void P_move();

    // napisanie na ekran klocka
    void show() const;

    // używanie Peace::show() w bardziej przystępny sposób
    friend ostream &operator<<(ostream &os, const Peace x);
};
