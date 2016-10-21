
#pragma warning(disable:4996) 

#ifndef HELPER_CPP
#define HELPER_CPP
//
//ERROR CODES
//
#define FILE_ERROR -404
#define FILE_READ_ERROR -400
#define MEMORY_ALLOC_ERROR -100
#define UNESPECTED_ERROR -1
//
//CONSTANTS
//
#define FILE_PATH_SIZE 50
#define MAP_SIZE 20
#define NAME_SIZE 50
#define LNAME_SIZE 50
#define NUMBER_SIZE 9
#define READ_BUFFER_SIZE 112 //name+lname+number+2 (2 spaces + 1 security)

//
//STRUCTS
//
typedef struct
{
	char* name;
	char* lname;
	float points;
	//int isMax;
} student, *stdp;


//
//FUNCTIONS
//
void ReleseMemoryStd(stdp* arr, int count);
void ReleseData(char** arr, int count);
void ReadData(stdp*, int, float);
char** GetSubstrings(char* string, char termChar);
//void Throw(int ErrorCode);
int GetRowCount(FILE* fp);
stdp* GetArray(FILE* fp, int count, float* max);


#endif
