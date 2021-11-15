#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX_LINE (1024)

struct _Person;
typedef struct _Person* Position;
typedef struct _Person {
	char name[50];
	char lastName[50];
	int birthYear;
	Position next;
}Person;

int insertAfter(Position pos, Position newPerson);
Position createPerson(char* name, char* lastName, int birthYear);;
int sortedInput(Position head, char* name, char* lastName, int birthYear);
Position findLast(Position head);
int prependList(Position head, char* name, char* lastName, int birhYear);
int appendList(Position head, char* name, char* lastName, int birthYear);
Position findByLastName(Position first, char* lastName);
int printList(Position first);
Position findBefore(Position head, char* lastName);
int deleteElement(Position head, char* lastName);
int insertAfterElement(char* surname, Position first, char* name,
                       char* lastName,int birthYear);
int insertBeforeElement(char* surname, Position head, char* name,
                       char* lastName,int birthYear);
int bubbleSort(Position head);
int writeInFIle(Position first);
int readFIle(char* nameOfFile, Position head);
Position findByLastName(Position first, char* lastName);

int main(int argc, char** argv)
{
	Person head = { .next = NULL, .name = {0}, .lastName = {0}, .birthYear = 0 };
	char izbor;
	char ime[MAX_LINE] = { 0 };
    char prezime[MAX_LINE] = { 0 };
    char lastN[MAX_LINE] = { 0 };
	int godina = 0;
	while(1){
		printf("Unesi:\nP za unos na pocetak\nK za unos na kraj\nI za ispis\n"
         "F za trazi po prezimenu\nA za unos iza\nB za unos ispred\nU za unos liste u datoteku\n"
         "C za citaj listu iz datoteke\nS za sortiraj po prezimenu\nZ za sortirani unos\nD brisi\nX za izlaz\n");
		scanf(" %c", &izbor);
		if (izbor == 'P'){
            printf("Ime: ");
            scanf(" %s", ime);
            printf("Prezime: ");
            scanf(" %s", prezime);
            printf("Godina rodenja: ");
            scanf(" %d", &godina);
            prependList(&head, ime, prezime, godina);
		}
		else if (izbor == 'I'){
            printList(head.next);
		}
		else if (izbor == 'K'){
            printf("Ime: ");
            scanf(" %s", ime);
            printf("Prezime: ");
            scanf(" %s", prezime);
            printf("Godina rodenja: ");
            scanf(" %d", &godina);
            appendList(&head, ime, prezime, godina);
		}
        else if (izbor == 'F'){
            printf("Prezime osobe koju zelite pronaci: ");
            scanf(" %s", lastN);
            findByLastName(head.next, lastN);
		}
		else if (izbor == 'D'){
		    printf("Prezime osobe koju zelite obrisati: ");
            scanf(" %s", lastN);
            deleteElement(&head, lastN);
		}
		else if (izbor == 'Z'){
            printf("Ime: ");
            scanf(" %s", ime);
            printf("Prezime: ");
            scanf(" %s", prezime);
            printf("Godina rodenja: ");
            scanf(" %d", &godina);
            sortedInput(&head, ime, prezime, godina);
		}
		else if (izbor == 'A'){
		    printf("Prezime osobe iza koje zelite dodati: ");
            scanf(" %s", lastN);
            printf("Ime: ");
            scanf(" %s", ime);
            printf("Prezime: ");
            scanf(" %s", prezime);
            printf("Godina rodenja: ");
            scanf(" %d", &godina);
            insertAfterElement(lastN, &head, ime, prezime, godina);
		}
		else if (izbor == 'B'){
            printf("Prezime osobe iza koje zelite dodati: ");
            scanf(" %s", lastN);
            printf("Ime: ");
            scanf(" %s", ime);
            printf("Prezime: ");
            scanf(" %s", prezime);
            printf("Godina rodenja: ");
            scanf(" %d", &godina);
            insertBeforeElement(lastN, &head, ime, prezime, godina);
		}
		else if (izbor == 'S'){
            bubbleSort(&head);
		}
		else if (izbor == 'U'){
            writeInFIle(head.next);
		}
		else if (izbor == 'C'){
            readFIle("datoteka.txt", &head);
		}
		else if (izbor == 'X'){
            break;
		}
		else
			printf("Greska! Niste unijeli dobro slovo!\n");
	}

	return EXIT_SUCCESS;
}


int insertAfter(Position pos, Position newPerson)
{
	newPerson->next = pos->next;
	pos->next = newPerson;

	return EXIT_SUCCESS;
}

Position createPerson(char* name, char* lastName, int birthYear)
{
	Position newPerson = NULL;

	newPerson = (Position)malloc(sizeof(Person));
	if (!newPerson) {
		perror("Can't allocate memory! \n");
		return NULL;
	}

	strcpy(newPerson->name, name);
	strcpy(newPerson->lastName, lastName);
	newPerson->birthYear = birthYear;
	newPerson->next = NULL;

	return newPerson;
}

int sortedInput(Position head, char* name, char* lastName, int birthYear)
{
    Position newPerson = NULL;

    newPerson = createPerson(name, lastName, birthYear);
    if(!newPerson){
        perror("greska");
        return -1;
    }

	while (head->next != NULL && strcmp(head->next->lastName, newPerson->lastName) < 0)
		head = head->next;

	insertAfter(head, newPerson);

	return EXIT_SUCCESS;
}

Position findLast(Position head)
{
	Position temp = NULL;
	temp = head;

	while (temp->next!=NULL)
	{
		temp = temp->next;
	}
	return temp;
}

int prependList(Position head, char* name, char* lastName, int birhYear)
{
	Position newPerson = NULL;
	newPerson = createPerson(name, lastName, birhYear);
	if (!newPerson) {
		return -1;
	}
	insertAfter(head, newPerson);

	return 0;
}

int appendList(Position head, char* name, char* lastName, int birthYear)
{
	Position newPerson = NULL;
	Position last = NULL;
	newPerson = createPerson(name, lastName, birthYear);
	if (!newPerson) {
		return -1;
	}
	last = findLast(head);
	insertAfter(last, newPerson);

	return EXIT_SUCCESS;
}

Position findByLastName(Position first, char* lastName)
{
	Position temp = first;

	while (temp)
	{
		if (strcmp(temp->lastName, lastName) == 0) {

			return temp;
		}
		temp = temp->next;
	}

	return NULL;
}

int printList(Position first)
{
	Position temp = first;

	while(temp)
	{
	    printf("Name: %s, Last name: %s, Birth year: %d \n",temp->name, temp->lastName, temp->birthYear);
	    temp=temp->next;
	}

	return EXIT_SUCCESS;
}

Position findBefore(Position head, char* lastName)
{
	Position before = head;

	while (before) {
		if (strcmp(before->next->lastName, lastName) == 0) {
			return before;
		}
		before = before->next;
	}
	return NULL;
}
int deleteElement(Position head, char* lastName)
{
	Position temp = head;
	Position before = NULL;
	before = findBefore(temp, lastName);

	if (before == NULL)
	{
		perror("Ne postoji prezime\n");
		return -1;
	}

	temp = before->next;
	before->next = temp->next;
	free(temp);

	return EXIT_SUCCESS;
}

int insertAfterElement(char* surname, Position first, char* name,
                       char* lastName,int birthYear)
{
    Position element = NULL;
    element = findByLastName(first, surname);

    if(!element){
        printf("There is no person with this last name!");
    }
    else{
        Position newPerson = NULL;
        newPerson = createPerson(name, lastName, birthYear);

        if(!newPerson){
            perror("Greska");
        return -1;
        }

        insertAfter(element, newPerson);
        }
    return EXIT_SUCCESS;
}

int insertBeforeElement(char* surname, Position head, char* name,
                       char* lastName,int birthYear)
{
    Position newPerson = NULL;
    Position before = NULL;
    Position temp = head;

    before = findBefore(temp, surname);
    newPerson = createPerson(name, lastName, birthYear);
    if(!newPerson){
        perror("Greska");
        return -1;
    }
    if(before){
        insertAfter(before, newPerson);
    }

    return EXIT_SUCCESS;
}

int bubbleSort(Position head)
{
    Position previous = NULL;
    Position temp = NULL;
    Position current = NULL;
    Position last = NULL;

    while(head->next != last){
        previous = head;
        current = head->next;
        while(current->next != last){
            if(strcmp(current->lastName, current->next->lastName)>0)
            {
                temp = current->next;
                previous->next = temp;
                current->next = temp->next;
                temp->next = current;
                current=temp;
            }
            previous = current;
            current = current->next;
        }
        last = current;
    }

    return EXIT_SUCCESS;
}

int writeInFIle(Position first)
{
    FILE *fp = NULL;
    Position temp = first;

    fp = fopen("datoteka.txt", "w");
    if(fp == NULL){
        printf("Greska!");
        return -1;
    }
    while(temp){
        fprintf(fp, "%s \t %s \t %d \n", temp->name, temp->lastName,
                 temp->birthYear);
        temp = temp->next;
    }
    fclose(fp);
    free(temp);
    return EXIT_SUCCESS;
}

int readFIle(char* nameOfFile, Position head)
{
    char line[1024] = {0};
    FILE* fp = NULL;
    Position newElement = NULL;
    Position temp = head;

    fp = fopen(nameOfFile, "r");
    if(!fp){
        perror("Greska");
        return -1;
    }

    newElement = (Position)malloc(sizeof(Person));
    if (!newElement)
		{
			perror("Can't allocate memory!\n");
			return -1;
		}


    while(feof(fp)==0){
		fgets(line, 1024, fp);
		if (sscanf(line, " %s %s %d", newElement->name, newElement->lastName, &newElement->birthYear) == 3)
		{
			printf("name form file: %s, last name from file: %s, birth year from file %d\n", newElement->name, newElement->lastName, newElement->birthYear);
			sortedInput(temp, newElement->name, newElement->lastName, newElement->birthYear);
			temp = temp->next;
		}
    }
    fclose(fp);

    return EXIT_SUCCESS;
}
