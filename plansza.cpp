#include <iostream>
#include <cstdlib>
#include <Windows.h>
#include "plansza.h"

using namespace std;


Plansza :: ~Plansza()
{

    //usuwanie uzytych tablic
    for (int i = 0; i < rozmiar_planszy; ++i)
        delete[] wolne_pola[i];

    delete[] tablica_pion;
    delete[] tablica_poziom;
}

//zlicza punkty komputera i gracza
void Plansza::rozlicz_punkty(double pkt_komp, double pkt_usr)
{
    punkty_usr = pkt_usr + punkty_usr;
    punkty_komp = pkt_komp + punkty_komp;
}

//okresla znaki graczy i definiuje tablice wykorzystywane w czasie gry
void Plansza::okresl_kto_kim(char komputer, char user, int rozmiar, int ile_do_wygranej, int wielk_pola_kw)
{
    pionek_komp = komputer;
    pionek_usr = user;
    rozmiar_planszy = rozmiar;
    ile_pionkow_do_wygranej = ile_do_wygranej;
    indeks_ostatniego_elementu = -1;
    wielkosc_pola = wielk_pola_kw;
    
    if (rozmiar < 5)
        MAX_glebokosc_rekurencji = 4;

    else if (rozmiar == 5 && ile_do_wygranej == 5)
        MAX_glebokosc_rekurencji = 4;

    else if (rozmiar == 5 && ile_do_wygranej != 5)
        MAX_glebokosc_rekurencji = 6;

    //tablica 2d kazde pole - czy wolne (true) czy zajete (false) 
    wolne_pola = new bool* [rozmiar_planszy];
    for (int i = 0; i < rozmiar_planszy; ++i) {
        wolne_pola[i] = new bool[rozmiar_planszy];
    }

    //tablica wykorzystana do okreslenia remisu
    tablica_pion = new bool[rozmiar_planszy];
    tablica_poziom = new bool[rozmiar_planszy];
    
}

//wynik
void Plansza::wyswietl_wynik()
{
    std::cout << "Wynik: user (" << pionek_usr << ")" << " " << punkty_usr << std::endl;
    std::cout << "Wynik: komputer (" << pionek_komp << ")" << " " << punkty_komp << std::endl;
    std::cout << "Rozmiar planszy: " << rozmiar_planszy << 'x' << rozmiar_planszy << std::endl;
    std::cout << "Wymagana ilosc elementow do wygranej: " << ile_pionkow_do_wygranej << std::endl;
    std::cout << "Rozmiar pola kwadratowego: " << wielkosc_pola << std::endl;
}


//tworzenie planszy, wypelnanie tablic
void Plansza::inicjuj_plansze(char** plansza)
{
    for (int i = 0; i < rozmiar_planszy; ++i)
    {
        for (int j = 0; j < rozmiar_planszy; ++j)
        {
            plansza[i][j] = ' ';
        }
    }

    for (int i = 0; i < rozmiar_planszy; ++i)
    {
        for (int j = 0; j < rozmiar_planszy; ++j)
        {
            wolne_pola[i][j] = true;
        }
    }

    for (int i = 0; i < rozmiar_planszy; ++i)
        tablica_pion[i] = true;

    for (int i = 0; i < rozmiar_planszy; ++i)
        tablica_poziom[i] = true;
}

void Plansza::wyswietl_plansze(char** plansza)
{
    for (int k = 0; k < rozmiar_planszy*wielkosc_pola; ++k)
        std::cout << "******";

    for (int k = 0; k < rozmiar_planszy * 2;++k)
        std::cout << "*";
    
    std::cout << std::endl;

    for (int i = 0; i < rozmiar_planszy; ++i)
    {


        for (int j = 0; j < rozmiar_planszy; ++j)
        {

            for (int licznik_spacji = 0; licznik_spacji < wielkosc_pola * 3; ++licznik_spacji)
                std::cout << " ";

            std::cout << plansza[i][j];

            for (int licznik_spacji = 0; licznik_spacji < wielkosc_pola * 3 ; ++licznik_spacji)
                std::cout << " ";

            std::cout << "|";

            if (j == rozmiar_planszy - 1)
            {
                std::cout << std::endl;

                for (int k = 0; k < rozmiar_planszy*wielkosc_pola; ++k)
                    std::cout << "******";

                for (int k = 0; k < rozmiar_planszy * 2;++k)
                    std::cout << "*";

                std::cout << std::endl;
            }
        }
    }
}

void Plansza::wyswietl_instrukcje()
{
    int licznik_w = 0;
    int licznik_k = 0;

    std::cout << "INSTRUKCJA GRY: " << std::endl;
    for (int k = 0; k < rozmiar_planszy; ++k)
        std::cout << "******";
    std::cout << "*";
    std::cout << std::endl;
    for (int i = 0; i < rozmiar_planszy; ++i)
    {
        std::cout << "|  ";
        for (int j = 0; j < rozmiar_planszy; ++j)
        {
            std::cout << licznik_w << licznik_k << " |  ";
            licznik_k = licznik_k + 1;
            if (j == rozmiar_planszy - 1)
            {
                std::cout << std::endl;
                for (int k = 0; k < rozmiar_planszy; ++k)
                    std::cout << "******";
                std::cout << "*";
                std::cout << std::endl;
                licznik_w = licznik_w + 1;
                licznik_k = 0;
            }
        }
    }
}

void Plansza::ruch_user(char** plansza)
{
    int i, j;

    int flaga_a = 0;

    while (flaga_a == 0)
    {
        std::cout << "Podaj wspolrzedne, gdzie chcesz sie ruszyc: " << std::endl;
        std::cout << "Rzad: ";
        std::cin >> i;
        std::cout << "Kolumna: ";
        std::cin >> j;


        if (i >= 0 && i < rozmiar_planszy && j >= 0 && j < rozmiar_planszy && wolne_pola[i][j] == true && cin.good())
        {
            plansza[i][j] = pionek_usr;
            wolne_pola[i][j] = false;
            flaga_a = 1;
        }
        else
        {
            cin.clear();
            cin.ignore();
            std::cout << "Tam pionka nie postawisz !" << std::endl;
        }
    }
}

//remis
bool Plansza::czy_plansza_pelna(char** plansza)
{
    for (int i = 0; i < rozmiar_planszy; ++i)
    {
        for (int j = 0; j < rozmiar_planszy; ++j)
        {
            if (plansza[i][j] == ' ')
            {
                return false;
            }
        }
    }
    return true;
}

//remis 2
bool Plansza::brak_wygranej_poziom(char** plansza)
{


    for (int i = 0; i < rozmiar_planszy; ++i)
    {
        //flagi a - w rzedzie jest pionek gracza
        int flaga_a = 0;
        //b - w rzedzie pionek komputera
        int flaga_b = 0;
        for (int j = 0; j < rozmiar_planszy; ++j)
        {
            if (plansza[i][j] == pionek_usr && flaga_b != 1)
                flaga_a = 1;

            if (plansza[i][j] == pionek_komp && flaga_a != 1)
                flaga_b = 1;

            if (plansza[i][j] == pionek_usr && flaga_b == 1)
            {
                tablica_poziom[i] = false;
                //brak mozliwosci wyranej w rzedzie i
            }

            if (plansza[i][j] == pionek_komp && flaga_a == 1)
            {
                tablica_poziom[i] = false;
                //tak samo brak mozliwosci wygranej w i
            }

        }
    }
    return true;
}


//remis 3
bool Plansza::brak_wygranej_pion(char** plansza)
{


    for (int j = 0; j < rozmiar_planszy; ++j)
    {
        //analogicznie flagi a - pionek gracza, b - komputera
        int flaga_a = 0;
        int flaga_b = 0;
        for (int i = 0; i < rozmiar_planszy; ++i)
        {
            if (plansza[i][j] == pionek_usr && flaga_b != 1)
                flaga_a = 1;

            if (plansza[i][j] == pionek_komp && flaga_a != 1)
                flaga_b = 1;

            if (plansza[i][j] == pionek_usr && flaga_b == 1)
            {
                tablica_pion[j] = false;
                //brak mozliwosci wygranej w kolumnie j
            }

            if (plansza[i][j] == pionek_komp && flaga_a == 1)
            {
                tablica_pion[j] = false;
                //brak mozliowsci wygranej w j
            }

        }
    }
    return true;
}


//czy jest mozliowsc wygranej w dowolnej kolumnie dla gracza czy komputetra
bool Plansza::remis_pion(char** plansza)
{
    brak_wygranej_pion(plansza);
    for (int i = 0; i < rozmiar_planszy; ++i)
    {
        if (tablica_pion[i] == true)
            return false;
    }
    return true;
}

//czy jest mozliowsc wygranej w dowolnym rzedzie dla gracza czy komputetra
bool Plansza::remis_poziom(char** plansza)
{
    brak_wygranej_poziom(plansza);
    for (int i = 0; i < rozmiar_planszy; ++i)
    {
        if (tablica_poziom[i] == true)
            return false;
    }
    return true;
}

//zlicza pionki zawodnika w kolumnie - min 2 i nie ma pionkow przeciwnika
int Plansza::zlicz_x_pion(char** plansza)
{
    int suma = 0;
    int flaga_b = 0;
    for (int j = 0; j < rozmiar_planszy; ++j)
    {
        flaga_b = 0;
        int ilosc_x = 0;
        for (int i = 0; i < rozmiar_planszy; ++i)
        {
            if (plansza[i][j] == pionek_usr)
                ilosc_x = ilosc_x + 1;

            if (plansza[i][j] == pionek_komp)
                flaga_b = 1;
        }
        if (ilosc_x >= 2 && flaga_b != 1)
            suma = suma + ilosc_x;
    }
    return suma;
}

//zlicza pionki gracza w rzedzie - min 2 i nie ma pionkow przeciwnika
int Plansza::zlicz_x_poziom(char** plansza)
{
    int suma = 0;
    for (int i = 0; i < rozmiar_planszy; ++i)
    {
        int flaga_b = 0;
        int ilosc_x = 0;
        for (int j = 0; j < rozmiar_planszy; ++j)
        {
            if (plansza[i][j] == pionek_usr)
                ilosc_x = ilosc_x + 1;

            if (plansza[i][j] == pionek_komp)
                flaga_b = 1;
        }
        if (ilosc_x >= 2 && flaga_b != 1)
            suma = suma + ilosc_x;
    }
    return suma;
}

//analogicznie dla komputera
int Plansza::zlicz_o_pion(char** plansza)
{
    int suma = 0;
    int flaga_b = 0;
    for (int j = 0; j < rozmiar_planszy; ++j)
    {
        flaga_b = 0;
        int ilosc_o = 0;
        for (int i = 0; i < rozmiar_planszy; ++i)
        {
            if (plansza[i][j] == pionek_komp)
                ilosc_o = ilosc_o + 1;

            if (plansza[i][j] == pionek_usr)
                flaga_b = 1;
        }
        if (ilosc_o >= 2 && flaga_b != 1)
            suma = suma + ilosc_o;
    }
    return suma;
}
int Plansza::zlicz_o_poziom(char** plansza)
{
    int suma = 0;
    for (int i = 0; i < rozmiar_planszy; ++i)
    {
        int flaga_b = 0;
        int ilosc_o = 0;
        for (int j = 0; j < rozmiar_planszy; ++j)
        {
            if (plansza[i][j] == pionek_komp)
                ilosc_o = ilosc_o + 1;

            if (plansza[i][j] == pionek_usr)
                flaga_b = 1;

        }
        if (ilosc_o >= 2 && flaga_b != 1)
            suma = suma + ilosc_o;
    }

    return suma;
}


int Plansza::zlicz_o_ukos_1(char** plansza)
{
    int suma = 0;
    int flaga_b = 0;
    int ilosc_o = 0;

    for (int j = 0; j < rozmiar_planszy; ++j)
    {
        if (plansza[j][j] == pionek_komp)
            ilosc_o = ilosc_o + 1;

        if (plansza[j][j] == pionek_usr)
            flaga_b = 1;
    }

    if (flaga_b != 1 && ilosc_o >= 2)
        return ilosc_o;

    else
        return 0;
}


int Plansza::zlicz_o_ukos_2(char** plansza)
{
    int licznik = 0;
    int suma = 0;
    int flaga_b = 0;
    int ilosc_o = 0;

    for (int j = rozmiar_planszy - 1; j >= 0; --j)
    {
        if (plansza[licznik][j] == pionek_komp)
            ilosc_o = ilosc_o + 1;

        if (plansza[licznik][j] == pionek_usr)
            flaga_b = 1;

        licznik = licznik + 1;
    }

    if (flaga_b != 1 && ilosc_o >= 2)
        return ilosc_o;

    else
        return 0;
}


bool Plansza::sprawdz_czy_wygrana_pion(char** plansza, int i)
{
    //sprawdzanie wygranej pion
    int licznik = 0;
    for (int j = 1; j < rozmiar_planszy; ++j)
    {
            if (plansza[j - 1][i] == plansza[j][i] && plansza[j - 1][i] != ' ')
            {
                if (licznik == 0)
                    licznik = licznik + 2;

                else if (licznik != 0)
                    licznik = licznik + 1;

                if (licznik == ile_pionkow_do_wygranej)
                {
                    indeks_ostatniego_elementu = j;
                    return true;
                }
            }
            else
                licznik = 0;
    }
    
    
     return false;
}

bool Plansza::sprawdz_czy_wygrana_poziom(char** plansza, int i)
{
    //sprawdzanie wygranej poziom 
    int licznik = 0;
    for (int j = 1; j < rozmiar_planszy; ++j)
    {
           if (plansza[i][j - 1] == plansza[i][j] && plansza[i][j] != ' ')
            {
               if (licznik == 0)
                   licznik = licznik + 2;

               else if (licznik != 0)
                   licznik = licznik + 1;

               if (licznik == ile_pionkow_do_wygranej)
               {
                   indeks_ostatniego_elementu = j;
                   return true;
               }

            }
            else
                licznik = 0;

    }
    
     return false;
}

bool Plansza::sprawdz_czy_wygrana_skos_1(char** plansza)
{
    //sprawdzanie wygranej skos
    int licznik = 0;
    for (int j = 1; j < rozmiar_planszy; ++j)
    {
            if (plansza[j - 1][j - 1] == plansza[j][j] && plansza[j - 1][j - 1] != ' ')
            {
                if (licznik == 0)
                    licznik = licznik + 2;

                else if (licznik != 0)
                    licznik = licznik + 1;

                if (licznik == ile_pionkow_do_wygranej)
                {
                    indeks_ostatniego_elementu = j;
                    return true;
                }


            }
            else
                licznik = 0;
    }
    
    return false;
}

bool Plansza::sprawdz_czy_wygrana_skos_2(char** plansza)
{
    //sprawdzanie wygranej - skos
    int licznik = 0;
    int licznik_do_wygranej = 0;

    for (int j = rozmiar_planszy - 1; j >= 0; --j)
    {
        if (j < rozmiar_planszy - 1 && licznik > 0) 
        {

            if (plansza[j + 1][licznik - 1] == plansza[j][licznik] && plansza[j + 1][licznik - 1] != ' ')
            {
                if (licznik_do_wygranej == 0)
                    licznik_do_wygranej = licznik_do_wygranej + 2;

                else if (licznik_do_wygranej != 0)
                    licznik_do_wygranej = licznik_do_wygranej + 1;

                if (licznik_do_wygranej == ile_pionkow_do_wygranej)
                {
                    indeks_ostatniego_elementu = j;
                    return true;
                }
            }
            else
                licznik_do_wygranej = 0;
        }

            licznik = licznik + 1;
    }

    return false;
}

int Plansza::czy_wygrana(char** plansza)
{
    //sprawdzanie wygranej 
    //poziom
    for (int i = 0; i < rozmiar_planszy; ++i)
    {
        if (sprawdz_czy_wygrana_poziom(plansza, i))
        {
            if (plansza[i][indeks_ostatniego_elementu] == pionek_komp)
            {
                return 10;
            }

            if (plansza[i][indeks_ostatniego_elementu] == pionek_usr)
            {
                return -10;
            }
        }
    }

    //pion
    for (int i = 0; i < rozmiar_planszy; ++i)
    {
        if (sprawdz_czy_wygrana_pion(plansza, i))
        {
            if (plansza[indeks_ostatniego_elementu][i] == pionek_komp)
            {
                return 10;
            }

            if (plansza[indeks_ostatniego_elementu][i] == pionek_usr)
                return -10;
        }
    }

    //skos
    if (sprawdz_czy_wygrana_skos_1(plansza))
    {
        if (plansza[indeks_ostatniego_elementu][indeks_ostatniego_elementu] == pionek_komp)
        {
            return 10;
        }

        if (plansza[indeks_ostatniego_elementu][indeks_ostatniego_elementu] == pionek_usr)
            return -10;
    }

    if (sprawdz_czy_wygrana_skos_2(plansza))
    {

        if (plansza[indeks_ostatniego_elementu][rozmiar_planszy - 1 - indeks_ostatniego_elementu] == pionek_komp)
        {
            return 10;
        }

        if (plansza[indeks_ostatniego_elementu][rozmiar_planszy - 1 - indeks_ostatniego_elementu] == pionek_usr)
            return -10;
    }

    return 0;
}

//zwraca wieksza liczbe
int Plansza::wieksza(int a, int b)
{
    if (a > b)
        return a;
    
    else if (b > a)
        return b;
    
    else
        return a;

}
//zwraca mniejsza liczbe
int Plansza::mniejsza(int a, int b)
{
    if (a < b)
        return a;
    
    else if (b < a)
        return b;
    
    else
        return b;
}

void Plansza::obsluga_planszy(char** plansza)
{
    system("CLS");
    wyswietl_wynik();
    wyswietl_instrukcje();
    wyswietl_plansze(plansza);
}


int Plansza::minimax(char** plansza, int alfa, int beta, int glebokosc, bool czy_MAX)
{
    //okreslenie wartosci ruchu
    int wynik = czy_wygrana(plansza);

    //wygrana + glebokosc - im szybsza tym lepsza
    if (wynik == 10)
        return wynik + glebokosc;

    //wygrana - glebokosc - im dluzsza tym lepiej
    else if (wynik == -10)
    {
        return wynik - glebokosc;
    }

    //remis
    else if (czy_plansza_pelna(plansza))
        return 0;

    //maksymalizowanie ilosci pionkow w linii (bez pionkow przeciwnika) 
    else if (glebokosc == 0)
        return (zlicz_o_pion(plansza) + zlicz_o_poziom(plansza) + zlicz_o_ukos_1(plansza) + zlicz_o_ukos_2(plansza));


    //ruch gracza maksymalizujacego
            if (czy_MAX)
            {
                int flaga = 0;
                int najlepszy_wynik = -1000;

                //po wszystkich wolnych polach
                for (int i = 0; i < rozmiar_planszy; ++i)
                {
                    for (int j = 0; j < rozmiar_planszy; ++j)
                    {
                        
                        if (plansza[i][j] == ' ')
                        {
                            plansza[i][j] = pionek_komp;

                            //okreslenie wartosci ruchu
                            najlepszy_wynik = wieksza(najlepszy_wynik,
                                minimax(plansza, alfa, beta, glebokosc - 1, !czy_MAX));
                            
                            alfa = wieksza(alfa, najlepszy_wynik);

                            if (alfa >= beta)
                            {
                                plansza[i][j] = ' ';
                                flaga = 1;
                                break;
                            }

                            //cofniecie ruchu
                            plansza[i][j] = ' ';
                        }
                    }
                    if (flaga == 1)
                        break;
                }
                return najlepszy_wynik;
            }

            else if(!czy_MAX)
            {
                int flaga = 0;
                int najlepszy_wynik = 1000;

                for (int i = 0; i < rozmiar_planszy; i++)
                {
                    for (int j = 0; j < rozmiar_planszy; j++)
                    {
                        if (plansza[i][j] == ' ')
                        {
                            plansza[i][j] = pionek_usr;

                            najlepszy_wynik = mniejsza(najlepszy_wynik,
                                minimax(plansza, alfa, beta, glebokosc - 1, !czy_MAX));

                            beta = mniejsza(beta, najlepszy_wynik);

                            if (alfa >= beta)
                            {
                                plansza[i][j] = ' ';
                                flaga = 1;
                                break;
                            }

                            plansza[i][j] = ' ';
                        }
                    }
                }
                return najlepszy_wynik;
            }
}

void Plansza::znajdz_najlpeszy_ruch(char** plansza)
{
    int najlepsza_wartosc = -1000;
    int wartosc_ruchu;
    int naj_rzd = -1;
    int naj_kol = -1;


    //sprawdzane sa wszystkie, wolne miejsca

    std::cout << "Loading ... " << std::endl;

    for (int i = 0; i < rozmiar_planszy; ++i)
    {
        for (int j = 0; j < rozmiar_planszy; ++j)
        {
            std::cout << "#";
            
            //czy miejsce wolne
            if (plansza[i][j] == ' ')
            {
                //wykonanie ruchu
                plansza[i][j] = pionek_komp;

                wartosc_ruchu = minimax(plansza, -1000, 1000, MAX_glebokosc_rekurencji , false);

                // cofniecie ruchu
                plansza[i][j] = ' ';

                if (wartosc_ruchu > najlepsza_wartosc)
                {
                    naj_rzd = i;
                    naj_kol = j;
                    najlepsza_wartosc = wartosc_ruchu;
                }
            }
        }
    }

    //wykonanie najlepszego ruchu
    plansza[naj_rzd][naj_kol] = pionek_komp;
    wolne_pola[naj_rzd][naj_kol] = false;

    //komentarze pomagajace przy grze
    std::cout << "\nWartosc ruchu : " << najlepsza_wartosc << "\nA tu sie ruszy: " << " " << naj_rzd << " , " << naj_kol << std::endl;

    if (najlepsza_wartosc == 0)
        std::cout << "Defensywa " << std::endl;

    else if (najlepsza_wartosc >= 10)
        std::cout << "Ofensywa - widac wygrana " << std::endl;

    else if (najlepsza_wartosc <= -10)
        std::cout << "No chyba przegrana :(" << std::endl;

    else
        std::cout << "Jakis ciekawszy ruch, ale jescze nie widac wygranej" << std::endl;

    Sleep(2000);
}
