#include <stdio.h>
#include <stdlib.h>

struct polinom{
	int Koef;
	int Pot;
	struct polinom * next;
};

typedef struct polinom poli;
typedef poli * pos;

int getlist(pos);
pos create();
int insert(pos, int, int);
int print(pos);
int suma(pos, pos, pos);
int produkt(pos, pos, pos);

int main(){
	//kreiram headove za sve liste koje trebam
	poli P1, P2, S, P;		
	
	P1.next = NULL;
	P2.next = NULL;
	S.next = NULL;
	P.next = NULL;

	getlist(&P1);
	printf("\nPrvi polinom\n");
	print(P1.next);
	
	getlist(&P2);
	printf("\nDrugi polinom\n");
	print(P2.next);

	suma(P1.next, P2.next, &S);
	printf("Zbroj polinoma\n");
	print(S.next);
	
	produkt(P1.next, P2.next, &P);
	printf("Umnozak polinoma\n");
	print(P.next);
	
	return 0;
}

int getlist(pos p){
	FILE * f;
	char dat[50];
	int koef, pot;

	printf("unesi ime dat\n");
	scanf(" %s", dat);
	f=fopen(dat,"r");
	if(f==NULL){
		printf("neuspjesno otvorena dat\n");
		return 0;
	}
	else{
		while(!feof(f)){ 
			fscanf(f,"%d %d", &koef, &pot);
			//ne zanimaju me clanovi s koef == 0
			if(koef != 0)		
				insert(p, koef, pot);
		}
		return 1;
	}

	fclose(f);
}

pos create(){
	pos q;

	q = (pos)malloc(sizeof(poli));

	if(q==NULL)
		printf("greska u alociranju memorije\n");
	else{
		q->Koef=0;
		q->Pot=0;
		q->next=NULL;
	}

	return q;
}

int insert(pos p, int koef, int pot){
	pos q;
	
	//trazim prethodni element
	while(p->next != NULL && pot < p->next->Pot)		
		p = p->next;

	//ako su iste pot ne stvaram novi el. nego samo zbrojim koef
	if(p->next != NULL && p->next->Pot == pot){		
		p->next->Koef += koef;
		return 1;
	}
	else{
		//stvaram novi el.
		q = create();		
		if(q==NULL)
			return 0;
		else{
			//spremim podatke u novi el
			q->Koef = koef;		
			q->Pot = pot;
			//povezem ga s ostatkom liste
			q->next = p->next;		
			p->next = q;
			return 1;
		}
	}
}

int print(pos p){

	while(p->next != NULL){
		printf("%dx^%d + ", p->Koef, p->Pot);
		p = p->next;
	}
	
	//zadnji element
	printf("%dx^%d\n\n", p->Koef, p->Pot);		

	return 1;
}


int suma(pos P1,pos P2, pos S){
	pos tmp;
	
	//dok ne dodjem do kraja jedne liste
	while(P1!=NULL && P2!=NULL){
		
		//ako nadjem dva clana sa istom potencijom 
		if(P1->Pot == P2->Pot){			
			S->next = create();
			if(S->next==NULL)
				return 0;
			//ako je zbroj 0 ne zanima me taj clan
			else if(P1->Koef + P2->Koef == 0){	
				//idem na iduce clanove
				P1 = P1->next;		
				P2 = P2->next;
				//brisem alociranu memoriju koju ne trebam
				free(S->next);		
				S->next = NULL;
			}
			else{
				//idem na sljedeci el sume na koji upisem podatke
				S = S->next;		
				S->Pot = P1 -> Pot;
				S->Koef = P1->Koef + P2->Koef;
				//idem na iduce clanove
				P1 = P1->next;		
				P2 = P2->next;
			}
		}
		//kad je prvi veci od drugog 
		else if(P1->Pot > P2->Pot){			
			S->next = create();
			if(S->next==NULL)
				return 0;
			else{
				S = S->next;
				//u sumu upisem samo veceg
				S->Pot = P1 -> Pot;		
				S->Koef = P1->Koef;
				//idem na sljedeci el 
				P1 = P1->next;		
			}
		}
		//kad je drugi veci od prvog
		else{		
			S->next = create();
			if(S->next==NULL)
				return 0;
			else{
				S = S->next;
				//u sumu upisem samo veceg
				S->Pot = P2 -> Pot;		
				S->Koef = P2->Koef;
				//idem na sljedeci el 
				P2 = P2->next;		
			}
		}
		
	}
	
	//ako p1 nije do kraja dosao
	if(P1 != NULL)		
		tmp = P1;
	//ako p2 nije do kraja dosao
	else
		tmp = P2; 		
	
	//dok nije kraj
	while(tmp != NULL){			
		S->next = create();
		if(S->next==NULL)
			return 0;
		else{
			S = S->next;
			//samo kopiram elemente u sumu
			S->Pot = tmp -> Pot;		
			S->Koef = tmp ->Koef;
			tmp = tmp->next;
		}
	}
	return 1;
	
}

int produkt(pos P1, pos P2, pos P){
	pos q = NULL, pocetak = P2, produkt = P;
	
	//mnozim svaki clan prve liste(vanjski while) sa svakim druge liste(unutarnji while)
	
	//dok ne dodjem do kraja prve liste
	while(P1 != NULL){ 
		//vracam se na pocetak lista
		P2 = pocetak; 		
		P = produkt;
		
		//dok ne dodjem do kraja prve liste
		while(P2 != NULL){		
			q = create();
			if(q == NULL)
				return 0;
			else{
				//spremim podaatke u novu strukturu
				q->Koef = P1->Koef * P2->Koef;		
				q->Pot = P1->Pot + P2->Pot;
				
				//trazim prethodni element u produktu
				while(P->next != NULL && q->Pot < P->next->Pot)		
					P=P->next;
					
				//ako nadjem istu potenciju samo zbrojim koef
				if(P->next != NULL && P->next->Pot == q->Pot){		
					P->next->Koef += q->Koef;
					//oslobodim alociranu memoriju koju ne trebam
					free(q); 		
				}
				else{
				//spojim el na odgovarajuce misto u produktu
				q->next = P->next;		
				P->next = q;
				}
			}
			//idem na iduci clan druge liste
			P2=P2->next;		
		}
		//idem na iduci clan prve liste
		P1=P1->next;		
	}

	return 1;
}