#include <stdio.h>
#include <time.h>
#include <stdlib.h>

/*
Napisati program koji pomoæu vezanih listi simulira rad:
a) stoga,
b) reda.
Napomena: Funkcija "push" sprema cijeli broj, sluèajno generirani u opsegu od 10 -100
*/

typedef struct cvor CV;
typedef struct cvor * pos;

struct cvor{
	int el;
	pos next;
};

pos CreateNew();
int RandomNumber();
int push(pos);
int print(pos);
int popR(pos);
int popS(pos);

int main(){
	CV R, S;
	char c='\0';
	R.next = NULL;
	S.next = NULL;

	srand(time(NULL));

	while(c!='g'){
		printf("Izbornik:\n\ta)Dodaj u red\n\tb)Izbaci iz reda\n\tc)Dodaj na stog\n\td)Izbaci sa stoga\n\te)Ispis reda\n\tf)Ispis stoga\n\tg)Izlaz\n");
		scanf(" %c", &c);
		switch(c){
		case 'a':
			push(&R);
			break;
		case 'b':
			popR(&R);
			break;
		case 'c':
			push(&S);
			break;
		case 'd':
			popS(&S);
			break;
		case 'e':
			printf("\nRed:\n");
			print(R.next);
			break;
		case 'f':
			printf("\nStog:\n");
			print(S.next);
			break;
		default:
			break;
		} 
	
	}

	return 0;
}

int RandomNumber(){
	return rand()%91+10;
}

pos CreateNew(){
	pos q;
	q=(pos)malloc(sizeof(CV));
	return q;
}

int push(pos R){
	pos q;

	q=CreateNew();
	if(q!=NULL){
		q->el = RandomNumber();
		q->next = R->next;
		R->next = q;
		return 1;
	}
	else{
		printf("greska u alokaciji memorije");
		return 0;
	}
}

int popR(pos R){
	int br;
	pos q;

	if(R->next != NULL){
		while(R->next->next != NULL)
			R=R->next;

		q=R->next;
		br= q->el;
		R->next=NULL;
		free(q);
		return br;
	}
	else{
		printf("Red je prazan\n");
		return 0;
	}

}

int popS(pos S){
	int br;
	pos q;

	if(S->next!=NULL){
		q=S->next;
		br = q->el;
		S->next = q->next;
		free(q);
		return br;
	}
	else{
		printf("stog je prazan\n");
		return 0;
	}
}

int print(pos L){

	while(L!=NULL){
		printf("%d ", L->el);
		L=L->next;
	}
	printf("\n\n");

	return 0;
}