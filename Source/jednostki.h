#ifndef _jednostki
  #define _jednostki

  #define map_szer 60
  #define map_wys 60

  //******************************************************************************

  class mapa_jednostek; // pomocnicza definicja klasy mapa jednostek

  //******************************************************************************

  /// klasa jednostek gry
  class jednostka
  {
    protected:
      /// wskaŸniki na potrzebne obiekty z zewnatrz klasy
      grafika *engine;
      mapa *obsluga_mapy;
      zdarzenia *obsluga_zdarzen;
      mapa_jednostek *obsluga_mapy_jednostek;

      int id;
      int nastepny_poziom;

      /// cel ai
      jednostka *cel;

      /// jest to wskaznik do tablicy przechowujacej tymczasowe informacje o zasiegu jednostki (pola na ktore moze 
      /// aktualnie wejsc)
      short *mapa_przejsc;

      /// wskaznik na tekst opisujacy jednostke
      char opis[1000];
      /// wyglad jednostki
      nazwa_pola wyglad;

      bool wcisniety;
      /// pozycja jednostki na mapie
      int x, y;
      /// Stan jednostki: 0 - nieaktywna, 1 - aktywna, 2 aktywna ale nie ma ruchu
      int stan;

      int punkty_ruchu;
      /// domyslne punkty ruchu jednostki
      int d_punkty_ruchu;
      /// informacja o przyale¿noœæi do gracza
      int gracz;
      int punkty_zycia;
      /// domyslne punkty zycia jednostki
      int d_punkty_zycia;

      /// umiejetnosci jednostki
      int atak;
      int obrona;
      int zwinnosc;

      short poziom;
      short doswiadczenie;
      /// ilosc doswiadczenia za zabicie jednostki
      short exp;

      short cena;
      /// pieniadze zdobyte przez jednostke (np. za zabicie innej)
      short pieniadze;
      /// ilosc punktow dostepnych do rozdysponowania dla jednostki
      short do_rozdysp;

    public:
      /// funkcja rysujaca jednostke oraz pasek sil i gdzie moze sie poruszyc
      virtual void rysuj();
      /// sprawdza czy jednostka zostala kliknieta (zwraca 1), badz jest nieaktywna (zwraca 0)
      virtual int obsluga();
      /// funkcja obslugujaca przesuwanie jednostki oraz walke
      virtual void sterowanie();
      /// zmienia stan jednostki na podany w argumencie
      virtual void zmien_stan(int);
      /// zwraca aktualny stan w jakim znajduje sie jednostka
      virtual int aktualny_stan();
      /// przywraca punkty ruchu do standardowej dla danej jednostki
      virtual void przywroc_punkty_ruchu(int);
      /// funkcja leczy jednostke maksymalnie o tyle procent ile podano domyœlnych punktow zycia
      virtual void ulecz(short);
      /// funkcja trenuje jednostke dodajac punkty doswiadczenia
      virtual void trenuj(short);
      /// sprawdza czy zostaly przekroczone punkty doswiadczenia potrzebne do skoku na wyzszy poziom i rzeczy z tym zwiazane
      virtual void nowy_poziom();

      /// sprawdza pola wokol czy sa dostepne do przejscia
      virtual void sprawdz_wokol(int, int);

      /// funkcje zmieniaj¹ce parametry jednostki
      virtual void zmien_pieniadze(short);
      virtual void zwieksz_atak(int);
      virtual void zwieksz_obrone(int);
      virtual void zwieksz_zwinnosc(int);
      virtual void zmniejsz_do_rozdysponowania();
      virtual void zmien_gracz(int);
      virtual void zmien_punkty_zycia(int);
      virtual void zmien_d_punkty_zycia(int);
      virtual void zmien_punkty_ruchu(int);
      virtual void zmien_atak(int);
      virtual void zmien_obrona(int);
      virtual void zmien_zwinnosc(int);
      virtual void zmien_do_rozdysponowania(int);
      virtual void zmien_poziom(int);
      virtual void zmien_doswiadczenie(int);
      virtual void zmien_exp(int);
      virtual void zmien_pieniadze(int);
      virtual void zmien_pozycje(int, int);
      virtual void zmien_id(int);

      /// wyswietla informacje o jednostce, pierwszy argument decyduje czy maja sie pojawic
      /// statystyki jednostki, drugi czy ma sie pojawic opis jednostki
      virtual void wyswietl_info(bool, bool);

      /// funkcje pobierajace parametry jednostki
      virtual int pobierz_gracz();
      virtual int pobierz_x();
      virtual int pobierz_y();
      virtual int pobierz_punkty_zycia();
      virtual int pobierz_d_punkty_zycia();
      virtual int pobierz_punkty_ruchu();
      virtual int pobierz_atak();
      virtual int pobierz_obrona();
      virtual int pobierz_zwinnosc();
      virtual int pobierz_do_rozdysponowania();
      virtual short pobierz_poziom();
      virtual short pobierz_doswiadczenie();
      virtual short pobierz_exp();
      virtual short pobierz_cene();
      virtual short pobierz_pieniadze();
      virtual char *pobierz_opis();
      virtual nazwa_pola pobierz_wyglad();
      virtual bool sprawdz_sasiadow(char*);
      virtual int pobierz_id();

      virtual void pobierz_cel();
      virtual punkt &akcja_cel();

      virtual void czysc_mape_przejsc();

  };

  //******************************************************************************


  /// klasa jednostki zamek__gracz_1
  class robotnik_1: public jednostka
  {
    public:
      robotnik_1(grafika *, mapa *, mapa_jednostek *, zdarzenia *, int, int,
        int);
  };

  class robotnik_2: public jednostka
  {
    public:
      robotnik_2(grafika *, mapa *, mapa_jednostek *, zdarzenia *, int, int,
        int);
  };

  /// klasa jednostki zamek__gracz_1
  class wieza_1: public jednostka
  {
    public:
      wieza_1(grafika *, mapa *, mapa_jednostek *, zdarzenia *, int, int, int);
  };

  /// klasa jednostki zamek__gracz_1
  class wieza_2: public jednostka
  {
    public:
      wieza_2(grafika *, mapa *, mapa_jednostek *, zdarzenia *, int, int, int);
  };

  /// klasa jednostki zamek__gracz_1
  class miasto_1: public jednostka
  {
    public:
      miasto_1(grafika *, mapa *, mapa_jednostek *, zdarzenia *, int, int, int);
  };

  /// klasa jednostki zamek__gracz_1
  class miasto_2: public jednostka
  {
    public:
      miasto_2(grafika *, mapa *, mapa_jednostek *, zdarzenia *, int, int, int);
  };


  /// klasa jednostki zamek__gracz_1
  class zamek_gracz_1: public jednostka
  {
    public:
      zamek_gracz_1(grafika *, mapa *, mapa_jednostek *, zdarzenia *, int, int,
        int);
  };

  /// klasa jednostki zamek_gracz_2
  class zamek_gracz_2: public jednostka
  {
    public:
      zamek_gracz_2(grafika *, mapa *, mapa_jednostek *, zdarzenia *, int, int,
        int);
  };


  /// klasa jednostki ognisty
  class ognisty: public jednostka
  {
    public:
      ognisty(grafika *, mapa *, mapa_jednostek *, zdarzenia *, int, int, int);
  };

  //******************************************************************************

  class zolnierz: public jednostka
  {
    public:
      zolnierz(grafika *, mapa *, mapa_jednostek *, zdarzenia *, int, int, int);
  };


  class rycerz: public jednostka
  {
    public:
      rycerz(grafika *, mapa *, mapa_jednostek *, zdarzenia *, int, int, int);
  };

  class hydra: public jednostka
  {
    public:
      hydra(grafika *, mapa *, mapa_jednostek *, zdarzenia *, int, int, int);
  };

  class archaniol: public jednostka
  {
    public:
      archaniol(grafika *, mapa *, mapa_jednostek *, zdarzenia *, int, int, int)
        ;
  };

  class mag: public jednostka
  {
    public:
      mag(grafika *, mapa *, mapa_jednostek *, zdarzenia *, int, int, int);
  };

  class smok: public jednostka
  {
    public:
      smok(grafika *, mapa *, mapa_jednostek *, zdarzenia *, int, int, int);
  };

  class lord: public jednostka
  {
    public:
      lord(grafika *, mapa *, mapa_jednostek *, zdarzenia *, int, int, int);
  };

  class ciemny_rycerz: public jednostka
  {
    public:
      ciemny_rycerz(grafika *, mapa *, mapa_jednostek *, zdarzenia *, int, int,
        int);
  };

  class trol: public jednostka
  {
    public:
      trol(grafika *, mapa *, mapa_jednostek *, zdarzenia *, int, int, int);
  };


  //******************************************************************************

  /// klasa obslugujaca tablice wskaznikow do jednostek na mapie
  class mapa_jednostek
  {
    protected:
      /// tablica jednostek (zawiera adresy do obiektów typu jednostka)
      /// tablica dwuwymiarowa zaimplementowana na jednowymiarowej tablicy
      jednostka **tab;

    public:
      /// konstruktor budujacy mape
      /// - alokujacy pamiec na tablice wskaznikow do jednostek
      mapa_jednostek();
      /// destruktor zwalnia pamiec przydzielona na mape wskaznikow do jednostek
      ~mapa_jednostek();
      /// funkcja wstawia adres jednostki - j do tablicy wskaznikow do jednostek, czyli mapy,
      /// w miejscu, w ktorym aktualnie sie znajduje
      void wstaw_jednostke(jednostka *j);
      /// funkcja zwraca adres do jednostki znajdujacej sie miejscu o wspolrzednych (x,y)
      jednostka *pobierz_jednostke(int x, int y);
      /// funkcja zeruje adres na mapie wskaznikow o wspolrzednych (x,y)
      void zeruj_pole(int x, int y);
  };

  //******************************************************************************

  /// klasa obslugujaca liste jednostek w grze
  class armia
  {
    protected:
      /// zmienna przechowuj¹ca informacje o przynale¿noœci jednostki do danego gracza
      int gracz;
      /// pomocniczy wskaŸnik przekazywany z klasy gry do obs³ugi mapy jednostek
      mapa_jednostek *obsluga_mapy_jednostek;
      /// adres do jednostki znajduj¹cej siê na elemencie listy
      jednostka *oddzial;
      /// adres do jednostki aktywnej
      jednostka *aktywna;
      /// adres do nastêpnego elementu listy
      armia *nastepny;

    public:
      /// konstruktor i destruktor klasy armia
      armia();
      ~armia();

      /// konstruktor z argumentami klasy armia
      armia(nazwa_pola, int, grafika *, mapa *, mapa_jednostek *, zdarzenia *,
        int, int, bool);
      /// funkcja dodaje do listy nowy element (jednostke)
      void dodaj(nazwa_pola, int, grafika *, mapa *, mapa_jednostek *,
        zdarzenia *, int, int, bool);
      /// funkcja usuwa element z listy
      void usun();

      /// funkcja analizuje kazda jednostke na liscie i:
      ///   - sprawdza czy jednostka zosta³a klikniêta
      ///   - ustala, ktora jednostka jest aktualnie aktywna
      ///   - rysuje jednostki
      short aktualizuj(int);

      /// funkcja przywraca standardowe parametry jednostkom zywym(uzyta na koniec tury,
      /// po to aby w nastepnej turze mialy punkty ruchu.
      void zeruj_jednostki();

      /// funkcja zwraca adres jednostki aktywnej
      jednostka *zwroc_aktywna();

      jednostka *zwroc_ostatnia();

      /// funkcja uzyta do przycisku zakoncz ture, jej dzialanie polega na tym, ze
      /// zyjacym jeszcze jednostkom ustawia punkty ruchu na 0, by zakonczyly ruch
      /// natomiast jednostkom martwym ustala stan na 2 czyli sa aktywne ale nie maja ruchu
      void zakoncz_ture();

      /// funkcja przeglada liste i aktywuje pierwsza zyjaca napotkana jednostke gracza
      /// ktory aktualnie ma ruch (ture)
      void zaznacz_pierwsza(int tura);

      /// funkcja przeglada wszystkie jednostki na liscie i umieszcza je na mapie
      /// jednostek, tak by wiadomo jaka jednostka znajduje sie na danym polu
      void inicjalizuj_mape_jednostek();

      /// funkcja przeszukuje liste jednostek i zwraca pierwsz¹ o podanym wygl¹dzie
      jednostka *zwroc_jednostke(nazwa_pola);
      jednostka *zwroc_jednostke_id(int);

      void zapisz_jednostki(short);

      bool czy_koniec_tury(int tura);

  };

  #include "jednostki.cpp"

#endif
