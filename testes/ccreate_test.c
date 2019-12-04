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

int return_with_param(void *param)
{
    return (int)param;
}

/*
    Testa funcionamento do ccreate com diferentes tipos de parametros

    Deve criar todas as thread sem erros, e sem imprimir nada na tela
*/
int main()
{
    int r1 = ccreate(&return_void_star, NULL, 0);
    int r2 = ccreate((void *)&return_int, NULL, 0);
    int r3 = ccreate((void *)&return_with_param, (void *)(2 << 10), 0);

    if (r1 < 0 || r2 < 0 || r3 < 0)
    {
        printf("Error while creating threads.\n");
    }

    return 0;
}