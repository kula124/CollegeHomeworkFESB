#include "Header.h"
#include <stdio.h>
#include <stdlib.h>

int GetNumberOfElements(polinom root)
{
	int i = 0;
	while (root) {
		root = root->next;
		i++;
	}
	return i-1;
}

polinom * ListToArray(polinom root)
{
	polinom p = root->next;
	int c = GetNumberOfElements(root);
	int i = 0;
	polinom* List = (polinom*)calloc(c,sizeof(polinom_));
	if (!List)
		return NULL;
	while (i++ < c && p)
	{
		List[i] = p;
		p = p->next;
	}
	return List;
}

polinom ArrayToList(polinom * array, polinom root, int c)
{
	polinom p = root;
	int i = 0;
	for (i = 0; i < c; i++)
	{
		p = array[i];
		p = p->next;
	}
}
