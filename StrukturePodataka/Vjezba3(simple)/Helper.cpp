#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <stdarg.h>
#include "Helper.h"
#include <windows.h>
/// <summary>
/// Creates new node.
/// </summary>
/// <param name="MODE"> -1 for root, 0 for new, 1 for given parameters</param>
/// <param name="">If mode is 1 params are char*name, char*lname, int born</param>
/// <returns>Pointer to node created. NULL on fail</returns>
osoba CreateNode(int MODE, ...)
{
	osoba n = NULL;
	if (MODE == CR8_ROOT)
	{
		n = (osoba)malloc(sizeof(osoba_));
		if (!n)
			return n;
		n->lname = NULL;
		n->name = NULL;
		n->next = NULL;
	}
	else if (MODE == CR8_NEW)
	{
		n = (osoba)malloc(sizeof(osoba_));
		if (!n)
			return n;
		char tname[NAME_SIZE], tlname[NAME_SIZE];
		printf("\nUnesite ime: ");
		scanf(" %s", &tname);
		printf("Unesite prezime: ");
		scanf(" %s", &tlname);
		printf("Unesite godinu rodjenja: ");
		scanf(" %d", &n->born);
		n->name = (char*)malloc(sizeof(char)*strlen(tname) + 2);
		n->lname = (char*)malloc(sizeof(char)*strlen(tlname) + 2);
		strcpy(n->name, tname);
		strcpy(n->lname, tlname);
		n->next = NULL;
	}
	else if (MODE == CR8_GIVEN)
	{
		va_list args;
		va_start(args, MODE);
		char* tname = va_arg(args, char*);
		char* tlname = va_arg(args, char*);
		int born = va_arg(args, int);
		n = (osoba)malloc(sizeof(osoba_));
		if (!n)
			return n;
		n->name = (char*)malloc(sizeof(char)*strlen(tname) + 2);
		n->lname = (char*)malloc(sizeof(char)*strlen(tlname) + 2);
		n->born = born;
		strcpy(n->name, tname);
		strcpy(n->lname, tlname);
		n->next = NULL;
	}
	else
		return NULL;
	return n;
	
}
/// <summary>
/// Inserts the node behind the target node
/// </summary>
/// <param name="root">The root.</param>
/// <param name="target">The target.</param>
/// <returns>Returns ERROR_CODE defined in Helper.h. 0 for success</returns>
int InsertNode(osoba root, osoba target)
{
	osoba p = root;
	if (!target)
	{
		while (p->next)
			p = p->next;
		p->next = CreateNode(CR8_NEW);
		return OK;
	}
	while (p && p != target)
		p = p->next;
	if (!p)
		return ERROR_ELEMENT_NOT_FOUND;
	osoba n = CreateNode(CR8_NEW);
	n->next = p->next;
	p->next = n;
	return OK;
}

osoba Find(osoba root)
{
	char n[NAME_SIZE], l[NAME_SIZE];
	int g=0;
	printf("\nUnesite trazeno ime: ");
	scanf(" %s", &n);
	printf("Unesite trazeno prezime: ");
	scanf(" %s", &l);
	printf("Unesite trazeno godiste: ");
	scanf(" %d", &g);
	if (!root || !root->next)
		return NULL;
	osoba p = root->next;
	int evaN = TRUE, evaL = TRUE, evaG = TRUE; //flags for evaluation
	if (!n || strlen(n) < 2)
		evaN = FALSE;
	if (!l || strlen(l) < 2)
		evaL = FALSE;
	if (g <= 0)
		evaG = FALSE;
	if (!evaN && !evaL && !evaG)
		return NULL;
	while (p)
	{
		int sn = FALSE, sl = FALSE, sg = FALSE; //same name, lname, god flags
		if (evaN && strcmp(p->name, n) == 0)
			sn = TRUE;
		if (evaL && strcmp(p->lname, l) == 0)
			sl = TRUE;
		if (evaG && p->born == g)
			sg = TRUE;
		if ((evaN == sn) && (evaL == sl) && (evaG == sg)) //Smart ha?
			return p; //Thank you short-circuting
		p = p->next;
	}
	return NULL;
}

osoba FindPrevTo(osoba root, osoba target)
{
	if (!target)
		return NULL;
	osoba p = root;
	if (!p || !p->next)
		return NULL;
	while (p && p->next != target)
		p = p->next;
	return p;
}

int PrintNode(osoba node)
{
	if (!node)
		return ERROR_UNESPECTED_NULL_PARAMETER;
	printf("%s\t%s\t\t%d\n", node->name, node->lname, node->born);
	return OK;
}

int PrintList(osoba root)
{
	osoba p = root->next;
	if (!p)
		return ERROR_EMPTY_LIST;
	printf("#|Ime\tPrezime\t\tGod\n");
	while (p)
	{
		PrintNode(p);
		p = p->next;
	}
	getchar();
	puts("\nPress ENTER to continue...");
	getchar();
	return OK;

}

int Sort()
{
	if (IS_READY < 0)
		return ReadAscii();
}

int ReadFile(osoba root)
{
	osoba p = root;
	char path[NAME_SIZE * 2];
	int append;

	printf("\nUnesite filepath: ");
	scanf(" %s", &path);
	printf("Nacin citanja:\n[%d]Dodaj na postojecu listu\n[%d]Izbrisi listu pa dodaj\nIzbor: ", TRUE, FALSE);
	scanf(" %d", &append);
	if (append != TRUE && append != FALSE)
		return ERROR_BAD_INPUT;
	if (append == FALSE)
		Clear(root);
	fpos_t pos;
	FILE* file_ = fopen(path, "r");
	if (!file_)
		return ERROR_OPENING_FILE;
	while (p->next)
		p = p->next;
	//read file
	char buffer[2 * NAME_SIZE + 6];
	while (!feof(file_))
	{
		char tn[NAME_SIZE], tl[NAME_SIZE];
		int born;
		fgetpos(file_, &pos);
		fgets(buffer, 2 * NAME_SIZE + 6, file_);
		if (buffer[0] == '#' || strlen(buffer) < 2)
			continue;
		fsetpos(file_, &pos);
		fscanf(file_, " %s %s %d", &tn, &tl, &born);
		osoba n = CreateNode(CR8_GIVEN, tn, tl, born);
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

int WriteToFile(osoba root)
{
	osoba p;
	int c = 0;
	printf("\nPocetni element:\n[%d]Pocetak liste(root)\n[%d]Nadji element\nIzor: ", TRUE, FALSE);
	scanf(" %d", &c);
	if (c == TRUE)
		p = root;
	else if (c == FALSE) {
		p = Find(root);
		if (!p)
			return ERROR_ELEMENT_NOT_FOUND;
	}
	else
		return ERROR_BAD_INPUT;
	FILE* file_ = NULL;
	if (!p)
		return ERROR_UNESPECTED_NULL_PARAMETER;
	if (p->lname == NULL || p->lname == NULL || p->born <= 0) //check for root
	{
		if (!p->next)
			return ERROR_EMPTY_LIST;
		p = p->next; //start
	}
	char path[NAME_SIZE * 2];
	int append = 0;
	printf("\nUnesite filepath: ");
	scanf(" %s", &path);
	printf("Nacin pisanja:\n[%d]Dodaj u postojeci file\n[%d]Ocisti file i dodaj\nIzbor: ", TRUE, FALSE);
	scanf(" %d", &append);
	if (append == TRUE)
		file_ = fopen(path, "a");
	else if (append == FALSE)
		file_ = fopen(path, "w");
	else
		return ERROR_BAD_INPUT;
	if (!file_)
		return ERROR_OPENING_FILE;
	fprintf(file_, "#Ime\tPrezime\t\tGod\n");
	while (p)
	{
		fprintf(file_, "%s\t%s\t\t%d\n", p->name, p->lname, p->born);
		p = p->next;
	}
	fclose(file_);
	return OK;
}

int DeleteNode(osoba root, osoba target)
{
	if (!target)
		return ERROR_ELEMENT_NOT_FOUND;
	osoba pr = FindPrevTo(root, target);
	if (!pr)
		return ERROR_UNESPECTED_NULL_PARAMETER;
	pr->next = target->next;
	FreeNode(target);
	return OK;
}

int FreeNode(osoba node)
{
	if (!node)
		return ERROR_UNESPECTED_NULL_PARAMETER;
	free(node->lname);
	free(node->name);
	free(node);
	return OK;
}

int CatchError(int error)
{
	switch (error)
	{
	case ERROR_BAD_INPUT:
		printf("Los unos, pokusajte ponovno\n");
		break;
	case ERROR_OPENING_FILE:
		 printf("Greska prilikom otvaranja datoteke. Jeste li unijeli tocan path?\n");
		 break;
	case ERROR_ELEMENT_NOT_FOUND:
		printf("Element niza nije pronadjen\n");
		break;
	case ERROR_EMPTY_LIST:
		printf("Lista je prazna\n");
	case ERROR_ALLOCATING_MEMORY:
		printf("Malloc failed... fek\n");
		break;
	case ERROR_UNESPECTED_NULL_PARAMETER:
		printf("NULL parametar neocekivan! Program ce sada izaci\n");
		break;
	case ERROR_UNDER_CONSTRUCTION:
		printf("UNDER CONSTRUCTION\nComming soon :^)\n");
		printf("You get hugz insted!\n");
		_sleep(1500);
		printf("Launching hugz");
		_sleep(800);
		printf(".");
		_sleep(800);
		printf(".");
		_sleep(800);
		printf(".");
		_sleep(800);
		printf(".");
		_sleep(800);
		printf("\nHUGZ \\^_^/");
		break;
	case ERROR_TOO_FEW_ELEMENTS:
		printf("Premalo elemenata za sortiranje\n");
		break;
	case OK:
		printf("[OK]\n");
		break;
	default:
		printf("Ayyy lmao....\n");
		break;
	}
	_sleep(SLEEP_TIME);
	return error;
}

int ReadAscii()
{
	static int count = 0;
	static fpos_t* positions = NULL;
	static FILETIME lastRan;
	const char* path = "asciiArt.txt";
	const LPWSTR pathW = L"asciiArt.txt";
	BOOL changed_flag = FALSE;
	FILETIME check_time;
	HANDLE file_h = CreateFile(pathW, GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (!file_h)
	{
		printf("\No art for you >_<\nWhere's my asciArt.txt? :(\n");
		return ERROR_UNDER_CONSTRUCTION;
	}
	GetFileTime(file_h, NULL, NULL, &check_time);
	CloseHandle(file_h);
	if (lastRan.dwHighDateTime != check_time.dwHighDateTime) 
	{
		lastRan.dwHighDateTime = check_time.dwHighDateTime;
		changed_flag = TRUE;
	}
	//--
	char buffer[READ_BUFFER_SIZE];
	FILE* file = fopen(path,"r");
	if (!file)
		return ERROR_UNDER_CONSTRUCTION;
	if (changed_flag == TRUE)
		while (fgets(buffer, READ_BUFFER_SIZE, file))
		{
			if (buffer[0] == '#' && buffer[1] == '#' && strlen(buffer) < 5)
			{
				fgetc(file);
				positions = (fpos_t*)realloc(positions,sizeof(fpos_t) * ++count);
				if (!positions)
					return ERROR_ALLOCATING_MEMORY;
				fgetpos(file, &positions[count - 1]);
			}
		}
	if (count == 0)
		return ERROR_UNDER_CONSTRUCTION;
	fsetpos(file, &positions[rand() % count]);
	while (fgets(buffer, READ_BUFFER_SIZE, file))
	{
		if (buffer[0] == '#' && buffer[1] == '#' && strlen(buffer) < 5)
			break;
		_sleep(700);
		printf("%s", buffer);
	}
	fclose(file);
	return ERROR_UNDER_CONSTRUCTION;
}

int Clear(osoba root)
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
