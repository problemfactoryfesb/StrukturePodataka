/*
Napisati program koji iz datoteke èita postfiks izraz i zatim stvara stablo proraèuna. Iz
gotovog stabla proraèuna upisati u datoteku infiks izraz.
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct cvor tree;
typedef struct cvor * pos;
typedef struct stog * ptr;

struct cvor{
	char el[12];
	pos L;
	pos R;
};

struct stog{
	ptr next;
	pos stablo;
};

int push(ptr, char*);
int pop(ptr, char*);
int getTree(char* , ptr);
int print(pos, FILE *);
pos CreateNewTreeNode();
ptr CreateNewStackNode();
int freeTree(pos);

int main(){
	ptr H, tmp;
	char fileName[255];
	FILE * out_file; //file u koji spremam na kraju

	H = (ptr)malloc(sizeof(struct stog)); //alociram mem. za head stoga
	H->next = NULL;
	H->stablo = NULL;

	printf("upisi ime filea: ");
	scanf("%s", fileName);
	getTree(fileName, H); //stvara stablo

	out_file = fopen("infix.txt", "w");

	//ako postoji clan na stogu u njemu je stablo
	//provjera da se dobro otvori file
	if(H->next!=NULL && out_file != NULL){
			printf("Infix izraz spremljen je u file infix.txt\n");
			print(H->next->stablo, out_file); //u file sprema stablo na kojeg pokazuje jedini clan na stogu
	}


	while(H != NULL && H->next != NULL ){
		tmp= H->next;
		H->next = tmp->next;
		freeTree(tmp->stablo);
		free(tmp);
	}

	free(H);
	fclose(out_file);

	return 0;
}

ptr CreateNewStackNode(){
	//stvara strukturu za na stog
	ptr q;
	q=(ptr)malloc(sizeof(struct stog));
	return q;
}
pos CreateNewTreeNode(){
	//stvara jedan cvor stabla
	pos q;
	q=(pos)malloc(sizeof(tree));
	return q;
}

//inorder ispis
int print(pos S, FILE * out_file){
	if(S==NULL)
		return 1;
	else{
		print(S->L, out_file);
		printf("%s ", S->el); //ispis na ekran
		fprintf(out_file, "%s ", S->el); //upisuje u datoteku
		print(S->R, out_file);
		return 0;
	}

}

//procitali smo broj iz datoteke
int push(ptr H, char* br){
	ptr q;
	q = CreateNewStackNode(); //stvaram novu strukturu za na stog

	//ako je alocirana memorija
	if(q!=NULL){
		q->next = H->next; //stavljam na pocetak liste(vrh stoga) i povezem
		H->next = q;
		q->stablo = CreateNewTreeNode(); //kreiram novi cvor stabla na koji pokazuje struktura sa stoga
		//ako je alocirana memorija
		if(q->stablo!=NULL){ 
			strcpy(q->stablo->el, br); //u el upisujem broj kao string
			q->stablo->L = NULL; //postavljam djecu na NULL
			q->stablo->R = NULL;
			return 0;
		}
		else return 1;
	}
	else return 1;
}
int pop(ptr H, char* op){
	pos q = CreateNewTreeNode();		//stvaram cvor stabla na koji pokazuje q
	ptr tmp;		//pointer na struct stog

	//ako je alocirana memorija
	if(q!=NULL){ 
		strcpy(q->el, op);		//kopiram operator u element cvora stabla
		if(H->next!=NULL){		//ako postoji nesto na stogu
			q->R = H->next->stablo;			//ono na sta struktura na vrhu stoga pokazuje postaje desno dijete operatora
			if(H->next->next!=NULL){		//ako postoji i druga struktura na stogu
				q->L = H->next->next->stablo;		//ono na sta druga struktura stoga pokazuje postaje lijevo dijete operatora
				tmp = H->next;		//moram prespojit prvi clan liste i obrisat ga
				H->next = tmp->next;
				free(tmp);
				H->next->stablo = q;
				return 0;
			}
			else return 1;
		}
		else return 1;
	}
	else return 1;
}

int getTree(char* fileName, ptr H){
	FILE * f;
	char buff[255];

	f = fopen(fileName, "r"); 
	//ako je uspjesno otvoren file
	if(f!=NULL){
		//sve dok ne dodjem do kraja
		while(!feof(f)){
			fscanf(f, "%s ", buff); //povlacim string po string(odvojeni " ")
			if(strcmp(buff, "+")==0 || strcmp(buff, "-")==0 || strcmp(buff, "*")==0 || strcmp(buff, "/")==0 ){
				//ako smo nasli operaciju ulazimo u pop
				pop(H, buff);
			}
			else
				push(H, buff); //ako smo nasli broj(ne operacija) ulazim u push tj. dodam novi element na stog
		}
		return 0;
	}
	else{
		printf("nije uspjesno otvoren file!\n");
		return 1;
	}
	fclose(f);
}

//oslobadjam dinamicki alociranu memoriju
int freeTree(pos S){
	if(S!=NULL ){
		freeTree(S->L); //ako ima lijevo brise ga, ako nema nista
		freeTree(S->R);	//ako ima desno brise ga, ako nema nista
		free(S); //obrisemo root podstabla
		return 0;
	}
	return 1;
}