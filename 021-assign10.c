/*
	NAME: DASH SUBHADEEP
	ROLL NO. 201601021
	Date last modified: Sat Mar 25 17:56:58 IST 2017
	Batch: 'A'
*/
#include<stdio.h>
#include<stdlib.h>
typedef int GRAPH;
int n, max = 0;
/*building a graph*/
GRAPH *buildUWGraph(int n)
{
	int i, j;
	GRAPH *graph = (GRAPH *)malloc(n * n * sizeof(GRAPH *));
	for(i = 0; i <= n - 1; i++)
	{
		for(j = i+1; j <= n - 1; j++)
		{
			*(graph + i * n + j) = *(graph + j * n + i) = rand()%6;
		}
	}
	for(i = 0; i <= n - 1; i++)
	{
		for(j = 0; j <= n - 1; j++)
		{
			printf("%d ", *(graph + i * n + j));
		}
		printf("\n");
	}
	return graph;
}
/*finding the degree of each node*/
int nodeDegree(GRAPH *graph, int n)
{
	int i, j, count;
	for(i = 0; i <= n - 1; i++)
	{
		count = 0;
		for(j = 0; j <= n - 1; j++)
		{
			if(*(graph + i * n +j) != 0)
			{
				count++;
			}
		}
		printf("Degree of Node %d: %d\n",i+1, count);
	}
	return 0;
}
/*finding an adjacent node*/
int adjacent(int *graph, int index, int *visit, int n)
{
	int i;
	for(i = 0; i <= n - 1; i++)
	{
		if(*(graph+index*n+i) >= 1 && visit[i] == 0)
		{
			return i;
		}
	}
	return -1;
}
/*print all elements in the stack*/
void print(int *stack, int top)
{
	int i;
	for(i = 0; i <= top; i++)
	{
		printf("%d ", stack[i]+1);
	}
	printf("\n");
}
/*permuting to obtain all possible paths*/
void permute(int *graph, int stack[], int top, int mark, int visit[], int k)
{
	int i, j;
	for(i = 0; i <= n - 1; i++)
	{
		for(j = 0; j <= n - 1; j++)
		{
			visit[j] = 0;
		}
		for(j = 0; j <= top-1; j++)
		{
			visit[stack[j]] = 1;
		}
		if(*(graph+mark*n+i) != 0 && visit[i] == 0)
		{
			if(top <= k)
			{			
				stack[top] = i;
				visit[mark] = 1;
				permute(graph, stack, top+1, stack[top], visit, k);
			}
			if(top == k)
			{
				print(stack, k);
			}
		}
	}
}
/*printing paths of length k*/
void printPathsOfLengthK(GRAPH *graph, int k)
{
	int i, j;
	if(k > 1)
	{
		int stack[n], visit[n];
		int m;
		for(i = 0; i <= n - 1; i++)
		{
			visit[i] = 0;
		}
		for(i = 0; i <=  n - 1; i++)
		{
			visit[i] = 1;
			stack[0] = i;
			for(j = 0; j <= n - 1; j++)
			{
				if(*(graph + i*n + j) != 0)
				{
					stack[1] = j;
					visit[j] = 1;
					permute(graph, stack, 2, j, visit, k);
				}
			}
			for(m = 0; m <= n - 1; m++)
			{
				visit[m] = 0;
			}
		}
	}
	else if(k == 1)
	{
		for(i = 0; i <= n - 1; i++)
		{
			for(j = 0 ; j <= n - 1; j++)
			{
				if(*(graph + i*n + j) != 0)
				{
					printf("%d %d\n", i, j);
				}
			}
		}
	}
	else if(k == 0)
	{
		for(i = 0; i <= n - 1; i++)
		printf("%d\n", i);
	}
}
/*performing DFS on the graph and printing its adjacency matrix*/
void performTraversalDFS(GRAPH* graph)
{
	printf("\n\nDFS of the graph is:\n");
	int stack[n], visit[n], top = -1, i, dfs[n][n], j;
	for(i = 0; i <= n - 1; i++)
	{
		visit[i] = 0;
		for(j = 0; j <= n - 1;j++)
		{
			dfs[i][j] = 0;
		}
	}
	i = 0;
	printf("%d ", i+1);
	visit[i] = 1;
	stack[++top] = i;
	while(top != -1)
	{
		int temp = adjacent(graph, stack[top], visit, n);
		if(temp == -1)
		{
			top--;
		}
		else
		{
			visit[temp] = 1;
			printf("%d ", temp+1);
			dfs[stack[top]][temp] = *(graph+stack[top]*n+temp);
			stack[++top] = temp;
		}
	}
	printf("\n\nAdjacency matrix for dfs is:\n\n");
	for(i = 0; i <= n - 1; i++)
	{
		for(j = 0; j <= n - 1; j++)
		{
			printf("%d ", dfs[i][j]);
		}
		printf("\n");
	} 
}

void printLongestPath(GRAPH *graph, int p)
{
	int stack[n], visit[n], top = -1, i, dfs[n][n], j;
	for(i = 0; i <= n - 1; i++)
	{
		visit[i] = 0;
		for(j = 0; j <= n - 1;j++)
		{
			dfs[i][j] = 0;
		}
	}
	i = 0;
	visit[i] = 1;
	stack[++top] = i;
	while(top != -1)
	{
		int temp = adjacent(graph, stack[top], visit, n);
		if(temp == -1)
		{
			top--;
		}
		else
		{
			visit[temp] = 1;
			dfs[stack[top]][temp] = *(graph+stack[top]*n+temp);
			stack[++top] = temp;
		}
		if(top == p)
		{
			max = 1;
			print(stack, top);
			break;
		}
	}
}

/*finding longest path along the graph*/
void findLongestPath(GRAPH* graph)
{
	int p = n;
	printf("\n\nThe longest path is:\n");
	for(;;p--)
	{	
		printLongestPath(graph, p - 1);
		if(max == 1)
		{	
			break;
		}
		else if(p == 1)
		{
			break;
		}
	}
}
/*delete a node of specifed degree*/
void deleteKdegreeVertices(GRAPH *graph, int k)
{
	printf("\n\nThe adjacency matrix after deletion of nodes of degree %d is:\n", k);
	int i, j, count, p, q, stack[n], top = - 1;
	for(i = 0; i <= n - 1; i++)
	{
		count = 0;
		for(j = 0; j <= n - 1; j++)
		{
			if(*(graph + i * n +j) != 0)
			{
				count++;
			}
		}
		if(count == k)
		{
			stack[++top] = i;
		}
	}
	for(i = 0; i <= top; i++)
	{	
		for(j = 0; j <= n - 1; j++)
		{
			*(graph + stack[i] * n + j) = *(graph + j * n + stack[i]) = 0;
		}
	}
	for(i = 0; i <= n - 1; i++)
	{
		for(j = 0; j <= n - 1; j++)
		{
			printf("%d ", *(graph + i * n + j));
		}
		printf("\n");
	}
}
/*main function*/
int main(int argc, char *argv[])
{
	n = (argc > 1)?atoi(argv[1]):20;
	GRAPH *graph;
	graph = buildUWGraph(n);
	nodeDegree(graph, n);
	printf("\n\nThe paths of length k are:\n\n");
	printPathsOfLengthK(graph, 3);
	performTraversalDFS(graph);
	findLongestPath(graph);
	deleteKdegreeVertices(graph, rand()%n);
	return 0;
}
