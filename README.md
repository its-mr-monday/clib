# CLIB

This is a collection of C files and Header files that extend your already amazing C library
GLIBC is great right? So is your systems native library, but what about these nice abstractions we got used to when learning?

Strings?
Linkedlists?
Stacks?
Binary Trees?

Well I've come along and designed a portable method of utilizing these data structures, the libraries do not rely on anything but glibc

So now you can create a String with ease and allow it to grow and shrink at your will

## String Example
```c
#include "str.h"

void example() {
	//Simple Hello world with the str.h header
	//You may use either malloc_strin_cstr or str_create to reserve memory with a predefined series of characters
	String* myString = malloc_string_cstr("Hello World!");	//Allocate memory for our string and presign it the value of Hello World!
	printf(str_to_cstr(myString)); //Results in: Hello World!
	//Let's add another string to it
	String* myOtherString = malloc_string(); //Allocate memory for a empty string
	str_append(myOtherString, '\n'); //Lets add a newline character
	str_append_str(myString, myOtherString); //Add myOtherString to the end of myString
	printf(str_to_cstr(myString)); //Now results in: Hello World!\n
	//Now lets make sure we free our memory, no garbage collector here!
	free_str(myOtherString);
	free_str(myString);
}
```

## List Example
```c
#include "list.h"

//Print handler function since type casting is involved
void printInt(void * value) {
	int * valueInt = (int *)value;
	printf("%d", *valueInt);
}

void example() {
	List* myList = malloc_list();
	//Let's append some numbers (remember they have to be pointers)
	int *num;
	for (int i = 0;i < 5;i++) {
		num = (int *)malloc(sizeof(int));
		*num = i;
		list_append(myList, (void*)num);
	}
	int listSize = list->size;
	//Lets print the list
	printList(list, &printInt);
	//Now lets free our memory
	freeList(list);
}

```
