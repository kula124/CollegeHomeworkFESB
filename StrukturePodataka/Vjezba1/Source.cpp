#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "helper.h"

int main()
{
	int option=-1;
	//flags
	int frun = 1; //Used to loop
	int fread = 0;//Is file read?
	int fpath = 0;//Is filepath entered?
	//
	int count;
	char filepath[FILE_PATH_SIZE];
	FILE* file_ = NULL;
	stdp* studenti_ = NULL;
	float max;
	while (frun)
	{
		printf("Vjezba 1\nChoose option:\n[1]Enter filepath\n[2]Read File\n[3]Show results\n[0]Exit\nChoise: ");
		scanf("  %d",&option);
		switch (option)
		{
		case 1 :
			printf("Please enter the filepath (''C:\\exampleUser\\example.txt''): ");
			scanf(" %s",&filepath);
			file_=fopen(filepath,"r");
			if (!file_)
			{
				puts("\nError opening file");
				break;
			}
			puts("[OK]\n");
			fpath = 1;
			fread = 0;
			break;
		case 2:
			if (!fpath)
			{
				puts("\nPath not entered. Choose option 1 first");
				break;
			}
			count = GetRowCount(file_);
			if (count<0)
				switch (count)
			{
				case FILE_ERROR:
					printf("Error handling the file");
					return FILE_ERROR;
					break;
				case FILE_READ_ERROR:
					printf("Error reading the file");
					return FILE_READ_ERROR;
					break;
					{
				default:
					break;
					}
			}
			studenti_ = GetArray(file_,count,&max);
			if (!studenti_)
			{
				printf("Error allocating memory");
				return MEMORY_ALLOC_ERROR;
			}
			puts("[OK]");
			fclose(file_);
			file_=NULL;
			puts("File closed\n");
			fread = 1;
			fpath = 0;
			break;
		case 3:
			if (!fread)
			{
				puts("\nFile not read yet. Use option 2 first");
				break;
			}
			ReadData(studenti_, count,max);
			break;
		case 0:
			frun = 0;
			puts("\nClearing up memory....");
			ReleseMemoryStd(studenti_,count);
			puts("\nByeee\n");
			break;
		default:
			puts("\nInvalid choise\n");
			break;
		}
	}
	return 0;
}