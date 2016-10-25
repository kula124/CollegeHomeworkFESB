#pragma warning(disable:4996)
/// <summary>
/// Kopiran i nadopunjen header iz prijasnje vjezbe
/// Promjenjena implementacija funkcija
/// </summary>
#ifndef HELPER_H
#define HELPER_H
//Error Codes
#define ERROR_TOO_FEW_ELEMENTS 10
#define ERROR_OPENING_FILE -404
#define ERROR_WRITTING_TO_FILE -403
#define ERROR_ELEMENT_NOT_FOUND 100
#define ERROR_READING_FILE -400
#define ERROR_NULL_ROOT -999
#define FALSE -1
#define ERROR_EMPTY_LIST 200
#define ERROR_ALLOCATING_MEMORY -101
#define ERROR_UNESPECTED_NULL_PARAMETER -3
#define OK 2
//
#define UNDER_CONSTRUCTION 1000
//Constants
#define NAME_LENGHT 50
#define TRUE 1
#define NAME 1
#define LNAME 2
#define BORN 3
#define METHOD_QSRT 20
#define METHOD_BUBBLE 21
#define ASCENDING 117
//#define DESCENDING 115
//STRUCT
typedef struct _osoba
{
	char* name;
	char* lname;
	int born;
	_osoba* next;
} *osoba;
#endif
//Methods delcaration
char * Catch(int ErrorCode, int* ShuldExit);
int Insert(osoba root, osoba element);
osoba Find(osoba root, char*n, char*l, int g);
osoba FindPrev(osoba root, osoba element);
int Swap(osoba A, osoba B, osoba prevA);
osoba CreateElement(char* n, char*l, int b);
int Delete(osoba root, osoba element);
int ClearList(osoba root);
int ReadFilev2(osoba root, char* path, int append);
int WriteFile(osoba start, char* path, int appendToFile);
int FreeEl(osoba elemnet);
int CompareElement(osoba A, osoba B, int compareBy);
int CompareBorn(const void* A, const void* B);
int Sort(osoba root, int sortBy, int method, double* time, char order);
osoba ListToArray(osoba root, int* count);
osoba ArrayToList(osoba root, osoba arr, int count);
int GetNumberOfElements(osoba root);
void ShowElement(osoba ele);
int ShowList(osoba root);