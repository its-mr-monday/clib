#ifndef LIST_H
#define LIST_H
#pragma once
typedef struct Node {
    void * data;
    struct Node* next;
} Node;
typedef struct List {
    struct Node* head;
    struct Node* tail;
    int size;
} List;

Node * malloc_node(void * data);

List * malloc_list();
void freeList(List * list);
void freeListA(List * list, void (*freeData)(void *));
void list_append(List * list, void * data);
void list_append_list(List * list, List * list2);
void list_insert(List * list, void * data, int index);
void * list_remove(List * list, int index);
void list_slice(List * list, int start, int end);
void * list_get(List * list, int index);
void * list_pop(List * list);
void list_set(List * list, void * data, int index);
void list_setA(List * list, void * data, int index, void (*freeData)(void *));
void printList(List * list, void (*printDataType)(void *));
#endif
