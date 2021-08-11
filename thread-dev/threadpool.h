#include <pthread.h>

// include guard
#ifndef THREADPOOL_H
#define THREADPOOL_H

/* Forward declaration of structs */
typedef struct threadpool_task_t threadpool_task_t;
typedef struct threadpool_t threadpool_t;

/* define structs */
typedef struct threadpool_task_t
{
    void *(*function)(void *);
    void *arg;
    threadpool_task_t *next;
    threadpool_task_t *prev;
}threadpool_task_t;


typedef struct threadpool_t
{
    pthread_mutex_t task_lock;     // lock used for fetching the task
    pthread_mutex_t result_lock;   // lock used for processing results
    pthread_cond_t condition;      // condition variable
    int num_threads;                // the number of threads to utilise
    pthread_t *threads;             // array containing each thread
    threadpool_task_t *head;        // front of the task queue
    threadpool_task_t *tail;        // rear of the task queue
    int count;                      // number of tasks to complete
    int started;                    // number of threads currently running

}threadpool_t;


#endif