#ifndef _SIEC
  #define _SIEC

  #include "gniazda.h"

  class Serwer
  {
    private:
      int gniazdoSerwer;
      int gniazdoKlient;
      char bufor[MAX_SIZE];

    public:
      Serwer(int port);
      ~Serwer();

      bool przyjmijKlienta();
      bool odbierzZapytanie();
      void wyslijZapytanie(char *tresc);
      void serwWyslijPlik(char *plik);
      char *zwrocZapytanie();
  };

  class Klient
  {
    private:
      int gniazdoKlient;
      char bufor[MAX_SIZE];
    public:
      Klient(char *ip, int port);
      ~Klient();
      int zwrocSocket();
      void wyslijZapytanie(char *tresc);
      bool odbierzZapytanie();
      char *zwrocZapytanie();
      void zerujBufor();
  };

  class ParserZapytan
  {
    public:
      char typZapytania[5];

      // Zapytanie MOVE
      int px, py;
      int dx, dy;

      int id;

      // dane jednostki
      int gracz;
      int punkty_zycia;
      int d_punkty_zycia;
      int punkty_ruchu;
      int atak;
      int obrona;
      int zwinnosc;
      int do_rozdysponowania;
      int poziom;
      int doswiadczenie;
      int exp;
      int pieniadze;

      int wyglad;
      int tura;
      int czy_heros;

      char tekst_czat[100];

      int ktora;
      int zloto;

      ParserZapytan();
      ~ParserZapytan();
      int przetwarzajZapytanie(char *zapytanie);
      void zeruj();

  };

  #include "siec.cpp"

#endif
