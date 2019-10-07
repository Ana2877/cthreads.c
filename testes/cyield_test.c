#include "../include/cdata.h"
#include "../include/cthread.h"
#include <stdio.h>
#include <stdlib.h>

void *return_void_star()
{
    printf("Starting thread1\n");
    int x = 0;
    while (x<1000000000) {
      x++;
    }
    x = 0;
    printf("thread1 yield\n");
    cyield();
    printf("Finishing Thread1\n");
    while (x<1000000000) {
      x++;
    }
    printf("thread1 finished\n");
    return NULL;
}

int return_int()
{
    printf("Starting thread2\n");
    int x = 0;
    while (x<10000000) {
      x++;
    }
    x = 0;
    printf("thread2 yield\n");
    cyield();
    printf("Finishing Thread2\n");
    while (x<10000000) {
      x++;
    }
    printf("thread2 finished\n");
    return 0;
}

int return_with_param(int param)
{
    printf("thread3 started and finished\n");
    return param;
}

int main()
{
    int thread1 = ccreate(&return_void_star, NULL, 0);
    int thread2 = ccreate((void *)&return_int, NULL, 0);
    int thread3 = ccreate((void *)&return_with_param, (void *)(2 << 10), 0);

    cjoin(thread1);
    cjoin(thread2);
    cjoin(thread3);

    return 0;
}
