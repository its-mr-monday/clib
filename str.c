#include "str.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

String * malloc_str() {
	List * list = malloc_list();
	String * str = malloc(sizeof(String));
	str->list = list;
	return str;
}

String* malloc_str_cstr(const char* cstr) {
	String * str = malloc_str();
	str_append_cstr(str, cstr);
	return str;
}

String* str_create(const char* cstr) {
	return malloc_str_cstr(cstr);
}

void free_str(String * str) {
	freeList(str->list);
	free(str);
}

int str_length(String* str) {
	if (str == NULL || str->list == NULL) {
		return 0;
	}
	return str->list->size;
}

void str_append(String* str, char c) {
	char * ch = malloc(sizeof(char));
	*ch = c;
	if (str->list == NULL) {
		str->list = malloc_list();
	}
	list_append(str->list, ch);
	return;
}

void str_append_str(String* str, String* str2) {
	if (str->list == NULL) {
		if (str2->list != NULL) {
			str->list = str2->list;
			return;
		}
		str->list = malloc_list();
	}
	if (str2->list == NULL) {
		return;
	}
	list_append_list(str->list, str2->list);
	return;
}

void str_append_cstr(String* str, const char* cstr) {
	if (str->list == NULL) {
		str->list = malloc_list();
	}
	int i = 0;
	while (cstr[i] != '\0') {
		char * ch = malloc(sizeof(char));
		*ch = cstr[i];
		list_append(str->list, (void*)ch);
		i++;
	}
	return;
}

void str_append_int(String* str, int i) {
	//Convert int to char[]
	//Then append char[] to str
	char * cstr = malloc(12);
	snprintf(cstr, 12, "%d", i);
	str_append_cstr(str, cstr);
	free(cstr);
}

void str_append_float(String* str, float f) {
	//Convert float to char[]
	//Then append char[] to str
	char * cstr = malloc(12);
	snprintf(cstr, 12, "%f", f);
	str_append_cstr(str, cstr);
	free(cstr);
}

void str_append_double(String* str, double d) {
	//Convert double to char[]
	//Then append char[] to str
	char * cstr = malloc(12);
	snprintf(cstr, 12, "%f", d);
	str_append_cstr(str, cstr);
	free(cstr);
}

void str_remove(String *str, int index) {
	if (str->list == NULL) {
		return;
	}
	void* data = list_remove(str->list, index);
	free(data);
}

void str_slice(String *str, int start, int end) {
	if (str->list == NULL) {
		return;
	}
	list_slice(str->list, start, end);
}

void str_clear(String *str) {
	//Simplest way is to freeList then malloc new one
	freeList(str->list);
	str->list = malloc_list();
}

char str_at(String* str, int index) {
	if (str->list == NULL) {
		return '\0';
	}
	char * ch = (char*)list_get(str->list, index);
	return *ch;
}

void str_set(String* str, int index, char c) {
	char * ch = malloc(sizeof(char));
	*ch = c;
	if (str->list == NULL) {
		str->list = malloc_list();
		list_append(str->list, (void*)ch);
		return;
	}
	list_set(str->list, (void*)ch, index);
}

void str_insert(String* str, int index, char c) {
	char * ch = malloc(sizeof(char));
	*ch = c;
	if (str->list == NULL) {
		str->list = malloc_list();
	}
	list_insert(str->list, (void*)ch, index);
	return;
}

void str_insert_str(String* str, int index, String* str2) {
	if (str->list == NULL) {
		if (str2->list != NULL) {
			str->list = str2->list;
			return;
		}
		str->list = malloc_list();
	}
	if (str2->list == NULL) {
		return;
	}
	list_insert_list(str->list, str2->list, index);
	return;
}

void str_insert_cstr(String* str, int index, const char* cstr) {
	if (str->list == NULL) {
		str->list = malloc_list();
	}
	int i = 0;
	while (cstr[i] != '\0') {
		char * ch = malloc(sizeof(char));
		*ch = cstr[i];
		list_insert(str->list, (void*)ch, index + i);
		i++;
	}
	return;
}

int str_index_of(String* str, char c) {
	if (str->list == NULL) {
		str->list = malloc_list(); //ensure we have something to work with
		return -1;
	}
	Node * node = str->list->head;
	int i = 0;
	while (node != NULL) {
		char * ch = (char*)node->data;
		if (*ch == c) {
			return i;
		}
		node = node->next;
		i++;
	}
	return -1;
}

int str_index_of_str(String* str, String* str2) {
	//This one is not so simple
	//We need to iterate through str and compare each character to str2
	//If we find a match, we need to check the next characters in str and str2
	//If we find a mismatch, we need to continue iterating through str
	
	if (str->list == NULL || str2->list == NULL) {
		return -1;
	}
	Node * node = str->list->head;
	Node * head2 = str2->list->head;
	int i = 0;
	while (node != NULL) {
		char * ch = (char*)node->data;
		if (*ch == *((char*)head2->data)) {
			Node * node2 = node;
			Node * head2 = str2->list->head;
			while (node2 != NULL && head2 != NULL) {
				char * ch2 = (char*)node2->data;
				char * ch3 = (char*)head2->data;
				if (*ch2 != *ch3) {
					break;
				}
				node2 = node2->next;
				head2 = head2->next;
			}
			if (head2 == NULL) {
				return i;
			}
		}
		node = node->next;
		i++;
	}
	return -1;
}

int str_index_of_cstr(String* str, const char* cstr) {
	//Easiest way to do this is convert cstr to a String and call str_index_of_str
	//Then free the String
	String * str2 = malloc_str_cstr(cstr);
	int index = str_index_of_str(str, str2);
	free_str(str2);
	return index;
}
char* str_to_cstr(String* str) {
	if (str->list == NULL) {
		return NULL;
	}
	char * cstr = malloc(str->list->size + 1);
	int i = 0;
	Node * node = str->list->head;
	while (node != NULL) {
		char * ch = (char*)node->data;
		cstr[i] = *ch;
		node = node->next;
		i++;
	}
	cstr[i] = '\0';
	return cstr;
}

