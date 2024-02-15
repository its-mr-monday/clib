/* This file contains the implementation of a singly linked list
 * The list is implemented as a struct with a head and tail pointer
 * 
 * Author: Zackary Morvan
 */

#include "list.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void freeNode(Node * node);
void freeNodeA(Node * node, void (*freeData)(void *));

//Function is essentially a constructor for the node struct
Node * malloc_node(void * data) {
	Node * newNode = (Node *)malloc(sizeof(Node));
	newNode->data = data;
	newNode->next = NULL;
	return newNode;
}

//Function frees a given node and its data
void freeNode(Node * node) {
	if (node == NULL) {
		return;
	}

	if (node->next != NULL) {
		freeNode(node->next);
		node->next = NULL;
	}
	if (node->data != NULL) {
		free(node->data);
		node->data = NULL;
	}
	free(node);
}

//Function frees a given node and its data, but uses a function pointer to free the data
void freeNodeA(Node * node, void (*freeData)(void *)) {
	if (node == NULL) {
		return;
	}
	if (node->next != NULL) {
		freeNodeA(node->next, freeData);
		node->next = NULL;
	}
	if (node->data != NULL) {
		freeData(node->data);
		node->data = NULL;
	}
	free(node);
}

//Function is essentially a constructor for the list struct
List * malloc_list() {
	List * newList = (List *)malloc(sizeof(List));
	newList->head = NULL;
	newList->tail = NULL;
	newList->size = 0;
	return newList;
}

//Function frees the list and all of its nodes
void freeList(List * list) {
	if (list->head != NULL) {
		freeNode(list->head);
		list->head = NULL;
	}
	list->tail = NULL;
	free(list);
}

//Function frees the list and all of its nodes but uses a function pointer to free the data
void freeListA(List * list, void (*freeData)(void *)) {
	if (list->head != NULL) {
		freeNodeA(list->head, freeData);
		list->head = NULL;
	}
	list->tail = NULL;
	free(list);
}

/* The following functions are helper hidden functions for waling/crawling the list */

//The following function is used to get a node at a given index, if the index is out of bounds, 
//the function returns NULL
Node * getNode(List * list, int index) {
	if (index < 0 || index >= list->size) {
		return NULL;
	}
	Node * current = list->head;
	for (int i = 0; i < index; i++) {
		current = current->next;
	}
	return current;
}


/* The following functions are defined by the header file to use the list */

void list_clear(List * list) {
	if (list->head != NULL) {
		freeNode(list->head);
		list->head = NULL;
	}
	list->tail = NULL;
	list->size = 0;
}

void list_clearA(List * list, void (*freeData)(void *)) {
	if (list->head != NULL) {
		freeNodeA(list->head, freeData);
		list->head = NULL;
	}
	list->tail = NULL;
	list->size = 0;
}

//Append function for list, adds a new node to the end of the list
void list_append(List * list, void * data) {
	Node * newNode = malloc_node(data);
	if (list->head == NULL) {
		list->head = newNode;
		list->tail = newNode;
	} else {
		list->tail->next = newNode;
		list->tail = newNode;
	}
	list->size++;
}

void list_append_list(List * list, List * list2) {
	if (list2->head == NULL) {
		return;
	}
	if (list->head == NULL) {
		list->head = list2->head;
		list->tail = list2->tail;
		list->size = list2->size;
	} else {
		list->tail->next = list2->head;
		list->tail = list2->tail;
		list->size += list2->size;
	}
}

//Function is used to list_insert a new node at a given index, if the index is greater than the size of the 
//list, the node is list_appended to the end
void list_insert(List * list, void * data, int index) {
	if (list->head == NULL || index >= list->size) {
		list_append(list, data);
		return;
	}
	if (index < 0) {
		index = 0;
	}
	if (index == 0) {
		Node * newNode = malloc_node(data);
		newNode->next = list->head;
		list->head = newNode;
		list->size++;
		return;
	}
	Node * current = getNode(list, index - 1);
	if (current == NULL) {
		list_append(list, data);
		return;
	}
	Node * newNode = malloc_node(data);
	Node * next = current->next;
	newNode->next = next;
	current->next = newNode;
	list->size++;
	return;
}

void list_insert_list(List * list, List * list2, int index) {
	if (list2->head == NULL) {
		return;
	}
	if (list->head == NULL || index >= list->size) {
		list_append_list(list, list2);
		return;
	}
	if (index < 0) {
		index = 0;
	}
	if (index == 0) {
		list2->tail->next = list->head;
		list->head = list2->head;
		list->size += list2->size;
		return;
	}
	Node * current = getNode(list, index - 1);
	if (current == NULL) {
		list_append_list(list, list2);
		return;
	}
	Node * next = current->next;
	current->next = list2->head;
	list2->tail->next = next;
	list->size += list2->size;
}
//Function is used to list_remove a node at a given index, if the index is out of bounds or there is no node 
//the function returns NULL, if succeeded the function returns the data of the list_removed node
void * list_remove(List * list, int index) {
	if (index < 0 || index >= list->size) {
		return NULL;
	}
	if (index == 0) {
		if (list->head == NULL) {
			return NULL;
		}
		Node * temp = list->head;
		void * data = temp->data;
		list->head = list->head->next;
		free(temp);
		list->size--;
		return data;
	}
	Node * current = getNode(list, index - 1);
	if (current == NULL) {
		return NULL;
	}
	Node * temp = current->next;
	void * data = temp->data;
	current->next = temp->next;
	free(temp);
	list->size--;
	return data;
}

void list_slice(List * list, int start, int end) {
	if (start < 0) {
		start = 0;
	}
	if (end >= list->size) {
		end = list->size - 1;
	}
	if (start >= end) {
		return;
	}
	List * tempList = malloc_list();
	//We need to get the node prior to the start and after the end
	//If either are NULL we will have a empty list
	if (start == 0) {
		if (end < list->size - 1) {
			tempList->head = list->head;
			tempList->tail = getNode(list, end);
			tempList->size = end + 1;
			list->head = tempList->tail->next;
			tempList->tail->next = NULL;
			list->size -= tempList->size;
		} else {
			tempList->head = list->head;
			tempList->tail = list->tail;
			tempList->size = list->size;
			list->head = NULL;
			list->tail = NULL;
			list->size = 0;
		}
	} else {
		Node * startNode = getNode(list, start - 1);
		if (startNode == NULL) {
			return;
		}
		if (end < list->size - 1) {
			tempList->head = startNode->next;
			tempList->tail = getNode(list, end);
			tempList->size = end - start + 1;
			startNode->next = tempList->tail->next;
			tempList->tail->next = NULL;
			list->size -= tempList->size;
		} else {
			tempList->head = startNode->next;
			tempList->tail = list->tail;
			tempList->size = list->size - start;
			startNode->next = NULL;
			list->tail = startNode;
			list->size -= tempList->size;
		}
	}
	freeList(tempList);
}

void list_sliceA(List * list, int start, int end, void (*freeData)(void *)) {
	if (start < 0) {
		start = 0;
	}
	if (end >= list->size) {
		end = list->size - 1;
	}
	if (start >= end) {
		return;
	}
	List * tempList = malloc_list();
	//We need to get the node prior to the start and after the end
	//If either are NULL we will have a empty list
	if (start == 0) {
		if (end < list->size - 1) {
			tempList->head = list->head;
			tempList->tail = getNode(list, end);
			tempList->size = end + 1;
			list->head = tempList->tail->next;
			tempList->tail->next = NULL;
			list->size -= tempList->size;
		} else {
			tempList->head = list->head;
			tempList->tail = list->tail;
			tempList->size = list->size;
			list->head = NULL;
			list->tail = NULL;
			list->size = 0;
		}
	} else {
		Node * startNode = getNode(list, start - 1);
		if (startNode == NULL) {
			return;
		}
		if (end < list->size - 1) {
			tempList->head = startNode->next;
			tempList->tail = getNode(list, end);
			tempList->size = end - start + 1;
			startNode->next = tempList->tail->next;
			tempList->tail->next = NULL;
			list->size -= tempList->size;
		} else {
			tempList->head = startNode->next;
			tempList->tail = list->tail;
			tempList->size = list->size - start;
			startNode->next = NULL;
			list->tail = startNode;
			list->size -= tempList->size;
		}	
	}
	freeListA(tempList, freeData);
}

//Function is used to get the data of a node at a given index, if the index is out of bounds, the function
//returns NULL
void * list_get(List * list, int index) {
	Node * current = getNode(list, index);
	if (current == NULL) {
		return NULL;
	}
	return current->data;
}

//Function is used to list_pop the last node off the list, if the list is empty, the function returns NULL
void * list_pop(List * list) {
	return list_remove(list, list->size - 1);
}

void list_set(List * list, void * data, int index) {
	if (index < 0 || index >= list->size) {
		return;
	}
	Node * current = getNode(list, index);
	if (current == NULL) {
		return;
	}
	void * oldData = current->data;
	current->data = data;
	free(oldData);
}

void list_setA(List * list, void * data, int index, void (*freeData)(void *)) {
	if (index < 0 || index >= list->size) {
		return;
	}
	Node * current = getNode(list, index);
	if (current == NULL) {
		return;
	}
	void * oldData = current->data;
	current->data = data;
	freeData(oldData);
}

void printList(List * list, void (*printDataType)(void *)) {
	Node * current = list->head;
	printf("[");
	while (current != NULL) {
		if (current->data != NULL) {
			printDataType(current->data);
		} else {
			printf("NULL");
		}
		current = current->next;
		if (current != NULL) {
			printf(", ");
		}
	}
	printf("]\n");
}
