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
		if (fList1 && fList2)
		{
			fUnion = 2;
			fSection = 2;
		}
		printf("1) Set 1st list");
		CheckFlag(fList1);
		printf("2) Set 2nd list");
		CheckFlag(fList2);
		printf("3) Union lists");
		CheckFlag(fUnion);
		printf("4) Join lists");
		CheckFlag(fSection);
		printf("5) Read list\n");
		printf("6) Clear list\n");
		printf("7) Write out to file\n");
		printf("Choose: ");
		scanf(" %d", &choise);
		switch (choise)
		{
		case 0:
			error = USER_EXIT;
			break;
		case 1:
			CLEAR_SCREEN();
			printf("Input 1st list:\n1) From file\n2) Input manually\nChoose: ");
			error = InputPicker(l1);
			if (!error)
				fList1 = 1;
			break;
		case 2:
			CLEAR_SCREEN();
			printf("Input 2nd list:\n1) From file\n2) Input manually\nChoose: ");
			error = InputPicker(l2);
			if (!error)
				fList2 = 1;
			break;
		case 3: 
			if (!fList1 || !fList2)
			{
				error = ERROR_LISTS_NOT_READY;
				break;
			}
			error = Union(l1, l2, uni);
			if (!error)
				fUnion = 1;
			break;
		case 4:
			if (!fList1 || !fList2)
			{
				error = ERROR_LISTS_NOT_READY;
				break;
			}
			error = JoinSection(l1, l2,&sec);
			if (!error) {
				fSection = 1;
			}
			break;
		case 5:
		{
			int pick = 0;
			CLEAR_SCREEN();
			puts("Read List:\n1) First list\n2) Second List\n3) Union List\n4) Joined List\n0) Back\nChoose: ");
			scanf(" %d", &pick);
			if (pick == 1)
				error = WriteOut(l1);
			else if (pick == 2)
				error = WriteOut(l2);
			else if (pick == 3)
				error = WriteOut(uni);
			else if (pick == 4)
				error = WriteOut(sec);
			else if (pick == 0)
				break;
			break;
		}
		case 6:
		{
			int pick6 = 0;
			CLEAR_SCREEN();
			puts("\nDelete List:\n1) First list\n2) Second List\n3) Union List\4) Joined List\n5) All \n0) Back\nChoose: ");
			scanf(" %d", &pick6);
			if (pick6 == 1)
				error = DeleteList(&l1);
			else if (pick6 == 2)
				error = DeleteList(&l2);
			else if (pick6 == 3)
				error = DeleteList(&uni);
			else if (pick6 == 4)
				error = DeleteList(&sec);
			else if (pick6 == 5)
			{
				if (!DeleteList(&l1))
					puts("List 1 deleted\n");
				if (!DeleteList(&l2))
					puts("List 2 deleted\n");
				if (!DeleteList(&uni))
					puts("Union list deleted\n");
				if (!DeleteList(&sec))
					puts("Joined list deleted\n");
				break;
			}
			else if (pick6 == 0)
				break;
			break;
		}
		default:
			printf("Bad choise!\n");
		}
		Catch(error);
		_sleep(2000);
		printf("Press ENTER to continue...");
		getchar();
		getchar();
		CLEAR_SCREEN();
	}
}
