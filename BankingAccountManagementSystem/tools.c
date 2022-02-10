#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h> 
#include <limits.h>
#include <time.h>
#include "tools.h"


void initArray(BankAccounts* a, size_t initialSize) {
	a->array = malloc(initialSize * sizeof(int));
	a->used = 0;
	a->size = initialSize;
}

void insertArray(BankAccounts* a, BankAccount * element) {
	// a->used is the number of used entries, because a->array[a->used++] updates a->used only *after* the array has been accessed.
	// Therefore a->used can go up to a->size 
	if (a->used == a->size) {
		a->size *= 2;
		a->array = realloc(a->array, a->size * sizeof(int));
	}
	a->array[a->used++] = element;
}

void freeArray(BankAccounts* a) {
	free(a->array);
	a->array = NULL;
	a->used = a->size = 0;
}

// Private Start
void initMultiArray(char** p, int m, int n)
{
	// dynamically allocate memory of size `n` for each row
	for (int r = 0; r < m; r++) {
		p[r] = (int*)calloc(n, sizeof(char));
	}
}
// Private End


// Public Start

int IsNumber(char* string)
{
	// return 0 --> not a number
	// return 1 -->  is a number

	for (int i = 0; i < strlen(string); i++)
	{
		if (!isdigit(string[i]))
		{
			return 0;
		}
	}

	return 1;
}

void PrintDatum()
{
	time_t rawtime;
	struct tm* info;
	time(&rawtime);
#pragma warning(suppress : 4996)
	info = localtime(&rawtime);

#pragma warning(suppress : 4996)
	printf("\n\nCurrent local time and date: %s", asctime(info));
}

void HoldTerminal()
{
	char s[80];
	char temp[255];
	char exit[255];

	strcpy_s(temp, sizeof(temp), "en");
	strcpy_s(exit, sizeof(exit), "Schlie\xe1");

	strcat_s(exit, sizeof(exit), temp);

	PrintDatum();
	printf("\n%s mit Enter...", exit);
	fgets(s, sizeof s, stdin);
}

int SeparateThousands(char* text)
{
	int s = 0;

	if (!IsNumber(text)) // return zero if not a valid number
	{
		return 0;
	}

	int length = strlen(text);

	if (length == 3)
	{
		printf("!Eingegebene Zahl braucht keine Tausenderpunkte\n");
		return 0;
	}

	printf(" Laenge: %d\n", length);

	int number = atoi(text); // char to int
	char* str = calloc(12, sizeof(char));
#pragma warning(suppress : 4996)
	sprintf(str, "%d", number);

	s = strlen(str) / 3;
	int rest = strlen(str) % 3;
	if (rest > 0) // wenn rest
	{
		s++;
	}

	// ** means multiArray[x][y] 2D
	char** subStrings = calloc((s + 1), sizeof(unsigned char*));
	initMultiArray(subStrings, s + 1, 4);

	char* newText = calloc(255, sizeof(char));
	int nextDigit = 0;

	for (int i = 0; i < s; i++)
	{
		char temp[3];

		if (i == 0 && rest > 0)
		{
			if (length - (3 * (s - 1)) == 2)
			{
#pragma warning(suppress : 4996)
				strncpy(temp, &text[0], 2);
				newText[nextDigit] = temp[0];
				newText[++nextDigit] = temp[1];
				newText[++nextDigit] = '.';
			}
			else if (length - (3 * (s - 1)) == 1)
			{
#pragma warning(suppress : 4996)
				strncpy(temp, &text[0], 1);
				newText[nextDigit] = temp[0];
				newText[++nextDigit] = '.';
			}
		}
		else
		{
#pragma warning(suppress : 4996)
			strncpy(temp, &text[length - (s - i) * 3], 3);

			for (int p = 0; p < 3; p++)
			{
				if (nextDigit == 0 && p == 0)
				{
					newText[nextDigit] = temp[p];
				}
				else
				{
					newText[++nextDigit] = temp[p];
				}
			}
			newText[++nextDigit] = '.';
		}
	}

	if (newText[nextDigit] == '.')
	{
		newText[nextDigit] = '\n';
	}

	return s;
}
// Public End