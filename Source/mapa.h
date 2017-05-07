#ifndef _mapa
  #define _mapa

  /// klasa obslugi mapy
  class mapa
  {
    private:
      /// szerokosc i wysokosc mapy
      int szerokosc;
      int wysokosc;

      /// wspolrzedne poczatku ekranu na mapie
      int start_x, start_y;
      /// szerokosc i wysokosc kadru mapy
      int ekran_szer;
      int ekran_wys;

      /// plik do wczytania mapy
      FILE *plik;
      /// wskaznik na tablice przechowywujaca dane o typie terenu
      char *pola;

      char plik_mapy[50];


      /// zmienne sluzace przechowaniu wspolrzednych aktualnie kliknietego pola srodek+stary_srodek
      punkt srodek;
      /// aktualnie klikniete pole
      punkt klikniete;

      /// pomocnicza zmienna do zwalniania przesuniecia mapy
      int przesuniecie;

      /// wskaznik na aktualnie uzywany przez klase mapa engine(obiekt) graficzny
      grafika *engine;

    public:
      /// konstruktor pobiera adres obiektu engine graficzny oraz sciezke do pliku z mapa
      mapa(grafika *, char*);
      ~mapa();
      /// funkcja rysuje aktualny kadr mapy do bufora_ekranu
      void pokaz();
      /// funkcja rysuje miniature mapy w podanej pozycji na ekranie i wybranym powiekszeniu
      void miniatura(int, int, int);
      /// funkcja s³u¿y do zmiany kadru mapy tak by po przesuniêciu kursora na krañce ekranu
      /// mapka siê przesuwa³a
      punkt wysrodkuj();
      /// funkcja sluzy do okreslenia, ktore pole na mapie jest aktualnie pod kursorem myszy oraz 
      /// zwraca wspolrzedne tego pola (rysuje wskazane pole gdy zaznacz_pole=true)
      punkt wskaz_pole(bool);
      /// funkcja zwraca bezwzgledna pozycje pola pod myszka
      punkt pole_pod_myszka();
      /// sprawdza czy zadana wspolrzedna jest w zasiegu kadru ekranu jesli tak to zwraca wartosc true
      bool czy_na_ekranie(int, int);
      /// zwraca wspolrzedne poczatku ekranu
      punkt start_ekranu();
      /// zwaca typ pola we wspo³rzednych x,y
      char jakie_pole(int, int);
      /// funkcja wstawia pole
      void wstaw(short);
      char *zwroc_nazwe();

  };

  #include "mapa.cpp"

#endif
