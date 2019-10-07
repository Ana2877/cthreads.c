#include "../include/cdata.h"
#include "../include/cthread.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

csem_t mutex;

void *return_void_star()
{
    printf("Thread1 tryng to enter in critial session\n");
    cwait(&mutex);
    printf("Thread1 entered in critical session\n");
    int x = 0;
    while (x<1000000000) {
      x++;
    }
    x = 0;
    cyield();
    while (x<1000000000) {
      x++;
    }
    printf("Thread1 finishing critical session\n");
    csignal(&mutex);
    printf("Thread1 leave critical session\n");
    return NULL;
}

int return_int()
{
  int x = 0;
  printf("Thread2 tryng to enter in critial session\n");
  cwait(&mutex);
  printf("Thread2 entered in critical session\n");
  while (x<1000000000) {
    x++;
  }
  printf("Thread2 finishing critical session\n");
  csignal(&mutex);
  printf("Thread2 leave critical session\n");
  return 0;
}

int main()
{
    csem_init(&mutex, 1);
    int thread1 = ccreate(&return_void_star, NULL, 0);
    int thread2 = ccreate((void *)&return_int, NULL, 0);

    cjoin(thread1);
    cjoin(thread2);
    return 0;
}
