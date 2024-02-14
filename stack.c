#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

StackNode* malloc_stack_node(void* data) {
	StackNode* node = (StackNode*)malloc(sizeof(StackNode));
	node->data = data;
	node->previous = NULL;
	return node;
}

Stack* malloc_stack() {
	Stack* stack = (Stack*)malloc(sizeof(Stack));
	stack->top = NULL;
	stack->size = 0;
	return stack;
}

void free_stack_node(StackNode* node) {
	if (node->previous != NULL) {
		free_stack_node(node->previous);
	}
	free(node->data);
	free(node);
}

void free_stack_nodeA(StackNode* node, void (*free_data)(void*)) {
	if (node->previous != NULL) {
		free_stack_nodeA(node->previous);
	}
	free_data(node->data);
	free(node);
}

void free_stack(Stack* stack) {
	if (stack->top != NULL) {
		free_stack_node(stack->top);
	}
	free(stack);
}

void free_stackA(Stack* stack, void (*freeData)(void*)) {
	if (stack->top != NULL) {
		free_stack_nodeA(stack->top, freeData);
	}
	free(stack);
}

void stack_push(Stack* stack, void* data) {
	StackNode* node = malloc_stack_node(data);
	node->previous = stack->top;
	stack->top = node;
	stack->size++;
}

void* stack_pop(Stack* stack) {
	if (stack->top == NULL) {
		return NULL;
	}
	StackNode* node = stack->top;
	stack->top = node->previous;
	stack->size--;
	void* data = node->data;
	free(node);
	return data;
}

void* stack_peek(Stack* stack) {
	if (stack->top == NULL) {
		return NULL;
	}
	return stack->top->data;
}


