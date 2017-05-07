#ifndef _menu
  #define _menu

  /// typ wyliczeniowy stan�w przycisku
  enum przycisk_zdarzenie
  {
    KLIKNIECIE, NAJECHANIE, NORMALNY, ZWOLNIENIE
  };

  /// klasa obsluguj�ca menu g��wne gry
  class menu
  {
    protected:
      /// wska�niki na potrzebne obiekty z zewn�trz klasy
      grafika *engine;
      char wybrana_mapa[100];
      short wybrana_gra;
      char pljezyk[12];

      bool u_dzwiek;
    public:
      /// funkcja wy�wietla menu g��wne i obs�uguje zdarzenia, zwraca �cie�ke do wybranej
      /// mapy
      short pokaz();
      /// konstruktor klasy menu
      menu(grafika*);
      /// funkcja wyswietlajaca okno z podanym tekstem w danym miejscu
      short okno(int, int, char *, char *, char*);
      /// funkcja rysuje miniature mapy z pliku w odpowienie miejsce
      void miniatura(char *, int, int, int);
      char *wczytana_mapa();
      short wczytana_gra();
      short zwroc_ustawienia(short);
  };

  //******************************************************************************

  /// klasa sluzy do wyswietlania oraz obslugi zdarzen przycisku
  class przycisk
  {
    private:
      /// wska�niki na potrzebne obiekty z zewn�trz klasy        
      grafika *engine;
      /// po�o�enie przycisku
      int x;
      int y;
      /// aktualny stan przycisku
      przycisk_zdarzenie aktualny;
      /// etykieta na przycisku      
      char tekst[50];

    public:
      /// konstruktor do klasy przycisk
      przycisk(grafika *, int, int, char*);
      /// destruktor klasy przycisk
      ~przycisk();
      /// funkcja odswieza status przycisku
      przycisk_zdarzenie zdarzenie();

      /// funkcja wyswietla przycisk w zaleznosci od stanu w jakim sie znajduje 
      /// wraz z etykieta
      void rysuj();
      /// funkcja przesuwa przycisk w dane miejsce
      void przesun(int, int);
      /// funkcja zmienia tekst przycisku na wybrany
      void napis(char*);
      char *zwroc_napis();
      void zmien_stan(przycisk_zdarzenie);
  };


  #include "menu.cpp"

#endif
