/* unija i presjek */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

struct _list;
typedef struct _list *Pos;
typedef struct _list _LIST; //pokazivac na strukturu _list

struct _list {
	int br;
	Pos next;
};

Pos CreateNew();
int Ispis(Pos);
int IspisIzDat(Pos);
int Unija(Pos, Pos, Pos);
int Presjek(Pos, Pos, Pos);


int main()
{
	_LIST L1, L2, Un, Pr; //head-ovi
	L1.next = L2.next = Un.next = Pr.next = NULL;
	int pr = 100, x = 0;

	while (pr != 0)
	{
		printf("\n1 - Ispis iz datoteke u prvu listu");
		printf("\n2 - Ispis iz datoteke u drugu listu");
		printf("\n3 - Ispis dviju lista");
		printf("\n4 - Ispis unija lista");
		printf("\n5 - Ispis presjeka lista");
		printf("\n0 - Izlaz");

		printf("\n\nUpisi svoj izbor: ");
		scanf("%d", &pr);
		printf("\n");

		switch (pr)
		{
		case 1:
			x = IspisIzDat(&L1);
			if (x == -1) printf("Greska!\n");
			break;
		case 2:
			IspisIzDat(&L2);
			if (x == -1) printf("Greska!\n");
			break;
		case 3:
			printf("Prva lista:\n");
			x = Ispis(L1.next);
			if (x == -1) printf("Prva lista je prazna!\n");

			printf("Druga lista:\n");
			x = Ispis(L2.next);
			if (x == -1) printf("Druga lista je prazna!\n");
			break;
		case 4:
			printf("Unija:\n");
			x = Unija(L1.next, L2.next, &Un);
			if (x == -1) printf("Greska!!\n");
			Ispis(Un.next);
			break;
		case 5:
			printf("Presjek:\n");
			x = Presjek(L1.next, L2.next, &Pr);
			if (x == -1) printf("Greska!!\n");
			Ispis(Pr.next);
			break;
		case 0:
			printf("Izlaz iz programa...\n");
			break;
		default:
			printf("Pogresan unos!!!\n");
			break;
		}
	}
	return 0;
}

Pos CreateNew()
{
	Pos q = NULL;
	q = (Pos)malloc(sizeof(_LIST));
	if (q == NULL) return q;

	q->next = NULL;

	return q;
}

int Ispis(Pos P)
{
	if (P == NULL) return -1;

	while (P != NULL)
	{
		printf(" %d", P->br);
		P = P->next;
	}
	printf("\n");
	return 0;
}

int IspisIzDat(Pos P)
{
	FILE * dat = NULL;
	char str[20];
	Pos q, Pocetak;
	q = NULL;
	Pocetak = P;

	printf("Upisi ime datoteke: ");
	scanf(" %s", str);

	dat = fopen(str, "r");
	if (dat == NULL) return -1;

	while (!feof(dat))
	{
		q = CreateNew();
		if (q == NULL) return -1;
		fscanf(dat, "%d", &q->br);

		while (P->next != NULL && P->next->br < q->br)
			P = P->next;

		q->next = P->next;
		P->next = q;
		P = Pocetak;
	}
	fclose(dat);
	return 0;
}

int Unija(Pos P1, Pos P2, Pos R)
{
	Pos q = NULL, Pocetak = P1, PocetakR = R;

	if (P1 == NULL && P2 == NULL) return -1;

	while (P1 != NULL) //prepise se prva lista
	{
		q = CreateNew();
		if (q == NULL) return -1;
		q->br = P1->br;

		q->next = R->next;
		R->next = q;
		R = q;

		P1 = P1->next;
	}

	R = PocetakR;

	while (P2 != NULL) //svaki element od druge liste usporedujemo sa svakim od prve i ako je razlicit od svih upisujemo sortirano :)
	{
		P1 = Pocetak;
		while (P1 != NULL && P1->br != P2->br)
		{
			P1 = P1->next;
		}

		if (P1 == NULL) //ako smo dosli do kraja, znaci da nema ponavljanja i treba prepisat clan iz L2
		{
			q = CreateNew();
			if (q == NULL) return -1;
			q->br = P2->br;

			while (R->next != NULL && R->next->br < q->br)
				R = R->next;
			q->next = R->next;
			R->next = q;
			R = PocetakR;
		}

		P2 = P2->next; //ako smo naletili na isti clan, samo krenemo na iduci u L2
	}
	return 0;
}

int Presjek(Pos P1, Pos P2, Pos R)
{
	Pos q = NULL;
	while (P1 != NULL && P2 != NULL)
	{
		if (P1->br > P2->br)
			P2 = P2->next;
		else if (P1->br < P2->br)
			P1 = P1->next;
		else
		{
			q = CreateNew();
			if (q == NULL) return -1;
			q->br = P1->br;

			q->next = R->next;
			R->next = q;
			R = q;
			P1 = P1->next;
			P2 = P2->next;
		}
	}
	return 0;
}
