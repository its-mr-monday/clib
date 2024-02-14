#ifndef STR_H
#define STR_H
#pragma once
#include "list.h"

typedef struct {
	struct List* list;
} String;

String* malloc_str();
String* malloc_str_cstr(const char* cstr);
String* str_create(const char* cstr);
void free_str(String* str);
int str_length(String* str);
void str_append(String* str, char c);
void str_append_str(String* str, String* str2);
void str_append_cstr(String* str, const char* cstr);
void str_append_int(String* str, int i);
void str_append_float(String* str, float f);
void str_append_double(String* str, double d);
void str_remove(String* str, int index);
void str_slice(String* str, int start, int end);
void str_clear(String* str);
char str_at(String* str, int index);
void str_set(String* str, int index, char c);
void str_insert(String* str, int index, char c);
void str_insert_str(String* str, int index, String* str2);
void str_insert_cstr(String* str, int index, const char* cstr);
void str_insert_int(String* str, int index, int i);
int str_index_of(String* str, char c);
int str_index_of_str(String* str, String* str2);
int str_index_of_cstr(String* str, const char* cstr);
char* str_to_cstr(String* str);
#endif
