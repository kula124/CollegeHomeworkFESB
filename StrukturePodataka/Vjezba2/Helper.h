#pragma warning(disable:4996)

#ifndef HELPER_H
#define HELPER_H
//Error Codes
#define ERROR_OPENING_FILE -404
#define ERROR_WRITTING_TO_FILE -403
#define ERROR_ELEMENT_NOT_FOUND 100
#define ERROR_READING_FILE -400
#define ERROR_NULL_ROOT -1
#define ERROR_EMPTY_LIST 200
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
optr CreateElement(char* n, char* l, int god);
int AddToBegining(optr root, char* name, char* lname, int god);
int AddToEnd(optr root, char* name, char* lname, int god);
int ShowList(optr root);
int ShowElement(optr element);
int Delete(optr root, optr elemnt);
int FindElements(optr root,optr** found ,char* lastName, int * FindAll);
char* Catch(int ErrorCode, int* shouldExit);
int WriteToFIle(optr root, char* filepath);
int ReadFile(optr root, char* path, int append);
int ClearList(optr root);
int FreeE(optr el);
char** GetSubstrings(char* string, char termChar);
#endif
