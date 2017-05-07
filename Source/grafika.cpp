// pozycja zamku ZLA, wykorzystywana do sciemniania chmur
int poz_zamku_x=0;
int poz_zamku_y=0;
BITMAP *b_chmury[3];
BITMAP *b_chmury_cien[3];

class Chmura 
{
    public:
        int jasnosc;
        int sciemnienie;
        int predkosc;
        int odleglosc;
        int odl_x, odl_y;
        int x, y;
        int px, py;
        int takty;
        int typ;
        bool bl;

    public:
    Chmura()
    {
        takty=0;
        x = rand()%2400;
        y = rand()%2200;
        jasnosc = 150+rand()%105;
        sciemnienie = 0;
        predkosc= 1+rand()%2;
        bl = true;
        typ = rand()%3;
    }
    void wyswietl(BITMAP * be)
    {
            px = przes_x+x;
            py = przes_y+y;
            odl_x = (py-poz_zamku_y+b_chmury[typ]->h/2);
            odl_y = (px-poz_zamku_x+b_chmury[typ]->w/2);
            odleglosc = sqrt(odl_x*odl_x+odl_y*odl_y);

            sciemnienie = 255-odleglosc/3;
            int blysk=0;
            ++takty;
            if(takty>15) 
            {
                takty=0;
                bl=true;
            }
            if(sciemnienie>150 && bl) 
            { 
                blysk = rand()%(100+sciemnienie/4); 
                
                bl=false;
            }


            if(px>-b_chmury[typ]->w && px<1024+b_chmury[typ]->w && py>-b_chmury[typ]->h && py<583+b_chmury[typ]->h) 
            {

                AlphaBlend32( b_chmury_cien[typ], be, px+30, py+30, jasnosc/2);
                AlphaBlend32( b_chmury[typ], be, px, py , (blysk>80 ? 255 : jasnosc));
                if(sciemnienie>0) AlphaBlend32( b_chmury_cien[typ], be, px, py , (blysk>80 ? 0 : sciemnienie));
            }       
             
    }
    void odswiez()
    {
            x+=predkosc;
            y+=predkosc;
            if(x>2400 || y>2200)
            {
                int los = rand()%2;
                if(los==0)
                {
                    x=-b_chmury[typ]->w;
                    y=rand()%2200;
                }
                else
                {
                    y=-b_chmury[typ]->h;
                    x=rand()%2400;
                }
            }
    }
};

Chmura *chmura[CHMUR];

/// konstruktor domyœlny punktu
punkt::punkt()
{
  x = 0;
  y = 0;
}

//******************************************************************************

/// konstruktor z argumentami, pobiera x i y punktu
punkt::punkt(float _x, float _y)
{
  x = _x;
  y = _y;
}

//******************************************************************************

/// konstruktor kopiuj¹cy inny punkt
punkt::punkt(const punkt &_p)
{
  x = _p.x;
  y = _p.y;
}

//******************************************************************************

/// przeci¹¿ony operator przypisywania punktu
punkt punkt::operator = (punkt pom)
{
  x = pom.x;
  y = pom.y;
  return  *this;
}

//******************************************************************************

/// przeci¹¿ony operator dodawania innego puktu
punkt punkt::operator + (punkt arg)
{
  punkt pom(0, 0);
  pom.x = x + arg.x;
  pom.y = y + arg.y;
  return pom;
}

//******************************************************************************

/// funkcja zwraca pole x punktu
float punkt::rx()
{
  return x;
}

//******************************************************************************

/// funkcja zwraca pole y punktu
float punkt::ry()
{
  return y;
}

//******************************************************************************

/// funkcja wstawia pod x (jeœli p=1), lub pod y (jeœli p=2) wartosc wstaw
void punkt::wpisz(float p, float wstaw)
{

  if (p == 1)
    x = wstaw;
  else if (p == 2)
    y = wstaw;
}


//******************************************************************************

/// Konstruktor klasy grafika. Inicjuje dzwiek, ekran, wczytuje niezbêdne bitmapy
/// oraz czcionke
grafika::grafika(char *s_screen)
{
    
  // inicjalizacja biblioteki allegro oraz timera, klawiatury i myszki
  allegro_init();
  install_timer();
  install_keyboard();
  install_mouse();

  set_config_file("config.cfg");
  if( strcmp(get_config_string("General", "chmury", "nie"), "tak") == 0 ) czy_chmury = true;

  /// plik ustawien
  //set_config_file("ll_pl.cfg");

  /// rejestrowanie png
  register_png_file_type();

  /// inicjalizacja dzwieku
  install_sound(DIGI_AUTODETECT, MIDI_NONE, 0);

  /// ustalanie g³êbii kolorów
  int glebia_kolorow = desktop_color_depth();
  if (glebia_kolorow == 0)
    glebia_kolorow = 32;
  set_color_depth(glebia_kolorow);
  int rozdzielczosc;

  /// wybor trybu pelnoekranowego lub w oknie w zale¿noœci od podanego argumentu
  if (strcmp(s_screen, "fullscreen") == 0)
    rozdzielczosc = set_gfx_mode(GFX_AUTODETECT_FULLSCREEN, 1024, 768, 0, 0);
  else if (strcmp(s_screen, "windowed") == 0)
    rozdzielczosc = set_gfx_mode(GFX_AUTODETECT_WINDOWED, 1024, 768, 0, 0);

  /// jesli nie udalo sie zainicjwowac trybu graficznego to wyswietlany jest b³ad i program siê wy³¹cza
  if (rozdzielczosc != 0)
  {
    allegro_message(allegro_error);
    exit( - 1);
  }

  /// tworzenie bitmapy bufor_ekranu oraz jej czyszczenie
  bufor_ekranu = create_bitmap(1024, 768);
  clear_bitmap(bufor_ekranu);

  /// wczytywanie bitmap z plików
  bitmapy = load_png("Pliki_danych/Bitmapy/bitmapy.png", default_palette);
  mieso = load_png("Pliki_danych/Bitmapy/szynka.png", default_palette);
  monety = load_png("Pliki_danych/Bitmapy/monety.png", default_palette);
  kursor = load_png("Pliki_danych/Bitmapy/kursor.png", default_palette);
  b_interfejs = load_png("Pliki_danych/Bitmapy/interfejs.png", NULL);
  b_wskaznik = load_png("Pliki_danych/Bitmapy/wskaznik.png", default_palette);
  b_nieaktywna = load_png("Pliki_danych/Bitmapy/nieaktywna.png",
    default_palette);
  b_tlo_menu = load_png("Pliki_danych/Bitmapy/tlo_menu.png", default_palette);
  b_button = load_png("Pliki_danych/Bitmapy/button.png", default_palette);
  b_pr = load_png("Pliki_danych/Bitmapy/pr.png", default_palette);
  b_pr2 = load_png("Pliki_danych/Bitmapy/pr2.png", default_palette);
  b_pr3 = load_png("Pliki_danych/Bitmapy/pr3.png", default_palette);
  b_ingamemenu = load_png("Pliki_danych/Bitmapy/ingamemenu.png",
    default_palette);
  b_chmury[0] = load_png("Pliki_danych/Bitmapy/chmury.png", NULL);
  b_chmury_cien[0] = load_png("Pliki_danych/Bitmapy/chmury_cien.png", NULL);
  b_chmury[1] = load_png("Pliki_danych/Bitmapy/chmury2.png", NULL);
  b_chmury_cien[1] = load_png("Pliki_danych/Bitmapy/chmury_cien2.png", NULL);
  b_chmury[2] = load_png("Pliki_danych/Bitmapy/chmury3.png", NULL);
  b_chmury_cien[2] = load_png("Pliki_danych/Bitmapy/chmury_cien3.png", NULL);  
  b_noc = create_sub_bitmap(bufor_ekranu, 0, 0, 517, 552);

    for(int i=0;i<CHMUR; ++i)
        chmura[i] = new Chmura();
  
  clear_bitmap(b_noc);
  ///wczytywanie znaków
  f_font = load_font("Pliki_danych/Fonty/ex01.pcx", default_palette, NULL); 
    //###########################################################3

  set_mouse_sprite(kursor);

  //select_mouse_cursor();

  /// wczytywanie pomocniczej bitmapy mapa_myszki
  mapa_myszki = load_png("Pliki_danych/Bitmapy/mapa_myszki.png",
    default_palette);

  /// ustawianie klatki na 0 oraz pocz¹tku klatki na aktualny czas
  klatka = 0;
  clk = CLOCKS_PER_SEC / 100;
  poczatek = clock();
  pokaz_klatke = true;
  wymus = false;

  set_display_switch_mode(SWITCH_BACKGROUND);
}

//******************************************************************************

/// destruktor klasy grafika usuwa utworzone bitmapy
grafika::~grafika()
{
  /// czyszczenie bufora klawiatury
  clear_keybuf();

  /// czyszczenie z pamieci bitmap
  destroy_bitmap(bufor_ekranu);
  destroy_bitmap(bitmapy);
  destroy_bitmap(mapa_myszki);
  destroy_bitmap(b_pr);
  destroy_bitmap(b_pr2);
  destroy_bitmap(b_pr3);
  destroy_bitmap(b_button);
  destroy_bitmap(b_tlo_menu);
  destroy_bitmap(b_noc);
  destroy_bitmap(kursor);
  destroy_bitmap(mieso);
  destroy_bitmap(monety);

  destroy_font(f_font);

  /// zamykanie wszystkich elementow biblioteki allegro
  allegro_exit();
}

//******************************************************************************

/// Funkcja przekopiowuje zawartoœæ bufora_ekranu na ekran oraz pokazuje kursor myszki.
void grafika::pokaz(bool pokazac = false)
{
  show_mouse(bufor_ekranu);

  if (pokaz_klatke || pokazac || wymus)
  {

    wymus = false;
    //fblend_fade_to_color(b_noc, bitmapy, 0,0, makecol(0,0,0), 150);
    fblend_trans(bufor_ekranu, screen, 0, 0, 255);
    //blit(bufor_ekranu, screen, 0, 0, 0, 0, 1024, 768);
    //set_config_file("config.cfg");
    //Sleep(30);
    //set_config_file((char*)get_config_string("General", "jezyk", 0));
    Sleep(30);
    pokaz_klatke = false;
  }
  show_mouse(NULL);
}

//******************************************************************************

/// Funkcja podobna do funkcji rysuj_pole(nazwa_pola, int, int) z t¹ róznic¹, ¿e 
/// nie obs³uguje animacji, oraz s³u¿y do wyœwietlania bitmap niebêd¹cych polami 
/// na mapiê, b¹dŸ jednostkami. Wyœwietla zatem interfejs, menu, tarcze gracza itp. 
/// Kolejn¹ ró¿nic¹ jest sposób umiejscowienia. O o ile we wspomnianej funkcji 
/// podawa³o siê wspó³rzêdne na mapie, o tyle tutaj podajemy dok³adne po³o¿enie 
/// bitmapy w pikselach na ekranie (argumenty x i y).
/// Pozosta³e argumenty s³u¿¹ do wycinania obszaru bitmapy prostok¹tem o pocz¹tku 
/// (od_x, od_y) oraz podanej szerokoœci i wysokoœci.

void grafika::rysuj_bitmape(typ_bitmapy typ, int x, int y, int od_x, int od_y,
  int szerokosc, int wysokosc)
{

  switch (typ)
  {
    case B_INTERFEJS:
      if (nowa_klatka)
        masked_blit(b_interfejs, bufor_ekranu, od_x, od_y, x, y, szerokosc,
          wysokosc);
      break;
    case B_GRA:
      break;
    case B_BUTTON:
      masked_blit(b_button, bufor_ekranu, od_x, od_y, x, y, szerokosc, wysokosc)
        ;
      break;
    case B_TLO_MENU:
      blit(b_tlo_menu, bufor_ekranu, od_x, od_y, x, y, szerokosc, wysokosc);
      break;
    case B_TARCZA_GRACZ_1:
      if (nowa_klatka)
        masked_blit(bitmapy, bufor_ekranu, 1, 93, x, y, 12, 15);
      break;
    case B_TARCZA_GRACZ_2:
      if (nowa_klatka)
        masked_blit(bitmapy, bufor_ekranu, 14, 93, x, y, 12, 15);
      break;
    case B_DUZA_TARCZA_GRACZ_1:
      masked_blit(bitmapy, bufor_ekranu, 1, 110, x, y, 51, 73);
      break;
    case B_DUZA_TARCZA_GRACZ_2:
      masked_blit(bitmapy, bufor_ekranu, 53, 110, x, y, 61, 73);
      break;
    case B_PASEK_SIL_BRAK:
      if (nowa_klatka)
        masked_blit(bitmapy, bufor_ekranu, 1, 87, x, y, szerokosc, 5);
      break;
    case B_PASEK_SIL_PELNY:
      if (nowa_klatka)
        masked_blit(bitmapy, bufor_ekranu, 1, 80, x, y, szerokosc, 5);
      break;
    case B_POLE_PRZ:
      set_trans_blender(255, 255, 255, 100);
      draw_trans_sprite(bufor_ekranu, b_pr, x, y);
      break;
    case B_POLE_PRZ_2:
      set_trans_blender(255, 255, 255, 100);
      draw_trans_sprite(bufor_ekranu, b_pr2, x, y);
      break;
    case B_POLE_PRZ_3:
      if (nowa_klatka)
        set_trans_blender(255, 255, 255, 240);
      if (nowa_klatka)
        draw_trans_sprite(bufor_ekranu, b_pr3, x, y);
      break;
    case INGAMEMENU:
      if (nowa_klatka)
        set_trans_blender(255, 255, 255, 240);
      if (nowa_klatka)
        draw_trans_sprite(bufor_ekranu, b_ingamemenu, x, y);
      break;
    case MIESO:
      if (nowa_klatka)
        set_alpha_blender();
      if (nowa_klatka)
        draw_trans_sprite(bufor_ekranu, mieso, x, y);
      break;
    case MONETY:
      if (nowa_klatka)
        set_alpha_blender();
      if (nowa_klatka)
        draw_trans_sprite(bufor_ekranu, monety, x, y);
      break;
  }

}

//******************************************************************************

/// Funkcja czyœci bufor ekranu do koloru podanego w argumencie.
void grafika::czysc_ekran(int kolor)
{
  clear_to_color(bufor_ekranu, kolor);
}

//******************************************************************************

/// Funkcja wyswietla pole na mapie o danej nazwie we wskazanym miejscu. 
/// Obs³uguje animacje pól (max. 8 klatek), które siê zmieniaj¹ co 200 milisekund.
void grafika::rysuj_pole(nazwa_pola wyglad, int mapaX, int mapaY, short _klatka
  = 0)
{


  // odstêp w pionie miêdzy polami heksagonalnymi
  float odstep_pionowy_pola = (wysokosc_pola) *0.75;

  // ustalanie pozycji pola na ekranie (-11 i +4 by wyrownac mape do interfejsu, tak samo w funkcji mapa::wskaz_pole() i jednostka::rysuj())


  int x = (mapaX *40) + ((mapaY % 2)*(szerokosc_pola / 2)) - 11;
  int y = (mapaY *odstep_pionowy_pola) + 2;
 

  if (mapaX > 100 && mapaY > 100)
  {
    x = mapaX;
    y = mapaY;
  }


  /// jest 8 klatek animacji dla wszystkich pol
  if (klatka > 7)
    klatka = 0;

  if (nowa_klatka)
  {
    // rysowanie pola w zale¿noœci od jego nazwy
    switch (wyglad)
    {
      case LAS:
        if (_klatka == 0)
          masked_blit(bitmapy, bufor_ekranu, klatka *40, 184, x, y,
            szerokosc_pola, wysokosc_pola);
        else
          masked_blit(bitmapy, bufor_ekranu, _klatka *40, 504, x, y,
            szerokosc_pola, wysokosc_pola);
        break;
      case WODA:
        masked_blit(bitmapy, bufor_ekranu, klatka *40, 224, x, y,
          szerokosc_pola, wysokosc_pola);
        break;
      case LAWA:
        masked_blit(bitmapy, bufor_ekranu, klatka *40, 264, x, y,
          szerokosc_pola, wysokosc_pola);
        break;
      case LAWA_2:
        masked_blit(bitmapy, bufor_ekranu, klatka *40, 424, x, y,
          szerokosc_pola, wysokosc_pola);
        break;
      case SPALONA_ZIEMIA:
        masked_blit(bitmapy, bufor_ekranu, _klatka *40, 464, x, y,
          szerokosc_pola, wysokosc_pola);
        break;
      case TRAWA:
        masked_blit(bitmapy, bufor_ekranu, _klatka *40, 304, x, y,
          szerokosc_pola, wysokosc_pola);
        break;
      case PUSTYNIA:
        masked_blit(bitmapy, bufor_ekranu, _klatka *40, 344, x, y,
          szerokosc_pola, wysokosc_pola);
        break;
      case GORA:
        masked_blit(bitmapy, bufor_ekranu, _klatka *40, 384, x, y,
          szerokosc_pola, wysokosc_pola);
        break;
      case AKTYWNE_POLE:
        set_trans_blender(250, 0, 0, 80);
        draw_trans_sprite(bufor_ekranu, b_wskaznik, x, y);
        break;
      case NIEAKTYWNA_JEDNOSTKA:
        set_trans_blender(200, 200, 200, 100);
        draw_trans_sprite(bufor_ekranu, b_nieaktywna, x, y);
        break;
      case OGNISTY:
        masked_blit(bitmapy, bufor_ekranu, 120, 0, x, y, szerokosc_pola,
          wysokosc_pola);
        break;
      case ROBOTNIK_1:
        masked_blit(bitmapy, bufor_ekranu, 126, 115, x, y, 39, 37);
        break;
      case ROBOTNIK_2:
        masked_blit(bitmapy, bufor_ekranu, 166, 115, x, y, 38, 37);
        break;
      case ZOLNIERZ:
        masked_blit(bitmapy, bufor_ekranu, 160, 0, x, y, 37, 37);
        break;
      case RYCERZ:
        masked_blit(bitmapy, bufor_ekranu, 0, 0, x + 6, y, 24, 37);
        break;
      case HYDRA:
        masked_blit(bitmapy, bufor_ekranu, 28, 0, x + 10, y, 20, 37);
        break;
      case ARCHANIOL:
        masked_blit(bitmapy, bufor_ekranu, 53, 0, x + 6, y, 24, 37);
        break;
      case MAG:
        masked_blit(bitmapy, bufor_ekranu, 84, 0, x + 10, y, 28, 37);
        break;
      case SMOK:
        masked_blit(bitmapy, bufor_ekranu, 30, 40, x + 10, y, 28, 37);
        break;
      case TROL:
        masked_blit(bitmapy, bufor_ekranu, 198, 0, x, y, 35, 37);
        break;
      case CIEMNY_RYCERZ:
        masked_blit(bitmapy, bufor_ekranu, 0, 40, x + 6, y, 23, 37);
        break;
      case LORD:
        masked_blit(bitmapy, bufor_ekranu, 62, 40, x + 4, y, 34, 37);
        break;
      case WIEZA_1:
        masked_blit(bitmapy, bufor_ekranu, 435, 16, x + 6, y - 26, 30, 57);
        break;
      case WIEZA_2:
        masked_blit(bitmapy, bufor_ekranu, 473, 16, x + 6, y - 26, 30, 57);
        break;
      case MIASTO_1:
        masked_blit(bitmapy, bufor_ekranu, 248, 0, x - 23, y - 30, 87, 87);
        break;
      case MIASTO_2:
        masked_blit(bitmapy, bufor_ekranu, 338, 0, x - 23, y - 30, 87, 87);
        break;
      case ZAMEK_GRACZ_1:
        masked_blit(bitmapy, bufor_ekranu, 126, 42, x, y - 30, 39, 66);
        break;
      case ZAMEK_GRACZ_2:
        masked_blit(bitmapy, bufor_ekranu, 174, 42, x, y - 30, 39, 66);
        poz_zamku_x = x;
        poz_zamku_y = y-30;
        break;
    }


  }
  /// klatka sie zmienia co 200 milisekund
  if ((clock() / clk) - (poczatek / clk) > 9)
  {
    klatka++;
    poczatek = clock();
    pokaz_klatke = true;
  }

}

void grafika::wpisz(std::string &edittext, int dlugosc = 15, bool numery =
  false)
{
  std::string::iterator iter = edittext.end();
  int caret = 0;
  bool insert = true;

  while (keypressed())
  {
    int newkey = readkey();
    char ASCII = newkey &0xff;
    char scancode = newkey >> 8;

    // a character key was pressed; add it to the string
    if ((ASCII >= '0' && ASCII <= '9') || ASCII == '.' || (!numery && ASCII >=
      32 && ASCII <= 126))
    {
      // add the new char, inserting or replacing as need be
      if ((insert || iter == edittext.end()) && edittext.size() < dlugosc)
      {
        iter = edittext.insert(iter, ASCII);

        caret++;
        iter++;
      }
    }
    // some other, "special" key was pressed; handle it here
    else
    switch (scancode)
    {
      case KEY_DEL:
        if (iter != edittext.end())
          iter = edittext.erase(iter);
        break;

      case KEY_BACKSPACE:
        if (iter != edittext.begin())
        {
          caret--;
          iter--;
          iter = edittext.erase(iter);
        }
        break;

      case KEY_RIGHT:
        if (iter != edittext.end())
          caret++, iter++;
        break;

      case KEY_LEFT:
        if (iter != edittext.begin())
          caret--, iter--;
        break;

      case KEY_INSERT:
        insert = !insert;
        break;

      default:

        break;
    }
  }
}

//******************************************************************************

/// Funkcja s³u¿y do wypisywania tekstu tekst w miejscu (x, y) o podanym kolorze. 
/// Jeœli chcemy dodatkowo za tekstem umieœciæ liczbê (b¹dŸ zmienn¹) to podajemy 
/// j¹ jako argument. Gdy argument jest równy -1, nie wyœwietlana jest ¿adna liczba
/// za tekstem. 
/// Funkcja ma tak¿e wbudowan¹ obs³ugê przechodzenia do nowej linijki, u¿ywa siê 
/// wtedy w tekœcie znaku '\n'.
/// Ostatni argument s³u¿y do zmiany sposobu umieszczania tekstu na wycentrowany, 
/// który nie obs³uguje znaku '\n' ooraz wyœwietlania argumentów.

void grafika::pisz(char *tekst, int x, int y, int arg = 0, int kolor = makecol
  (255, 255, 255), bool wycentrowane = true, int szerokosc =  - 1)
{
  y = y - 4;
  int px = x, py = y;
  int poz = 0;
  if (wycentrowane)
    textprintf_centre_ex(bufor_ekranu, f_font, x, y, kolor,  - 1, tekst, arg);
  else
  {
    while (tekst[poz])
    {
      if (tekst[poz] == '\n' || (px - x > szerokosc && szerokosc >  - 1))
      {
        ++poz;
        px = x;
        py += text_height(f_font);
        continue;
      }
      char pom[2] = " ";
      pom[0] = tekst[poz];
      textout_ex(bufor_ekranu, f_font, pom, px, py, kolor,  - 1);
      px += text_length(f_font, pom);
      poz++;
    }
    if (arg !=  - 1)
      textprintf_ex(bufor_ekranu, f_font, px, py, kolor,  - 1, "%d", arg);
  }
}

/// Funkcja wyœwietla prostok¹t , którego lewy górny róg znajduje siê w punkcie (x1, y1) 
/// natomiast prawy dolny w punkcjie (x2, y2). Prostok¹t ma kolor podany w argumencie i 
/// mo¿e byæ nim wype³niony (wypelniony=true), b¹dŸ te¿ pusty w œrodku (wypelniony=false).
void grafika::prostokat(int x1, int y1, int x2, int y2, int kolor, bool
  wypelniony = true)
{

  if (wypelniony)
    rectfill(bufor_ekranu, x1, y1, x2, y2, kolor);
  else
    rect(bufor_ekranu, x1, y1, x2, y2, kolor);
}

void grafika::zmiana_klatki(bool na_co)
{
  nowa_klatka = na_co;
}

bool grafika::czy_pokazac()
{
  if ((clock() / clk) - (poczatek / clk) > 8)
    return true;
  return false;
}

void grafika::wymus_rysowanie()
{
  wymus = true;
}

void grafika::rysuj_noc(short godzina)
{
  int alpha;
  if (godzina >= 12 && godzina <= 23)
    alpha = (godzina - 12) *19;
  if (godzina >= 0 && godzina <= 11)
    alpha = 228-godzina * 19;

  if (nowa_klatka) 
  {
        if(czy_chmury)
        {
            for(int i=0; i<CHMUR; ++i)
            {
                chmura[i]->odswiez();
                chmura[i]->wyswietl(bufor_ekranu);
            }
        }
        fblend_rect_trans(bufor_ekranu, 0, 0, 1024, 583, makecol(0, 0, 0), alpha);
  }
}

#include "obsluga.h"
