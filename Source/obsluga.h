#ifndef _obsluga
  #define _obsluga

  /// klasa obslugujaca stan przyciskow myszy. Czy zostaly klikniete, badz zwolnione.
  class zdarzenia
  {
    private:
      /// informuje czy lewy przycisk myszki zostal wcisniety lub klikniety
      int l_wcisn;
      int l_klik;
      /// informuje czy prawy przycisk myszki zostal wcisniety lub klikniety
      int p_wcisn;
      int p_klik;
      /// lewy przycisk zwolniony i pomocnicze zmienne
      int l_zwol;
      int p_l_zwol1;
      int p_l_zwol2;
      /// prawy przycisk zwolniony i pomocnice zmienne
      int p_zwol;
      int p_p_zwol1;
      int p_p_zwol2;

      short aktualne_okno;

    public:
      zdarzenia(grafika *engine);
      ~zdarzenia(){}

      void wyswietl_okno(short);
      short zwroc_okno();

      /// sprawdza stan myszki i zapisuje go
      void odswiez();

      /// zwraca informacje o tym, czy lewy przycisk jest klikniety 
      bool l_klikniety();
      /// zwraca informacje o tym, czy prawy przycisk jest klikniety 
      bool p_klikniety();

      /// zwraca informacje o tym czy lewy przycisk jest zwolniony
      bool l_zwolniony();
      /// zwraca informacje o tym czy prway przycisk jest zwolniony
      bool p_zwolniony();

      /// funkcja zeruje stan wszystkich przycisków
      void zeruj();
  };

  #include "obsluga.cpp"

#endif
