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
