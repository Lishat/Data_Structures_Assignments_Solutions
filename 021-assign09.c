/*
	NAME : DASH SUBHADEEP
	ROLL NO. 201601021
	LAST MODIFIED: Wed Mar 15 02:22:41 IST 2017	
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//defining the struct MOVIE
typedef struct MOVIE
{
	int movieID;
	char mname[16];
	int likes;
	int year;
	float rating;
	float budget;
	float revenue;
	int time;
}MOVIE;
//defining the struct HEAP
typedef struct HEAP
{
	MOVIE *data;
	struct HEAP *left;
	struct HEAP *right;
}HEAP;
//defining the struct NODE
typedef struct NODE
{
	MOVIE *info;
	struct NODE *next;
}NODE;
NODE *first;
//function to store in linked list
void push(MOVIE *p)
{
	NODE *temp;
	temp = (NODE *)(malloc(sizeof(NODE)));
	temp->info = p;
	temp->next = first;
	first = temp;
}

int inserted = 0;
int count = 0;
int scount = 0;
int flag;
char movienames[20][16] = {"ABC", "DEF", "GHI", "JKL", "MNO", "PQR", "STU", "VWX", "YZA", "BCD", "EFG", "HIJ", "KLM", "NOP", "QRS", "TUV", "WXY", "ZAB", "CDE", "FGH"};
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
//set function to heapify
void set(HEAP *head, HEAP *root)
{
	if(head->left != NULL && head->data->time < head->left->data->time)
	{
		MOVIE *temp;
		temp = head->data;
		head->data = head->left->data;
		head->left->data = temp;
		set(root, root);
	} 
	else if(head->right != NULL && head->data->time < head->right->data->time)
	{
		MOVIE *temp;
		temp = head->data;
		head->data = head->right->data;
		head->right->data = temp;
		set(root, root);
	} 
	else if(head->left != NULL && head -> right != NULL)
	{
		set(head->left, root);
		set(head->right, root);
	}
}
//check whether to insert new level or not
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
//to calculate the height of the heap
int height(HEAP *head)
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
//to insert levelwise
void insertLevel(HEAP *head, int level, HEAP *temp)
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
//to insert an element
void insert(HEAP *temp, HEAP *root)
{

	HEAP *head;
	head = (HEAP *)(malloc(sizeof(HEAP)));
	if(root == NULL || count == 0)
	{
		root = temp;
	}
	else
	{
		if(rem() != 0)
		{
			head = root;
			inserted = 0;
			insertLevel(head, height(head), temp);
		}
		else
		{
			head = root;
			while(head->left != NULL)
			{
				head=head->left;
			}
			head->left = temp;
		}
	}
	set(root, root);
	count++;
}

//to return root of the heap after heapifying
HEAP *createMovieDataset(HEAP *heap, int n)
{
	int i;
	HEAP *root;
	root = (HEAP *)(malloc(sizeof(HEAP)));
	for(i = 0; i <= n - 1; i++)
	{
		MOVIE *temp;
		temp = (MOVIE *)(malloc(sizeof(MOVIE)));
		temp->movieID = 100 + rand()%1991;
		strcpy(temp->mname, movienames[i]);
		temp->likes = 50 + rand()%9951;
		temp->year = 1990 + rand()%20;
		temp->rating = 1 + rand()%9 + (rand()%100)/100.0;
		temp->budget = 1 + rand()%19 + (rand()%100)/100.0;
		temp->revenue = 1 + rand()%999 + (rand()%100)/100.0;
		temp->time = 20 + rand()%161;
		if(count == 0)
		{
			root->data = temp;
			root->left = NULL;
			root->right = NULL;
			count += 1;
		}
		else
		{
			HEAP *tempi;
			tempi = (HEAP *)(malloc(sizeof(HEAP)));
			tempi->data = temp;
			tempi->left = NULL;
			tempi->right = NULL;
			insert(tempi, root);
		}
	}
	return root;
}

//print movie details preorderly
void printMovieDetails(HEAP *movie)
{
	if(movie != NULL)
	{
		printf("%d %s %d %d %0.2f %0.2f %0.2f %d\n", movie->data->movieID, movie->data->mname, movie->data->likes, movie->data->year, movie->data->rating, movie->data->budget, movie->data->revenue, movie->data->time);
		printMovieDetails(movie->left);
		printMovieDetails(movie->right);
	}
}
//print levelwise provided level is given
void printLevel(HEAP *head, int lev, int level)
{
	if(head == NULL)
	{

	}
	else if(lev == 1)
	{
		printf("Level: %d, %d %s %d %d %0.2f %0.2f %0.2f %d\n", level, head->data->movieID, head->data->mname, head->data->likes, head->data->year, head->data->rating, head->data->budget, head->data->revenue, head->data->time);
	}
	else if(lev > 1)
	{
		printLevel(head->left, lev - 1, level);
		printLevel(head->right, lev - 1, level);
	}
}
//to perform BFS
void performBreadthFirstSearch(HEAP *heap)
{
	int i;
	printf("BFS:\n");
	for(i = 1; i <= height(heap); i++)
	{
		printLevel(heap, i, i);
	} 
}
//to push in linked list
void preorder(HEAP *head)
{
	if(head != NULL)
	{
		push(head->data);
		preorder(head->left);
		preorder(head->right);
	}
}
//to sort the linked list
void ListSort()
{
	int j = count - 1, k;
	int temp;
	while(j >= 1)
	{
		k = 1;
		NODE *head;
		head = (NODE *)(malloc(sizeof(NODE)));
		head = first;
		while(k <= j)
		{
			if(head->info->time > head->next->info->time)
			{
				temp = head->info->time;
				head->info->time = head->next->info->time;
				head->next->info->time = temp;
			}
			head = head->next;
			k++;
		}
		j--;
	}
}
//heap to linked list
void convertHeapToSortedLinkedList(HEAP *heap)
{
	printf("\n\nSortedLinkedList:\n\n");
	first = (NODE *)(malloc(sizeof(NODE)));
	first->info = heap->data;
	first->next = NULL;
	preorder(heap->left);
	preorder(heap->right);
	NODE *head;
	head = (NODE *)(malloc(sizeof(NODE)));
	head = first;
	ListSort();
	while(head != NULL)
	{
		printf("%d %s %d %d %0.2f %0.2f %0.2f %d\n", head->info->movieID, head->info->mname, head->info->likes, head->info->year, head->info->rating, head->info->budget, head->info->revenue, head->info->time);
		head = head->next;
	}
	printf("\n\n");
}
//set as per ratings
void setr(HEAP *head, HEAP *root)
{
	if(head->left != NULL && head->data->rating < head->left->data->rating)
	{
		MOVIE *temp;
		temp = head->data;
		head->data = head->left->data;
		head->left->data = temp;
		setr(root, root);
	} 
	else if(head->right != NULL && head->data->rating < head->right->data->rating)
	{
		MOVIE *temp;
		temp = head->data;
		head->data = head->right->data;
		head->right->data = temp;
		setr(root, root);
	} 
	else if(head->left != NULL && head -> right != NULL)
	{
		setr(head->left, root);
		setr(head->right, root);
	}
}
//to delete last node
void deleteLast(HEAP *head, int level, HEAP *root)
{
	if(head == NULL)
	{
	
	}
	else if(level == 1)
	{
		scount++;
		if(scount == count/2)
		{
			if(head->right != NULL && flag == 1)
			{
				root->data = head->right->data;
				head->right = NULL;
				flag = 0;
				count--;
			}
			else if(head->left != NULL && flag == 1)
			{
				root->data = head->left->data;
				head->left = NULL;
				flag = 0;
				count--;
			}	
		}
	}
	else if(level > 1)
	{
		deleteLast(head->left, level - 1, root);
		deleteLast(head->right, level - 1, root);
	}
}
//to delete node
void deletenode(HEAP *head)
{
	int i;
	scount = 0;
	flag = 1;
	for(i = 1; i<= height(head);i++)
	{
		deleteLast(head, i, head);
	}
}
//heap sort
HEAP *sortMovies(HEAP *movie,  char A[])
{
	int i;
	int r = count;
	for(i = 1; i <= r; i++)
	{
		setr(movie, movie);
		printf("%d %s %d %d %0.2f %0.2f %0.2f %d\n", movie->data->movieID, movie->data->mname, movie->data->likes, movie->data->year, movie->data->rating, movie->data->budget, movie->data->revenue, movie->data->time);
		deletenode(movie);
		scount = 0;
	}
	printf("\n");
}

int main(int argc, char *argv[])
{
	HEAP *root = NULL;
	int n = (argc > 1)?atoi(argv[1]):20;
	root = createMovieDataset(root, n);
	printf("The Movie details in the MAX heap traversed preorderly is as follows:\n\n");
	printMovieDetails(root);
	printf("\n\n");
	performBreadthFirstSearch(root);
	convertHeapToSortedLinkedList(root);
	printf("Highly rated sorted movies sorted by heap sort is as follows:\n\n");
	root=sortMovies(root, "rating");	
	return 0;
}
