#include "../include/cdata.h"
#include "../include/cthread.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

csem_t mutex;

void *return_void_star()
{
    cwait(&mutex);
    printf("WAITEI\n");
    int x = 0;
    while (x<1000000000) {
      x++;
    }
    x = 0;
    cyield();
    while (x<1000000000) {
      x++;
    }
    x = 0;
    printf("SOLTEI O CU PRA RUUUDA TUDO\n");
    csignal(&mutex);
    return NULL;
}

int return_int()
{
  int x = 0;
  printf("VO TENTA RUUDA TUDO\n");
  cwait(&mutex);
  while (x<1000000000) {
    x++;
  }
  printf("SÓ PRINTO DEPOIS CPX\n");
  csignal(&mutex);
  return 0;
}

int main()
{
    csem_init(&mutex, 1);
    int primeira = ccreate(&return_void_star, NULL, 0);
    int segunda = ccreate((void *)&return_int, NULL, 0);

    printf("Waiting for primeira e segunda (%d %d)\n", primeira, segunda);
    cjoin(primeira);
    cjoin(segunda);
    return 0;
}
