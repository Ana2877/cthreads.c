#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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
int global_tid = FIRST_TID;

/* Prototypes to auxiliar functions */
void initialize_cthread();
void scheduler();
void wakeUp(int);

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
	new_thread->tid = global_tid++;
	printf("[DEBUG] Created new thread with TID %d\n", new_thread->tid);

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

	return new_thread->tid;
}

int cyield(void)
{
	TCB_t *current_thread;

	/* Initialize cthread library if not initialized yet */
	if (running == NULL)
		initialize_cthread();

	/* Update current_thread status to ready */
	current_thread = running;
	current_thread->state = PROCST_APTO;
	current_thread->prio = stopTimer(); /* Time since started running */

	/* Remove current running thread */
	running = NULL;

	/* Restart timer for next thread */
	startTimer();

	/* Swap context to the scheduler decide who runs */
	swapcontext(&(current_thread->context), scheduler_context);

	return 0;
}

int cjoin(int tid)
{
	TCB_t *joined_thread, *current_thread;

	/* Initialize cthread library if not initialized yet */
	if (running == NULL)
		initialize_cthread();

	current_thread = running;
	joined_thread = (TCB_t *)findPriorityQueue(ready, tid);

	/* If it is trying to wait for main, we return an error */
	if (tid == FIRST_TID)
		return -1;

	/* If this thread doesn't exist, we return an error */
	if (joined_thread == NULL)
		return -1;

	/* If there is already somebody waiting for this, we return an error */
	if (joined_thread->waited_by != NULL)
		return -1;

	/* Update waited_thread to mark current_thread as waiting for it */
	printf("[DEBUG] Thread tid %d is waited by thread tid %d\n", tid, current_thread->tid);
	joined_thread->waited_by = current_thread;

	/* Update current_thread status to blocked, and add it to their list */
	current_thread->state = PROCST_BLOQ;
	current_thread->prio = stopTimer();
	insertPriorityQueue(blocked, current_thread);

	/* Remove current running thread */
	running = NULL;

	/* Restart timer for next thread */
	startTimer();

	/* Swap context to the scheduler decide who runs */
	printf("[DEBUG] Swapping to scheduler!\n");
	swapcontext(&(current_thread->context), scheduler_context);

	return 0;
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
	main_TCB->tid = global_tid++;
	printf("[DEBUG] Created main thread with TID %d\n", main_TCB->tid);

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
	TCB_t *scheduled;
	printf("[DEBUG] Current running %p\n", (void *)running);

	/* If running is not null, this means the thread it was there just finished */
	if (running != NULL)
	{
		printf("[DEBUG] Thread tid %d just finished, waking up its children (if exists)...\n", running->tid);
		if (running->waited_by != NULL)
			wakeUp(running->waited_by->tid);

		/* Free memory, as it already finished */
		free(running);

		/* Clean the space for running, to schedule new value */
		running = NULL;
	}

	printf("[DEBUG] Reached scheduler!\n");
	scheduled = frontPriorityQueue(ready);
	if (scheduled == NULL)
	{
		printf("[ERROR] There is no thread to be scheduled\n");
		exit(1);
	}

	/* Remove the entry from the priority queue */
	popPriorityQueue(ready);

	/* Update state */
	scheduled->state = PROCST_EXEC;

	/* Update running */
	running = scheduled;

	/* Change context to the scheduled thread */
	printf("[DEBUG] Starting to run thread tid %d\n", running->tid);
	setcontext(&(scheduled->context));
}

/* Remove the tid with this value from the blocked list, and add it to the ready one */
void wakeUp(int tid)
{
	TCB_t *unblocked;

	printf("[DEBUG] Trying to wake up thread %d\n", tid);
	unblocked = (TCB_t *)findPriorityQueue(blocked, tid);
	removePriorityQueue(blocked, tid);

	/* If it was a valid thread to be unblocked, we add it to the ready ones */
	if (unblocked != NULL)
	{
		printf("[DEBUG] Waking up thread tid %d\n", tid);
		insertPriorityQueue(ready, (void *)unblocked);
	}

	return;
}
