#ifndef HELPER_H
#define HELPER_H
#pragma warning(disable:4996)
//FATAL ERRORS----------> Result in program termination
#define ERROR_ALLOCATING_MEMORY -100
#define ERROR_UNESPECTED_NULL_PARAMETER -99
//SIMPLE ERRORS --------> Invalid request, program continues
#define ERROR_OPENING_FILE 404
#define ERROR_EMPTY_LIST 500
#define ERROR_ELEMENT_NOT_FOUND 501
#define ERROR_TOO_FEW_ELEMENTS  502
#define UNDER_CONSTRUCTION 505
//CONSTANTS
#define OK 0
#define FALSE -1
#define TRUE 1
#define SLEEP_TIME 2500
#define READY 0 //is sort function ready?
//sizes
#define NAME_LENGHT 50
#define FILE_PATH_LENGHT 100
#define READ_BUFFER_LENGHT 2 * NAME_LENGHT + 2 + 4 //2 razmaka, 4 znamenke
//Main struct declaration
typedef struct _osoba
{
	char *name;
	char *lname;
	int born;
	_osoba* next;
} osoba_S, *osoba;

//Functions declarations
osoba CreateNode(int args, ...);
int InsertNode(osoba root, osoba node);
osoba Find(osoba root);
osoba FindPrevTo(osoba root, osoba node);
int DeleteNode(osoba root, osoba node);
int ClearList(osoba root);
int WrtiteToFile(osoba startNode);
int FreeNode(osoba target);
int ReadFromFile(osoba root);
int ReadList(osoba root);
int ReadNode(osoba element);
int Catch(int ErrorCode);
int Sort();
void Jump();
void ReadASCIIart();
#endif // !HELPER_H
