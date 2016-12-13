#pragma once
typedef struct _element
{
	int value;
	_element* next;
}_element, *element, *list;

///Error codes
#define ERROR_OPENING_FILE 404
#define ERROR_LIST_NOT_EMPTY 400
#define ERROR_MALLOC_FAILED -2
#define ERROR_READING_FILE -4
#define ERROR_NULL_NOT_EXPECTED -10
#define ERROR_EMPTY_LIST 500
#define ERROR_BAD_INPUT 2
#define USER_EXIT -1
#define ERROR_LISTS_NOT_READY -5
#define OK 0

int Read(list l);
int PopS(list s, int* v);
int PopQ(list q, int* v);
int Push(list l, int v);
element CreateElement(int temp);