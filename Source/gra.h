#ifndef _gra
  #define _gra

  class gracz
  {
    protected:
      int zloto;
      int _ostatni_bilans;
      bool technologie[5];
      int liczba_jednostek;
      int tura;
    public:
      gracz();
      void zmien_ture(int);
      int pobierz_zloto();
      int ostatni_bilans();
      void zaplac(int);
      void kup_technologie(short);
      bool sprawdz_technologie(short);
      void zmien_zloto(int _zloto);
      void zmien_technologie(int);
      void zwieksz_jednostki();
      void zmniejsz_jednostki();
      int pobierz_liczbe_jednostek();
  };

  class gra
  {
    private:
      grafika *engine;
      mapa *obsluga_mapy;
      mapa_jednostek *obsluga_mapy_jednostek;
      menu *obsluga_menu;
      zdarzenia *obsluga_zdarzen;

    public:
      gra(char*);
      ~gra();
      bool czy_heros();

  };


  #include "gra.cpp"

#endif
