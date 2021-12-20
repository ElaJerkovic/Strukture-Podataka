#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <time.h>

struct _binaryTree;
typedef struct _binaryTree* Position;
typedef struct _binaryTree{
    int element;
    Position Left;
    Position Right;
}binaryTree;

struct _list;
typedef struct _list* listPointer;
typedef struct _list{
    int element;
    listPointer next;
}list;

Position initializeBinaryTree(int elem);
Position addElement(int elem, Position root);
int Insert(Position root);
int inorderPrint(Position root, listPointer);
int replace(Position root);
listPointer converTreeToList(Position root);
int fileName(char* file_name);
int writeListToFile(listPointer head, char* nameOfFile);

int main()
{
    list head = { .element = 0, .next = NULL};
	  Position root = NULL, temp = NULL;;
	  int i = 0, x = 0;
	  int choice = 0, element = 0;
	  char* name = '\0';

    root = addElement(2, root);
    root = addElement(5, root);
    root = addElement(7, root);
    root = addElement(8, root);
    root = addElement(11, root);
    root = addElement(1, root);
    root = addElement(4, root);
    root = addElement(2, root);
    root = addElement(3, root);
    root = addElement(7, root);
    replace(root);

	do{
        	printf("\nChoose your option: \n1) add new element\n"
        	"2) inorder print to file\n"
        	"3) input random numbers in range: <10, 90>\n"
        	"4) stop\n");

        	scanf("%d", &choice);

       	 	switch (choice)
			    {
			        case 1:
				        printf("Enter number you want to insert: \n");
				        scanf("%d", &element);
                root = addElement(element, root);
                break;

              case 2:
                inorderPrint(root, &head);
                printList(head.next);
                writeListToFile(&head, "dat.txt");
				        break;
			        case 3:
				        Insert(root);
				        break;
              case 4:
				        break;
			        default:
				        printf("Wrong input!\n");
			    }

	}while(choice != 4);

	return 0;
}

Position initializeBinaryTree(int elem)
{
    Position newNode = (Position)malloc(sizeof(binaryTree));

    if(!newNode){
        perror("Can't allocate memory! \n");
        return NULL;
    }

    newNode->element = elem;
    newNode->Right = NULL;
    newNode->Left = NULL;
    return newNode;
}

Position addElement(int elem, Position root)
{
    if(!root)
        return initializeBinaryTree(elem);
    else if(elem < root->element)
        root->Right = addElement(elem, root->Right);
    else if(elem >= root->element)
        root->Left = addElement(elem, root->Left);
    return root;
}

int Insert(Position root)
{
    srand((unsigned) time(NULL));
    int element = 0;
    element = (rand() %(90 - 10 + 1)) + 10;
    printf("Random element is %d", element);
    root = addElement(element,root);
    return 0;
}

listPointer createElement(int element)
{
	listPointer newElement = NULL;

	newElement = (listPointer)malloc(sizeof(list));
	if (!newElement) {
		perror("Can't allocate memory! \n");
		return -1;
	}
	newElement->element = element;
	newElement->next = NULL;

	return newElement;
}

listPointer findLast(listPointer head)
{
	listPointer temp = NULL;
	temp = head;

	while (temp->next!=NULL)
	{
		temp = temp->next;
	}
	return temp;
}

int insertAfter(listPointer pos, listPointer newElement)
{
	newElement->next = pos->next;
	pos->next = newElement;

	return EXIT_SUCCESS;
}

int appendList(listPointer head, int element)
{
	listPointer newElement = NULL;
	listPointer last = NULL;
  
	newElement = createElement(element);
	if (!newElement) {
		return -1;
	}
  
	last = findLast(head);
	insertAfter(last, newElement);

	return EXIT_SUCCESS;
}

int printList(listPointer first)
{
	listPointer temp = first;

	while(temp)
	{
	    printf("%d ", temp->element);
	    temp=temp->next;
	}

	return EXIT_SUCCESS;
}

int inorderPrint(Position root, listPointer head)
{
	if (root)
	{
		inorderPrint(root->Left, head);
		appendList(head, root->element);
		inorderPrint(root->Right, head);
	}

	return 0;
}

int replace(Position root)
{
    int element = 0;

    if(root == NULL)
        return 0;

    else if(root->Left != NULL && root->Right != NULL){
        element = root->element;
        root->element = replace(root->Left) + replace(root->Right);
        return root->element + element;
    }

    else if (root->Left == NULL){
		  element = root->element;
		  root->element = replace(root->Right);
		  return root->element + element;
	  }

	  else if (root->Right == NULL){
		  element = root->element;
		  root->element = replace(root->Left);
		  return root->element + element;
	  }
  
	  else{
      element = root->element;
      root->element = 0;
      return root->element;
	}

}

int writeListToFile(listPointer head, char* nameOfFile)
{
    listPointer temp = head->next;
    FILE *fp = NULL;
    fp = fopen(nameOfFile, "a");
    if(!fp){
        printf("Can't open file!\n");
        return -1;
    }

    while(temp != NULL){
        fprintf(fp, "%d ", temp->element);
        temp = temp->next;
    }

    fclose(fp);
    return 0;
}
