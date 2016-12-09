#include <stdio.h>
#include "Halp.h"
#include <stdlib.h>



int main ()
{
	int fList1=0, fList2=0, fUnion=0, fSection=0, choise = -1, error = 0;
	list l1, l2, uni, sec;
	l1 = CreateElement(-999);
	l2 = CreateElement(-999);
	uni = CreateElement(-999);
	sec = CreateElement(-999);
	while (choise != 0)
	{
		printf("1) Set 1st list");
		CheckFlag(fList1);
		printf("2) Set 2nd list");
		CheckFlag(fList2);
		printf("3) Union lists");
		CheckFlag(fUnion);
		printf("4) Join lists");
		CheckFlag(fSection);
		printf("5) Read list\n");
		printf("6) Clear all\n");
		printf("Choose: ");
		scanf(" %d", &choise);
		switch (choise)
		{
		case 1:
			printf("Input 1st list:\1)From file\n2)Input manually\nChoose: ");
			error = InputPicker(l1);
			if (!error)
				fList1 = 1;
			break;
		case 2:
			printf("Input 2nd list:\1)From file\n2)Input manually\nChoose: ");
			error = InputPicker(l2);
			if (!error)
				fList2 = 1;
			break;
		case 3: 
			Catch(error);
			CLEAR_SCREEN();
		}
	}
}
