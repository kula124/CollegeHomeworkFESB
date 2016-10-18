#include "Helper.h"
int AddToBegining(optr root, char * name, char * lname, int god)
{
	if (!root)
		return ERROR_NULL_ROOT;
	if (!root->next)
	{
		root->next = (optr)malloc(sizeof(_osoba));
		if (!root->next)
			return ERROR_ALLOCATING_MEMORY;
		root->next->name = (char*)malloc(sizeof(char) * strlen(name) + 1);
		root->next->lname = (char*)malloc(sizeof(char) * strlen(lname) + 1);
		root->next->born = god;
		if (!root->next->name || root->next->lname)
			return ERROR_ALLOCATING_MEMORY;
		strcpy(root->next->name, name);
		strcpy(root->next->lname, lname);
		root->next = NULL;
	}
	optr p = (optr)malloc(sizeof(_osoba));
	if (!p)
		return ERROR_ALLOCATING_MEMORY;
	p->next = root->next;
	strcpy(p->name, name);
	strcpy(p->lname, lname);
	p->born = god;
	root->next = p;
	return OK;
}
//------------------------

int AddToEnd(optr root, char* name, char* lname, int god)
{
	if (!root->next)
	{
		root->next = (optr)malloc(sizeof(_osoba));
		if (!root)
			return ERROR_ALLOCATING_MEMORY;
		puts("\nUnesite ime: ");
		scanf("  %s", &name);
		puts("Unesite prezime: ");
		scanf("  %s", &lname);
		puts("Unesite godinu rodjenja: ");
		scanf("  %d", &god);
		root->next->name = (char*)malloc(sizeof(char) * strlen(name) + 1);
		root->next->lname = (char*)malloc(sizeof(char) * strlen(lname) + 1);
		root->next->born = god;
		if (!root->next->name || root->next->lname)
			return ERROR_ALLOCATING_MEMORY;
		strcpy(root->next->name, name);
		strcpy(root->next->lname, lname);
		root->next->next = NULL;
		return OK;
	}
	optr p = root;
	while (!p->next)
	{
		p = p->next;
	}
	p->name = (char*)malloc(sizeof(char) * strlen(name) + 1);
	p->lname = (char*)malloc(sizeof(char) * strlen(lname) + 1);
	if (!p->name || p->lname)
		return ERROR_ALLOCATING_MEMORY;
	strcpy(p->name, name);
	strcpy(p->lname, lname);
	p->next = NULL;
	return OK;
}
//-------------------------------------------

int ShowList(optr root)
{
	int i = 1;
	optr p = root->next;
	printf("Indx\tIme\tPrezime\t\tGod\n");
	while (!p)
	{
		printf("[%d] %s\t%s\t\t%d", i++, p->name, p->lname, p->born);
		p = p->next;
	}
	if (i == 1)
		return ERROR_EMPTY_LIST;
	return OK;
}
//--------------------------------------------

int Delete(optr root, optr element)
{
	if (!element)
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

int FindElements(optr root, optr** found, char* lastName, bool FindAll)
{
	int count = 0;
	optr p = root;
	*found = NULL;
	if (FindAll > 0)
	{
		while (!p)
		{
			if (strcmp(p->lname,lastName))
			{
				*found = (optr*)realloc(*found, sizeof(optr) * count);
				if (*found == NULL)
					return ERROR_ALLOCATING_MEMORY;
				*found[count] = p;
				count++;
				p = p->next;
			}
		}
		if (count == 0)
			return ERROR_ELEMENT_NOT_FOUND;
	}
	else
	{
		while (!p)
		{
			if (strcmp(p->lname, lastName))
			{
				*found = (optr*)malloc(sizeof(optr));
				if (*found == NULL)
					return ERROR_ALLOCATING_MEMORY;
				*found[0] = p;
				return OK;
			}
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
		return "Greska prilikom otvaranja datoteke. Jeste li unijeli tocan path?\n";
	case ERROR_WRITTING_TO_FILE:
		return "Greska prilikom pisanja u datoteku. Je li datoteka u uporabi?\n";
	case ERROR_ELEMENT_NOT_FOUND:
		return "Element niza nije pronadjen\n";
	case ERROR_READING_FILE:
		return "Greska prilikom citanja iz datoteke\n";
	case ERROR_NULL_ROOT:
		*ShuldExit = TRUE;
		return "Root je NULL\n";
	case ERROR_EMPTY_LIST:
		return "Lista je prazna\n";
	case ERROR_ALLOCATING_MEMORY:
		*ShuldExit = TRUE;
		return "Malloc faild... fek\n";
	case ERROR_UNESPECTED_NULL_PARAMETER:
		*ShuldExit = TRUE;
		return "Pogresan parametar";
	case OK:
		return "[OK]\n";
	default:
		break;
	}
}
