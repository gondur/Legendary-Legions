/// konstruktor klasy menu
menu::menu(grafika *_engine)
{
  engine = _engine;
  wybrana_gra = 6;
}

//******************************************************************************

/// funkcja wyœwietla menu g³ówne i obs³uguje zdarzenia, zwraca œcie¿ke do wybranej
/// mapy
short menu::pokaz()
{
	
  przycisk jezyk_pl(engine, 678, 290, "Polski");
  przycisk jezyk_en(engine, 678, 320, "English");
  przycisk jezyk_sp(engine, 678, 350, "Spanish");
  przycisk jezyk_it(engine, 678, 380, "Italian");
  przycisk jezyk_fr(engine, 678, 410, "French");
  przycisk jezyk_cz(engine, 678, 440, "Czech");
  przycisk jezyk_ge(engine, 678, 470, "German");
  przycisk jezyk(engine, 678, 380, "lang");
  set_config_file("config.cfg");
  if (strcmp((char*)get_config_string("General", "language", 0), "ENGLISH") ==
    0)
  {
    sprintf(pljezyk, "%s", "ll_en.cfg");
    set_config_string("General", "jezyk", pljezyk);
    set_config_file("ll_en.cfg");
    ajezyk = "ll_en.cfg";
    jezyk.napis("LANG: English");
  }
  else if (strcmp((char*)get_config_string("General", "language", 0), "POLSKI")
    == 0)
  {
    sprintf(pljezyk, "%s", "ll_pl.cfg");
    set_config_string("General", "jezyk", pljezyk);
    set_config_file("ll_pl.cfg");
    ajezyk = "ll_pl.cfg";
    jezyk.napis("LANG: Polski");
  }
  else if (strcmp((char*)get_config_string("General", "language", 0), "SPANISH")
    == 0)
  {
    sprintf(pljezyk, "%s", "ll_sp.cfg");
    set_config_string("General", "jezyk", pljezyk);
    set_config_file("ll_sp.cfg");
    ajezyk = "ll_sp.cfg";
    jezyk.napis("LANG: Spanish");
  }
  else if (strcmp((char*)get_config_string("General", "language", 0), "ITALIAN")
    == 0)
  {
    sprintf(pljezyk, "%s", "ll_it.cfg");
    set_config_string("General", "jezyk", pljezyk);
    set_config_file("ll_it.cfg");
    ajezyk = "ll_it.cfg";
    jezyk.napis("LANG: Italian");
  }
  else if (strcmp((char*)get_config_string("General", "language", 0), "FRENCH")
    == 0)
  {
    sprintf(pljezyk, "%s", "ll_fr.cfg");
    set_config_string("General", "jezyk", pljezyk);
    set_config_file("ll_fr.cfg");
    ajezyk = "ll_fr.cfg";
    jezyk.napis("LANG: French");
  }
  else if (strcmp((char*)get_config_string("General", "language", 0), "CZECH") 
    == 0)
  {
    sprintf(pljezyk, "%s", "ll_cz.cfg");
    set_config_string("General", "jezyk", pljezyk);
    set_config_file("ll_cz.cfg");
    ajezyk = "ll_cz.cfg";
    jezyk.napis("LANG: Czech");
  }
  else if (strcmp((char*)get_config_string("General", "language", 0), "GERMAN")
    == 0)
  {
    sprintf(pljezyk, "%s", "ll_ge.cfg");
    set_config_string("General", "jezyk", pljezyk);
    set_config_file("ll_ge.cfg");
    ajezyk = "ll_ge.cfg";
    jezyk.napis("LANG: Germany");
  }

  /// zmienna pomocnicza przechowujaca aktualnie wybrana mape

  /// domyœlna mapa
  strcpy(wybrana_mapa, "Pliki_danych/Mapy/map1.map");

  /// tworzenie przyciskow do menu wczytywania map
  przycisk mapa1(engine, 600, 410, (char*)get_config_string("teksty", "mapa1",
    0));
  przycisk mapa2(engine, 765, 410, (char*)get_config_string("teksty", "mapa2",
    0));
  przycisk mapa3(engine, 600, 535, (char*)get_config_string("teksty", "mapa3",
    0));
  przycisk mapa4(engine, 765, 535, (char*)get_config_string("teksty", "mapa4",
    0));
  przycisk powrot2(engine, 682, 575, (char*)get_config_string("teksty", 
    "powrot", 0));

  /// tworzenie przyciskow do menu wczytywania gry
  przycisk stan1(engine, 678, 320, (char*)get_config_string("teksty", "save1",
    0));
  przycisk stan2(engine, 678, 350, (char*)get_config_string("teksty", "save2",
    0));
  przycisk stan3(engine, 678, 380, (char*)get_config_string("teksty", "save3",
    0));
  przycisk stan4(engine, 678, 410, (char*)get_config_string("teksty", "save4",
    0));
  przycisk stan5(engine, 678, 440, (char*)get_config_string("teksty", "save5",
    0));
  przycisk powrot3(engine, 678, 500, (char*)get_config_string("teksty", 
    "powrot", 0));

  przycisk dzwiek(engine, 678, 320, (char*)get_config_string("teksty", 
    "soundon", 0));
  przycisk sztuczna(engine, 678, 350, (char*)get_config_string("teksty", 
    "aioff", 0));

  przycisk siec(engine, 678, 410, (char*)get_config_string("teksty", "siec", 0))
    ;

  set_config_file("config.cfg");
  przycisk klient(engine, 678, 320, "");


  if (strcmp((char*)get_config_string("General", "multiplayer", 0), 
    "POJEDYNCZY") == 0)
  {
    set_config_file(pljezyk);
    klient.napis((char*)get_config_string("teksty", "single", 0));
  }
  else if (strcmp((char*)get_config_string("General", "multiplayer", 0), 
    "SERWER") == 0)
  {
    set_config_file(pljezyk);
    klient.napis((char*)get_config_string("teksty", "serwer", 0));
  }
  else if (strcmp((char*)get_config_string("General", "multiplayer", 0), 
    "KLIENT") == 0)
  {
    set_config_file(pljezyk);
    klient.napis((char*)get_config_string("teksty", "klient", 0));
  }
  set_config_file("config.cfg");
  przycisk adresip(engine, 678, 350, (char*)get_config_string("General", "ip",
    0));
  przycisk strona(engine, 678, 350, "");
  if (strcmp((char*)get_config_string("General", "strona", 0), "DOBRA") == 0)
  {
    set_config_file(pljezyk);
    strona.napis((char*)get_config_string("teksty", "stronadobra", 0));
  }
  else if (strcmp((char*)get_config_string("General", "strona", 0), "ZLA") == 0)
  {
    set_config_file(pljezyk);
    strona.napis((char*)get_config_string("teksty", "stronazla", 0));
  }

  set_config_file(pljezyk);


  /// tworzenie przyciskow do menu glownego
  przycisk nowa(engine, get_config_int("button_nowagra", "x", 0),
    get_config_int("button_nowagra", "y", 0), (char*)get_config_string(
    "button_nowagra", "napis", 0));
  przycisk wczytaj(engine, get_config_int("button_wczytajmape", "x", 0),
    get_config_int("button_wczytajmape", "y", 0), (char*)get_config_string(
    "button_wczytajmape", "napis", 0));
  przycisk wczytaj_gre(engine, get_config_int("button_wczytajgre", "x", 0),
    get_config_int("button_wczytajgre", "y", 0), (char*)get_config_string(
    "button_wczytajgre", "napis", 0));
  przycisk opcje(engine, get_config_int("button_opcje", "x", 0), get_config_int
    ("button_opcje", "y", 0), (char*)get_config_string("button_opcje", "napis",
    0));
  przycisk info(engine, get_config_int("button_info", "x", 0), get_config_int(
    "button_info", "y", 0), (char*)get_config_string("button_info", "napis", 0))
    ;
  przycisk wyjscie(engine, get_config_int("button_wyjscie", "x", 0),
    get_config_int("button_wyjscie", "y", 0), (char*)get_config_string(
    "button_wyjscie", "napis", 0));

  przycisk powrot(engine, 682, 548, (char*)get_config_string("teksty", "powrot",
    0));

  /// ustalanie menu poczatkowego na 1 (g³ówne)
  short menu = 1;

  /// zmienna przechowujaca informacje czy wciœniêto przycisk nowa gra
  bool czy_nowa = false;

  /// wczytanie muzyki do menu
  muzyka *menu_sound = new muzyka("Pliki_danych/Muzyka/menu.mp3");

  /// zainicjowanie muzyki w menu
  //menu_sound->przygotuj();   

  /// petla g³ówna menu
  while (1)
  {
    /// odtwarzanie muzyki w menu
    //menu_sound->odtwarzaj();    

    engine->czysc_ekran(makecol(90, 138, 64));
    engine->rysuj_bitmape(B_TLO_MENU, 0, 0, 0, 0, 1024, 768);

    /// wybor menu w zaleznosci od wartosci zmiennej menu
    switch (menu)
    {
      /// menu glowne
      case 1:
        /// rysowanie przezroczystego tla pod przyciski
        engine->rysuj_bitmape(B_POLE_PRZ, 657, 288, 100, 100, 0, 0);

        /// aktualizacja przyciskow i zdarzenia z nimi zwiazane
        if (opcje.zdarzenie() == ZWOLNIENIE)
          menu = 6;
        if (wczytaj.zdarzenie() == ZWOLNIENIE)
          menu = 3;
        if (wczytaj_gre.zdarzenie() == ZWOLNIENIE)
          menu = 5;
        if (info.zdarzenie() == ZWOLNIENIE)
          menu = 2;
        if (nowa.zdarzenie() == ZWOLNIENIE)
        {
          menu_sound->zatrzymaj();
          czy_nowa = true;
        }
        if (wyjscie.zdarzenie() == ZWOLNIENIE)
        {
          delete menu_sound;
          exit( - 1);
        }

        /// wyswietlanie przyciskow
        nowa.rysuj();
        wczytaj.rysuj();
        wczytaj_gre.rysuj();
        opcje.rysuj();
        info.rysuj();
        wyjscie.rysuj();
        break;

        /// menu info
      case 2:
        /// rysowanie przezroczystego tla pod przyciski
        engine->rysuj_bitmape(B_POLE_PRZ_2, 563, 256, 100, 100, 0, 0);
        engine->pisz(
          "\nInformacje na temat gry\n\n Nowa gra - daje mozliwosc zagrania nowej gry \n Wczytaj mape - wczytuje zapisana mape z pliku \n Opcje - ustawienia gry \n Opis - informacje na temat menu \n Exit - wyjscie z gry ", 576, 268,  - 1, makecol(200, 200, 200), false);
        powrot.rysuj();
        /// powrot do menu glownego
        if (powrot.zdarzenie() == ZWOLNIENIE)
          menu = 1;
        break;

        /// menu wczytywania map
      case 3:
        /// rysowanie miniatur map, przyciskow pod nimi i przezroczystego menu pod nie
        engine->rysuj_bitmape(B_POLE_PRZ_2, 573, 286, 100, 100, 0, 0);

        miniatura("Pliki_danych/Mapy/map1.map", 624, 330, 1);
        miniatura("Pliki_danych/Mapy/map2.map", 789, 330, 1);
        miniatura("Pliki_danych/Mapy/map3.map", 624, 455, 1);
        miniatura("Pliki_danych/Mapy/map4.map", 789, 455, 1);

        mapa1.rysuj();
        mapa2.rysuj();
        mapa3.rysuj();
        mapa4.rysuj();
        powrot2.rysuj();

        /// zmiana aktualnie wybranej mapy w zaleznosci od przycisku
        if (mapa1.zdarzenie() == ZWOLNIENIE)
        {
          //strcpy(wybrana_mapa,"Pliki_danych/Mapy/map1.map");
          wybrana_gra = 6;
          menu = 1;
        }
        if (mapa2.zdarzenie() == ZWOLNIENIE)
        {
          //strcpy(wybrana_mapa,"Pliki_danych/Mapy/map2.map");
          wybrana_gra = 7;
          menu = 1;
        }
        if (mapa3.zdarzenie() == ZWOLNIENIE)
        {
          //strcpy(wybrana_mapa,"Pliki_danych/Mapy/map3.map");
          wybrana_gra = 8;
          menu = 1;
        }
        if (mapa4.zdarzenie() == ZWOLNIENIE)
        {
          //strcpy(wybrana_mapa,"Pliki_danych/Mapy/map4.map");
          wybrana_gra = 9;
          menu = 1;
        }
        if (powrot2.zdarzenie() == ZWOLNIENIE)
          menu = 1;
        break;

        /// menu opcji
      case 4:
        /// rysowanie przezroczystego tla pod przyciski
        engine->rysuj_bitmape(B_POLE_PRZ, 510, 225, 100, 100, 0, 0);

        break;

        /// menu wczytywania gry
      case 5:
        engine->rysuj_bitmape(B_POLE_PRZ, 657, 288, 100, 100, 0, 0);

        stan1.rysuj();
        stan2.rysuj();
        stan3.rysuj();
        stan4.rysuj();
        stan5.rysuj();
        powrot3.rysuj();

        /// zmiana aktualnie wybranej gry w zaleznosci od przycisku
        if (stan1.zdarzenie() == ZWOLNIENIE)
        {
          wybrana_gra = 1;
          return 1;
        }
        if (stan2.zdarzenie() == ZWOLNIENIE)
        {
          wybrana_gra = 2;
          return 1;
        }
        if (stan3.zdarzenie() == ZWOLNIENIE)
        {
          wybrana_gra = 3;
          return 1;
        }
        if (stan4.zdarzenie() == ZWOLNIENIE)
        {
          wybrana_gra = 4;
          return 1;
        }
        if (stan5.zdarzenie() == ZWOLNIENIE)
        {
          wybrana_gra = 5;
          return 1;
        }
        if (powrot3.zdarzenie() == ZWOLNIENIE)
          menu = 1;
        break;

        /// menu wyboru jezyka
      case 7:
        engine->rysuj_bitmape(B_POLE_PRZ, 657, 288, 100, 100, 0, 0);


        jezyk_pl.rysuj();
        jezyk_en.rysuj();
        jezyk_sp.rysuj();
        jezyk_it.rysuj();
        jezyk_fr.rysuj();
        jezyk_cz.rysuj();
        jezyk_ge.rysuj();
        powrot3.rysuj();

        if (jezyk_en.zdarzenie() == ZWOLNIENIE)
        {
          set_config_file("config.cfg");
          set_config_string("General", "language", "ENGLISH");
          menu = 1;
        }
        if (jezyk_pl.zdarzenie() == ZWOLNIENIE)
        {
          set_config_file("config.cfg");
          set_config_string("General", "language", "POLSKI");
          menu = 1;
        }
        if (jezyk_sp.zdarzenie() == ZWOLNIENIE)
        {
          set_config_file("config.cfg");
          set_config_string("General", "language", "SPANISH");
          menu = 1;
        }
        if (jezyk_it.zdarzenie() == ZWOLNIENIE)
        {
          set_config_file("config.cfg");
          set_config_string("General", "language", "ITALIAN");
          menu = 1;
        }
        if (jezyk_fr.zdarzenie() == ZWOLNIENIE)
        {
          set_config_file("config.cfg");
          set_config_string("General", "language", "FRENCH");
          menu = 1;
        }
        if (jezyk_cz.zdarzenie() == ZWOLNIENIE)
        {
          set_config_file("config.cfg");
          set_config_string("General", "language", "CZECH");
          menu = 1;
        }
        if (jezyk_ge.zdarzenie() == ZWOLNIENIE)
        {
          set_config_file("config.cfg");
          set_config_string("General", "language", "GERMAN");
          menu = 1;
        }
        if (menu == 1)
        {
          set_config_file("config.cfg");
          if (strcmp((char*)get_config_string("General", "language", 0), 
            "ENGLISH") == 0)
          {
            set_config_file("ll_en.cfg");
            jezyk.napis("LANG: English");
          }
          else if (strcmp((char*)get_config_string("General", "language", 0), 
            "POLSKI") == 0)
          {
            set_config_file("ll_pl.cfg");
            jezyk.napis("LANG: Polski");
          }
          else if (strcmp((char*)get_config_string("General", "language", 0), 
            "SPANISH") == 0)
          {
            set_config_file("ll_sp.cfg");
            jezyk.napis("LANG: Spanish");
          }
          else if (strcmp((char*)get_config_string("General", "language", 0), 
            "ITALIAN") == 0)
          {
            set_config_file("ll_it.cfg");
            jezyk.napis("LANG: Italian");
          }
          else if (strcmp((char*)get_config_string("General", "language", 0), 
            "FRENCH") == 0)
          {
            set_config_file("ll_fr.cfg");
            jezyk.napis("LANG: French");
          }
          else if (strcmp((char*)get_config_string("General", "language", 0), 
            "CZECH") == 0)
          {
            set_config_file("ll_cz.cfg");
            jezyk.napis("LANG: Czech");
          }
          else if (strcmp((char*)get_config_string("General", "language", 0), 
            "GERMAN") == 0)
          {
            set_config_file("ll_ge.cfg");
            jezyk.napis("LANG: German");
          }

          mapa1.napis((char*)get_config_string("teksty", "mapa1", 0));
          mapa2.napis((char*)get_config_string("teksty", "mapa2", 0));
          mapa3.napis((char*)get_config_string("teksty", "mapa3", 0));
          mapa4.napis((char*)get_config_string("teksty", "mapa4", 0));
          powrot2.napis((char*)get_config_string("teksty", "powrot", 0));
          stan1.napis((char*)get_config_string("teksty", "save1", 0));
          stan2.napis((char*)get_config_string("teksty", "save2", 0));
          stan3.napis((char*)get_config_string("teksty", "save3", 0));
          stan4.napis((char*)get_config_string("teksty", "save4", 0));
          stan5.napis((char*)get_config_string("teksty", "save5", 0));
          powrot3.napis((char*)get_config_string("teksty", "powrot", 0));
          dzwiek.napis((char*)get_config_string("teksty", "soundon", 0));
          sztuczna.napis((char*)get_config_string("teksty", "aievil", 0));
          nowa.napis((char*)get_config_string("button_nowagra", "napis", 0));
          wczytaj.napis((char*)get_config_string("button_wczytajmape", "napis",
            0));
          wczytaj_gre.napis((char*)get_config_string("button_wczytajgre", 
            "napis", 0));
          opcje.napis((char*)get_config_string("button_opcje", "napis", 0));
          info.napis((char*)get_config_string("button_info", "napis", 0));
          wyjscie.napis((char*)get_config_string("button_wyjscie", "napis", 0));
          powrot.napis((char*)get_config_string("teksty", "powrot", 0));

        }
        if (powrot3.zdarzenie() == ZWOLNIENIE)
          menu = 6;
        break;
        // menu sieci
      case 8:
        set_config_file("config.cfg");
        engine->rysuj_bitmape(B_POLE_PRZ, 657, 288, 100, 100, 0, 0);
        klient.rysuj();
        przycisk_zdarzenie pz_tmp;
        przycisk_zdarzenie pz_tmp3;

        if (strcmp((char*)get_config_string("General", "multiplayer", 0), 
          "KLIENT") == 0)
        {
          adresip.rysuj();
          pz_tmp3 = adresip.zdarzenie();
        }
        if (strcmp((char*)get_config_string("General", "multiplayer", 0), 
          "SERWER") == 0)
        {
          strona.rysuj();
          pz_tmp = strona.zdarzenie();
        }
        powrot3.rysuj();
        if (powrot3.zdarzenie() == ZWOLNIENIE)
          menu = 6;
        przycisk_zdarzenie pz_tmp2;
        pz_tmp2 = klient.zdarzenie();

        if (pz_tmp2 == ZWOLNIENIE && strcmp((char*)get_config_string("General",
          "multiplayer", 0), "POJEDYNCZY") == 0)
        {
          set_config_file("config.cfg");
          set_config_string("General", "multiplayer", "SERWER");
          set_config_file(pljezyk);
          klient.napis((char*)get_config_string("teksty", "serwer", 0));
        }
        else if (pz_tmp2 == ZWOLNIENIE && strcmp((char*)get_config_string(
          "General", "multiplayer", 0), "SERWER") == 0)
        {
          set_config_file("config.cfg");
          set_config_string("General", "multiplayer", "KLIENT");
          set_config_file(pljezyk);
          klient.napis((char*)get_config_string("teksty", "klient", 0));
        }
        else if (pz_tmp2 == ZWOLNIENIE && strcmp((char*)get_config_string(
          "General", "multiplayer", 0), "KLIENT") == 0)
        {
          set_config_file("config.cfg");
          set_config_string("General", "multiplayer", "POJEDYNCZY");
          set_config_file(pljezyk);
          klient.napis((char*)get_config_string("teksty", "single", 0));
        }
        set_config_file("config.cfg");

        if (pz_tmp == ZWOLNIENIE && strcmp((char*)get_config_string("General", 
          "strona", 0), "DOBRA") == 0)
        {
          set_config_string("General", "strona", "ZLA");
          set_config_file(pljezyk);
          strona.napis((char*)get_config_string("teksty", "stronazla", 0));
        }
        else if (pz_tmp == ZWOLNIENIE && strcmp((char*)get_config_string(
          "General", "strona", 0), "ZLA") == 0)
        {
          set_config_string("General", "strona", "DOBRA");
          set_config_file(pljezyk);
          strona.napis((char*)get_config_string("teksty", "stronadobra", 0));
        }
        set_config_file(pljezyk);
        if (pz_tmp3 == ZWOLNIENIE)
        {
          std::string tekst = adresip.zwroc_napis();
          char pokaz[17];

          while (!key[KEY_ENTER])
          {
            adresip.zmien_stan(NAJECHANIE);
            adresip.rysuj();
            engine->wpisz(tekst, 15, true);
            sprintf(pokaz, "%s_", (char*)(tekst.c_str()));
            adresip.napis(pokaz);
            engine->pokaz(true);
          }
          if (tekst.size() == 0)
            tekst = "127.0.0.1";
          sprintf(pokaz, "%s_", (char*)(tekst.c_str()));
          pokaz[strlen(pokaz) - 1] = 0;
          adresip.napis(pokaz);

          set_config_file("config.cfg");
          set_config_string("General", "ip", (char*)(tekst.c_str()));
          set_config_file(pljezyk);
        }
        break;
        /// menu opcji
      case 6:
        engine->rysuj_bitmape(B_POLE_PRZ, 657, 288, 100, 100, 0, 0);
        siec.rysuj();
        dzwiek.rysuj();
        sztuczna.rysuj();
        jezyk.rysuj();
        powrot3.rysuj();

        if (siec.zdarzenie() == ZWOLNIENIE)
        {
          menu = 8;
        }
        if (dzwiek.zdarzenie() == ZWOLNIENIE)
          u_dzwiek = !u_dzwiek;
        if (u_dzwiek)
          dzwiek.napis((char*)get_config_string("teksty", "soundoff", 0));
        else
          dzwiek.napis((char*)get_config_string("teksty", "soundon", 0));

        if (jezyk.zdarzenie() == ZWOLNIENIE)
          menu = 7;

        przycisk_zdarzenie z_sztuczna = sztuczna.zdarzenie();

        if (z_sztuczna == ZWOLNIENIE && ai == 0)
        {
          ai = 1;
          sztuczna.napis((char*)get_config_string("teksty", "aigood", 0));
        }
        else if (z_sztuczna == ZWOLNIENIE && ai == 1)
        {
          ai = 2;
          sztuczna.napis((char*)get_config_string("teksty", "aievil", 0));
        }
        else if (z_sztuczna == ZWOLNIENIE && ai == 2)
        {
          ai = 0;
          sztuczna.napis((char*)get_config_string("teksty", "aioff", 0));
        }


        if (powrot3.zdarzenie() == ZWOLNIENIE)
          menu = 1;
        break;

    }

    engine->pisz((char*)get_config_string("teksty", "build", 0), 330, 755);

    /// jesli przycisk nowa gra zostal wcisniety to funkcja zwraca sciezke do aktualnie
    /// wybranej mapy
    if (czy_nowa == true)
    {
      delete menu_sound;
      return 1;
    }
    /// wyswietlanie wszystkiego na ekran
    engine->pokaz(true);
  }
}

short menu::zwroc_ustawienia(short jakie)
{
  //dzwiek
  if (jakie == 1)
  {
    if (u_dzwiek)
      return 0;
    else
      return 1;
  }
}

char *menu::wczytana_mapa()
{
  return wybrana_mapa;
}


short menu::wczytana_gra()
{
  return wybrana_gra;
}

short menu::okno(int x, int y, char *tekst, char *przyc1, char *przyc2)
{
  static przycisk przycisk1(engine, x + 70, y + 125, przyc1);
  static przycisk przycisk2(engine, x + 190, y + 125, przyc2);

  static bool pierwsze_uruchomienie = true;
  if (pierwsze_uruchomienie)
  {
    engine->zmiana_klatki(true);
    pierwsze_uruchomienie = false;
  }

  /// zmiana napisow
  przycisk1.napis(przyc1);
  przycisk2.napis(przyc2);

  if (*przyc1 != ' ' &&  *przyc2 != ' ')
  {
    przycisk1.przesun(x + 70, y + 125);
    przycisk2.przesun(x + 190, y + 125);
  }
  else if (*przyc1 == ' ' &&  *przyc2 != ' ')
    przycisk2.przesun(x + 130, y + 125);
  else if (*przyc1 != ' ' &&  *przyc2 == ' ')
    przycisk1.przesun(x + 130, y + 125);

  /// Wyœwietlana jest przezroczysta bitmapa, na której napisany jest tekst 
  /// pytaj¹cy o potwierdzenie wyjœcia.
  engine->rysuj_bitmape(B_POLE_PRZ_3, x, y, 100, 100, 0, 0);
  engine->pisz(tekst, x + 80, y + 80,  - 1, makecol(255, 255, 255), false, 220);

  if (*przyc1 != ' ')
  if (przycisk1.zdarzenie() == ZWOLNIENIE)
  {
    pierwsze_uruchomienie = true;
    return 0;
  }
  if (*przyc2 != ' ')
  if (przycisk2.zdarzenie() == ZWOLNIENIE)
  {
    pierwsze_uruchomienie = true;
    return 1;
  }

  if (*przyc1 != ' ')
    przycisk1.rysuj();
  if (*przyc2 != ' ')
    przycisk2.rysuj();
}

//******************************************************************************

/// konstruktor klasy przycisk ustawia domyslnie aktualny stan na NORMALNY,
/// ustala pozycje przycisku oraz tekst na przycisku
przycisk::przycisk(grafika *_engine, int _x, int _y, char *_tekst)
{
  engine = _engine;
  x = _x;
  y = _y;
  aktualny = NORMALNY;
  //tekst = new char[255];
  sprintf(tekst, "%s", _tekst);
 // strcpy(tekst, _tekst);

}

//******************************************************************************

/// destruktor klasy przycisk
przycisk::~przycisk()
{
}

//******************************************************************************

/// funkcja wyswietla przycisk w zaleznosci od stanu w jakim sie znajduje 
/// wraz z etykieta
void przycisk::rysuj()
{
  if (aktualny == NAJECHANIE)
    engine->rysuj_bitmape(B_BUTTON, x, y, 0, 22, 108, 22);
  if (aktualny == NORMALNY || aktualny == ZWOLNIENIE)
    engine->rysuj_bitmape(B_BUTTON, x, y, 0, 0, 108, 22);
  if (aktualny == KLIKNIECIE)
    engine->rysuj_bitmape(B_BUTTON, x, y, 0, 44, 108, 22);

  /// etykieta przycisku
  engine->pisz(tekst, x + 55, y + 7);
}

//******************************************************************************

/// funkcja odswieza status przycisku
przycisk_zdarzenie przycisk::zdarzenie()
{
  /// jesli kursor nie znajduje sie w obrebie myszki to jest stan NORMALNY
  if (!(mouse_x > x && mouse_x < x + 108 && mouse_y > y && mouse_y < y + 22))
    aktualny = NORMALNY;
  /// jesli najedziemy na przycisk i nie zosta³ klikniety to jest to najechanie na przycisk
  if (mouse_x > x && mouse_x < x + 108 && mouse_y > y && mouse_y < y + 22 &&
    aktualny != KLIKNIECIE)
    aktualny = NAJECHANIE;
  /// jesli najedziemy na przycisk i zostanie wycisniety klawisz myszki, a poprzedni stan byl
  /// kliknieciem na przycisk to aktualny stan jest zwolnieniem przycisku
  if (mouse_x > x && mouse_x < x + 108 && mouse_y > y && mouse_y < y + 22 &&
    !mouse_b &1 && aktualny == KLIKNIECIE)
    aktualny = ZWOLNIENIE;
  /// jeœli najedziemy na przycisk i klikniemy przycisk i poprzedni stan jest rozny od klikniecia
  /// to aktualnym stanem jest klikniecie
  if (mouse_x > x && mouse_x < x + 108 && mouse_y > y && mouse_y < y + 22 &&
    mouse_b &1 && aktualny != KLIKNIECIE)
    aktualny = KLIKNIECIE;


  /// przesuwanie przycisku :D
  if (mouse_x > x && mouse_x < x + 108 && mouse_y > y - 20 && mouse_y < y + 42
    && mouse_b &2 && dev_mode)
  {
    przesun(mouse_x - 54, mouse_y - 11);
    engine->pisz("%d, ", x, y - 10, x);
    engine->pisz("%d", x + 25, y - 10, y);

  }

  /// zwracany jest stan przycisku
  if (!zablokowane)
    return aktualny;
}

void przycisk::przesun(int _x, int _y)
{
  x = _x;
  y = _y;
}

void przycisk::napis(char *_tekst)
{
  strcpy(tekst, _tekst);
}

char *przycisk::zwroc_napis()
{
  return tekst;
}

void przycisk::zmien_stan(przycisk_zdarzenie stan)
{
  aktualny = stan;
}

//******************************************************************************

/// funkcja rysuje miniature mapy z pliku w okreslonym miejscu
void menu::miniatura(char *nazwa, int pozX, int pozY, int zoom)
{
  /// wczytywanie mapy

  char z; /// zmienna pomocnicza do czytania pliku bajt po bajcie

  FILE *plik_min = fopen(nazwa, "r"); // otwieranie pliku z map¹

  short wysokosc = 60; /// tutaj domyœlnie mapa ma szerokosc i wysokosc 60
  short szerokosc = 60;

  char *pola = new char[wysokosc *szerokosc]; // rezerwacja pamiêci na mape
  int pozycja = 0; // zmienna pomocnicza

  while ((z = getc(plik_min)) != EOF)
  // wczytywanie bajt po bajcie mape z pliku do pamiêci
  {
    pola[pozycja++] = z;
  }

  fclose(plik_min); // zamkniêcie pliku

  /// zmienne pomocnicze
  int pomX;
  int pomY;

  /// rysowanie kwadratow o kolorach zale¿nych od typu pola, bêd¹cych miniatur¹ mapy
  for (int y = 0; y < wysokosc; y++)
  {
    for (int x = 0; x < szerokosc; x++)
    {
      /// ustalanie pozycji kwadratu
      pomX = pozX + x * zoom;
      pomY = pozY + y * zoom;

      pozycja = y * szerokosc + x;

      /// w zale¿noœci od typu pola wyœwietla sie kwadrat o innym kolorze
      if (pola[pozycja] == '1')
        engine->prostokat(pomX, pomY, pomX + (zoom - 1), pomY + (zoom - 1),
          makecol(34, 94, 18));
      if (pola[pozycja] == '2')
        engine->prostokat(pomX, pomY, pomX + (zoom - 1), pomY + (zoom - 1),
          makecol(14, 28, 5));
      if (pola[pozycja] == '3')
        engine->prostokat(pomX, pomY, pomX + (zoom - 1), pomY + (zoom - 1),
          makecol(14, 15, 141));
      if (pola[pozycja] == '4')
        engine->prostokat(pomX, pomY, pomX + (zoom - 1), pomY + (zoom - 1),
          makecol(128, 3, 3));
      if (pola[pozycja] == '5')
        engine->prostokat(pomX, pomY, pomX + (zoom - 1), pomY + (zoom - 1),
          makecol(200, 200, 200));
      if (pola[pozycja] == '6')
        engine->prostokat(pomX, pomY, pomX + (zoom - 1), pomY + (zoom - 1),
          makecol(70, 3, 3));
      if (pola[pozycja] == '7')
        engine->prostokat(pomX, pomY, pomX + (zoom - 1), pomY + (zoom - 1),
          makecol(100, 100, 100));
      if (pola[pozycja] == '8')
        engine->prostokat(pomX, pomY, pomX + (zoom - 1), pomY + (zoom - 1),
          makecol(255, 255, 0));

    }
  }
  delete [] pola;
}



#include "mapa.h"
