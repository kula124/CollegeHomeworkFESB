#include "Halp.h"
#include <stdlib.h>
#include  <stdio.h>

int SortedReadFile(char* path, list* l)
{
	int option;
	char s;
	do
	{
		printf("Sort [A]scending or [D]escending: ");
		scanf("  %c", &s);
	} while (s != 'A' && s != 'D');
	int sflag = s == 'A' ? 1 : -1;
	int error = 0;
	list head = *l;
	FILE* file_ = fopen(path, "r");
	if (!file_)
		return ERROR_OPENING_FILE;

	if (!IsEmpty(head))
	{
		option = ManageList();
		if (option == OPTION_CANCEL)
			return ERROR_LIST_NOT_EMPTY;
		if (option == OPTION_ERASE)
		{
			error = DeleteList(l);
			if (error == 0)
				printf("\nList cleared!\n");
			else
				return error;
		}
		element F = head->next;
		while (F->next)
			F = F->next;
	}

	element p, prev;
	int scaned = 0;
	while (fscanf(file_, " %d", &scaned) && !feof(file_))
	{
		p = head->next;
		if (IsEmpty(head))
		{
			head->next = CreateElement(scaned);
			break;
		}
		if (Compare (p->value,scaned,sflag) > 0)
		{
			prev = p;
			p = p->next;
		}
		error = InsertBehind(&prev, scaned);
		if (error != 0)
			return error;
	}
	if (!feof(file_))
		return ERROR_READING_FILE;
	return OK;
}

int Union(list l1, list l2, list l3)
{
	int option = 0;
	int error = 0;
	if (l3->next)
	{
		option = ManageList();
		if (option == OPTION_CANCEL)
			return ERROR_LIST_NOT_EMPTY;
		if (option == OPTION_ERASE)
		{
			error = DeleteList(&l3);
			if (error == 0)
				printf("\nList cleared!\n");
			else
				return error;
		}
		while (l3->next)
			l3 = l3->next;
	}
	while (l1 && l2)
}

int WriteOut(list li)
{
	if (!li->next)
		return ERROR_EMPTY_LIST;
	printf("List: ");
	while (li)
	{
		printf(" %d, ", li->value);
		li = li->next;
	}
	return OK;
}

int SortedInput(list* li)
{
	char s;
	do
	{
		printf("Sort [A]scending or [D]escending: ");
		scanf("  %c", &s);
	} while (s != 'A' && s != 'D');
	int sflag = s == 'A' ? 1 : -1;
	element head = *li;
	int error = 0;
	int scaned;
	if (!IsEmpty(head))
	{
		char c = 'b';
		do
		{
			printf("Given list is not empty and should be erased! Continue or append to it? \n[e]rase/[a]ppend/[c]ancel: ");
			scanf("  %c", &c);
		}
		while (c != 'e' && c != 'a' && c != 'c');
		if (c == 'c')
			return ERROR_LIST_NOT_EMPTY;
		if (c == 'e')
		{
			error = DeleteList(li);
			if (error != 0)
				return error;
			puts("List cleared!");
		}
	}
	element p, prev, temp;
	puts("Enter -1 to stop inputing!\nInput integer: ");
	while (scanf(" %d", &scaned)>0 && scaned!=-1)
	{
		p = head->next;
		if (IsEmpty(head))
		{
			head->next = CreateElement(scaned);
			break;
		}
		if (p && p->value > scaned)
		{
			prev = p;
			p = p->next;
		}
		error = InsertBehind(&prev, scaned);
		if (error != 0)
			return error;
	}
	return OK;
}

int IsEmpty(list li)
{
	return li->next == NULL ? 1 : 0;
}

int DeleteList(list* li)
{
	if (!li && !(*li)->next)
		return ERROR_NULL_NOT_EXPECTED;
	element head = *li;
	element prev, p = head->next;
	while (p)
	{
		prev = p;
		p = p->next;
		free(prev);
	}
	head->next = NULL;
	return OK;
}

int InsertBehind(element* el, int val)
{
	element t, ele = *el;
	element ne = CreateElement(val);
	if (!ne)
		return ERROR_MALLOC_FAILED;
	t = ele->next;
	ele->next = ne;
	ne->next = t;
	return OK;
}

int Compare(int a, int b, int flag)
{
	if (a == b)
		return 0;
	if (Signum(a) == Signum(b))
		return flag * (a - b);
	if (Signum(a) > 0)
		return flag * a;
	return flag * b;
}

int ManageList()
{
	char c = 'b';
	do
	{
		printf("Given list is not empty and should be erased! Continue or append to it? \n[e]rase/[a]ppend/[c]ancel: ");
		scanf("  %c", &c);
	} while (c != 'e' && c != 'a' && c != 'c');
	if (c == 'c')
		return 1;
	if (c == 'e')
	{
		return 2;
	}
	return 3;
}

element CreateElement(int temp)
{
	element ne = (element)malloc(sizeof(_element));
	if (!ne)
		return NULL;
	ne->value = temp;
	ne->next = NULL;
	return ne;
}

int Signum(int value)
{
	return value > 0 ? 1 : -1;
}
