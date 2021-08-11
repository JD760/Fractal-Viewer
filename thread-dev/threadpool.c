/* external includes */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/* project includes */
#include "threadpool.h"

/* function prototypes */
static void *threadpool_thread(void *pool);


extern threadpool_t * 
threadpool_create(int numThreads)
{
    threadpool_t *pool;
    /* request memory */
    pool = (threadpool_t *)malloc(sizeof(threadpool_t));
    if (pool == NULL)
    {
        printf("Memory allocation error in threadpool_create\n");
        return NULL;
    }

    /* Initialise values for threadpool */
    pool->num_threads = numThreads;
    pool->head = pool->tail = NULL;
    pool->started = pool->count = 0;
    pthread_cond_init(&pool->condition, NULL);
    pthread_mutex_init(&pool->task_lock, NULL);
    pthread_mutex_init(&pool->result_lock, NULL);
    pool->threads = (pthread_t *) malloc(sizeof(pthread_t) * numThreads);

    
    for (int i = 0; i < numThreads; i++)
    {
        if (pthread_create(&pool->threads[i], NULL, 
            threadpool_thread, (void *)pool) != 0)
        {
            printf("Failed to create thread %d\n", i);
            return NULL;
        }
        printf("Created thread %d\n", i);    
    }

    return pool;
}

extern void
threadpool_free()
{
    return;
}

/**
 * Add a task to the threadpool task queue 
 * pool -> pointer to the threadpool structure
 * task -> pointer to the task structure 
**/
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
    pthread_cond_signal(&(pool->condition));
}

/**
 * The function that each thread in the pool executes until the pool is
 * shut down or all tasks have been completed
 * pool -> pointer to the threadpool structure
**/
static void 
*threadpool_thread(void *threadpool)
{
    printf("thread execution started\n");
    threadpool_task_t *task;
    threadpool_t *pool = (threadpool_t *) threadpool;
    
    /* loop until no tasks remain */
    while(1)
    {
        /* Fetch task from the queue */
        /* Acquire lock before accessing shared data*/
        
        pthread_mutex_lock(&pool->task_lock);
        while (pool->count == 0)
        {
            pthread_cond_wait(&pool->condition, &pool->task_lock);
        }

        if (pool->head)
        {
            task = pool->head;
            if (pool->head->prev) 
            {
                pool->head->prev->next = NULL;
                pool->head = pool->head->prev;
            } else pool->head = pool->tail = NULL;
            pool->count--;
        } else {
            break;
        }
        pthread_mutex_unlock(&pool->task_lock);

        /* Execute thread function */
        task->function((void *)task->arg);

    }
    pthread_mutex_unlock(&pool->task_lock);
    pthread_exit(NULL);
}

int main()
{
    threadpool_t *pool;
    pool = threadpool_create(10);

    printf("Program execution complete\n");
    return 0;
}