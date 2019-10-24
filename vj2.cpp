#define _CRT_SECURE_NO_WARNINGS
#define MAX 128
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Definirati strukturu osoba (ime, prezime, godina rođenja) i napisati program koji:
a) dinamički dodaje novi element na početak liste,
b) ispisuje listu,
c) dinamički dodaje novi element na kraj liste,
d) pronalazi element u listi (po prezimenu),
e) briše određeni element iz liste,
f) dinamički dodaje novi element iza određenog elementa,
g) dinamički dodaje novi element ispred određenog elementa,
h) sortira listu po prezimenima osoba,
i) upisuje listu u datoteku,
j) čita listu iz datoteke.
U zadatku se ne smiju koristiti globalne varijable.*/

struct osoba{
	char ime[MAX];
	char prez[MAX];
	int god;
	struct osoba * Next;
};

typedef struct osoba OS;
typedef struct osoba * pos;

pos CreateNew();
int Insert(pos);
int Print(pos);
int InsertEnd(pos);
pos FindPrez(pos);
int Delete(pos);
int InsertAfter(pos);
int InsertBefore(pos);
int GetList(pos);
int SaveList(pos);	
int Sort(pos);

int main(){
	char izbor='\0';
	OS head;
	head.Next = NULL;

	while(izbor!='k'){
		printf("Izaberite zeljenu radnju:\n");
		printf("\ta) dodaj elemen na pocetak\n");
		printf("\tb) dodaj elemen na kraj\n");
		printf("\tc) trazi element po prezimenu\n");
		printf("\td) brisi element\n");
		printf("\te) ispisi listu\n");
		printf("\tf) dodaj element iza nekog clana\n");
		printf("\tg) dodaj element ispred nekog clana\n");
		printf("\th) sortiraj listu po prezimenu\n");
		printf("\ti) citaj listu iz datoteke\n");
		printf("\tj) upisi listu u datoteku\n");
		printf("\tk) izlaz\n");
		
		//scanf(" %[^\n]", &izbor);
		scanf(" %c", &izbor);
		
		switch(izbor){
			case 'a':
				Insert(&head);
				break;
			case 'b':
				InsertEnd(&head);
				break;
			case 'c':
				FindPrez(head.Next);
				break;
			case 'd':
				Delete(&head);
				break;
			case 'e':
				Print(head.Next);
				break;
			case 'f':
				InsertAfter(&head);
				break;
			case 'g':
				InsertBefore(&head);
				break;
			case 'h':
				Sort(&head);
				break;
			case 'i':
				GetList(&head);
				break;
			case 'j':
				SaveList(head.Next);
				break;
			case 'k':
				printf("izlaz iz programa");
				break;
			default:
				printf("greska! nije izbarana valjana radnja\n");
				break;
		}
	}
	
	return 0;
}

pos CreateNew(){
	pos q=NULL;
	q=(pos)malloc(sizeof(OS));
	q->Next = NULL;
	return q;
}

int Insert(pos p){
	
	pos q = NULL;
	q = CreateNew();
	if(q==NULL){
		printf("greka u alokaciji memorije!\n");
		return 0;
	}
	else{
		printf("unesi ime i prezime te god rodjenja\n");
		scanf("%s %s %d", q->ime, q->prez, &q->god);
		q->Next = p->Next;
		p->Next = q;
		return 1;
	}
}

int Print(pos p){
	if(p==NULL){
		printf("prazna lista\n");
		return 0;
	}
	else{
		while(p!=NULL){
			printf("%s %s %d\n", p->ime, p->prez, p->god);
			p=p->Next;
		}
		return 1;
	}
	
}

int InsertEnd(pos p){
	int tmp;
	while(p->Next!=NULL)
		p=p->Next;
	tmp = Insert(p);
	if(tmp == 0)
		return 0;
	else
		return 1;
}

pos FindPrez(pos p){
	char pr[20];
	
	printf("Unesi prezime koje trazis:\n");
	scanf("%s", pr);
	
	while(p!=NULL && strcmp(pr, p->prez)!=0){
		p=p->Next;
	}
	
	if(p==NULL){
		printf("niije pronadjeno trazeno prezime\n");
		return NULL;
	}
	else{
		printf("Trazena osoba:\n%s %s %d\n", p->ime, p->prez, p->god);
		return p;
	}
}

pos FindPrev(pos p){
	char pr[20];
	
	printf("Unesi prezime koje trazis:\n");
	scanf("%s", pr);
	
	while(p->Next!=NULL && strcmp(pr, p->Next->prez)!=0){
		p=p->Next;
	}
	
	if(p->Next==NULL)
		printf("nije pronadjeno trazeno prezime\n");
	else
		printf("Trazena osoba:\n%s %s %d\n", p->Next->ime, p->Next->prez, p->Next->god);
	
	return p;
}

int Delete(pos p){
	pos tmp;
	
	p = FindPrev(p);
	
	if (p==NULL)
		return 0;
	else{
		tmp = p->Next;
		p->Next=p->Next->Next;
		free(tmp);
		return 1;
	}
}

int InsertAfter(pos p){
	int tmp;
	p = FindPrez(p);
	
	tmp = Insert(p);
	if (p==NULL)
		return 0;
	else
		return 1;
}

int InsertBefore(pos p){
	int tmp;
	p = FindPrev(p);
	
	tmp = Insert(p);
	if (p==NULL)
		return 0;
	else
		return 1;
}

int Sort(pos p){
	pos i, j, prev_j, end, tmp;
	
	end = NULL;
	i = p;
	
	while(i->Next != end){
		prev_j = i;
		j = i->Next;
			while(j->Next != end){
				if(strcmp(j->prez, j->Next->prez)>0){
					tmp = j->Next;
					j->Next = tmp->Next;
					tmp->Next = j;
					prev_j->Next = tmp;
					j = tmp;	
				}
				prev_j = j;
				j = j->Next;
			}
		end = j;
	}
	
	return 1;
}

int GetList(pos p){
	FILE * f;
	char tmp[255];
	pos q;
	
	printf("unesi ime datoteke iz koje se citaju podaci\n");
	scanf(" %s", tmp);
	f = fopen(tmp, "r");
	
	if(f == NULL){
		printf("neuspjesno otvaranje datoteke\n");
		return 0;
	}
	
	else{
		while(!feof(f)){
			q = CreateNew();
			if(q==NULL)
				printf("neuspjesno stvaranje novog clana\n");
			else{
				fscanf(f, "%s %s %d\n", q->ime, q->prez, &q->god);
				q->Next = NULL;
				p->Next = q;
				p = q;
			}
		}
		fclose(f);
		return 1;
	}
}

int SaveList(pos p){
	FILE * f;
	char tmp[255];
	pos q;
	
	printf("unesi ime datoteke u koju se spremaju podaci\n");
	scanf(" %s", tmp);
	f = fopen(tmp, "w");
	
	if(f == NULL){
		printf("neuspjesno otvaranje datoteke\n");
		return 0;
	}
	else{
		while(p!=NULL){
			if(p->Next != NULL)
				fprintf(f, "%s %s %d\n", p->ime, p->prez, p->god);
			else
				fprintf(f, "%s %s %d", p->ime, p->prez, p->god);
			p = p->Next;
		}
		
		fclose(f);
		return 1;
	}
}