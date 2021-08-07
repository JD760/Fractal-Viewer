/*
 * Thread pools allow many tasks to be shared among a number of threads
 * work is handed to threads and completed, taken from a queue of work.
*/

// external includes
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// project (local) includes
#include "dev/1.0.0-multithread/thread/threadpool.h"

/* type definitions */
    /* Queue System */
typedef struct Task{
    struct Task *prev;
    struct Task *next;
    int startX;
    int startY;
    int TaskNum;
    int *iterationData;
}Task;

typedef struct Queue{
    Task *front;
    Task *end;
    int length;
}Queue;

    /* Thread Pool */

typedef struct ThreadPool{
    pthread_t *threads;
    int numThreads;
    Queue *work;
    pthread_mutex_t queue_mutex;
    pthread_mutex_t data_mutex;
    
}ThreadPool;

typedef struct computeBlockArgs{
    Queue *work;
    pthread_mutex_t queue_mutex;
    pthread_mutex_t data_mutex;
    
}computeBlockArgs;

// Function Prototypes
Queue *createQueue();
void Enqueue();
Task *Dequeue();
ThreadPool *createThreadPool(int numThreads, computeBlockArgs *args, Queue *queue, void *(*start_routine)(void *));
void computeBlock(void *args);

/* QUEUE SYSTEM */
// set up a queue structure for adding and removing work
// queues follow First In First Out structure, oldest item taken first

Queue *createQueue()
{
    Queue *queue = malloc(sizeof(Queue));
    queue->length = 0;
    queue->end = NULL;
    queue->front = NULL;
    return queue;
}

void Enqueue(
    Queue *queue,
    Task *task
)
{
    if (queue->length == 0)
    {
        // if no existing elements, the new element is both the front
        // and end of the queue
        queue->front = task;
        queue->end = task;
        queue->length++;
    } else {
        // get the next element in the list and adjust pointers such
        // that the new element is the new end, pointing to the next
        // element and with the next element pointing back to it
        Task *nextTask = queue->end;
        queue->end = task;
        nextTask->prev = task;
        task->next = nextTask;
        task->prev = NULL;
        queue->length++;
    }
}

/*
 * Return the element at the front of the list and remove it from
 * this position 
*/
Task *Dequeue(
    Queue *queue
)
{
    // no item to fetch if the queue has no items in it
    if (queue->length == 0) return NULL;

    Task *task = queue->front;
    if (task->prev)
    {
        queue->front = task->prev;
        task->prev->next = NULL;
    } else {
        queue->front = NULL;
        queue->end = NULL;
    } 

    queue->length--;
    return task;
}


/* THREAD POOL SYSTEM */
ThreadPool *createThreadPool(
    int numThreads,
    computeBlockArgs *args,
    Queue *queue,
    void *(*start_routine)(void *)
)
{
    ThreadPool *pool = malloc(sizeof(ThreadPool));

    pthread_mutex_init(&pool->queue_mutex, NULL);
    pthread_mutex_init(&pool->data_mutex, NULL);

    for (int i = 0; i < numThreads; i++)
    {
        pthread_create(&pool->threads[i], NULL, start_routine, (void *)args);
    }

}

void computeBlock(void *args)
{
    computeBlockArgs *parameters = (computeBlockArgs*)args;

    // retrieve the block to compute from the queue
    pthread_mutex_lock(&parameters->queue_mutex);
    Task *task = Dequeue(parameters->work);
    pthread_mutex_unlock(&parameters->queue_mutex);

    // compute the iteration data for each pixel in the block area
    for (int i = task->startY; i < task->startY + 40; i++)
    {
        for (int j = task->startX; j < task->startX + 40; j++)
        {

        }
    }

    // write the data to the relevant positions on the iteration data array
    

}

int main()
{
    Queue *queue;
    queue = createQueue();

    Task *block1 = malloc(sizeof(Task));
    Task *block2 = malloc(sizeof(Task));

    Enqueue(queue, block1);
    Enqueue(queue, block2);
    printf("Queue Length: %d\n", queue->length);
    if (queue->front == block1) printf("Added to queue\n");

    printf("Front: %x , End: %x\n", queue->front, queue->end);
    printf("Prev: %x , Next: %x\n", block2->prev, block2->next);

    Dequeue(queue);
    Dequeue(queue);
    printf("Front: %x , End: %x\n", queue->front, queue->end);
    printf("Dequeued\n");

    // function pointer
    void*(*fun_ptr)(void *) = &createQueue;
    return 0;
}

