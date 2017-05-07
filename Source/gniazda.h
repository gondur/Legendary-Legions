#ifndef _GNIAZDA
  #define _GNIAZDA

  /*
  #include <sys/types.h>
  #include <sys/socket.h>
  #include <netinet/in.h>
  #include <sys/wait.h>
  #include <arpa/inet.h>
  #include <unistd.h>

   */

  #include <winsock2.h>
  #include <stdio.h>
  #include <string.h>
  #include <stdlib.h>
  // open
  #include <sys/stat.h>
  #include <fcntl.h>

  const int MAX_SIZE = 99;

  int utworzPolaczenie(char *ip, int port);
  int wyslijTekst(int gniazdo, char *tekst);
  int wyslijPlik(int gniazdo, char *nazwaPliku);
  int utworzGniazdoSerwera(int port);
  void Blad(char *tekst);
  void zatzymajWinsocket();
  void inicjujWinsocket();

  #include "gniazda.cpp"

#endif
