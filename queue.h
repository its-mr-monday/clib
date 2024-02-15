#ifndef QUEUE_H
#define QUEUE_H
#pragma once
#include "list.h"
#include <stdbool.h>

typedef struct Queue {
	List *list;
} Queue;

Queue * malloc_queue();
void free_queue(Queue *queue);
void free_queueA(Queue *queue, void (*free_data)(void *));
void queue_push(Queue *queue, void *data);
void * queue_pop(Queue *queue);
void * queue_peek(Queue *queue);
int queue_size(Queue *queue);
bool queue_is_empty(Queue *queue);

#endif
