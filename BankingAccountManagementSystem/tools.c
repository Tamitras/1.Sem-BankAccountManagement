#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h> 
#include <limits.h>
#include <time.h>
#include "tools.h"

int default_accountNumber = 1337000;

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
		if (!isdigit(string[i]))
			return 0;
	return 1;
}

void PrintDatum()
{
	time_t rawtime;
	struct tm* info;
	time(&rawtime);
	info = localtime(&rawtime);

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
	if (!IsNumber(text)) // return zero if not a valid number
		return 0;

	int s = 0;
	int length = strlen(text);

	if (length == 3)
	{
		printf("!Eingegebene Zahl braucht keine Tausenderpunkte\n");
		return 0;
	}

	printf(" Laenge: %d\n", length);

	int number = atoi(text); // char to int
	char* str = calloc(12, sizeof(char));
	sprintf(str, "%d", number);

	s = strlen(str) / 3;
	int rest = strlen(str) % 3;
	if (rest > 0) // wenn rest
		s++;

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
				strncpy(temp, &text[0], 2);
				newText[nextDigit] = temp[0];
				newText[++nextDigit] = temp[1];
				newText[++nextDigit] = '.';
			}
			else if (length - (3 * (s - 1)) == 1)
			{
				strncpy(temp, &text[0], 1);
				newText[nextDigit] = temp[0];
				newText[++nextDigit] = '.';
			}
		}
		else
		{
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
		newText[nextDigit] = '\n';

	return s;
}

void SaveListInFile(BankAccount** head)
{
	BankAccount* current = *head;
	// Datei oeffnen
	accountFile = fopen("accounts.txt", "wb");

	if (accountFile == NULL) {
		// Create new file if not exist
		printf("Neue Datei wurde angelegt\n");
	}

	printf(RED"\t\t Dummy Daten wurden generiert\n"RESET);
	while (current != NULL) {

		char* prevName = current->prev ? ((BankAccount*)current->prev)->FirstName : "NULL(void*)";
		char* nextName = current->next ? ((BankAccount*)current->next)->FirstName : "NULL(void*)";

		// Write concatted string into fileStream
		fprintf(accountFile,
			"Id: %-4d;"
			"Vorname:%-14s;"
			"Nachname:%-14s;"
			"KontoNummer:%-14d;"
			"Davor:%-14s;"
			"Danach:%-14s"
			"\n",
			current->index,
			current->FirstName,
			current->LastName,
			current->AccountNumber,
			prevName,
			nextName);

		//fwrite(_BankAccountHead, sizeof(BankAccount), 1, accountFile);
		current = current->next;
	}

	fclose(accountFile);
	printf(GRN"\t\t Speichern erfolgreich\n\n" RESET);
}

int GetArrayLength(BankAccount** head)
{
	int counter = 0;
	BankAccount* current = *head;

	if (current != NULL && current->index >= 0)
	{
		counter = 1;

		while (current->next != NULL)
		{
			current = current->next;
			counter++;
		}
	}
	return counter;
}

int GetAccountNumber(BankAccount** head)
{
	BankAccount* current = *head;
	int accountNumber = current->AccountNumber;

	if (current != NULL && current->index >= 0)
	{
		while (current->next != NULL)
		{
			current = current->next;

			if (current->AccountNumber > accountNumber)
			{
				accountNumber = current->AccountNumber;
			}
		}
		accountNumber++;
	}
	else
	{
		accountNumber = default_accountNumber;
	}

	return accountNumber;
}


void AddDummyData()
{
	int index = GetArrayLength(&_BankAccountHead);
	BankAccount* acc1 = malloc(sizeof(BankAccount));
	BankAccount* acc2 = malloc(sizeof(BankAccount));
	BankAccount* acc3 = malloc(sizeof(BankAccount));
	BankAccount* acc4 = malloc(sizeof(BankAccount));
	BankAccount* acc5 = malloc(sizeof(BankAccount));
	BankAccount* acc6 = malloc(sizeof(BankAccount));
	BankAccount* acc7 = malloc(sizeof(BankAccount));
	BankAccount* acc8 = malloc(sizeof(BankAccount));
	BankAccount* acc9 = malloc(sizeof(BankAccount));
	BankAccount* acc10 = malloc(sizeof(BankAccount));

	acc1->FirstName = "Erik";
	acc1->LastName = "Kaufmann";
	acc1->AccountNumber = "123456";
	acc1->BirthDate = "06.07.1991";
	acc1->Adress = "Testwohnort";
	acc1->LastLogin = "11.02.2022";
	acc1->AccountNumber = GetAccountNumber(&_BankAccountHead);
	acc1->index = index++;
	acc1->next = NULL;
	acc1->prev = NULL;
	PushAtTheEnd(&_BankAccountHead, &acc1);

	acc2->FirstName = "Pascal";
	acc2->LastName = "Lorenz";
	acc2->AccountNumber = "99999";
	acc2->BirthDate = "01.01.2001";
	acc2->Adress = "Testwohnort";
	acc2->LastLogin = "11.02.2022";
	acc2->AccountNumber = GetAccountNumber(&_BankAccountHead);
	acc2->index = index++;
	acc2->next = NULL;
	acc2->prev = NULL;
	PushAtTheEnd(&_BankAccountHead, &acc2);

	acc3->FirstName = "Lukas";
	acc3->LastName = "Haaf";
	acc3->AccountNumber = "99999";
	acc3->BirthDate = "01.01.2001";
	acc3->Adress = "Testwohnort";
	acc3->LastLogin = "11.02.2022";
	acc3->AccountNumber = GetAccountNumber(&_BankAccountHead);
	acc3->index = index++;
	acc3->next = NULL;
	acc3->prev = NULL;
	PushAtTheEnd(&_BankAccountHead, &acc3);

	acc4->FirstName = "Donald";
	acc4->LastName = "Trump";
	acc4->AccountNumber = "99999";
	acc4->BirthDate = "01.01.2001";
	acc4->Adress = "Testwohnort";
	acc4->LastLogin = "11.02.2022";
	acc4->AccountNumber = GetAccountNumber(&_BankAccountHead);
	acc4->index = index++;
	acc4->next = NULL;
	acc4->prev = NULL;
	PushAtTheEnd(&_BankAccountHead, &acc4);

	acc5->FirstName = "Winfred";
	acc5->LastName = "Kretschmann";
	acc5->AccountNumber = "99999";
	acc5->BirthDate = "01.01.2001";
	acc5->Adress = "Testwohnort";
	acc5->LastLogin = "11.02.2022";
	acc5->AccountNumber = GetAccountNumber(&_BankAccountHead);
	acc5->index = index++;
	acc5->next = NULL;
	acc5->prev = NULL;
	PushAtTheEnd(&_BankAccountHead, &acc5);

	acc6->FirstName = "Freddy";
	acc6->LastName = "Krüger";
	acc6->AccountNumber = "99999";
	acc6->BirthDate = "01.01.2001";
	acc6->Adress = "Testwohnort";
	acc6->LastLogin = "11.02.2022";
	acc6->AccountNumber = GetAccountNumber(&_BankAccountHead);
	acc6->index = index++;
	acc6->next = NULL;
	acc6->prev = NULL;
	PushAtTheEnd(&_BankAccountHead, &acc6);

	acc7->FirstName = "Osama";
	acc7->LastName = "Binladen";
	acc7->AccountNumber = "99999";
	acc7->BirthDate = "01.01.2001";
	acc7->Adress = "Testwohnort";
	acc7->LastLogin = "11.02.2022";
	acc7->AccountNumber = GetAccountNumber(&_BankAccountHead);
	acc7->index = index++;
	acc7->next = NULL;
	acc7->prev = NULL;
	PushAtTheEnd(&_BankAccountHead, &acc7);

	acc8->FirstName = "Max";
	acc8->LastName = "Mustermann";
	acc8->AccountNumber = "99999";
	acc8->BirthDate = "01.01.2001";
	acc8->Adress = "Testwohnort";
	acc8->LastLogin = "11.02.2022";
	acc8->AccountNumber = GetAccountNumber(&_BankAccountHead);
	acc8->index = index++;
	acc8->next = NULL;
	acc8->prev = NULL;
	PushAtTheEnd(&_BankAccountHead, &acc8);

	acc9->FirstName = "Rolf";
	acc9->LastName = "Gerber";
	acc9->AccountNumber = "99999";
	acc9->BirthDate = "01.01.2001";
	acc9->Adress = "Testwohnort";
	acc9->LastLogin = "11.02.2022";
	acc9->AccountNumber = GetAccountNumber(&_BankAccountHead);
	acc9->index = index++;
	acc9->next = NULL;
	acc9->prev = NULL;
	PushAtTheEnd(&_BankAccountHead, &acc9);

	acc10->FirstName = "Liselotte";
	acc10->LastName = "Schutte";
	acc10->AccountNumber = "99999";
	acc10->BirthDate = "01.01.2001";
	acc10->Adress = "Testwohnort";
	acc10->LastLogin = "11.02.2022";
	acc10->AccountNumber = GetAccountNumber(&_BankAccountHead);
	acc10->index = index++;
	acc10->next = NULL;
	acc10->prev = NULL;
	PushAtTheEnd(&_BankAccountHead, &acc10);

	//PrintList(&_BankAccountHead, -1);

	// Save in File
	SaveListInFile(&_BankAccountHead);
}

BankAccount* CreateNode() {
	BankAccount* newNode = malloc(sizeof(BankAccount));
	newNode->next = NULL;
	return newNode;
}

/// <summary>
/// Add to the end
/// </summary>
/// <param name="head"></param>
/// <param name="val"></param>
void PushAtTheEnd(BankAccount** head, BankAccount** next) {

	BankAccount* current = *head;

	if (current->index == -1)
	{
		(*next)->next = NULL;
		(*next)->prev = NULL;
		*head = *next;
	}
	else
	{
		while (current->next != NULL) {
			current = current->next;
		}

		current->next = *next;
		(*next)->prev = current;
		(*next)->next = NULL;
	}
}

void PrintList(BankAccount** head, int toDelete)
{
	char* result = malloc(1024 * sizeof(char));
	char* temp = malloc(1024 * sizeof(char));
	char prevName[100];
	char nextName[100];

	BankAccount* current = *head;

	while (current && current->index > -1)
	{
		BankAccount* prev = current->prev;
		BankAccount* next = current->next;

		if (prev)
			strcpy(prevName, prev->FirstName);
		else
			strcpy(prevName, "NULL(void*)");

		if (next)
			strcpy(nextName, next->FirstName);
		else
			strcpy(nextName, "NULL(void*)");

		snprintf(result,
			1024,
			"Vorname: %-14s;"
			"Nachname: %-14s;"
			"KontoNummer: %-14d;"
			"Davor: %-14s;"
			"Danach: %-14s"
			"Id: "
			YEL"(%d) "RESET,
			current->FirstName,
			current->LastName,
			current->AccountNumber,
			prevName,
			nextName,
			current->index);

		if (current->index == toDelete)
			//printf("%s"RED"<delete>"RESET"\head", result);
			printf(RED"%s\n"RESET, result);
		else
			printf("%s\n", result);

		current = current->next;
	}

	free(result);
	free(temp);
}

void remove_spaces(char* s)
{
	char* d = s;
	do {
		while (*d == ' ') {
			++d;
		}
	} while (*s++ = *d++);
}
// Public End