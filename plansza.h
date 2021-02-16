#include <iostream>


class Plansza {
    bool* tablica_pion;
    bool* tablica_poziom;
    bool** wolne_pola;
    char pionek_usr, pionek_komp;
    int rozmiar_planszy;
    int ile_pionkow_do_wygranej;
    int indeks_ostatniego_elementu;
    bool pierwszy_ruch_AI;
    bool pierwszy_ruch_gracz;
    int MAX_glebokosc_rekurencji;
    int wielkosc_pola;
public:
    ~Plansza();
    double punkty_usr, punkty_komp;
    void inicjuj_plansze(char** plansza);
    void wyswietl_plansze(char** plansza);
    void wyswietl_instrukcje();
    void ruch_AI(char** plansza);
    bool czy_plansza_pelna(char** plansza);
    bool czy_remis(char** plansza);
    int czy_wygrana(char** plansza);
    void ruch_user(char** plansza);
    void obsluga_planszy(char** plansza);
    int minimax(char** plansza, int alfa, int beta,  int glebokosc, bool czy_MAX);
    void znajdz_najlpeszy_ruch(char** plansza);
    void okresl_kto_kim(char komputer, char user, int rozmiar, int ile_do_wygranej, int wielk_pola_kw);
    void wyswietl_wynik();
    void rozlicz_punkty(double pkt_komp, double pkt_usr);
    bool sprawdz_czy_wygrana_pion(char** plansza, int i);
    bool sprawdz_czy_wygrana_poziom(char** plansza, int i);
    bool sprawdz_czy_wygrana_skos_1(char** plansza);
    bool sprawdz_czy_wygrana_skos_2(char** plansza);
    bool brak_wygranej_poziom(char** plansza);
    bool brak_wygranej_pion(char** plansza);
    bool remis_pion(char** plansza);
    bool remis_poziom(char** plansza);
    int zlicz_x_pion(char** plansza);
    int zlicz_x_poziom(char** plansza);
    int zlicz_o_pion(char** plansza);
    int zlicz_o_poziom(char** plansza);
    int mniejsza(int a, int b);
    int wieksza(int a, int b);
    int zlicz_o_ukos_2(char** plansza);
    int zlicz_o_ukos_1(char** plansza);
};