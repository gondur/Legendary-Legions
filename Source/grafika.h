#ifndef _grafika
  #define _grafika

#include "BlendColors32.cpp"
  
  /// sta³a wysokosc/szerokosc pola
  const int wysokosc_pola = 40;
  const int szerokosc_pola = 40;

  //******************************************************************************

  /// typ wyliczeniowy nazw pol do rysowania
  enum nazwa_pola
  {
    PUSTE_POLE = 0, LAS, AKTYWNE_POLE, TRAWA, GORA, WODA, LAWA, LAWA_2,
      SPALONA_ZIEMIA, PUSTYNIA, OGNISTY, ZOLNIERZ, RYCERZ, HYDRA, ARCHANIOL,
      MAG, SMOK, TROL, CIEMNY_RYCERZ, LORD, NIEAKTYWNA_JEDNOSTKA, ZAMEK_GRACZ_1,
      ZAMEK_GRACZ_2, KURSOR, WIEZA_1, WIEZA_2, MIASTO_1, MIASTO_2, ROBOTNIK_1,
      ROBOTNIK_2
  };

  /// typ wyliczeniowy bitmap
  enum typ_bitmapy
  {
    B_MENU = 0, B_GRA, B_INTERFEJS, B_BUTTON, B_TLO_MENU, B_POLE_PRZ,
      B_POLE_PRZ_2, B_POLE_PRZ_3, INGAMEMENU, B_TARCZA_GRACZ_1,
      B_TARCZA_GRACZ_2, B_DUZA_TARCZA_GRACZ_1, B_DUZA_TARCZA_GRACZ_2,
      B_PASEK_SIL_BRAK, B_PASEK_SIL_PELNY, MIESO, MONETY
  };

  //******************************************************************************


  /// klasa pomocnicza punkt
  class punkt
  {
    private:
      float x, y;
    public:
      punkt(float, float);
      punkt(const punkt &);
      punkt();
      float rx();
      float ry();
      void wpisz(float, float);
      punkt operator = (punkt);
      punkt operator + (punkt);
  };

  //******************************************************************************


  /// klasa ta s³u¿y do sterowania wyœwietlan¹ grafik¹
  class grafika
  {
    private:
      /*@param bufor_ekranu bufor tylni, który jest kopiowany po wyrysowaniu elementow na ekran
      bitmapy pol, jednostek itp.*/
      BITMAP *bufor_ekranu;
      BITMAP *bitmapy;

      BITMAP *mieso;
      BITMAP *monety;
      BITMAP *kursor;

      /// bitmapy interfejsu
      BITMAP *b_interfejs;
      /// bitmapa wskaznika na mapie 
      BITMAP *b_wskaznik;
      /// bitmapa nieaktywnej jednostki
      BITMAP *b_nieaktywna;
      /// bitmapy tla pod menu
      BITMAP *b_tlo_menu;
      /// bitmapy buttona
      BITMAP *b_button;
      /// przezroczyste bitmapy u¿yte w menu
      BITMAP *b_pr;
      BITMAP *b_pr2;
      BITMAP *b_pr3;
      BITMAP *b_ingamemenu;

      /// bitmapa do robienia dnia/nocy
      BITMAP *b_noc;

      /// wskaŸnik na czcionke  
      FONT *f_font;
      /// licznik klatek (animacja)
      int klatka;
      /// klatka nowa
      int nowa_klatka;
      /// czas ostatniej klatki
      int poczatek;
      /// ilosc ticksow na sekunde (by uniezaleznic sie od srzetu)
      int clk;

      bool pokaz_klatke;
      bool wymus;

    public:
      void zmiana_klatki(bool);
      void wymus_rysowanie();
      bool czy_pokazac();
      /// bitmapa pomocnicza do okreslania aktualnego pola pod myszka (patrz. klasa mapa)
      BITMAP *mapa_myszki;
      /// metoda rysuje/animuje pole o danym typie pola w podanych wspó³rzêdnych
      void rysuj_pole(nazwa_pola, int, int, short);
      /// metoda rysuje kadr/ca³oœæ bitmapy o danym typie w okreslonym miejscu
      void rysuj_bitmape(typ_bitmapy, int, int, int, int, int, int);
      /// metoda wypisuje tekst na ekran
      void pisz(char *, int, int, int, int, bool, int);
      /// metoda do wpisywania tekstu z klawiatury do przekazanego stringu
      void wpisz(std::string &, int, bool);
      /// metoda wyswietla prostokat
      void prostokat(int, int, int, int, int, bool);
      /// metoda czysci bufor ekranu do danego koloru
      void czysc_ekran(int);
      /// funkcja pokazuje myszke a takze przekopiowuje bufor_ekranu na ekran
      void pokaz(bool);
      void rysuj_noc(short);
      /// inicjalizacja enginu graficznego i biblioteki allegro
      grafika(char*);
      /// destruktor klasy grafika
      ~grafika();
  };

  #include "grafika.cpp"

#endif
