#include "Helper.h"

int AddToBegining(optr root, char * name, char * lname, int god)
{
	if (!root)
	{
		root = (optr)malloc(sizeof(_osoba));
		if (!root)
			return ERROR_ALLOCATING_MEMORY;
		root->name = (char*)malloc(sizeof(char) * strlen(name) + 1);
		root->lname = (char*)malloc(sizeof(char) * strlen(lname) + 1);
		root->born = god;
		if (!root->name || root->lname)
			return ERROR_ALLOCATING_MEMORY;
		strcpy(root->name, name);
		strcpy(root->lname, lname);
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

int AddToEnd(optr root,char* name,char* lname, int god)
{
	if (!root)
	{
		root = (optr)malloc(sizeof(_osoba));
		if (!root)
			return ERROR_ALLOCATING_MEMORY;
		puts("\nUnesite ime: ");
		scanf("  %s", &name);
		puts("Unesite prezime: ");
		scanf("  %s", &lname);
		puts("Unesite godinu rodjenja: ");
		scanf("  %d", &god);
		root->name = (char*)malloc(sizeof(char) * strlen(name) + 1);
		root->lname = (char*)malloc(sizeof(char) * strlen(lname) + 1);
		root->born = god;
		if (!root->name || root->lname)
			return ERROR_ALLOCATING_MEMORY;
		strcpy(root->name, name);
		strcpy(root->lname, lname);
		root->next = NULL;
		return OK;
	}
	optr p = root;
	while (!p->next)
	{
		p = p->next;
	}
	p->name = (char*)malloc(sizeof(char) * strlen(name) + 1);
	p->lname = (char*)malloc(sizeof(char) * strlen(lname) + 1);
	if (!root->name || root->lname)
		return ERROR_ALLOCATING_MEMORY;
	strcpy(root->name, name);
	strcpy(root->lname, lname);
	p->next = NULL;
	return OK;
}
//-------------------------------------------

int ShowList(optr root)
{
	int i = 1;
	optr p = root;
	printf("Indx\tIme\tPrezime\t\tGod\n");
	while (!p)
	{
		printf("[%d] %s\t%s\t\t%d",i++,p->name,p->lname,p->born);
		p = p->next;
	}
	if (i == 1)
		return ERROR_EMPTY_LIST;
	return OK;
}
//---------------------------------------------

int FindElement(optr root, optr ** found, char * lastName, bool FindAll)
{
	int count = 0;
	optr p = root;
	*found = NULL;
	if (FindAll > 0)
	{
		while (!p)
		{
			if (p->lname == lastName)
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
			if (p->lname == lastName)
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
