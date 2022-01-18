#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_SIZE 128
#define MAX_LINE 1024

struct _List;
typedef struct _List* Position1;
typedef struct _List
{
	char name[MAX_SIZE];
	Position1 sibling;
	Position1 child;
}List;

struct _Stog;
typedef struct _Stog* Position2;
typedef struct _Stog
{
	Position1 directory;
	Position2 next;
}Stog;

Position1 MakeDir(char* name, Position1 current);
Position1 InsertDir(Position1 current, Position1 new);
int PushToStog(Position2 head, Position1 directory);
int PopFromStog(Position2 head);
Position2 FindLast(Position2 head);
Position2 FindBeforeLast(Position2 head);
Position1 ChangeDir(Position2 head, Position1 current, char* name);
int DisplayInformation(Position1 current);
int Exit(Position1 current);
int PrintCurrentDirectories(Position2 head);
int Menu(Position1 current, Position2 head);

int main()
{
	List root;
	Stog head;

	strcpy(root.name, "C:");
	root.child = NULL;
	root.sibling = NULL;

	head.directory = NULL;
	head.next = NULL;

	PushToStog(&head, &root);
	Menu(&root, &head);

	return 0;

}

Position1 MakeDir(char* name, Position1 current)
{
	Position1 newel = NULL;
	newel = (Position1)malloc(sizeof(List));
	if (!newel)
	{
		perror("Error: can't allocate!\n");
		return NULL;
	}

	strcpy(newel->name, name);

	newel->child = NULL;
	newel->sibling = NULL;

	current->child=InsertDir(current->child, newel);

	return current;
}

Position1 InsertDir(Position1 current, Position1 newel)
{
	if (current == NULL)
		return newel;

	else if (strcmp(current->name, newel->name) > 0)
	{
		newel->sibling = current;
		return newel;
	}
	else if (strcmp(current->name, newel->name) < 0)
	{
		current->sibling = InsertDir(current->sibling, newel);
	}
	else
	{
		printf("Error: there is a directory with same name!\n");
		free(newel);
	}
	return current;
}

int PushToStog(Position2 head, Position1 directory)
{
	Position2 newel = NULL;
	newel = (Position2)malloc(sizeof(Stog));
	if (!newel)
	{
		perror("Error: issue with allocation!\n");
		return -1;
	}
	Position2 last = FindLast(head);

	newel->next = last->next;
	last->next = newel;
	newel->directory = directory;

	return 0;
}

Position2 FindLast(Position2 head)
{
	Position2 temp = head;
	while (temp->next != NULL)
	{
		temp = temp->next;
	}

	return temp;
}

Position2 FindBeforeLast(Position2 head)
{
	Position2 temp = head;
	while (temp->next->next != NULL)
	{
		temp = temp->next;
	}

	return temp;
}

int PopFromStog(Position2 head)
{
	if (!head->next)
		return 0;

	Position2 before = FindBeforeLast(head);
	Position2 toDelete = NULL;

	toDelete = before->next;
	before->next = toDelete->next;
	free(toDelete);

	return 0;
}

Position1 ChangeDir(Position2 head, Position1 current,char* name)
{
	if (NULL == current->child)
	{
		printf("The system cannot find the path specified (current directory is empty).\n");
		return current;
	}
	else
	{
		Position1 temp = current->child;
		while (temp != NULL && strcmp(temp->name,name)!=0)
			temp = temp->sibling;

		if (temp == NULL)
		{
			printf("The system cannot find the path specified.\n");
			return current;
		}
		else
		{
			PushToStog(head, temp); //!!
			return temp;
		}
	}
}

int DisplayInformation(Position1 current)
{
	if (NULL == current->child)
	{
		printf("Directory is empty.\n");
	}
	else
	{
		Position1 temp = current->child;
		while (temp != NULL)
		{
			printf("<DIR>\t\t %s\n", temp->name);
			temp = temp->sibling;
		}
	}

	return 0;
}

int PrintCurrentDirectories(Position2 head)
{
	Position2 temp = head->next;

	while (temp!=NULL)
	{
		printf("%s\\", temp->directory->name);
		temp = temp->next;
	}
	printf(">");

	return 0;
}

int Menu(Position1 current, Position2 head)
{
	Position1 first = current;
	char name[MAX_LINE] = { 0 };
	char command[MAX_LINE] = { 0 };
	char line[MAX_LINE] = { 0 };
	printf("md- make directory\ncd- create directory"
         "\ncd..- go to parent directory"
         "\ndir- print the contents of the directory"
         "\nexit\n\n");

	while (1)
	{
		PrintCurrentDirectories(head);
		fgets(line, MAX_LINE, stdin);
		sscanf(line, "%s %s", command, name);

		if (strcmp(command, "md")==0)
		{
			current = MakeDir(name, current);
		}
		else if(strcmp(command, "cd")==0)
		{
			current=ChangeDir(head,current,name);
		}
		else if (strcmp(command, "cd..")==0)
		{
			PopFromStog(head);
			current = FindLast(head)->directory;
		}
		else if (strcmp(command, "dir")==0)
		{
			DisplayInformation(current);
		}
		else if (strcmp(command, "exit")==0)
		{
			return 0;
		}
		else
		{
			printf("'%s' command not recognized.\n", command);
		}
	}
	return 0;
}
