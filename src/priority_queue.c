#include "../include/priority_queue.h"
#include "../include/cdata.h"
#include <stdio.h>
#include <stdlib.h>

/* Inicializa uma estrutura de dados do tipo PriorityQueue. */
PriorityQueue *createPriorityQueue(void)
{
    PriorityQueue *pq = (PFILA2)malloc(sizeof(PFILA2));
    CreateFila2((PFILA2)pq);
    return pq;
}

/* Retorna o primeiro elemento da fila. */
void *frontPriorityQueue(PriorityQueue *pq)
{
    if (FirstFila2(pq) != 0)
        return NULL;

    return GetAtIteratorFila2((PFILA2)pq);
}

/* Exclui o primeiro elemento da fila. */
void popPriorityQueue(PriorityQueue *pq)
{
    if (FirstFila2((PFILA2)pq) != 0)
        return;

    DeleteAtIteratorFila2((PFILA2)pq); /* Doesn't need to use the value */
    return;
}

/* Coloca o ponteiro "content" na posição correta na PriorityQueue,
        de acordo com a sua prioridade */
void insertPriorityQueue(PriorityQueue *pq, void *content)
{
    TCB_t *current_node = (TCB_t *)content;
    printf("Trying to add node with prio %d\n", current_node->prio);

    /* If pq is empty, we append it to the end */
    if (FirstFila2(pq) != 0)
    {
        printf("[DEBUG] PQ empty, we must add at the end\n");
        AppendFila2((PFILA2)pq, content);
        return;
    }

    /* Iterate to find where we should add our current_node */
    while (GetAtIteratorFila2(pq) != NULL)
    {
        TCB_t *node = (TCB_t *)GetAtIteratorFila2((PFILA2)pq);
        printf("Current at node with prio %d\n", node->prio);

        /* We will use a descending priority order */
        if (node->prio >= current_node->prio)
            NextFila2((PFILA2)pq);
        else
            break;
    }

    /* If we have an iterator, we append before it, else we append at the end of the queue */
    if (GetAtIteratorFila2((PFILA2)pq) != NULL)
    {
        printf("[DEBUG] Pq not empty, added before an iterator with prio %d\n", ((TCB_t *)GetAtIteratorFila2(pq))->prio);
        InsertBeforeIteratorFila2((PFILA2)pq, content);
    }
    else
    {
        AppendFila2((PFILA2)pq, content);
        printf("[DEBUG] Need to add at the end\n");
    }

    return;
}