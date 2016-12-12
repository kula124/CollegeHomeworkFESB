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

	element p = head, prev;
	int scaned = 0;
	while (p && Compare(p->value, scaned, sflag))
	{
		prev = head;
		p = head->next;
		if (IsEmpty(head))
		{
			head->next = CreateElement(scaned);
			continue;
		}
		while (p && p->value > scaned)
		{
			prev = p;
			p = p->next;
		}
		error = InsertBehind(prev, scaned);
		if (error != 0)
			return error;
	}
	if (!feof(file_))
		return ERROR_READING_FILE;
	return OK;
}

int AddList(list l, list lt)
{
	while (l)
	{
		lt->next = l;
		lt = lt->next;
		l = l->next;
	}
	lt->next = NULL;
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
		while (l3->next) //Set pointer to end of the list
			l3 = l3->next;
	}
	while (l1 && l2)
	{
		if (l1->value > l2->value)
		{
			l3->next = l1;
			l1 = l1->next;
		}
		else if (l2->value > l1->value)
		{
			l3->next = l2;
			l2 = l2->next;
		}
		else
		{
			l3->next = l2;
			l2 = l2->next;
			l1 = l1->next;
		}
		l3 = l3->next;
	}
	if (!l1)
		AddList(l2, l3);
	else
		AddList(l1, l3);
	return OK;
}

int JoinSection(list l1, list l2, list * l3)
{
	if (!l1 || !l2 || !l2->next || l1->next)
		return ERROR_EMPTY_LIST;
	list head = *l3;
	element p = l2->next;
	while (l1)
	{
		while (p)
		{
			if (l1->value == p->value)
				InsertBehind(*l3, p->value);
			p = p->next;
		}
		l1 = l1->next;
	}
	return OK;
}

int WriteOut(list li)
{
	li = li->next;
	if (!li)
		return ERROR_EMPTY_LIST;
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
	element p = head, prev;
	puts("Enter -1 to stop inputing!\nInput integer: ");
	while (scanf("  %d", &scaned)>0 && scaned!=-1)
	{
		prev = head;
		p = head->next;
		if (IsEmpty(head))
		{
			head->next = CreateElement(scaned);
			continue;
		}
		while (p && Compare(p->value,scaned,sflag))
		{
			prev = p;
			p = p->next;
		}
		error = InsertBehind(prev, scaned);
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

int InsertBehind(element el, int val)
{
	element t;
	element ne = CreateElement(val);
	if (!ne)
		return ERROR_MALLOC_FAILED;
	t = el->next;
	el->next = ne;
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
	case ERROR_BAD_INPUT :
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
	case OK :
		printf("[OK]\n");
		break;
	case USER_EXIT:
		printf("Byeee :)\n");
	default:
		printf("ayyyy lmao... dafaq just happened? O_o");
	}
}

void CheckFlag(int f)
{
	if (f == 1)
		printf("   [OK]\n");
	else if (f == 2)
		printf("   [Ready]\n");
	else
		printf("\n");
}

int InputPicker(list tl)
{
	int c;
	scanf(" %d", &c);
	if (c == 1)
	{
		char path[P_SIZE];
		printf("Enter path: ");
		scanf(" %s", &path);
		return SortedReadFile(path, &tl);
	}
	if (c == 2)
		return SortedInput(&tl);
	return ERROR_BAD_INPUT;
}

