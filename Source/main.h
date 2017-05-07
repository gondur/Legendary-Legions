#ifndef _main
  #define _main

  // tryb developerski :D
  bool MIERZ_FPS = false;
  bool dev_mode = false;

  short ai = 0;
  float godzina;
  char * ajezyk = "ll_pl.cfg";
  const int CHMUR=50;
  bool czy_chmury = false;
  int przes_x=0, przes_y=0;
  
  
  #include <allegro.h>
  #include <winalleg.h>
  #include <strings.h>
  #include <fstream.h>
  #include <stdlib.h>
  #include <time.h>
  #include <fblend.h>
  #include <math.h>
  #include <string.h>
  #include <iostream>

  ////debug

  void piszlog(char *tekst, int liczba)
  {
    FILE *plik;
    plik = fopen("log.txt", "a");
    fprintf(plik, "\n%s --- %d ", tekst, liczba);
    fclose(plik);
  }
  
  /////////
  #include "siec.h"
  Serwer *serwer = NULL;
  Klient *klient = NULL;
  ParserZapytan *parser = new ParserZapytan();
  int multiplayer = 0; // 0 - single player 1 - klient 2 - serwer
  int nowe_id = 0; 
    // id jednostek przydzielane kazdej jednostce w celu ich identyfikacji
  int multi_tura = 0; // 0 -tryb poj. 1 - dobra 2-zla
  bool kon_tur = false;
  bool zablokowane = false;

  #include "loadpng.h"
  #include "muzyka.h"
  #include "grafika.h"

  using namespace std;

#endif
