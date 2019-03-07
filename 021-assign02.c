#include<stdio.h>
int A[6][9];
int add = 0;
int m = 6, n = 9, count=0;
void read()
{
	int i, j;
	A[0][0] = 5;
	A[0][1] = 3;
	A[0][2] = 2;
	A[0][3] = 7;
	A[0][4] = 3;
	A[0][5] = 1;
	A[0][6] = 9;
	A[0][7] = 1;
	A[0][8] = 5;
	A[1][0] = 8;
	A[1][1] = 7;
	A[1][2] = 4;
	A[1][3] = 5;
	A[1][4] = 1;
	A[1][5] = 9;
	A[1][6] = 2;
	A[1][7] = 3;
	A[1][8] = 6;
	A[2][0] = 7;
	A[2][1] = 5;
	A[2][2] = 6;
	A[2][3] = 1;
	A[2][4] = 6;
	A[2][5] = 1;
	A[2][6] = 2;
	A[2][7] = 1;
	A[2][8] = 3;
	A[3][0] = 2;
	A[3][1] = 2;
	A[3][2] = 1;
	A[3][3] = 3;
	A[3][4] = 2;
	A[3][5] = 5;
	A[3][6] = 1;
	A[3][7] = 5;
	A[3][8] = 0;
	A[4][0] = 3;
	A[4][1] = 1;
	A[4][2] = 4;
	A[4][3] = 3;
	A[4][4] = 8;
	A[4][5] = 3;
	A[4][6] = 6;
	A[4][7] = 1;
	A[4][8] = 9;
	A[5][0] = 1;
	A[5][1] = 3;
	A[5][2] = 4;
	A[5][3] = 8;
	A[5][4] = 6;
	A[5][5] = 9;
	A[5][6] = 4;
	A[5][7] = 1;
	A[5][8] = 1;
	for(i = 0; i <= 5; i++)
	{
		for(j = 0; j <= 8; j++)
		{
			printf("%d ", A[i][j]);
		}
		printf("\n");
	}
}

int paths(int i, int j)
{
	if (i == m - 1 || j == n - 1)
	{
		return 1;
	}
	else
	{
		return paths(i+1, j) + paths(i,j+1);
	}
}

void check()
{
	int sum = 0;
	int i, j, k, count;
	for(i = 0; i <= m - 1; i++)
	{
		count = 0;
		for(k = 1; k <= 9; k++)
		{
			for(j = 0; j <= n - 1; j++)
			{
				if(k == A[i][j])
				{
					count++;
					break;
				}
			} 
		}
		if(count == 9)
		{
			sum = 0;
			for(j = 0; j <= n - 1; j++)
			{
				sum  = sum + A[i][j];
				printf("%d\n", A[i][j]);
			}
			printf("%d\n", sum);
		}
	}
}

void magic(int B[][1000], int n)
{
	int i, j, p, q, r;
	i = n - 1;
	j = n/2;
	for(r = 1; r <= n*n; r++)
	{
		p = (i+n)%n;
		q = (j+n)%n;	
		if(B[p][q] == 0)
		{
			B[p][q] = r;
			i = i + 1;
			j = j + 1;
		} 
		else if(B[p][q] != 0)
		{
			B[(p - 2 + n) % n][(q - 1 + n) % n] = r;
			i = p - 1;
			j = q;
		}
	}
	for(i = n-1; i >= 0; i--)
	{
		for(j = 0; j <= n - 1; j++)
		{
			printf("%d ", B[i][j]);
		}
		printf("\n");
	}
	check();
}

int reverse(int sum1)
{
	int m, q, r=0;
	m = sum1;
	while(m != 0)
	{
		q = m%10;
		r = r*10 + q;
		m = m/10;
	}
	return r;
}

void reflexive()
{
	int sum[9],i, j, k, l;
	for(j = 0; j <= n - 1; j++)
	{
		sum[j] = 0;
		for(i = 0; i <= m -1; i++)
		{
			sum[j] = sum[j] + A[i][j]; 
		}
	} 
	for(k = 0; k <= n - 1; k++)
	{
		for(l = k; l <= n - 1; l++)
		{
			if(reverse(sum[k]) == sum[l])
			{
				for(i = 0; i <= 5; i++)
				{
					printf("%d\n", A[i][k]);	
				} 
				printf("\n");
				for(i = 0; i <= 5; i++)
				{
					printf("%d\n", A[i][l]);
				}
				printf("\n");
				for(i = 0; i <= 5; i++)
				{
					printf("%d ", A[i][k]);	
				} 
				printf("%d\n", sum[k]);
				for(i = 0; i <= 5; i++)
				{
					printf("%d ", A[i][l]);
				}
				printf("%d\n", sum[l]);
			}
		}
	} 
}

void pascal()
{
	int y, z, x, flag;
	int i, j, count;
	for(y = 0; y <= m - 1; y++)
	{
		for(z = 0; z <= n - 1; z++)
		{
			if(A[y][z] == 1)
			{
				for(x = 1; y+x <= m - 1; x++)
				if(A[y+x][z-x] == 1 && A[y+x][z+x] == 1)
				{
					flag = 1;	
				}
				else
				{
					flag = 0;
					break;
				}
				if (flag == 1)
				{
					i = y;
					j = z;
				}
			}
		}
	} 
	int r, k;
	for(k = 1; k <= m - 1; k++)
	{
		count = 0;
		r = j;
		while(count != k)
		{
			printf("%d(%d,%d) ", A[k][r], k, r);
			r = r + 2;
			count++;
		}
		printf("\n");
		j--;
	}
}

int isprime(int j)
{
	int flag = 1, i;
	for(i = 2; i*i <= j; i++)
	{
		if(j%i == 0)
		{
			flag = 0;
			break;
		}
	} 
	return flag;
}

void prime()
{
	int i, j, k;
	for(i = 0; i <= m - 1; i++)
	{
		for(j = 0; j <= n - 1; j++)
		{
			if(isprime(A[i][j]) != 1 || A[i][j] == 1)
			{
				for(k = j; k <= n - 2; k++)
				{
					A[i][k] = A[i][k+1];
				}
				A[i][n - 1] = 0;
				j--;
			}
		}
	}
	for(i = 0; i <= 5; i++)
	{
		for(j = 0; j <= 5; j++)
		{
			printf("%d ", A[i][j]);
		}
		printf("\n");
	}
}

int main()
{
	int B[1000][1000];
	read();
	printf("\n");
	magic(B, 3);
	printf("\n");
	printf("%d\n", paths(0,0));
	printf("\n");
	reflexive();
	printf("\n");
	pascal();
	printf("\n");
	prime();
	return 0;
}
