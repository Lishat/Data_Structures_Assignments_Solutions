/*
	NAME: DASH SUBHADEEP
	BATCH: A
	ROLL NO. 201601021
 	DATE LAST MODIFIED: Sun Apr 2 14:06:33 IST 2017
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
/*defining a node in adjacency list*/
typedef struct NODE
{
	int data;
	float weight;
	struct NODE *next;
}NODE;
/*defining a graph*/
typedef struct GRAPH
{
	NODE *node[30];
}GRAPH;

/*defining a trie data structure*/
typedef struct TRIE
{
	int value;
	struct TRIE *children[54];	
}TRIE;

/*print the stack array of characters*/
void printStack(char *stack, int top)
{
	int i;
	for(i = 0 ; i <= top - 1; i++)
	{
		printf("%c", stack[i]);
	}
	printf("\t\t\t");
}
/*print the stack array of integers*/
void print(int *stack, int top)
{
	int i;
	for(i = 0; i <= top; i++)
	{
		printf("%d ", stack[i]);
	}
	printf("\n");
}
/*print the degree of the node*/
void printGraph(GRAPH *graph)
{
	int i, count = 0, n = 0;
	while(graph->node[n] != NULL)
	{
		n++;
	}
	for(i = 0; i <= n - 1; i++)
	{
		count = 0;
		NODE *head;
		head = graph->node[i]->next;
		printf("head ");
		while(head != NULL)
		{
			printf("-> %d ", head->data);
			count++;
			head = head->next;
		}
		printf("\n");
		printf("Degree of Node %d is: %d\n", i, count);
	}
}
/*inserting an edge in a graph*/
GRAPH *insert(GRAPH *graph, int src, int dest, float weight)
{
	NODE *temp = (NODE *)malloc(sizeof(NODE));
	temp->data = src;
	temp->weight = weight;
	temp->next = graph->node[dest]->next;
	graph->node[dest]->next = temp;
	
	NODE *temp1 = (NODE *)malloc(sizeof(NODE));
	temp1->data = dest;
	temp1->weight = weight;
	temp1->next = graph->node[src]->next;
	graph->node[src]->next = temp1;
	return graph;
}
/*building an undirected Graph*/
GRAPH *buildUndirectedGraph(int n)
{
	GRAPH *graph = (GRAPH *)malloc(sizeof(GRAPH));
	int i, j;
	for(i = 0; i <= n - 1; i++)
	{
		NODE *temp = (NODE *)malloc(sizeof(NODE));
		temp->data = i;
		temp->weight = 0.0;
		temp->next = NULL;
		graph->node[i] = temp;
	}
	for(i = 0; i <= n - 1; i++)
	{
		for(j = i + 1; j <= n - 1; j++)
		{
			if(rand()%2 == 1)
			{
				graph = insert(graph, i, j, (rand()%1000000)/1000000.0);
			}
		} 
	}
	return graph;
}
/*Checking the unvisited and adjacent node of a node in a graph*/
int adjacent(GRAPH *graph, int temp, int visit[])
{	
	NODE *head;
	head = graph->node[temp];
	while(head != NULL)
	{
		if(visit[head->data] == 0)
		{
			return head->data;
		}
		else
		{
			head = head->next;
		}
	}
	return -1;
}
/*Building a spanning tree out of the graph given*/
GRAPH *getSpanningTree(GRAPH *graph)
{
	GRAPH *stree;
	int i, n = 0;
	int visit[30], dfs[30], top = -1;
	while(graph->node[n] != NULL)
	{
		n++;
	}
	stree = (GRAPH *)malloc(sizeof(GRAPH));
	for(i = 0; i <= n - 1; i++)
	{
		NODE *temp = (NODE *)malloc(sizeof(NODE));
		temp->data = i;
		temp->weight = 0.0;
		temp->next = NULL;
		stree->node[i] = temp;
		visit[i] = 0;
	}
	visit[0] = 1;
	dfs[++top] = 0;
	while(top != -1)
	{
		int tem = adjacent(graph,dfs[top], visit);
		if(tem == -1)
		{
			top--;
		}
		else
		{
			NODE *head = graph->node[dfs[top]];
			while(head != NULL)
			{
				if(head->data == tem)
				{
					int p = tem, q = dfs[top];
					float r = head->weight;
					insert(stree, p, q, r);
					visit[tem] = 1;
					dfs[++top] = tem;
					break;
				}
				else
				{
					head=head->next;
				}
			}
		}
	}	
	for(i = 0; i <= n - 1; i++)
	{
		visit[i] = 0;
	}
	return stree;
}
/*finding all possible ways in the graph*/
void permute(GRAPH *graph, int stack[], int visit[], float sum, int top, int dest)
{
	int j,n = 0;
	while(graph->node[n] != NULL)
	{
		n++;
	}
	NODE *head = graph->node[stack[top-1]];
	head = head->next;
	while(head != NULL)
	{
		for(j = 0; j <= n - 1; j++)
		{
			visit[j] = 0;
		}
		for(j = 0; j <= top-1; j++)
		{
			visit[stack[j]] = 1;
		}
		if(visit[head->data] == 0)
		{
			stack[top] = head->data;
			permute(graph, stack, visit, sum+(head->weight), top+1, dest);
			if(stack[top] == dest && sum <= 6)
			{
				print(stack, top);
			}
		}	
		head = head->next;
	}
}
/*finding all the shortest paths with total weight <= 6*/
void *findShortestPathsL6(GRAPH *graph, int source, int dest)
{
	int n = 0, i, j, m;
	float sum = 0;
	while(graph->node[n] != NULL)
	{
		n++;
	}
	int visit[n], stack[n], top = -1;
	for(i = 0; i <= n - 1; i++)
	{
		visit[i] = 0;
	}
	visit[source] = 1;
	stack[++top] = source;
	NODE *head = graph->node[source];
	
	while(head->next != NULL)
	{
		top = 0;
		sum = 0;
		head = head->next;
		stack[++top] = head->data;
		if(head->data == dest)
		{
			print(stack, top);
		}
		visit[head->data] = 1;
		permute(graph, stack, visit, sum+(head->weight), top+1, dest);
	}
	for(m = 0; m <= n - 1; m++)
	{
		visit[m] = 0; 
	}
}
/*inserting a character in trie*/
void insertchar(TRIE *head, char *name, int l, int strlength)
{
	int i;
	if(l > 1)
	{
		if(name[strlength - l]	>= 65 && name[strlength - l] <= 90)
		{
			if(head->children[name[strlength-l] - 39] == NULL)
			{
				TRIE *temp;
				temp = (TRIE *)(malloc(sizeof(TRIE)));
				temp->value = 1;
				head->children[name[strlength-l] - 39] = temp;
			}
			head = head->children[name[strlength-l] - 39];
			insertchar(head, name, l - 1, strlength);
		}
		else if(name[strlength - l] >= 97 && name[strlength - l] <= 122)
		{
			if(head->children[name[strlength-l] - 97] == NULL)
			{
				TRIE *temp;
				temp = (TRIE *)(malloc(sizeof(TRIE)));
				temp->value = 1;
				head->children[name[strlength-l] - 97] = temp;
			}
			head = head->children[name[strlength-l] - 97];
			insertchar(head, name, l - 1, strlength);
		}
		else if(name[strlength - l] == 46)
		{
			if(head->children[52] == NULL)
			{
				TRIE *temp;
				temp = (TRIE *)(malloc(sizeof(TRIE)));
				temp->value = 1;
				head->children[52] = temp;
			}
			head = head->children[52];
			insertchar(head, name, l - 1, strlength);
		}
	}
	else if(l == 1)
	{
		if(name[strlength - l]	>= 65 && name[strlength - l] <= 90)
		{
			if(head->children[name[strlength-l] - 39] == NULL)
			{
				TRIE *temp;
				temp = (TRIE *)(malloc(sizeof(TRIE)));
				temp->value = 1;
				head->children[name[strlength-l] - 39] = temp;
			}
			head = head->children[name[strlength-l] - 39];
			insertchar(head, name, l - 1, strlength);
		}
		else if(name[strlength - l] >= 97 && name[strlength - l] <= 122)
		{
			if(head->children[name[strlength-l] - 97] == NULL)
			{
				TRIE *temp;
				temp = (TRIE *)(malloc(sizeof(TRIE)));
				temp->value = 1;
				head->children[name[strlength-l] - 97] = temp;
			}
			head = head->children[name[strlength-l] - 97];
			insertchar(head, name, l - 1, strlength);
		}
		else if(name[strlength - l] == 46)
		{
			if(head->children[52] == NULL)
			{
				TRIE *temp;
				temp = (TRIE *)(malloc(sizeof(TRIE)));
				temp->value = 1;
				head->children[52] = temp;
			}
			head = head->children[52];
			insertchar(head, name, l - 1, strlength);
		}
		if(head->children[53] == NULL)
		{
			TRIE *tempi;
			tempi = (TRIE *)(malloc(sizeof(TRIE)));
			tempi->value = 1;
			head->children[53] = tempi;
		}
	}
}
/*inserting string in a Trie*/
TRIE *insertTrie(TRIE *root,char *name)
{
	int l = strlen(name), i;
	insertchar(root, name, l, l);
	return root;
}
/*printing all possible prefixes*/
void printAllPrefixes(TRIE *head, char *stack, int top, int k)
{
	int i, count = 0;
	for(i = 0; i <= 53; i++)
	{
		if(head->children[i] != NULL)
		{
			if(i <= 25 && i >= 0)
			{
				char c = i + 97;
				stack[top] = c;
				printAllPrefixes(head->children[i], stack, top+1, k);
			}
			else if(i == 52)
			{
				stack[top] = '.';
				printAllPrefixes(head->children[i], stack, top+1, k);
			}
			else if(i >= 26 && i <= 51)
			{
				char c = i + 39;
				stack[top] = c;
				printAllPrefixes(head->children[i], stack, top+1, k);
			}
			count++;
		}
		
	}
	if(count > 1 && top > k)
	{
		printStack(stack, top);
		printf("COUNT:%d\n", count);
	}
}
/*reading an element to a trie*/
TRIE *readTrie(TRIE *head)
{
	char name[100];
	int count = 0;
	head->value = 0;
	FILE *fp = fopen("names-authors.txt", "r");
	while(fscanf(fp, "%s", name) >= 1)
	{
		if(rand()%2 == 1)
		{
			head = insertTrie(head, name);
			count++;
		}
		if(count == 200)
		{
			break;
		}
	}
	fclose(fp);
	return head;
}
/*finding prefix of size k*/
void findPrefixofSizeK(TRIE *trie, int k)
{
	char stack[100];
	printAllPrefixes(trie,stack, 0, k);
}
/*This is the main function*/
int main(int argc, char *argv[])
{
	int n = (argc > 1)?atoi(argv[1]):10;
	GRAPH *graph;
	graph = buildUndirectedGraph(n);
	GRAPH *stree;
	stree = getSpanningTree(graph);
	printGraph(stree);
	printf("\n\nAll possible paths between 5 and 7 with weight less than or equal to 6:\n");
	findShortestPathsL6(graph, 5, 7);
	printf("\n\nAll prefixes greater than 3 are:\n");
	TRIE *root;
	root = (TRIE *)(malloc(sizeof(TRIE)));
	root = readTrie(root);
	findPrefixofSizeK(root, 3);
	return 0;
}
