#pragma once
//#ifdef HALP_H
#define HALP_H
#pragma warning(disable:4996)
typedef struct _element
{
	int value;
	_element* next;
}_element, *element, *list;

///Error codes
#define ERROR_OPENING_FILE 404
#define ERROR_LIST_NOT_EMPTY 400
#define ERROR_MALLOC_FAILED -2;
#define ERROR_READING_FILE -4
#define ERROR_NULL_NOT_EXPECTED -10
#define ERROR_EMPTY_LIST 500
#define OK 0
///Constants
#define OPTION_CANCEL 1
#define OPTION_ERASE 2
#define OPTION_APPEND 3
int SortedReadFile(char* path, list* l);
int Union(list l1, list l2, list l3);
int JoinSection(list l1, list l2, list* l3);
int WriteOut(list li);
int SortedInput(list* li);
int IsEmpty(list li);
int DeleteList(list* li);
int InsertBehind(element* el, int value);
int Compare(int a, int b, int flag);
int ManageList();
element CreateElement(int temp);
int Signum(int value);
//#endif