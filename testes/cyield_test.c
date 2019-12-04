#include "../include/cdata.h"
#include "../include/cthread.h"
#include <stdio.h>
#include <stdlib.h>

void *return_1()
{
  printf("Starting thread1\n");
  int x = 0;
  while (x < 1000000000)
  {
    x++;
  }
  x = 0;
  printf("thread1 yield\n");

  cyield();

  printf("Finishing Thread1\n");
  while (x < 1000000000)
  {
    x++;
  }
  printf("thread1 finished\n");

  return NULL;
}

void *return_2()
{
  printf("Starting thread2\n");
  int x = 0;
  while (x < 10000000)
  {
    x++;
  }
  x = 0;
  printf("thread2 yield\n");

  cyield();

  printf("Finishing Thread2\n");
  while (x < 10000000)
  {
    x++;
  }
  printf("thread2 finished\n");

  return 0;
}

void *return_3()
{
  printf("thread3 started and finished\n");
  return NULL;
}

/*
  Testa funcionamento do csempahore

  Deve imprimir, em ordem:
    Starting thread1
    thread1 yield
    Starting thread2
    thread2 yield
    thread3 started and finished
    Finishing Thread2
    thread2 finished
    Finishing Thread1
    thread1 finished

  Função principal cria 3 threads. Damos join em sequencia nelas. Devemos rodar, em ordem,
  thread1, depois thread2, depois thread3, por causa dos timeouts usados.
*/
int main()
{
  int thread1 = ccreate(&return_1, NULL, 0);
  int thread2 = ccreate(&return_2, NULL, 0);
  int thread3 = ccreate(&return_3, NULL, 0);

  cjoin(thread1);
  cjoin(thread2);
  cjoin(thread3);

  return 0;
}
