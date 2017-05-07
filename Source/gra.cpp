/// Klasa gra jest klas¹ testuj¹c¹ wszystkie dostêpne klasy. Jest to g³ówna klasa gry. 
/// konstruktor z argumentem decyduje o tym, czy gra uruchomi siê w trybie pe³noekranowym, 
/// czy w oknie (przekazywany jest on obiektowi engine bêd¹cemu obiektem klasy grafika). 
gra::gra(char *s_screen)
{
  const int ILOSC_LINII = 8;
  std::string tekst_czat[ILOSC_LINII];
  for (int i = 0; i < ILOSC_LINII; ++i)
    tekst_czat[i] = "";

  // uruchomienie enginu graficznego (w tym biblioteki allegro)
  engine = new grafika(s_screen);

  /// Tworzone s¹ obiekty klasy  i przyciski potrzebne do implementacji interfejsu, 
  /// tak¿e napisanej w konstruktorze klasy gra.

  obsluga_menu = new menu(engine);

  /// Tworzony jest tak¿e obiekt klasy zdarzenia, obs³uguj¹cy stan klawiszy myszki, okna i 
  /// przekazywany do kolejnych jednostek.
  obsluga_zdarzen = new zdarzenia(engine);


  /// Inicjowane s¹ tak¿e zmienne pomocnicze przechowywuj¹ce np. aktualn¹ turê rozgrywki, 
  /// aktualnego menu interfejsu gry, indeksu wybranej jednostki do kupna.
  short indeks_wybrana[2];
  indeks_wybrana[0] = 0;
  indeks_wybrana[1] = 0;
  short menu = 1;
  short podmenu = 0;
  int tura = 1;
  int net_tura = tura;


  set_config_file(ajezyk);
  char nazwa_pliku_mapy[100]; // z savu
  short wybor_menu = obsluga_menu->pokaz();

  przycisk koniec_tury(engine, 750, 740, (char*)get_config_string("teksty", 
    "endturn", "Not Read"));
  przycisk wyjscie(engine, 400, 740, (char*)get_config_string("teksty", 
    "options", "Not Read"));
  przycisk powrot(engine, 400, 740, (char*)get_config_string("teksty", "powrot",
    0));

  przycisk ulecz(engine, 400, 700, (char*)get_config_string("teksty", "heal", "Not Read")
    );
  przycisk napraw(engine, 620, 700, (char*)get_config_string("teksty", "repair",
    "Not Read"));
  przycisk buduj(engine, 620, 680, (char*)get_config_string("teksty", "buduj",
    "Not Read"));
  przycisk buduj_miasto(engine, 200, 609, (char*)get_config_string("teksty", "buduj_miasto",
    "Not Read"));
  przycisk buduj_wieze(engine, 200, 633, (char*)get_config_string("teksty", "buduj_wieze",
    "Not Read"));
    
  przycisk trenuj(engine, 510, 700, (char*)get_config_string("teksty", 
    "training", 0));

  przycisk zapis1(engine, 455, 200, (char*)get_config_string("teksty", "save1",
    "Not Read"));
  przycisk zapis2(engine, 455, 230, (char*)get_config_string("teksty", "save2",
    "Not Read"));
  przycisk zapis3(engine, 455, 260, (char*)get_config_string("teksty", "save3",
    "Not Read"));
  przycisk zapis4(engine, 455, 290, (char*)get_config_string("teksty", "save4",
    "Not Read"));
  przycisk zapis5(engine, 455, 320, (char*)get_config_string("teksty", "save5",
    "Not Read"));
  przycisk powrot3(engine, 455, 380, (char*)get_config_string("teksty", 
    "powrot", 0));
  przycisk wyjscie2(engine, 455, 410, (char*)get_config_string("teksty", "exit",
    "Not Read"));

  przycisk kup(engine, 510, 740, (char*)get_config_string("teksty", "buy", "Not Read"));
  przycisk nastepna(engine, 510, 700, (char*)get_config_string("teksty", "next",
    "Not Read"));
  przycisk poprzednia(engine, 400, 700, (char*)get_config_string("teksty", 
    "previous", "Not Read"));

  przycisk zwieksz_atak(engine, 448, 627, (char*)get_config_string("teksty", 
    "raiseattack", "Not Read"));
  przycisk zwieksz_obrone(engine, 448, 651, (char*)get_config_string("teksty", 
    "raisedefense", "Not Read"));
  przycisk zwieksz_zwinnosc(engine, 448, 675, (char*)get_config_string("teksty",
    "raiseagility", "Not Read"));

  przycisk kup_jednostke(engine, 200, 609, (char*)get_config_string("teksty", 
    "buyunit", "Not Read"));
  przycisk kup_technologie(engine, 200, 633, (char*)get_config_string("teksty",
    "buytechnology", "Not Read"));

  przycisk niedostepna(engine, 510, 740, (char*)get_config_string("teksty", 
    "notavaiable", "Not Read"));
  przycisk technologia_1(engine, 200, 609, (char*)get_config_string("teksty", 
    "technology1", "Not Read"));
  przycisk technologia_2(engine, 200, 633, (char*)get_config_string("teksty", 
    "technology2", "Not Read"));
  przycisk technologia_3(engine, 200, 657, (char*)get_config_string("teksty", 
    "technology3", "Not Read"));
  przycisk technologia_4(engine, 200, 681, (char*)get_config_string("teksty", 
    "technology4", "Not Read"));




  /// Wczytywana jest mapa przy pomocy obiektu klasy mapa, 
  FILE *plik_l;

  //if(wybor_menu==1) 
  //{
  char wybrana_mapa[255];

  if (obsluga_menu->wczytana_gra() == 1)
    strcpy(wybrana_mapa, "Zapisane_gry/1.sav");
  if (obsluga_menu->wczytana_gra() == 2)
    strcpy(wybrana_mapa, "Zapisane_gry/2.sav");
  if (obsluga_menu->wczytana_gra() == 3)
    strcpy(wybrana_mapa, "Zapisane_gry/3.sav");
  if (obsluga_menu->wczytana_gra() == 4)
    strcpy(wybrana_mapa, "Zapisane_gry/4.sav");
  if (obsluga_menu->wczytana_gra() == 5)
    strcpy(wybrana_mapa, "Zapisane_gry/5.sav");

  if (obsluga_menu->wczytana_gra() == 6)
    strcpy(wybrana_mapa, "Pliki_danych/Mapy/map1.sce");
  if (obsluga_menu->wczytana_gra() == 7)
    strcpy(wybrana_mapa, "Pliki_danych/Mapy/map2.sce");
  if (obsluga_menu->wczytana_gra() == 8)
    strcpy(wybrana_mapa, "Pliki_danych/Mapy/map3.sce");
  if (obsluga_menu->wczytana_gra() == 9)
    strcpy(wybrana_mapa, "Pliki_danych/Mapy/map4.sce");
  plik_l = fopen(wybrana_mapa, "r");
  //////////////////////////    SIEC    /////////////////////////////////////////////////////////////////////

  set_config_file("config.cfg");
  if (strcmp((char*)get_config_string("General", "multiplayer", "Not Read"), 
    "POJEDYNCZY") == 0)
    multiplayer = 0;
  if (strcmp((char*)get_config_string("General", "multiplayer", "Not Read"), "KLIENT") 
    == 0)
    multiplayer = 1;
  if (strcmp((char*)get_config_string("General", "multiplayer", "Not Read"), "SERWER") 
    == 0)
    multiplayer = 2;
  set_config_file(ajezyk);
  switch (multiplayer)
  {
    case 1:
      // klient
      set_config_file("config.cfg");
      klient = new Klient((char*)get_config_string("General", "ip", "127.0.0.1"), get_config_int("General", "port", 0));
	  set_config_file(ajezyk);
      if (klient->zwrocSocket() ==  - 1)
      {
        engine->czysc_ekran(0);
        while (1)
        {
          if (obsluga_menu->okno(320, 216, (char*)get_config_string("teksty", 
            "zlyadres", 0), " ", (char*)get_config_string("teksty", "anuluj", "Not Read")
            ) == 1)
            exit(1);

          obsluga_zdarzen->wyswietl_okno(0);
          engine->pokaz(true);
        }
      }

      set_config_file("config.cfg");


      while (!klient->odbierzZapytanie())
        ;
      parser->przetwarzajZapytanie(klient->zwrocZapytanie());
      if (parser->tura == 1)
      {
        net_tura = 1;
        multi_tura = 2;
      }
      if (parser->tura == 2)
      {
        net_tura = 2;
        multi_tura = 1;
      }

      char pom_tekst[105];
      int plik_mapnet;
      plik_mapnet = open("Pliki_danych/Mapy/mapnet.sce", O_WRONLY);

      parser->zeruj();
      while (strcmp(parser->typZapytania, "END") != 0)
      {

        if (!klient->odbierzZapytanie())
          continue;
        strcpy(pom_tekst, klient->zwrocZapytanie());
        parser->przetwarzajZapytanie(klient->zwrocZapytanie());
        //if( strcmp(parser->typZapytania, "END")!=0 ) 
        if (strcmp(parser->typZapytania, "END") != 0)
          write(plik_mapnet, pom_tekst, strlen(pom_tekst));

      }


      close(plik_mapnet);
      parser->zeruj();
      plik_mapnet = open("Pliki_danych/Mapy/mapnet.map", O_WRONLY);
      while (strcmp(parser->typZapytania, "END") != 0)
      {
        if (!klient->odbierzZapytanie())
          continue;
        strcpy(pom_tekst, klient->zwrocZapytanie());

        parser->przetwarzajZapytanie(klient->zwrocZapytanie());
        if (strcmp(parser->typZapytania, "END") != 0)
          write(plik_mapnet, pom_tekst, strlen(pom_tekst));
      }
      fprintf(stderr, "\n\n");
      close(plik_mapnet);

      plik_l = fopen("Pliki_danych/Mapy/mapnet.sce", "r");
	  set_config_file(ajezyk);
	  sprintf(nazwa_pliku_mapy, "Pliki_danych/Mapy/mapnet.map");
      break;
    case 2:
      // serwer
      set_config_file("config.cfg");
      engine->czysc_ekran(0);
      serwer = new Serwer(get_config_int("General", "port", 0));
      set_config_file(ajezyk);
      
      while (1)
      {
        if (obsluga_menu->okno(320, 216, (char*)get_config_string("teksty", 
          "oczekuje", "Error"), (char*)get_config_string("teksty", "anuluj", "Error"), " ")
          == 0)
          exit(1);

        if (serwer->przyjmijKlienta())
          break;
        obsluga_zdarzen->wyswietl_okno(0);
        engine->pokaz(true);
      }

      set_config_file("config.cfg");
      char zap[100];
      if (strcmp((char*)get_config_string("General", "strona", "Not Read"), "DOBRA") ==
        0)
      {
        net_tura = 1;
        multi_tura = 1;
      }
      if (strcmp((char*)get_config_string("General", "strona", "Not Read"), "ZLA") == 0)
      {
        net_tura = 2;
        multi_tura = 2;
      }
      sprintf(zap, "TURA %d", tura);
      serwer->wyslijZapytanie(zap);
      serwer->serwWyslijPlik(wybrana_mapa);
      serwer->wyslijZapytanie("END");
      fscanf(plik_l, "%s", nazwa_pliku_mapy);
      serwer->serwWyslijPlik(nazwa_pliku_mapy);
      serwer->wyslijZapytanie("END");
      rewind(plik_l);
	  set_config_file(ajezyk);
      break;
  }

  ///////////////////////////////

  fscanf(plik_l, "%s", nazwa_pliku_mapy);
  obsluga_mapy = new mapa(engine, nazwa_pliku_mapy);
  //}
  //else
  //obsluga_mapy = new mapa(engine, obsluga_menu->wczytana_mapa());



  clock_t fps = clock();
  short l_klatek = 0, fps_ile = 0;
  int clk = CLOCKS_PER_SEC;


  /// oraz  obs³uga mapy jednostek.
  obsluga_mapy_jednostek = new mapa_jednostek;

  /// jednostki do kupienia (pozycja -1, -1, by nie weszla na mape jednostek)
  armia do_kupienia_1(ROBOTNIK_1, 1, engine, obsluga_mapy,
    obsluga_mapy_jednostek, obsluga_zdarzen,  - 1,  - 1);
  do_kupienia_1.dodaj(ZOLNIERZ, 1, engine, obsluga_mapy, obsluga_mapy_jednostek,
    obsluga_zdarzen,  - 1,  - 1);
  do_kupienia_1.dodaj(RYCERZ, 1, engine, obsluga_mapy, obsluga_mapy_jednostek,
    obsluga_zdarzen,  - 1,  - 1);
  do_kupienia_1.dodaj(MAG, 1, engine, obsluga_mapy, obsluga_mapy_jednostek,
    obsluga_zdarzen,  - 1,  - 1);
  do_kupienia_1.dodaj(HYDRA, 1, engine, obsluga_mapy, obsluga_mapy_jednostek,
    obsluga_zdarzen,  - 1,  - 1);
  do_kupienia_1.dodaj(ARCHANIOL, 1, engine, obsluga_mapy,
    obsluga_mapy_jednostek, obsluga_zdarzen,  - 1,  - 1);

  armia do_kupienia_2(CIEMNY_RYCERZ, 2, engine, obsluga_mapy,
    obsluga_mapy_jednostek, obsluga_zdarzen,  - 1,  - 1);
  do_kupienia_2.dodaj(ROBOTNIK_2, 2, engine, obsluga_mapy,
    obsluga_mapy_jednostek, obsluga_zdarzen,  - 1,  - 1);
  do_kupienia_2.dodaj(OGNISTY, 2, engine, obsluga_mapy, obsluga_mapy_jednostek,
    obsluga_zdarzen,  - 1,  - 1);
  do_kupienia_2.dodaj(LORD, 2, engine, obsluga_mapy, obsluga_mapy_jednostek,
    obsluga_zdarzen,  - 1,  - 1);
  do_kupienia_2.dodaj(SMOK, 2, engine, obsluga_mapy, obsluga_mapy_jednostek,
    obsluga_zdarzen,  - 1,  - 1);
  do_kupienia_2.dodaj(TROL, 2, engine, obsluga_mapy, obsluga_mapy_jednostek,
    obsluga_zdarzen,  - 1,  - 1);


  /// tworzony jest obiekt klasy gracz i armia_l, która dodaje jednostki do ka¿dego z 
  /// uczestników gry (wymagana jest inicjalizacja mapy jednostek, by mog³y one wiedzieæ, 
  /// gdzie mog¹ siê poruszaæ, a tak¿e wykrywaæ wrogie oddzia³y).

  gracz gracz[2];
  gracz[0].zmien_ture(1);
  gracz[1].zmien_ture(2);

  armia armia_l(ZOLNIERZ, 0, engine, obsluga_mapy, obsluga_mapy_jednostek,
    obsluga_zdarzen, 1, 1);

  /// wczytywanie stanu gry

  char w_jedn;
  int w_gracz;
  int w_x, w_y;
  int w_punkty_zycia;
  int w_d_punkty_zycia;
  int w_punkty_ruchu;
  int w_atak;
  int w_obrona;
  int w_zwinnosc;
  int w_do_rozdysponowania;
  int w_poziom;
  int w_doswiadczenie;
  int w_exp;
  int w_pieniadze;
  int w_zloto1, w_zloto2;

  int w_tech2, w_tech3, w_tech4, w_tech5;

  /// tylko wtedy gdy wybralismy taka opcje w menu
  if (wybor_menu == 1)
  {

    fscanf(plik_l, "%d %f %d %d", &tura, &godzina, &w_zloto1, &w_zloto2);
    fscanf(plik_l, "%d %d %d %d", &w_tech2, &w_tech3, &w_tech4, &w_tech5);
    if (w_tech2 == 1)
      gracz[0].kup_technologie(2);
    if (w_tech3 == 1)
      gracz[0].kup_technologie(3);
    if (w_tech4 == 1)
      gracz[0].kup_technologie(4);
    if (w_tech5 == 1)
      gracz[0].kup_technologie(5);

    fscanf(plik_l, "%d %d %d %d", &w_tech2, &w_tech3, &w_tech4, &w_tech5);

    if (w_tech2 == 1)
      gracz[1].kup_technologie(2);
    if (w_tech3 == 1)
      gracz[1].kup_technologie(3);
    if (w_tech4 == 1)
      gracz[1].kup_technologie(4);
    if (w_tech5 == 1)
      gracz[1].kup_technologie(5);


    gracz[0].zmien_zloto(w_zloto1);
    gracz[1].zmien_zloto(w_zloto2);

    while (1)
    {
      fscanf(plik_l, "%c", &w_jedn);
      if (w_jedn == 'E')
        break;
      fscanf(plik_l, "%d %d %d %d %d %d %d %d %d %d %d %d %d %d", &w_gracz, 
        &w_x, &w_y, &w_punkty_zycia, &w_d_punkty_zycia, &w_punkty_ruchu, 
        &w_atak, &w_obrona, &w_zwinnosc, &w_do_rozdysponowania, &w_poziom, 
        &w_doswiadczenie, &w_exp, &w_pieniadze);

      if (w_jedn == 'M')
        armia_l.dodaj(WIEZA_1, w_gracz, engine, obsluga_mapy,
          obsluga_mapy_jednostek, obsluga_zdarzen, w_x, w_y);
      if (w_jedn == 'J')
        armia_l.dodaj(WIEZA_2, w_gracz, engine, obsluga_mapy,
          obsluga_mapy_jednostek, obsluga_zdarzen, w_x, w_y);
      if (w_jedn == 'K')
        armia_l.dodaj(MIASTO_1, w_gracz, engine, obsluga_mapy,
          obsluga_mapy_jednostek, obsluga_zdarzen, w_x, w_y);
      if (w_jedn == 'L')
        armia_l.dodaj(MIASTO_2, w_gracz, engine, obsluga_mapy,
          obsluga_mapy_jednostek, obsluga_zdarzen, w_x, w_y);
      if (w_jedn == 'Q')
        armia_l.dodaj(ROBOTNIK_1, w_gracz, engine, obsluga_mapy,
          obsluga_mapy_jednostek, obsluga_zdarzen, w_x, w_y);
      if (w_jedn == 'W')
        armia_l.dodaj(ROBOTNIK_2, w_gracz, engine, obsluga_mapy,
          obsluga_mapy_jednostek, obsluga_zdarzen, w_x, w_y);

      if (w_jedn == 'Z')
        armia_l.dodaj(ZAMEK_GRACZ_1, w_gracz, engine, obsluga_mapy,
          obsluga_mapy_jednostek, obsluga_zdarzen, w_x, w_y);
      if (w_jedn == 'X')
        armia_l.dodaj(ZOLNIERZ, w_gracz, engine, obsluga_mapy,
          obsluga_mapy_jednostek, obsluga_zdarzen, w_x, w_y);
      if (w_jedn == 'C')
        armia_l.dodaj(HYDRA, w_gracz, engine, obsluga_mapy,
          obsluga_mapy_jednostek, obsluga_zdarzen, w_x, w_y);
      if (w_jedn == 'V')
        armia_l.dodaj(ARCHANIOL, w_gracz, engine, obsluga_mapy,
          obsluga_mapy_jednostek, obsluga_zdarzen, w_x, w_y);
      if (w_jedn == 'B')
        armia_l.dodaj(MAG, w_gracz, engine, obsluga_mapy,
          obsluga_mapy_jednostek, obsluga_zdarzen, w_x, w_y);
      if (w_jedn == 'N')
        armia_l.dodaj(RYCERZ, w_gracz, engine, obsluga_mapy,
          obsluga_mapy_jednostek, obsluga_zdarzen, w_x, w_y);


      if (w_jedn == 'A')
        armia_l.dodaj(ZAMEK_GRACZ_2, w_gracz, engine, obsluga_mapy,
          obsluga_mapy_jednostek, obsluga_zdarzen, w_x, w_y);
      if (w_jedn == 'S')
        armia_l.dodaj(OGNISTY, w_gracz, engine, obsluga_mapy,
          obsluga_mapy_jednostek, obsluga_zdarzen, w_x, w_y);
      if (w_jedn == 'D')
        armia_l.dodaj(SMOK, w_gracz, engine, obsluga_mapy,
          obsluga_mapy_jednostek, obsluga_zdarzen, w_x, w_y);
      if (w_jedn == 'F')
        armia_l.dodaj(TROL, w_gracz, engine, obsluga_mapy,
          obsluga_mapy_jednostek, obsluga_zdarzen, w_x, w_y);
      if (w_jedn == 'G')
        armia_l.dodaj(CIEMNY_RYCERZ, w_gracz, engine, obsluga_mapy,
          obsluga_mapy_jednostek, obsluga_zdarzen, w_x, w_y);
      if (w_jedn == 'H')
        armia_l.dodaj(LORD, w_gracz, engine, obsluga_mapy,
          obsluga_mapy_jednostek, obsluga_zdarzen, w_x, w_y);

      armia_l.zwroc_ostatnia()->zmien_punkty_zycia(w_punkty_zycia);
      armia_l.zwroc_ostatnia()->zmien_d_punkty_zycia(w_d_punkty_zycia);
      armia_l.zwroc_ostatnia()->zmien_punkty_ruchu(w_punkty_ruchu);
      armia_l.zwroc_ostatnia()->zmien_atak(w_atak);
      armia_l.zwroc_ostatnia()->zmien_obrona(w_obrona);
      armia_l.zwroc_ostatnia()->zmien_zwinnosc(w_zwinnosc);
      armia_l.zwroc_ostatnia()->zmien_do_rozdysponowania(w_do_rozdysponowania);
      armia_l.zwroc_ostatnia()->zmien_poziom(w_poziom);
      armia_l.zwroc_ostatnia()->zmien_doswiadczenie(w_doswiadczenie);
      armia_l.zwroc_ostatnia()->zmien_exp(w_exp);
      armia_l.zwroc_ostatnia()->zmien_pieniadze(w_pieniadze);

    }
    fclose(plik_l); // zamkniêcie pliku
  }
  else
  {
    armia_l.dodaj(RYCERZ, 1, engine, obsluga_mapy, obsluga_mapy_jednostek,
      obsluga_zdarzen, 11, 20);
    armia_l.dodaj(ZOLNIERZ, 1, engine, obsluga_mapy, obsluga_mapy_jednostek,
      obsluga_zdarzen, 10, 16);
    armia_l.dodaj(HYDRA, 1, engine, obsluga_mapy, obsluga_mapy_jednostek,
      obsluga_zdarzen, 10, 18);
    armia_l.dodaj(ARCHANIOL, 1, engine, obsluga_mapy, obsluga_mapy_jednostek,
      obsluga_zdarzen, 13, 20);
    armia_l.dodaj(MAG, 1, engine, obsluga_mapy, obsluga_mapy_jednostek,
      obsluga_zdarzen, 13, 18);
    armia_l.dodaj(ZAMEK_GRACZ_1, 1, engine, obsluga_mapy,
      obsluga_mapy_jednostek, obsluga_zdarzen, 9, 20);

    armia_l.dodaj(OGNISTY, 2, engine, obsluga_mapy, obsluga_mapy_jednostek,
      obsluga_zdarzen, 16, 10);
    armia_l.dodaj(SMOK, 2, engine, obsluga_mapy, obsluga_mapy_jednostek,
      obsluga_zdarzen, 17, 9);
    armia_l.dodaj(TROL, 2, engine, obsluga_mapy, obsluga_mapy_jednostek,
      obsluga_zdarzen, 18, 11);
    armia_l.dodaj(CIEMNY_RYCERZ, 2, engine, obsluga_mapy,
      obsluga_mapy_jednostek, obsluga_zdarzen, 20, 10);
    armia_l.dodaj(LORD, 2, engine, obsluga_mapy, obsluga_mapy_jednostek,
      obsluga_zdarzen, 19, 8);
    armia_l.dodaj(ZAMEK_GRACZ_2, 2, engine, obsluga_mapy,
      obsluga_mapy_jednostek, obsluga_zdarzen, 18, 8);
  }

  armia_l.inicjalizuj_mape_jednostek();

  armia_l.zaznacz_pierwsza(tura);




























  ///////////////////////////////////////////////////////////////////////////////////////////////

  // good and evil music for testing purpose only ;]

  muzyka *tablica[2];
  tablica[0] = new muzyka("Pliki_danych/Muzyka/walka.mp3");
  tablica[1] = new muzyka("Pliki_danych/Muzyka/walka_2.mp3");

  // tablica muzyki do przyciskow...

  muzyka *play_l[9];

  play_l[0] = new muzyka("Pliki_danych/Muzyka/1.mp3");
  play_l[1] = new muzyka("Pliki_danych/Muzyka/2.mp3");
  play_l[2] = new muzyka("Pliki_danych/Muzyka/3.mp3");
  play_l[3] = new muzyka("Pliki_danych/Muzyka/4.mp3");
  play_l[4] = new muzyka("Pliki_danych/Muzyka/5.mp3");
  play_l[5] = new muzyka("Pliki_danych/Muzyka/6.mp3");
  play_l[6] = new muzyka("Pliki_danych/Muzyka/7.mp3");
  play_l[7] = new muzyka("Pliki_danych/Muzyka/8.mp3");
  play_l[8] = new muzyka("Pliki_danych/Muzyka/9.mp3");

  // wavy...

  dzwiek *test_wav = NULL;
  dzwiek *test_wav2 = NULL;
  test_wav = new odglosy("Pliki_danych/Odglosy/test.wav");
  test_wav2 = new odglosy("Pliki_danych/Odglosy/test2.wav");
  // test playlisty
  playlista test("Pliki_danych/Muzyka/walka.mp3");
  test.dodaj("Pliki_danych/Muzyka/walka_2.mp3");
  test.dodaj("Pliki_danych/Muzyka/menu.mp3");
  test.dodaj("Pliki_danych/Muzyka/1.mp3");
  test.dodaj("Pliki_danych/Muzyka/2.mp3");
  test.dodaj("Pliki_danych/Muzyka/3.mp3");
  test.przygotuj();

  muzyka *aktualna;
  aktualna = tablica[0];
  //aktualna -> przygotuj();

  /// zmienna pomocnicza dzieki ktorej wybieramy wlasna mp3
  /// jesli ma wartosc -1, gra odtwarza standardowe pliki mp3
  int mp3_s =  - 1;

  bool optymalne_rysowanie;


  // obsluga sieci
  if (multiplayer > 0)
    tura = net_tura;
  while (1)
  {

    if (key[KEY_D])
      dev_mode = !dev_mode;
    optymalne_rysowanie = engine->czy_pokazac();
    if (optymalne_rysowanie)
      engine->zmiana_klatki(true);
    obsluga_mapy->pokaz();



    /// kolejne warunki sprawdzaja czy dany przycik zostal wcisniety
    /// jesli tak, to wskaznik do aktualnie odtwarzanego utworu zostaje
    /// zostaje zmieniony na wybrany plik mp3
    /// zmienna informujaca o tym, czy odtwarzany 
    /// jest standardowy zestaw plikow muzycznych ustawiona zostaje na 1
    /// czyli odtwarzamy wybrane motywy 
    if (key[KEY_1])
    {
      aktualna->zatrzymaj();
      aktualna = play_l[0];
      aktualna->przygotuj();
      mp3_s = 1;
    }

    if (key[KEY_2])
    {
      aktualna->zatrzymaj();
      aktualna = play_l[1];
      aktualna->przygotuj();
      mp3_s = 1;
    }

    if (key[KEY_3])
    {
      aktualna->zatrzymaj();
      aktualna = play_l[2];
      aktualna->przygotuj();
      mp3_s = 1;
    }

    if (key[KEY_4])
    {
      aktualna->zatrzymaj();
      aktualna = play_l[3];
      aktualna->przygotuj();
      mp3_s = 1;
    }

    if (key[KEY_5])
    {
      aktualna->zatrzymaj();
      aktualna = play_l[4];
      aktualna->przygotuj();
      mp3_s = 1;
    }

    if (key[KEY_6])
    {
      aktualna->zatrzymaj();
      aktualna = play_l[5];
      aktualna->przygotuj();
      mp3_s = 1;
    }

    if (key[KEY_7])
    {
      aktualna->zatrzymaj();
      aktualna = play_l[6];
      aktualna->przygotuj();
      mp3_s = 1;
    }

    if (key[KEY_8])
    {
      aktualna->zatrzymaj();
      aktualna = play_l[7];
      aktualna->przygotuj();
      mp3_s = 1;
    }

    if (key[KEY_9])
    {
      aktualna->zatrzymaj();
      aktualna = play_l[8];
      aktualna->przygotuj();
      mp3_s = 1;
    }

    // jesli wcisniemy 0, gra odtwarza standardowe mp3
    if (key[KEY_0])
    {
      aktualna->zatrzymaj();
      aktualna = tablica[tura - 1];
      aktualna->przygotuj();
      mp3_s =  - 1;
    }

    /// jesli wcisniemy X, odtworzone zostaja pliki zapisane w playliscie
    if (key[KEY_X])
    {
      aktualna->zatrzymaj();
      aktualna = test.pobierz_utwor();
      aktualna->przygotuj();
      mp3_s = 1;
    }

    /// jesli wcisniemy Z, zostaje odtworzony koleny utwor z playlisty
    if (key[KEY_Z])
    {
      aktualna->zatrzymaj();
      test = test.przeskocz();
      aktualna = test.pobierz_utwor();
      aktualna->przygotuj();
      mp3_s = 1;
    }

    /// jeœli gra siê jeszcze nie skoñczy³a (co jest równoznaczne z aktywacja menu interfejsu nr 3) 
    /// to wywo³ywana jest funkcja podœwietlaj¹ca pole pod kursorem, funkcja do przesuwania 
    /// kadru mapy i odœwie¿any jest stan przycisków myszy.
    if (menu != 3)
    {
      obsluga_mapy->wskaz_pole(true);
      obsluga_mapy->wysrodkuj();
      obsluga_zdarzen->odswiez();

    }


    /// rysowanie jednostek i w zale¿noœci, który gracz ma aktualnie ruch wywo³ywana 
    /// jest funkcja aktualizuj dla jego jednostek, co pozwala na sterowanie oddzia³em 
    /// i atakowanie innych.
    short liczba_miast;
    liczba_miast = armia_l.aktualizuj(tura);
    if (tura == ai)
      armia_l.zaznacz_pierwsza(ai);
    /// rysowanie interfejsu i minimapy
    engine->rysuj_noc(godzina);
    engine->rysuj_bitmape(B_INTERFEJS, 0, 0, 0, 0, 1024, 768);


    obsluga_mapy->miniatura(39, 622, 2);


    // rysowanie tarczy gracza w zaleznosci od tury
    if (tura == 1)
      engine->rysuj_bitmape(B_DUZA_TARCZA_GRACZ_1, 778, 640, 0, 0, 0, 0);
    else
      engine->rysuj_bitmape(B_DUZA_TARCZA_GRACZ_2, 774, 640, 0, 0, 0, 0);

    /// koniec gry jest wtedy gdy, któryœ z graczy ma zniszczony zamek
    if ((armia_l.zwroc_jednostke(ZAMEK_GRACZ_2)->pobierz_punkty_zycia() <= 0) 
      || (armia_l.zwroc_jednostke(ZAMEK_GRACZ_1)->pobierz_punkty_zycia() <= 0))
    {
      wyjscie.napis("Exit");
      menu = 3;
    }

    srand(time(NULL));

    /// Interfejs  gry oparty jest na switchu, który w zale¿noœci od wartoœci 
    /// zmiennej menu wyœwietla inny widok na dole ekranu. 

    /// wyswietlanie okna

    if (tura == ai || tura != multi_tura)
      obsluga_zdarzen->wyswietl_okno(0);

    switch (obsluga_zdarzen->zwroc_okno())
    {
      case 1:
        if (obsluga_menu->okno(320, 216, (char*)get_config_string("teksty", 
          "foodfound", 0), (char*)get_config_string("teksty", "great", "Not Read"), " ")
          == 0)
          obsluga_zdarzen->wyswietl_okno(0);
        engine->rysuj_bitmape(MIESO, 470, 245, 0, 0, 0, 0);
        break;
      case 2:
        if (obsluga_menu->okno(320, 216, (char*)get_config_string("teksty", 
          "goldfound", 0), (char*)get_config_string("teksty", "great", "Not Read"), " ")
          == 0)
          obsluga_zdarzen->wyswietl_okno(0);
        engine->rysuj_bitmape(MONETY, 470, 235, 0, 0, 0, 0);
        break;
      case 3:
        if (obsluga_menu->okno(320, 216, (char*)get_config_string("teksty", 
          "lavaburns", 0), (char*)get_config_string("teksty", "youch", "Not Read"), " ")
          == 0)
          obsluga_zdarzen->wyswietl_okno(0);
        break;
      case 4:
        if (obsluga_menu->okno(320, 216, (char*)get_config_string("teksty", 
          "herobuild", 0), (char*)get_config_string("teksty", "great", "Not Read"), " ")
          == 0)
          obsluga_zdarzen->wyswietl_okno(0);
        break;
    }



    /// SZTUCZNA INTELIGENCJA
    if (tura == ai)
    {

      //menu=0;
      /// jesli ma kase to kupuje technologie

      if (!gracz[tura - 1].sprawdz_technologie(5) && gracz[tura -
        1].pobierz_zloto() >= 10000)
      {
        gracz[tura - 1].kup_technologie(5);
        gracz[tura - 1].zaplac(8000);
      }

      if (!gracz[tura - 1].sprawdz_technologie(4) && gracz[tura -
        1].pobierz_zloto() >= 5500)
      {
        gracz[tura - 1].kup_technologie(4);
        gracz[tura - 1].zaplac(4000);
      }

      if (!gracz[tura - 1].sprawdz_technologie(3) && gracz[tura -
        1].pobierz_zloto() >= 3000)
      {
        gracz[tura - 1].kup_technologie(3);
        gracz[tura - 1].zaplac(2000);
      }

      if (!gracz[tura - 1].sprawdz_technologie(2) && gracz[tura -
        1].pobierz_zloto() >= 1500)
      {
        gracz[tura - 1].kup_technologie(2);
        gracz[tura - 1].zaplac(1000);
      }







      /// kupuje jednostki

      short ai_j1;
      short ai_j2;
      short ai_j3;
      short ai_j4;
      short ai_j5;


      bool t1, t2, t3, t4;
      t1 = gracz[tura - 1].sprawdz_technologie(2);
      t2 = gracz[tura - 1].sprawdz_technologie(3);
      t3 = gracz[tura - 1].sprawdz_technologie(4);
      t4 = gracz[tura - 1].sprawdz_technologie(5);

      ai_j1 = 90-t1 * 10-t2 * 10-t3 * 10-t4 * 10;
      ai_j2 = 90-t2 * 15-t3 * 15-t4 * 15;
      ai_j3 = 90-t3 * 20-t4 * 25;
      ai_j4 = 90-t4 * 45;
      ai_j5 = 90;

      if ((rand() % 100 < ai_j1 && gracz[tura - 1].pobierz_zloto() >= 200) || 
        (rand() % 100 < ai_j2 && gracz[tura - 1].pobierz_zloto() >= 300) || 
        (rand() % 100 < ai_j3 && gracz[tura - 1].pobierz_zloto() >= 400) || 
        (rand() % 100 < ai_j4 && gracz[tura - 1].pobierz_zloto() >= 600) || 
        (rand() % 100 < ai_j5 && gracz[tura - 1].pobierz_zloto() >= 900)

      )
      {



        jednostka *ai_kup_jednostke;
        jednostka *zamek;

        if (tura == 1)
        {
          ai_kup_jednostke = do_kupienia_1.zwroc_jednostke(ZOLNIERZ);
          if (gracz[tura - 1].sprawdz_technologie(2) && gracz[tura -
            1].pobierz_zloto() >= 150)
            ai_kup_jednostke = do_kupienia_1.zwroc_jednostke(RYCERZ);

          if (gracz[tura - 1].sprawdz_technologie(3) && gracz[tura -
            1].pobierz_zloto() >= 200)
            ai_kup_jednostke = do_kupienia_1.zwroc_jednostke(MAG);

          if (gracz[tura - 1].sprawdz_technologie(4) && gracz[tura -
            1].pobierz_zloto() >= 300)
            ai_kup_jednostke = do_kupienia_1.zwroc_jednostke(HYDRA);

          if (gracz[tura - 1].sprawdz_technologie(5) && gracz[tura -
            1].pobierz_zloto() >= 450)
            ai_kup_jednostke = do_kupienia_1.zwroc_jednostke(ARCHANIOL);

          zamek = armia_l.zwroc_jednostke(ZAMEK_GRACZ_1);
        }
        else
        {
          ai_kup_jednostke = do_kupienia_2.zwroc_jednostke(CIEMNY_RYCERZ);
          if (gracz[tura - 1].sprawdz_technologie(2) && gracz[tura -
            1].pobierz_zloto() >= 150)
            ai_kup_jednostke = do_kupienia_2.zwroc_jednostke(OGNISTY);

          if (gracz[tura - 1].sprawdz_technologie(3) && gracz[tura -
            1].pobierz_zloto() >= 200)
            ai_kup_jednostke = do_kupienia_2.zwroc_jednostke(LORD);

          if (gracz[tura - 1].sprawdz_technologie(4) && gracz[tura -
            1].pobierz_zloto() >= 300)
            ai_kup_jednostke = do_kupienia_2.zwroc_jednostke(SMOK);

          if (gracz[tura - 1].sprawdz_technologie(5) && gracz[tura -
            1].pobierz_zloto() >= 500)
            ai_kup_jednostke = do_kupienia_2.zwroc_jednostke(TROL);

          zamek = armia_l.zwroc_jednostke(ZAMEK_GRACZ_2);
        }

        if (gracz[tura - 1].pobierz_zloto() >= ai_kup_jednostke->pobierz_cene())
        {
          armia_l.dodaj(ai_kup_jednostke->pobierz_wyglad(), tura, engine,
            obsluga_mapy, obsluga_mapy_jednostek, obsluga_zdarzen, zamek
            ->pobierz_x(), zamek->pobierz_y());

          gracz[tura - 1].zaplac(ai_kup_jednostke->pobierz_cene());
          gracz[tura - 1].zwieksz_jednostki();
          armia_l.zwroc_ostatnia()->czysc_mape_przejsc();
        }

      }


    }
    else
    {
      //if(menu==0) menu=1;
    }


    switch (menu)
    {
      case 8:
        {
          engine->pisz((char*)get_config_string("teksty", "waitturn", "Not Read"), 435,
            621,  - 1, makecol(0, 0, 0));
          break;
        }
        // menu glowne gry
      case 1:
        /// Sprawdzany jest stan punktów do rozdysponowania aktywnej jednostki jeœli jest 
        /// wiêkszy ni¿ 0 to wyœwietlaj¹ siê przyciski pozwalaj¹ce zwiêkszyæ atrybuty danego 
        /// oddzia³u. Oparte jest to na obiektach klasy przycisk.
        if (armia_l.zwroc_aktywna()->pobierz_do_rozdysponowania() > 0)
        {
          armia_l.zwroc_aktywna()->wyswietl_info(true, false);
          zwieksz_atak.rysuj();
          if (zwieksz_atak.zdarzenie() == ZWOLNIENIE)
          {
            armia_l.zwroc_aktywna()->zwieksz_atak();
            armia_l.zwroc_aktywna()->zmniejsz_do_rozdysponowania();
          }
          zwieksz_obrone.rysuj();
          if (zwieksz_obrone.zdarzenie() == ZWOLNIENIE)
          {
            armia_l.zwroc_aktywna()->zwieksz_obrone();
            armia_l.zwroc_aktywna()->zmniejsz_do_rozdysponowania();
          }
          zwieksz_zwinnosc.rysuj();
          if (zwieksz_zwinnosc.zdarzenie() == ZWOLNIENIE)
          {
            armia_l.zwroc_aktywna()->zwieksz_zwinnosc();
            armia_l.zwroc_aktywna()->zmniejsz_do_rozdysponowania();
          }
          engine->pisz((char*)get_config_string("teksty", "disposepoints", "Not Read"),
            384, 614, armia_l.zwroc_aktywna()->pobierz_do_rozdysponowania(),
            makecol(0, 0, 0), false);
        }
        /// jesli jednostka zgarnela jakis lup to dodawana jest ta suma do skarbca
        else if (armia_l.zwroc_aktywna()->pobierz_pieniadze() > 0)
        {
          gracz[tura - 1].zaplac( - armia_l.zwroc_aktywna()->pobierz_pieniadze()
            );
          armia_l.zwroc_aktywna()->zmien_pieniadze(0);
        }

        /// W koñcu jeœli ¿aden z tych warunków nie zosta³ spe³niony wyœwietlane jest 
        /// menu g³ówne, z widokiem jednostki, jej statystykami i opisem. Dostêpne s¹ 
        /// opcje kup, wyjscie, koniec tury.
        else
        {
          // wypisywanie danych o aktywnej jednostce
          armia_l.zwroc_aktywna()->wyswietl_info(true, true);

          // obsluga przyciskow
          wyjscie.rysuj();
          kup.rysuj();
          /// Przycisk ulecz wyœwietlany jest tylko, gdy jednostka jest zraniona i znajduje sie w poblizu ("dotyka")  zamku/miasta
          if ((armia_l.zwroc_aktywna()->pobierz_punkty_zycia() > 0 &&
            armia_l.zwroc_aktywna()->pobierz_punkty_zycia() <
            armia_l.zwroc_aktywna()->pobierz_d_punkty_zycia() &&
            armia_l.zwroc_aktywna()->sprawdz_sasiadow("zamek")) || 
            (armia_l.zwroc_aktywna()->pobierz_punkty_zycia() > 0 &&
            armia_l.zwroc_aktywna()->pobierz_punkty_zycia() <
            armia_l.zwroc_aktywna()->pobierz_d_punkty_zycia() &&
            armia_l.zwroc_aktywna()->sprawdz_sasiadow("miasto")))
          {
            ulecz.rysuj();
            if ((ulecz.zdarzenie() == ZWOLNIENIE && gracz[tura -
              1].pobierz_zloto() >= armia_l.zwroc_aktywna()->pobierz_cene() / 4)
              || (tura == ai && armia_l.zwroc_aktywna()->pobierz_punkty_zycia()
              + 30 < armia_l.zwroc_aktywna()->pobierz_d_punkty_zycia() &&
              gracz[tura - 1].pobierz_zloto() >= armia_l.zwroc_aktywna()
              ->pobierz_cene() / 4))
            {
              gracz[tura - 1].zaplac(armia_l.zwroc_aktywna()->pobierz_cene() /
                4);
              armia_l.zwroc_aktywna()->ulecz(10);
            }
          }


jednostka *tmp_zam;
jednostka *tmp_rob;
tmp_rob = armia_l.zwroc_aktywna();
if(tura == 1 )tmp_zam = armia_l.zwroc_jednostke(ZAMEK_GRACZ_1);
else if(tura == 2 )tmp_zam = armia_l.zwroc_jednostke(ZAMEK_GRACZ_2);
if(tmp_rob->pobierz_wyglad() == ROBOTNIK_1 || tmp_rob->pobierz_wyglad() == ROBOTNIK_2)
{
    if (tmp_rob->pobierz_x() != tmp_zam->pobierz_x() || tmp_rob->pobierz_y() != tmp_zam->pobierz_y())
    {
      buduj.rysuj();
      if(buduj.zdarzenie() == ZWOLNIENIE) menu=7;
    }
}


          if (armia_l.zwroc_jednostke(ZAMEK_GRACZ_1)->pobierz_punkty_zycia() <
            armia_l.zwroc_jednostke(ZAMEK_GRACZ_1)->pobierz_d_punkty_zycia() &&
            armia_l.zwroc_aktywna()->sprawdz_sasiadow("zamek") &&
            armia_l.zwroc_aktywna()->pobierz_wyglad() == ROBOTNIK_1)
          {
            napraw.rysuj();
            if ((napraw.zdarzenie() == ZWOLNIENIE && gracz[tura -
              1].pobierz_zloto() >= armia_l.zwroc_jednostke(ZAMEK_GRACZ_1)
              ->pobierz_cene() / 4) || (tura == ai && armia_l.zwroc_jednostke
              (ZAMEK_GRACZ_1)->pobierz_punkty_zycia() + 30 <
              armia_l.zwroc_jednostke(ZAMEK_GRACZ_1)->pobierz_d_punkty_zycia()
              && gracz[tura - 1].pobierz_zloto() >= armia_l.zwroc_jednostke
              (ZAMEK_GRACZ_1)->pobierz_cene() / 4))
            {
              gracz[tura - 1].zaplac(armia_l.zwroc_jednostke(ZAMEK_GRACZ_1)
                ->pobierz_cene() / 4);
              armia_l.zwroc_jednostke(ZAMEK_GRACZ_1)->ulecz(10);
            }
          }

          if (armia_l.zwroc_jednostke(ZAMEK_GRACZ_2)->pobierz_punkty_zycia() <
            armia_l.zwroc_jednostke(ZAMEK_GRACZ_2)->pobierz_d_punkty_zycia() &&
            armia_l.zwroc_aktywna()->sprawdz_sasiadow("zamek") &&
            armia_l.zwroc_aktywna()->pobierz_wyglad() == ROBOTNIK_2)
          {
            napraw.rysuj();
            if ((napraw.zdarzenie() == ZWOLNIENIE && gracz[tura -
              1].pobierz_zloto() >= armia_l.zwroc_jednostke(ZAMEK_GRACZ_2)
              ->pobierz_cene() / 4) || (tura == ai && armia_l.zwroc_jednostke
              (ZAMEK_GRACZ_2)->pobierz_punkty_zycia() + 30 <
              armia_l.zwroc_jednostke(ZAMEK_GRACZ_2)->pobierz_d_punkty_zycia()
              && gracz[tura - 1].pobierz_zloto() >= armia_l.zwroc_jednostke
              (ZAMEK_GRACZ_2)->pobierz_cene() / 4))
            {
              gracz[tura - 1].zaplac(armia_l.zwroc_jednostke(ZAMEK_GRACZ_2)
                ->pobierz_cene() / 4);
              armia_l.zwroc_jednostke(ZAMEK_GRACZ_2)->ulecz(10);
            }
          }


          /// Przycisk trenuj wyœwietlany jest tylko, gdy masz kase
          if (gracz[tura - 1].pobierz_zloto() >= armia_l.zwroc_aktywna()
            ->pobierz_cene() / 2 && armia_l.zwroc_aktywna()->sprawdz_sasiadow(
            "zamek"))
          {
            trenuj.rysuj();
            if (trenuj.zdarzenie() == ZWOLNIENIE)
            {
              gracz[tura - 1].zaplac(armia_l.zwroc_aktywna()->pobierz_cene() /
                2);
              armia_l.zwroc_aktywna()->trenuj(25);
            }
          }

          /// Przycisk kup jednostke zmienia aktywne menu na 2 (czyli menu kupowania jednostek).
          if (kup.zdarzenie() == ZWOLNIENIE)
            menu = 5;

          if (wyjscie.zdarzenie() == ZWOLNIENIE)
          {
            engine->zmiana_klatki(true);
            podmenu = 1;
          }
          if (podmenu == 1)
          {
            engine->rysuj_bitmape(INGAMEMENU, 410, 115, 100, 100, 0, 0);
            if (wyjscie2.zdarzenie() == ZWOLNIENIE)
            {
              podmenu = 0;
              menu = 4;
            }

            if (powrot3.zdarzenie() == ZWOLNIENIE)
            {
              engine->zmiana_klatki(true);
              podmenu = 0;
            }


            if (zapis1.zdarzenie() == ZWOLNIENIE)
            {

              FILE *plik_s = fopen("Zapisane_gry/1.sav", "w");

              fprintf(plik_s, "%s", obsluga_mapy->zwroc_nazwe());

              fprintf(plik_s, " %d %f %d %d", tura, godzina,
                gracz[0].pobierz_zloto(), gracz[1].pobierz_zloto());

              fprintf(plik_s, " %d %d %d %d", gracz[0].sprawdz_technologie(2),
                gracz[0].sprawdz_technologie(3), gracz[0].sprawdz_technologie(4)
                , gracz[0].sprawdz_technologie(5));
              fprintf(plik_s, " %d %d %d %d ", gracz[1].sprawdz_technologie(2),
                gracz[1].sprawdz_technologie(3), gracz[1].sprawdz_technologie(4)
                , gracz[1].sprawdz_technologie(5));
              fclose(plik_s);

              armia_l.zapisz_jednostki(1);
              podmenu = 0;
            }

            if (zapis2.zdarzenie() == ZWOLNIENIE)
            {
              FILE *plik_s = fopen("Zapisane_gry/2.sav", "w");
              fprintf(plik_s, "%s", obsluga_mapy->zwroc_nazwe());
              fprintf(plik_s, " %d %f %d %d", tura, godzina,
                gracz[0].pobierz_zloto(), gracz[1].pobierz_zloto());

              fprintf(plik_s, " %d %d %d %d", gracz[0].sprawdz_technologie(2),
                gracz[0].sprawdz_technologie(3), gracz[0].sprawdz_technologie(4)
                , gracz[0].sprawdz_technologie(5));
              fprintf(plik_s, " %d %d %d %d ", gracz[1].sprawdz_technologie(2),
                gracz[1].sprawdz_technologie(3), gracz[1].sprawdz_technologie(4)
                , gracz[1].sprawdz_technologie(5));
              fclose(plik_s);

              armia_l.zapisz_jednostki(2);
              podmenu = 0;
            }

            if (zapis3.zdarzenie() == ZWOLNIENIE)
            {
              FILE *plik_s = fopen("Zapisane_gry/3.sav", "w");
              fprintf(plik_s, "%s", obsluga_mapy->zwroc_nazwe());
              fprintf(plik_s, " %d %f %d %d", tura, godzina,
                gracz[0].pobierz_zloto(), gracz[1].pobierz_zloto());

              fprintf(plik_s, " %d %d %d %d", gracz[0].sprawdz_technologie(2),
                gracz[0].sprawdz_technologie(3), gracz[0].sprawdz_technologie(4)
                , gracz[0].sprawdz_technologie(5));
              fprintf(plik_s, " %d %d %d %d ", gracz[1].sprawdz_technologie(2),
                gracz[1].sprawdz_technologie(3), gracz[1].sprawdz_technologie(4)
                , gracz[1].sprawdz_technologie(5));
              fclose(plik_s);

              armia_l.zapisz_jednostki(3);
              podmenu = 0;
            }

            if (zapis4.zdarzenie() == ZWOLNIENIE)
            {
              FILE *plik_s = fopen("Zapisane_gry/4.sav", "w");
              fprintf(plik_s, "%s", obsluga_mapy->zwroc_nazwe());
              fprintf(plik_s, " %d %f %d %d", tura, godzina,
                gracz[0].pobierz_zloto(), gracz[1].pobierz_zloto());

              fprintf(plik_s, " %d %d %d %d", gracz[0].sprawdz_technologie(2),
                gracz[0].sprawdz_technologie(3), gracz[0].sprawdz_technologie(4)
                , gracz[0].sprawdz_technologie(5));
              fprintf(plik_s, " %d %d %d %d ", gracz[1].sprawdz_technologie(2),
                gracz[1].sprawdz_technologie(3), gracz[1].sprawdz_technologie(4)
                , gracz[1].sprawdz_technologie(5));
              fclose(plik_s);

              armia_l.zapisz_jednostki(4);
              podmenu = 0;
            }

            if (zapis5.zdarzenie() == ZWOLNIENIE)
            {
              FILE *plik_s = fopen("Zapisane_gry/5.sav", "w");
              fprintf(plik_s, "%s", obsluga_mapy->zwroc_nazwe());
              fprintf(plik_s, " %d %f %d %d", tura, godzina,
                gracz[0].pobierz_zloto(), gracz[1].pobierz_zloto());

              fprintf(plik_s, " %d %d %d %d", gracz[0].sprawdz_technologie(2),
                gracz[0].sprawdz_technologie(3), gracz[0].sprawdz_technologie(4)
                , gracz[0].sprawdz_technologie(5));
              fprintf(plik_s, " %d %d %d %d ", gracz[1].sprawdz_technologie(2),
                gracz[1].sprawdz_technologie(3), gracz[1].sprawdz_technologie(4)
                , gracz[1].sprawdz_technologie(5));
              fclose(plik_s);

              armia_l.zapisz_jednostki(5);
              podmenu = 0;
            }

            zapis1.rysuj();
            zapis2.rysuj();
            zapis3.rysuj();
            zapis4.rysuj();
            zapis5.rysuj();
            wyjscie2.rysuj();
            powrot3.rysuj();
          }
        }
        break;
        // menu kupowania jednostek
      case 2:
        powrot.rysuj();
        if (gracz[tura - 1].sprawdz_technologie(indeks_wybrana[tura - 1]))
          kup.rysuj();
        else
          niedostepna.rysuj();
        /// przy ostatniej nie wyswietla przycisku nastepna
        if (indeks_wybrana[tura - 1] < 5)
          nastepna.rysuj();
        /// przy pierwszej nie wyswietla przycisku poprzednia
        if (indeks_wybrana[tura - 1] > 0)
          poprzednia.rysuj();
        jednostka *wybrana;
        wybrana = NULL;
        /// Wybrana jednostka jest wskaŸnikiem do obiektu klasy jednostka i podstawiana 
        /// jest pod ni¹ jednostka w zale¿noœci od tury (czyli od gracza) i od indeksu 
        /// jednostki wybranej.
        if (tura == 1)
        {
          if (indeks_wybrana[tura - 1] == 0)
            wybrana = do_kupienia_1.zwroc_jednostke(ROBOTNIK_1);
          if (indeks_wybrana[tura - 1] == 1)
            wybrana = do_kupienia_1.zwroc_jednostke(ZOLNIERZ);
          if (indeks_wybrana[tura - 1] == 2)
            wybrana = do_kupienia_1.zwroc_jednostke(RYCERZ);
          if (indeks_wybrana[tura - 1] == 3)
            wybrana = do_kupienia_1.zwroc_jednostke(MAG);
          if (indeks_wybrana[tura - 1] == 4)
            wybrana = do_kupienia_1.zwroc_jednostke(HYDRA);
          if (indeks_wybrana[tura - 1] == 5)
            wybrana = do_kupienia_1.zwroc_jednostke(ARCHANIOL);
        }

        if (tura == 2)
        {
          if (indeks_wybrana[tura - 1] == 0)
            wybrana = do_kupienia_2.zwroc_jednostke(ROBOTNIK_2);
          if (indeks_wybrana[tura - 1] == 1)
            wybrana = do_kupienia_2.zwroc_jednostke(CIEMNY_RYCERZ);
          if (indeks_wybrana[tura - 1] == 2)
            wybrana = do_kupienia_2.zwroc_jednostke(OGNISTY);
          if (indeks_wybrana[tura - 1] == 3)
            wybrana = do_kupienia_2.zwroc_jednostke(LORD);
          if (indeks_wybrana[tura - 1] == 4)
            wybrana = do_kupienia_2.zwroc_jednostke(SMOK);
          if (indeks_wybrana[tura - 1] == 5)
            wybrana = do_kupienia_2.zwroc_jednostke(TROL);
        }
        /// wyœwietlane s¹ informacje o jednostce do kupienia
        wybrana->wyswietl_info(true, true);

        /// Obs³ugiwany jest przycisk powrót, który zmienia menu na 1.
        if (powrot.zdarzenie() == ZWOLNIENIE)
          menu = 1;

        if (nastepna.zdarzenie() == ZWOLNIENIE)
          indeks_wybrana[tura - 1]++;
        if (poprzednia.zdarzenie() == ZWOLNIENIE)
          indeks_wybrana[tura - 1]--;

        /// Sprawdzane s¹ indeksy aktualnie wybranej jednostki tak, aby nie wyjœæ poza zakres.
        if (indeks_wybrana[tura - 1] > 5)
          indeks_wybrana[tura - 1] = 5;
        if (indeks_wybrana[tura - 1] < 0)
          indeks_wybrana[tura - 1] = 0;

        /// Obs³ugiwany jest przycisk kup jednostke. Sprawdzane jest w tym samym czasie 
        /// czy gracz ma wystarczaj¹co du¿o z³ota w skarbcu na zakup i dodawana jest 
        /// wybrana jednostka w miejscu zamku gracza, który ma aktualnie ruch. 
        /// Przy tym odtwarzany jest dŸwiêk w zaleznosci od strony, która gramy
        /// sprawdzana jest takze dostepna technologia
        if (kup.zdarzenie() == ZWOLNIENIE && gracz[tura - 1].pobierz_zloto() >=
          wybrana->pobierz_cene() && gracz[tura - 1].sprawdz_technologie
          (indeks_wybrana[tura - 1]))
        {
          /// wybor zamku w ktorym ma sie pojawic kupiona jednostka
          jednostka *zamek;
          if (tura == 1)
          {
            zamek = armia_l.zwroc_jednostke(ZAMEK_GRACZ_1);
            if (obsluga_menu->zwroc_ustawienia(1) == 1)
              test_wav->odtwarzaj();
          }
          else
          {
            zamek = armia_l.zwroc_jednostke(ZAMEK_GRACZ_2);
            if (obsluga_menu->zwroc_ustawienia(1) == 1)
              test_wav2->odtwarzaj();
          }
          // obsluga sieci
          char kom_add[100];
          sprintf(kom_add, "UNDEF");
          int pom_czy_heros = czy_heros();
          sprintf(kom_add, "ADD %d %d %d %d %d", zamek->pobierz_x(), zamek
            ->pobierz_y(), wybrana->pobierz_wyglad(), tura, pom_czy_heros);
          switch (multiplayer)
          {
          case 1:
            if (strcmp(kom_add, "UNDEF") != 0)
              klient->wyslijZapytanie(kom_add);

            break;
          case 2:
            if (strcmp(kom_add, "UNDEF") != 0)
              serwer->wyslijZapytanie(kom_add);

            break;
          }

          armia_l.dodaj(wybrana->pobierz_wyglad(), tura, engine, obsluga_mapy,
            obsluga_mapy_jednostek, obsluga_zdarzen, zamek->pobierz_x(), zamek
            ->pobierz_y(), pom_czy_heros);

          gracz[tura - 1].zaplac(wybrana->pobierz_cene());
          gracz[tura - 1].zwieksz_jednostki();
          armia_l.zwroc_ostatnia()->czysc_mape_przejsc();


        }
        break;
        /// menu konca gry
        /// Wyœwietlany jest komunikat koñca gry oraz w zale¿noœci, który zamek zosta³ 
        /// zniszczony komunikat o zwyciêstwie danego gracza.
      case 3:
        {
          wyjscie.rysuj();
          if (wyjscie.zdarzenie() == ZWOLNIENIE)
            exit( - 1);
          engine->pisz((char*)get_config_string("teksty", "endofgame", "Not Read"), 435,
            621,  - 1, makecol(0, 0, 0));

          if (armia_l.zwroc_jednostke(ZAMEK_GRACZ_1)->pobierz_punkty_zycia() <=
            0)
            engine->pisz((char*)get_config_string("teksty", "yellowwins", "Not Read"),
              435, 653,  - 1, makecol(255, 255, 0));
          else if (armia_l.zwroc_jednostke(ZAMEK_GRACZ_2)->pobierz_punkty_zycia
            () <= 0)
            engine->pisz((char*)get_config_string("teksty", "bluewins", "Not Read"), 435,
              653,  - 1, makecol(0, 0, 255));
          ;

          break;
        }
        // menu wychodzenia
      case 4:
        {

          /// Wyœwietlana jest przezroczysta bitmapa, na której napisany jest tekst 
          /// pytaj¹cy o potwierdzenie wyjœcia.

          ///Przycisk ok zakañcza program, natomiast przycisk anuluj zmienia menu na 1 
          /// czyli wraca do menu g³ównego.
          short co_zwraca = 2;
          co_zwraca = obsluga_menu->okno(320, 216, (char*)get_config_string(
            "teksty", "reallyquit", "Not Read"), (char*)get_config_string("teksty", "ok",
            0), (char*)get_config_string("teksty", "cancel", "Not Read"));
          if (co_zwraca == 0)
          {
            if(multiplayer==1) klient->wyslijZapytanie("EXIT");
            else if(multiplayer==2) serwer->wyslijZapytanie("EXIT");
            exit( - 1);
          }
          if (co_zwraca == 1)
            menu = 1;

          // wypisywanie danych o aktywnej jednostce
          armia_l.zwroc_aktywna()->wyswietl_info(true, true);

          /// obsluga przyciskow
          wyjscie.rysuj();
          kup.rysuj();


          break;
        }

        // menu budowania
      case 7:
            {

przycisk_zdarzenie pz_tmp1, pz_tmp2;
nazwa_pola wybrana;
jednostka *tmp_rob;
tmp_rob = armia_l.zwroc_aktywna();
                
if( tmp_rob->pobierz_wyglad()==ROBOTNIK_1 || tmp_rob->pobierz_wyglad()==ROBOTNIK_2)
{               
    if( gracz[tura - 1].pobierz_zloto() >=
    armia_l.zwroc_jednostke(MIASTO_1)->pobierz_cene() )
    {
        buduj_miasto.rysuj();
        pz_tmp1 = buduj_miasto.zdarzenie();
    }
    if( gracz[tura - 1].pobierz_zloto() >=
    armia_l.zwroc_jednostke(WIEZA_1)->pobierz_cene() )
    {
        buduj_wieze.rysuj();
        pz_tmp2 = buduj_wieze.zdarzenie();
    }    
}
    powrot.rysuj();

  if( pz_tmp1 == ZWOLNIENIE && tura==1) wybrana=MIASTO_1;
  if( pz_tmp1 == ZWOLNIENIE && tura==2) wybrana=MIASTO_2;
  if( pz_tmp2 == ZWOLNIENIE && tura==1) wybrana=WIEZA_1;
  if( pz_tmp2 == ZWOLNIENIE && tura==2) wybrana=WIEZA_2;

  if (pz_tmp1 == ZWOLNIENIE || pz_tmp2 == ZWOLNIENIE)
  {
        menu = 1;
    tmp_rob->zmien_punkty_zycia(0);
    armia_l.dodaj(wybrana, tura, engine, obsluga_mapy, obsluga_mapy_jednostek,
      obsluga_zdarzen, tmp_rob->pobierz_x(), tmp_rob->pobierz_y());
      
          gracz[tura - 1].zaplac(armia_l.zwroc_jednostke(wybrana)->pobierz_cene());
          gracz[tura - 1].zwieksz_jednostki();

    // obsluga sieci
    char kom_add[100];
    char kom_kill[100];
    char kom_updt[100];

    sprintf(kom_add, "ADD %d %d %d %d %d", tmp_rob->pobierz_x(), tmp_rob
      ->pobierz_y(), wybrana, tura, false);
    sprintf(kom_updt, "UPDT %d %d %d %d %d %d %d %d %d %d %d %d %d", tmp_rob->pobierz_id(), 0,
      0, 0, 0,0,0,0,0,0,0);      
    sprintf(kom_kill, "KILL %d %d", tmp_rob->pobierz_x(), tmp_rob->pobierz_y());
    switch (multiplayer)
    {
      case 1:
          klient->wyslijZapytanie(kom_updt);
          klient->wyslijZapytanie(kom_kill);
          klient->wyslijZapytanie(kom_add);
        break;
      case 2:
          serwer->wyslijZapytanie(kom_updt);  
          serwer->wyslijZapytanie(kom_kill);
          serwer->wyslijZapytanie(kom_add);
        break;
    }
    armia_l.zaznacz_pierwsza(tura);
  }


  



                
                if (powrot.zdarzenie() == ZWOLNIENIE)
                    menu = 1;                
                break;
            }
        /// menu kupowania
      case 5:
        {
          kup_jednostke.rysuj();
          kup_technologie.rysuj();
          powrot.rysuj();

          if (kup_jednostke.zdarzenie() == ZWOLNIENIE)
            menu = 2;
          if (kup_technologie.zdarzenie() == ZWOLNIENIE)
            menu = 6;
          if (powrot.zdarzenie() == ZWOLNIENIE)
            menu = 1;
          break;
        }
        /// menu kupowania technologii
      case 6:
        {
          if (!gracz[tura - 1].sprawdz_technologie(2))
            technologia_1.rysuj();
          else
            engine->pisz((char*)get_config_string("teksty", "bought", "Not Read"), 247,
              618,  - 1, makecol(0, 200, 0));

          if (!gracz[tura - 1].sprawdz_technologie(3))
            technologia_2.rysuj();
          else
            engine->pisz((char*)get_config_string("teksty", "bought", "Not Read"), 247,
              642,  - 1, makecol(0, 200, 0));

          if (!gracz[tura - 1].sprawdz_technologie(4))
            technologia_3.rysuj();
          else
            engine->pisz((char*)get_config_string("teksty", "bought", "Not Read"), 247,
              666,  - 1, makecol(0, 200, 0));

          if (!gracz[tura - 1].sprawdz_technologie(5))
            technologia_4.rysuj();
          else
            engine->pisz((char*)get_config_string("teksty", "bought", "Not Read"), 247,
              690,  - 1, makecol(0, 200, 0));

          if (tura == 1)
          {
            engine->pisz((char*)get_config_string("teksty", "allows1", "Not Read"), 352,
              618,  - 1, makecol(0, 0, 0), false);
            engine->pisz((char*)get_config_string("teksty", "allows2", "Not Read"), 352,
              642,  - 1, makecol(0, 0, 0), false);
            engine->pisz((char*)get_config_string("teksty", "allows3", "Not Read"), 352,
              666,  - 1, makecol(0, 0, 0), false);
            engine->pisz((char*)get_config_string("teksty", "allows4", "Not Read"), 352,
              690,  - 1, makecol(0, 0, 0), false);
          }
          else
          {
            engine->pisz((char*)get_config_string("teksty", "allows5", "Not Read"), 352,
              618,  - 1, makecol(0, 0, 0), false);
            engine->pisz((char*)get_config_string("teksty", "allows6", "Not Read"), 352,
              642,  - 1, makecol(0, 0, 0), false);
            engine->pisz((char*)get_config_string("teksty", "allows7", "Not Read"), 352,
              666,  - 1, makecol(0, 0, 0), false);
            engine->pisz((char*)get_config_string("teksty", "allows8", "Not Read"), 352,
              690,  - 1, makecol(0, 0, 0), false);
          }

          powrot.rysuj();

          if (technologia_1.zdarzenie() == ZWOLNIENIE && gracz[tura -
            1].pobierz_zloto() >= 1000)
          {
            gracz[tura - 1].kup_technologie(2);
            gracz[tura - 1].zaplac(1000);
          }
          if (technologia_2.zdarzenie() == ZWOLNIENIE && gracz[tura -
            1].pobierz_zloto() >= 2000)
          {
            gracz[tura - 1].kup_technologie(3);
            gracz[tura - 1].zaplac(2000);
          }
          if (technologia_3.zdarzenie() == ZWOLNIENIE && gracz[tura -
            1].pobierz_zloto() >= 4000)
          {
            gracz[tura - 1].kup_technologie(4);
            gracz[tura - 1].zaplac(4000);
          }
          if (technologia_4.zdarzenie() == ZWOLNIENIE && gracz[tura -
            1].pobierz_zloto() >= 8000)
          {
            gracz[tura - 1].kup_technologie(5);
            gracz[tura - 1].zaplac(8000);
          }

          if (powrot.zdarzenie() == ZWOLNIENIE)
            menu = 5;

        }

    }

    //przycisk_zdarzenie pz_koniec_tury=NORMALNY;
    if (tura == ai){}
    else if (multi_tura > 0)
    {
      if (tura == multi_tura)
      {
        koniec_tury.rysuj();

        /// Licznik czasu dla tury

        engine->pisz("%d", 762, 747, godzina);
        engine->pisz("%d", 847, 747, godzina);
        zablokowane = false;
      }
      else
      {
        zablokowane = true;
        menu = 8;
      }

    }
    else
    {
        engine->pisz("%d", 762, 747, godzina);
        engine->pisz("%d", 847, 747, godzina);
        koniec_tury.rysuj();
    }

    /// Przycisk koniec tury, wywo³uje funkcje koñcz¹c¹ ture, a tak¿e dodaje do skarbca 25 gp.
    // z czasem tury if((koniec_tury.zdarzenie()==ZWOLNIENIE || 120-(120-w_czas_tury)-(clock()/clk)-(czas_tury/clk)<=0) || (armia_l.czy_koniec_tury(ai) && tura==ai) )
    if ((koniec_tury.zdarzenie() == ZWOLNIENIE) || kon_tur || 
      (armia_l.czy_koniec_tury(ai) && tura == ai))
    {
      /// zerowanie zegara
      godzina += 0.5;
      if (godzina > 23)
        godzina = 0;

      /// dodawanie 25gp co ture do skarbca i 10gp za kazde miasto
      gracz[tura - 1].zaplac( - 25-(liczba_miast *10));
      armia_l.zakoncz_ture();

      if (tura == 1)
        tura = 2;
      else
        tura = 1;

      armia_l.zeruj_jednostki();
      armia_l.zaznacz_pierwsza(tura);

      /// jesli nie odtwarzamy wlasnych mp3, sa one nadawane przez gre
      if (mp3_s ==  - 1)
      {
        aktualna->zatrzymaj();
        aktualna = tablica[tura - 1];
        aktualna->przygotuj();
      }
      //obsluga sieci

      if (!kon_tur)
      {
        if (multiplayer == 1)
          klient->wyslijZapytanie("NEXT");
        else if (multiplayer == 2)
          serwer->wyslijZapytanie("NEXT");
      }
      kon_tur = false;
      menu = 1;
    }

    /// Niezale¿nie od wybranego menu zawsze pokazuje siê aktualny stan konta gracza, który ma ruch.
    if(multiplayer>0 && tura!=multi_tura) {}
    else 
    {
        engine->pisz("Gold: %d", 230, 747, gracz[tura - 1].pobierz_zloto());
        engine->pisz("(%d)", 280, 747, gracz[tura-1].ostatni_bilans());
    }



    /// ilosc klatek na sekunde
    if ((clock() / clk) - (fps / clk) >= 1)
    {
      fps = clock();
      fps_ile = l_klatek;
      l_klatek = 0;
    }
    if (MIERZ_FPS)
      engine->pisz("FPS: %d", 100, 20, fps_ile);

    if (multiplayer > 0)
    {
      char pokaz[70];
      /// czat

      engine->wpisz(tekst_czat[0], 70, false);
      sprintf(pokaz, ">%s_", (char*)(tekst_czat[0].c_str()));
      engine->pisz(pokaz, 20, 530,  - 1, makecol(255, 255, 255), false);
      for (int i = 1; i < ILOSC_LINII; ++i)
        engine->pisz((char*)tekst_czat[i].c_str(), 20, 530-15 * i,  - 1,
          makecol(255, 255, 255), false);
      if (key[KEY_ENTER])
      {
        /// obsluga sieci
        char kom_czat[70];

        sprintf(kom_czat, "CZAT %s", (char*)(tekst_czat[0].c_str()));
        if (multiplayer == 1)
          klient->wyslijZapytanie(kom_czat);
        else if (multiplayer == 2)
          serwer->wyslijZapytanie(kom_czat);
        ///
        for (int i = ILOSC_LINII - 1; i > 0; --i)
          tekst_czat[i] = tekst_czat[i - 1];
        tekst_czat[0] = "";
        key[KEY_ENTER] = false;
      }

    }
    ///

    ////
    parser->zeruj();
    bool czyParsuj = false;
    if (multiplayer == 2)
    {
      if (serwer->odbierzZapytanie())
      {
        czyParsuj = true;
        parser->przetwarzajZapytanie(serwer->zwrocZapytanie());
      }
    }
    else if (multiplayer == 1)
    {
      if (klient->odbierzZapytanie())
      {
        czyParsuj = true;
        parser->przetwarzajZapytanie(klient->zwrocZapytanie());
      }
    }


    if (czyParsuj)
    {


      if (strcmp(parser->typZapytania, "ADD") == 0)
      {
        jednostka *tmp;
        armia_l.dodaj((nazwa_pola)parser->wyglad, parser->tura, engine,
          obsluga_mapy, obsluga_mapy_jednostek, obsluga_zdarzen, parser->px,
          parser->py, parser->czy_heros);
        tmp = armia_l.zwroc_ostatnia();
        //gracz[parser->tura - 1].zaplac(tmp->pobierz_cene());
        gracz[parser->tura - 1].zwieksz_jednostki();
        tmp->czysc_mape_przejsc();
      }
      if (strcmp(parser->typZapytania, "UPDT") == 0)
      {
        jednostka *tmp;
        tmp = armia_l.zwroc_jednostke_id(parser->id);
        tmp->zmien_gracz(parser->gracz);
        tmp->zmien_punkty_zycia(parser->punkty_zycia);
        tmp->zmien_d_punkty_zycia(parser->d_punkty_zycia);
        tmp->zmien_punkty_ruchu(parser->punkty_ruchu);
        tmp->zmien_atak(parser->atak);
        tmp->zmien_obrona(parser->obrona);
        tmp->zmien_zwinnosc(parser->zwinnosc);
        tmp->zmien_do_rozdysponowania(parser->do_rozdysponowania);
        tmp->zmien_poziom(parser->poziom);
        tmp->zmien_doswiadczenie(parser->doswiadczenie);
        tmp->zmien_exp(parser->exp);
        tmp->zmien_pieniadze(parser->pieniadze);
      }
      if (strcmp(parser->typZapytania, "MOVE") == 0)
      {
        jednostka *tmp;
        jednostka *tmp2;
        tmp = armia_l.zwroc_jednostke_id(parser->id);
        tmp2 = obsluga_mapy_jednostek->pobierz_jednostke(tmp->pobierz_x(), tmp
          ->pobierz_y());
        if (tmp2 != NULL)
        {
          if (tmp2->pobierz_wyglad() != ZAMEK_GRACZ_1 && tmp2->pobierz_wyglad()
            != ZAMEK_GRACZ_2)
            obsluga_mapy_jednostek->zeruj_pole(tmp2->pobierz_x(), tmp2
              ->pobierz_y());
        }
        else
        {
          obsluga_mapy_jednostek->zeruj_pole(tmp->pobierz_x(), tmp->pobierz_y())
            ;
        }
        tmp->zmien_pozycje(parser->dx, parser->dy);
        obsluga_mapy_jednostek->wstaw_jednostke(tmp);
      }
      if (strcmp(parser->typZapytania, "KILL") == 0)
      {
        obsluga_mapy_jednostek->zeruj_pole(parser->px, parser->py);
      }

      if (strcmp(parser->typZapytania, "NEXT") == 0)
      {
        kon_tur = true;
      }
      if (strcmp(parser->typZapytania, "CZAT") == 0)
      {
        for (int i = ILOSC_LINII - 1; i > 1; --i)
          tekst_czat[i] = tekst_czat[i - 1];
        tekst_czat[1] = parser->tekst_czat;
      }
      if (strcmp(parser->typZapytania, "GOLD") == 0)
      {
        gracz[parser->tura - 1].zmien_zloto(parser->zloto);
      }
      if (strcmp(parser->typZapytania, "TECH") == 0)
      {
        fprintf(stderr, "TECH %d\n", parser->ktora);
        gracz[tura - 1].zmien_technologie(parser->ktora);
      }
    }


    l_klatek++;

    if (mouse_b &1 || mouse_b &2 | mouse_b &2)
      engine->zmiana_klatki(true);

    /// Pêtla koñczy siê wyœwietleniem zawartoœci bufora ekranu na ekran monitora. 
    engine->zmiana_klatki(false);
    engine->pokaz();

    /// Odœwie¿a siê stan myszki (funkcja allegro)
    poll_mouse();
    // odtwarza mp3
    aktualna->odtwarzaj();


    /// EDYTOR MAP
    //dev_mode = false;
    if (key[KEY_Q] && dev_mode)
      obsluga_mapy->wstaw(1);
    if (key[KEY_W] && dev_mode)
      obsluga_mapy->wstaw(2);
    if (key[KEY_E] && dev_mode)
      obsluga_mapy->wstaw(3);
    if (key[KEY_R] && dev_mode)
      obsluga_mapy->wstaw(4);
    if (key[KEY_T] && dev_mode)
      obsluga_mapy->wstaw(5);
    if (key[KEY_Y] && dev_mode)
      obsluga_mapy->wstaw(6);
    if (key[KEY_U] && dev_mode)
      obsluga_mapy->wstaw(7);
    if (key[KEY_I] && dev_mode)
      obsluga_mapy->wstaw(8);
    if (key[KEY_S] && dev_mode)
      obsluga_mapy->wstaw(9);
    if (key[KEY_O] && dev_mode)
    {
      if (obsluga_mapy_jednostek->pobierz_jednostke(10, 10) == NULL)
        armia_l.dodaj(MIASTO_1, tura, engine, obsluga_mapy,
          obsluga_mapy_jednostek, obsluga_zdarzen, 10, 10);
    }
    if (key[KEY_P] && dev_mode)
    {
      if (obsluga_mapy_jednostek->pobierz_jednostke(10, 10) == NULL)
        armia_l.dodaj(MIASTO_2, tura, engine, obsluga_mapy,
          obsluga_mapy_jednostek, obsluga_zdarzen, 10, 10);
    }

    if (key[KEY_N] && dev_mode)
    {
      if (obsluga_mapy_jednostek->pobierz_jednostke(10, 10) == NULL)
        armia_l.dodaj(WIEZA_1, tura, engine, obsluga_mapy,
          obsluga_mapy_jednostek, obsluga_zdarzen, 10, 10);
    }
    if (key[KEY_M] && dev_mode)
    {
      if (obsluga_mapy_jednostek->pobierz_jednostke(10, 10) == NULL)
        armia_l.dodaj(WIEZA_2, tura, engine, obsluga_mapy,
          obsluga_mapy_jednostek, obsluga_zdarzen, 10, 10);
    }


  }



}

//******************************************************************************

gra::~gra()
{
  delete engine;
  delete obsluga_mapy;
  delete obsluga_zdarzen;
//  delete obsluga_menu;
}

//******************************************************************************

/// konstruktor gracza (wplyw na konto gracza 1000 gp
gracz::gracz()
{
  _ostatni_bilans = 0;
  zloto = 1000;
  liczba_jednostek = 5;
  /// ustawiamy technologie na false z wyjatkiem pierwszej i drugiej
  technologie[0] = true;
  technologie[1] = true;
  for (int i = 2; i < 6; i++)
    technologie[i] = false;
}

void gracz::zmien_ture(int _tura)
{
    tura = _tura;
}

/// funkcja zwraca aktualny stan konta gracza
int gracz::pobierz_zloto()
{
  return zloto;
}

void gracz::zmien_zloto(int _zloto)
{
  zloto = _zloto;
}

void gracz::zmien_technologie(int ktora)
{
  technologie[ktora] = true;
}
int gracz::ostatni_bilans()
{
    return _ostatni_bilans;
}
/// funkcja zabiera odpowiedni¹ liczbe pieniedzy (jesli jest ujemna to dodaje)
void gracz::zaplac(int kwota)
{
  zloto -= kwota;
  _ostatni_bilans = -kwota;
  /// obsluga sieci
  if (multiplayer > 0)
  {
    char kom_gold[100];
    sprintf(kom_gold, "GOLD %d %d", tura, zloto);
    if (multiplayer == 1)
      klient->wyslijZapytanie(kom_gold);
    else if (multiplayer == 2)
      serwer->wyslijZapytanie(kom_gold);
  }
}

/// funkcja kupuje technologie dla gracza
void gracz::kup_technologie(short ktora)
{
  technologie[ktora] = true;

  /// obsluga sieci
  if (multiplayer > 0)
  {
    char kom_tech[100];
    sprintf(kom_tech, "TECH %d", ktora);
    if (multiplayer == 1)
      klient->wyslijZapytanie(kom_tech);
    else if (multiplayer == 2)
      serwer->wyslijZapytanie(kom_tech);
  }
}

bool gracz::sprawdz_technologie(short ktora)
{
  return technologie[ktora];
}

void gracz::zwieksz_jednostki()
{
  liczba_jednostek++;
}

void gracz::zmniejsz_jednostki()
{
  liczba_jednostek--;
}

int gracz::pobierz_liczbe_jednostek()
{
  return liczba_jednostek;
}

bool gra::czy_heros()
{
  bool heros = false;
  float los;
  srand(time(NULL));
  los = rand() % 100;
  if (los <= 5)
    heros = true;
  return heros;
}
