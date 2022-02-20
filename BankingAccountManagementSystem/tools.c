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

void remove_spaces(char* s)
{
	char* d = s;
	do {
		while (*d == ' ') {
			++d;
		}
	} while (*s++ = *d++);
}

int containsInIntArray(int* array, int key, int len)
{
	for (int i = 0; i < len; i++)
	{
		if (key == array[i])
			return 1;
	}
	return 0;
}

int contains(int key)
{
	BankAccount* current = _BankAccountHead;

	if (current != NULL && current->Id >= 0)
	{
		for (int i = 1; i < 100000; i++)
		{
			while (current)
			{
				if (current->Id == key)
					return 1;

				current = current->next;
			}
		}
	}

	return 0;
}

/// <summary>
/// Function to swap pointers
/// </summary>
/// <param name="ptr1"></param>
/// <param name="ptr2"></param>
/// <returns></returns>
BankAccount* swap(BankAccount* ptr1, BankAccount* ptr2)
{
	// Hilfspointer
	BankAccount* a = ptr1->prev;
	BankAccount* b = ptr1;
	BankAccount* c = ptr2;
	BankAccount* d = ptr2->next;

	// Swapping
	if (a)
		a->next = c;
	b->prev = c;
	b->next = d;
	c->prev = a;
	c->next = b;
	if (d)
		d->prev = b;

	return ptr2;
}

// Private End

// Public Start

void SaveListInFile(BankAccount** head)
{
	BankAccount* current = *head;

	if (current == NULL)
	{
		// Security Warning - not allowed to overwrite file with an empty list.
		printf(RED "\n\Fehler! Liste ist leer - Datei kann nicht %sberschrieben werden \n\n" RESET, "\x81");
		system("pause");
		system("cls");
		return 0;
	}

	// Open file
	accountFile = fopen("accounts.txt", "wb");

	if (accountFile == NULL) {
		// Create new file if not exist
		printf("Neue Datei wurde angelegt\n");
	}

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
			current->Id,
			current->FirstName,
			current->LastName,
			current->AccountNumber,
			prevName,
			nextName);

		current = current->next;
	}

	fclose(accountFile);

	printf(GRN"\t\Daten wurden erfolgreich in Datei geschrieben"RESET"\n\n");
	system("pause");
	system("cls");
}

int GetArrayLength(BankAccount** head)
{
	int counter = 0;
	BankAccount* current = *head;

	if (current != NULL && current->Id >= 0)
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

int GetNewId()
{
	int searching = 1;
	BankAccount* current = _BankAccountHead;

	if (current != NULL && current->Id >= 0)
	{
		for (int i = 1; i < 100000; i++)
		{
			while (current && searching)
			{
				if (current->Id == i)
					searching = 0;

				current = current->next;
			}

			if (searching == 1)
			{
				// found unused id
				return i;
			}

			// still searching
			searching = 1;
			current = _BankAccountHead;
		}
	}
	else
	{
		//first id
		return 1;
	}
	return -1;
}

int GetAccountNumber(BankAccount* head)
{
	int accountNumber = 0;
	BankAccount* current = head;

	if (current != NULL && current->Id >= 0)
	{
		accountNumber = current->AccountNumber;

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
	acc1->Adress = "Testwohnort";
	acc1->LastLogin = "11.02.2022";
	acc1->AccountNumber = GetAccountNumber(_BankAccountHead);
	acc1->Id = GetNewId(&_BankAccountHead);
	acc1->next = NULL;
	acc1->prev = NULL;
	PushAtTheEnd(&_BankAccountHead, &acc1);

	acc2->FirstName = "Brad";
	acc2->LastName = "Pitt";
	acc2->AccountNumber = "99999";
	acc2->Adress = "Testwohnort";
	acc2->LastLogin = "11.02.2022";
	acc2->AccountNumber = GetAccountNumber(_BankAccountHead);
	acc2->Id = GetNewId(&_BankAccountHead);
	acc2->next = NULL;
	acc2->prev = NULL;
	PushAtTheEnd(&_BankAccountHead, &acc2);

	acc3->FirstName = "Arnold";
	acc3->LastName = "Schwarzenegger";
	acc3->AccountNumber = "99999";
	acc3->Adress = "Testwohnort";
	acc3->LastLogin = "11.02.2022";
	acc3->AccountNumber = GetAccountNumber(_BankAccountHead);
	acc3->Id = GetNewId(&_BankAccountHead);
	acc3->next = NULL;
	acc3->prev = NULL;
	PushAtTheEnd(&_BankAccountHead, &acc3);

	acc4->FirstName = "Donald";
	acc4->LastName = "Trump";
	acc4->AccountNumber = "99999";
	acc4->Adress = "Testwohnort";
	acc4->LastLogin = "11.02.2022";
	acc4->AccountNumber = GetAccountNumber(_BankAccountHead);
	acc4->Id = GetNewId(&_BankAccountHead);
	acc4->next = NULL;
	acc4->prev = NULL;
	PushAtTheEnd(&_BankAccountHead, &acc4);

	acc5->FirstName = "Winfred";
	acc5->LastName = "Kretschmann";
	acc5->AccountNumber = "99999";
	acc5->Adress = "Testwohnort";
	acc5->LastLogin = "11.02.2022";
	acc5->AccountNumber = GetAccountNumber(_BankAccountHead);
	acc5->Id = GetNewId(&_BankAccountHead);
	acc5->next = NULL;
	acc5->prev = NULL;
	PushAtTheEnd(&_BankAccountHead, &acc5);

	acc6->FirstName = "Freddy";
	acc6->LastName = "Krueger";
	acc6->AccountNumber = "99999";
	acc6->Adress = "Testwohnort";
	acc6->LastLogin = "11.02.2022";
	acc6->AccountNumber = GetAccountNumber(_BankAccountHead);
	acc6->Id = GetNewId(&_BankAccountHead);
	acc6->next = NULL;
	acc6->prev = NULL;
	PushAtTheEnd(&_BankAccountHead, &acc6);

	acc7->FirstName = "Angelo";
	acc7->LastName = "Merte";
	acc7->AccountNumber = "99999";
	acc7->Adress = "Testwohnort";
	acc7->LastLogin = "11.02.2022";
	acc7->AccountNumber = GetAccountNumber(_BankAccountHead);
	acc7->Id = GetNewId(&_BankAccountHead);
	acc7->next = NULL;
	acc7->prev = NULL;
	PushAtTheEnd(&_BankAccountHead, &acc7);

	acc8->FirstName = "Max";
	acc8->LastName = "Mustermann";
	acc8->AccountNumber = "99999";
	acc8->Adress = "Testwohnort";
	acc8->LastLogin = "11.02.2022";
	acc8->AccountNumber = GetAccountNumber(_BankAccountHead);
	acc8->Id = GetNewId(&_BankAccountHead);
	acc8->next = NULL;
	acc8->prev = NULL;
	PushAtTheEnd(&_BankAccountHead, &acc8);

	acc9->FirstName = "Rolf";
	acc9->LastName = "Gerber";
	acc9->AccountNumber = "99999";
	acc9->Adress = "Testwohnort";
	acc9->LastLogin = "11.02.2022";
	acc9->AccountNumber = GetAccountNumber(_BankAccountHead);
	acc9->Id = GetNewId(&_BankAccountHead);
	acc9->next = NULL;
	acc9->prev = NULL;
	PushAtTheEnd(&_BankAccountHead, &acc9);

	acc10->FirstName = "Veronika";
	acc10->LastName = "Poth";
	acc10->AccountNumber = "99999";
	acc10->Adress = "Testwohnort";
	acc10->LastLogin = "11.02.2022";
	acc10->AccountNumber = GetAccountNumber(_BankAccountHead);
	acc10->Id = GetNewId(&_BankAccountHead);
	acc10->next = NULL;
	acc10->prev = NULL;
	PushAtTheEnd(&_BankAccountHead, &acc10);

	printf(RED"\t\t Testdaten erstellt"RESET);
}

BankAccount* CreateNode() {
	BankAccount* newNode = malloc(sizeof(BankAccount));
	newNode->next = NULL;
	return newNode;
}

void Sort(BankAccount** head, SortType type)
{
	int i, j, swapped;
	int marked[1] = { -1 };
	int count = GetArrayLength(&_BankAccountHead);
	char* sortTypeAsString = malloc(100 * sizeof(char));
	BankAccount** h;

	if (*head == NULL)
		return 0;

	for (i = 0; i <= count; i++) {

		h = head;
		swapped = 0;

		for (j = 0; j < count - i - 1; j++) {

			BankAccount* p1 = *h;
			BankAccount* p2 = p1->next;

			switch (type)
			{
			case FirstName:
				if (strcmp(p1->FirstName, p2->FirstName) > 0) {
					*h = swap(p1, p2);
					swapped = 1;
				}
				strcpy(sortTypeAsString, "Vorname");
				break;
			case LastName:
				if (strcmp(p1->LastName, p2->LastName) > 0) {
					*h = swap(p1, p2);
					swapped = 1;
				}
				strcpy(sortTypeAsString, "Nachname");
				break;
			case AccountNumber:
				if (p1->AccountNumber > p2->AccountNumber) {
					*h = swap(p1, p2);
					swapped = 1;
				}
				strcpy(sortTypeAsString, "Kontonummer");
				break;
			case Id:
				if (p1->Id > p2->Id) {
					*h = swap(p1, p2);
					swapped = 1;
				}
				strcpy(sortTypeAsString, "Id");
				break;
			default:
				break;
			}

			h = &(*h)->next;
		}

		/* break if the loop ended without any swap */
		if (swapped == 0)
			break;
	}

	printf(GRN"\t\t Erfolgreich sortiert (%s)\n\n" RESET, sortTypeAsString);
	PrintList(&_BankAccountHead, marked, 1, 25);

	free(sortTypeAsString);
}

/// <summary>
/// Add to the end
/// </summary>
/// <param name="head"></param>
/// <param name="val"></param>
void PushAtTheEnd(BankAccount** head, BankAccount** next)
{
	if (_BankAccountHead == NULL)
	{
		_BankAccountHead = malloc(sizeof(BankAccount));
		_BankAccountHead->Id = -1;
		*head = _BankAccountHead;
	}

	BankAccount* current = *head;

	if (current->Id == -1)
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

void PrintList(BankAccount** head, int* toDelete, int arrayLen, int limit)
{
	char* result = malloc(1024 * sizeof(char));
	char* temp = malloc(1024 * sizeof(char));
	char* prevName = malloc(100 * sizeof(char));
	char* nextName = malloc(100 * sizeof(char));
	int limitCounter = 0;

	BankAccount* current = *head;

	if (GetArrayLength(&_BankAccountHead) > 0) // Data avaiable
	{
		while (current != NULL && current->Id > -1)
		{
			BankAccount* prev = current->prev;
			BankAccount* next = current->next;

			if (prev)
				prevName = _strdup(prev->FirstName);
			else
				prevName = _strdup("NULL(void*)");

			if (next)
				nextName = _strdup(next->FirstName);
			else
				nextName = _strdup("NULL(void*)");

			if (containsInIntArray(toDelete, current->Id, arrayLen) > 0)
			{
				snprintf(result,
					1024,
					" (%d)\tVorname: %-15s"
					" Nachname: %-15s"
					" KontoNummer: %-15d"
					" Davor: %-15s"
					" Danach: %-15s",
					current->Id,
					current->FirstName,
					current->LastName,
					current->AccountNumber,
					prevName,
					nextName);
				printf(RED"%s\n"RESET, result);
			}
			else
			{
				snprintf(result,
					1024,
					YEL" (%d)"RESET
					CYN"\tVorname: "RESET
					"%-15s"BLK";"RESET
					CYN"Nachname: "RESET
					"%-15s"BLK";"RESET
					CYN"KontoNummer: "RESET
					"%-15d"BLK";"RESET
					CYN"Davor: "RESET
					"%-15s"BLK";"RESET
					CYN"Danach: "RESET
					"%-15s",
					current->Id,
					current->FirstName,
					current->LastName,
					current->AccountNumber,
					prevName,
					nextName);
				printf("%s\n", result);
			}

			limitCounter++;

			if (limit > 0 && limitCounter == limit)
			{
				system("pause");
				limitCounter = 0;
			}
			current = current->next;
		}
	}
	else
	{
		printf(RED "\n\tEs sind noch keine Daten im Speicher vorhanden, bitte erstellen Sie oder Laden aus der Datei\n\n" RESET);
		system("pause");
		system("cls");
	}

	//printf("\n\n");
	free(result);
	free(temp);
}

void FreeArray(BankAccount** head)
{
	BankAccount* current = *head;
	BankAccount* temp = NULL;

	while (current != NULL)
	{
		temp = current->next;
		free(current);
		current = temp;
	}
}

// Public End