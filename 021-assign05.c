/*
	Program: 021-assign05.c
	Author: DASH SUBHADEEP
	Last Modified: Tuesday Feb 14, 2017 15:28:32 IST 
*/
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define PI 3.14159265
typedef struct		/* This is defining the struct */
	{
		float x1, x2, x3, y1, y2, y3, area;
	}TRIANGLE;

void printTriangles(TRIANGLE *t, int n) /*This function prints the points of the triangle along with their area*/
{
	int i;
	for(i = 0; i <= n - 1; i++)
	{
		printf("POINTS: (%f, %f) (%f, %f) (%f, %f) AREA: %f\n", t[i].x1, t[i].y1, t[i].x2, t[i].y2, t[i].x3, t[i].y3, t[i].area);
	}
}

void computeArea(TRIANGLE *t, int n) /*This function computes the area of each and every triangle*/
{
	int i;
	for(i = 0; i <= n - 1; i++)
	{
		t[i].area = 0.5*fabs((t[i].x1 * (t[i].y2 - t[i].y3)) + (t[i].x2 * (t[i].y3 - t[i].y1)) + (t[i].x3 * (t[i].y1 - t[i].y2)));
	}
	printTriangles(t, n);
}

void findPrintInAngles(TRIANGLE *t, int n) /*This function prints the angles in the triangle*/
{
	int i;
	float angles[3], m1 = 0, m2 = 0, m3 = 0;
	for(i = 0; i <= n - 1; i++)
	{
		m1 = (t[i].y2 - t[i].y1)/(t[i].x2 - t[i].x1);
		m2 = (t[i].y3 - t[i].y2)/(t[i].x3 - t[i].x2);
		m3 = (t[i].y1 - t[i].y3)/(t[i].x1 - t[i].x3);
		angles[0] = (atan((m1 - m2)/(1 + m1 * m2)));
		angles[1] = (atan((m2 - m3)/(1 + m2 * m3)));
		angles[2] = (atan((m3 - m1)/(1 + m3 * m1)));
		if(angles[0] < 0 && angles[1] < 0 && angles[2] < 0)
		{
			printf("Angles for triangle no. %d: %f %f %f\n", i, fabs(angles[0]*180/PI), fabs(angles[1]*180/PI), fabs(angles[2]*180/PI));
		}
		else if(angles[0] > 0 && angles[1] > 0 && angles[2] > 0)
		{
			printf("Angles for triangle no. %d: %f %f %f\n", i, angles[0]*180/PI, angles[1]*180/PI, angles[2]*180/PI);
		}
		else if(angles[0] < 0 && angles[1] > 0 && angles[2] > 0)
		{
			printf("Angles for triangle no. %d: %f %f %f\n", i, 180+angles[0]*180/PI, angles[1]*180/PI, angles[2]*180/PI);
		}
		else if(angles[0] > 0 && angles[1] < 0 && angles[2] > 0)
		{
			printf("Angles for triangle no. %d: %f %f %f\n", i, angles[0]*180/PI, 180+angles[1]*180/PI, angles[2]*180/PI);
		}
		else if(angles[0] > 0 && angles[1] > 0 && angles[2] < 0)
		{
			printf("Angles for triangle no. %d: %f %f %f\n", i, angles[0]*180/PI, angles[1]*180/PI, 180+angles[2]*180/PI);
		}
		else if(angles[0] < 0 && angles[1] < 0 && angles[2] > 0)
		{
			printf("Angles for triangle no. %d: %f %f %f\n", i, fabs(angles[0]*180/PI), fabs(angles[1]*180/PI), fabs(180-angles[2]*180/PI));
		}
		else if(angles[0] > 0 && angles[1] < 0 && angles[2] < 0)
		{
			printf("Angles for triangle no. %d: %f %f %f\n", i, fabs(180-angles[0]*180/PI), fabs(angles[1]*180/PI), fabs(angles[2]*180/PI));
		}
		else if(angles[0] < 0 && angles[1] > 0 && angles[2] < 0)
		{
			printf("Angles for triangle no. %d: %f %f %f\n", i, fabs(angles[0]*180/PI), fabs(180-angles[1]*180/PI), fabs(angles[2]*180/PI));
		}
	}
}

TRIANGLE *genTriangles(int n)	/*This function generates n triangles*/
{
	int i;
	TRIANGLE *tri = (TRIANGLE *)malloc(n*(sizeof(TRIANGLE)));
	for(i = 0; i <= n - 1; i++)
	{
		tri[i].x1 = (10 + rand()%30 + (rand()%1000000)/1000000.0);
		tri[i].x2 = (10 + rand()%30 + (rand()%1000000)/1000000.0);
		tri[i].x3 = (10 + rand()%30 + (rand()%1000000)/1000000.0);
		tri[i].y1 = (10 + rand()%30 + (rand()%1000000)/1000000.0);
		tri[i].y2 = (10 + rand()%30 + (rand()%1000000)/1000000.0);
		tri[i].y3 = (10 + rand()%30 + (rand()%1000000)/1000000.0);
	}
	computeArea(tri, n);
	findPrintInAngles(tri, n);
	return tri;
}

int main(int argc, char *argv[]) /*This is the main function*/
{
	int n;
	n = (argc > 1)? atoi(argv[1]) : 10;
	genTriangles(n);
	return 0;
}
