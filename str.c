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

char* str_to_cstr(String* str) {
	if (str->list == NULL) {
		return NULL;
	}
	char * cstr = malloc(str->list->size + 1);
	Node * node = str->list->head;
	int i = 0;
	while (node != NULL) {
		cstr[i] = *((char*)node->data);
		node = node->next;
		i++;
	}
	cstr[i] = '\0';
	return cstr;
}

