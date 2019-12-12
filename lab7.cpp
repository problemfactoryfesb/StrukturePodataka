#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
/*
Napisati program koji iz datoteke èita postfiks izraz i zatim korištenjem stoga raèuna
rezultat. Stog je potrebno realizirati preko vezane liste.
*/


typedef struct cvor CV;
typedef struct cvor * pos;

struct cvor {
	int br;
	pos next;
};

int Calc(int, int, char*, int*);
int push(pos, int);
int pop(pos, int*);
int ReadFromFile(char*, pos);
int DeleteStack(pos);
pos CreateNew();
int print(pos);

int main() {
	CV S;
	S.next = NULL;
	char ime[1024];

	printf("Unesi ime datoteke u kojoj je postfix izraz:\n");
	scanf("%s", ime);

	ReadFromFile(ime, &S);

	//ispis cijelog stoga, ako je sve proslo ok na stogu ce ostat samo rezutat
	print(S.next);

	return 0;
}

int Calc(int op1, int op2, char* op, int* result) {

	// op1 i op2 su brojevi, op je string u koji je spremljena operacija, a result je varijabla u koju cemo spremit rjesenje
	switch (*op) {
	case '+':
		*result = op1 + op2;
		return 0;
		break;
	case '-':
		*result = op1 - op2;
		return 0;
		break;
	case '*':
		*result = op1 * op2;
		return 0;
		break;
	case '/':
		if (op2 != 0) {
			*result = op1 / op2;
			return 0;
		}
		else {
			printf("Gresak! Nije moguce djeliti s 0");
			return 1;
		}
		break;
	default:
		printf("Greska! Nepoznata operacija.\n");
		return 1;
		break;
	}
}

int push(pos P, int op) {
	//prima pocetak stoga i broj koji treba ubacit
	pos q;

	//kreiram novu strukturu
	q = CreateNew();
	if (q != NULL) {

		//ako se alocirala memorija u strukturu upisujem broj i stavim ga na pocetak liste tj na vrh stoga
		q->br = op;
		q->next = P->next;
		P->next = q;
		return 0;
	}
	else {
		printf("greska u alociranju memorije\n");
		return 1;
	}
}

int pop(pos P, int* op) {
	//prima pocetak liste tj vrh stoga i varijablu u koju spremamo broj koji skinemo sa stoga
	pos tmp;

	if (P->next != NULL) {
		//ako postoji prvi clan ulazim u if
		tmp = P->next;
		//spremim vrijednost koja je bila na vrhu 
		*op = tmp->br;
		//povezem head sa drugim clanom i prvi izbrisem
		P->next = tmp->next;
		free(tmp);
		return 0;
	}
	else {
		printf("Greska! Prazan stog\n");
		return 1;
	}

}


int ReadFromFile(char* fileName, pos P) {
	//prima pokazivac na pocetak stringa i pocetak liste
	FILE * f;
	char buff[10];
	int op, op1, op2, result;

	//sve elemente niza postavljam na 0
	memset(buff, 0, 10);
	f = fopen(fileName, "r");

	if (f != NULL) {
		while (!feof(f)) {
			//dok ne dodjemo do kraja filea citam stringove i upisujem ih u buffer
			fscanf(f, "%s", buff);
			if (sscanf(buff, "%d", &op) > 0) {
				//iz buffer pokusam izvuc int ako uspijem sscanf vraca poz vrijednost i spremi je u op
				//na vrh stoga dodam procitani broj
				push(P, op);
				//printf("%d\n", op);
			}
			else {
				//kad sscanf vrati br manji ili jednak 0 to nije int pa mora bit operacija
				//sa vrha stoga skidam dva broja, zadnji ide u op2, a predzadnji u op1
				pop(P, &op2);
				pop(P, &op1);
				//saljem dva broja, operaciju(u bufferu) i adresu varijable u koju spremim rezultat operacije
				Calc(op1, op2, buff, &result);
				//printf("%d %s %d = %d\n", op1, buff, op2, result);
				//na vrh stoga stavim rezlutat
				push(P, result);
			}
		}
	}
	else {
		printf("greska! Neuspjesno otvaranje datoteke\n");
		return 1;
	}
}

int DeleteStack(pos P) {
	pos tmp = NULL;
	//trazim predzadnji element da izbrisem zadnji
	//ako nema ni prvog elementa u listi ispisem "Prazan stog.\n"

	if (P->next != NULL) {
		if (P->next->next != NULL) {
			//nije predzadnji pa idem dalje
			DeleteStack(P->next);
		}
		else
			//P je predzadnji element, pa brisem zadnji
			tmp = P->next;
		P->next = NULL;
		free(tmp);
		return 0;
	}
	else {
		printf("Prazan stog.\n");
		return 1;
	}
}

int print(pos L) {
	//ispis liste

	while (L != NULL) {
		printf("%d ", L->br);
		L = L->next;
	}
	printf("\n\n");

	return 0;
}

pos CreateNew() {
	pos q;
	q = (pos)malloc(sizeof(CV));
	return q;
}
