/*  Auteurs         - Jort Gijzen       1874233
                    - Lennard Schaap    1914839
    Studie          - BSc Informatica
    Datum           - 16 februari 2017
    Opdracht        - Building and Linking a library.
    File						- Makefile

    Dit is de mylib.c file. Hierin staan functies die worden aangeroepen in
    de test file om te kijken of deze twee aan elkaar correct gelinked zijn.
*/

#include "mylib.h"

int telop (int x, int y) {
  return x + y;
}

int vermenigvuldig (int x, int y) {
  return x * y;
}

int modulo (int x, int y) {
  return x % y;
}
