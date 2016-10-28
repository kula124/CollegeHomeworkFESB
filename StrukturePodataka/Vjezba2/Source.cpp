#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Helper.h"
#include <conio.h>
#include <ctype.h>


int main()
{
	int exitflag = 0;
	optr root = NULL;
	root = CreateElement("\n", " \n", 0);
	int choise = 1;
	while (choise)
	{
		printf("***********************************\n");
		printf("***********************************\n");
		printf("***************IZBORNIK************\n");
		printf("***********************************\n");
		printf("***********************************\n");
		printf("1) Dodaj element na pocetak\n");
		printf("2) Dodaj element na kraj\n");
		printf("3) Pronadji element(e) po prezimenu\n");
		printf("4) Izbrisi element(e) po prezimenu\n");
		printf("5) Ispisi listu\n");
		printf("6) Zapisi u file\n");
		printf("7) Procitaj iz filea\n");
		printf("0) Izlaz\n\n");
		printf("Izbor:   ");
		scanf(" %d", &choise);
		switch (choise)
		{
		case 1:
		{
			char name[NAME_LENGHT], lname[NAME_LENGHT];
			int god;
			printf("Unesite ime: ");
			scanf(" %s", &name);
			printf("Unesite prezime: ");
			scanf(" %s", &lname);
			printf("Unesite god rodjenja: ");
			scanf(" %d", &god);
			printf(Catch(AddToBegining(root, name, lname, god), &exitflag));
			if (exitflag < 0)
			{
				//free
				return exitflag;
			}
			exitflag = 0;
			printf("\nPress anykey to continue...");
			getch();
			printf("\n\n\n\n\n\n\n\n\n\n");
			break;
		}
		case 2:
		{
			char name[NAME_LENGHT], lname[NAME_LENGHT];
			int god;
			printf("Unesite ime: ");
			scanf(" %s", &name);
			printf("Unesite prezime: ");
			scanf(" %s", &lname);
			printf("Unesite god rodjenja: ");
			scanf(" %d", &god);
			printf(Catch(AddToEnd(root, name, lname, god), &exitflag));
			if (exitflag < 0)
			{
				//free
				return exitflag;
			}
			exitflag = 0;
			printf("\nPress anykey to continue...");
			getch();
			printf("\n\n\n\n\n\n\n\n\n\n");
			break;
		}
		case 3:
		{
			char confirm, name[NAME_LENGHT];
			optr* f = NULL;
			int FindAll, i = 0;
			printf("Unesie prezime koje trazite: ");
			scanf(" %s", &name);
			printf("Zelite li pronaci sve osobe s tim prezimenom? [d]a/[n]e: ");
			scanf(" %c", &confirm);
			if (confirm == 'd' || confirm == 'D')
				FindAll = 1;
			else if (confirm == 'n' || confirm == 'n')
				FindAll = 0;
			else
			{
				printf("Pogresan izbor (d->da n->ne)\n");
				break;
			}
			printf(Catch(FindElements(root, &f, name, &FindAll), &exitflag));
			if (exitflag != OK)
				break;
			printf("Indx\tIme\tPrezime\t\tGod\n");
			while (i < FindAll)
			{
				printf("[%d]\t", i + 1);
				ShowElement(f[i++]);
			}
			exitflag = 0;
			printf("\nPress anykey to continue...");
			getch();
			printf("\n\n\n\n\n\n\n\n\n\n");
			break;
		}
		case 4:
		{
			char confirm, name[NAME_LENGHT];
			optr* f = NULL;
			int FindAll, i = 0;
			printf("Unesie prezime koje trazite: ");
			scanf(" %s", &name);
			printf("Zelite li izbrisati sve osobe s tim prezimenom? [d]a/[n]e: ");
			scanf(" %c", &confirm);
			if (confirm == 'd' || confirm == 'D')
				FindAll = 1;
			else if (confirm == 'n' || confirm == 'n')
				FindAll = 0;
			else
			{
				printf("Pogresan izbor (d->da n->ne)\n");
				break;
			}
			printf(Catch(FindElements(root, &f, name, &FindAll), &exitflag));
			if (exitflag != OK)
				break;
			while (i < FindAll)
			{
				Delete(root, f[i++]);
			}
			exitflag = 0;
			printf("\nPress anykey to continue...");
			getch();
			printf("\n\n\n\n\n\n\n\n\n\n");
			break;
		}
		case 5:
			ShowList(root);
			printf("\nPress anykey to continue...");
			getch();
			printf("\n\n\n\n\n\n\n\n\n\n");
			break;
		case 6 :
		{
			char path[NAME_LENGHT * 2];
			printf("Unesite filepath: ");
			scanf(" %s", &path);
			printf(Catch(WriteToFIle(root, path),&exitflag));
			printf("\nPress anykey to continue...");
			getch();
			printf("\n\n\n\n\n\n\n\n\n\n");
			break;
		}
		case 7 :
		{
			char path[NAME_LENGHT * 2], c;
			int append = -1;
			printf("Unesite filepath: ");
			scanf(" %s", &path);
			printf("Dodati podatke na postojecu listu? [d/n]: ");
			scanf(" %c", &c);
			if (c == 'd' || c == 'D')
				append = 1;
			else if (c == 'n' || c == 'n')
				append = 0;
			printf(Catch(ReadFile(root, path,append), &exitflag));
			printf("\nPress anykey to continue...");
			getch();
			printf("\n\n\n\n\n\n\n\n\n\n");
			break;
		}
		case 0:
			printf("byeee");
			ClearList(root);
			free(root);
			break;
		default:
			printf("Krivi izbor, 0-5");
			printf("\nPress anykey to continue...");
			getch();
			printf("\n\n\n\n\n\n\n\n\n\n");
			break;
		}
	}
	return OK;
}