#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct stog;
typedef struct stog * st;
struct stog {
	int broj;
	st next;
};

int random();
st CreateNew();
int ispis(st);
int push(st);
int pop(st);
int pushRed(st);

int main()
{
	int pr, izbor = 12;
	struct stog head;
	head.next = NULL;

	while (izbor != 0)
	{
		printf("\t0 - izlaz iz programa \n\t1 - Ispis \n\t2 - Insert \n\t3 - Delete \n\n");
		printf("Izbor: ");
		scanf(" %d", &izbor);

		switch (izbor)
		{
		case 0:
			printf("Izlaz iz programa\n");
			break;

		case 1:
			printf("U stogu se nalazi: ");
			pr = ispis(head.next);
			if (pr == -1) printf("Lista je prazna!\n");
			break;

		case 2:
			pr = push(&head);
			if (pr == -1) printf("Greska!\n");
			break;

		case 3:
			pr = pop(&head);
			if (pr == -1) printf("Greska!!!\n");
			break;

		default:
			printf("Nein\n");
			break;
		}
		printf("\n\n");
	}
	return 0;
}

int random()
{
	int x;
	srand((unsigned)time(NULL));
	x = rand() % (100 - 10 + 1) + 10;
	return x;
}

st CreateNew()
{
	st q = NULL;
	q = (struct stog *) malloc(sizeof(struct stog));
	if (q == NULL) return NULL;

	return q;
}

int ispis(st S)
{
	if (S == NULL) return -1;
	while (S != NULL)
	{
		printf(" %d", S->broj);
		S = S->next;
	}
	return 0;
}

int push(st S)
{
	st q = NULL;
	q = CreateNew();
	if (q == NULL) return -1;

	q->broj = random();

	q->next = S->next;
	S->next = q;

	return 0;
}

int pop(st S)
{

	struct stog * temp;
	if (S->next == NULL) return -1;

	temp = S->next;
	S->next = temp->next;
	free(temp);

	return 0;

