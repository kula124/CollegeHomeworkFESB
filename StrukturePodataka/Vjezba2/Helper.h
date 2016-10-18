#pragma warning(disable:4996)

#ifndef HELPER_H
#define HELPER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Error Codes
#define ERROR_OPENING_FILE -404
#define ERROR_WRITTING_TO_FILE -403
#define ERROR_ELEMENT_NOT_FOUND -100
#define ERROR_READING_FILE -400
#define ERROR_NULL_ROOT -1
#define ERROR_EMPTY_LIST -2
#define ERROR_ALLOCATING_MEMORY -101
#define ERROR_UNESPECTED_NULL_PARAMETER -3
#define OK 0
#define TRUE 1
//Constants
#define NAME_LENGHT 50
//STRUCT
typedef struct _osoba
{
	char* name;
	char* lname;
	int born;
	_osoba* next;
} *optr;

//Methods delcaration
int AddToBegining(optr root, char* name, char* lname, int god);
int AddToEnd(optr root, char* name, char* lname, int god);
int ShowList(optr root);
int Delete(optr root, optr elemnt);
int FindElements(optr root,optr** found ,char* lastName, bool FindAll);
char* Catch(int ErrorCode, int* shouldExit);
//int WriteToFIle(optr root, char* filepath, int append, optr* AdditionalPersons);
//int ReadFile(optr root, char* path, optr seperateList);
#endif
