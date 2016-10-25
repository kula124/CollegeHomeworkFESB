#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Helper.h"
#include <conio.h>
#include <ctype.h>


int main()
{
	int exitflag = 0;
	osoba root = NULL;
	root = CreateElement("\n", " \n", -1);
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
		printf("3) Dodaj iza elementa\n");
		printf("4) Pronadji element(e) po prezimenu\n");
		printf("5) Izbrisi element(e) po prezimenu\n");
		printf("6) Ispisi listu\n");
		printf("7) Zapisi u file\n");
		printf("8) Procitaj iz filea\n");
		printf("9) Sortiraj list\n");
		printf("10) Ocisti listu\n");
		printf("0) Izlaz\n\n");
		printf("Izbor:   ");
		scanf(" %d", &choise);
		switch (choise)
		{
		case 1:
		{
			printf(Catch(Insert(root,root), &exitflag));
			if (exitflag < 0)
			{
				ClearList(root);
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
			printf(Catch(Insert(root,NULL), &exitflag));
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
			if (!root->next)
			{
				printf("Lista je prazna...\n");
				printf("\nPress anykey to continue...");
				getch();
				printf("\n\n\n\n\n\n\n\n\n\n");
				break;
			}
			char confirm, name[NAME_LENGHT], lname[NAME_LENGHT];
			int god, i = 0;
			printf("Unesie ime koje trazite: ");
			scanf(" %s", &name);
			printf("Unesie ime koje trazite: ");
			scanf(" %s", &lname);
			printf("Unesie godiste osobe: ");
			scanf(" %d", &god);
			printf("Je ste li sigurni [d]a/[n]e: ");
			scanf(" %c", &confirm);
			confirm = tolower(confirm);
			while (confirm!= 'd' && confirm!= 'n')
				printf("Pogresan izbor (d->da n->ne)\n");
			if (confirm == 'n')
				break;
			printf(Catch(Insert(root, Find(root, name, lname, god)), &exitflag));
			exitflag = 0;
			printf("\nPress anykey to continue...");
			getch();
			printf("\n\n\n\n\n\n\n\n\n\n");
			break;
		}
		case 4:
		{
			if (!root->next)
			{
				printf("Lista je prazna...\n");
				printf("\nPress anykey to continue...");
				getch();
				printf("\n\n\n\n\n\n\n\n\n\n");
				break;
			}
			char confirm, name[NAME_LENGHT], lname[NAME_LENGHT];
			int god, i = 0;
			printf("Unesie ime koje trazite: ");
			scanf(" %s", &name);
			printf("Unesie ime koje trazite: ");
			scanf(" %s", &lname);
			printf("Unesie godiste osobe: ");
			scanf(" %d", &god);
			printf("Je ste li sigurni [d]a/[n]e: ");
			scanf(" %c", &confirm);
			confirm = tolower(confirm);
			while (confirm != 'd' && confirm != 'n')
				printf("Pogresan izbor (d->da n->ne)\n");
			if (confirm == 'n')
				break;
			ShowElement(Find(root, name, lname, god));
			exitflag = 0;
			printf("\nPress anykey to continue...");
			getch();
			printf("\n\n\n\n\n\n\n\n\n\n");
			break;
		}
		case 5:
		{
			if (!root->next)
			{
				printf("Lista je prazna...\n");
				printf("\nPress anykey to continue...");
				getch();
				printf("\n\n\n\n\n\n\n\n\n\n");
				break;
			}
			char confirm, name[NAME_LENGHT], lname[NAME_LENGHT];
			int god, i = 0;
			printf("Unesie ime koje trazite: ");
			scanf(" %s", &name);
			printf("Unesie ime koje trazite: ");
			scanf(" %s", &lname);
			printf("Unesie godiste osobe: ");
			scanf(" %d", &god);
			printf("Je ste li sigurni [d]a/[n]e: ");
			scanf(" %c", &confirm);
			confirm = tolower(confirm);
			while (confirm != 'd' && confirm != 'n')
				printf("Pogresan izbor (d->da n->ne)\n");
			if (confirm == 'n')
				break;
			printf(Catch(Delete(root, Find(root, name, lname, god)),&exitflag));
			exitflag = 0;
			printf("\nPress anykey to continue...");
			getch();
			printf("\n\n\n\n\n\n\n\n\n\n");
			break;
		}
		case 6:
			printf(Catch(ShowList(root),&exitflag));
			printf("\nPress anykey to continue...");
			getch();
			printf("\n\n\n\n\n\n\n\n\n");
			break;
		case 7:
		{
			if (!root->next)
			{
				printf("Lista je prazna...\n");
				printf("\nPress anykey to continue...");
				getch();
				printf("\n\n\n\n\n\n\n\n\n\n");
				break;
			}
			char path[NAME_LENGHT * 2], ap='0', start;
			int app = FALSE;
			printf("Unesite filepath: ");
			scanf(" %s", &path);
			printf("Zelite li poceti s odredjenim elementom? [d/n=root]: ");
			scanf(" %c", &start);
			osoba p = NULL;
			start = tolower(start);
			while (start != 'd' && start != 'n')
				printf("Pogresan izbor (d->da n->ne)\n");
			if (start == 'd')
			{
				char confirm, name[NAME_LENGHT], lname[NAME_LENGHT];
				int god = 0;
				printf("Unesie ime koje trazite: ");
				scanf(" %s", &name);
				printf("Unesie ime koje trazite: ");
				scanf(" %s", &lname);
				printf("Unesie godiste osobe: ");
				scanf(" %d", &god);
				p = Find(root, name, lname, god);
				if (!p)
				{
					printf(Catch(ERROR_ELEMENT_NOT_FOUND, &exitflag));
					p = root;
				}
			}
			else
				p = root;
			printf("Zelite li dodati elemente na postojuce u file-u [d/n] : ");
			scanf(" %c", &ap);
			ap = tolower(ap);
			while (ap != 'd' && ap != 'n')
				printf("Pogresan izbor (d->da n->ne)\n");
			ap == 'd' ? app = TRUE: app = FALSE;
			printf(Catch(WriteFile(p, path, app), &exitflag));
			printf("\nPress anykey to continue...");
			getch();
			printf("\n\n\n\n\n\n\n\n\n\n");
			break;
		}
		case 8:
		{
			char path[NAME_LENGHT * 2], c;
			int append = FALSE;
			printf("Unesite filepath: ");
			scanf(" %s", &path);
			if (root->next)
			{
				printf("Dodati podatke na postojecu listu? [d/n]: ");
				scanf(" %c", &c);
				c = tolower(c);
				while (c != 'd' && c != 'n')
					printf("Pogresan izbor (d->da n->ne)\n");
				c == 'd' ? append = TRUE : append = FALSE;
			}
			printf(Catch(ReadFilev2(root, path, append), &exitflag));
			printf("\nPress anykey to continue...");
			getch();
			printf("\n\n\n\n\n\n\n\n\n\n");
			break;
		}
		case 9:
		{
			if (!root->next)
			{
				printf("Lista je prazna...\n");
				printf("\nPress anykey to continue...");
				getch();
				printf("\n\n\n\n\n\n\n\n\n\n");
				break;
			}
			double time = 0;
			printf("Sortiraj po parametru: \n");
			int c, c1;
			char uz;
			printf("[%d] Ime\n",NAME);
			printf("[%d] Prezime\n",LNAME);
			printf("[%d] Godiste\n",BORN);
			printf("Izbor:\t");
			scanf(" %d", &c1);
			printf("[U]zlazno/[S]ilazno: ");
			scanf(" %c", &uz);
			uz = tolower(uz);
			if (uz != 'u' && uz != 's')
			{
				printf("Krivi izbor\n");
				break;
			}
			printf("Sortiraj po:\n");
			printf("[%d] Quick Sort\n",METHOD_QSRT);
			printf("[%d] Bubble sort\n",METHOD_BUBBLE);
			printf("Izbor:\t");
			scanf(" %d", &c);
			printf(Catch(Sort(root, c1, c, &time, uz),&exitflag));
			break;
		}
		case 10:
			printf(Catch(ClearList(root),&exitflag));
			printf("\nPress anykey to continue...");
			getch();
			printf("\n\n\n\n\n\n\n\n\n\n");
			break;
		case 0:
			printf("byeee");
			ClearList(root);
			free(root);
			break;
		default:
			printf("Krivi izbor, 0-9");
			printf("\nPress anykey to continue...");
			getch();
			printf("\n\n\n\n\n\n\n\n\n\n");
			break;
		}
	}
	return OK;
}