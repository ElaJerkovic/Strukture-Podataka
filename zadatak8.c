#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

struct _binaryTree;
typedef struct _binaryTree* Position;
typedef struct _binaryTree{
    int element;
    Position Left;
    Position Right;
}binaryTree;

Position initializeBinaryTree(int elem);
Position addElement(int elem, Position root);
int inorderPrint(Position root);
int postorderPrint(Position root);
int preorderPrint(Position root);
int depth(Position node);
int levelOrder(Position node, int level);
int printLevelOrder(Position root);
Position FindMin(Position root);
Position findElement(int element, Position root);
Position DeleteElement(int element, Position root);

int main()
{
	Position root = NULL, temp = NULL;;
	int i = 0;
	int choice = 0, element = 0;

	printf("Enter 5 numbers: \n");
	for(i = 0; i < 5; i++){
        scanf("%d", &element);
        root = addElement(element, root);
	}
	system("cls");

	do{
        	printf("\nChoose your option: \n1) add new element\n"
        	"2) delete element\n"
        	"3) inorder\n"
        	"4) preorder\n"
        	"5) postorder\n"
        	"6) level order\n"
        	"7) find element\n"
        	"8) stop\n");

        	scanf("%d", &choice);
        	system("cls");

       	 	switch (choice)
			{
			case 1:
				printf("Enter number you want to insert: \n");
				scanf("%d", &element);
				root = addElement(element, root);
				break;
			case 2:
		    		printf("Enter number you want to delete:\n");
				scanf("%d", &element);
				root = DeleteElement(element, root);
				break;
			case 3:
		    		inorderPrint(root);
				break;
			case 4:
				preorderPrint(root);
				break;
			case 5:
		    		postorderPrint(root);
				break;
			case 6:
				printLevelOrder(root);
				break;
			case 7:
				printf("Enter number you are searching for:\n");
				scanf("%d", &element);
				temp = findElement(element, root);
				if (temp)
					printf("Element %d is on adress %d\n", temp->element, temp);
				break;
        		case 8:
				break;
			default:
				printf("Wrong input!\n");
			}

	}while(choice != 8);

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
        root->Left = addElement(elem, root->Left);
    else if(elem > root->element)
        root->Right = addElement(elem, root->Right);
    return root;
}

int inorderPrint(Position root)
{
	if (root)
	{
		inorderPrint(root->Left);
		printf("%d ", root->element);
		inorderPrint(root->Right);
	}
	return 0;
}

int postorderPrint(Position root)
{
	if (root)
	{
		postorderPrint(root->Left);
		postorderPrint(root->Right);
		printf("%d ", root->element);
	}
	return 0;
}
int preorderPrint(Position root)
{
	if (root)
	{
		printf("%d ", root->element);
		preorderPrint(root->Left);
		preorderPrint(root->Right);
	}
	return 0;
}

int depth(Position node)
{
    int ldepth =  0;
    int rdepth = 0;
    if(!node)
        return -1;
    ldepth = depth(node->Left);
    rdepth = depth(node->Right);
    if(ldepth > rdepth)
        return ldepth + 1;
    else
        return rdepth + 1;
}

int levelOrder(Position node, int level)
{
    if(!node)
        return -1;
    else if(level == 0)
        printf("%d ", node->element);
    else if(level > 0){
        levelOrder(node->Left, level - 1);
        levelOrder(node->Right, level - 1);
    }

    return 0;
}

int printLevelOrder(Position root)
{
    int level = 0;

    for(level = 0; level <= depth(root); level++){
        levelOrder(root, level);
    }

    return EXIT_SUCCESS;
}

Position FindMin(Position root)
{
	while (root->Left)
		root = root->Left;

	return root;
}

Position findElement(int element, Position root)
{
	if (!root)
		return root;

    	else if (element > root->element)
		return findElement(element, root->Right);

	else if (element < root->element)
		return findElement(element, root->Left);

	else
		return root;
}

Position DeleteElement(int element, Position root)
{
	Position temp;
	if (!root)
		return root;
	else if (element < root->element)
		root->Left = DeleteElement(element, root->Left);
	else if (element > root->element)
		root->Right = DeleteElement(element, root->Right);
	else
	{
		if (root->Left && root->Right)
		{
			temp = FindMin(root->Right);
			root->element = temp->element;
			root->Right = DeleteElement(temp->element, root->Right);
		}
		else
		{
			temp = root;
			if (!root->Left)
				root = root->Right;
			else if (!root->Right)
				root = root->Left;
			free(temp);
		}
	}
	return root;
}



