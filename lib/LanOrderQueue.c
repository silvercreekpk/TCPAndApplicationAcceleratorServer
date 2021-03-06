
/*
 *
 *
 *  Created on: Sep 7, 2017
 *      Author: deshanchathusanka
 */

#include <writeInLogger.h>
#include <LanOrderQueue.h>

void Init_order(ORDER_QUEUE* queue, int capacity)
{
    queue->capacity = capacity;
    queue->front = queue->size = 0;
    queue->rear = -1;
    queue->orderRecordArray = (ORDER_RECORD**) malloc(queue->capacity * sizeof(ORDER_RECORD*));
}

// Queue is full when size becomes equal to the capacity
int isFull_order(ORDER_QUEUE* queue)
{
	return (queue->size == queue->capacity);
}

// Queue is empty when size is 0
int isEmpty_order(ORDER_QUEUE* queue)
{
	return (queue->size == 0);
}

// Function to add an item to the queue.  It changes rear and size
void enqueue_order(ORDER_QUEUE* queue, ORDER_RECORD* item)
{

	if (isFull_data(queue))
		return;

	pthread_mutex_lock(&queue->rearLock);
	queue->rear = (queue->rear+1)%(queue->capacity);
	pthread_mutex_unlock(&queue->rearLock);
	queue->orderRecordArray[queue->rear] = item;

	pthread_mutex_lock(&queue->sizeLock);
	++queue->size;
	pthread_mutex_unlock(&queue->sizeLock);
}

// Function to remove an item from queue.  It changes front and size
int dequeue_order(ORDER_QUEUE* queue)
{
	if (isEmpty_data(queue))
		return INT_MIN;
	DATA_RECORD* item = queue->orderRecordArray[queue->front];
	pthread_mutex_lock(&queue->frontLock);
	queue->front=(queue->front+1)%(queue->capacity);
	pthread_mutex_unlock(&queue->frontLock);

	pthread_mutex_lock(&queue->sizeLock);
	queue->size = queue->size - 1;
	pthread_mutex_unlock(&queue->sizeLock);
	return item;
}

// Function to get front of queue
ORDER_RECORD* front_order(ORDER_QUEUE* queue)
{
    if (isEmpty_order(queue))
        return INT_MIN;
    return queue->orderRecordArray[queue->front];
}

// Function to get rear of queue
ORDER_RECORD* rear_order(ORDER_QUEUE* queue)
{
    if (isEmpty_order(queue))
        return INT_MIN;
    return queue->orderRecordArray[queue->rear];
}

void displayOrderOnLogger(ORDER_QUEUE* queue, FILE* logfile)
{

	int i=queue->front;
	if(queue->front<=queue->rear){

		 for(;i<=queue->rear;i++)
		 {
			 fprintf(logfile,"order record : %d\n",i);
			 fprintf(logfile,"sessionId : %d\n",queue->orderRecordArray[i]->sessionId);
			 fprintf(logfile,"location : %d\n\n",queue->orderRecordArray[i]->location);

		 }
	}else{

		 for(;(i%(queue->capacity))!=(queue->rear);++i)
		 {
			 fprintf(logfile,"order record : %d\n",i%(queue->capacity));
			 fprintf(logfile,"sessionId : %d\n",queue->orderRecordArray[i%(queue->capacity)]->sessionId);
			 fprintf(logfile,"location : %d\n\n",queue->orderRecordArray[i]->location);

		 }
	}


     return;
}
