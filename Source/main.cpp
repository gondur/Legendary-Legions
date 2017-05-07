#include "main.h"

int main(int argc, char **argv)
{
  if (argc == 3)
  if (*argv[2] == 'd')
  {
    dev_mode = true;
    MIERZ_FPS = true;
  }
  system("binkplay /R logo.bik");
  if (argv[1] != NULL)
    gra gra1(argv[1]);
  else
    gra gra1("fullscreen");
  return 0;

}

END_OF_MAIN();
