#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "Helper.h"
#include <time.h>
int main()
{
	srand(time(NULL));
	osoba temp, root = NULL;
	root = CreateNode(CR8_ROOT);
	int Error_Code, choise = 1;
	while (choise)
	{
		printf("***********************************\n");
		printf("***********************************\n");
		printf("***************IZBORNIK************\n");
		printf("***********************************\n");
		printf("***********************************\n");
		printf("1) Dodaj element na pocetak\n");
		printf("2) Dodaj element na kraj\n");
		printf("3) Dodaj iza elementa\n");
		printf("4) Dodaj ispred elementa\n");
		printf("5) Pronadji element(e) po prezimenu\n");
		printf("6) Izbrisi element(e) po prezimenu\n");
		printf("7) Ispisi listu\n");
		printf("8) Zapisi u file\n");
		printf("9) Procitaj iz filea\n");
		printf("10) Sortiraj list\n");
		printf("11) Ocisti listu\n");
		printf("0) Izlaz\n\n");
		printf("Izbor:   ");
		scanf(" %d", &choise);
		switch (choise)
		{
		case 1:
			Error_Code = InsertNode(root, root);
			break;
		case 2:
			Error_Code = InsertNode(root, NULL);
			break;
		case 3:
			temp = Find(root);
			if (!temp) {
				Error_Code = ERROR_ELEMENT_NOT_FOUND;
				break;
			}
			Error_Code = InsertNode(root, temp);
			break;
		case 4:
			temp = FindPrevTo(root, Find(root));
			if (!temp) {
				Error_Code = ERROR_ELEMENT_NOT_FOUND;
				break;
			}
			Error_Code = InsertNode(root, temp);
			break;
		case 5:
			temp = Find(root);
			if (!temp) {
				Error_Code = ERROR_ELEMENT_NOT_FOUND;
				break;
			}
			Error_Code = PrintNode(temp);
			break;
		case 6:
			Error_Code = DeleteNode(root, Find(root));
			break;
		case 7:
			Error_Code = PrintList(root);
			break;
		case 8:
			Error_Code = WriteToFile(root);
			break;
		case 9:
			Error_Code = ReadFile(root);
			break;
		case 10:
			Error_Code = Sort();
			break;
		case 11:
			Clear(root);
			break;
		}
		if (CatchError(Error_Code) < 0)
			return Error_Code;
		printf("\n\n\n\n\n\n\n");
	}
	return OK;
}