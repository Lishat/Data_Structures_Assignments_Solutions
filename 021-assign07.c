/*
    Name: Dash Subhadeep
    Roll no. 201601021
*/
#include<stdio.h>
#include<stdlib.h>
//defining struct BTNODE
typedef struct
{
	int proID;
	int rank;
	int level;
	float cost;
	float discount;
}BTNODE;
//defining tree node
struct Tree
{
	BTNODE *data;
	struct Tree *left;
	struct Tree *right;
};
struct Tree *root;
int count = 0;
int flag = 1;
int inserted = 0;
int dist = 0;
float least;
float least2;
BTNODE *stack[1000];
int scount = 0;
//power function
int power(int a, int b)
{
	int c = 1, i;
	for(i = 1 ; i <= b; i++)
	{
		c = c * a;
	}
	return c;
}
//remove if no. of nodes = 2 ^ h - 1
int rem()
{
	int fl = 1, i;
	for(i = 0; count > power(2, i); i++)
	{
		if(count == power(2, i+1) -1)
		{
			fl = 0;
			break;
		}
	}
	if(count == 1)
	{
		fl = 0;
	}
	return fl;
}
//to find out height of head node
int height(struct Tree *head)
{
	if(head == NULL)
	{
		return 0;
	}
	else
	{
		int leftHeight = height(head->left);
		int rightHeight = height(head->right);
		if(leftHeight > rightHeight)
		{
			return (leftHeight+1);
		}
		else
		{
			return (rightHeight+1);
		}
	}
}
//to insert at a particular level
void insertLevel(struct Tree *head, int level, struct Tree *temp)
{
	if(head == NULL)
	{

	}
	else if(level == 2)
	{
		if(head->left == NULL && inserted == 0)
		{
			head->left = temp;
			inserted = 1;
		}
		else if(head->right == NULL && inserted == 0)
		{
			head->right = temp;
			inserted = 1;
		}
	}
	else if(level > 1)
	{
		insertLevel(head->left, level - 1, temp);
		insertLevel(head->right, level - 1, temp);
	}
}
//to insert a node
void insert(struct Tree *temp)
{

	struct Tree *head;
	head = (struct Tree *)(malloc(sizeof(struct Tree)));
	if(root == NULL || count == 0)
	{
		root = temp;
	}
	else
	{
		if(rem() != 0)
		{
			head = root;
			temp->data->level = dist;
			inserted = 0;
			insertLevel(head, height(head), temp);
		}
		else
		{
			dist++;
			temp->data->level = dist;
			head = root;
			while(head->left != NULL)
			{
				head=head->left;
			}
			head->left = temp;
		}
	}
	count++;
}
//to generate binary trees
BTNODE *genBinaryTree(BTNODE *btnode, int n)
{
	int i;
	for(i = 1; i <= n; i++)
	{
		BTNODE *temp;
		temp = (BTNODE *)(malloc(sizeof(BTNODE)));
		temp->proID = (1000 + rand()%9000);
		temp->rank = (1 + rand()%9000);
		temp->level = dist;
		temp->cost = (99 + rand()%400 + (rand()%1000000)/1000000.0);
		temp->discount = (2+rand()%3 + + (rand()%1000000)/1000000.0);
		if(flag == 1)
		{
			root = (struct Tree *)(malloc(sizeof(struct Tree)));
			root->data = temp;
			root->left = NULL;
			root->right = NULL;
			flag = 0;
			count = 1;
		}
		else
		{
			struct Tree *tempi;
			tempi = (struct Tree *)(malloc(sizeof(struct Tree)));
			tempi->data = temp;
			tempi->left = NULL;
			tempi->right = NULL;
			insert(tempi);
		}
	}
	return root->data;
}
//to print elements in a level
void printLevel(struct Tree *head, int lev)
{
	if(head == NULL)
	{

	}
	else if(lev == 1)
	{
		printf("%d %d %f %d\n", head->data->proID, head->data->rank, head->data->cost - head->data->discount, head->data->level);
	}
	else if(lev > 1)
	{
		printLevel(head->left, lev - 1);
		printLevel(head->right, lev - 1);
	}
}
//to print all the elements
void printElements(BTNODE *temp)
{
	struct Tree *head = root;
	int i;
	for(i = 1; i <= height(head); i++)
	{
		printLevel(head, i);
	}
}
//to print all cost prices within the particular range
void printRange(struct Tree *head, int lev)
{
	if(head == NULL)
	{

	}
	else if(lev == 1)
	{
		if((head->data->cost - head->data->discount) >= 129.0 && (head->data->cost - head->data->discount) <= 399.5)
		{
			printf("%d %d %f %d\n", head->data->proID, head->data->rank, head->data->cost - head->data->discount, head->data->level);
		}
	}
	else if(lev > 1)
	{
		printRange(head->left, lev - 1);
		printRange(head->right, lev - 1);
	}
}
//to search range by cost
void RangeSearchByCost(BTNODE *item, float scost)
{
	struct Tree *head = root;
	int i;
	for(i = 1; i <= height(head); i++)
	{
		printRange(head, i);
	}
}
//to find the smallest element
void small(struct Tree *head)
{
	if (head != NULL)
	{
		if(least > (head->data->cost - head->data->discount))
		{
			least = head->data->cost - head->data->discount;
		}
		small(head->left);
		small(head->right);
	}
}
//to find the second smallest element
void small2(struct Tree *head)
{
	if (head != NULL)
	{
		if(least2 > (head->data->cost - head->data->discount) && (head->data->cost - head->data->discount) != least)
		{
			least2 = head->data->cost - head->data->discount;
		}
		small2(head->left);
		small2(head->right);
	}
}
//to search the element head
void search(struct Tree *head, float tmp)
{
	if (head != NULL)
	{
		if(tmp == head->data->cost - head->data->discount)
		{
			printf("%d %d %f %d\n", head->data->proID, head->data->rank, head->data->cost - head->data->discount, head->data->level);
		}
		search(head->left, tmp);
		search(head->right, tmp);
	}
}
//to search minimum cost
void SearchMinCost(BTNODE *btnode)
{
	least = (root->data->cost - root->data->discount);
	small(root);
	if(least == (root->data->cost - root->data->discount))
	{
		least2 = root->left->data->cost - root->left->data->discount;
	}
	else
	{
		least2 = root->data->cost - root->data->discount;
	}
	small2(root);
	search(root, least);
	search(root, least2);
}
//to store all the elements in a level
void storeLevel(struct Tree *head, int lev)
{
	if(head == NULL)
	{

	}
	else if(lev == 1)
	{
		stack[scount++] = head->data;
	}
	else if(lev > 1)
	{
		storeLevel(head->left, lev - 1);
		storeLevel(head->right, lev - 1);
	}
}
//to store all elements
void store(struct Tree *temp)
{
	struct Tree *head = root;
	int i;
	for(i = 1; i <= height(head); i++)
	{
		storeLevel(head, i);
	}
}

//to make a tree
void makeTree()
{
	int i;
	for(i = 0; i <= scount - 1; i++)
	{
		struct Tree *temp;
		temp = (struct Tree *)(malloc(sizeof(struct Tree)));
		temp->data = stack[i];
		temp->left = NULL;
		temp->right = NULL;
		insert(temp);
	}
}
//to delete elements in a level
BTNODE *deleteElements(BTNODE *btnode, int level)
{
	int i, p;
	store(root);
	count = 0;
	for(i = 0; i <= scount - 1; i++)
	{
		if(stack[i]->level == level && level != height(root) - 1)
		{
			p = i;
			stack[p] = stack[scount-1];
			scount--;
			i--;
		}
		else if(stack[i]->level == level && level == height(root) - 1)
		{
			scount = i;
			break;
		}
	}
	dist = 0;
	makeTree();
}
// main function
int main(int argc, char *argv[])
{
	int i;
	int n = (argc > 1)? atoi(argv[1]): 10;
	BTNODE *temp;
	temp = (BTNODE *)(malloc(sizeof(BTNODE)));
	genBinaryTree(temp, n);
	printElements(temp);
	printf("\n\n");
	RangeSearchByCost(temp, 2);
	printf("\n\n");
	SearchMinCost(temp);
	printf("\n\n");
	deleteElements(temp, 2);
	printElements(temp);
	return 0;
}
