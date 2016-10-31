#ifndef HELPER_H
#define HELPER_H
#pragma warning(disable:4996)
//ERROR CODES------
//FATAL ERRORS -->Terminate program
#define ERROR_ALLOCATING_MEMORY -100
#define ERROR_UNESPECTED_NULL_PARAMETER -101
//WARNINGS -->Program continues to run
#define ERROR_OPENING_FILE 504
#define ERROR_EMPTY_LIST 500
#define ERROR_ELEMENT_NOT_FOUND 404 //html analogy :^)
#define ERROR_UNDER_CONSTRUCTION 999
#define ERROR_TOO_FEW_ELEMENTS 502
#define ERROR_BAD_INPUT 509
//Constants
#define TRUE 1
#define FALSE -1
#define OK 0
#define IS_READY -2
#define SLEEP_TIME 2500
//Sizes
#define NAME_SIZE 50
#define READ_BUFFER_SIZE 2*NAME_SIZE + 2 + 1 + 4 //2 + 1\n names, 2 spaces, 4 digits //fgets takes '\n'
#define MAX_BUFFER_SIZE 255
//Modes for certan functions
//CreateNode()
#define CR8_ROOT -1
#define CR8_NEW 0
#define CR8_GIVEN 1
//Main structure
typedef struct OSOBA osoba_, *osoba;
struct OSOBA
{
	char* name;
	char* lname;
	int born;
	osoba next;
};
///------------------------------------------
///FUNCTIONS///------------------------------
///------------------------------------------
//List functions
osoba CreateNode(int MODE, ...);
int InsertNode(osoba root, osoba target); //Insert Always insters behind node
osoba Find(osoba root);
osoba FindPrevTo(osoba root, osoba target);
int PrintNode(osoba node);
int PrintList(osoba List);
int Sort();
//HelperFunctions

int ReadFile(osoba root);
int WriteToFile(osoba root);
int Clear(osoba root);
int DeleteNode(osoba root, osoba target);
int FreeNode(osoba node);
int CatchError(int error);
int ReadAscii();
#endif