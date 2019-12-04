#include "../include/cdata.h"
#include "../include/cthread.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

csem_t mutex;

void *return_1()
{
  int x = 0;

  printf("Thread1 trying to enter in critial session\n");
  cwait(&mutex);

  printf("Thread1 entered in critical session\n");
  while (x < 1000000000)
  {
    x++;
  }
  x = 0;

  cyield();

  while (x < 1000000000)
  {
    x++;
  }
  printf("Thread1 finishing critical session\n");
  csignal(&mutex);
  printf("Thread1 left critical session\n");

  return NULL;
}

void *return_2()
{
  int x = 0;

  printf("Thread2 trying to enter in critial session\n");
  cwait(&mutex);

  printf("Thread2 entered in critical session\n");
  while (x < 1000000000)
  {
    x++;
  }

  printf("Thread2 finishing critical session\n");
  csignal(&mutex);
  printf("Thread2 left critical session\n");

  return 0;
}

/*
  Testa funcionamento do csempahore

  Deve imprimir, em ordem:
    Thread1 trying to enter in critial session
    Thread1 entered in critical session
    Thread2 trying to enter in critial session
    Thread1 finishing critical session
    Thread1 left critical session
    Thread2 entered in critical session
    Thread2 finishing critical session
    Thread2 left critical session

  Faz thread 1 entrar na seção crítica, e dá yield para thread 2, que não consegue entrar.
  Quando thread 1 liberar seção crítica, thread 2 consegue.
*/
int main()
{
  csem_init(&mutex, 1);
  int thread1 = ccreate(&return_1, NULL, 0);
  int thread2 = ccreate(&return_2, NULL, 0);

  cjoin(thread1);
  cjoin(thread2);

  return 0;
}
