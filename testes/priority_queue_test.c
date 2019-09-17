#include "../include/priority_queue.h"
#include "../include/cdata.h"
#include <stdio.h>
#include <stdlib.h>

#define TCB_SIZE 6

int main()
{
    int i;
    TCB_t *TCB[TCB_SIZE];

    for (i = 0; i < TCB_SIZE; i++)
    {
        TCB[i] = (TCB_t *)malloc(sizeof(TCB_t));
        TCB[i]->prio = i;
    }

    PriorityQueue *pq = createPriorityQueue();
    printf("Created pq\n");
    insertPriorityQueue(pq, (void *)TCB[0]);
    insertPriorityQueue(pq, (void *)TCB[1]);
    insertPriorityQueue(pq, (void *)TCB[TCB_SIZE - 1]);
    insertPriorityQueue(pq, (void *)TCB[2]);
    insertPriorityQueue(pq, (void *)TCB[3]);

    /* Must print TCB_SIZE - 1 */
    TCB_t *returned = (TCB_t *)frontPriorityQueue(pq);
    printf("%d == %d \n", returned->prio, TCB_SIZE - 1);

    /* Must print 3 */
    popPriorityQueue(pq);
    returned = (TCB_t *)frontPriorityQueue(pq);
    printf("%d == 3\n", returned->prio);

    /* Must equal NULL */
    popPriorityQueue(pq);
    popPriorityQueue(pq);
    popPriorityQueue(pq);
    popPriorityQueue(pq);
    returned = (TCB_t *)frontPriorityQueue(pq);
    printf("%p == (nil)", returned);

    return 0;
}