#include <iostream>
#include <cstdlib>
#include <Windows.h>
#include "plansza.h"

using namespace std;

int main()
{
    while (1) {

        system("CLS");
        char wybor_usr;
        char wybor_komp;
        char kto_zaczyna;
        int rozmiar_planszy;
        int wielkosc_pola;
        int ile_do_wygranej;
        bool koniec_gry = false;
        int flaga_a = 0;
        int flaga_b = 0;
        int flaga_c = 0;
        int flaga_d = 0;
        int flaga_e = 0;
        char powrot;


        cout << "Kolko i krzyzyk " << endl;

        //pytania poczatkowe, dzieki flagom mozliwe jest sprawdzenie wpisywanych danych
        while (flaga_a == 0)
        {
            cout << "Podaj czym chcesz grac (O,X): ";
            cin >> wybor_usr;
            cout << "Podaj czym ma grac komputer (O,X): ";
            cin >> wybor_komp;

            if (wybor_usr == wybor_komp)
                cout << "Pionki takie same!" << endl;

            else if (wybor_usr != wybor_komp && (wybor_komp == 'O' || wybor_komp == 'X') && (wybor_usr == 'O' || wybor_usr == 'X'))
                flaga_a = 1;

            else
                cout << "Blednie dobrane pionki!" << endl;
        }

        while (flaga_b == 0)
        {
            cout << "Kto ma zaczac rozgrywke? 'k' lub 'u':";
            cin >> kto_zaczyna;

            if (kto_zaczyna == 'k' || kto_zaczyna == 'u')
                flaga_b = 1;

            else
                cout << "Brak podanej opcji!" << endl;
        }

        while (flaga_c == 0)
        {
            cout << "Podaj rozmiar planszy: ";
            cin >> rozmiar_planszy;

            if (rozmiar_planszy >= 3 && rozmiar_planszy <= 5 && cin.good())
            {
                ile_do_wygranej = rozmiar_planszy;
                flaga_c = 1;
            }

            else
            {
                cin.clear();
                cin.ignore();
                cout << "Rozmiar musi byc liczba dodatnia, z przedzialu <3;5>";
            }
        }


        if (rozmiar_planszy == 5) 
        {
            while (flaga_d == 0)
            {
                cout << "Podaj ile pionkow w rzedzie, kolumnie i na skosie wystraczy by wygrac - 4 lub 5: ";
                cin >> ile_do_wygranej;

                if (ile_do_wygranej == 4 && cin.good())
                    flaga_d = 1;

                else if (ile_do_wygranej == 5 && cin.good())
                    flaga_d = 1;
                
                else 
                {
                    cin.clear();
                    cin.ignore();
                    cout << "Brak podanej opcji!\n";
                }


            }
        }

        while (flaga_e == 0)
        {
            cout << "Podaj wielkosc pola kwadratoego planszy - <1,2,3,4,5>: ";
            cin >> wielkosc_pola;

            if (wielkosc_pola >= 1 && wielkosc_pola <= 5 && cin.good())
                flaga_e = 1;

            else
            {
                cin.clear();
                cin.ignore();
                cout << "Rozmiar pola musi byc liczba naturalna z przedzialu <1;5>";
            }
        }

        Sleep(1000);
        system("CLS");


        std::cout << " ";

        //tworzenie planszy gry
        char** plansza = new char* [rozmiar_planszy];
        for (int i = 0; i < rozmiar_planszy; ++i) {
            plansza[i] = new char[rozmiar_planszy];
        }

        Plansza gra;
        gra.punkty_usr = 0;
        gra.punkty_komp = 0;



        while (1)
        {
            //okreslenie wartosci 
            gra.okresl_kto_kim(wybor_komp, wybor_usr, rozmiar_planszy, ile_do_wygranej, wielkosc_pola);
            gra.inicjuj_plansze(plansza);
            gra.obsluga_planszy(plansza);

            //jesli zaczyna komputer
            if (kto_zaczyna == 'k')
            {
                gra.znajdz_najlpeszy_ruch(plansza);
                gra.obsluga_planszy(plansza);

            }
            while (1)
            {

                gra.obsluga_planszy(plansza);


                //ruch usera
                gra.ruch_user(plansza);
                gra.obsluga_planszy(plansza);
                if (gra.czy_wygrana(plansza))
                {
                    //koniec gry - nadanie punktow, zakonczenie petli
                    cout << "Tym razem wygrales" << endl;
                    gra.rozlicz_punkty(0, 1);
                    Sleep(3000);
                    break;
                }
                if (gra.czy_plansza_pelna(plansza))
                {
                    cout << "Plansza pelna :(" << std::endl;
                    gra.rozlicz_punkty(0.5, 0.5);
                    Sleep(3000);
                    break;
                }

                if (gra.remis_poziom(plansza) == true && gra.remis_pion(plansza) == true)
                {
                    cout << "brak mozliwosci wygranej :(" << std::endl;
                    gra.rozlicz_punkty(0.5, 0.5);
                    Sleep(3000);
                    break;
                }



                //ruch komputera
                gra.znajdz_najlpeszy_ruch(plansza);
                gra.obsluga_planszy(plansza);
                if (gra.czy_wygrana(plansza))
                {
                    cout << "Matematyka ... " << endl;
                    gra.rozlicz_punkty(1, 0);
                    Sleep(3000);
                    break;
                }
                if (gra.czy_plansza_pelna(plansza))
                {
                    cout << "Plansza pelna :(" << std::endl;
                    gra.rozlicz_punkty(0.5, 0.5);
                    Sleep(3000);
                    break;
                }

                if (gra.remis_poziom(plansza) == true && gra.remis_pion(plansza) == true)
                {
                    cout << "brak mozliwosci wygranej :( " << std::endl;
                    gra.rozlicz_punkty(0.5, 0.5);
                    Sleep(3000);
                    break;
                }
            }

            cout << "Czy wrocic do menu glownego (t) lub koniec gry (k)? jezeli nie - dowolny inny znak: ";
            cin >> powrot;

            //powort do menu
            if (powrot == 't')
                break;

            //wyjscie
            if (powrot == 'k')
                break;
        }

        //koniec gry, usuniecie planszy
        if (powrot == 'k')
        {
            system("CLS");
            std::cout << "Koniec Gry";
            Sleep(2000);

            for (int i = 0; i < rozmiar_planszy; ++i)
                delete[] plansza[i];
            break;
        }
    }

    return 0;
}