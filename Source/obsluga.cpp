/// konstruktor klasy zdarzenia
zdarzenia::zdarzenia(grafika *_engine)
{
  l_wcisn = 0;
  p_wcisn = 0;

  l_klik = 0;
  p_klik = 0;

  l_zwol = 0;
  p_zwol = 0;
}

//******************************************************************************

void zdarzenia::wyswietl_okno(short _aktualne_okno)
{
  aktualne_okno = _aktualne_okno;
}

short zdarzenia::zwroc_okno()
{
  return aktualne_okno;
}


/// Funkcja aktualizujaca stan przyciskow myszy. Czy zostaly klikniete, badz zwolnione
void zdarzenia::odswiez()
{

  /// Sprawdzanie stanu lewego przycisku myszki, jeœli lewy przycisk jest wciœniety
  /// a poprzednio nie byl wcisniety, to zmiana stanu na wcisniety i klikniety
  /// w przeciwnym przypadku zmiana stanu na nie klikniety.
  /// Natomiast jeœli lewy przycisk nie jest wcisniety to zmian stanu na nie klikniety.
  if (mouse_b &1)
  {
    if (!l_wcisn)
    {
      l_wcisn = 1;
      l_klik = 1;
    }
    else
    {
      l_klik = 0;
    }
  }
  else
  {
    l_wcisn = 0;
  }

  /// To samo co powyzej tylko dla prawego przycisku myszy.
  if (mouse_b &2)
  {
    if (!p_wcisn)
    {
      p_wcisn = 1;
      p_klik = 1;
    }
    else
    {
      p_klik = 0;
    }
  }
  else
  {
    p_wcisn = 0;
  }

  /// sprawdzanie czy zostal zwolniony przycisk lewy

  /// przechowanie informacji o poprzednim stanie (czy byl zwolniony przycisk)
  p_l_zwol2 = p_l_zwol1;
  /// aktualizowanie stanu o przycisku
  p_l_zwol1 = mouse_b;

  /// jesli lewy przycisk jest nie wcisniety (pierwszy warunek), a byl (drugi warunek)
  /// to aktualnie przycisk jest zwolniony, w przeciwnym przypadku nie jest zwolniony
  if ((!(p_l_zwol1 &1)) && (p_l_zwol2 &1))
    l_zwol = true;
  else
    l_zwol = false;

  /// sprawdzanie czy zostal zwolniony przycisk prawy (sposob analogiczny jak dla
  /// przycisku lewego)
  p_p_zwol2 = p_p_zwol1;
  p_p_zwol1 = mouse_b;

  if ((!(p_p_zwol1 &2)) && (p_p_zwol2 &2))
    p_zwol = true;
  else
    p_zwol = false;

}

//******************************************************************************

/// zwraca informacje o tym, czy prawy przycisk jest klikniety 
bool zdarzenia::p_klikniety()
{
  return p_klik;
}

//******************************************************************************

/// zwraca informacje o tym, czy lewy przycisk jest klikniety 
bool zdarzenia::l_klikniety()
{
  return l_klik;
}

//******************************************************************************

/// zwraca informacje o tym czy prawy przycisk jest zwolniony
bool zdarzenia::p_zwolniony()
{
  return p_zwol;
}

//******************************************************************************

/// zwraca informacje o tym czy lewy przycisk jest zwolniony
bool zdarzenia::l_zwolniony()
{
  return l_zwol;
}

//******************************************************************************

/// funkcja zeruje stan wszystkich przycisków
void zdarzenia::zeruj()
{
  p_klik = 0;
  l_klik = 0;
  p_wcisn = 0;
  l_wcisn = 0;
  l_zwol = 0;
  p_zwol = 0;
}

#include "menu.h"
