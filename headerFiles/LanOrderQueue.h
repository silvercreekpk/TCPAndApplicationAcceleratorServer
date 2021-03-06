#define LanorderQueueIncluded

#ifndef headerIncluded
#include "headers.h"
#endif

#ifndef structIncluded
#include "types.h"
#endif

#ifndef constantsIncluded
#include "constants.h"
#endif

void Init_order(ORDER_QUEUE* queue, int capacity);


// Queue is full when size becomes equal to the capacity
int isFull_order(ORDER_QUEUE* queue);

// Queue is empty when size is 0
int isEmpty_order(ORDER_QUEUE* queue);


// Function to add an item to the queue.  It changes rear and size
void enqueue_order(ORDER_QUEUE* queue, ORDER_RECORD* item);

// Function to remove an item from queue.  It changes front and size
int dequeue_order(ORDER_QUEUE* queue);

// Function to get front of queue
ORDER_RECORD* front_order(ORDER_QUEUE* queue);


// Function to get rear of queue
ORDER_RECORD* rear_order(ORDER_QUEUE* queue);

//display data in queue
void displayOrderOnLogger(ORDER_QUEUE* queue, FILE* logfile);

