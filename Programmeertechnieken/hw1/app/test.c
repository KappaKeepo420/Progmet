#include "mylib.h"
#include "stdio.h"

int main () {

  int x = 5;
  int y = 7;

  printf("Dit is telop: %d \n", telop(x, y));
  printf("Dit is vermenigvuldig: %d \n", vermenigvuldig(x, y));
  printf("Dit is modulo: %d \n", modulo(x, y));

  return 0;
}
