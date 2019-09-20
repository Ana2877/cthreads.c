/*
 * priority_queue.h: arquivo de inclusão com os protótipos das funções responsáveis
 *                   por um wrapper ao redor das funções definidas em support.h
 *                   para termos uma biblioteca capaz de lidar com filas ordenadas
 *                   de maneira mais fácil
 *
 */

#include "support.h"

#ifndef _PRIORITY_QUEUE_H
#define _PRIORITY_QUEUE_H

/* Wrapper para representar PriorityQueue mais facilmente */
typedef FILA2 PriorityQueue;
typedef NODE2 PriorityQueueNode;

/*-------------------------------------------------------------------
Função:	Inicializa uma estrutura de dados do tipo PriorityQueue
Ret:	==0, se conseguiu
	    !=0, caso contrário (erro ou fila vazia)
-------------------------------------------------------------------*/
PriorityQueue *createPriorityQueue(void);

/*-------------------------------------------------------------------
Função:	Retorna o primeiro elemento da fila
Ret:	-> Ponteiro válido, se conseguiu
	    -> NULL, caso fila esteja vazia
-------------------------------------------------------------------*/
void *frontPriorityQueue(PriorityQueue *pq);

/*-------------------------------------------------------------------
Função:	Exclui o primeiro elemento da fila.
        Caso esteja vazia, não faz nada.
-------------------------------------------------------------------*/
void popPriorityQueue(PriorityQueue *pq);

/*-------------------------------------------------------------------
Função:	Coloca o ponteiro "content" na posição correta na PriorityQueue,
        de acordo com a sua prioridade
-------------------------------------------------------------------*/
void insertPriorityQueue(PriorityQueue *pq, void *content);

/*-------------------------------------------------------------------
Função:	Procura na PriorityQueue um TCB cujo TID seja igual
        ao valor passado como parâmetro
-------------------------------------------------------------------*/
void *findPriorityQueue(PriorityQueue *pq, int value);

/* Procura na lista um TCB cujo TID seja o valor passado,
   e remove essa entrada da PriorityQueue */
/*-------------------------------------------------------------------
Função:	Procura na PriorityQueue um TCB cujo TID seja igual
        ao valor passado como parâmetro, e o remove da lista
Ret:    -> 0 se consegue deletar o valor
        -> -1 se não consegue encontrar o valor na lista
-------------------------------------------------------------------*/
int removePriorityQueue(PriorityQueue *pq, int value);

#endif