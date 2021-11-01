#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct _Person;
typedef struct _Person* Position;
typedef struct _Person {
	char name[50];
	char lastName[50];
	int birthYear;
	Position next;
}Person;



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
		return -1;
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

	return EXIT_SUCCESS;;
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

	return EXIT_SUCCESS;
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
	    printf("Name: %s, Last name: %s, Birth year: %d \n",
             temp->name, temp->lastName, temp->birthYear);
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

    return <EXIT_SUCCESS;
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

int main(int argc, char** argv)
{
	Person head = { .next = NULL, .name = {0}, .lastName = {0}, .birthYear = 0 };
	Position p = &head;
	Position temp = NULL;
	char name1[] = "name1";
	char lastName1[] = "F_lastName1";
	int birthYear1 = 1991;
	char name2[] = "name2";
	char lastName2[] = "A_lastName2";
	int birthYear2 = 1992;
	char name3[] = "name3";
	char lastName3[] = "B_lastName3";
	int birthYear3 = 1993;
    char name4[] = "name4";
	char lastName4[] = "Z_lastName4";
	int birthYear4 = 1994;
	char name5[] = "name5";
	char lastName5[] = "E_lastName5";
	int birthYear5 = 1995;

	printf("Sorted input: \n");
    sortedInput(p, name4, lastName4, birthYear4);
    sortedInput(p, name2, lastName2, birthYear2);
    sortedInput(p, name3, lastName3, birthYear3);
    sortedInput(p, name1, lastName1, birthYear1);
    printList(p->next);
    printf("\n");

    printf("Adding element to beggining and end of list:\n ");
    prependList(p, name5, lastName5, birthYear5);
    appendList(p, name5, lastName5, birthYear5);
    printList(p->next);
    printf("\n");

    printf("New sorted list:\n");
    bubbleSort(p);
    printList(p->next);
    printf("\n");

    printf("Finding element by last name (Z_lastName4):\n");
    temp = findByLastName(p->next, lastName4);
    printList(temp);
    printf("\n");

    printf("Deleting element from list (B_lastName3): \n");
    deleteElement(p, lastName3);
    printList(p->next);
    printf("\n");

    printf("Writing list to file and reading list from file:\n");
    writeInFIle(p->next);
    readFIle("datoteka2.txt", p);
    printList(p->next);

	return EXIT_SUCCESS;
}
