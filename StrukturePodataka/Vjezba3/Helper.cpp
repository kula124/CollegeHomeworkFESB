#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Helper.h"
///<sumary>Always inserts new behind element</sumary>
/// <param name="elemnt">Element behind witch new element is inserted</param>
///<returns>(int)Error code defined in Helper.h</returns>
///<remarks>If "element" equals NULL new element is insterted at the end of the list</remarks>
int Insert(osoba root, osoba element)
{
	osoba p = root;
	if (!element)
	{
		while (p->next)
			p = p->next;
		p->next = CreateElement(" ", " ", 0);
		if (!p->next)
			return ERROR_ALLOCATING_MEMORY;
		return OK;
	}
	p = CreateElement(" ", " ", 0);
	if (!p)
		return ERROR_ALLOCATING_MEMORY;
	p->next = element->next;
	element->next = p;
	return OK;
}
///<sumary>Finds element with matching parameters in a list</sumary>
/// <param type = "char*">Strings to be evaluated</param>
///<returns>Pointer to element if found, NULL otherwise</returns>
///<remarks>Leaving strings empty or single charred and/or "g" set to 0 will skip their evaluation</remarks>
osoba Find(osoba root, char * n, char * l, int g)
{
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
	while (p->next)
	{
		int sn = FALSE, sl = FALSE, sg = FALSE; //same name, lname, god flags
		if (evaN && strcmp(p->name, n) == 0)
			sn = TRUE;
		if (evaL && strcmp(p->lname, l)==0)
			sl = TRUE;
		if (evaG && p->born == g)
			sg = TRUE;
		if ((evaN == sn) && (evaL == sl) && (evaG == sg)) //Smart ha?
			return p; //Thank you short-circuting
		p = p->next;
	}
	return NULL;
}

osoba FindPrev(osoba root, osoba element)
{
	if (!element)
		return NULL;
	osoba p = root;
	while (p->next && p->next != element)
		p = p->next;
	if (!p->next)
		return NULL;
	return p;
}

int Swap(osoba A, osoba B, osoba prevA)
{
	if (!A || !B || !prevA)
		return ERROR_UNESPECTED_NULL_PARAMETER;
	prevA->next= B;
	A->next = B->next;
	B->next = A;
	return OK;
}

osoba CreateElement(char* n, char*l, int b)
{
	if (b < 0) //Create root
	{
		osoba p = (osoba)malloc(sizeof(_osoba));
		if (!p)
			return NULL;
		p->lname = NULL;
		p->name = NULL;
		p->born = -1;
		p->next = NULL;
		return p;
	}
	if (!n || !l || b == 0 || strlen(n) < 2 || strlen(l) < 2)
	{
		char name[NAME_LENGHT], lname[NAME_LENGHT];
		int born;
		osoba q = (osoba)malloc(sizeof(_osoba));
		if (!q)
			return NULL;
		printf("\nUnesite ime: ");
		scanf(" %s", &name);
		printf("Unesite prezime: ");
		scanf(" %s", &lname);
		printf("Unesite godinu rodjenja: ");
		scanf(" %d", &born);
		q->born = born;
		q->lname = (char*)malloc(sizeof(char) * strlen(lname) + 1);
		strcpy(q->lname, lname);
		q->name = (char*)malloc(sizeof(char) * strlen(name) + 1);
		strcpy(q->name, name);
		q->next = NULL;
		return q;
	}

	osoba p = (osoba)malloc(sizeof(_osoba));
	if (!p)
		return NULL;
	p->name = (char*)malloc(sizeof(n) + 3);
	p->lname = (char*)malloc(sizeof(l) + 3);
	p->born = b;
	strcpy(p->lname, l);
	strcpy(p->name, n);
	p->next = NULL;
	return p;
}

int Delete(osoba root, osoba element)
{
	osoba p = root;
	if (!element)
		return ERROR_ELEMENT_NOT_FOUND;
	while (p->next && p->next != element)
		p = p->next;
	if (!p->next)
		return ERROR_ELEMENT_NOT_FOUND;
	osoba q = p->next;
	p->next = p->next->next;
	return FreeEl(q);
}

int ClearList(osoba root)
{
	osoba p, prev;
	p = root->next;
	if (!root)
		return ERROR_NULL_ROOT;
	if (!root->next)
		return ERROR_EMPTY_LIST;
	while (p)
	{
		prev = p;
		p = p->next;
		FreeEl(prev);
	}
	root->next = NULL;
	return OK;
}

int ReadFilev2(osoba root, char* path, int append)
{
	osoba p = root;
	fpos_t pos;
	FILE* file_ = fopen(path, "r");
	if (!file_)
		return ERROR_OPENING_FILE;
	if (!append)
		if (ClearList(root) < 0)
			return ERROR_NULL_ROOT;
	while (p->next)
		p = p->next;
	//read file
	char buffer[2 * NAME_LENGHT + 6];
	while (!feof(file_))
	{
		char tn[NAME_LENGHT], tl[NAME_LENGHT];
		int born;
		fgetpos(file_, &pos);
		fgets(buffer, 2 * NAME_LENGHT + 6, file_);
		if (buffer[0] == '#' || strlen(buffer) < 2)
			continue;
		fsetpos(file_, &pos);
		fscanf(file_, " %s%s%d", &tn, &tl, &born);
		osoba n = CreateElement(tn, tl, born);
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

int WriteFile(osoba start, char* path, int appendToFile)
{
	FILE* file_ = NULL;
	osoba p = start;
	if (!p)
		return ERROR_UNESPECTED_NULL_PARAMETER;
	if (p->lname == NULL || p->lname == NULL || p->born <= 0) //check for root
	{
		if (!p->next)
			return ERROR_EMPTY_LIST;
		p = p->next; //start
	}
	if (appendToFile > 0)
		file_ = fopen(path, "a");
	else
		file_ = fopen(path, "w");
	if (!file_)
		return ERROR_OPENING_FILE;
	fprintf(file_, "#Ime\tPrezime\t\tGod\n");
	while (p)
	{
		fprintf(file_, "%s\t%s\t\t%d\n",p->name,p->lname,p->born);
		p = p->next;
	}
	fclose(file_);
	return OK;
}

int FreeEl(osoba element)
{
	if (!element)
		return ERROR_UNESPECTED_NULL_PARAMETER;
	free(element->lname);
	free(element->name);
	free(element);
	return OK;
}

int CompareElement(osoba A, osoba B, int compareBy)
{
	if (compareBy == NAME)
	{
		return strcmp(A->name, B->name);
	}
	else if (compareBy == LNAME)
	{
		return strcmp(A->lname, B->lname);
	}
	else if (compareBy == BORN)
	{
		return A->born - B->born;
	}
	else
	{
		if (strcmp(A->name, B->name) == 0 && strcmp(A->lname, B->lname) == 0 && A->born == B->born)
			return 0;
	}
}

int CompareBorn(const void * A, const void * B)
{
	osoba a = (osoba)A;
	osoba b = (osoba)B;
	return (a->born - b->born);
}

int Sort(osoba root, int sortBy, int method, double *time, char order) //Under construction
{
	int Order = (int)order == ASCENDING ? -1 : 1;
	if (!root->next)
		return ERROR_EMPTY_LIST;
	if (sortBy == BORN && method == METHOD_QSRT) //Broken
	{
		return UNDER_CONSTRUCTION; //temp dissabled
		int c = 0;
		osoba arr = ListToArray(root, &c);
		double start = (double)clock() / CLOCKS_PER_SEC;
		qsort(arr, c, sizeof(_osoba), CompareBorn);
		double end = (double)clock() / CLOCKS_PER_SEC;
		*time = start - end;
		ArrayToList(root, arr, c);
		return OK;
	}
	else if (sortBy == BORN && method == METHOD_BUBBLE)
	{
		osoba p, prev;
		p = root;
		prev = root;
		int i = 0, n = GetNumberOfElements(root);
		if (n < 2)
			return ERROR_TOO_FEW_ELEMENTS;
		while (i++ < n)
		{

			while (true)
			{
				prev = p;
				p = p->next;
				if (!p->next)
					break;
				if ((Order * CompareElement(p, p->next, BORN)) >= 0)
					continue;
				Swap(p, p->next, prev);
				p = prev->next;
			}
		}
	}
	else
		return UNDER_CONSTRUCTION;
}

osoba ListToArray(osoba root, int* c)
{
	osoba p = root->next;
	*c = GetNumberOfElements(root);
	int i;
	osoba List = (osoba)malloc(sizeof(_osoba) * *c);
	if (!List)
		return List;
	for (i = 0; i < *c; i++)
	{
		List[i] = *p;
		p = p->next;
	}
	return List;
}

osoba ArrayToList(osoba root, osoba arr, int c)
{
	int i = 0;
	osoba p = root;
	ClearList(root);
	for (i = 0; i < c; i++)
	{
		p->next = &arr[i];
		p = p->next;
	}
	return root;
}

int GetNumberOfElements(osoba root)
{
	osoba p = root;
	int c = 0;
	while (p->next)
	{
		p = p->next;
		c++;
	}
	return c;
}

void ShowElement(osoba ele)
{
	if (!ele)
		printf("Osoba ne postoji u listi");
	printf("\n------------\nOsoba:\n ");
	printf("Ime: %s\n Prezime: %s\n Godiste: %d\n", ele->name, ele->lname, ele->born);
}

int ShowList(osoba root)
{
	if (!root)
		ERROR_NULL_ROOT;
	if (!root->next)
		return ERROR_EMPTY_LIST;
	int i = 1;
	osoba p = root->next;
	printf("[I] Ime\t\tPrezime\t\tGod\n");
	while (p)
	{
		printf("[%d] %s\t%s\t\t%d\n", i++, p->name, p->lname, p->born);
		p = p->next;
	}
	if (i == 1)
		return ERROR_EMPTY_LIST;
	return OK;
}

//////////////////////////////////////////
char * Catch(int ErrorCode, int* ShuldExit)
{
	*ShuldExit = ErrorCode;
	switch (ErrorCode)
	{
	case ERROR_OPENING_FILE:
		return "Greska prilikom otvaranja datoteke. Jeste li unijeli tocan path?\n";
	case ERROR_WRITTING_TO_FILE:
		return "Greska prilikom pisanja u datoteku. Je li datoteka u uporabi?\n";
	case ERROR_ELEMENT_NOT_FOUND:
		return "Element niza nije pronadjen\n";
	case ERROR_READING_FILE:
		return "Greska prilikom citanja iz datoteke\n";
	case ERROR_NULL_ROOT:
		return "Root je NULL\n";
	case ERROR_EMPTY_LIST:
		return "Lista je prazna\n";
	case ERROR_ALLOCATING_MEMORY:
		return "Malloc failed... fek\n";
	case ERROR_UNESPECTED_NULL_PARAMETER:
		return "Pogresan parametar\n";
	case UNDER_CONSTRUCTION:
		return "Metoda jos nije napisana (coming soon)\n";
	case ERROR_TOO_FEW_ELEMENTS:
		return "Premalo elemenata za sortiranje\n";
	case OK:
		return "[OK]\n";
	default:
		break;
	}
}