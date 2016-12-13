#include "halp.h"
#include <stdio.h>
#include <stdlib.h>

int ManageList(list l)
{
	int error;
	if (l->next)
	{
		char c;
		do
		{
			puts("List is not empty!");
			printf("What to do with the list\n[A]pend | [E]rase | [C]ancel input | [S]how data\nPick: ");
			scanf(" %c", &c);
			if (c == 'S')
				if (error = WriteOut(l) != 0)
					return error;
		} while (c != 'A' && c != 'E' && c != 'C');
		if (c == 'A') 
		{
			while (l->next)
				l = l->next;
			return OK;
		}
		else if (c == 'E')
		{
			return DeleteList(&l);
		}
		else if (c == 'C')
			return ERROR_LIST_NOT_EMPTY;
	}
	return OK;
}

element CreateElement(int temp)
{
	element ne = (element)malloc(sizeof(_element));
	if (!ne)
		return ne;
	ne->value = temp;
	ne->next = NULL;
	return ne;
}

void Catch(int error)
{
	switch (error)
	{
	case ERROR_OPENING_FILE:
		printf("Failed to open file...\n");
		break;
	case ERROR_EMPTY_LIST:
		printf("Trying to manipulate empty list!\n");
		break;
	case ERROR_BAD_INPUT:
		printf("Bad input!\n");
		break;
	case ERROR_LISTS_NOT_READY:
		printf("Make sure the list is ready! (Check if lists 1 and 2 are empty)\n");
		break;
	case ERROR_LIST_NOT_EMPTY:
		printf("List is not empty, new input declined by user!\n");
		break;
	case ERROR_MALLOC_FAILED:
		printf("Failed to allocate memory! Quitting...\n");
		break;
	case ERROR_NULL_NOT_EXPECTED:
		printf("Unsepected null parameter! Should not happen! Quitting....\n");
		break;
	case ERROR_READING_FILE:
		printf("Reading inperupted, End Of File not reached! Qutting...\n");
		break;
	case OK:
		printf("[OK]\n");
		break;
	case USER_EXIT:
		printf("Byeee :)\n");
	case ABORTED:
		printf("Canceled!\n");
		break;
	default:
		printf("ayyyy lmao... dafaq just happened? O_o");
	}
}

void CheckFlag(int f)
{
	if (!f)
	{
		printf("    [");
		system(COLOR_RED);
		printf("NOT SET");
		system(COLOR_RST);
		printf("]\n");
	}
	else if (f = STATUS_OK) {
		printf("    [");
		system(COLOR_GRN);
		printf("OK");
		system(COLOR_RST);
		printf("]\n");
	}
	else if (f == STATUS_READY)
	{
		printf("    [");
		system(COLOR_YLW);
		printf("READY");
		system(COLOR_RST);
		printf("]\n");
	}
}

void CheckFlagUNIX(int f)
{
	return;
}

int InputPicker(list l)
{
	int e = ManageList(l);
	if (e != 0)
		return e;
	int c = 0;
	do {
		printf("Input to list:\n1) Read from file\n2) Input manually\n0) Back\nChoose: ");
		scanf(" %d", &c);
	} while (c != 0);
	if (!c)
		return ABORTED;
	if (c == 1)
	{
		char path[100];
		scanf(" %s", &path);
		return SortedReadFile(path, l);
	}
	if (c == 2)
	{
		return SortedInput(l);
	}
	return OK;
}

int SortedReadFile(char * path, list l)
{
	FILE* file_ = fopen(path, "r");
	if (!file_)
		return ERROR_OPENING_FILE;
	char c;
	int error;
	do
	{
		printf("[A]scending or [D]escending: ");
		scanf(" %c", &c);
	} while (c != 'A' && c != 'D');
	int fSort = c == 'A' ? 1 : -1;
	element p, prev, head = l;
	int val;
	while (fscanf(file_," %d", &val) && !feof(file_))
	{
		if (val < 0)
		{
			continue;
		}
		prev = head;
		p = head->next;
		if (!head->next)
		{
			head->next = CreateElement(val);
			continue;
		}
		while (p && (fSort * (p->value - val)) > 0)
		{
			prev = p;
			p = p->next;
		}
		if (error = InsertBehind(prev, val) != 0)
			return error;
	}
	return OK;
}

int Union(list l1, list l2, list l3)
{
	int e = ManageList(l3);
	if (e != 0)
		return e;
	if (!l1->next || !l2->next)
		return ERROR_EMPTY_LIST;
	element p = l3->next;
	while (l1 && l2)
	{
		if (l1->value > l2->value || l1->value == l2->value)
		{
			l3->next = CreateElement(l1->value);
			if (!l3->next)
				return ERROR_MALLOC_FAILED;
			l1 = l1->next;
		}
		else
		{
			l3->next = CreateElement(l2->value);
			if (!l3->next)
				return ERROR_MALLOC_FAILED;
			l2 = l2->next;
		}
	}
	while (l1)
	{
		l3->next = CreateElement(l1->value);
		if (!l3->next)
			ERROR_MALLOC_FAILED;
		l1 = l1->next;
	}
	while (l2)
	{
			l3->next = CreateElement(l2->value);
			if (!l3->next)
				ERROR_MALLOC_FAILED;
			l2 = l2->next;
	}
	return OK;
}

int JoinSection(list l1, list l2, list l3)
{
	int e = ManageList(l3);
	if (e != 0)
		return e;
	if (!l1->next || !l2->next)
		return ERROR_EMPTY_LIST;
	l1 = l1->next;
	element p = l2->next;
	while (l1)
	{
		while (p)
		{
			if (p->value == l1->value)
			{
				l3->next = CreateElement(p->value);
				l3 = l3->next;
			}
		}
		p = l2->next;
		l1 = l1->next;
	}
	return OK;
}

int WriteOut(list li)
{
	li = li->next;
	if (!li)
		return ERROR_EMPTY_LIST;
	while (li)
	{
		printf("%d, ",li->value);
		li = li->next;
	}
	return OK;
}

int SortedInput(list li)
{
	char c;
	int error;
	do 
	{
		printf("[A]scending or [D]escending: ");
		scanf(" %c", &c);
	} while (c != 'A' && c != 'D');
	int fSort = c == 'A' ? 1 : -1;
	element p, prev, head = li;
	int val;
	while (scanf(" %d", &val) && val != -1)
	{
		if (val < 0)
		{
			puts("Positive numbers only!");
			continue;
		}
		prev = head;
		p = head->next;
		if (!head->next)
		{
			head->next = CreateElement(val);
			continue;
		}
		while (p && (fSort * (p->value - val)) > 0)
		{
			prev = p;
			p = p->next;
		}
		if (error = InsertBehind(prev, val) != 0)
			return error;
	}
	return OK;
}

int DeleteList(list *li)
{
	element p = (*li)->next;
	if (!p)
		return ERROR_EMPTY_LIST;
	element prev = p;
	while (p)
	{
		prev = p;
		p = p->next;
		free(prev);
	}
	(*li)->next = NULL;
	return OK;
}

int InsertBehind(element el, int value)
{
	element temp = el->next;
	element ne = CreateElement(value);
	if (!ne)
		return ERROR_MALLOC_FAILED;
	ne->value = value;
	el->next = ne;
	ne->next = temp;
	return OK;
}
