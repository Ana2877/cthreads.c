#include "../include/cdata.h"
#include "../include/cthread.h"
#include <stdio.h>
#include <stdlib.h>

void *return_void_star()
{
    return NULL;
}

int return_int()
{
    return 0;
}

int return_with_param(int param)
{
    return param;
}

int main()
{
    int first_tid = ccreate(&return_void_star, NULL, 0);
    ccreate((void *)&return_int, NULL, 0);
    ccreate((void *)&return_with_param, (void *)(2 << 10), 0);

    printf("Waiting for tid %d\n", first_tid);
    cjoin(first_tid);

    return 0;
}