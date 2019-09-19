#include <stdio.h>
#include <string.h>
#include "../include/support.h"
#include "../include/cthread.h"
#include "../include/cdata.h"
#include "../include/priority_queue.h"

/* Configure default values */
#define FIRST_TID 0
#define STACK_SIZE (2 << 16)

/* Configure global variables */
TCB_t *running = NULL;
PriorityQueue *ready = NULL;
PriorityQueue *blocked = NULL;
ucontext_t *scheduler_context = NULL;
int tid = FIRST_TID;

/* Prototypes to auxiliar functions */
void initialize_cthread();
void scheduler();

int ccreate(void *(*start)(void *), void *arg, int prio)
{
	TCB_t *new_thread;

	/* Initialize cthread library if not initialized yet */
	if (running == NULL)
		initialize_cthread();

	/* Allocate new thread TCB */
	new_thread = (TCB_t *)malloc(sizeof(TCB_t));
	new_thread->state = PROCST_APTO;
	new_thread->prio = 0;
	new_thread->tid = tid++;

	/* Initialize context of it */
	if (getcontext(&new_thread->context) == -1)
		return -1;
	new_thread->context.uc_link = scheduler_context;
	new_thread->context.uc_stack.ss_sp = malloc(STACK_SIZE);
	new_thread->context.uc_stack.ss_size = STACK_SIZE;
	new_thread->context.uc_stack.ss_flags = 0;
	makecontext(&new_thread->context, (void (*)(void))start, 1, arg);

	/* Add it to the Ready Queue */
	insertPriorityQueue(ready, (void *)new_thread);

	return 0;
}

int cyield(void)
{
	/* Initialize cthread library if not initialized yet */
	if (running == NULL)
		initialize_cthread();

	return -9;
}

int cjoin(int tid)
{
	/* Initialize cthread library if not initialized yet */
	if (running == NULL)
		initialize_cthread();

	return -9;
}

int csem_init(csem_t *sem, int count)
{
	/* Initialize cthread library if not initialized yet */
	if (running == NULL)
		initialize_cthread();

	return -9;
}

int cwait(csem_t *sem)
{
	/* Initialize cthread library if not initialized yet */
	if (running == NULL)
		initialize_cthread();

	return -9;
}

int csignal(csem_t *sem)
{
	/* Initialize cthread library if not initialized yet */
	if (running == NULL)
		initialize_cthread();

	return -9;
}

int cidentify(char *name, int size)
{
	/* Initialize cthread library if not initialized yet */
	if (running == NULL)
		initialize_cthread();

	strncpy(name, "Ana Carolina Pagnoncelli - 00287714\nAugusto Zanella Bardini  - 00278083\nRafael Baldasso Audibert - 00287695", size);
	return 0;
}

/* AUXILIAR FUNCTIONS */

/* First time running a cthread function, so need to create TCB for
   main and PriorityQueues for ready and blocked */
void initialize_cthread()
{
	TCB_t *main_TCB = (TCB_t *)malloc(sizeof(TCB_t));
	main_TCB->state = PROCST_EXEC;
	main_TCB->prio = 0;
	main_TCB->tid = tid++;

	/* Configure the global variables */
	running = main_TCB;
	ready = createPriorityQueue();
	blocked = createPriorityQueue();

	/* Configure scheduler_context (with utc_link pointing to itself - infinite loop) */
	scheduler_context = (ucontext_t *)malloc(sizeof(ucontext_t));
	getcontext(scheduler_context);
	scheduler_context->uc_link = scheduler_context;
	scheduler_context->uc_stack.ss_sp = malloc(STACK_SIZE);
	scheduler_context->uc_stack.ss_size = STACK_SIZE;
	scheduler_context->uc_stack.ss_flags = 0;
	makecontext(scheduler_context, scheduler, 1, NULL);

	/* Start counting the time for the main thread */
	startTimer();
}

/* Scheduler */
void scheduler()
{
	return;
}
