#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME (128)
#define MEMORY_DIDNT_ALLOCATE_ERROR (-1)
#define CAN_NOT_OPEN_FILE_ERROR (-2)

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
int InsertAfter(StudentP student, StudentP newStudent, char* surname);
int InsertBefore(StudentP student, StudentP newStudent, char* surname);
int Sort(StudentP student);
int WriteToFile(char* filename, StudentP student);
int ReadFromFile(char* filename, StudentP student);
int InsertSort(StudentP student, StudentP head);

int main()
{
	Student Head = { .name = {0}, .surname = {0}, .birthYear = 0, .next = NULL };
	StudentP p = &Head;
	StudentP found = NULL;
	StudentP newStudent = NULL;

	int choice = 1;
	char name[MAX_NAME] = { 0 };
	char surname[MAX_NAME] = { 0 };
	char newSurname[MAX_NAME] = { 0 };
	int birthYear = 0;


	printf("----------MENI---------\n");
	printf("Tipka 1 - Unos elementa na pocetak liste\n");
	printf("Tipka 2 - Unos elementa na kraj liste\n");
	printf("Tipka 3 - Ispis liste\n");
	printf("Tipka 4 - Pronalazak elementa po prezimenu\n");
	printf("Tipka 5 - Brisanje elementa iz liste\n");
	printf("Tipka 6 - Unos iza nekog elementa\n");
	printf("Tipka 7 - Unos ispred nekog elementa\n");
	printf("Tipka 8 - Sortiranje liste\n");
	printf("Tipka 9 - Unos podataka u datoteku\n");
	printf("Tipka 10 - Ispis podataka iz datoteke\n");
	printf("Tipka 11 - Sortiran unos studenata\n");
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

			found = (StudentP)malloc(sizeof(Student));

			found = FindBySurname(p, surname);
			printf("Pronadeni element je roden %d i zove se %s \n", found->birthYear, found->name);
			break;
		case 5:
			printf("Unesite prezime studenta kojeg zelite izbrisati\n");
			scanf(" %s", surname);

			DeleteStudent(p, surname);
			printf("Stuent izbrisan iz liste \n");
			break;

		case 6:
			printf("Unesite prezime studenta iza kojeg zelite unjeti novi clan\n");
			scanf(" %s", surname);

			printf("Unesite ime studenta:\n");
			scanf(" %s", name);
			printf("Unesite prezime studenta:\n");
			scanf(" %s", surname);
			printf("Unesite godinu rodjenja studenta:");
			scanf(" %d", &birthYear);

			newStudent = createStudent(name, surname, birthYear);

			InsertAfter(p,newStudent, surname);
			break;

		case 7:
			printf("Unesite prezime studenta ispred kojeg zelite unjeti novi clan\n");
			scanf(" %s", surname);

			printf("Unesite ime studenta:\n");
			scanf(" %s", name);
			printf("Unesite prezime studenta:\n");
			scanf(" %s", newSurname);
			printf("Unesite godinu rodjenja studenta:");
			scanf(" %d", &birthYear);

			newStudent = createStudent(name, newSurname, birthYear);

			InsertBefore(p, newStudent, surname);
			break;

		case 8:
			Sort(p);
			break;

		case 9:

			WriteToFile("Studenti.txt", p);
			break;

		case 10:

			ReadFromFile("Studenti.txt", p);
			break;

		case 11:

			printf("Unesite ime studenta:\n");
			scanf(" %s", name);
			printf("Unesite prezime studenta:\n");
			scanf(" %s", surname);
			printf("Unesite godinu rodjenja studenta:");
			scanf(" %d", &birthYear);

			newStudent = createStudent(name, surname, birthYear);
			InsertSort(newStudent, p);
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
		student = student->next;
		printf(" %s %s %d\n", student->name, student->surname, student->birthYear);
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

	StudentP foundStudent = student->next;

	if (!foundStudent) {
		printf("Lista je prazna\n");
		return NULL;
	}

	while (foundStudent != NULL && (strcmp(foundStudent->surname, surname) != 0))
		foundStudent = foundStudent->next;


	return foundStudent;
}

StudentP FindBefore(StudentP student, char* surname) {
	StudentP prevStudent = NULL;
	prevStudent = student;
	student = student->next;


	while (student != NULL && (strcmp(student->surname, surname) != 0)) {
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

int InsertAfter(StudentP student,StudentP newStudent, char* surname) {


	while (student->next != NULL && (strcmp(student->surname, surname) != 0))
		student = student->next;

	if (student == NULL) {
		printf("Student ne postoji!\n");
		return EXIT_FAILURE;
	}

	newStudent->next = student->next;
	student->next = newStudent;



	return EXIT_SUCCESS;


}

int InsertBefore(StudentP student, StudentP newStudent, char* surname) {

	if (student->next == NULL) {
		printf("Lista je prazna\n");
		return EXIT_FAILURE;
	}

	while (student->next != NULL && (strcmp(student->next->surname, surname) != 0))
		student = student->next;

	newStudent->next = student->next;
	student->next = newStudent;

	return EXIT_SUCCESS;

}

int Sort(StudentP student) {
	StudentP student1 = NULL;
	StudentP student2 = NULL;
	StudentP temp = NULL, end = NULL;

	while (student->next != end) {
		student1 = student;
		student2 = student->next;

		
			while (student2->next != end) {
				
				if (strcmp(student2->surname, student2->next->surname) > 0) {

					temp = student2->next;
					student1->next = temp;
					student2->next = temp->next;
					temp->next = student2;

					student2 = temp;

				}

				student1 = student2;
				student2 = student2->next;
			}

			end = student2;
		
	}
	
	
	return EXIT_SUCCESS;
}

int WriteToFile(char* filename, StudentP student) {
	FILE* fp = NULL;
	StudentP temp = NULL;
	temp = student->next;

	fp = fopen(filename, "w");

	if (!fp) {
		printf("Can not open file\n");
		return CAN_NOT_OPEN_FILE_ERROR;
	}

	while (temp) {
		fprintf(fp, "Name: %-15s Surname: %-15s Birth year: %d\n", temp->name, temp->surname, temp->birthYear);
		temp = temp->next;
	}


	fclose(fp);

	printf("Podaci uspjesno uneseni u datoteku\n");

	return EXIT_SUCCESS;
}

int ReadFromFile(char* filename, StudentP student) {
	FILE* fp = NULL;
	fp = fopen(filename, "r");

	char name[MAX_NAME] = { 0 };
	char surname[MAX_NAME] = { 0 };
	int birthYear = 0;
	
	StudentP temp = NULL;
	temp = student->next;

	if (!fp) {
		printf("Can not open file\n");
		return CAN_NOT_OPEN_FILE_ERROR;
	}

	while (!feof(fp)) {
		fscanf(fp, " %s %s %d\n", name, surname, &birthYear);
		PrependList(student, name, surname, birthYear);

	}

	fclose(fp);

	return EXIT_SUCCESS;
}

int InsertSort(StudentP student, StudentP head) {

	StudentP temp = NULL;
	temp = head;
	

	if (head->next == NULL) 
		PrependList(head, student->name, student->surname, student->birthYear);
	else {

		while (temp->next != NULL) {

			if (strcmp(student->surname, temp->next->surname) > 0) {

				temp = temp->next;
			}
			else if (strcmp(student->surname, temp->next->surname) < 0) {
				InsertAfter(head, student, temp->surname);
				break;

			}

			if (temp == NULL) {
				AppendList(head, student->name, student->surname, student->birthYear);
			}
		}

	}
	
	return EXIT_SUCCESS;
}




