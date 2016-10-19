#include "Helper.h"
optr CreateElement(char * n, char * l, int god)
{
	optr p = (optr)malloc(sizeof(_osoba));
	if (!p)
		return p;
	if ((n == NULL || strlen(n) <= 2) && (l == NULL || strlen(l) <= 2))
	{
		p->name = NULL;
		p->lname = NULL;
		p->next = NULL;
		p->born = 0;
		return p;
	}
	p->name = (char*)malloc(sizeof(char) * strlen(n) + 1);
	p->lname = (char*)malloc(sizeof(char) * strlen(l) + 1);
	if (!p->name || !p->lname)
		return NULL;
	strcpy(p->name, n);
	strcpy(p->lname, l);
	p->born = god;
	return p;
}
//--------------------------------------

int AddToBegining(optr root, char * name, char * lname, int god)
{
	if (!root)
		return ERROR_NULL_ROOT;
	optr p = CreateElement(name, lname, god);
	if (!p)
		return ERROR_ALLOCATING_MEMORY;
	p->next = root->next;
	root->next = p;
	return OK;
}
//------------------------

int AddToEnd(optr root, char* name, char* lname, int god)
{
	if (!root)
		return ERROR_NULL_ROOT;
	optr p = root;
	while (p->next)
	{
		p = p->next;
	}
	p->next = CreateElement(name, lname, god);
	p->next->next = NULL;
	return OK;
}
//-------------------------------------------

int ShowList(optr root)
{
	int i = 1;
	optr p = root->next;
	printf("Indx\tIme\tPrezime\t\tGod\n");
	while (p)
	{
		printf("[%d] %s\t%s\t\t%d", i++, p->name, p->lname, p->born);
		p = p->next;
	}
	if (i == 1)
		return ERROR_EMPTY_LIST;
	return OK;
}
//--------------------------------------------

int ShowElement(optr p)
{
	if (!p)
		return ERROR_EMPTY_LIST;
	printf("%s\t%s\t\t%d\n", p->name, p->lname, p->born);
	return OK;
}
//--------------------------------------------

int Delete(optr root, optr element)
{
	if (!element || !root)
		return ERROR_UNESPECTED_NULL_PARAMETER;
	if (!root->next)
		return ERROR_EMPTY_LIST;
	optr p = root->next;
	while (p->next != element && p->next != NULL)
		p = p->next;
	if (p->next == NULL)
		return ERROR_ELEMENT_NOT_FOUND;
	optr del = p->next;
	p->next = p->next->next;
	free(del);
	return OK;
}
//---------------------------------------------

int FindElements(optr root, optr** found, char* lastName, int* FindAll)
{
	int count = 1;
	optr p = root->next;
	*found = NULL;
	if (*FindAll > 0)
	{
		while (p)
		{
			if (strcmp(p->lname,lastName) == 0)
			{
				*found = (optr*)realloc(*found, sizeof(_osoba) * count);
				if (*found == NULL)
					return ERROR_ALLOCATING_MEMORY;
				*found[count - 1] = (optr)malloc(sizeof(optr));
				*found[count - 1] = p;
				count++;
				p = p->next;
			}
		}
		if (count == 0)
			return ERROR_ELEMENT_NOT_FOUND;
		*FindAll = count;
		return OK;
	}
	else
	{
		while (p)
		{
			if (strcmp(p->lname, lastName) == 0)
			{
				*found = (optr*)malloc(sizeof(optr));
				if (*found == NULL)
					return ERROR_ALLOCATING_MEMORY;
				*found[0] = p;
				*FindAll = 1;
				return OK;
			}
			p = p->next;
		}
		return ERROR_ELEMENT_NOT_FOUND;
	}
}
//---------------------------------------------
char * Catch(int ErrorCode, int* ShuldExit)
{
	*ShuldExit = 0;
	switch (ErrorCode)
	{
	case ERROR_OPENING_FILE:
		*ShuldExit = ERROR_OPENING_FILE;
		return "Greska prilikom otvaranja datoteke. Jeste li unijeli tocan path?\n";
	case ERROR_WRITTING_TO_FILE:
		*ShuldExit = ERROR_WRITTING_TO_FILE;
		return "Greska prilikom pisanja u datoteku. Je li datoteka u uporabi?\n";
	case ERROR_ELEMENT_NOT_FOUND:
		*ShuldExit = ERROR_ELEMENT_NOT_FOUND;
		return "Element niza nije pronadjen\n";
	case ERROR_READING_FILE:
		*ShuldExit = ERROR_READING_FILE;
		return "Greska prilikom citanja iz datoteke\n";
	case ERROR_NULL_ROOT:
		*ShuldExit = ERROR_NULL_ROOT;
		return "Root je NULL\n";
	case ERROR_EMPTY_LIST:
		*ShuldExit = ERROR_EMPTY_LIST;
		return "Lista je prazna\n";
	case ERROR_ALLOCATING_MEMORY:
		*ShuldExit = ERROR_ALLOCATING_MEMORY;
		return "Malloc failed... fek\n";
	case ERROR_UNESPECTED_NULL_PARAMETER:
		*ShuldExit = ERROR_UNESPECTED_NULL_PARAMETER;
		return "Pogresan parametar";
	case OK:
		return "[OK]\n";
	default:
		break;
	}
}
