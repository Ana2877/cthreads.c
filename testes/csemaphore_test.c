#include "../include/cdata.h"
#include "../include/cthread.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

csem_t mutex;

void *return_void_star()
{
    cwait(&mutex);
    DEBUG("SLEEP");
    sleep(3);
    DEBUG("SLEPT");
    csignal(&mutex);
    return NULL;
}

int return_int()
{
    cwait(&mutex);
    DEBUG("TENTA ENTRAR");
    csignal(&mutex);
    return 0;
}

int main()
{
    csem_init(&mutex, 1);
    ccreate(&return_void_star, NULL, 0);
    ccreate((void *)&return_int, NULL, 0);

    return 0;
}
