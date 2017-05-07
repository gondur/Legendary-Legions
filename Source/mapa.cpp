/// konstruktor pobiera adres obiektu engine graficzny oraz sciezke do pliku z mapa
mapa::mapa(grafika *_engine, char *nazwa_pliku)
{
  if (multiplayer == 1)
    nazwa_pliku = "Pliki_danych/Mapy/mapnet.map";
  przesuniecie = 0;

  engine = _engine; /// inicjujemy mape poprzez ustalenie aktualnego enginu oraz
  ekran_szer = 27; /// szerokosci i wysokoœci kadru mapy
  ekran_wys = 20;

  /// ustalanie pocz¹tkowego punktu na mapie, który staje siê œrodkiem ekranu
  srodek.wpisz(1, ekran_szer / 2);
  srodek.wpisz(2, ekran_wys / 2);

  char z; /// zmienna pomocnicza do czytania pliku bajt po bajcie


  plik = fopen(nazwa_pliku, "r"); // otwieranie pliku z map¹

  wysokosc = 60; /// tutaj domyœlnie mapa ma szerokosc i wysokosc 30
  szerokosc = 60;

  pola = new char[wysokosc *szerokosc]; // rezerwacja pamiêci na mape
  int pozycja = 0; // zmienna pomocnicza

  while ((z = getc(plik)) != EOF)
  // wczytywanie bajt po bajcie mape z pliku do pamiêci
  {
    pola[pozycja++] = z;
  }

  fclose(plik); // zamkniêcie pliku
  strcpy(plik_mapy, nazwa_pliku);

}

//******************************************************************************

char *mapa::zwroc_nazwe()
{
  return plik_mapy;
}

//******************************************************************************

mapa::~mapa()
{
  /// usuwanie mapy z pamiêci
  delete [] pola;
}

//******************************************************************************

void mapa::wstaw(short co)
{
  int x = klikniete.rx();
  int y = klikniete.ry();
  if (co == 1)
    pola[y *szerokosc + x] = '1';
  if (co == 2)
    pola[y *szerokosc + x] = '2';
  if (co == 3)
    pola[y *szerokosc + x] = '3';
  if (co == 4)
    pola[y *szerokosc + x] = '4';
  if (co == 5)
    pola[y *szerokosc + x] = '5';
  if (co == 6)
    pola[y *szerokosc + x] = '6';
  if (co == 7)
    pola[y *szerokosc + x] = '7';
  if (co == 8)
    pola[y *szerokosc + x] = '8';
  if (co == 9)
  {
    FILE *zapamietaj = fopen("Pliki_danych/Mapy/map4.map", "w+");
    //fputc(pola, zapamietaj);
    for (int k = 0; k < szerokosc *wysokosc; k++)
      fputc(pola[k], zapamietaj);
    fclose(zapamietaj);
  }
}

//******************************************************************************

/// funkcja wyswietla na ekran kadr mapy
void mapa::pokaz()
{
  /// zmienna pomocnicza przechowuj¹ca koniec kadru mapy
  int koniec_x, koniec_y;

  /// zmienna slu¿¹ca do przechowywania aktualnego indeksu w tablicy pole
  int pozycja = 0;

  /// zmienne pomocnicze
  int i = 0, j = 0;
  int x, y;

  /// Ustalamy kadr jako prostokat o szerokosci ekran_szer i wysokosci ekran_wys
  /// oraz jego srodek. Przy czym sprawdzamy czy kadr nie wyje¿d¿a poza granice mapy
  if ((start_x = srodek.rx() - ekran_szer / 2) < 0)
    start_x = 0;
  if ((start_y = srodek.ry() - ekran_wys / 2) < 0)
    start_y = 0;
  if ((koniec_x = start_x + ekran_szer) > szerokosc)
    koniec_x = szerokosc;
  if ((koniec_y = start_y + ekran_wys) > wysokosc)
    koniec_y = wysokosc;

  /// zapobie¿ pokazywaniu pustych(czarnych) pól (ekran nie mo¿e 'wyjechac' poza mape)
  if (szerokosc - start_x < ekran_szer)
    if ((start_x = szerokosc - ekran_szer) % 2)
      start_x++;
  if (wysokosc - start_y < ekran_wys)
    if ((start_y = wysokosc - ekran_wys) % 2)
      start_y++;

  /// utworzony kadr pos³u¿y do wczytania przez niego wyznaczonego fragmentu mapy.

  /// RYSUJEMY NAJPIERW TYLKO POLA NA KTORE MA PRZECHODZIC INNE
  for (y = start_y; y < koniec_y; y++)
  {
    i = 0;
    for (x = start_x; x < koniec_x; x++)
    {
      pozycja = y * szerokosc + x;

      /// Okreœla jaki typ pola znajduje siê pod indeksem pozycja i rysuje dana bitmape.
      if (pola[pozycja] == '3')
        engine->rysuj_pole(WODA, i, j);
      if (pola[pozycja] == '1')
        engine->rysuj_pole(TRAWA, i, j);
      if (pola[pozycja] == '7')
        engine->rysuj_pole(SPALONA_ZIEMIA, i, j);
      if (pola[pozycja] == '8')
        engine->rysuj_pole(PUSTYNIA, i, j);
      if (pola[pozycja] == '4')
        engine->rysuj_pole(LAWA, i, j);
      if (pola[pozycja] == '6')
        engine->rysuj_pole(LAWA_2, i, j);

      i++;
    }
    j++;
  }

  /// a teraz reszte z przejsciami
  j = 0;
  for (y = start_y; y < koniec_y; y++)
  {
    i = 0;
    for (x = start_x; x < koniec_x; x++)
    {
      pozycja = y * szerokosc + x;

      /// Okreœla jaki typ pola znajduje siê pod indeksem pozycja i rysuje dana bitmape.
      /// na te pola nie moga nachodzic inne
      if (pola[pozycja] == '2')
        engine->rysuj_pole(LAS, i, j);
      if (pola[pozycja] == '5')
        engine->rysuj_pole(GORA, i, j);


      /// przejscia :D
      /// Chodzi tu o to, ze przechodzic moze w dany sposob pole ktore spelnia pierwszy
      /// warunek. Gdy zostanie spelniony to sprawdza czy przypadkiem sasiednie pole sie
      /// rowna jednemu z tablicy. Jesli tak to mozna rysowac przejscie.

      /// jak wyglada pole ktore przechodzi
      nazwa_pola aktualne_pole[6];
      aktualne_pole[0] = TRAWA;
      aktualne_pole[1] = SPALONA_ZIEMIA;
      aktualne_pole[2] = SPALONA_ZIEMIA;
      aktualne_pole[3] = PUSTYNIA;
      aktualne_pole[4] = GORA;
      aktualne_pole[5] = LAS;

      /// pola ktore przechodza w dany sposob
      char przechodza[3];

      /// pola na ktore moze nachodzic dane pole
      char moze[10];

      for (int zmiana = 0; zmiana < 6; zmiana++)
      {

        switch (zmiana)
        {
          /// dla trawy (te cyferki znacza, ze pola 1,2 i 5 przechodza trawa na pola 1,2,3,4,6,7
          case 0:
            {
              strcpy(przechodza, "100");
              strcpy(moze, "3467");
              break;
            }
            /// dla spalonej ziemi
          case 1:
            {
              strcpy(przechodza, "700");
              strcpy(moze, "346");
              break;
            }

            /// dla lawy2
          case 2:
            {
              strcpy(przechodza, "600");
              strcpy(moze, "34");
              break;
            }

            /// dla pustyni
          case 3:
            {
              strcpy(przechodza, "800");
              strcpy(moze, "13467");
              break;
            }

            /// dla gor
          case 4:
            {
              strcpy(przechodza, "500");
              strcpy(moze, "1378");
              break;
            }

            /// dla lasu
          case 5:
            {
              strcpy(przechodza, "200");
              strcpy(moze, "137");
              break;
            }

        }

        if (pola[pozycja] == przechodza[0] || pola[pozycja] == przechodza[1] ||
          pola[pozycja] == przechodza[2])
        {
          for (int m = 0; m < strlen(moze); m++)
          {
            if (pola[pozycja + 1] == moze[m])
              engine->rysuj_pole(aktualne_pole[zmiana], i + 1, j, 5);
            if (pola[pozycja - 1] == moze[m])
              engine->rysuj_pole(aktualne_pole[zmiana], i - 1, j, 6);
            if (j % 2 != 0)
            {
              if (pola[pozycja - szerokosc] == moze[m])
                engine->rysuj_pole(aktualne_pole[zmiana], i, j - 1, 3);
              if (pola[pozycja + szerokosc] == moze[m])
                engine->rysuj_pole(aktualne_pole[zmiana], i, j + 1, 2);

              if (pola[pozycja - szerokosc + 1] == moze[m])
                engine->rysuj_pole(aktualne_pole[zmiana], i + 1, j - 1, 4);
              if (pola[pozycja + szerokosc + 1] == moze[m])
                engine->rysuj_pole(aktualne_pole[zmiana], i + 1, j + 1, 1);
            }
            if (j % 2 == 0)
            {
              if (pola[pozycja - szerokosc - 1] == moze[m])
                engine->rysuj_pole(aktualne_pole[zmiana], i - 1, j - 1, 3);
              if (pola[pozycja + szerokosc - 1] == moze[m])
                engine->rysuj_pole(aktualne_pole[zmiana], i - 1, j + 1, 2);

              if (pola[pozycja - szerokosc] == moze[m])
                engine->rysuj_pole(aktualne_pole[zmiana], i, j - 1, 4);
              if (pola[pozycja + szerokosc] == moze[m])
                engine->rysuj_pole(aktualne_pole[zmiana], i, j + 1, 1);
            }
          }
        }
      }


      i++;
    }
    j++;
  }





}

//******************************************************************************

/// funkcja rysuje miniature mapy w podanej pozycji (pozX, pozY) na ekranie i 
/// wybranym powiekszeniu zoom
void mapa::miniatura(int pozX, int pozY, int zoom)
{
  int pozycja = 0;

  /// zmienne pomocnicze
  int pomX;
  int pomY;

  /// ustalanie kadru miniatury mapy
  int kadrX = pozX + srodek.rx() *zoom - ekran_szer / 2 * zoom;
  int kadrY = pozY + srodek.ry() *zoom - ekran_wys / 2 * zoom;

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
  /// rysowanie kadru miniatury mapy (bialy, niewype³niony prostok¹t)
  engine->prostokat(kadrX, kadrY, (kadrX - 2) + ekran_szer * zoom, kadrY + 
    (ekran_wys - 1) *zoom, makecol(255, 255, 255), false);
}

//******************************************************************************

/// Funkcja sprawdza czy zadana wspolrzedna jest w zasiegu kadru ekranu jesli 
/// tak to zwraca wartosc true.
bool mapa::czy_na_ekranie(int x, int y)
{
  if (x >= start_x && x <= start_x + ekran_szer && y >= start_y && y <= start_y
    + ekran_wys)
    return true;
  else
    return false;
}

//******************************************************************************

/// zwraca wspolrzedne poczatku ekranu
punkt mapa::start_ekranu()
{
  punkt poczatek(start_x, start_y);
  return poczatek;
}

//******************************************************************************

/// funkcja s³u¿y do zmiany kadru mapy tak by po przesuniêciu kursora na krañce ekranu
/// mapka siê przesuwa³a
punkt mapa::wysrodkuj()
{
    // pom dla chmur
    int pom_x = srodek.rx();
    int pom_y = srodek.ry();
  // 4 oznacza, ze co 4 klatki nastapi przesuniecie
  przesuniecie += 1;
  if (przesuniecie > 4)
    przesuniecie = 0;

  if (przesuniecie == 0)
  {
    if (mouse_x > 924 && srodek.rx() < szerokosc - ekran_szer / 2)
      srodek.wpisz(1, srodek.rx() + 1);
    if (mouse_x < 100 && srodek.rx() > ekran_szer / 2)
      srodek.wpisz(1, srodek.rx() - 1);
    if (mouse_y > 766 && mouse_y <= 768 && srodek.ry() < szerokosc - ekran_wys
      / 2)
      srodek.wpisz(2, srodek.ry() + 2);
    
      // tu wyjatkowo inaczej aby nie przesuwalo mapy gdy myszka jest na interfejsie
    if (mouse_y < 100 && srodek.ry() > ekran_wys / 2)
      srodek.wpisz(2, srodek.ry() - 2);

    // przyspieszenie - jeœli kursor jest blizej krawedzi ekranu

    if (mouse_x > 1014 && srodek.rx() < szerokosc - ekran_szer / 2)
      srodek.wpisz(1, srodek.rx() + 1);
    if (mouse_x < 10 && srodek.rx() > ekran_szer / 2)
      srodek.wpisz(1, srodek.rx() - 1);
    if (mouse_y > 767 && srodek.ry() < szerokosc - ekran_wys / 2)
      srodek.wpisz(2, srodek.ry() + 2);
    
      // tu wyjatkowo inaczej aby nie przesuwalo mapy gdy myszka jest na interfejsie
    if (mouse_y < 10 && srodek.ry() > ekran_wys / 2)
      srodek.wpisz(2, srodek.ry() - 2);
      
    // przesuniecie dla chmur
    przes_x += (pom_x-srodek.rx())*40;
    przes_y += (pom_y-srodek.ry())*40;
    engine->wymus_rysowanie();
  }

  return srodek;
}

//******************************************************************************

/// funkcja sluzy do okreslenia, ktore pole na mapie jest aktualnie pod kursorem myszy 
/// oraz zwraca wspolrzedne tego pola (rysuje wskazane pole gdy zaznacz_pole=true)
punkt mapa::wskaz_pole(bool zaznacz_pole)
{
  // Mapa Myszy to bitmapa zawierajaca pola odpowiednich kolorów, które s³u¿¹
  // okreœleniu, które pole jest aktualnie pod kursorem myszy.
  int SzerokoscMapkiMyszy = 40;
  int WysokoscMapkiMyszy = 60;

  int PoleOffsetX, PoleOffsetY;

  // Wyznaczamy pod którym polem mapy myszy siê znajdujemy...
  float PoleX = (int)((mouse_x + 11) / SzerokoscMapkiMyszy);
  float PoleY = (int)((mouse_y - 2) / WysokoscMapkiMyszy) *2;

  // ...i okreœlamy dok³adnie pod którym pikselem tej mapy pikseli...
  float MapaMyszyX = (mouse_x + 11) % SzerokoscMapkiMyszy;
  float MapaMyszyY = (mouse_y - 2) % WysokoscMapkiMyszy;

  // ... sprawdzamy, jaki ten piksel ma kolor i odpowiednio przesuwamy offset pola
  switch (getpixel(engine->mapa_myszki, MapaMyszyX, MapaMyszyY))
  {
    case 16711680:
      PoleOffsetX =  - 1, PoleOffsetY =  - 1;
      break;
    case 16776960:
      PoleOffsetX = 0, PoleOffsetY =  - 1;
      break;
    case 16777215:
      PoleOffsetX = 0, PoleOffsetY = 0;
      break;
    case 65280:
      PoleOffsetX =  - 1, PoleOffsetY = 1;
      break;
    case 255:
      PoleOffsetX = 0, PoleOffsetY = 1;
      break;
  }

  // Faktycznie wskazany heks to wyznaczone pole oraz offset

  int WskazanyHexX = PoleX + PoleOffsetX;
  int WskazanyHexY = PoleY + PoleOffsetY;

  if (start_x + WskazanyHexX < szerokosc && start_y + WskazanyHexY < wysokosc)
  {
    // Wskazane pole podswietlamy odpowiednim "kursorem"
    if (WskazanyHexX >= 0 && WskazanyHexY >= 0 && WskazanyHexX < ekran_szer &&
      WskazanyHexY < ekran_wys && zaznacz_pole)
      engine->rysuj_pole(AKTYWNE_POLE, WskazanyHexX, WskazanyHexY);

    // Zwracamy wspolrzedne wzgledne zaznaczonego pola
    if (WskazanyHexX < 0)
      WskazanyHexX = 0;
    if (WskazanyHexY < 0)
      WskazanyHexY = 0;
    punkt wskazany(WskazanyHexX, WskazanyHexY);
    return wskazany;
  }
  else
  {
    punkt wskazany(ekran_szer / 2, ekran_wys / 2);
    return wskazany;
  }
}

//******************************************************************************

/// funkcja zwraca bezwzgledna pozycje pola pod myszka
punkt mapa::pole_pod_myszka()
{
  /// pole w lewym gornym rogu kadru
  punkt pom(start_x, start_y);
  /// wzgledna pozycja kliknietego pola
  klikniete = mapa::wskaz_pole(false);
  /// w sumie wspolrzedne aktualnie kliknietego pola
  klikniete = klikniete + pom;
  return klikniete;
}

//******************************************************************************

/// zwaca typ pola we wspo³rzednych x,y
char mapa::jakie_pole(int x, int y)
{
  return pola[y *szerokosc + x];
}

#include "jednostki.h"
