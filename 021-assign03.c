#include<stdio.h>
#include<string.h>

int strlength(char str[])
{	
	int i;
	for(i = 0; ; i++)
	{
		if (str[i] == '\0')
		{
			break;
		}
	}
	return i;
}

void print(char A[][100])
{
	int i;
	for(i = 0; i <= 9; i++)
	{
		printf("%s\n", A[i]);
	}
}

void read(char str[][100])
{
	int i, a, b, c;
	a = strlength(str[0]);
	c = 0;
	for(i = 0; i <= 9; i++)
	{
		b = strlength(str[i]);
		if(b >= a)
		{
			a = b;
			c = i;
		}
	}
	print(str);
	printf("\n%s\n", str[c]);	
}

int compare(char str[][100], int i, int j)
{
	int k;
	for(k = 0; ;k++)
	{
		if(str[i][k] == '\0' && str[j][k] == '\0')
		{
			return 0;
		}
		else if(str[i][k] == '\0')
		{
			return -1;
			break;
		}
		else if(str[j][k] == '\0')
		{
			return 1;
			break;
		}
		else if(str[i][k] > str[j][k])
		{
			return 1;
			break;
		}
		else if(str[i][k] < str[j][k])
		{
			return -1;
			break;
		}
	}
}

void sort(char str[][100])
{
	int i, j;
	char temp[100];
	for(j = 8; j >= 0; j--)
	{
		for(i = 0; i <= j; i++)
		{
			if(compare(str, i, i+1) == 1)
			{
				strcpy(temp, str[i]);
				strcpy(str[i], str[i+1]);
				strcpy(str[i+1], temp);
			}
		}
	}
	print(str);
}
 
void endsWithan(char str[][100])
{
	int i;
	for(i = 0; i <= 9; i++)
	{
		if(str[i][strlength(str[i])-1] == 'n' && str[i][strlength(str[i])-2] == 'a')
		printf("%s\n", str[i]);
	}
}

void Rpresent(char str[][100])
{
	int i, j;
	for(i = 0; i <= 9; i++)
	{
		for(j = 0; j <= strlength(str[i]) - 1;j++)
		{
			if(str[i][j] == 'R')
			{
				printf("%s\n", str[i]);
				break;
			}
		} 
	}
}

void trigrams(char str[][100])
{
	int i, j, k1, k2, k3,count=0;
	for(i = 0; i <= 9; i++)
	{	
		for(j = 0; str[i][j+2] != '\0'; j++)
		{
			if(str[i][j] == ' ')
			{
				continue;
			}
			else if(str[i][j+1] == ' ')
			{
				if(str[i][j+3] != '\0')
				{
					k1 = j;
					k2 = j+2;
					if(str[i][j+3] != ' ')
					{
						k3 = j + 3;
						count++;
					}
					else
					{
						k3 = j + 4;
						count++;
					}
				}	
			}
			else if(str[i][j+2] == ' ')
			{
				if(str[i][j+3] != '\0')
				{
					k1 = j;
					k2 = j+1;
					k3 = j+3;
				}
				count++;
			}
			else
			{
				k1 = j;
				k2 = j+1;
				k3 = j+2;
				count++;
			}
			printf("%c%c%c ", str[i][k1], str[i][k2], str[i][k3]);
		}
	}
	printf("%d\n", count);
}
void swap(char string[], int i, int j)
{
	char temp;
	temp =string[i];
	string[i] = string[j];
	string[j] = temp;
}
void permute(char string[], int low, int high)
{
	int i;
	if(low == high)
	{
		printf("%s\n", string);
	}
	
	else
	{
		for(i = low; i <= high; i++)
		{
			swap(string, low, i);
			permute(string, low+1, high);
			swap(string, low, i);
		}
	}
}

void select(char string[])
{
	int i, j,k,l;
	char string1[5];
	for(i = 3; i <= 9; i++)
	{
		for(j = 2; j < i; j++)
		{
			for(k = 1; k < j; k++)
			{
				for(l = 0; l < k; l++)
				{
					string1[0] = string[l];
					string1[1] = string[k];
					string1[2] = string[j];
					string1[3] = string[i];
					string1[4] = '\0';
					permute(string1, 0, 3);
				}
			}
		}
	}
}

void permuten(char string[], int low, int high)
{
	int i,j;
	if(low == high)
	{
		for(j = 0; j <= 2; j++)
		{
			if(string[j] == 'n' && string[j+1] == 'o')
			{
				printf("%s\n", string);
			}
			else if(string[j] == 's' && string[j+1] == 't')
			{
				printf("%s\n", string);
			}
		}
	}
	
	else
	{
		for(i = low; i <= high; i++)
		{
			swap(string, low, i);
			permuten(string, low+1, high);
			swap(string, low, i);
		}
	}
}

void selectn(char string[])
{
	int i, j,k,l;
	char string1[5];
	for(i = 3; i <= 9; i++)
	{
		for(j = 2; j < i; j++)
		{
			for(k = 1; k < j; k++)
			{
				for(l = 0; l < k; l++)
				{
					string1[0] = string[l];
					string1[1] = string[k];
					string1[2] = string[j];
					string1[3] = string[i];
					string1[4] = '\0';
					permuten(string1, 0, 3);
				}
			}
		}
	}
}

void check(char substring[])
{
	int i,j, length, max_length=0, max_index=0, m, n;
	for(i = 0; i <= 49; i++)
	{
		for(j = i+1; j <= 49; j++)
		{
			if(substring[i] == substring[j])
			{

				length = 0;
				m = i;
				n = j;
				for(;m <= 49 && n <= 49;)
				{
					if (m != 0 && substring[m-1] > substring[m])
					break;
					if(substring[m] != substring[n])
					{
						break;
					}
					else
					{
						length++;
					}
					m++;
					n++;				
				}
				if(max_length < length)
				{
					max_length = length;
					max_index = i;
				}
			}
		}
	}	
	for(i = max_index; i < max_index + max_length; i++)
	{
		printf("%c", substring[i]);
	}
	printf("\n");
}
		
int main()
{
	
	char str[10][100] = {"Raguvanshi", "M Radhakrishnan", "Pauline Haddow", "Sunil Chandran", "Uma Gopinath", "Soma Raju", "T V Gopala Krishnan", "Sudha Raghunath", "Rajarshi Pal","Karthikeyan"};
	char string[10];
	strcpy(string, "mnopqrstuv");
	char substring[50];
	strcpy(substring, "mnoarswtdefgharamnnopyqrrstuvwxystuvwxyxwzrwqtuvwxz");
	read(str);
	printf("\n");
	sort(str);
	printf("\n");
	endsWithan(str);
	printf("\n");
	Rpresent(str);
	printf("\n");
	trigrams(str);
	printf("\n");
	select(string);
	printf("\n");
	selectn(string);
	printf("\n");
	check(substring);
	return 0;
}
