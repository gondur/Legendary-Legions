#ifndef _muzyka
  #define _muzyka

  #include <almp3.h>

  ///klasa ADT odpowiedzialna za obsluge dzwieku w grze
  class dzwiek
  {
    protected:
      /// wskaznik do pliku z danymi
      PACKFILE *file;
      /// glosnosc
      short volume;
      /// sila dzwieku w poszczegolnych glosnikach
      short pan;
      /// wskaznik na strumien danych
      ALMP3_MP3STREAM *plik_mp3;
      /// wskaznik na tytul utworu
      char *tytul;
      /// wskaznik na plik wav
      SAMPLE *plik_wav;
    public:
      /// funkcja otwiera plik, do ktorego wskaznik podamy w argumencie
      virtual short otworz(char *filename);
      /// funkcja zamyka plik 
      virtual short zamknij();
      /// funkcja przygotowuje plik do odtwarzania
      virtual short przygotuj();
      /// funkcja odtwarza dzwiek
      virtual short odtwarzaj();
      /// funkcja zatrzymuje odtwarzanie dzwieku
      virtual short zatrzymaj();
      /// funkcja zwraca tytul pliku na ktoryw skazyje pole tytul 
      virtual char *podaj_tytul();
  };

  //******************************************************************************

  /// klasa odpowiedzialna za odtwarzanie odglosow w grze (pliki w formacie wav)
  /// dziedziczy ona po klasie dzwiek
  class odglosy: public dzwiek
  {
    public:
      /// konstruktor obiektu klasy odglosy, w argumencie podajemy wskaznik na plik wav
      odglosy(char *filename);
      /// funckja odtwarza dzwiek w formacje wav
      short odtwarzaj();
      /// destruktor obeiktu klasy dzwiek
      ~odglosy();
  };

  //******************************************************************************

  /// klasa odpowiedzialna zaobsluge plikow muzycznych w grze (pliki mp3)
  class muzyka: public dzwiek
  {
    public:
      /// konstruktor obiektu klasy muzyka, w argumencie podajemy wskaznik na plik w formacie mp3
      muzyka(char *filename);
      /// destruktor obiektu klasy muzyka
      ~muzyka();
  };

  //******************************************************************************

  /// klasa odpowiedzialna za obsluge list odtwarzania utworow mp3
  class playlista
  {
    protected:
      /// wskaznik na kolejnyelement listy
      playlista *kolejny;
      /// wskazni na element klasy muzyka
      muzyka *utwor;
    public:
      /// bezargumentowy konstruktor klasy
      playlista();
      /// konstruktor klasy w ktorym podajemy nazwe pliku mp3 ktory ma zostac umieszczont w nowej liscie
      playlista(char*);
      /// funkcja bezargumentowa dodajca nowy elementlisty
      playlista dodaj();
      /// funkcja umieszczana koncu listynowy element ze wskaznikiem na plik podany mp3
      playlista dodaj(char*);
      /// funkcja odtwarza utwor obecnego elementu listy
      void odtwarzaj();
      /// funkcja przygotowuje doodtwarzania plik mp3 z pola utwor
      void przygotuj();
      /// funkcja zatrzymje odtwarzanie utworu z pola utwor aktualnego elementu listy
      void zatrzymaj();
      /// funkcja zwraca adres do pliku mp3 umieszczoengo w obecnym elemencielisty
      muzyka *pobierz_utwor();
      /// funkcja przesuwa wskaznik na kolenjy element listy
      playlista przeskocz();
  };

  #include "muzyka.cpp"

#endif
