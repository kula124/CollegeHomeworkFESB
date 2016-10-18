#ifndef MAIN_LIBS
#define MAIN_LIBS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996) 
#endif

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
//GLOBALS
//
void ReleseMemoryStd(stdp* arr, int count);
void ReleseData(char** arr,int count);
void ReadData(stdp*, int, float);
char** GetSubstrings(char* string, char termChar);
//void Throw(int ErrorCode);
int GetRowCount(FILE* fp);
stdp* GetArray(FILE* fp, int count, float* max);

//
//FUNCTIONS
//

//void Throw(int ErrorCode)
//{
//	switch (ErrorCode)
//	{
//	case FILE_ERROR :
//		printf("\nError opening file. Is file path correct? Is file in use?");
//		break;
//	case FILE_READ_ERROR :
//		printf("\nError reading file");
//		break;
//	case MEMORY_ALLOC_ERROR:
//		printf("\nMemory allocation failed!");
//		break;
//	default:
//		printf("\nUnknown error has occured...");
//		break;
//	}
//	puts("\nClearing memory...");
//	puts("\nExiting.....");
//	//Clear up memory here
//	exit(ErrorCode);
//}
//
//---------------------
//
int GetRowCount(FILE* fp)
{
	int count = 0;
	if (!fp)
	{
		return FILE_ERROR;
	}
	char buffer[READ_BUFFER_SIZE];
	while(fgets(buffer,READ_BUFFER_SIZE,fp))
	{
		if (buffer[0]=='#' || strlen(buffer) < 10) //junk line detection, #->comment ///TODO: Detect large junk lines
			continue;
		count++;
	}
	if(!feof(fp)) //Izlaz iz While a nije pogodjen EOF, znaci fgets() failed
		return FILE_READ_ERROR;
	return count;
}
//
//---------------------
//
stdp* GetArray(FILE* fp, int count, float* cmax)
{
	rewind(fp);
	stdp *sarray = NULL;
	sarray = (stdp*) malloc (sizeof(student)*count);
	if (!sarray)
		return NULL;
	int i = 0;
	*cmax = 0;
	char buffer[READ_BUFFER_SIZE];
	char** data = NULL;
	for (i=0;i<count;i++)
	{
		fgets(buffer,READ_BUFFER_SIZE,fp);
		if (buffer[0] == '#' || strlen(buffer)<10) //TODO: Better junk detection
		{
			i -=1;
			continue;
		}
		//	fscanf(fp,"  %s  %s  %f  ",&nameb,&lnameb, &temp->points); --> too izi
		stdp temp = (stdp)malloc(sizeof(student));
		if (!temp)
			return NULL;
		data = GetSubstrings(buffer,' ');
		if (!data)
			return NULL;
		temp->name = (char*)malloc(sizeof(char)*strlen(data[2]) + 1);
		strcpy(temp->name,data[2]);
		temp->lname = (char*)malloc(sizeof(char)*strlen(data[1]) + 1);
		strcpy(temp->lname,data[1]);
		temp->points = atof(data[0]);
		if (*cmax < temp->points)
			*cmax = temp->points;
		sarray[i] = temp;
	}
	ReleseData(data, 3); //--> Bad heap access error? [SOLVED]
	return sarray;
}
char** GetSubstrings(char* string, char termChar)  // 
{
	int lengt = strlen(string);
	int i, previ =0, count=0;
	for (i=0;i<lengt;i++)
	{
		if (string[i] == termChar)
		{
			count++;
		}
	}
	char** substrings = (char**)malloc(sizeof(char*)*count + 1);
	if (!substrings)
		return NULL;
	for (i=0;i<lengt;i++)
	{
		if (string[i] == termChar || string[i] == '\0' || string[i] == '\n' || i==lengt-1)
		{
			char* sub = (char*)malloc(sizeof(char)*(i-previ) + 1);
			if (!sub)
				return NULL;
			memcpy(sub,&string[previ],i-previ);
			sub[i-previ] = '\0'; //memset mozda?
			previ=i+1;
			substrings[count--] = sub; //naopako ce ic: bod, prez, ime (2,1,0)
		}
	}
	return substrings; 
}
void ReadData(stdp* studenti_, int c, float max)
{
	int preL;
	preL = strlen("Prezime");
	printf("\nIme\tPrezime\t\tBodovi\tRel.Bodovi\n");
	int i;
	for (i=0;i<c;i++)
	{
		printf("%s\t",studenti_[i]->name);
		printf("%s\t",studenti_[i]->lname);
		if (strlen(studenti_[i]->lname) < preL+4)
			printf("\t"); //formatiranje, da ne preskace iz stupca ako je prezime dugacko, bio sam ljen da dodam to i za ime
		printf("%6.3f\t",studenti_[i]->points);
		printf("%6.3lf\t",((((double)studenti_[i]->points/(max)))*100));
		puts("\t");
	}
	puts("\n");
}

//-----------------------------------------------------------------//
//-----------------------------------------------------------------//
                      //CLEANER METHODS
//-----------------------------------------------------------------//
//-----------------------------------------------------------------//

void ReleseMemoryStd(stdp* arr, int count)
{
	for (int i=0;i<count;i++)
	{
		free(arr[i]->lname);
		free(arr[i]->name);
		free(arr[i]);
	}
}
void ReleseData(char** data, int count)
{
	for (int i=0;i<count;i++)
		free(data[i]); //Ne dodavanje +1 u size u malloc-u je rusilo free kod poziva na char*. Znaci da '\0' se ne broji u strlen... Nisam to znao
	//free(data) -> Error, data = data[0]?
}
//mozda se mogu spojiti ove dvije funkcije u jednu oblika:
//void ReleseMemory(void**p, int count, int isStdudent);
//pokusao ali odustao... heap overwrite errors n stuff
#endif
