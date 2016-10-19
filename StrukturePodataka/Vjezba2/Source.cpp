#include "Helper.h"


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
			if (exitflag<0)
			{
				//free
				return exitflag;
			}
			exitflag = 0;
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
			if (exitflag<0)
			{
				//free
				return exitflag;
			}
			exitflag = 0;
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
			while (i<FindAll)
			{
				printf("[%d]\t", i+1);
				ShowElement(f[i++]);
			}
			exitflag = 0;
			break;
		}
		default:
			break;
		}
	}
	return OK;
}