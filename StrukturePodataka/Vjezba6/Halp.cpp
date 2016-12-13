#include "Halp.h"
#include <stdlib.h>
#include <stdio.h>

int Read(list l)
{
	if (!l->next)
		return ERROR_EMPTY_LIST;
	element p = l->next;
	while (p) {
		printf(" %d,", p->value);
		p = p->next;
	}
	printf("\n");
	return OK;
}

int PopS(list s, int* v)
{
	if (!s->next)
		return ERROR_EMPTY_LIST;
	element p = s;
	while (p->next)
		p = p->next;
	*v = p->value;
	return OK;
}

int PopQ(list q, int * v)
{
	if (q->next == NULL)
		return ERROR_EMPTY_LIST;
	*v = q->next->value;
	return OK;
}

int Push(list l, int v)
{
	element p = l;
	while (p->next)
		p = p->next;
	p->next = CreateElement(v);
	if (!p->next)
		return ERROR_MALLOC_FAILED;
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