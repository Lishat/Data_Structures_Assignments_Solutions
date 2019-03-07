/*
	Name: Dash Subhadeep
	Roll no. 201601021
	Date last modified:Wed Feb 22 22:27:12 IST 2017
*/
#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>

//defining the typedef struct
typedef struct
{
	int proID;
	char name[50];
	int type;
	char make[50];
	float mrp;
	float discount;
	float charges;
	float starrate;
} ITEM;

//defining the struct Node
struct NODE
{
	ITEM *data;
	struct NODE *next;
};
int flag = 1;
struct NODE *first=NULL;
struct NODE *head = NULL; 
struct NODE *rear=NULL;

//function to insert an item
ITEM *insertItem(ITEM *item)
{
	struct NODE *temp;
	temp = (struct NODE *)(malloc(sizeof(struct NODE)));
	temp->data = item;
	temp->next = NULL;
	if(flag == 1)
	{
		first = (struct NODE *)(malloc(sizeof(struct NODE)));
		first = temp;
		head = (struct NODE *)(malloc(sizeof(struct NODE)));
		head = temp;
		rear = (struct NODE *)(malloc(sizeof(struct NODE)));
		rear = first;
		flag += 5;
	}
	else
	{
		rear->next = temp;
		rear=temp;
	}
}
//function to print an item
void printItems(ITEM*item)
{
	head = first;
	while(head != NULL)
	{
		printf("%s %d %0.2f\n", (head->data)->name, (head->data)->type, (head->data)->mrp);
		head = head->next;
	}
	printf("\n\n");
}
//to generate the dataset taking input from the file
ITEM *genDataset(FILE *fp)
{
	int i = 0,j = 0, k = 0, l = 0, m = 0;
	while(i != 12)
	{
		ITEM *item = (ITEM *)(malloc(sizeof(ITEM)));
		char comma[500];
		char cam[8][500];
		char temp[500];
		for(m = 0; m <= 7; m++)
		{
			strcpy(cam[m], temp);
		}
		fgets(comma, 500, fp);
		i++;
		l = 0;
		for(k = 0; k <= 7; k++)
		{
			for(j = 0;comma[l] != ',';)
			{
				cam[k][j++] = comma[l++];
			}
			cam[k][j] ='\0';
			l++;
		} 
		item->proID = atoi(cam[0]);
		strcpy(item->name, cam[1]);
		item->type = atoi(cam[2]);
		strcpy(item->make, cam[3]);
		item->mrp = atof(cam[4]);
		item->discount = atof(cam[5]);
		item->charges = atof(cam[6]);
		item->starrate = atof(cam[7]);
		//printf("%d %s %d %s %0.2f %0.2f %0.2f %0.2f\n", item->proID, item->name, item->type, item->make, item->mrp, item->discount, item->charges, item->starrate);
		insertItem(item);
	}
}
//To search an item by its maker
void SearchItemByMake(ITEM *item, char *make)
{
	head = first;
	while(head != NULL)
	{
		if(strcmp(head->data->make,make) == 0)
		{
			printf("\n%s", head->data->name);
		}
		head = head->next;
	}
	printf("\n\n");
}
//to search the lowest price of an item considering all charges, discounts and printing the details
void SearchLowPrice(ITEM *item)
{
	head = first;
	float low = head->data->mrp + head->data->charges - ((head->data->discount)*(head->data->mrp)/100);
	while(head != NULL)
	{
		if((head->data->mrp + head->data->charges -  ((head->data->discount)*(head->data->mrp)/100)) < low)
		{
			low = head->data->mrp + head->data->charges -  ((head->data->discount)*(head->data->mrp)/100);
		}
		head = head->next;
	}
	head = first;
	while(head != NULL)
	{
		if(low == (head->data->mrp + head->data->charges -  ((head->data->discount)*(head->data->mrp)/100)))
		{
			low = (head->data->mrp + head->data->charges -  ((head->data->discount)*(head->data->mrp)/100));
			printf("\n%d %s %d %s %0.2f %0.2f %0.2f %0.2f\n", head->data->proID, head->data->name, head->data->type, head->data->make, head->data->mrp, head->data->discount, head->data->charges, head->data->starrate);
		}
		head = head->next;
	}
	printf("\n\n");
}
//to modify the discount
ITEM *modifyDiscount(ITEM *item, float off)
{
	head = first;
	while(head != NULL)
	{
		head->data->discount = head->data->discount+off;
		printf("\n%d %s %d %s %0.2f %0.2f %0.2f %0.2f\n", head->data->proID, head->data->name, head->data->type, head->data->make, head->data->mrp, head->data->discount, head->data->charges, head->data->starrate);
		head = head->next;
	}
	printf("\n\n");
}
//to delete an item by ID
void deleteItemByID(ITEM *item, int proID)
{
	head = first;
	if(first->data->proID == proID)
	{
		printf("\n%d %s %d %s %0.2f %0.2f %0.2f %0.2f\n", head->data->proID, head->data->name, head->data->type, head->data->make, head->data->mrp, head->data->discount, head->data->charges, head->data->starrate);
		struct NODE *temp = (struct NODE *)(malloc(sizeof(struct NODE)));
		temp = first;
		first = first->next;
		head = first;
		free(temp); 
	}
	else if(rear->data->proID == proID)
	{
		while(head->next != rear)
		{
			head = head->next;
		}
		printf("\n%d %s %d %s %0.2f %0.2f %0.2f %0.2f\n", rear->data->proID, rear->data->name, rear->data->type, rear->data->make, rear->data->mrp, rear->data->discount, rear->data->charges, rear->data->starrate);
		head->next = NULL;
		struct NODE *temp = (struct NODE *)(malloc(sizeof(struct NODE)));
		temp = rear;
		rear = head;
		free(temp);		
	}
	else
	{
		while(head->next->data->proID != proID)
		{
			head = head->next;
		}
		printf("\n%d %s %d %s %0.2f %0.2f %0.2f %0.2f\n", head->next->data->proID, head->next->data->name, head->next->data->type, head->next->data->make, head->next->data->mrp, head->next->data->discount, head->next->data->charges,head->next->data->starrate);
		struct NODE *temp = (struct NODE *)(malloc(sizeof(struct NODE)));
		temp = head->next;
		head->next = head->next->next;
		free(temp);
	}
}
//This is the main function
int main( int argc, char *argv[] )
{
    ITEM *item;
    FILE *fp;

    fp = (argc > 1) ? fopen(argv[1], "r+") : fopen("inputdata.txt", "r+");
    item = genDataset(fp);
    fclose(fp);
   
    printItems(item);
   
    char *product = "Nikon";
    printf("\nPRODUCT: %s", product);
   
    SearchItemByMake(item, product);
    
    SearchLowPrice(item);
   
    float off = -0.5;       // you could change the sign to give additional discount
    item = modifyDiscount(item, off);

    int proID = 75242;
    deleteItemByID(item, proID);
   
    return 0;
}
