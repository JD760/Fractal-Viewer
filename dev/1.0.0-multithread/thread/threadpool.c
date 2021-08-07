/* external includes */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/* project includes */
#include "dev/1.0.0-multithread/thread/threadpool.h"

/* type definitions */

/* function prototypes */
//
static void *threadpool_thread(void *threadpool);
/* functions */

threadpool_t *threadpool_create(
    int num_threads
)
{
    // variable declarations
    threadpool_t *pool;
    pthread_t *threads;

    // allocate memory for the thread pool structure
    if (pool = (threadpool_t *) malloc(sizeof(threadpool_t)) == NULL)
    {
        return NULL;
    }

    // initialise pool values
    
    pthread_mutex_init(&pool->lock, NULL);
    pthread_cond_init(&pool->condition, NULL);
    pool->num_threads = num_threads;
    pool->task_count = 0;
    pool->shutdown = pool->started = 0;

    pool->queue = NULL;
    pool->front = NULL;
    pool->rear = NULL;

    if (threads = (pthread_t *) malloc(sizeof(pthread_t) * num_threads) == NULL)
    {
        return NULL;
    }

    for (int i = 0; i < pool->num_threads; i++)
    {
        if (pthread_create(&pool->threads[i], 
            NULL, threadpool_thread, (void *)pool) != 0)
        {
            threadpool_free(pool);
            return NULL;
        }
        pool->started++;
    }
    
    return pool;
}

/* add a Task to the thread pool */
void threadpool_add(threadpool_t *pool, void *(*thread_function)(void *), void *arg)
{
    threadpool_task_t *task;
    threadpool_task_t *next_task;
    task = (threadpool_task_t *) malloc(sizeof(threadpool_task_t));

    task->arg = arg;
    task->function = thread_function;
    
    // acquire lock before modifying pool
    pthread_mutex_lock(&pool->lock);
    // add the task to the queue
    if(pool->task_count > 0)
    {
        next_task = pool->rear;
        next_task->prev = task;
        task->next = next_task;
        task->prev = NULL;
        pool->rear = task;
    } else {
        task->next = task->prev = NULL;
        pool->front = pool->rear = task;
    }
    pool->task_count++;
    // release the lock as modification to pool is done
    pthread_mutex_unlock(&pool->lock);
}

/* Free memory requested by the thread pool */
void threadpool_free(threadpool_t *pool)
{
    // free tasks in the queue if any
    threadpool_task_t *rear_task;
    if (pool->rear)
    {
        rear_task = pool->rear;
        if (rear_task->next) pool->rear = rear_task->next;
        free(rear_task);
    }

    // free all other parts of the pool
    free(pool);
}

/**
 * The function executed by every thread, contains 
 * synchronisation tasks and executes the user-defined thread
 * function afterwards.
**/
void *threadpool_thread(void *threadpool)
{
    // mutex not needed as we are only reading data here
    threadpool_t *pool = (threadpool_t *)threadpool;
    threadpool_task_t *task;

    // fetch tasks while there are tasks remaining in the queue
    while (pool->task_count > 0)
    {
        // retrieve a task from the queue
        task = pool->front;
        // mutex required as this involves changing pointers
        if (pool->task_count > 1)
        {
            pthread_mutex_lock(&pool->lock);
            task->prev = pool->front;
            task->prev->next = NULL;
            pool->task_count--;
            pthread_mutex_unlock(&pool->lock);
        } else {
            pthread_mutex_lock(&pool->lock);
            pool->front = pool->rear = NULL;
            pool->task_count--;
            pthread_mutex_unlock(&pool->lock);
        }

        // process the task with its relevant function and arguments
        task->function(task->arg);
    }



}