#define _CRT_SECURE_NO_WARNINGS
#define NAME_BUFFER_LENGTH 128
#include <stdio.h>
#include <stdlib.h>
/*
-Napisati program koji prvo proèita koliko redaka ima datoteka, tj. koliko ima studenata
zapisanih u datoteci. Nakon toga potrebno je dinamièki alocirati prostor za niz struktura
studenata (ime, prezime, bodovi) i uèitati iz datoteke sve zapise. Na ekran ispisati ime,
prezime,apsolutni i relativni broj bodova.
Napomena: Svaki redak datoteke sadrži ime i prezime studenta, te broj bodova na kolokviju.
relatvan_br_bodova = br_bodova/max_br_bodova*100
*/

struct student {
	char ime[NAME_BUFFER_LENGTH];
	char prez[NAME_BUFFER_LENGTH];
	int bodovi;
};

typedef struct student STUD;

int redaka(char *);
STUD * niz(int);
int ucitaj(STUD *, char *);
void ispis(STUD *, int, int);

int main(int arg, char ** argc) {
	STUD * p;
	int max, n;

if (arg < 1) {
		printf("\n Nije unesena datoteka !");
	}
else {
	n = redaka(argc[1]);
	p = niz(n);
	max = ucitaj(p, argc[1]);
	ispis(p, n, max);
	ucitaj(niz(redaka(argc[1])), argc[1]);


}
//free(p);
	return 0;
}

int redaka(char * dat) {
	FILE * f;
	int n = 0;

	f = fopen("Source1.txt", "r");

	if (f == NULL) {
		printf("\nNije otvorena datoteka!");
		exit(0);
	}

	while (!feof(f)) {
		if (fgetc(f) == '\n')
			n++;
	}

	fclose(f);

	n++;

	printf("Broj redaka %d\n", n);
	return n;
}

STUD * niz(int n) {
	STUD * p;

	p = (STUD *)malloc(n * sizeof(STUD));

	if (p == NULL)
		printf("\ngreska pri alociranju memorije");

	return p;
}

int ucitaj(STUD * p, char * dat) {
	FILE * f;
	int i = 0, max = 0;

	f = fopen("Source1.txt", "r");

	if (f == NULL) {
		printf("\nNije otvorena datoteka!");
		exit(0);
	}

	while (!feof(f)) {
		fscanf(f, "%s %s %d", p[i].ime, p[i].prez, &p[i].bodovi);
		if (p[i].bodovi > max)
			max = p[i].bodovi;
		i++;
	}

	fclose(f);
	return max;
}

void ispis(STUD * p, int n, int max) {
	int i;

	printf("ime\tprezime\taps br bodova\trel br bod\n");
	for (i = 0; i < n; i++) {
		printf("%s\t%s\t%5d\t\t%f\n", p[i].ime, p[i].prez, p[i].bodovi, (float)p[i].bodovi / max * 100);
	}
}