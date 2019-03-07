#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int isPrime(int A[], int B[], int C[], int k) //to know whether its prime or not 
{
	int flag = 1, i;
	for(i = 2; i*i <= A[k]; i++)
	{
		if(A[k] % i == 0)
		{
			flag = 0;
			break;
		}	
	}
	return flag;
}

void swap(int A[], int i) // to swap int values
{
	int temp;
	temp = A[i];
	A[i] = A[i+1];
	A[i+1] = temp;
}

void print(int A[], int count) // to print in ascending order
{
	int i;
	for(i = 0; i <= count - 1; i++)
	{
		printf("%d ", A[i]);
	}
	printf("\n");
}

void printr(int A[], int count) // to print in descending order
{
	int i;
	for(i = count - 1; i >= 0; i--)
	{
		printf("%d ", A[i]);
	}
	printf("\n");
}

void bubblesort(int B[], int count) // to bubblesort int values
{
	int i, j;
	for(j = count - 2; j >= 0; j--)
	{
		for(i = 0; i <= j; i++)
		{
			if(B[i] >= B[i+1])
			{
				swap(B, i);
			}
		}
	}
}

void primesort() // to sort the given array consisting of prime and composite no.s
{
	int A[30]= {8, 2, 70, 11, 36, 29, 67, 41, 13, 3, 6, 5, 35, 52, 96, 24, 17, 29, 37, 41, 53, 47, 61, 53, 71, 14, 11, 7, 82, 57}, B[30], C[30], i, j = 0, k = 0;
	for(i = 0; i <= 29; i++)
	{
		if(isPrime(A, B, C, i) == 1)
		{
			B[j] = A[i];
			j++;
		}
		else if(isPrime(A, B, C, i) == 0)
		{
			C[k] = A[i];
			k++;
		}
	}
	bubblesort(B, j);
	bubblesort(C, k);
	print(B, j);
	printr(C, k);
	printf("\n\n");
}

int isVowel(char A[][1000], int i) // to identify whether it is a vowel or not
{
	if(A[i][0] == 'A' || A[i][0] == 'E' || A[i][0] == 'I' || A[i][0] == 'O' || A[i][0] == 'U')
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void printword(char A[][1000], int count) // to print in ascending order
{
	int i;
	for(i = 0; i <= count - 1; i++)
	{
		printf("%s\n", A[i]);
	}
}

void printrevword(char A[][1000], int count) // to print in decreasing order
{
	int i;
	for(i = count - 1; i >= 0; i--)
	{
		printf("%s\n", A[i]);
	}
}

void swapwords(char A[][1000], int i) // to swap words during bubble sort
{
	char temp[1000];
	strcpy(temp, A[i]);
	strcpy(A[i], A[i+1]);
	strcpy(A[i+1], temp); 
}

void wordsort(char A[][1000], int count) // to bubble sort two dimensional arrays
{
	int i, j;
	for(j = count - 2; j >= 0; j--)
	{
		for(i = 0; i <= j; i++)
		{
			if(strcmp(A[i], A[i+1]) > 0)
			{
				swapwords(A, i);
			}
		}
	}
}

void sortalpha() //to sort names starting with vowels and non-vowels
{
	int i, j, k;
	char A[10][1000] = {"T V S Sundaram", "James Bond 007", "Elangovan T S", "Raghu Raja  Pandian", "Uma Mageswari", "Kamal Talukdar", "Anbarasu Kannan", "Janaku Ramu", "Ishwarya Gireesh", "Odelu Venga Prasad"}, B[10][1000], C[10][1000];
	for(i = 0; i <= 9; i++)
	{
		if(isVowel(A, i) == 1)
		{
			strcpy(B[j], A[i]);
			j++;
		}
		else if(isVowel(A, i) == 0)
		{
			strcpy(C[k], A[i]);
			k++;
		}	
	}
	wordsort(B, j);
	wordsort(C, k);
	printword(B, j);
	printf("\n");
	printrevword(C, k); 
	
}

void generateNumbers(int n) // to generate random float no.s
{
	int i, s;
	float r;
	FILE *fp = fopen("021-input.txt", "w");
	for(i = 0; i <= n - 1; i++)
	{
		s = rand()%1000000;
		r = s/1000000.0;
		fprintf(fp,"%f\n", r);
	}
	fclose(fp);
}


void floatswap(float A[], int i) // to swap the float variables
{
	float temp;
	temp = A[i];
	A[i] = A[i+1];
	A[i+1] = temp;
}

void floatsort(float A[]) // to sort the float values
{
	int i, j;
	for(j = 498; j >= 0; j--)
	{
		for(i = 0; i <= j; i++)
		{
			if(A[i] >= A[i+1])
			{
				floatswap(A, i);
			}
		}
	}
}

void fileprint(float A[]) // to print the float values in descending order and in range[0.315, 0.625] in increasing order
{
	int i;
	FILE *fp = fopen("021-output.txt", "w");
	for(i = 499; i >= 0; i--)
	{
		fprintf(fp, "%f\n", A[i]);
	}
	fprintf(fp, "\n\n");
	for(i = 0; i <= 499; i++)
	{
		if(A[i] >= 0.315 && A[i] <= 0.625)
		{ 
			fprintf(fp, "%f\n", A[i]);
		}
	}
	fclose(fp);
}

void sortfile() // to sort the elements in a file and store them in a two dimensional array
{
	float A[500];
	int i = 0;
	FILE *fp = fopen("021-input.txt", "r");
	while(fscanf(fp, "%f\n", &A[i]) >= 0)
	{
		i++;
	}
	floatsort(A);
	printf("\n%f %f\n", A[499], A[0]);
	fileprint(A);
	fclose(fp);
}

void file()	// to generate no.s from 0 to 1 and sort them and print the output in a file
{
	generateNumbers(500);
	sortfile();
}

int main()
{
	primesort();	//To sort the prime no.s and the composite no.s
	sortalpha();	//To sort the vowels and non vowel names
	file();		//To print the float values and sort them and print the output in another file
	return 0;
}
