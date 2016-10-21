#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "helper.h"

int GetRowCount(FILE* fp)
{
	int count = 0;
	if (!fp)
	{
		return FILE_ERROR;
	}
	char buffer[READ_BUFFER_SIZE];
	while (fgets(buffer, READ_BUFFER_SIZE, fp))
	{
		if (buffer[0] == '#' || strlen(buffer) < 10) //junk line detection, #->comment ///TODO: Detect large junk lines
			continue;
		count++;
	}
	if (!feof(fp)) //Izlaz iz While a nije pogodjen EOF, znaci fgets() failed
		return FILE_READ_ERROR;
	return count;
}

stdp* GetArray(FILE* fp, int count, float* cmax)
{
	rewind(fp);
	stdp *sarray = NULL;
	sarray = (stdp*)malloc(sizeof(stdp)*count);
	if (!sarray)
		return NULL;
	int i = 0;
	*cmax = 0;
	char buffer[READ_BUFFER_SIZE];
	char** data = NULL;
	for (i = 0; i < count; i++)
	{
		fgets(buffer, READ_BUFFER_SIZE, fp);
		if (buffer[0] == '#' || strlen(buffer) < 10) //TODO: Better junk detection
		{
			i -= 1;
			continue;
		}
		//	fscanf(fp,"  %s  %s  %f  ",&nameb,&lnameb, &temp->points); --> too izi
		stdp temp = (stdp)malloc(sizeof(student));
		if (!temp)
			return NULL;
		data = GetSubstrings(buffer, ' ');
		if (!data)
			return NULL;
		temp->name = (char*)malloc(sizeof(char)*strlen(data[0]) + 1);
		strcpy(temp->name, data[0]);
		temp->lname = (char*)malloc(sizeof(char)*strlen(data[1]) + 1);
		strcpy(temp->lname, data[1]);
		temp->points = atof(data[2]);
		if (*cmax < temp->points)
			*cmax = temp->points;
		sarray[i] = temp;
	}
	ReleseData(data, 3); //--> Bad heap access error? [SOLVED]
	return sarray;
}

char** GetSubstrings(char* string, char termChar)  // Improved from Vjezba2
{
	int lengt = strlen(string);
	if (lengt < 10)
		return NULL;
	int i, previ = 0, count = 0;
	for (i = 0; i < lengt; i++)
	{
		if (string[i] == termChar)
		{
			if (string[i - 1] == termChar)
				continue;
			count++;
			previ = i;
		}
	}
	count++;
	char** substrings = (char**)malloc(sizeof(char*)*count); //fixed +1 extra field allocation
	if (!substrings)
		return NULL;
	int tempCount = 0;
	previ = 0;
	for (i = 0; i <= lengt; i++) //fixed skipping over block due to for exit
	{
		if (string[i] == termChar || string[i] == '\0' || string[i] == '\n' || i == lengt || tempCount == count)
		{
			char* sub = (char*)malloc(sizeof(char)*(i - previ) + 1);
			if (!sub)
				return NULL;
			memcpy(sub, &string[previ], i - previ);
			sub[i - previ] = '\0'; //memset mozda?
			previ = i + 1;
			if (strlen(sub) <= 1)
			{
				free(sub);
				continue;
			}
			substrings[tempCount++] = sub; //not reversed anymore
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
	for (i = 0; i < c; i++)
	{
		printf("%s\t", studenti_[i]->name);
		printf("%s\t", studenti_[i]->lname);
		if (strlen(studenti_[i]->lname) < preL + 4)
			printf("\t"); //formatiranje, da ne preskace iz stupca ako je prezime dugacko, bio sam ljen da dodam to i za ime
		printf("%6.3f\t", studenti_[i]->points);
		printf("%6.3lf\t", ((((double)studenti_[i]->points / (max))) * 100));
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
	for (int i = 0; i < count; i++)
	{
		free(arr[i]->lname);
		free(arr[i]->name);
		free(arr[i]);
	}
}

void ReleseData(char** data, int count)
{
	for (int i = 0; i < count; i++)
		free(data[i]); //Ne dodavanje +1 u size u malloc-u je rusilo free kod poziva na char*. Znaci da '\0' se ne broji u strlen... Nisam to znao
					   //free(data) -> Error, data = data[0]?... duuuhh
}
//mozda se mogu spojiti ove dvije funkcije u jednu oblika:
//void ReleseMemory(void**p, int count, int isStdudent);
//pokusao ali odustao... heap overwrite errors n stuff

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