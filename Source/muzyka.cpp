/// Szczegolowe infomacje na temat funkcji z prefixem almp3_ znajduja sie
/// w dokumentacji biblioteczki AllegroMP3

//******************************************************************************

/// konstruktor obiektu klasy muzyka
/// w argumencie przyjmuje nazwe pliku mp3, ktory zostaje otwarty
muzyka::muzyka(char *filename)
{
  /// otwiera plik o padanej w argumencie nazwie
  otworz(filename);
  /// do pola tytul zostaje wpisana nazwa pliku
  tytul = filename;
  /// glosnosc zostaje ustawiona na maximum
  volume = 255;
  /// ustawienie jednakowej sily dzwieku na obuglosnikach
  pan = 128;
}

//******************************************************************************

/// destruktor obiektuklasy muzyka
muzyka::~muzyka()
{
  /// zamyka plik mp3 oraz niszczy strumien danych
  zamknij();
}

//******************************************************************************

/// funkcja otwiera plik mp3 o nazwie podanej w argunemcie
short dzwiek::otworz(char *filename)
{
  /// zmienna znakowa o rozmiarze 10000000000000 w systemie dwojkowym 
  /// (ilosc danych ktore pobieramy jednorazowo z dyku]
  char data[1 << 15];
  /// zmienna pomocnicza przy otwarciu pliku
  int len;

  /// jesli chcemy otworzyc plik ktorego niema
  if (!(file = pack_fopen(filename, F_READ)))
  /// idziemy do bledu
    goto error;

  /// jesli wielkosc pliku jest mniejsza niz 1
  if ((len = pack_fread(data, 1 << 15, file)) <= 0)
  /// idziemy do bledu
    goto error;

  /// jesli wielkosc pliku jest mniejsza niz ilosc danych pobieranych z dysku
  if (len < 1 << 15)
  {
    /// jesli nie mozemy utworzyc strumienia 
    if (!(plik_mp3 = almp3_create_mp3stream(data, len, TRUE)))
    /// idziemy do bledu
      goto error;
  }
  /// jesli rozmiar otwieranego pliku jest wiekszy niz ilosc danych pobieranych z dysku
  else
  {
    /// jesli nie mozamy utworzyc strumienia danych z dysku
    if (!(plik_mp3 = almp3_create_mp3stream(data, 1 << 15, FALSE)))
    /// idzemy do bledu
      goto error;
  }
  return 0;
  /// jesli wystapil blad
  error: 
  /// zamykamy plik z danymi
  pack_fclose(file);
  /// zwraca -1
  return  - 1;
}

//******************************************************************************

/// funkcja zamykajaca plik mp3 oraz niszczaca strumien danych
short dzwiek::zamknij()
{
  /// zamykaplik mp3
  pack_fclose(file);
  /// niszczy strumien danych
  almp3_destroy_mp3stream(plik_mp3);
  /// zwraca wartosc 0
  return 0;
}

//****************************************************************************** 

/// funkcja laduje do burofa o rozmairze 10000000000000 w systemie dwojkowym
/// glosnosc zostaje ustawion na vartosc pola volumne, 
/// natomiast sila glosu na wartosc pan
short dzwiek::przygotuj()
{
  return almp3_play_mp3stream(plik_mp3, 1 << 16, volume, pan);
}

//******************************************************************************

/// zwraca wartosc z pola utwor aktualnego elementu typu dzwiek
char *dzwiek::podaj_tytul()
{
  return tytul;
}

//******************************************************************************

/// odtwarza plik mp3 na ktory wskazuje pole plik_mp3 elementu, 
/// od ktorego wywolano funkcje
short dzwiek::odtwarzaj()
{

  /// wskaznik tylko znakowego
  char *data;
  /// zmienna odpowiedzialna za ilosc danych ladowanych do bufora
  long len;

  /// tworzymy w pamieci bufor, ktory bedziemy zapelnili fragmentami pliku 
  data = (char*)almp3_get_mp3stream_buffer(plik_mp3);

  /// jesli bufor nie jest pusty
  if (data)
  {
    /// pobieramy z dysku fragment pliku
    len = pack_fread(data, 1 << 15, file);
    /// jesli go wielkosc jest mniejsza niz 1<<15
    if (len < 1 << 15)
    /// wiadomo, ze nastepny bedzie koncowy fragment danych, 
    /// wiec zostaje zwolniona tylko wymagana ilosc pamieci
      almp3_free_mp3stream_buffer(plik_mp3, len);
    /// gdy wielkosc pobranego fragmentu jest wieksza niz 1<<15
    else
    /// zwolniozy zostaje caly bufor, poniewaz nie jest to ostatnia partia danych
      almp3_free_mp3stream_buffer(plik_mp3,  - 1);
  }
  /// jesli wlasnie zakonczylismy odtwarzanie pliku mp3
  if (almp3_poll_mp3stream(plik_mp3) == ALMP3_POLL_PLAYJUSTFINISHED)
  {
    /// zatrzymujemy odtwarzanie pliku
    zatrzymaj();
    /// wskazujaca zamienna pomocnicza typu znakowego
    char *pom;
    // za zmienna pomocnicza podstawiamy wskaznik do tytulu pliku, ktory skonczylismy odtwarzac
    pom = podaj_tytul();
    /// zamykamy plik mp3 i niszczymy strumien danych
    zamknij();
    /// otwieramy pomownie plik mp3
    otworz(pom);
    /// tworzymy nowy strumien danych
    przygotuj();
  }
  /// zwraca wartosc 1 jesli wszytko wykonalo siepoprawnie
  return 1;
}

//******************************************************************************

/// zatrzymujemy odtwarzanie dzwieku
short dzwiek::zatrzymaj()
{
  /// zatrzymuje odtwarzanie pliku mp3
  almp3_stop_mp3stream(plik_mp3);
  /// zwraca 0 jesli operacja zostalawykonana poprawnie
  return 0;
}

//******************************************************************************

/// bezargumentowy konstruktor obiektu typu playlista
playlista::playlista()
{
  /// wskaznik na kolejny elementu przyjmuje wartosc NULL
  kolejny = NULL;
  /// wskoznik na tytul utworu przyjmuje wartosc NULL
  utwor = NULL;
}

//******************************************************************************

/// konstruktor obiektu typu playlista
/// w argumencie podajemy wskoaznik to tytulu pliku mp3
playlista::playlista(char *plik_mp3)
{
  /// wskaznik na kolejny elementu przyjmuje wartosc NULL
  kolejny = NULL;
  /// wskaznik na tytul pliku mp3 przyjmuje wartosc podana w argumencie
  utwor = new muzyka(plik_mp3);
}

//******************************************************************************

/// funkcja zwracajaca wskaznik na koleny element listy 
/// lub jesli nie jest to mozliwe zwraca wskaznik do aktualnego elementu
playlista playlista::przeskocz()
{
  if (kolejny != NULL)
    return  *kolejny;
  else
    return  *this;
}

//******************************************************************************

/// funkcja dodaje nowy element na koniec listy, umieszczajac w polu utwor 
/// wskaznik do nowego pliku muzycznego o nazwie podanej w argumencie 
playlista playlista::dodaj(char *plik_mp3)
{
  /// zmienna pomocnicza z adresem elementu, w ktorym obecnie jestesmy
  playlista *pom = this;

  /// petla ustawia wskaznik na ostatnim elemencie listy
  /// poki wskaznik dokolenjego elementu listy nie jest pusty
  while (pom->kolejny != NULL)
  {
    /// adres kolenjego elementu staje sie obecnym adresem 
    pom = pom->kolejny;
  }

  /// gdy juz jestemy w ostatnim elemencie
  pom->kolejny = new playlista(plik_mp3);
}

//******************************************************************************

/// funkcja odtwarza utwor, do ktorego wskaznik znajduje siew polu utwor
void playlista::odtwarzaj()
{
  this->utwor->odtwarzaj();
}

//******************************************************************************

/// funkcja przygotowuje do odtwarzanie plik mp3, 
/// do ktorego wskaznik znajduje sie w polu utwor
void playlista::przygotuj()
{
  this->utwor->przygotuj();
}

//******************************************************************************

/// funkcja zatrzymuje odtwarzanie utworu, 
/// do ktorego wskaznikznajdujesie w polu utwor
void playlista::zatrzymaj()
{
  this->utwor->zatrzymaj();
}

//******************************************************************************

/// funckja zwraca wskaznik do tytulu utworu 
/// przechowywanego w aktualnym elemencie listy
muzyka *playlista::pobierz_utwor()
{
  return utwor;
}

//******************************************************************************

/// konstruktor obiektu klasy odglosy
/// w argumencie podajemy nazwe pliku,
/// do ktorego wskaznikzostanie umieszczony w polu plik_wav
odglosy::odglosy(char *filename)
{
  plik_wav = load_wav(filename);
}

//******************************************************************************

/// funkcja odtwarza plik_wav
/// do ktorego wskaznik znajduje sie w polu plik_wav obiektu klasy odglosy
short odglosy::odtwarzaj()
{
  play_sample(plik_wav, 125, 125, 1000, 0); // 
}

//******************************************************************************

/// destruktor obiektu klasy odglosy zwalnianacy 
/// pamiec zajeta przez zaladowany plik_wav
odglosy::~odglosy()
{
  free(plik_wav);
}
