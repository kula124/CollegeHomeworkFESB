#pragma once
/**
* \Check for OS
*/
#define U_FLAG 0
#ifdef _WIN32
#define COLOR_RED "color 04"
#define COLOR_YLW "color 06"
#define COLOR_GRN "color 02"
#define COLOR_RST "color 07"
#define CLEAR_SCREEN() system("cls")
#endif
#ifdef _linux_
#define CLEAR_SCREEN() system("clear")
#define U_FLAG 1
#endif
#pragma warning(disable:4996)
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
///Constants
#define STATUS_OK 10
#define STATUS_READY 11
#define OPTION_CANCEL 1
#define OPTION_ERASE 2
#define OPTION_APPEND 3
#define P_SIZE 50
#define ABORTED -7
int SortedReadFile(char* path, list l);
int Union(list l1, list l2, list l3);
int JoinSection(list l1, list l2, list l3);
int WriteOut(list li);
int SortedInput(list li);
//int IsEmpty(list li);
int DeleteList(list *li);
int InsertBehind(element el, int value);
//int Compare(int a, int b, int flag);
int ManageList(list l);
element CreateElement(int temp);
//int Signum(int value);
void Catch(int error);
void CheckFlag(int f);
void CheckFlagUNIX(int f);
int InputPicker(list l);
//#endif
