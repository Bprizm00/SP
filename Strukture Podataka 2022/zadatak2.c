#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME (128)
#define MEMORY_DIDNT_ALLOCATE_ERROR (-1)

struct student_;
typedef struct student_* StudentP;
typedef struct student_ {

	char name[MAX_NAME];
	char surname[MAX_NAME];
	int birthYear;
	StudentP next;

} Student;

StudentP createStudent(char* name, char* surname, int birthYear);
int PrependList(StudentP student, char* name, char* surname, int birthYear);
void PrintList(StudentP student);
int AppendList(StudentP student, char* name, char* surname, int birthYear);
StudentP FindBySurname(StudentP student, char* surname);
int DeleteStudent(StudentP student, char* surname);
StudentP FindBefore(StudentP student, char* surname);

int main()
{	
	Student Head={.name = {0}, .surname = {0}, .birthYear = 0, .next = NULL};
	StudentP p = &Head;

	int choice = 1;
	char name[MAX_NAME] = { 0 };
	char surname[MAX_NAME] = { 0 };
	int birthYear = 0;
	

		printf("----------MENI---------\n");
	printf("Tipka 1 - Unos elementa na pocetak liste\n");
	printf("Tipka 2 - Unos elementa na kraj liste\n");
	printf("Tipka 3 - Ispis liste\n");
	printf("Tipka 4 - Pronalazak elementa po prezimenu\n");
	printf("Tipka 5 - Brisanje elementa iz liste\n");
	printf("Tipka 0 - Prekid programa\n");

	while (choice != 0) {

		scanf("%d", &choice);

		switch (choice)
		{
		case 0:
			printf("Program prekinut!\n");
			break;

		case 1:
			printf("Unesite ime studenta:\n");
			scanf(" %s", name);
			printf("Unesite prezime studenta:\n");
			scanf(" %s", surname);
			printf("Unesite godinu rodjenja studenta:");
			scanf("%d", &birthYear);

			PrependList(p, name, surname, birthYear);
			printf("Student uspjesno dodan na pocetak liste!");
			break;

		case 2:
			printf("Unesite ime studenta:\n");
			scanf(" %s", name);
			printf("Unesite prezime studenta:\n");
			scanf(" %s", surname);
			printf("Unesite godinu rodjenja studenta:");
			scanf(" %d", &birthYear);

			AppendList(p, name, surname, birthYear);
			printf("Student uspjesno dodan na kraj liste!");
			break;

		case 3:
			PrintList(p);
			break;

		case 4:
			printf("Unesite prezime studenta kojeg trazite\n");
			scanf(" %s", surname);

			FindBySurname(p, surname);
			break;
		case 5:
			printf("Unesite prezime studenta kojeg zelite izbrisati\n");
			scanf(" %s", surname);

			DeleteStudent(p, surname);
			printf("Stuent izbrisan iz liste \n");
			break;

		}
	}



	

	return 0;
}

StudentP createStudent(char* name, char* surname, int birthYear)
{
	StudentP newElement = NULL;

	newElement = (StudentP)malloc(sizeof(Student));

	if (!newElement)
	{
		printf("Can not allocate memmory! \n");
		return NULL;
	}

	strcpy(newElement->name, name);
	strcpy(newElement->surname, surname);
	newElement->birthYear = birthYear;
	newElement->next = NULL;

	return newElement;
}

int PrependList(StudentP student, char* name, char* surname, int birthYear)
{
	StudentP newStudent = NULL;

	newStudent = (StudentP)malloc(sizeof(Student));

	if (!newStudent)
	{
		printf("Can not allocate memory\n");
		return MEMORY_DIDNT_ALLOCATE_ERROR;
	}
	else
		newStudent = createStudent(name, surname, birthYear);

	newStudent->next = student->next;
	student->next = newStudent;

	return EXIT_SUCCESS;
}

void PrintList(StudentP student)
{
	while (student->next != NULL) {
		printf(" %s %s %d", student->name, student->surname, student->birthYear);
		student = student->next;
	}
}

int AppendList(StudentP student, char* name, char* surname, int birthYear)
{
	StudentP newStudent = NULL;

	newStudent = (StudentP)malloc(sizeof(Student));

	if (!newStudent) {
		printf("Can not allocate memory\n");
		return MEMORY_DIDNT_ALLOCATE_ERROR;
	}
	else
		newStudent = createStudent(name, surname, birthYear);

	while (student->next != NULL) {
		student = student->next;
	}

	newStudent->next = student->next;
	student->next = newStudent;

	return EXIT_SUCCESS;
}

StudentP FindBySurname(StudentP student, char* surname) {

	StudentP foundStudent = student;

	while (foundStudent != NULL && (strcmp(foundStudent->surname, surname) == 0))
		foundStudent = foundStudent->next;


	return foundStudent;
}

StudentP FindBefore(StudentP student, char* surname) {
	StudentP prevStudent = NULL;
	prevStudent = student;
	student = student->next;


	while (student != NULL && (strcmp(student->surname, surname) == 0)) {
		prevStudent = prevStudent->next;
		student = student->next;
	}

	if (student == NULL)
		return NULL;


	return prevStudent;
}

int DeleteStudent(StudentP student, char* surname) {
	StudentP prevStudent = NULL;
	StudentP temp = NULL;

	prevStudent = FindBefore(student, surname);

	if (!prevStudent) {
		printf("Student does not exist\n");
		return EXIT_FAILURE;
	}
	else {
		temp = prevStudent->next;
		prevStudent->next = prevStudent->next->next;
		free(temp);
	}


	return EXIT_SUCCESS;
}


