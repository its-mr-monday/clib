#ifndef STACK_H
#define STACK_H
#pragma once
//The stack defined here is a dynamic stack
//You may push any void* into the stack and pop it out
//The stack can grow and shrink as needed
//We are not limited to standard C size constraints and will dynamically allocate memory as needed in a safe manner
//We are essentially making a linked list but with a reverse order
typedef struct StackNode {
	void* data;
	struct StackNode* previous;
} StackNode;

typedef struct Stack {
	StackNode* top;
	int size;
} Stack;

Stack* malloc_stack(); //Allocates memory for a stack
void free_stack(Stack* stack); //Frees the stack and the data inside
void free_stackA(Stack* stack, void(*freeData)(void*)); //Frees the stack and the data inside with a custom handler free function
void stack_push(Stack* stack, void* data); //Pushes the data onto the stack
void* stack_pop(Stack* stack); //Returns the top of the stack and removes it
void* stack_peek(Stack* stack); //Returns the top of the stack without removing it
#endif
