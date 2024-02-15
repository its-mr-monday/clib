#include "queue.h"
#include <stdlib.h>
#include <stdio.h>

/* Inner List Management fucntions */

/* Standard Queue Functions defined in Header */

Queue* malloc_queue() {
	Queue * q = (Queue*)malloc(sizeof(Queue));
	List * innerList = malloc_list();
	q->list = innerList;
	return q;
}

void free_queue(Queue * queue) {
	free_list(q->list);
	free(q);
}

void free_queueA(Queue *queue, void (*freeData)(void *)) {
	free_listA(queue->list, freeData);
	free(queue);
}

void queue_push(Queue *queue, void *data) {
	list_push(queue->list, data);
}

void *queue_pop(Queue *queue) {
	void *data = list_remove(queue->list, 0);
	return data;
}

void *queue_peek(Queue *queue) {
	void *data = list_get(queue->list, 0);
	return data;
}

int queue_size(Queue *queue) {
	return queue->list->size;
}

bool queue_is_empty(Queue *queue) {
	if (queue->list->size == 0) {
		return true;
	}
	return false;
}
