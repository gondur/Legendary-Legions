int utworzPolaczenie(char *ip, int port)
{
  char *adres_serwera;
  int gniazdoKlient;
  struct sockaddr_in adres;

  adres_serwera = ip;
  gniazdoKlient = socket(PF_INET, SOCK_STREAM, 0);

  adres.sin_family = AF_INET;
  adres.sin_addr.s_addr = inet_addr(adres_serwera);
  adres.sin_port = htons(port);

  if (connect(gniazdoKlient, (const struct sockaddr*) &adres, sizeof(adres)) ==
    - 1)
  {
    perror("connect");
    return  - 1;
  } return gniazdoKlient;
}


int wyslijTekst(int gniazdo, char *tekst)
{
  int bajtowWyslanych = 0;
  int doWyslania = strlen(tekst);
  char zapytanie[MAX_SIZE + 2];

  sprintf(zapytanie, "%2d%s", doWyslania, tekst);

  tekst = zapytanie;

  while ((bajtowWyslanych = send(gniazdo, tekst, doWyslania + 2, 0)) <
    doWyslania + 2)
  {
    tekst += bajtowWyslanych;
    doWyslania -= bajtowWyslanych;
  }
}

int wyslijPlik(int gniazdo, char *nazwaPliku)
{
  int plik;
  int n;
  char bufor[10];
  plik = open(nazwaPliku, O_RDONLY);
  while ((n = read(plik, bufor, strlen(bufor))) > 0)
  {
    bufor[n] = '\0';
    wyslijTekst(gniazdo, bufor);
  }
  close(plik);

}

int utworzGniazdoSerwera(int port)
{
  int gniazdoSerwer;
  struct sockaddr_in adres;

  gniazdoSerwer = socket(PF_INET, SOCK_STREAM, 0);


  adres.sin_family = AF_INET;
  adres.sin_addr.s_addr = INADDR_ANY;
  adres.sin_port = htons(port);

  if (bind(gniazdoSerwer, (struct sockaddr*) &adres, sizeof(adres)) < 0)
  {
    perror("bind");
    exit(1);
  } 

  if (listen(gniazdoSerwer, 5) < 0)
  {
    perror("listen");
    exit(1);
  }
  return gniazdoSerwer;
}

void Blad(char *tekst)
{
  perror(tekst);
  exit(1);
}

void zatzymajWinsocket()
{
  WSACleanup();
}

void inicjujWinsocket()
{
  WSADATA wsaData;

  if (WSAStartup(MAKEWORD(1, 1), &wsaData) != 0)
  {
    fprintf(stderr, "WSAStartup failed.\n");
    exit(1);
  }
}
