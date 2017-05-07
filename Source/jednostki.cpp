/// funkcja rysujaca jednostke oraz pasek sil i gdzie moze sie poruszyc
void jednostka::rysuj()
{
  if (gracz == 0)
    return ;
  punkt pom(0, 0);
  pom = obsluga_mapy->start_ekranu();

  if (punkty_zycia > 0)
  {
    /// jesli zaznaczony to rysujemy gdzie moze isc
    if (stan == 1)
    {
      /// zaznaczanie aktywnej jednostki
      for (int i = 0; i < 3; i++)
        engine->rysuj_pole(AKTYWNE_POLE, x - pom.rx(), y - pom.ry());

      /// sprawdzanie pol wokol jednostki i jesli moze tam przejsc (nie ma innej jednostki badz pole mapy nie jest woda
      /// to rysuje przezroczyste zielone pole
      for (int ii = 0; ii < map_szer *map_wys; ii++)
        mapa_przejsc[ii] = 0;
      mapa_przejsc[y *map_wys + x] = punkty_ruchu + 1;
      sprawdz_wokol(x, y);

    }
    /// rysowanie jednostki
    engine->rysuj_pole(wyglad, x - pom.rx(), y - pom.ry());
    /// "zaszarzanie" jednostki gdy nie ma punktow ruchu, ale nie zamek poniewaz on nie ma punktow ruchu
    if ((stan == 2 && wyglad != ZAMEK_GRACZ_1 && wyglad != WIEZA_1 && wyglad !=
      MIASTO_1 && gracz == 1) || (stan == 2 && wyglad != ZAMEK_GRACZ_2 &&
      wyglad != WIEZA_2 && wyglad != MIASTO_2 && gracz == 2))
      engine->rysuj_pole(NIEAKTYWNA_JEDNOSTKA, x - pom.rx(), y - pom.ry());

    /// prostokat sily oraz tarcza identyfikacyjna gracza

    /// obliczanie wspolrzednych jednostki na ekranie
    float odstep_pionowy_pola = (wysokosc_pola) *0.75;
    int px = ((x - pom.rx()) *40) + (((int)(y - pom.ry()) % 2)*(szerokosc_pola
      / 2)) - 11;
    int py = ((y - pom.ry()) *odstep_pionowy_pola) + 2;

    int pom_y = 0;
    /// jesli zamek to paski musza byc wyzej
    if (wyglad == ZAMEK_GRACZ_1 || wyglad == ZAMEK_GRACZ_2)
      pom_y =  - 30;
    if (wyglad == WIEZA_1 || wyglad == WIEZA_2)
      pom_y =  - 35;
    if (wyglad == MIASTO_1 || wyglad == MIASTO_2)
      pom_y =  - 35;

    /// wyliczanie ile pikseli ma pasek zycia (maksymalnie 43)
    float sily = 43 *((float)punkty_zycia / (float)d_punkty_zycia);

    /// rysowanie tarczy identyfikujacej jednostke w zaleznosci od przynaleznosci
    /// do gracza
    if (gracz == 1)
      engine->rysuj_bitmape(B_TARCZA_GRACZ_1, px, py + 3+pom_y, 0, 0, 0, 0);
    else
      engine->rysuj_bitmape(B_TARCZA_GRACZ_2, px, py + 3+pom_y, 0, 0, 0, 0);

    if ((mouse_x > px && mouse_x < px + 40 && mouse_y > py && mouse_y < py + 40)
      || stan == 1)
    {

      /// rysowanie paska sil
      engine->rysuj_bitmape(B_PASEK_SIL_BRAK, px - 2, py - 2+pom_y, 0, 0, 43, 0)
        ;
      engine->rysuj_bitmape(B_PASEK_SIL_PELNY, px - 2, py - 2+pom_y, 0, 0, sily,
        0);
    }


  }

}

//******************************************************************************

/// funkcja obslugujaca przesuwanie jednostki oraz walke
void jednostka::sterowanie()
{
  // pom do sieci
  int pocz_x = x, pocz_y = y;

  int pocz_punkty_zycia = punkty_zycia;
  int pocz_d_punkty_zycia = d_punkty_zycia;
  int pocz_punkty_ruchu = punkty_ruchu;
  int pocz_atak = atak;
  int pocz_obrona = obrona;
  int pocz_zwinnosc = zwinnosc;
  int pocz_do_rozdysponowania = do_rozdysp;
  int pocz_poziom = poziom;
  int pocz_doswiadczenie = doswiadczenie;
  int pocz_exp = exp;
  int pocz_pieniadze = pieniadze;
  char kom_docupdt[100];
  char kom_dockill[100];
  char kom_updt[100];
  char kom_move[100];
  char kom_kill[100];
  sprintf(kom_docupdt, "UNDEF");
  sprintf(kom_dockill, "UNDEF");
  sprintf(kom_updt, "UNDEF");
  sprintf(kom_move, "UNDEF");
  sprintf(kom_kill, "UNDEF");


  punkt pom(0, 0);
  pom = obsluga_mapy->start_ekranu();

  punkt docelowy(0, 0);
  docelowy = obsluga_mapy->pole_pod_myszka();

  /// sztuczna glupota :D

  jednostka *jednostka_docelowa = NULL;

  if (gracz == ai)
  {
    pobierz_cel();
    punkt ai_cel(akcja_cel());
    docelowy.wpisz(1, ai_cel.rx());
    docelowy.wpisz(2, ai_cel.ry());

  }


  /// jednostka docelowa (atakowana, badz swoja na ktora nie mozna przejsc)
  //jednostka * 
  jednostka_docelowa = obsluga_mapy_jednostek->pobierz_jednostke(docelowy.rx(),
    docelowy.ry());
  int doc_pocz_punkty_zycia;
  int doc_pocz_d_punkty_zycia;
  int doc_pocz_punkty_ruchu;
  int doc_pocz_atak;
  int doc_pocz_obrona;
  int doc_pocz_zwinnosc;
  int doc_pocz_do_rozdysponowania;
  int doc_pocz_poziom;
  int doc_pocz_doswiadczenie;
  int doc_pocz_exp;
  int doc_pocz_pieniadze;
  int doc_pocz_x;
  int doc_pocz_y;
  if (jednostka_docelowa != NULL)
  {
    doc_pocz_punkty_zycia = jednostka_docelowa->punkty_zycia;
    doc_pocz_d_punkty_zycia = jednostka_docelowa->d_punkty_zycia;
    doc_pocz_punkty_ruchu = jednostka_docelowa->punkty_ruchu;
    doc_pocz_atak = jednostka_docelowa->atak;
    doc_pocz_obrona = jednostka_docelowa->obrona;
    doc_pocz_zwinnosc = jednostka_docelowa->zwinnosc;
    doc_pocz_do_rozdysponowania = jednostka_docelowa->do_rozdysp;
    doc_pocz_poziom = jednostka_docelowa->poziom;
    doc_pocz_doswiadczenie = jednostka_docelowa->doswiadczenie;
    doc_pocz_exp = jednostka_docelowa->exp;
    doc_pocz_pieniadze = jednostka_docelowa->pieniadze;
    doc_pocz_x = jednostka_docelowa->x;
    doc_pocz_y = jednostka_docelowa->y;
  }

  if (!dev_mode)
  {
    /// czy znajduje sie tam jakas jednostka, jeœli nie to sprwadzany czy pole docelowe jest wod¹
    if ((jednostka_docelowa) == NULL && wyglad != WIEZA_1 && wyglad != WIEZA_2)
    {
      /// nie mozna wchodzic na wode (nr pola 3)
      if ((obsluga_zdarzen->p_zwolniony() == 1 && obsluga_mapy->jakie_pole
        (docelowy.rx(), docelowy.ry()) != '3') || (gracz == ai && obsluga_mapy
        ->jakie_pole(docelowy.rx(), docelowy.ry()) != '3'))
      {


        if (mapa_przejsc[(int)docelowy.ry() *map_wys + (int)docelowy.rx()] != 0
          && stan == 1)
        {
          if (punkty_ruchu + 1-mapa_przejsc[(int)docelowy.ry() *map_wys + (int)
            docelowy.rx()] > 0)
          //punkty_ruchu=punkty_ruchu-(mapa_przejsc[y*map_wys+x]-mapa_przejsc[(int)docelowy.ry()*map_wys+(int)docelowy.rx()]);
            punkty_ruchu = punkty_ruchu - (punkty_ruchu + 1-mapa_przejsc[(int)
              docelowy.ry() *map_wys + (int)docelowy.rx()]);
          /// jesli przechodzi na nowe pole to stare zeruje tak by bylo wiadomo ze nikogo tam nie ma
          /// chyba ze wychodzi z zamku (po kupnie)
          if (obsluga_mapy_jednostek->pobierz_jednostke(x, y)->pobierz_wyglad()
            != ZAMEK_GRACZ_1 && obsluga_mapy_jednostek->pobierz_jednostke(x, y)
            ->pobierz_wyglad() != ZAMEK_GRACZ_2)
            obsluga_mapy_jednostek->zeruj_pole(x, y);

          x = docelowy.rx();
          y = docelowy.ry();
          /// oraz wstawianie na mapie jednostek nowej jednostki (wskaznika do niej)
          obsluga_mapy_jednostek->wstaw_jednostke(this);

          /// odejmowanie punktow ruchu w zaleznosi od terenu
          char pole_pod_jednostka = obsluga_mapy->jakie_pole(x, y);


          /// przypadkowe wydarzenia zwiazane z terenem
          short los = rand() % 101+1;

          /// w lesie moze upolowac zwierzyne
          if (pole_pod_jednostka == '2' && los <= 10)
          {
            obsluga_zdarzen->wyswietl_okno(1);
            ulecz(5);
          }

          /// w gorach mozna znalezc zloto
          if (pole_pod_jednostka == '5' && los <= 10)
          {
            obsluga_zdarzen->wyswietl_okno(2);
            pieniadze += rand() % 26+25;
          }

          /// na lawie mozna sie przypalic
          if (pole_pod_jednostka == '4' && los <= 10)
          {
            obsluga_zdarzen->wyswietl_okno(3);
            punkty_zycia -= rand() % 20;
          }




        }
      }
    }
    /// jesli na polu docelowym nie znajduje sie przyjazna jednostka to rozpoczyna sie walka
    else if (jednostka_docelowa != NULL)
    {
      if ((jednostka_docelowa)->gracz != gracz && gracz != 0)
      {
        if (obsluga_zdarzen->p_zwolniony() == 1 || gracz == ai)
        {
          /// nie mozna zaatakowac jednostki oddalonej dalej niz jedno pole oraz stan jednostki
          /// atakujacej musi byc aktywny (1) 
          if ((fabs(docelowy.rx() - x) <= 1 && fabs(docelowy.ry() - y == 0 &&
            stan == 1) || docelowy.rx() - x - y % 2 >=  - 1 && docelowy.rx() -
            x - y % 2 <= 0 && fabs(docelowy.ry() - y) == 1 && stan == 1) || (
            (wyglad == WIEZA_1 || wyglad == WIEZA_2)))
          {
            // jesli zaatakowal ai to ai zmienia cel na atakujacego
            if (gracz != ai)
              jednostka_docelowa->cel = this;

            // na jakim polu staja walczace jednostki
            char pole_broniacy = obsluga_mapy->jakie_pole(docelowy.rx(),
              docelowy.ry());
            char pole_atakujacy = obsluga_mapy->jakie_pole(x, y);

            // ustalanie parametrow i bonusow walczacych
            float atakujacy_atak = jednostka_docelowa->atak;
            float atakujacy_obrona = jednostka_docelowa->obrona;
            float atakujacy_zwinnosc = jednostka_docelowa->zwinnosc;

            float przeciwnik_atak = jednostka_docelowa->atak;
            float przeciwnik_obrona = jednostka_docelowa->obrona;
            float przeciwnik_zwinnosc = jednostka_docelowa->zwinnosc;

            float at_przyjaciel_bonus = 0;
            float br_przyjaciel_bonus = 0;
            float at_bonus_nocdzien = 0;
            float br_bonus_nocdzien = 0;
            if (jednostka_docelowa->sprawdz_sasiadow("przyjaciel"))
              br_przyjaciel_bonus = .1;
            if (sprawdz_sasiadow("przyjaciel"))
              at_przyjaciel_bonus = .1;
            /// w zaleznosci czy pole jest lasem, lawa czy gora wyrozniamy rozne bonusy

            if (godzina >= 9 && godzina <= 19 && gracz == 1)
              at_bonus_nocdzien = .05;
            if ((godzina >= 20 && godzina <= 23 && gracz == 2) || (godzina >= 0
              && godzina <= 8 && gracz == 1))
              at_bonus_nocdzien = .05;

            if (godzina >= 9 && godzina <= 19 && jednostka_docelowa
              ->pobierz_gracz() == 1)
              br_bonus_nocdzien = .05;
            if ((godzina >= 20 && godzina <= 23 && jednostka_docelowa
              ->pobierz_gracz() == 2) || (godzina >= 0 && godzina <= 8 && gracz
              == 2))
              br_bonus_nocdzien = .05;

            switch (pole_atakujacy)
            {
              case '2':
                atakujacy_obrona += atakujacy_obrona *(.2 + at_przyjaciel_bonus
                  + at_bonus_nocdzien);
                atakujacy_zwinnosc -= atakujacy_zwinnosc * .1;
                atakujacy_atak += atakujacy_atak * .1;
                break;
              case '4':
                atakujacy_obrona -= atakujacy_obrona *(.1 + at_przyjaciel_bonus
                  + at_bonus_nocdzien);
                atakujacy_zwinnosc -= atakujacy_zwinnosc * .1;
                atakujacy_atak += atakujacy_atak * .1;
                break;
              case '5':
                atakujacy_obrona += atakujacy_obrona *(.35 +
                  at_przyjaciel_bonus + at_bonus_nocdzien);
                atakujacy_zwinnosc -= atakujacy_zwinnosc * .3;
                atakujacy_atak += atakujacy_atak * .2;
                break;
              default:
                atakujacy_obrona += atakujacy_obrona *(at_przyjaciel_bonus);
            }

            /// w zaleznosci czy pole jest lasem, lawa czy gora wyrozniamy rozne bonusy
            switch (pole_broniacy)
            {
              case '2':
                przeciwnik_obrona += przeciwnik_obrona *(.2 +
                  br_przyjaciel_bonus + br_bonus_nocdzien);
                przeciwnik_zwinnosc -= przeciwnik_zwinnosc * .1;
                przeciwnik_atak += przeciwnik_atak * .1;
                break;
              case '4':
                przeciwnik_obrona -= przeciwnik_obrona *(.1 +
                  br_przyjaciel_bonus + br_bonus_nocdzien);
                przeciwnik_zwinnosc -= przeciwnik_zwinnosc * .1;
                przeciwnik_atak += przeciwnik_atak * .1;
                break;
              case '5':
                przeciwnik_obrona += przeciwnik_obrona *(.35 +
                  br_przyjaciel_bonus + br_bonus_nocdzien);
                przeciwnik_zwinnosc -= przeciwnik_zwinnosc * .3;
                przeciwnik_atak += przeciwnik_atak * .2;
                break;
              default:
                przeciwnik_obrona += przeciwnik_obrona *(br_przyjaciel_bonus);
            }

            /// atak atakujacego
            short broniacy_zdazyl = 0;
            if (rand() % 100 < przeciwnik_obrona)
              broniacy_zdazyl = 1;
            short obrazenia = rand() % (int)atakujacy_atak - broniacy_zdazyl *
              (rand() % (int)przeciwnik_obrona);
            if (obrazenia < 0)
              obrazenia = 0;
            jednostka_docelowa->punkty_zycia -= obrazenia;

            /// atak broniacego
            short atakujacy_zdazyl = 0;
            if (rand() % 100 < atakujacy_obrona)
              atakujacy_zdazyl = 1;
            obrazenia = rand() % (int)przeciwnik_atak - atakujacy_zdazyl *(rand
              () % (int)atakujacy_obrona);
            if (obrazenia < 0)
              obrazenia = 0;
            punkty_zycia -= obrazenia;

            // smierc jednostek - zerowanie pol na ktorych staly
            bool atakujacy_smierc = false;
            bool broniacy_smierc = false;

            if (punkty_zycia <= 0)
            {
              // dodajemy punkty doswiadczenia i pieniadze za zabicie
              jednostka_docelowa->doswiadczenie += exp;
              jednostka_docelowa->pieniadze += rand() % (cena / 2);
              if (wyglad != WIEZA_1 && wyglad != MIASTO_1 && wyglad != WIEZA_2
                && wyglad != MIASTO_2)
                obsluga_mapy_jednostek->zeruj_pole(x, y);
              else
              {
                punkty_zycia = d_punkty_zycia;
                gracz = jednostka_docelowa->gracz;
                punkty_ruchu = 0;
              }
              atakujacy_smierc = true;
            }

            if (jednostka_docelowa->punkty_zycia <= 0 && !atakujacy_smierc)
            /// zabezpieczenie by jednostki nie ginely na raz
            {
              // dodajemy punkty doswiadczenia i pieniadze za zabicie
              doswiadczenie += jednostka_docelowa->exp;
              pieniadze += rand() % (jednostka_docelowa->cena / 2);
              if (jednostka_docelowa->wyglad != WIEZA_1 && jednostka_docelowa
                ->wyglad != MIASTO_1 && jednostka_docelowa->wyglad != WIEZA_2
                && jednostka_docelowa->wyglad != MIASTO_2)
                obsluga_mapy_jednostek->zeruj_pole(docelowy.rx(), docelowy.ry())
                  ;
              else
              {
                jednostka_docelowa->punkty_zycia = jednostka_docelowa
                  ->d_punkty_zycia;
                jednostka_docelowa->gracz = gracz;
                jednostka_docelowa->punkty_ruchu = 0;
              }
              broniacy_smierc = true;
            }
            else if (jednostka_docelowa->punkty_zycia <= 0 && atakujacy_smierc)
              jednostka_docelowa->punkty_zycia = 1;

            // jesli przekroczyl poziom doswiadczenia to moze rozdysponowac punkty doswiadczenia
            if (!atakujacy_smierc)
              nowy_poziom();

            if (!broniacy_smierc)
              jednostka_docelowa->nowy_poziom();

            // walka kosztuje 1 punkt ruchu tylko atakujacego
            punkty_ruchu--;
          }
        }
      }
    }
  }
  else
  {
    if (obsluga_zdarzen->p_zwolniony() == 1)
    {
      obsluga_mapy_jednostek->zeruj_pole(x, y);
      x = docelowy.rx();
      y = docelowy.ry();

      obsluga_mapy_jednostek->wstaw_jednostke(this);

    }
  }
  if (jednostka_docelowa != NULL)
  {
    if (doc_pocz_punkty_zycia != jednostka_docelowa->punkty_zycia ||
      doc_pocz_d_punkty_zycia != jednostka_docelowa->d_punkty_zycia ||
      doc_pocz_punkty_ruchu != jednostka_docelowa->punkty_ruchu ||
      doc_pocz_atak != jednostka_docelowa->atak || doc_pocz_obrona !=
      jednostka_docelowa->obrona || doc_pocz_zwinnosc != jednostka_docelowa
      ->zwinnosc || doc_pocz_do_rozdysponowania != jednostka_docelowa
      ->do_rozdysp || doc_pocz_poziom != jednostka_docelowa->poziom ||
      doc_pocz_doswiadczenie != jednostka_docelowa->doswiadczenie ||
      doc_pocz_exp != jednostka_docelowa->exp || doc_pocz_pieniadze !=
      jednostka_docelowa->pieniadze)
    {
      sprintf(kom_docupdt, "UPDT %d %d %d %d %d %d %d %d %d %d %d %d %d",
        jednostka_docelowa->id, jednostka_docelowa->gracz, jednostka_docelowa
        ->punkty_zycia, jednostka_docelowa->d_punkty_zycia, jednostka_docelowa
        ->punkty_ruchu, jednostka_docelowa->atak, jednostka_docelowa->obrona,
        jednostka_docelowa->zwinnosc, jednostka_docelowa->do_rozdysp,
        jednostka_docelowa->poziom, jednostka_docelowa->doswiadczenie,
        jednostka_docelowa->exp, jednostka_docelowa->pieniadze);
    }
  }
  if (pocz_punkty_zycia != punkty_zycia || pocz_d_punkty_zycia !=
    d_punkty_zycia || pocz_punkty_ruchu != punkty_ruchu || pocz_atak != atak ||
    pocz_obrona != obrona || pocz_zwinnosc != zwinnosc ||
    pocz_do_rozdysponowania != do_rozdysp || pocz_poziom != poziom ||
    pocz_doswiadczenie != doswiadczenie || pocz_exp != exp || pocz_pieniadze !=
    pieniadze)
  {
    sprintf(kom_updt, "UPDT %d %d %d %d %d %d %d %d %d %d %d %d %d", id, gracz,
      punkty_zycia, d_punkty_zycia, punkty_ruchu, atak, obrona, zwinnosc,
      do_rozdysp, poziom, doswiadczenie, exp, pieniadze);
  }
  if (x != pocz_x || y != pocz_y)
  {
    sprintf(kom_move, "MOVE %d %d %d", id, x, y);
  }
  if (punkty_zycia <= 0 && x > 0 && y > 0)
  {
    sprintf(kom_kill, "KILL %d %d", pocz_x, pocz_y);
  }
  if (doc_pocz_punkty_zycia <= 0)
  {
    sprintf(kom_dockill, "KILL %d %d", doc_pocz_x, doc_pocz_y);
  }



  // obsluga sieci
  switch (multiplayer)
  {
    case 1:
      if (strcmp(kom_docupdt, "UNDEF") != 0)
        klient->wyslijZapytanie(kom_docupdt);
      if (strcmp(kom_dockill, "UNDEF") != 0)
        klient->wyslijZapytanie(kom_dockill);
      if (strcmp(kom_updt, "UNDEF") != 0)
        klient->wyslijZapytanie(kom_updt);
      if (strcmp(kom_move, "UNDEF") != 0)
        klient->wyslijZapytanie(kom_move);
      if (strcmp(kom_kill, "UNDEF") != 0)
        klient->wyslijZapytanie(kom_kill);

      break;
    case 2:
      if (strcmp(kom_docupdt, "UNDEF") != 0)
        serwer->wyslijZapytanie(kom_docupdt);
      if (strcmp(kom_dockill, "UNDEF") != 0)
        serwer->wyslijZapytanie(kom_dockill);
      if (strcmp(kom_updt, "UNDEF") != 0)
        serwer->wyslijZapytanie(kom_updt);
      if (strcmp(kom_move, "UNDEF") != 0)
        serwer->wyslijZapytanie(kom_move);
      if (strcmp(kom_kill, "UNDEF") != 0)
        serwer->wyslijZapytanie(kom_kill);

      break;
  }




}

//******************************************************************************

/// sprawdza czy jednostka zostala kliknieta (zwraca 1), badz jest nieaktywna (zwraca 0)
int jednostka::obsluga()
{
  /// jeœli jednostka nie ¿yje lub nie ma punktow ruchu przyjmuje stan 2, czyli
  /// jest aktywna ale nie ma ruchu
  if ((punkty_ruchu <= 0 && !dev_mode) || punkty_zycia <= 0)
    stan = 2;

  /// jesli jest aktywna i ¿yje to mo¿na siê ni¹ poruszaæ lub atakowaæ (funkcja sterowanie)
  if (stan == 1 && punkty_zycia > 0)
    sterowanie();

  /// czy jednostka zostala kliknieta (aktywowana), tzn. wspolrzedne pola zaznaczonego
  /// przez myszke sa takie same jak pozycja jednostki oraz zostal klikniety lewy klawisz
  /// myszy oraz jednostka ma jeszcze punkty ruchu (czyli stan rozny od 2)
  punkt pom(0, 0);
  pom = obsluga_mapy->pole_pod_myszka();
  /// jesli jednostka zostala kliknieta to funkcja zwraca 1
  if (x == pom.rx() && y == pom.ry() && obsluga_zdarzen->l_klikniety() == 1 &&
    punkty_zycia > 0)
    return 1;
  /// jesli nie to zwraca 0
  return 0;
}

void jednostka::wyswietl_info(bool stats, bool _opis)
{
  char pole_pod_jednostka = obsluga_mapy->jakie_pole(x, y);
  float bonus_atak = 0;
  float bonus_obrona = 0;
  float bonus_zwinnosc = 0;


  if (pole_pod_jednostka == '2')
  {
    bonus_atak = .1;
    bonus_obrona = .2;
    bonus_zwinnosc =  - .1;
  }

  if (pole_pod_jednostka == '4')
  {
    bonus_atak = .1;
    bonus_obrona =  - .1;
    bonus_zwinnosc =  - .1;
  }

  if (pole_pod_jednostka == '5')
  {
    bonus_atak = .2;
    bonus_obrona = .35;
    bonus_zwinnosc =  - .3;
  }

  if (x !=  - 1 && y !=  - 1)
    if (sprawdz_sasiadow("przyjaciel"))
      bonus_obrona += .1;
  if (godzina >= 9 && godzina <= 19 && gracz == 1)
    bonus_obrona += .05;
  if ((godzina >= 20 && godzina <= 23 && gracz == 2) || (godzina >= 0 &&
    godzina <= 8 && gracz == 2))
    bonus_obrona += .05;

  engine->rysuj_pole(wyglad, 230, 650);

  if (stats)
  {
    engine->pisz("HP:", 310, 610, punkty_zycia, makecol(0, 0, 0), false);
    engine->pisz("\\", 361, 610, d_punkty_zycia, makecol(0, 0, 0), false);
    engine->pisz((char*)get_config_string("teksty", "moves", 0), 310, 622,
      punkty_ruchu, makecol(0, 0, 0), false);
    engine->pisz("\\", 367, 622, d_punkty_ruchu, makecol(0, 0, 0), false);

    if (bonus_atak > 0)
      engine->pisz((char*)get_config_string("teksty", "attack", 0), 310, 634,
        atak + bonus_atak * atak, makecol(0, 200, 0), false);
    else if (bonus_atak < 0)
      engine->pisz((char*)get_config_string("teksty", "attack", 0), 310, 634,
        atak + bonus_atak * atak, makecol(200, 0, 0), false);
    else
      engine->pisz((char*)get_config_string("teksty", "attack", 0), 310, 634,
        atak + bonus_atak * atak, makecol(0, 0, 0), false);

    if (bonus_obrona > 0)
      engine->pisz((char*)get_config_string("teksty", "defense", 0), 310, 646,
        obrona + bonus_obrona * obrona, makecol(0, 200, 0), false);
    else if (bonus_obrona < 0)
      engine->pisz((char*)get_config_string("teksty", "defense", 0), 310, 646,
        obrona + bonus_obrona * obrona, makecol(200, 0, 0), false);
    else
      engine->pisz((char*)get_config_string("teksty", "defense", 0), 310, 646,
        obrona + bonus_obrona * obrona, makecol(0, 0, 0), false);

    if (bonus_zwinnosc > 0)
      engine->pisz((char*)get_config_string("teksty", "agility", 0), 310, 658,
        zwinnosc + bonus_zwinnosc * zwinnosc, makecol(0, 200, 0), false);
    else if (bonus_zwinnosc < 0)
      engine->pisz((char*)get_config_string("teksty", "agility", 0), 310, 658,
        zwinnosc + bonus_zwinnosc * zwinnosc, makecol(200, 0, 0), false);
    else
      engine->pisz((char*)get_config_string("teksty", "agility", 0), 310, 658,
        zwinnosc + bonus_zwinnosc * zwinnosc, makecol(0, 0, 0), false);

    engine->pisz("Exp: ", 310, 670, exp, makecol(0, 0, 0), false);
    engine->pisz((char*)get_config_string("teksty", "level", 0), 310, 682,
      poziom, makecol(0, 0, 0), false);
    engine->pisz((char*)get_config_string("teksty", "experience", 0), 310, 694,
      doswiadczenie, makecol(0, 0, 0), false);
    engine->pisz((char*)get_config_string("teksty", "nextlevel", 0), 310, 706, nastepny_poziom, makecol(0, 0, 0), false);
    engine->pisz((char*)get_config_string("teksty", "cost", 0), 310, 718, cena,
      makecol(0, 0, 0), false);
  }
  if (_opis)
    engine->pisz(opis, 400, 610,  - 1, makecol(0, 0, 0), false, 280);

}


//******************************************************************************

void jednostka::zmien_id(int _id)
{
  id = _id;
  nowy_poziom();
}

void jednostka::zmien_gracz(int _gracz)
{
  gracz = _gracz;
}

int jednostka::pobierz_id()
{
  return id;
}

void jednostka::zmien_stan(int _stan)
{
  stan = _stan;
}

void jednostka::zmien_pozycje(int _x, int _y)
{
  x = _x;
  y = _y;
}

//******************************************************************************

int jednostka::aktualny_stan()
{
  return stan;
}

//******************************************************************************

void jednostka::przywroc_punkty_ruchu(int punkty)
{
  if (punkty ==  - 1)
    punkty_ruchu = d_punkty_ruchu;
  else
    punkty_ruchu = punkty;
}

//******************************************************************************

int jednostka::pobierz_gracz()
{
  return gracz;
}

//******************************************************************************

int jednostka::pobierz_x()
{
  return x;
}

//******************************************************************************

int jednostka::pobierz_y()
{
  return y;
}

//******************************************************************************

int jednostka::pobierz_punkty_zycia()
{
  return punkty_zycia;
}

//******************************************************************************

int jednostka::pobierz_d_punkty_zycia()
{
  return d_punkty_zycia;
}

//******************************************************************************

int jednostka::pobierz_punkty_ruchu()
{
  return punkty_ruchu;
}

//******************************************************************************

int jednostka::pobierz_atak()
{
  return atak;
}

//******************************************************************************

int jednostka::pobierz_obrona()
{
  return obrona;
}

//******************************************************************************

int jednostka::pobierz_zwinnosc()
{
  return zwinnosc;
}

//******************************************************************************

int jednostka::pobierz_do_rozdysponowania()
{
  return do_rozdysp;
}




void jednostka::pobierz_cel()
{
  jednostka *szukana_jednostka = NULL;

  if (cel == NULL || cel->pobierz_punkty_zycia() <= 0 || cel->gracz == gracz)
  {
    float odleglosc = 999999;

    for (int iy = 0; iy < map_wys; iy++)
    for (int ix = 0; ix < map_szer; ix++)
    {
      szukana_jednostka = obsluga_mapy_jednostek->pobierz_jednostke(ix, iy);
      if (szukana_jednostka != NULL)
      {

        if (szukana_jednostka->pobierz_gracz() != ai && szukana_jednostka
          ->pobierz_gracz() != 0 && szukana_jednostka->pobierz_punkty_zycia() >
          0 && sqrt((x - szukana_jednostka->pobierz_x())*(x - szukana_jednostka
          ->pobierz_x()) + (y - szukana_jednostka->pobierz_y())*(y -
          szukana_jednostka->pobierz_y())) < odleglosc)
        {
          odleglosc = sqrt((x - szukana_jednostka->pobierz_x())*(x -
            szukana_jednostka->pobierz_x()) + (y - szukana_jednostka->pobierz_y
            ())*(y - szukana_jednostka->pobierz_y()));
          cel = obsluga_mapy_jednostek->pobierz_jednostke(ix, iy);
        }

      }

    }
  }

}


punkt &jednostka::akcja_cel()
{

  for (int ii = 0; ii < map_szer *map_wys; ii++)
    mapa_przejsc[ii] = 0;
  mapa_przejsc[y *map_wys + x] = punkty_ruchu + 1;
  sprawdz_wokol(x, y);


  punkt doc(0, 0);
  int zx = x, zy = y;


  /* wyszukaj wszystkie punkty i sprawdz ktory z nich jest najblizej celu*/

  float odleglosc = 999999;

  for (int iy = y - punkty_ruchu - 1; iy <= y + punkty_ruchu + 1; iy++)
  for (int ix = x - punkty_ruchu - 1; ix <= x + punkty_ruchu + 1; ix++)
  {
    if (ix >= 0 && ix <= map_szer && iy >= 0 && iy <= map_wys)
    {

      if (mapa_przejsc[iy *map_szer + ix] != 0 && sqrt((ix - cel->pobierz_x())*
        (ix - cel->pobierz_x()) + (iy - cel->pobierz_y())*(iy - cel->pobierz_y()
        )) < odleglosc)

      {
        odleglosc = sqrt((ix - cel->pobierz_x())*(ix - cel->pobierz_x()) + (iy 
          - cel->pobierz_y())*(iy - cel->pobierz_y()));
        zx = ix;
        zy = iy;
      }
    }

  }

  bool wyznaczona = false;
  // jesli nic sie nie przemiescil to wybiera losowe pole
  if (zx == x && zy == y)
  {
    for (int iy = y - punkty_ruchu - 1; iy <= y + punkty_ruchu + 1; iy++)
    for (int ix = x - punkty_ruchu - 1; ix <= x + punkty_ruchu + 1; ix++)
    {
      if (ix >= 0 && ix <= map_szer && iy >= 0 && iy <= map_wys)
      {
        if (mapa_przejsc[iy *map_szer + ix] != 0 && !wyznaczona)
        {
          zx = ix;
          zy = iy;
          wyznaczona = true;
        }
        else if (mapa_przejsc[iy *map_szer + ix] != 0 && rand() % 10 <= 2)
        {
          zx = ix;
          zy = iy;
        }
      }
    }
  }




  // jesli jest blisko celu to atakuje
  if (sqrt((x - cel->pobierz_x())*(x - cel->pobierz_x()) + (y - cel->pobierz_y()
    )*(y - cel->pobierz_y())) <= 1)
  {
    zx = cel->pobierz_x();
    zy = cel->pobierz_y();

  }

  if (zx == x && zy == y)
  {
    punkty_ruchu--;
  }

  /// jesli to wieza to szuka celu jesli nie znajdzie to konczy ruch
  bool znalazl = false;
  if (wyglad == WIEZA_1 || wyglad == WIEZA_2)
  {
    for (int iy = y - punkty_ruchu - 1; iy <= y + punkty_ruchu + 1; iy++)
    for (int ix = x - punkty_ruchu - 1; ix <= x + punkty_ruchu + 1; ix++)

    {
      if (ix >= 0 && ix <= map_szer && iy >= 0 && iy <= map_wys)
      {

        if (obsluga_mapy_jednostek->pobierz_jednostke(ix, iy) != NULL)
        {
          piszlog("gracz", obsluga_mapy_jednostek->pobierz_jednostke(ix, iy)
            ->gracz);


          if (obsluga_mapy_jednostek->pobierz_jednostke(ix, iy)->gracz != gracz)
          {
            zx = obsluga_mapy_jednostek->pobierz_jednostke(ix, iy)->x;
            zy = obsluga_mapy_jednostek->pobierz_jednostke(ix, iy)->y;
            znalazl = true;
          }
        }
      }
    }

    if (!znalazl)
      punkty_ruchu = 0;
  }



  if (zx < 0)
    zx = 0;
  if (zx >= map_szer)
    zx = map_szer - 1;
  if (zy < 0)
    zy = 0;
  if (zy >= map_wys)
    zy = map_wys - 1;

  doc.wpisz(1, zx);
  doc.wpisz(2, zy);
  return doc;

}




//******************************************************************************

void jednostka::zwieksz_atak(int o_ile = 1)
{
  if (atak < 100)
    atak += o_ile;
}

//******************************************************************************

void jednostka::zwieksz_obrone(int o_ile = 1)
{
  if (obrona < 100)
    obrona += o_ile;
}

//******************************************************************************

void jednostka::zwieksz_zwinnosc(int o_ile = 1)
{
  if (obrona < 100)
    zwinnosc += o_ile;
}


void jednostka::zmien_punkty_zycia(int z)
{
  punkty_zycia = z;
}

void jednostka::zmien_d_punkty_zycia(int z)
{
  d_punkty_zycia = z;
}

void jednostka::zmien_punkty_ruchu(int z)
{
  punkty_ruchu = z;
}

void jednostka::zmien_atak(int z)
{
  atak = z;
}

void jednostka::zmien_obrona(int z)
{
  obrona = z;
}

void jednostka::zmien_zwinnosc(int z)
{
  zwinnosc = z;
}

void jednostka::zmien_do_rozdysponowania(int z)
{
  do_rozdysp = z;
}

void jednostka::zmien_poziom(int z)
{
  poziom = z;
}

void jednostka::zmien_doswiadczenie(int z)
{
  doswiadczenie = z;
}

void jednostka::zmien_exp(int z)
{
  exp = z;
}

void jednostka::zmien_pieniadze(int z)
{
  pieniadze = z;
}



//******************************************************************************

void jednostka::ulecz(short maksymalnie)
{
  int tmp = (d_punkty_zycia *maksymalnie / 100);
  if (tmp <= 0)
    tmp = 1;
  short ile_odzyska = rand() % tmp;
  punkty_zycia += ile_odzyska;
  if (punkty_zycia > d_punkty_zycia)
    punkty_zycia = d_punkty_zycia;
  char kom_updt[100];
  sprintf(kom_updt, "UNDEF");
  sprintf(kom_updt, "UPDT %d %d %d %d %d %d %d %d %d %d %d %d %d", id, gracz,
  punkty_zycia, d_punkty_zycia, punkty_ruchu, atak, obrona, zwinnosc,
  do_rozdysp, poziom, doswiadczenie, exp, pieniadze);
  if(multiplayer==1)
    klient->wyslijZapytanie(kom_updt);
  else if(multiplayer==2)
    serwer->wyslijZapytanie(kom_updt);
  


}

//******************************************************************************

void jednostka::trenuj(short maksymalnie)
{
  doswiadczenie += rand() % maksymalnie;
  nowy_poziom();
}

void jednostka::nowy_poziom()
{
  short prog[11];
  prog[1] = 100;
  prog[2] = 250;
  prog[3] = 450;
  prog[4] = 700;
  prog[5] = 1000;
  prog[6] = 1350;
  prog[7] = 1750;
  prog[8] = 2200;
  prog[9] = 2700;
  prog[10] = 3250;
  if (doswiadczenie >= prog[poziom])
  {
    do_rozdysp = 10;
    poziom++;
    punkty_zycia += punkty_zycia *((float)obrona / 500);
    d_punkty_zycia += d_punkty_zycia *((float)obrona / 500);
  }
  nastepny_poziom = prog[poziom];
}

//******************************************************************************

void jednostka::zmniejsz_do_rozdysponowania()
{
  do_rozdysp--;
}

//******************************************************************************

nazwa_pola jednostka::pobierz_wyglad()
{
  return wyglad;
}

bool jednostka::sprawdz_sasiadow(char *jakie_pole)
{
  nazwa_pola np;

  if (strcmp(jakie_pole, "zamek") == 0)
  {
    if (gracz == 1)
      np = ZAMEK_GRACZ_1;
    else if (gracz == 2)
      np = ZAMEK_GRACZ_2;
  }
  else if (strcmp(jakie_pole, "wieza") == 0)
  {
    if (gracz == 1)
      np = WIEZA_1;
    else if (gracz == 2)
      np = WIEZA_2;
  }
  else if (strcmp(jakie_pole, "miasto") == 0)
  {
    if (gracz == 1)
      np = MIASTO_1;
    else if (gracz == 2)
      np = MIASTO_2;
  }

  if (strcmp(jakie_pole, "przyjaciel") == 0)
  {
    if (obsluga_mapy_jednostek->pobierz_jednostke(x - 1, y) != NULL)
      if (obsluga_mapy_jednostek->pobierz_jednostke(x - 1, y)->pobierz_gracz() 
        == gracz)
        return true;

    if (obsluga_mapy_jednostek->pobierz_jednostke(x + 1, y) != NULL)
      if (obsluga_mapy_jednostek->pobierz_jednostke(x + 1, y)->pobierz_gracz() 
        == gracz)
        return true;

    if (obsluga_mapy_jednostek->pobierz_jednostke(x - 1+y % 2, y - 1) != NULL)
      if (obsluga_mapy_jednostek->pobierz_jednostke(x - 1+y % 2, y - 1)
        ->pobierz_gracz() == gracz)
        return true;

    if (obsluga_mapy_jednostek->pobierz_jednostke(x + y % 2, y - 1) != NULL)
      if (obsluga_mapy_jednostek->pobierz_jednostke(x + y % 2, y - 1)
        ->pobierz_gracz() == gracz)
        return true;

    if (obsluga_mapy_jednostek->pobierz_jednostke(x - 1+y % 2, y + 1) != NULL)
      if (obsluga_mapy_jednostek->pobierz_jednostke(x - 1+y % 2, y + 1)
        ->pobierz_gracz() == gracz)
        return true;

    if (obsluga_mapy_jednostek->pobierz_jednostke(x + y % 2, y + 1) != NULL)
      if (obsluga_mapy_jednostek->pobierz_jednostke(x + y % 2, y + 1)
        ->pobierz_gracz() == gracz)
        return true;
  }


  if (obsluga_mapy_jednostek->pobierz_jednostke(x - 1, y) != NULL)
    if (obsluga_mapy_jednostek->pobierz_jednostke(x - 1, y)->pobierz_wyglad() 
      == np)
      return true;

  if (obsluga_mapy_jednostek->pobierz_jednostke(x + 1, y) != NULL)
    if (obsluga_mapy_jednostek->pobierz_jednostke(x + 1, y)->pobierz_wyglad() 
      == np)
      return true;

  if (obsluga_mapy_jednostek->pobierz_jednostke(x - 1+y % 2, y - 1) != NULL)
    if (obsluga_mapy_jednostek->pobierz_jednostke(x - 1+y % 2, y - 1)
      ->pobierz_wyglad() == np)
      return true;

  if (obsluga_mapy_jednostek->pobierz_jednostke(x + y % 2, y - 1) != NULL)
    if (obsluga_mapy_jednostek->pobierz_jednostke(x + y % 2, y - 1)
      ->pobierz_wyglad() == np)
      return true;

  if (obsluga_mapy_jednostek->pobierz_jednostke(x - 1+y % 2, y + 1) != NULL)
    if (obsluga_mapy_jednostek->pobierz_jednostke(x - 1+y % 2, y + 1)
      ->pobierz_wyglad() == np)
      return true;

  if (obsluga_mapy_jednostek->pobierz_jednostke(x + y % 2, y + 1) != NULL)
    if (obsluga_mapy_jednostek->pobierz_jednostke(x + y % 2, y + 1)
      ->pobierz_wyglad() == np)
      return true;

  return false;

}

//******************************************************************************

short jednostka::pobierz_poziom()
{
  return poziom;
}

//******************************************************************************

short jednostka::pobierz_doswiadczenie()
{
  return doswiadczenie;
}

//******************************************************************************

short jednostka::pobierz_cene()
{
  return cena;
}

//******************************************************************************

short jednostka::pobierz_pieniadze()
{
  return pieniadze;
}

//******************************************************************************

void jednostka::zmien_pieniadze(short _pieniadze)
{
  pieniadze = _pieniadze;
}

//******************************************************************************

short jednostka::pobierz_exp()
{
  return exp;
}

//******************************************************************************

char *jednostka::pobierz_opis()
{
  return opis;
}

//******************************************************************************

robotnik_1::robotnik_1(grafika *_engine, mapa *_obsluga_mapy, mapa_jednostek
  *_obsluga_mapy_jednostek, zdarzenia *_obsluga_zdarzen, int _x, int _y, int
  _gracz)
{
  mapa_przejsc = new short[map_szer *map_wys];
  cel = NULL;

  engine = _engine;
  obsluga_mapy = _obsluga_mapy;
  obsluga_mapy_jednostek = _obsluga_mapy_jednostek;
  obsluga_zdarzen = _obsluga_zdarzen;
  wyglad = ROBOTNIK_1;
  x = _x;
  y = _y;
  stan = 0;
  punkty_ruchu = 5;
  d_punkty_ruchu = 5;
  gracz = _gracz;
  punkty_zycia = 50;
  d_punkty_zycia = 50;
  atak = 10;
  obrona = 15;
  zwinnosc = 30;
  strcpy(opis, (char*)get_config_string("teksty", "robotnik", 0));
  exp = 50;
  poziom = 1;
  doswiadczenie = 0;
  cena = 70;
  do_rozdysp = 0;
  pieniadze = 0;
}

robotnik_2::robotnik_2(grafika *_engine, mapa *_obsluga_mapy, mapa_jednostek
  *_obsluga_mapy_jednostek, zdarzenia *_obsluga_zdarzen, int _x, int _y, int
  _gracz)
{
  mapa_przejsc = new short[map_szer *map_wys];
  cel = NULL;

  engine = _engine;
  obsluga_mapy = _obsluga_mapy;
  obsluga_mapy_jednostek = _obsluga_mapy_jednostek;
  obsluga_zdarzen = _obsluga_zdarzen;
  wyglad = ROBOTNIK_2;
  x = _x;
  y = _y;
  stan = 0;
  punkty_ruchu = 5;
  d_punkty_ruchu = 5;
  gracz = _gracz;
  punkty_zycia = 50;
  d_punkty_zycia = 50;
  atak = 10;
  obrona = 15;
  zwinnosc = 30;
  strcpy(opis, (char*)get_config_string("teksty", "robotnik", 0));
  exp = 50;
  poziom = 1;
  doswiadczenie = 0;
  cena = 70;
  do_rozdysp = 0;
  pieniadze = 0;
}

wieza_1::wieza_1(grafika *_engine, mapa *_obsluga_mapy, mapa_jednostek
  *_obsluga_mapy_jednostek, zdarzenia *_obsluga_zdarzen, int _x, int _y, int
  _gracz)
{
  mapa_przejsc = new short[map_szer *map_wys];

  cel = NULL;

  engine = _engine;
  obsluga_mapy = _obsluga_mapy;
  obsluga_mapy_jednostek = _obsluga_mapy_jednostek;
  obsluga_zdarzen = _obsluga_zdarzen;
  wyglad = WIEZA_1;
  x = _x;
  y = _y;
  stan = 0;
  punkty_ruchu = 9;
  d_punkty_ruchu = 9;
  gracz = _gracz;
  punkty_zycia = 150;
  d_punkty_zycia = 150;
  atak = 60;
  obrona = 65;
  zwinnosc = 30;
  strcpy(opis, (char*)get_config_string("teksty", "wieza", 0));
  exp = 50;
  poziom = 1;
  doswiadczenie = 0;
  cena = 300;
  do_rozdysp = 0;
  pieniadze = 0;


}

wieza_2::wieza_2(grafika *_engine, mapa *_obsluga_mapy, mapa_jednostek
  *_obsluga_mapy_jednostek, zdarzenia *_obsluga_zdarzen, int _x, int _y, int
  _gracz)
{
  mapa_przejsc = new short[map_szer *map_wys];

  cel = NULL;

  engine = _engine;
  obsluga_mapy = _obsluga_mapy;
  obsluga_mapy_jednostek = _obsluga_mapy_jednostek;
  obsluga_zdarzen = _obsluga_zdarzen;
  wyglad = WIEZA_2;
  x = _x;
  y = _y;
  stan = 0;
  punkty_ruchu = 9;
  d_punkty_ruchu = 9;
  gracz = _gracz;
  punkty_zycia = 150;
  d_punkty_zycia = 150;
  atak = 60;
  obrona = 65;
  zwinnosc = 30;
  strcpy(opis, (char*)get_config_string("teksty", "wieza", 0));
  exp = 50;
  poziom = 1;
  doswiadczenie = 0;
  cena = 300;
  do_rozdysp = 0;
  pieniadze = 0;


}

miasto_1::miasto_1(grafika *_engine, mapa *_obsluga_mapy, mapa_jednostek
  *_obsluga_mapy_jednostek, zdarzenia *_obsluga_zdarzen, int _x, int _y, int
  _gracz)
{
  mapa_przejsc = new short[map_szer *map_wys];

  cel = NULL;

  engine = _engine;
  obsluga_mapy = _obsluga_mapy;
  obsluga_mapy_jednostek = _obsluga_mapy_jednostek;
  obsluga_zdarzen = _obsluga_zdarzen;
  wyglad = MIASTO_1;
  x = _x;
  y = _y;
  stan = 0;
  punkty_ruchu = 0;
  d_punkty_ruchu = 0;
  gracz = _gracz;
  punkty_zycia = 100;
  d_punkty_zycia = 100;
  atak = 30;
  obrona = 30;
  zwinnosc = 20;
  strcpy(opis, (char*)get_config_string("teksty", "miasto", 0));
  exp = 10;
  poziom = 1;
  doswiadczenie = 0;
  cena = 500;
  do_rozdysp = 0;
  pieniadze = 0;


}

miasto_2::miasto_2(grafika *_engine, mapa *_obsluga_mapy, mapa_jednostek
  *_obsluga_mapy_jednostek, zdarzenia *_obsluga_zdarzen, int _x, int _y, int
  _gracz)
{
  mapa_przejsc = new short[map_szer *map_wys];

  cel = NULL;

  engine = _engine;
  obsluga_mapy = _obsluga_mapy;
  obsluga_mapy_jednostek = _obsluga_mapy_jednostek;
  obsluga_zdarzen = _obsluga_zdarzen;
  wyglad = MIASTO_2;
  x = _x;
  y = _y;
  stan = 0;
  punkty_ruchu = 0;
  d_punkty_ruchu = 0;
  gracz = _gracz;
  punkty_zycia = 100;
  d_punkty_zycia = 100;
  atak = 30;
  obrona = 30;
  zwinnosc = 20;
  strcpy(opis, (char*)get_config_string("teksty", "miasto", 0));
  exp = 10;
  poziom = 1;
  doswiadczenie = 0;
  cena = 500;
  do_rozdysp = 0;
  pieniadze = 0;



}


zamek_gracz_1::zamek_gracz_1(grafika *_engine, mapa *_obsluga_mapy,
  mapa_jednostek *_obsluga_mapy_jednostek, zdarzenia *_obsluga_zdarzen, int _x,
  int _y, int _gracz)
{
  mapa_przejsc = new short[map_szer *map_wys];

  cel = NULL;

  engine = _engine;
  obsluga_mapy = _obsluga_mapy;
  obsluga_mapy_jednostek = _obsluga_mapy_jednostek;
  obsluga_zdarzen = _obsluga_zdarzen;
  wyglad = ZAMEK_GRACZ_1;
  x = _x;
  y = _y;
  stan = 0;
  punkty_ruchu = 0;
  d_punkty_ruchu = 0;
  gracz = _gracz;
  punkty_zycia = 600;
  d_punkty_zycia = 600;
  atak = 95;
  obrona = 90;
  zwinnosc = 40;
  strcpy(opis, (char*)get_config_string("teksty", "white_fort", 0));
  exp = 200;
  poziom = 1;
  doswiadczenie = 0;
  cena = 1000;
  do_rozdysp = 0;
  pieniadze = 0;


}

zamek_gracz_2::zamek_gracz_2(grafika *_engine, mapa *_obsluga_mapy,
  mapa_jednostek *_obsluga_mapy_jednostek, zdarzenia *_obsluga_zdarzen, int _x,
  int _y, int _gracz)
{

  mapa_przejsc = new short[map_szer *map_wys];
  cel = NULL;

  engine = _engine;
  obsluga_mapy = _obsluga_mapy;
  obsluga_mapy_jednostek = _obsluga_mapy_jednostek;
  obsluga_zdarzen = _obsluga_zdarzen;
  wyglad = ZAMEK_GRACZ_2;
  x = _x;
  y = _y;
  stan = 0;
  punkty_ruchu = 0;
  d_punkty_ruchu = 0;
  gracz = _gracz;
  punkty_zycia = 600;
  d_punkty_zycia = 600;
  atak = 95;
  obrona = 90;
  zwinnosc = 40;
  strcpy(opis, (char*)get_config_string("teksty", "dark_fort", 0));
  exp = 200;
  poziom = 1;
  doswiadczenie = 0;
  cena = 1000;
  do_rozdysp = 0;
  pieniadze = 0;

}


ognisty::ognisty(grafika *_engine, mapa *_obsluga_mapy, mapa_jednostek
  *_obsluga_mapy_jednostek, zdarzenia *_obsluga_zdarzen, int _x, int _y, int
  _gracz)
{

  mapa_przejsc = new short[map_szer *map_wys];
  cel = NULL;

  engine = _engine;
  obsluga_mapy = _obsluga_mapy;
  obsluga_mapy_jednostek = _obsluga_mapy_jednostek;
  obsluga_zdarzen = _obsluga_zdarzen;
  wyglad = OGNISTY;
  x = _x;
  y = _y;
  stan = 0;
  punkty_ruchu = 10;
  d_punkty_ruchu = 10;
  gracz = _gracz;
  punkty_zycia = 200;
  d_punkty_zycia = 200;
  atak = 50;
  obrona = 60;
  zwinnosc = 60;
  strcpy(opis, (char*)get_config_string("teksty", "kula_ognista", 0));
  exp = 40;
  poziom = 1;
  doswiadczenie = 0;
  cena = 150;
  do_rozdysp = 0;
  pieniadze = 0;


}

//******************************************************************************


zolnierz::zolnierz(grafika *_engine, mapa *_obsluga_mapy, mapa_jednostek
  *_obsluga_mapy_jednostek, zdarzenia *_obsluga_zdarzen, int _x, int _y, int
  _gracz)
{

  mapa_przejsc = new short[map_szer *map_wys];
  cel = NULL;

  engine = _engine;
  obsluga_mapy = _obsluga_mapy;
  obsluga_mapy_jednostek = _obsluga_mapy_jednostek;
  obsluga_zdarzen = _obsluga_zdarzen;
  wyglad = ZOLNIERZ;
  x = _x;
  y = _y;
  stan = 0;
  punkty_ruchu = 9;
  d_punkty_ruchu = 9;
  gracz = _gracz;
  punkty_zycia = 180;
  d_punkty_zycia = 180;
  atak = 40;
  obrona = 50;
  zwinnosc = 70;
  strcpy(opis, (char*)get_config_string("teksty", "rycerz", 0));
  exp = 20;
  poziom = 1;
  doswiadczenie = 0;
  cena = 100;
  do_rozdysp = 0;
  pieniadze = 0;



}

//******************************************************************************


rycerz::rycerz(grafika *_engine, mapa *_obsluga_mapy, mapa_jednostek
  *_obsluga_mapy_jednostek, zdarzenia *_obsluga_zdarzen, int _x, int _y, int
  _gracz)
{

  mapa_przejsc = new short[map_szer *map_wys];
  cel = NULL;

  engine = _engine;
  obsluga_mapy = _obsluga_mapy;
  obsluga_mapy_jednostek = _obsluga_mapy_jednostek;
  obsluga_zdarzen = _obsluga_zdarzen;
  wyglad = RYCERZ;
  x = _x;
  y = _y;
  stan = 0;
  punkty_ruchu = 10;
  d_punkty_ruchu = 10;
  gracz = _gracz;
  punkty_zycia = 200;
  d_punkty_zycia = 200;
  atak = 50;
  obrona = 60;
  zwinnosc = 60;
  strcpy(opis, (char*)get_config_string("teksty", "lord", 0));
  exp = 40;
  poziom = 1;
  doswiadczenie = 0;
  cena = 150;
  do_rozdysp = 0;
  pieniadze = 0;


}

//******************************************************************************


hydra::hydra(grafika *_engine, mapa *_obsluga_mapy, mapa_jednostek
  *_obsluga_mapy_jednostek, zdarzenia *_obsluga_zdarzen, int _x, int _y, int
  _gracz)
{

  mapa_przejsc = new short[map_szer *map_wys];
  cel = NULL;

  engine = _engine;
  obsluga_mapy = _obsluga_mapy;
  obsluga_mapy_jednostek = _obsluga_mapy_jednostek;
  obsluga_zdarzen = _obsluga_zdarzen;
  wyglad = HYDRA;
  x = _x;
  y = _y;
  stan = 0;
  punkty_ruchu = 8;
  d_punkty_ruchu = 8;
  gracz = _gracz;
  punkty_zycia = 220;
  d_punkty_zycia = 220;
  atak = 70;
  obrona = 50;
  zwinnosc = 40;
  strcpy(opis, (char*)get_config_string("teksty", "hydra", 0));
  exp = 70;
  poziom = 1;
  doswiadczenie = 0;
  cena = 300;
  do_rozdysp = 0;
  pieniadze = 0;

}

//******************************************************************************


archaniol::archaniol(grafika *_engine, mapa *_obsluga_mapy, mapa_jednostek
  *_obsluga_mapy_jednostek, zdarzenia *_obsluga_zdarzen, int _x, int _y, int
  _gracz)
{
  cel = NULL;
  mapa_przejsc = new short[map_szer *map_wys];

  engine = _engine;
  obsluga_mapy = _obsluga_mapy;
  obsluga_mapy_jednostek = _obsluga_mapy_jednostek;
  obsluga_zdarzen = _obsluga_zdarzen;
  wyglad = ARCHANIOL;
  x = _x;
  y = _y;
  stan = 0;
  punkty_ruchu = 8;
  d_punkty_ruchu = 8;
  gracz = _gracz;
  punkty_zycia = 250;
  d_punkty_zycia = 250;
  atak = 80;
  obrona = 70;
  zwinnosc = 60;
  strcpy(opis, (char*)get_config_string("teksty", "archaniol", 0));
  exp = 100;
  poziom = 1;
  doswiadczenie = 0;
  cena = 450;
  do_rozdysp = 0;
  pieniadze = 0;

}

//******************************************************************************


mag::mag(grafika *_engine, mapa *_obsluga_mapy, mapa_jednostek
  *_obsluga_mapy_jednostek, zdarzenia *_obsluga_zdarzen, int _x, int _y, int
  _gracz)
{

  mapa_przejsc = new short[map_szer *map_wys];
  cel = NULL;

  engine = _engine;
  obsluga_mapy = _obsluga_mapy;
  obsluga_mapy_jednostek = _obsluga_mapy_jednostek;
  obsluga_zdarzen = _obsluga_zdarzen;
  wyglad = MAG;
  x = _x;
  y = _y;
  stan = 0;
  punkty_ruchu = 10;
  d_punkty_ruchu = 10;
  gracz = _gracz;
  punkty_zycia = 170;
  d_punkty_zycia = 170;
  atak = 60;
  obrona = 30;
  zwinnosc = 50;
  strcpy(opis, (char*)get_config_string("teksty", "mag", 0));
  exp = 50;
  poziom = 1;
  doswiadczenie = 0;
  cena = 200;
  do_rozdysp = 0;
  pieniadze = 0;


}

smok::smok(grafika *_engine, mapa *_obsluga_mapy, mapa_jednostek
  *_obsluga_mapy_jednostek, zdarzenia *_obsluga_zdarzen, int _x, int _y, int
  _gracz)
{

  mapa_przejsc = new short[map_szer *map_wys];
  cel = NULL;

  engine = _engine;
  obsluga_mapy = _obsluga_mapy;
  obsluga_mapy_jednostek = _obsluga_mapy_jednostek;
  obsluga_zdarzen = _obsluga_zdarzen;
  wyglad = SMOK;
  x = _x;
  y = _y;
  stan = 0;
  punkty_ruchu = 8;
  d_punkty_ruchu = 8;
  gracz = _gracz;
  punkty_zycia = 220;
  d_punkty_zycia = 220;
  atak = 70;
  obrona = 50;
  zwinnosc = 40;
  strcpy(opis, (char*)get_config_string("teksty", "smok", 0));
  exp = 70;
  poziom = 1;
  doswiadczenie = 0;
  cena = 300;
  do_rozdysp = 0;
  pieniadze = 0;

}

ciemny_rycerz::ciemny_rycerz(grafika *_engine, mapa *_obsluga_mapy,
  mapa_jednostek *_obsluga_mapy_jednostek, zdarzenia *_obsluga_zdarzen, int _x,
  int _y, int _gracz)
{

  mapa_przejsc = new short[map_szer *map_wys];
  cel = NULL;

  engine = _engine;
  obsluga_mapy = _obsluga_mapy;
  obsluga_mapy_jednostek = _obsluga_mapy_jednostek;
  obsluga_zdarzen = _obsluga_zdarzen;
  wyglad = CIEMNY_RYCERZ;
  x = _x;
  y = _y;
  stan = 0;
  punkty_ruchu = 9;
  d_punkty_ruchu = 9;
  gracz = _gracz;
  punkty_zycia = 180;
  d_punkty_zycia = 180;
  atak = 40;
  obrona = 50;
  zwinnosc = 70;
  strcpy(opis, (char*)get_config_string("teksty", "ciemny_rycerz", 0));
  exp = 20;
  poziom = 1;
  doswiadczenie = 0;
  cena = 100;
  do_rozdysp = 0;
  pieniadze = 0;

}

lord::lord(grafika *_engine, mapa *_obsluga_mapy, mapa_jednostek
  *_obsluga_mapy_jednostek, zdarzenia *_obsluga_zdarzen, int _x, int _y, int
  _gracz)
{

  mapa_przejsc = new short[map_szer *map_wys];
  cel = NULL;

  engine = _engine;
  obsluga_mapy = _obsluga_mapy;
  obsluga_mapy_jednostek = _obsluga_mapy_jednostek;
  obsluga_zdarzen = _obsluga_zdarzen;
  wyglad = LORD;
  x = _x;
  y = _y;
  stan = 0;
  punkty_ruchu = 10;
  d_punkty_ruchu = 10;
  gracz = _gracz;
  punkty_zycia = 170;
  d_punkty_zycia = 170;
  atak = 60;
  obrona = 30;
  zwinnosc = 50;
  strcpy(opis, (char*)get_config_string("teksty", "arcymag", 0));
  exp = 50;
  poziom = 1;
  doswiadczenie = 0;
  cena = 200;
  do_rozdysp = 0;
  pieniadze = 0;

}

trol::trol(grafika *_engine, mapa *_obsluga_mapy, mapa_jednostek
  *_obsluga_mapy_jednostek, zdarzenia *_obsluga_zdarzen, int _x, int _y, int
  _gracz)
{

  mapa_przejsc = new short[map_szer *map_wys];
  cel = NULL;

  engine = _engine;
  obsluga_mapy = _obsluga_mapy;
  obsluga_mapy_jednostek = _obsluga_mapy_jednostek;
  obsluga_zdarzen = _obsluga_zdarzen;
  wyglad = TROL;
  x = _x;
  y = _y;
  stan = 0;
  punkty_ruchu = 8;
  d_punkty_ruchu = 8;
  gracz = _gracz;
  punkty_zycia = 250;
  d_punkty_zycia = 250;
  atak = 80;
  obrona = 70;
  zwinnosc = 60;
  exp = 100;
  strcpy(opis, (char*)get_config_string("teksty", "trol", 0));
  ;
  poziom = 1;
  doswiadczenie = 0;
  cena = 500;
  do_rozdysp = 0;
  pieniadze = 0;


}

void jednostka::czysc_mape_przejsc()
{
  for (int ii = 0; ii < map_szer *map_wys; ii++)
    mapa_przejsc[ii] = 0;
}

//******************************************************************************

void jednostka::sprawdz_wokol(int _x, int _y)
{
  punkt pom(0, 0);
  pom = obsluga_mapy->start_ekranu();

  bool spelniony[6];
  for (int i = 0; i < 6; i++)
    spelniony[i] = false;
  short ile_ruchow = 1;

  if (mapa_przejsc[_y *map_wys + _x] > 0)
  {
    ile_ruchow = 1;
    if (obsluga_mapy->jakie_pole(_x - 1, _y) == '2' || obsluga_mapy->jakie_pole
      (_x - 1, _y) == '4' || obsluga_mapy->jakie_pole(_x - 1, _y) == '6')
      ile_ruchow = 2;
    if (obsluga_mapy->jakie_pole(_x - 1, _y) == '5')
      ile_ruchow = 3;

    if (obsluga_mapy_jednostek->pobierz_jednostke(_x - 1, _y) == NULL &&
      obsluga_mapy->jakie_pole(_x - 1, _y) != '3' && mapa_przejsc[_y *map_wys +
      _x] - ile_ruchow > mapa_przejsc[_y *map_wys + _x - 1])
    {
      if (mapa_przejsc[_y *map_wys + _x - 1] == 0)
        engine->rysuj_pole(AKTYWNE_POLE, _x - pom.rx() - 1, _y - pom.ry());
      mapa_przejsc[_y *map_wys + _x - 1] = mapa_przejsc[_y *map_wys + _x] -
        ile_ruchow;
      spelniony[0] = true;
    }

    ile_ruchow = 1;
    if (obsluga_mapy->jakie_pole(_x + 1, _y) == '2' || obsluga_mapy->jakie_pole
      (_x + 1, _y) == '4' || obsluga_mapy->jakie_pole(_x + 1, _y) == '6')
      ile_ruchow = 2;
    if (obsluga_mapy->jakie_pole(_x + 1, _y) == '5')
      ile_ruchow = 3;

    if (obsluga_mapy_jednostek->pobierz_jednostke(_x + 1, _y) == NULL &&
      obsluga_mapy->jakie_pole(_x + 1, _y) != '3' && mapa_przejsc[_y *map_wys +
      _x] - ile_ruchow > mapa_przejsc[_y *map_wys + _x + 1])
    {
      if (mapa_przejsc[_y *map_wys + _x + 1] == 0)
        engine->rysuj_pole(AKTYWNE_POLE, _x - pom.rx() + 1, _y - pom.ry());
      mapa_przejsc[_y *map_wys + _x + 1] = mapa_przejsc[_y *map_wys + _x] -
        ile_ruchow;
      spelniony[1] = true;
    }

    ile_ruchow = 1;
    if (obsluga_mapy->jakie_pole(_x - 1+_y % 2, _y - 1) == '2' || obsluga_mapy
      ->jakie_pole(_x - 1+_y % 2, _y - 1) == '4' || obsluga_mapy->jakie_pole(_x
      - 1+_y % 2, _y - 1) == '6')
      ile_ruchow = 2;
    if (obsluga_mapy->jakie_pole(_x - 1+_y % 2, _y - 1) == '5')
      ile_ruchow = 3;

    if (obsluga_mapy_jednostek->pobierz_jednostke(_x - 1+_y % 2, _y - 1) ==
      NULL && obsluga_mapy->jakie_pole(_x - 1+_y % 2, _y - 1) != '3' &&
      mapa_przejsc[_y *map_wys + _x] - ile_ruchow > mapa_przejsc[(_y - 1)
      *map_wys + _x - 1+_y % 2])
    {
      if (mapa_przejsc[(_y - 1) *map_wys + _x - 1+_y % 2] == 0)
        engine->rysuj_pole(AKTYWNE_POLE, _x - pom.rx() - 1+_y % 2, _y - pom.ry()
          - 1);
      mapa_przejsc[(_y - 1) *map_wys + _x - 1+_y % 2] = mapa_przejsc[_y
        *map_wys + _x] - ile_ruchow;
      spelniony[2] = true;
    }

    ile_ruchow = 1;
    if (obsluga_mapy->jakie_pole(_x + _y % 2, _y - 1) == '2' || obsluga_mapy
      ->jakie_pole(_x + _y % 2, _y - 1) == '4' || obsluga_mapy->jakie_pole(_x +
      _y % 2, _y - 1) == '6')
      ile_ruchow = 2;
    if (obsluga_mapy->jakie_pole(_x + _y % 2, _y - 1) == '5')
      ile_ruchow = 3;

    if (obsluga_mapy_jednostek->pobierz_jednostke(_x + _y % 2, _y - 1) == NULL
      && obsluga_mapy->jakie_pole(_x + _y % 2, _y - 1) != '3' &&
      mapa_przejsc[_y *map_wys + _x] - ile_ruchow > mapa_przejsc[(_y - 1)
      *map_wys + _x + _y % 2])
    {
      if (mapa_przejsc[(_y - 1) *map_wys + _x + _y % 2] == 0)
        engine->rysuj_pole(AKTYWNE_POLE, _x - pom.rx() + _y % 2, _y - pom.ry() 
          - 1);
      mapa_przejsc[(_y - 1) *map_wys + _x + _y % 2] = mapa_przejsc[_y *map_wys 
        + _x] - ile_ruchow;
      spelniony[3] = true;
    }

    ile_ruchow = 1;
    if (obsluga_mapy->jakie_pole(_x - 1+_y % 2, _y + 1) == '2' || obsluga_mapy
      ->jakie_pole(_x - 1+_y % 2, _y + 1) == '4' || obsluga_mapy->jakie_pole(_x
      - 1+_y % 2, _y + 1) == '6')
      ile_ruchow = 2;
    if (obsluga_mapy->jakie_pole(_x - 1+_y % 2, _y + 1) == '5')
      ile_ruchow = 3;

    if (obsluga_mapy_jednostek->pobierz_jednostke(_x - 1+_y % 2, _y + 1) ==
      NULL && obsluga_mapy->jakie_pole(_x - 1+_y % 2, _y + 1) != '3' &&
      mapa_przejsc[_y *map_wys + _x] - ile_ruchow > mapa_przejsc[(_y + 1)
      *map_wys + _x - 1+_y % 2])
    {
      if (mapa_przejsc[(_y + 1) *map_wys + _x - 1+_y % 2] == 0)
        engine->rysuj_pole(AKTYWNE_POLE, _x - pom.rx() - 1+_y % 2, _y - pom.ry()
          + 1);
      mapa_przejsc[(_y + 1) *map_wys + _x - 1+_y % 2] = mapa_przejsc[_y
        *map_wys + _x] - ile_ruchow;
      spelniony[4] = true;
    }

    ile_ruchow = 1;
    if (obsluga_mapy->jakie_pole(_x + _y % 2, _y + 1) == '2' || obsluga_mapy
      ->jakie_pole(_x + _y % 2, _y + 1) == '4' || obsluga_mapy->jakie_pole(_x +
      _y % 2, _y + 1) == '6')
      ile_ruchow = 2;
    if (obsluga_mapy->jakie_pole(_x + _y % 2, _y + 1) == '5')
      ile_ruchow = 3;

    if (obsluga_mapy_jednostek->pobierz_jednostke(_x + _y % 2, _y + 1) == NULL
      && obsluga_mapy->jakie_pole(_x + _y % 2, _y + 1) != '3' &&
      mapa_przejsc[_y *map_wys + _x] - ile_ruchow > mapa_przejsc[(_y + 1)
      *map_wys + _x + _y % 2])
    {
      if (mapa_przejsc[(_y + 1) *map_wys + _x + _y % 2] == 0)
        engine->rysuj_pole(AKTYWNE_POLE, _x - pom.rx() + _y % 2, _y - pom.ry() 
          + 1);
      mapa_przejsc[(_y + 1) *map_wys + _x + _y % 2] = mapa_przejsc[_y *map_wys 
        + _x] - ile_ruchow;
      spelniony[5] = true;
    }
    if (spelniony[0])
      sprawdz_wokol(_x - 1, _y);
    if (spelniony[1])
      sprawdz_wokol(_x + 1, _y);
    if (spelniony[2])
      sprawdz_wokol(_x - 1+_y % 2, _y - 1);
    if (spelniony[3])
      sprawdz_wokol(_x + _y % 2, _y - 1);
    if (spelniony[4])
      sprawdz_wokol(_x - 1+_y % 2, _y + 1);
    if (spelniony[5])
      sprawdz_wokol(_x + _y % 2, _y + 1);


  }

}




//******************************************************************************

/// konstruktor budujacy mape
/// - alokujacy pamiec na tablice wskaznikow do jednostek
mapa_jednostek::mapa_jednostek()
{
  tab = new jednostka *[map_wys *map_szer];
  for (int i = 0; i < map_szer *map_wys; i++)
    tab[i] = NULL;
}

/// destruktor zwalnia pamiec przydzielona na mape wskaznikow do jednostek
mapa_jednostek::~mapa_jednostek()
{
  delete [] tab;
}

//******************************************************************************

/// funkcja wstawia adres jednostki - j do tablicy wskaznikow do jednostek, czyli mapy,
/// w miejscu, w ktorym aktualnie sie znajduje
void mapa_jednostek::wstaw_jednostke(jednostka *j)
{
  int pozycja = j->pobierz_y() *map_wys + j->pobierz_x();
  if(pozycja>=0 && pozycja<= map_wys*map_wys+map_szer) tab[pozycja] = j;
}

//******************************************************************************

/// funkcja zwraca adres do jednostki znajdujacej sie miejscu o wspolrzednych (x,y)
jednostka *mapa_jednostek::pobierz_jednostke(int x, int y)
{
  int pozycja = y * map_wys + x;
  if(pozycja>=0 && pozycja<=map_wys*map_wys+map_szer) 
	return tab[pozycja];
  else
	return NULL;
}

//******************************************************************************

/// funkcja zeruje adres na mapie wskaznikow o wspolrzednych (x,y)
void mapa_jednostek::zeruj_pole(int x, int y)
{
  int pozycja = y * map_wys + x;
  if(pozycja>=0 && pozycja<= map_wys*map_wys+map_szer) tab[pozycja] = NULL;
}

//******************************************************************************

armia::armia()
{
  gracz =  - 1;
  nastepny = NULL;
  aktywna = NULL;
  oddzial = NULL;
}

//******************************************************************************

/// konstruktor klasy armia uruchamia konstruktory jednostek podanych w arhumencie nazwa
armia::armia(nazwa_pola nazwa, int _gracz, grafika *_engine, mapa
  *_obsluga_mapy, mapa_jednostek *_obsluga_mapy_jednostek, zdarzenia
  *_obsluga_zdarzen, int _x, int _y, bool czy_heros = false)
{
  gracz = _gracz;
  nastepny = NULL;
  aktywna = NULL;
  oddzial = NULL;
  obsluga_mapy_jednostek = _obsluga_mapy_jednostek;
  set_config_file(ajezyk);
  switch (nazwa)
  {
    case ROBOTNIK_1:
      oddzial = new robotnik_1(_engine, _obsluga_mapy, _obsluga_mapy_jednostek,
        _obsluga_zdarzen, _x, _y, _gracz);
      break;
    case ROBOTNIK_2:
      oddzial = new robotnik_2(_engine, _obsluga_mapy, _obsluga_mapy_jednostek,
        _obsluga_zdarzen, _x, _y, _gracz);
      break;
    case OGNISTY:
      oddzial = new ognisty(_engine, _obsluga_mapy, _obsluga_mapy_jednostek,
        _obsluga_zdarzen, _x, _y, _gracz);
      break;
    case ZOLNIERZ:
      oddzial = new zolnierz(_engine, _obsluga_mapy, _obsluga_mapy_jednostek,
        _obsluga_zdarzen, _x, _y, _gracz);
      break;
    case RYCERZ:
      oddzial = new rycerz(_engine, _obsluga_mapy, _obsluga_mapy_jednostek,
        _obsluga_zdarzen, _x, _y, _gracz);
      break;
    case HYDRA:
      oddzial = new hydra(_engine, _obsluga_mapy, _obsluga_mapy_jednostek,
        _obsluga_zdarzen, _x, _y, _gracz);
      break;
    case ARCHANIOL:
      oddzial = new archaniol(_engine, _obsluga_mapy, _obsluga_mapy_jednostek,
        _obsluga_zdarzen, _x, _y, _gracz);
      break;
    case MAG:
      oddzial = new mag(_engine, _obsluga_mapy, _obsluga_mapy_jednostek,
        _obsluga_zdarzen, _x, _y, _gracz);
      break;
    case SMOK:
      oddzial = new smok(_engine, _obsluga_mapy, _obsluga_mapy_jednostek,
        _obsluga_zdarzen, _x, _y, _gracz);
      break;
    case LORD:
      oddzial = new lord(_engine, _obsluga_mapy, _obsluga_mapy_jednostek,
        _obsluga_zdarzen, _x, _y, _gracz);
      break;
    case CIEMNY_RYCERZ:
      oddzial = new ciemny_rycerz(_engine, _obsluga_mapy,
        _obsluga_mapy_jednostek, _obsluga_zdarzen, _x, _y, _gracz);
      break;
    case TROL:
      oddzial = new trol(_engine, _obsluga_mapy, _obsluga_mapy_jednostek,
        _obsluga_zdarzen, _x, _y, _gracz);
      break;
    case WIEZA_1:
      oddzial = new wieza_1(_engine, _obsluga_mapy, _obsluga_mapy_jednostek,
        _obsluga_zdarzen, _x, _y, _gracz);
      break;
    case WIEZA_2:
      oddzial = new wieza_2(_engine, _obsluga_mapy, _obsluga_mapy_jednostek,
        _obsluga_zdarzen, _x, _y, _gracz);
      break;
    case MIASTO_1:
      oddzial = new miasto_1(_engine, _obsluga_mapy, _obsluga_mapy_jednostek,
        _obsluga_zdarzen, _x, _y, _gracz);
      break;
    case MIASTO_2:
      oddzial = new miasto_2(_engine, _obsluga_mapy, _obsluga_mapy_jednostek,
        _obsluga_zdarzen, _x, _y, _gracz);
      break;
    case ZAMEK_GRACZ_1:
      oddzial = new zamek_gracz_1(_engine, _obsluga_mapy,
        _obsluga_mapy_jednostek, _obsluga_zdarzen, _x, _y, _gracz);
      break;
    case ZAMEK_GRACZ_2:
      oddzial = new zamek_gracz_2(_engine, _obsluga_mapy,
        _obsluga_mapy_jednostek, _obsluga_zdarzen, _x, _y, _gracz);
      break;
  }
  oddzial->zmien_id(nowe_id);
  nowe_id++;
  /// jesli heros to ma statsy x2
  if (czy_heros)
  {
    oddzial->zwieksz_atak(oddzial->pobierz_atak());
    oddzial->zwieksz_obrone(oddzial->pobierz_obrona());
    oddzial->zwieksz_zwinnosc(oddzial->pobierz_zwinnosc());
    _obsluga_zdarzen->wyswietl_okno(4);
  }
  /// wstawianie jednostki na mape jednostek chyba ze juz tam stoi inna (np. zamek przy kupowaniu)
  /// lub ma pozycje (-1, -1) co oznacza, ¿e jest tylko jednostka do kupienia.
  if (_x !=  - 1 && _y !=  - 1)
    if (!obsluga_mapy_jednostek->pobierz_jednostke(_x, _y))
      obsluga_mapy_jednostek->wstaw_jednostke(oddzial);
}

//******************************************************************************

/// funkcja dodaje jednostke o podanej nazwie na koniec listy jednostek
void armia::dodaj(nazwa_pola nazwa, int _gracz, grafika *_engine, mapa
  *_obsluga_mapy, mapa_jednostek *_obsluga_mapy_jednostek, zdarzenia
  *_obsluga_zdarzen, int _x, int _y, bool czy_heros = false)
{
  armia *pocz = this;
  while (pocz->nastepny != NULL)
    pocz = pocz->nastepny;
  pocz->nastepny = new armia(nazwa, _gracz, _engine, _obsluga_mapy,
    _obsluga_mapy_jednostek, _obsluga_zdarzen, _x, _y, czy_heros);
}

//******************************************************************************

/// funkcja usuwa atkualny element listy
void armia::usun()
{
  this->oddzial = this->nastepny->oddzial;
  this->gracz = this->nastepny->gracz;
  this->nastepny = this->nastepny->nastepny;
  delete this->nastepny;
}

//******************************************************************************

/// funkcja analizuje kazda jednostke na liscie i:
///   - sprawdza czy jednostka zosta³a klikniêta
///   - ustala, ktora jednostka jest aktualnie aktywna
///   - rysuje jednostki

/// zwraca liczbe miast
short armia::aktualizuj(int tura)
{
  armia *pocz = this;
  short l_miast = 0;

  int pom;
  while (pocz != NULL)
  {
    /// analizujemy tylko jednostki gracza ktory ma ruch
    if (pocz->oddzial->pobierz_gracz() == tura)
    {

      pom = pocz->oddzial->obsluga();

      if (tura == ai){}
      else if (multi_tura > 0)
      {
        if (tura != multi_tura)
          pom = false;
      }

      /// jesli jednostka zostala kliknieta oraz nie ma wybranej jednostki aktywnej 
      /// to zmienia jej stan na 1 ma ruch oraz jest aktywna), a takze ustawia aktualnie
      /// aktywna jednostke na ta wybrana
      if (pom && aktywna == NULL)
      {
        aktywna = pocz->oddzial;
        aktywna->zmien_stan(1);
      }
      /// jesli jednostka zostala kliknieta ale aktywna jednostka zostala juz wybrana
      /// i nie jest ni¹ jednostka bie¿¹ca (na liœcie) to zmienia stan biezacej jednostki
      /// na 1 (aktywna oraz ma ruch), natomiast jednostka, ktora wczesniej byla aktywna
      /// staje sie nieaktywna, a aktualnie wybrana aktywna jednostka staje sie jednostka
      /// biezaca.
      else if (pom && aktywna != NULL && aktywna != pocz->oddzial)
      {
        pocz->oddzial->zmien_stan(1);
        aktywna->zmien_stan(0);
        aktywna = pocz->oddzial;
      }
      if (pocz->oddzial->pobierz_punkty_zycia() > 0 && pocz->oddzial
        ->pobierz_wyglad() == MIASTO_1)
        l_miast++;
      if (pocz->oddzial->pobierz_punkty_zycia() > 0 && pocz->oddzial
        ->pobierz_wyglad() == MIASTO_2)
        l_miast++;
    }
    /// rysowanie danej jednostki
    pocz->oddzial->rysuj();

    /// przejscie do nastepnej jednostki na liscie
    pocz = pocz->nastepny;

  }
  return l_miast;
}

//******************************************************************************

jednostka *armia::zwroc_aktywna()
{
  return aktywna;
}

//******************************************************************************

/// funkcja przywraca standardowe parametry jednostkom zywym(uzyta na koniec tury,
/// po to aby w nastepnej turze mialy punkty ruchu.
void armia::zeruj_jednostki()
{
  armia *pocz = this;

  while (pocz != NULL)
  {
    /// wybieramy tylko zywe jednostki
    if (pocz->oddzial->pobierz_punkty_zycia() > 0)
    {
      /// zmieniamy im stan na 0, czyli nieaktywne
      pocz->oddzial->zmien_stan(0);
      /// przywracamy im standardowe punkty ruchu
      pocz->oddzial->przywroc_punkty_ruchu( - 1);
      /// przejscie do nastepnej jednostki na liscie
      pocz = pocz->nastepny;
    }
    else
    {
      /// jesli jednostka nie zyje to zmieniamy jej stan na 2, czyli tak jakby zakonczyla swoj ruch
      pocz->oddzial->zmien_stan(2);
      pocz = pocz->nastepny;
    }
  }

}


bool armia::czy_koniec_tury(int tura)
{
  armia *pocz = this;

  while (pocz != NULL)
  {
    /// wybieramy tylko zywe jednostki
    if (pocz->oddzial->pobierz_gracz() == tura && pocz->oddzial
      ->pobierz_punkty_ruchu() > 0 && pocz->oddzial->pobierz_punkty_zycia() > 0
      && pocz->oddzial->pobierz_wyglad() != WIEZA_1 && pocz->oddzial
      ->pobierz_wyglad() != WIEZA_2 && pocz->oddzial->pobierz_wyglad() !=
      MIASTO_1 && pocz->oddzial->pobierz_wyglad() != MIASTO_2)
      return false;
    pocz = pocz->nastepny;
  }

  return true;

}


jednostka *armia::zwroc_ostatnia()
{
  armia *pocz = this;

  while (pocz->nastepny != NULL)
  {
    pocz = pocz->nastepny;
  }
  return pocz->oddzial;

}

void armia::zapisz_jednostki(short nr)
{
  FILE *plik;
  if (nr == 1)
    plik = fopen("Zapisane_gry/1.sav", "a");
  if (nr == 2)
    plik = fopen("Zapisane_gry/2.sav", "a");
  if (nr == 3)
    plik = fopen("Zapisane_gry/3.sav", "a");
  if (nr == 4)
    plik = fopen("Zapisane_gry/4.sav", "a");
  if (nr == 5)
    plik = fopen("Zapisane_gry/5.sav", "a");

  armia *pocz = this;
  char pom;

  while (pocz != NULL)
  {
    /// wybieramy tylko zywe jednostki
    if (pocz->oddzial->pobierz_punkty_zycia() > 0 && pocz->oddzial
      ->pobierz_gracz() != 0)
    {
      switch (pocz->oddzial->pobierz_wyglad())
      {
        case WIEZA_1:
          pom = 'M';
          break;
        case WIEZA_2:
          pom = 'J';
          break;
        case MIASTO_1:
          pom = 'K';
          break;
        case MIASTO_2:
          pom = 'L';
          break;
        case ROBOTNIK_1:
          pom = 'Q';
          break;
        case ROBOTNIK_2:
          pom = 'W';
          break;
        case ZAMEK_GRACZ_1:
          pom = 'Z';
          break;
        case ZOLNIERZ:
          pom = 'X';
          break;
        case HYDRA:
          pom = 'C';
          break;
        case ARCHANIOL:
          pom = 'V';
          break;
        case MAG:
          pom = 'B';
          break;
        case RYCERZ:
          pom = 'N';
          break;
        case ZAMEK_GRACZ_2:
          pom = 'A';
          break;
        case OGNISTY:
          pom = 'S';
          break;
        case SMOK:
          pom = 'D';
          break;
        case TROL:
          pom = 'F';
          break;
        case CIEMNY_RYCERZ:
          pom = 'G';
          break;
        case LORD:
          pom = 'H';
          break;
      }

      fprintf(plik, "%c %d %d %d %d %d %d %d %d %d %d %d %d %d %d ", pom, pocz
        ->oddzial->pobierz_gracz(), pocz->oddzial->pobierz_x(), pocz->oddzial
        ->pobierz_y(), pocz->oddzial->pobierz_punkty_zycia(), pocz->oddzial
        ->pobierz_d_punkty_zycia(), pocz->oddzial->pobierz_punkty_ruchu(), pocz
        ->oddzial->pobierz_atak(), pocz->oddzial->pobierz_obrona(), pocz
        ->oddzial->pobierz_zwinnosc(), pocz->oddzial
        ->pobierz_do_rozdysponowania(), pocz->oddzial->pobierz_poziom(), pocz
        ->oddzial->pobierz_doswiadczenie(), pocz->oddzial->pobierz_exp(), pocz
        ->oddzial->pobierz_pieniadze());

    }
    pocz = pocz->nastepny;

  }

  fprintf(plik, "E");

  fclose(plik); // zamkniêcie pliku

}

//******************************************************************************

/// funkcja uzyta do przycisku zakoncz ture, jej dzialanie polega na tym, ze
/// zyjacym jeszcze jednostkom ustawia punkty ruchu na 0, by zakonczyly ruch
/// natomiast jednostkom martwym ustala stan na 2 czyli sa aktywne ale nie maja ruchu

void armia::zakoncz_ture()
{
  armia *pocz = this;

  while (pocz != NULL)
  {
    if (pocz->oddzial->pobierz_punkty_zycia() > 0)
    {
      pocz->oddzial->przywroc_punkty_ruchu(0);
      pocz->oddzial->ulecz(5);
      pocz = pocz->nastepny;
    }
    else
    {
      pocz->oddzial->przywroc_punkty_ruchu(0);
      pocz->oddzial->zmien_stan(2);
      pocz = pocz->nastepny;
    }
  }

}

//******************************************************************************

/// funkcja przeglada liste i aktywuje pierwsza zyjaca napotkana jednostke gracza
/// ktory aktualnie ma ruch (ture)
void armia::zaznacz_pierwsza(int tura)
{
  armia *pocz = this;

  while (pocz != NULL)
  {
    if (tura == pocz->gracz)
    {
      if (pocz->oddzial->pobierz_punkty_zycia() > 0 && pocz->oddzial
        ->pobierz_punkty_ruchu() > 0)
      // nie chcemy aktywowac martwej jednostki
      {
        pocz->oddzial->zmien_stan(1);
        aktywna = pocz->oddzial;
        break;
      }
    }
    pocz = pocz->nastepny;
  }
}

//******************************************************************************

/// funkcja przeszukuje liste jednostek i zwraca pierwsz¹ o podanym wygl¹dzie
jednostka *armia::zwroc_jednostke(nazwa_pola _wyglad)
{
  armia *pocz = this;

  while (pocz != NULL)
  {

    if (pocz != NULL)
      if (pocz->oddzial != NULL)
    if (pocz->oddzial->pobierz_wyglad() == _wyglad)
    {

      return pocz->oddzial;
    }
    pocz = pocz->nastepny;
  }
  return NULL;
}

jednostka *armia::zwroc_jednostke_id(int _id)
{
  armia *pocz = this;

  while (pocz != NULL)
  {

    if (pocz != NULL)
      if (pocz->oddzial != NULL)
    if (pocz->oddzial->pobierz_id() == _id)
    {

      return pocz->oddzial;
    }
    pocz = pocz->nastepny;
  }
  return NULL;
}


//******************************************************************************


/// funkcja przeglada wszystkie jednostki na liscie i umieszcza je na mapie
/// jednostek, tak by wiadomo jaka jednostka znajduje sie na danym polu
void armia::inicjalizuj_mape_jednostek()
{
  armia *pocz = this;

  while (pocz != NULL)
  {
    obsluga_mapy_jednostek->wstaw_jednostke(pocz->oddzial);
    pocz = pocz->nastepny;
  }
}

//******************************************************************************

/// destruktor klasy armia
armia::~armia()
{
  while (this->nastepny != NULL)
  {
    this->usun();
  }
  this->nastepny = NULL;
  this->oddzial = NULL;
  this->gracz =  - 1;
  delete oddzial;
}

#include "gra.h"
