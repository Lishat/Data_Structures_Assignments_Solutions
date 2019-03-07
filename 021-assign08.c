#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct BSTREE
{
	int nID;
	char proname[16];
	int size;
	float nbeds;
	float base;
	float charges;
	int ptype;
	struct BSTREE *left;
	struct BSTREE *right;
}BSTREE;
BSTREE *stack[25],*stack1[25];
BSTREE *root1;
char input[20][16] = {"ABC", "DEF", "GHI", "JKL", "MNO", "PQR", "STU", "VWX", "YZA", "BCD", "EFG", "HIJ", "KLM", "NOP", "QRS", "TUV", "WXY", "ZAB", "CDE", "FGH"}; 
int count = 0;
int flag = 1, inserted = 0;

int power(int a, int b)
{
	int c = 1, i;
	for(i = 1 ; i <= b; i++)
	{
		c = c * a;
	}
	return c;
}

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
BSTREE *genFlatsDataset(BSTREE *bstree, int n)
{
	int i;
	BSTREE *root;
	for(i = 0; i <= n - 1; i++)
	{
		BSTREE *temp;
		BSTREE *head;
		temp = (BSTREE *)(malloc(sizeof(BSTREE)));
		temp->nID = (1 + rand()%1999);
		strcpy(temp->proname, input[i]);
		temp->size = (480 + rand()%2894);
		temp->nbeds = (1 + rand()%10)*5/10.0;
		temp->base = (2499.0+rand()%2350 + (rand()%1000000)/1000000.0);
		temp->charges = (214 + rand()%(610))/100.0; 
		temp->ptype = rand()%3;
		temp->left = NULL;
		temp->right = NULL;
		if(flag == 1)
		{
			root = (BSTREE *)(malloc(sizeof(BSTREE)));
			root = temp;
			head = root;
			flag = 0;
		}
		else
		{
			struct BSTREE *current;
			current = (BSTREE *)(malloc(sizeof(BSTREE)));
			struct BSTREE *parent;
			parent = (BSTREE *)(malloc(sizeof(BSTREE)));
			current = root;
			while(1)
			{
				parent = current;
				if(temp->size < current->size)
				{
					current = current->left;
					if(current == NULL)
					{
						parent->left = temp;
						break;
					}
				}
				else
				{
					current = current->right;
					if(current == NULL)
					{
						parent->right = temp;
						break;
					}
				}
			}
		}
	}
	return root;
}

void printFlatDetails(BSTREE *bstree)
{
	if(bstree != NULL)
	{
		printFlatDetails(bstree->left);
		printf("%d %s %d %0.2f %f %0.2f %d\n", bstree->nID, bstree->proname, bstree->size, bstree->nbeds, bstree->base, bstree->charges, bstree->ptype);
		printFlatDetails(bstree->right);
	}
}

void FindFlatsByNBeds(BSTREE *bstree, float n)
{
	if(bstree != NULL)
	{
		if(bstree->nbeds == n)
		{
			printf("%d %s %d %0.2f %f %0.2f %d\n", bstree->nID, bstree->proname, bstree->size, bstree->nbeds, bstree->base, bstree->charges, bstree->ptype);
		}
		FindFlatsByNBeds(bstree->left, n);
		FindFlatsByNBeds(bstree->right, n);
	}
}

void ModifyParking(BSTREE *bstree, int oldPark, int newpark)
{
	if(bstree != NULL)
	{
		if(bstree->ptype == oldPark)
		{
			bstree->ptype = newpark;
		}
		ModifyParking(bstree->left, oldPark, newpark);
		ModifyParking(bstree->right, oldPark, newpark);
	}
}
void stacking(BSTREE *bstree)
{
	if(bstree != NULL)
	{
		stacking(bstree->left);
		stack[count++] = bstree;
		stacking(bstree->right);
	}
}

int height(BSTREE *head)
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

void insertLevel(BSTREE *head, int level, BSTREE *temp)
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

void insert(BSTREE *temp)
{

	BSTREE *head;
	head = (BSTREE *)(malloc(sizeof(BSTREE)));
	if(root1 == NULL || count == 0)
	{
		root1 = temp;
	}
	else
	{
		if(rem() != 0)
		{
			head = root1;
			inserted = 0;
			insertLevel(head, height(head), temp);
		}
		else
		{
			head = root1;
			while(head->left != NULL)
			{
				head=head->left;
			}
			head->left = temp;
		}
	}
	count++;
}


void BalanceBST(BSTREE *bstree)
{
	int i;
	stacking(bstree);
	int p = 9, q = 10;
	count = 0;
	for(;;)
	{
		if(q < 20)
		{
			stack1[count++] = stack[q];
			q += 1;
		}
		if(p >= 0)
		{
			stack1[count++] = stack[p];
			p -= 1;
		}	
		if(q == 20 && p == -1)
		{
			break;
		}
	}
	count = 0;
	for(i = 0; i <= 19; i++)
	{
		stack1[i]->left = NULL;
		stack1[i]->right = NULL;
		insert(stack1[i]);
	}
	printFlatDetails(root1);
}

BSTREE *deleteElements(BSTREE *bstree, int min, int max)
{
	int i;
	for(i = 0;i <= count - 1; i++)
	{
		if(stack[i]->charges >= min && stack[i]->charges <= max)
		{
			if(i == count -1)
			{
				count -= 1;
			}
			else
			{
				stack[i] = stack[count-1];
				count--;
				i--;
			}
		}
	}
}



int main()
{
	int n = 20;
	BSTREE *bstree;
	bstree = genFlatsDataset(bstree, n);
	printFlatDetails(bstree);
	printf("\n\n");
	FindFlatsByNBeds(bstree, 3.5);
	ModifyParking(bstree, 2, 0);
	BalanceBST(bstree);
	deleteElements(bstree, 3, 4);
	return 0;
}
