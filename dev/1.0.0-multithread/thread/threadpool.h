/* type definitions */

typedef struct {
    void *(*function)(void *);
    void *arg;
    threadpool_task_t *prev;
    threadpool_task_t *next;
} threadpool_task_t;

typedef struct threadpool_t {
    pthread_mutex_t lock;       // mutex
    pthread_cond_t condition;   // conditional variable
    int num_threads;            // number of threads in use
    int task_count;             // number of tasks to complete
    int shutdown;               // is the pool active?
    int started;                // number of active threads
    pthread_t *threads;         // starting ptr of thread array
    threadpool_task_t *queue;   // starting ptr of task queue
    threadpool_task_t *front;   // task queue 'front' element
    threadpool_task_t *rear;    // task queue 'rear' element
}threadpool_t;

/* function prototypes */
threadpool_t *threadpool_create(int num_threads);
void threadpool_addWork(threadpool_t *pool, threadpool_task_t);
void threadpool_destroy(threadpool_t *pool);