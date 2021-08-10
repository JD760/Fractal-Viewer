/* external includes */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/* project includes */
#include "threadpool.h"

/* function prototypes */
static void threadpool_thread(void *pool);


extern int 
threadpool_create(int numThreads)
{
    threadpool_t *pool;
    /* request memory */
    if (pool = malloc(sizeof(threadpool_t)) == NULL)
    {
        printf("Memory allocation error in threadpool_create\n");
        return 1;
    }

    /* Initialise values for threadpool */
    pool->num_threads = numThreads;
    pool->head = pool->tail = NULL;
    pool->started = pool->count = 0;
    pthread_cond_init(&pool->condition, NULL);
    pthread_mutex_init(&pool->task_lock, NULL);
    pthread_mutex_init(&pool->result_lock, NULL);

    for (int i = 0; i < numThreads; i++)
    {
        pthread_create(&pool->threads[i], NULL, 
            threadpool_thread, (void *)pool);
    }

    return 0;
}

extern void
threadpool_free()
{

}

extern void 
threadpool_add(threadpool_t *pool, threadpool_task_t *task)
{
    if (pool->tail)
    {
        task->next = pool->tail;
        pool->tail->prev = task;
        pool->tail = task;
    }
    else 
    {
        pool->head = task;
        pool->tail = task;
        task->prev = task->next = NULL;
    }
    pool->count++;
}
