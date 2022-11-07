#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_SIZE 24
#define CANNOT_ALLOCATE_MEMORY (-1);
#define CANNOT_OPEN_FILE (-2);

struct _poly;
typedef struct _poly* PolynomialP;
typedef struct _poly {
	int coefficient;
	int exponent;
	PolynomialP next;
}Polynomial;


int meni();
PolynomialP createPolynomial(int coefficient, int exponent);
int InsertSorted(PolynomialP head, PolynomialP newPolynomial);
int InsertAfter(PolynomialP head, PolynomialP newPolynomial, int exponent);
int InsertBefore(PolynomialP head, PolynomialP newPolynomial, int exponent);
int Append(PolynomialP head, PolynomialP newPolynomial);
int Prepend(PolynomialP head, PolynomialP newPolynomial);
int Print(PolynomialP head);
int AddPolynomials(PolynomialP polynomial1, PolynomialP polynomial2);
int MultiplyPolynomials(PolynomialP polynomial1, PolynomialP polynomial2);
int ReadFromFile(char* filename, PolynomialP polynomial1, PolynomialP polynomial2);
int DeallocateMemory(PolynomialP polynomial);

int main() {
	Polynomial head1 = { .coefficient = 0, .exponent = 0, .next = NULL };
	Polynomial head2 = { .coefficient = 0, .exponent = 0, .next = NULL };
	Polynomial resultMulti = { .coefficient = 0,.exponent = 0,.next = NULL };
	PolynomialP p1 = &head1;
	PolynomialP p2 = &head2;
	PolynomialP p = &resultMulti;
	PolynomialP newPolynomial = NULL;
	int coefficient = 0;
	int exponent = 0;
	int choice = 1;
	int i = 0, n = 0, m = 0;

	while (choice != 0) {

		meni();
		scanf(" %d", &choice);

		switch (choice) {

		case 1:
			printf("Koliko clanova ce imati vas 1. polinom?\n");
			scanf(" %d", &n);

			for (i = 0; i < n; i++) {
				printf("Unesite koeficijent: ");
				scanf(" %d", &coefficient);
				printf("Unesite exponent: ");
				scanf(" %d", &exponent);


				InsertSorted(p1, createPolynomial(coefficient, exponent));
			}

			printf("Koliko clanova ce imati vas 2. polinom?\n");
			scanf(" %d", &m);

			for (i = 0; i < m; i++) {
				printf("Unesite koeficijent: ");
				scanf(" %d", &coefficient);
				printf("Unesite exponent: ");
				scanf(" %d", &exponent);


				InsertSorted(p2, createPolynomial(coefficient, exponent));
			}

			break;
		case 2:
			ReadFromFile("Polinomi.txt", p1, p2);
			printf("Prvi polinom: ");
			Print(p1);
			printf("Drugi polinom: ");
			Print(p2);

			break;

		case 3: 
			printf("Rezultat zbrajanja polinoma je: ");

			AddPolynomials(p1, p2);
			break;

		case 4:
			printf("Rezultat mnozenja polinoma je: ");

			MultiplyPolynomials(p1, p2);

			break;

		case 5:
			printf("Prvi polinom: ");
			Print(p1);
			printf("Drugi polinom: ");
			Print(p2);
			break;

		}

	}

	DeallocateMemory(p1);
	DeallocateMemory(p2);

	return 0;
}

int meni() {

	printf("\n");
	printf("Tipka 1 - Sami unesite polinome \n");
	printf("Tipka 2 - Ucitajte polinome iz datoteke\n");
	printf("Tipka 3 - Zbrajanje polinoma\n");
	printf("Tipka 4 - Mnozenje polinoma\n");
	printf("Tipka 5 - Ispis liste\n");
	printf("Tipka 0 - Prekid programa\n");
	printf("Unesite vas izbor: ");

	return 0;
} 

PolynomialP createPolynomial(int coefficient, int exponent) {
	PolynomialP polynomial = NULL;

	polynomial = (PolynomialP)malloc(sizeof(Polynomial));

	if (!polynomial) {
		printf("Can not allocate memory\n");
		return CANNOT_ALLOCATE_MEMORY;
	}

	polynomial->coefficient = coefficient;
	polynomial->exponent = exponent;
	polynomial->next = NULL;


	return polynomial;
}

int InsertSorted(PolynomialP head, PolynomialP newPolynomial) {
	PolynomialP temp = NULL;
	PolynomialP temp2 = NULL;
	temp = head;
	PolynomialP same = NULL;
	if (head->next == NULL) {
		Prepend(head, newPolynomial);
	}

	else {

		while (temp->next != NULL) {
			if (newPolynomial->exponent < temp->next->exponent) {
				temp = temp->next;
			}
			else if (newPolynomial->exponent > temp->next->exponent) {
				InsertAfter(head, newPolynomial, temp->exponent);
				break;
			}
			else if (newPolynomial->exponent == temp->next->exponent) {
				
				same = createPolynomial(newPolynomial->coefficient + temp->next->coefficient, newPolynomial->exponent);
				InsertBefore(head, same, newPolynomial->exponent);
				temp2 = same->next;
				same->next = temp2->next;
				temp2->next = NULL;
				free(temp2);
				free(newPolynomial);
				break;
			}
		}

		if (temp->next == NULL) {
			Append(head, newPolynomial);
			
		}
	}
	return 0;
}

int InsertAfter(PolynomialP head, PolynomialP newPolynomial, int exponent) {

	if (head->next == NULL) {
		printf("Lista je prazna\n");
		return EXIT_FAILURE;
	}

	while (head->next != NULL && (head->exponent != exponent)) {
		head = head->next;
	}

	newPolynomial->next = head->next;
	head->next = newPolynomial;


	return EXIT_SUCCESS;
}

int InsertBefore(PolynomialP head, PolynomialP newPolynomial, int exponent) {

	PolynomialP temp = NULL;
	
	if (head->next == NULL) {
		printf("Lista je prazna\n");
		return EXIT_FAILURE;
	}

	temp = head->next;

	while (temp != NULL && newPolynomial->exponent < temp->next->exponent)
		temp = temp->next;

	InsertAfter(head, newPolynomial, temp->exponent);



	return EXIT_SUCCESS;
}

int Prepend(PolynomialP head, PolynomialP newPolynomial) {
	
	newPolynomial->next = head->next;
	head->next = newPolynomial;

	return EXIT_SUCCESS;
}

int Append(PolynomialP head, PolynomialP newPolynomial) {
	PolynomialP temp = NULL;

	temp = (PolynomialP)malloc(sizeof(Polynomial));

	temp = head;

	while (head->next != NULL) {
		head = head->next;
	}

	newPolynomial->next = head->next;
	head->next = newPolynomial;

	return EXIT_SUCCESS;
}

int Print(PolynomialP head) {
	PolynomialP temp = NULL;

	temp = head->next;

	while (temp != NULL) {

		printf(" %dx^(%d) ", temp->coefficient, temp->exponent);
		temp = temp->next;
	}

	printf("\n");

	return EXIT_SUCCESS;
}

int AddPolynomials(PolynomialP polynomial1, PolynomialP polynomial2) {
	Polynomial head = { .coefficient = 0, .exponent = 0, .next = NULL };
	PolynomialP p = &head;
	PolynomialP temp1 = polynomial1->next;
	PolynomialP temp2 = polynomial2->next;
	PolynomialP temp = NULL;


	while (temp1 != NULL && temp2 != NULL) {
		if (temp1->exponent == temp2->exponent) {
			InsertSorted(p, createPolynomial((temp1->coefficient + temp2->coefficient), temp2->exponent));
			temp1 = temp1->next;
			temp2 = temp2->next;
		}
		else if (temp1->exponent > temp2->exponent) {
			InsertSorted(p, createPolynomial(temp1->coefficient, temp1->exponent));
			temp1 = temp1->next;
		}
		else if (temp1->exponent < temp2->exponent) {
			InsertSorted(p, createPolynomial(temp2->coefficient,temp2->exponent));
			temp2 = temp2->next;
		}
	}

	while (temp1 != NULL) {
		InsertSorted(p, temp1);
		temp1 = temp1->next;
	}

	while (temp2 != NULL) {
		InsertSorted(p, temp2);
		temp2 = temp2->next;
	}

	return EXIT_SUCCESS;
}

int MultiplyPolynomials(PolynomialP polynomial1, PolynomialP polynomial2) {
	Polynomial head = { .coefficient = 0, .exponent = 0, .next = NULL };
	PolynomialP result = &head;
	PolynomialP temp1 = NULL;
	PolynomialP temp2 = NULL;
	PolynomialP newElement = NULL;
	PolynomialP temp = NULL;

	for (temp1 = polynomial1->next; temp1 != NULL; temp1 = temp1->next) {
		for (temp2 = polynomial2->next; temp2 != NULL; temp2 = temp2->next) {
			newElement = createPolynomial(temp1->coefficient * temp2->coefficient, temp1->exponent + temp2->exponent);
			InsertSorted(result, newElement);
		}
	}

	Print(result);


	return EXIT_SUCCESS;
}

int ReadFromFile(char* filename, PolynomialP polynomial1, PolynomialP polynomial2) {
	FILE* fp = NULL;
	PolynomialP newPolynomial = NULL;
	int coefficient = 0;
	int exponent = 0;
	char buffer[MAX_SIZE] = { 0 };
	char* tempBuffer = NULL;
	int n = 0;

	fp = fopen(filename, "r");

	if (!fp) {
		printf("Cannot open file\n");
		return CANNOT_OPEN_FILE;
	}

	fgets(buffer, MAX_SIZE, fp);
	tempBuffer = buffer;

	while (strlen(tempBuffer) > 0) {

		sscanf(tempBuffer, " %d %d %n", &coefficient, &exponent, &n);

		InsertSorted(polynomial1, createPolynomial(coefficient, exponent));
		
		tempBuffer += n;
	}

	fgets(buffer, MAX_SIZE, fp);
	tempBuffer = buffer;

	while (strlen(tempBuffer) > 0) {

		sscanf(tempBuffer, " %d %d %n", &coefficient, &exponent, &n);

		InsertSorted(polynomial2, createPolynomial(coefficient, exponent));

		tempBuffer += n;
	}



	fclose(fp);

	return EXIT_SUCCESS;
}

int DeallocateMemory(PolynomialP polynomial) {

	PolynomialP temp = NULL;
	
	while (polynomial->next != NULL) {
		temp = polynomial->next;
		polynomial->next = temp->next;
		temp->next = NULL;
		free(temp);
	}

	return EXIT_SUCCESS;
}