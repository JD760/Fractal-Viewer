#include <pthread.h>

typedef struct {
    void *(*function)(void *);
    void *arg;
    threadpool_task_t *next;
}threadpool_task_t;


typedef struct {
    pthread_mutex_t *task_lock;     // lock used for fetching the task
    pthread_mutex_t *result_lock;   // lock used for processing results
    pthread_cond_t *condition;      // condition variable
    int num_threads;                // the number of threads to utilise
    pthread_t *threads;             // array containing each thread
    threadpool_task_t *head;        // front of the task queue
    threadpool_task_t *tail;        // rear of the task queue
    int count;                      // number of tasks to complete
    int started;                    // number of tasks currently running

}threadpool_t;