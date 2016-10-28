#include <stdio.h>
#include <stdlib.h>
#include "Helper.h"
#include <time.h>
int main()
{
	osoba root = CreateNode(-1);
	int choise = -1;
	int ERROR_CODE;
	char tempC; 
	while (choise != 0)
	{
		printf("\n***********************************\n");
		printf("***********************************\n");
		printf("***************IZBORNIK************\n");
		printf("***********************************\n");
		printf("***********************************\n");
		printf("1) Dodaj element na pocetak\n");
		printf("2) Dodaj element na kraj\n");
		printf("3) Dodaj iza elementa\n");
		printf("4) Dodaj ispred elementa\n");
		printf("5) Pronadji element\n");
		printf("6) Izbrisi element\n");
		printf("7) Ispisi listu\n");
		printf("8) Zapisi u file\n");
		printf("9) Procitaj iz filea\n");
		printf("10) Sortiraj list\n");
		printf("11) Ocisti listu\n");
		printf("0) Izlaz\n\n");
		printf("Izbor:   ");
		scanf(" %d", &choise);
		ERROR_CODE = OK;
		switch (choise)
		{
		case 1: //na pocetak
			ERROR_CODE = InsertNode(root, root);
			break;
		case 2: //na kraj
			ERROR_CODE = InsertNode(root, NULL);
			break;
		case 3: //iza elementa
		{
			osoba target = Find(root);
			if (target == NULL) 
			{
				ERROR_CODE = ERROR_ELEMENT_NOT_FOUND;
				break; 
			}
			ERROR_CODE = InsertNode(root, target);
			break;
		}
		case 4: //Ispred elementa
		{
			osoba target = FindPrevTo(root, Find(root));
			if (target == NULL) {
				ERROR_CODE = ERROR_ELEMENT_NOT_FOUND;
				break;
			}
			ERROR_CODE = InsertNode(root, target);
			break;
		}
		case 5: //pronadji
		{
			osoba target = Find(root);
			if (target == NULL)
				ERROR_CODE = ERROR_ELEMENT_NOT_FOUND;
			ERROR_CODE = ReadNode(target);
			getchar();
			puts("\nPress ENTER to continue...");
			getchar();
			break;
		}
		case 6: //delete
			ERROR_CODE = DeleteNode(root, Find(root));
			break;
		case 7: //Ispisi listu
			ERROR_CODE = ReadList(root);
			break;
		case 8: //write to file
			printf("Zelite li zapisati od pocetka [d/n]: ");
			scanf(" %c", &tempC);
			if (tempC == 'd' || 'D')
				ERROR_CODE = WrtiteToFile(root->next);
			else if (tempC == 'n' || 'N')
				ERROR_CODE = WrtiteToFile(Find(root));
			else
			{
				puts("Bad entry\n");
				break;
			}
			break;
		case 9: //read from file
			ERROR_CODE = ReadFromFile(root);
			break;
		case 10: //Sort
			ERROR_CODE = Sort();
			break;
		case 11: //Clear
			ERROR_CODE = ClearList(root);
			break;
		case 0: //exit
			ClearList(root);
			break;
		default:
			printf("heu heu hue heu ehue heu ehu eh ueheu heu heu heu\n");
			_sleep(3000);
		}
		if (Catch(ERROR_CODE) < 0)
			return 0;
		Jump();
	}
}