#include<stdio.h>
#include<stdlib.h>

void prime()
{
	/*print first 20 prime numbers*/
	int count = 0, i = 2, j, flag = 1, sum = 0;
	for(;;)
	{
		if(count == 20)
		{
			break;
		}
		else
		{
			for(j = 2;j*j <= i; j++)
			{
				if(i%j == 0)
				{
					flag = 0;
					break;
				}
			}
		}

		if(flag == 1)
		{
			sum = sum + i;
			count++;
		}
		else if(flag == 0)
		{
			flag = 1;
		}
		i++;
	}
	printf("%d\n", sum);
}

void div3not2()
{
	/*print all integers that are divisible by 3 but not 2 in [1,50]*/
	int i;
	for(i = 3; i <= 50; i = i + 6)
	{
		printf("%d ", i);
	}
	printf("\n");
}

void factors()
{
	/*all factors of any positive integer in [60, 200]*/
	int i, j = ((rand()%(141))+60);
	for(i = 1; i <= j; i++)
	{
		if(j%i == 0)
		{
			printf("%d ", i);
		}
	}
	printf("\n");
}

void countOddDigits()
{
	/*print all the odd digits in a given number*/
	long long int j = rand();
	int i, count = 0;
	while(j != 0)
	{
		if((j%10)%2 != 0)
		{
			count++;
		}
		j = j/10;
		
	}
	printf("%d\n", count);
}

void Fibonacci()
{
	/*print Fibonacci sequence up to 80*/
	/*Sum of the Fibonacci sequence as well*/
	int a = 0, b = 1, sum = 0;
	for(;;)
	{
		a = a + b;
		b = a - b;
		if(a > 80)
		{
			break;
		}
		else if(a<=80)
		{
			sum = sum + a;	 
			printf("%d ", a);
		}
	}
	printf("\n%d\n", sum);
}

void pythagorean() /*x = y^2+z^2*/
{
	int A[500], i, j;
	for(i = 1; i <= 500; i++)
	{
		A[i] = 0;
	}
	for(i = 1; i*i <= 500; i++)
	{
		for(j = i; i*i + j*j <= 500; j++)
		{
			if(i*i + j*j <= 500)
			{
				A[i*i + j*j] = -1;
			}
		}
	}
	for(i = 1; i <= 500; i++)
	{
		if(A[i] == -1)
		{
			printf("%d ", i);
		}
	}
	printf("\n");
}

int main()
{
	prime();
	div3not2();
	factors();
	countOddDigits();
	Fibonacci();
	pythagorean();
	return 0;
}
