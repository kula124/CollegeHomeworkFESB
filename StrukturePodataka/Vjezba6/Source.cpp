#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include "Halp.h"
int main()
{
	list stack = (list) malloc (sizeof(_element));
	stack->value = -1;
	stack->next = NULL;
	list que = (list)malloc(sizeof(_element));
	que->value = -1;
	que->next = NULL;
	int choise = -1;
	int error;
	while (choise)
	{
		printf("1) Push to stack\n");
		printf("2) Pop from stack\n");
		printf("3) Push to que\n");
		printf("4) Pop form que\n");
		printf("5) Read stack\n");
		printf("6) Read que\n");
		printf("Choose: ");
		scanf(" %d", &choise);
		switch (choise)
		{
		case 1:
		{
			int val = 0;
			printf("Enter value to push: ");
			scanf(" %d", &val);
			error = Push(stack, val);
			break;
		}
		case 2:
		{
			int val = 0;
			error = PopS(stack,&val);
			if (error)
				break;
			printf("Value poped from stack: %d\n", val);
			break;
		}
		case 3:
		{
			int val = 0;
			printf("Enter value to push: ");
			scanf(" %d", &val);
			error = Push(que, val);
			break;
		}
		case 4:
		{
			int val = 0;
			error = PopQ(stack, &val);
			if (error)
				break;
			printf("Value poped from stack: %d\n", val);
			break;
		}
		case 5:
			error =	Read(stack);
			break;
		case 6:
			error = Read(que);
			break;
		}
	}
	return 0;
}