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

int findByLastName(Position first, char* lastName)
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
	Position before = findBefore(temp, lastName);

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

int main(int argc, char** argv)
{
	Person head = { .next = NULL, .name = {0}, .lastName = {0}, .birthYear = 0 };
	Position p = &head;
	Position temp = NULL;
	char name1[] = "ime1";
	char lastName1[] = "prezime1";
	int birthYear1 = 1991;
	char name2[] = "ime2";
	char lastName2[] = "prezime2";
	int birthYear2 = 1992;

  prependList(p, name1, lastName1, birthYear1);
  appendList(p, name2, lastName2, birthYear2);
	printList(p->next);
  printf("\n");

  temp = findByLastName(p->next, lastName2);
  printList(temp);
  printf("\n");

  deleteElement(p, lastName2);
  printList(p->next);

	return EXIT_SUCCESS;
}
