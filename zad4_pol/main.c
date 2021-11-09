#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50
#define MAX_LINE 1024

struct _Poly;
typedef struct _Poly* Position;
typedef struct _Poly{
    int coef;
    int expo;
    Position next;
} Poly;

int ReadFile(char*, Position one, Position two);
int SortedAdd(Position head, int coef, int expo);
Position insert(Position head,int co,int ex);
int multy(Position one, Position two, Position result);
Position CreateElement(int coefficient, int exponent);
int addition(Position head1, Position head2);

int main(){

    Poly head1 = {.coef = 0, .expo = 0, .next = NULL};
    Poly head2 = {.coef = 0, .expo = 0, .next = NULL};
    Poly zbroj = {.coef = 0, .expo = 0, .next = NULL};
    Poly umnozak = {.coef = 0, .expo = 0, .next = NULL};
    FILE *f = NULL;

    ReadFile("pol.txt", &head1, &head2);

    printf("First polynomial:\n");
    print(&head1);

    printf("\nSecond polynomial:\n");
    print(&head2);

    addition(&head1, &head2);
    multy(&head1, &head2, &umnozak);

    printf("\nMultiplied polynomials are:\n");
    findSameExpo(umnozak);
    print(&umnozak);

    return 0;
}

int ReadFile(char* nameOfFile, Position one, Position two){

    char buffer[MAX_LINE] = {0};
    char *tempBuffer;
    FILE *fp = NULL;
    int n = 0;
    int tempCoef, tempExpo, bytes;
    Position new = NULL;
    Position temp = NULL, prev = NULL;

    fp = fopen(nameOfFile, "r");

    if(!fp){
        printf("Greska pri otvaranju datoteke!\n");
        return -1;
    }

    fgets(buffer, MAX_LINE, fp);
    tempBuffer = buffer;
    while(strlen(tempBuffer) > 0){

        if(sscanf(tempBuffer, " %d %d %n", &tempCoef, &tempExpo, &bytes)==2){
            temp = one->next;
            prev = one;
            SortedAdd(one, tempCoef, tempExpo);
        }

        tempBuffer = tempBuffer + bytes;
    }

    fgets(buffer, MAX_LINE, fp);
    tempBuffer = buffer;
    while(strlen(tempBuffer) > 0){

        if(sscanf(tempBuffer, " %d %d %n", &tempCoef, &tempExpo, &bytes)==2){
            temp = two->next;
            prev = two;
            SortedAdd(two, tempCoef, tempExpo);
        }

        tempBuffer = tempBuffer + bytes;
    }

    fclose(fp);

    return EXIT_SUCCESS;
}
Position CreateElement(int coefficient, int exponent)
{
	Position element = NULL;

	element = (Position)malloc(sizeof(Poly));
	if (!element)
	{
		perror("Can't allocate memory!\n");
		return element; //NULL
	}

	element->coef = coefficient;
	element->expo = exponent;
	element->next = NULL;

	return element;
}
int SortedAdd(Position head, int coef, int expo){

    Position temp = NULL;
    Position prev = NULL;
    Position new = NULL;

    temp = head->next;
    prev = head;

    while(temp!=NULL && temp->expo > expo){
        prev = temp;
        temp = temp->next;
    }
    new = CreateElement(coef, expo);

    new->next = prev->next;
    prev->next = new;

    return EXIT_SUCCESS;
}

Position insert(Position head,int co,int ex)
{

	Position temp;
	Position newp=(Position)malloc(sizeof(Poly));
	newp->coef=co;
	newp->expo=ex;
	newp->next=NULL;



	if(head==NULL || ex>head->expo)
	{
	newp->next=head;
	head=newp;
	}
	else
	{
		temp=head;
		while(temp->next!=NULL && temp->next->expo>=ex)
		{
			temp=temp->next;
		}
		newp->next=temp->next;
		temp->next=newp;

	}
		return head;

}
int findSameExpo(Position head){

    Position prev = head;
    Position temp = NULL;

    while(prev->next!=NULL){
        temp = prev->next;
        if(prev->expo == temp->expo){
            prev->coef = prev->coef + temp->coef;
            prev->next = temp->next;
            free(temp);
        }
        prev = prev->next;
    }

    return EXIT_SUCCESS;
}

int addition(Position head1, Position head2){

    Position ptr1=head1;
	Position ptr2=head2;
	Position head3=NULL;

	if(ptr1!=NULL && ptr2!=NULL)
	{

		if(ptr1->expo==ptr2->expo)
		{
			head3=insert(head3,ptr1->coef+ptr2->coef,ptr1->expo);
			ptr1=ptr1->next;
			ptr2=ptr2->next;
		}
		else if(ptr1->expo>ptr2->expo)
		{
			head3=insert(head3,ptr1->coef,ptr1->expo);
			ptr1=ptr1->next;
		}
		else if(ptr2->expo>ptr1->expo)
		{
			head3=insert(head3,ptr2->coef,ptr2->expo);
			ptr2=ptr2->next;
		}
	}
	while(ptr1!=NULL)
	{
		head3=insert(head3,ptr1->coef,ptr1->expo);
		ptr1=ptr1->next;
	}
		while(ptr2!=NULL)
	{
		head3=insert(head3,ptr2->coef,ptr2->expo);
			ptr2=ptr2->next;
	}
	printf("\n\nAdded polynomials are: \n");
	findSameExpo(head3);
	print(head3);

}

void print(Position head3)
{
	Position temp=head3;
	if(head3==NULL)
	printf("no polynomials");
	while(temp!=NULL)
	{
	    if(temp->coef == 0)temp = temp->next;
	    else{
		printf("%dx^%d",temp->coef,temp->expo);
		temp=temp->next;
		if(temp!=NULL && temp->coef != 0)
		{
			printf("+");
		}
		else
		printf("\n");
		}
	}
}

int multy(Position one, Position two, Position result){

    Position temp1 = NULL, temp2 = NULL;
    int tempCoef = 0, tempExpo = 0;

    temp1 = one->next;

    while(temp1!=NULL){
        temp2 = two->next;
        while(temp2!=NULL){

            tempCoef = temp1->coef * temp2->coef;
            tempExpo = temp1->expo + temp2->expo;

            SortedAdd(result, tempCoef, tempExpo);

            temp2 = temp2->next;
        }
        temp1 = temp1->next;
    }
    return EXIT_SUCCESS;
}

