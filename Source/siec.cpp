Serwer::Serwer(int port)
{
  inicjujWinsocket();
  gniazdoSerwer = utworzGniazdoSerwera(port);

  unsigned long NonBlock = 1;
  ioctlsocket(gniazdoSerwer, FIONBIO, &NonBlock);
}

Serwer::~Serwer()
{
  closesocket(gniazdoKlient);
  closesocket(gniazdoSerwer);
  zatzymajWinsocket();
}

bool Serwer::przyjmijKlienta()
{
  // czekanie na klienta
  gniazdoKlient = accept(gniazdoSerwer, NULL, NULL);
  unsigned long NonBlock = 1;
  ioctlsocket(gniazdoKlient, FIONBIO, &NonBlock);
  if (gniazdoKlient < 0)
    return false;
  else
    return true;
}

void Serwer::wyslijZapytanie(char *tresc)
{
  wyslijTekst(gniazdoKlient, tresc);
}

void Serwer::serwWyslijPlik(char *plik)
{
  wyslijPlik(gniazdoKlient, plik);
}

bool Serwer::odbierzZapytanie()
{
  int ile = 0;
  int ileOdebrac = 0;
  if (recv(gniazdoKlient, bufor, 2, 0) == SOCKET_ERROR)
  {
      if (WSAGetLastError() == WSAEWOULDBLOCK)
      return false;
  }
  char pom[3];
  pom[0] = bufor[0];
  pom[1] = bufor[1];
  pom[2] = 0;
  ileOdebrac = atoi(pom);
  recv(gniazdoKlient, bufor, ileOdebrac, 0);

  bufor[ileOdebrac] = '\0';
  return true;
}

char *Serwer::zwrocZapytanie()
{
  return bufor;
}

Klient::Klient(char *ip, int port)
{
  inicjujWinsocket();
  gniazdoKlient = utworzPolaczenie(ip, port);
  unsigned long NonBlock = 1;
  ioctlsocket(gniazdoKlient, FIONBIO, &NonBlock);
  bufor[0] = 0;
}

Klient::~Klient()
{
  zatzymajWinsocket();
}

int Klient::zwrocSocket()
{
  return gniazdoKlient;
}

void Klient::wyslijZapytanie(char *tresc)
{
  wyslijTekst(gniazdoKlient, tresc);
}

bool Klient::odbierzZapytanie()
{
  int ile = 0;
  int ileOdebrac = 0;
  if (recv(gniazdoKlient, bufor, 2, 0) == SOCKET_ERROR)
  {
    if (WSAGetLastError() == WSAEWOULDBLOCK)
      return false;
  }
  char pom[3];
  pom[0] = bufor[0];
  pom[1] = bufor[1];
  pom[2] = 0;
  ileOdebrac = atoi(pom);
  recv(gniazdoKlient, bufor, ileOdebrac, 0);

  bufor[ileOdebrac] = '\0';
  return true;
}

void Klient::zerujBufor()
{
  strcpy(bufor, " ");
}

char *Klient::zwrocZapytanie()
{
  return bufor;
}

int ParserZapytan::przetwarzajZapytanie(char *zapytanie)
{
  char *token;
  char czat_zapytanie[105];
  if (zapytanie == NULL)
    return  - 1;
  strcpy(czat_zapytanie, zapytanie);
  token = strtok(zapytanie, " ");
  if (token == NULL)
    return  - 1;
  if (strcmp(token, "MOVE") == 0)
  {
    sprintf(typZapytania, "MOVE");
    token = strtok(NULL, " ");
    id = atoi(token);
    token = strtok(NULL, " ");
    dx = atoi(token);
    token = strtok(NULL, " ");
    dy = atoi(token);
  }
  else if (strcmp(token, "UPDT") == 0)
  {
    sprintf(typZapytania, "UPDT");
    token = strtok(NULL, " ");
    id = atoi(token);
    token = strtok(NULL, " ");
    gracz = atoi(token);
    token = strtok(NULL, " ");
    punkty_zycia = atoi(token);
    token = strtok(NULL, " ");
    d_punkty_zycia = atoi(token);
    token = strtok(NULL, " ");
    punkty_ruchu = atoi(token);
    token = strtok(NULL, " ");
    atak = atoi(token);
    token = strtok(NULL, " ");
    obrona = atoi(token);
    token = strtok(NULL, " ");
    zwinnosc = atoi(token);
    token = strtok(NULL, " ");
    do_rozdysponowania = atoi(token);
    token = strtok(NULL, " ");
    poziom = atoi(token);
    token = strtok(NULL, " ");
    doswiadczenie = atoi(token);
    token = strtok(NULL, " ");
    exp = atoi(token);
    token = strtok(NULL, " ");
    pieniadze = atoi(token);
  }
  else if (strcmp(token, "KILL") == 0)
  {
    sprintf(typZapytania, "KILL");
    token = strtok(NULL, " ");
    px = atoi(token);
    token = strtok(NULL, " ");
    py = atoi(token);
  }
  else if (strcmp(token, "ADD") == 0)
  {
    sprintf(typZapytania, "ADD");
    token = strtok(NULL, " ");
    px = atoi(token);
    token = strtok(NULL, " ");
    py = atoi(token);
    token = strtok(NULL, " ");
    wyglad = atoi(token);
    token = strtok(NULL, " ");
    tura = atoi(token);
    token = strtok(NULL, " ");
    czy_heros = atoi(token);
  }
  else if (strcmp(token, "TURA") == 0)
  {
    sprintf(typZapytania, "TURA");
    token = strtok(NULL, " ");
    tura = atoi(token);
  }
  else if (strcmp(token, "CZAT") == 0)
  {
    sprintf(typZapytania, "CZAT");
    strcpy(tekst_czat, czat_zapytanie + 5);
  }
  else if (strcmp(token, "NEXT") == 0)
  {
    sprintf(typZapytania, "NEXT");
  }
  else if (strcmp(token, "GOLD") == 0)
  {
    sprintf(typZapytania, "GOLD");
    token = strtok(NULL, " ");
    tura = atoi(token);
    token = strtok(NULL, " ");
    zloto = atoi(token);
  }
  else if (strcmp(token, "TECH") == 0)
  {
    sprintf(typZapytania, "TECH");
    token = strtok(NULL, " ");
    ktora = atoi(token);
  }
  else if (strcmp(token, "EXIT") == 0)
  {
    exit(0);
  }
  else if (strcmp(token, "END") == 0)
  {
    sprintf(typZapytania, "END");
  }
  else
  {
    sprintf(typZapytania, "UNDEF");
  }

}

void ParserZapytan::zeruj()
{
  sprintf(typZapytania, "UNDEF");
}

ParserZapytan::ParserZapytan()
{
  sprintf(typZapytania, "UNDEF");
  px = 0;
  py = 0;
  dx = 0;
  dy = 0;
  punkty_zycia = 0;
  d_punkty_zycia = 0;
  punkty_ruchu = 0;
  atak = 0;
  obrona = 0;
  zwinnosc = 0;
  do_rozdysponowania = 0;
  poziom = 0;
  doswiadczenie = 0;
  exp = 0;
  pieniadze = 0;
}

ParserZapytan::~ParserZapytan(){}
