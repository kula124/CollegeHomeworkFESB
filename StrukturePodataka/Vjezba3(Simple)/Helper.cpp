#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "Helper.h"
#include <stdarg.h>
#include <ctype.h>
#include <Windows.h>
//variatic funtion, had to try :3
osoba CreateNode(int args, ...)
{
	if (args == -1) //Create root :O :O :O *\* MAGICS */*
	{
		srand(GetTickCount());
		osoba p = (osoba)malloc(sizeof(osoba_S));
		if (!p)
			exit(ERROR_ALLOCATING_MEMORY);
		p->lname = NULL;
		p->name = NULL;
		p->born = -1;
		p->next = NULL;
		return p;
	}
	if (args == 0)
	{
		char tempName[NAME_LENGHT], tempLname[NAME_LENGHT];
		int tempBorn = 0;
		osoba p = (osoba)malloc(sizeof(osoba_S));
		if (!p)
			return NULL;
		printf("Unesite ime osobe: ");
		scanf(" %s", &tempName);
		printf("Unesite prezime osobe: ");
		scanf(" %s", &tempLname);
		printf("Unesite godiste osobe: ");
		scanf(" %d", &p->born);
		p->name = (char*)malloc((strlen(tempName) + 2) * sizeof(char));
		p->lname = (char*)malloc((strlen(tempName) + 2) * sizeof(char));
		strcpy(p->name, tempName);
		strcpy(p->lname, tempLname);
		p->next = NULL;
		return p;
	}
	if (args != 3)
	{
		printf("Bad argument number\n");
		return NULL;
	}
	osoba p = (osoba)malloc(sizeof(osoba_S));
	int i = 0;
	va_list ap;
	va_start(ap, args);
	char* temp = va_arg(ap, char*);
	if (temp && strlen(temp) > 2)
	{
		p->name = (char*)malloc(sizeof(char) * strlen(temp) + 2);
		strcpy(p->name, temp);
	}
	else
	{
		printf("var function broken1\n");
		return NULL;
	}
	temp = va_arg(ap, char*);
	if (temp && strlen(temp) > 2)
	{
		p->lname = (char*)malloc(sizeof(char) * strlen(temp) + 2);
		strcpy(p->lname, temp);
	}
	else
	{
		printf("var function broken2\n");
		return NULL;
	}
	p->born = va_arg(ap, int);
	p->next = NULL;
	return p;
}
//yes, I'm THAT good
int InsertNode(osoba root, osoba target)
{
	osoba p = root;
	if (!root) //root == NULL means bad call to function, terminate
	{
		return ERROR_UNESPECTED_NULL_PARAMETER;
	}
	if (!target) //if target node is NULL node will be insterted at the end of the list
	{
		while (p->next) //get to the end
		{
			p = p->next;
		}
		p->next = CreateNode(0); //instert
		if (!p->next)
			return ERROR_ALLOCATING_MEMORY;
		return OK;
	}
	osoba n, temp = target->next;
	n = CreateNode(0);
	if (!n)
		return ERROR_ALLOCATING_MEMORY;
	target->next = n;
	n->next = temp;
	return OK;
}

osoba Find(osoba root)
{
	if (!root->next)
		return NULL;
	char n[NAME_LENGHT], l[NAME_LENGHT];
	int b;
	//Unos
	printf("Trazeo ime osobe: ");
	scanf(" %s", &n);
	printf("Trazeno prezime osobe: ");
	scanf(" %s", &l);
	printf("Trazeno godiste osobe: ");
	scanf(" %d", &b);
	puts("\n");
	//--//
	///Ako ne zelite trazit po nekom parametru ostavite ga praznim i bit ce preskocen
	///Za godine tada unesite 0. Provjera se vrsi preko BOOL zastavica(flags, f)
	osoba p = root->next;
	int evaN = TRUE, evaL = TRUE, evaG = TRUE; //flags for evaluation
	if (!n || strlen(n) < 2) //ime je prazno
		evaN = FALSE; //ne provjeravaj
	if (!l || strlen(l) < 2) //prezime je prazno, 
		evaL = FALSE; //ne provjeravaj
	if (b <= 0) //god je 0 itd
		evaG = FALSE;
	if (!evaN && !evaL && !evaG) //ako su svi null nema se sta provjerit, duuuuh
		return NULL;
	while (p)
	{
		int sn = FALSE, sl = FALSE, sg = FALSE; //same name, lname, god flags
		if (evaN && strcmp(p->name, n) == 0)
			sn = TRUE;
		if (evaL && strcmp(p->lname, l) == 0)
			sl = TRUE;
		if (evaG && p->born == b)
			sg = TRUE;
		if ((evaN == sn) && (evaL == sl) && (evaG == sg)) //Smart ha? ^ ^
			return p; //Thank you short-circuting
		p = p->next;
	}
	return NULL;
}

osoba FindPrevTo(osoba root, osoba target)
{
	if (!root->next || !target)
		return NULL;
	osoba p = root;
	while (p->next)
	{
		if (p->next == target)
			return p;
		p = p->next;
	}
	return NULL;
}

int DeleteNode(osoba root, osoba node)
{
	if (!root->next)
		return ERROR_EMPTY_LIST;
	if (!node)
		return ERROR_ELEMENT_NOT_FOUND;
	osoba prev = FindPrevTo(root, node);
	if (!prev)
		return ERROR_UNESPECTED_NULL_PARAMETER; //shouldn't happen
	prev->next = node->next;
	//ili
	//prev->next = prev->next->next;
	//
	FreeNode(node);
	return OK;
}

int ClearList(osoba root)
{
	if (!root->next)
		return ERROR_EMPTY_LIST;
	osoba prev, p = root->next;
	while (p)
	{
		prev = p;
		p = p->next;
		FreeNode(prev);
	}
	root->next = NULL;
	return OK;
}

int WrtiteToFile(osoba startNode)
{
	FILE* file_;
	if (!startNode)
		return ERROR_EMPTY_LIST;
	else if (startNode && !startNode->next)
	{
		if (!startNode->name || strlen(startNode->name) < 2) //check if root
			return ERROR_EMPTY_LIST;
	}
	char path[FILE_PATH_LENGHT];
	printf("\nUnesite filepath: ");
	scanf(" %s", &path);
	char c = 'c';
	while (c != 'n' && c != 'y') 
	{
		printf("\nAppend to file? [y/n]: ");
		scanf(" %c", &c);
		c = tolower(c); //Convert to lower, Y->y, N->n
	}
	if (c == 'y')
		file_ = fopen(path, "a");
	else
		file_ = fopen(path, "w");
	if (!file_)
		return ERROR_OPENING_FILE;
	if (c != 'y')
		fprintf(file_, "#Ime\tPrezime\t\tGod\n");
//	else
	//	fputc('\n', file_);
	while (startNode)
	{
		fprintf(file_, "%s\t%s\t\t%d\n", startNode->name, startNode->lname, startNode->born);
		startNode = startNode->next;
	}
	fclose(file_);
	return OK;
}

int FreeNode(osoba target)
{
	if (!target)
		return ERROR_UNESPECTED_NULL_PARAMETER;
	free(target->lname);
	free(target->name);
	free(target);
	return OK;
}

int ReadFromFile(osoba root)
{
	osoba p = root;
	fpos_t pos;
	char path[FILE_PATH_LENGHT];
	printf("\nUnesite filepath: ");
	scanf(" %s", &path);
	FILE* file_ = fopen(path, "r");
	if (!file_)
		return ERROR_OPENING_FILE;
	char c = 'c';
	while (c != 'n' && c != 'y')
	{
		printf("\nAppend to list? [y/n]: ");
		scanf(" %c", &c);
		c = tolower(c); //Convert to lower, Y->y, N->n
	}
	if (c == 'y')
		while (p->next)
			p = p->next;
	else
		ClearList(root);
	//read file
	char buffer[2 * NAME_LENGHT + 6];
	while (!feof(file_))
	{
		char tn[NAME_LENGHT], tl[NAME_LENGHT];
		int born;
		fgetpos(file_, &pos);
		fgets(buffer, 2 * NAME_LENGHT + 6, file_);
		if (buffer[0] == '#' || strlen(buffer) < 12)
			continue;
		fsetpos(file_, &pos);
		fscanf(file_, " %s%s%d", &tn, &tl, &born);
		osoba n = CreateNode(3,tn, tl, born);
		if (!n)
		{
			fclose(file_);
			return ERROR_ALLOCATING_MEMORY;
		}
		p->next = n;
		p = n;
	}
	fclose(file_);
	return OK;
}

int ReadList(osoba root)
{
	if (!root->next)
		return ERROR_EMPTY_LIST;
	osoba p = root->next;
	int i = 1;
	printf("n|Ime\t\tPrezime\t\tGod\n");
	while (p)
	{
		printf("[%d] ", i++);
		ReadNode(p);
		p = p->next;
	}
	getchar();
	puts("\nPress ENTER to continue...");
	getchar();
	return OK;
}

int ReadNode(osoba element)
{
	if (!element)
		return ERROR_UNESPECTED_NULL_PARAMETER;
	printf("%s\t%s\t\t%d\n", element->name, element->lname, element->born);
	return OK;
}

int Catch(int ErrorCode)
{
	switch (ErrorCode)
	{
	case ERROR_ALLOCATING_MEMORY:
		printf("FATAL ERROR: Error allocationg memory. Program will now exit...\n");
		_sleep(SLEEP_TIME);
		break;
	case ERROR_ELEMENT_NOT_FOUND :
		printf("Error: Element not found!\n");
		_sleep(SLEEP_TIME);
		break;
	case ERROR_EMPTY_LIST:
		printf("Error: Empty list\n");
		_sleep(SLEEP_TIME);
		break;
	case ERROR_OPENING_FILE:
		printf("Error: Can't open file. Is filepath right?\n");
		_sleep(SLEEP_TIME);
		break;
	case ERROR_UNESPECTED_NULL_PARAMETER:
		printf("FATAL ERROR: Unsepected NULL paramater passed to function! Program will now exit...\n");
		_sleep(SLEEP_TIME);
		break;
	case ERROR_TOO_FEW_ELEMENTS:
		printf("Error: Too few elements to sort list (2 min)!\n");
		_sleep(1200);
		break;
	case UNDER_CONSTRUCTION:
	//	system("cls");
		printf("UNDER CONSTRUCTION!\nComing soon...\nYou get hugz instead:\n");
		_sleep(2000);
		printf("\nLaunching hugz"); 
		printf(".");
		_sleep(800);
		printf(".");
		_sleep(800);
		printf(".");
		_sleep(800);
		printf(".");
		_sleep(800);
		printf(".");
		_sleep(800);
		printf("\nHugz! \\^_^/"); 
		_sleep(SLEEP_TIME);
		break;
	case OK:
		printf("[OK]");
		_sleep(SLEEP_TIME);
		break;
	default:
		printf("Bad error code: %d", ErrorCode);
		_sleep(SLEEP_TIME);
		break;
	}
	return ErrorCode;
}

int Sort()
{
	if(!READY)
	{
		ReadASCIIart();
		return UNDER_CONSTRUCTION;
	}

}

void Jump()
{
	printf("\n\n\n\n\n\n\n");
}

void ReadASCIIart()
{
	///-----
	///windows.h libary calls (WINAPI)
	///----
#pragma region Statics
	static BOOL changed = FALSE;
	const char* path = "asciiArt.txt";
	const LPCWSTR WSTR_path = L"asciiArt.txt";
	static fpos_t * artz = NULL;
	static FILETIME s_LastAccessed;
	static int count = 0;
	HANDLE file_hd = CreateFile(WSTR_path, GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL); //Open file
#pragma endregion
	//Makes sure that file is scaned only if changed from last run
	FILETIME accessed;
	if (file_hd < 0)
		return;
	GetFileTime(file_hd, NULL, NULL, &accessed); //Read last modified
	if (accessed.dwHighDateTime != s_LastAccessed.dwHighDateTime) //Compare timestamps
	{
		changed = TRUE;
		s_LastAccessed = accessed;
	}
	else
		changed = FALSE;
	CloseHandle(file_hd); //Close Windows File Handle
	FILE* file_ = fopen(path, "r"); //Open "normal" file handle
	if (!file_) {
		puts("No ascii art for you >_>\nBring me my asciiArt.txt back >_<\n");
		return;
	}
	//get number of entries:
	char buffer[255];
	if (changed == TRUE)
		while (fgets(buffer, 255, file_))
		{
			if (buffer[0] == '#' && buffer[1] == '#' && strlen(buffer)<5) {
				fgetc(file_);
				artz = (fpos_t*)realloc(artz, sizeof(fpos_t) * ++count);
				if (!artz)
					return;
				fgetpos(file_, &artz[count - 1]);
			}
		}
	count--;
	if (count== 0)
	{
		puts("Count 0");
		return;
	}
	int pick = rand() % count;
	fsetpos(file_, &artz[pick]);
//	Print out!
	while (!feof(file_))
	{
		fgets(buffer, 255, file_);
		if (buffer[0] == '#' && buffer[1] == '#')
			break;
		_sleep(500);
		printf(buffer);
	}
	count++;
	fclose(file_);
}



