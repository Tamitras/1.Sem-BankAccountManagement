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

		//fwrite(_BankAccountHead, sizeof(BankAccount), 1, accountFile);
		current = current->next;
	}

	fclose(accountFile);
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

int GetAccountNumber(BankAccount** head)
{
	BankAccount* current = *head;
	int accountNumber = current->AccountNumber;

	if (current != NULL && current->Id >= 0)
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
	acc1->AccountNumber = GetAccountNumber(&_BankAccountHead);
	acc1->Id = GetNewId(&_BankAccountHead);
	acc1->next = NULL;
	acc1->prev = NULL;
	PushAtTheEnd(&_BankAccountHead, &acc1);

	acc2->FirstName = "Pascal";
	acc2->LastName = "Lorenz";
	acc2->AccountNumber = "99999";
	acc2->Adress = "Testwohnort";
	acc2->LastLogin = "11.02.2022";
	acc2->AccountNumber = GetAccountNumber(&_BankAccountHead);
	acc2->Id = GetNewId(&_BankAccountHead);
	acc2->next = NULL;
	acc2->prev = NULL;
	PushAtTheEnd(&_BankAccountHead, &acc2);

	acc3->FirstName = "Lukas";
	acc3->LastName = "Haaf";
	acc3->AccountNumber = "99999";
	acc3->Adress = "Testwohnort";
	acc3->LastLogin = "11.02.2022";
	acc3->AccountNumber = GetAccountNumber(&_BankAccountHead);
	acc3->Id = GetNewId(&_BankAccountHead);
	acc3->next = NULL;
	acc3->prev = NULL;
	PushAtTheEnd(&_BankAccountHead, &acc3);

	acc4->FirstName = "Donald";
	acc4->LastName = "Trump";
	acc4->AccountNumber = "99999";
	acc4->Adress = "Testwohnort";
	acc4->LastLogin = "11.02.2022";
	acc4->AccountNumber = GetAccountNumber(&_BankAccountHead);
	acc4->Id = GetNewId(&_BankAccountHead);
	acc4->next = NULL;
	acc4->prev = NULL;
	PushAtTheEnd(&_BankAccountHead, &acc4);

	acc5->FirstName = "Winfred";
	acc5->LastName = "Kretschmann";
	acc5->AccountNumber = "99999";
	acc5->Adress = "Testwohnort";
	acc5->LastLogin = "11.02.2022";
	acc5->AccountNumber = GetAccountNumber(&_BankAccountHead);
	acc5->Id = GetNewId(&_BankAccountHead);
	acc5->next = NULL;
	acc5->prev = NULL;
	PushAtTheEnd(&_BankAccountHead, &acc5);

	acc6->FirstName = "Freddy";
	acc6->LastName = "Krüger";
	acc6->AccountNumber = "99999";
	acc6->Adress = "Testwohnort";
	acc6->LastLogin = "11.02.2022";
	acc6->AccountNumber = GetAccountNumber(&_BankAccountHead);
	acc6->Id = GetNewId(&_BankAccountHead);
	acc6->next = NULL;
	acc6->prev = NULL;
	PushAtTheEnd(&_BankAccountHead, &acc6);

	acc7->FirstName = "Osama";
	acc7->LastName = "Binladen";
	acc7->AccountNumber = "99999";
	acc7->Adress = "Testwohnort";
	acc7->LastLogin = "11.02.2022";
	acc7->AccountNumber = GetAccountNumber(&_BankAccountHead);
	acc7->Id = GetNewId(&_BankAccountHead);
	acc7->next = NULL;
	acc7->prev = NULL;
	PushAtTheEnd(&_BankAccountHead, &acc7);

	acc8->FirstName = "Max";
	acc8->LastName = "Mustermann";
	acc8->AccountNumber = "99999";
	acc8->Adress = "Testwohnort";
	acc8->LastLogin = "11.02.2022";
	acc8->AccountNumber = GetAccountNumber(&_BankAccountHead);
	acc8->Id = GetNewId(&_BankAccountHead);
	acc8->next = NULL;
	acc8->prev = NULL;
	PushAtTheEnd(&_BankAccountHead, &acc8);

	acc9->FirstName = "Rolf";
	acc9->LastName = "Gerber";
	acc9->AccountNumber = "99999";
	acc9->Adress = "Testwohnort";
	acc9->LastLogin = "11.02.2022";
	acc9->AccountNumber = GetAccountNumber(&_BankAccountHead);
	acc9->Id = GetNewId(&_BankAccountHead);
	acc9->next = NULL;
	acc9->prev = NULL;
	PushAtTheEnd(&_BankAccountHead, &acc9);

	acc10->FirstName = "Liselotte";
	acc10->LastName = "Schutte";
	acc10->AccountNumber = "99999";
	acc10->Adress = "Testwohnort";
	acc10->LastLogin = "11.02.2022";
	acc10->AccountNumber = GetAccountNumber(&_BankAccountHead);
	acc10->Id = GetNewId(&_BankAccountHead);
	acc10->next = NULL;
	acc10->prev = NULL;
	PushAtTheEnd(&_BankAccountHead, &acc10);


	// Save in File
	SaveListInFile(&_BankAccountHead);
	printf(RED"\t\t Dummy Daten wurden generiert\n"RESET);
}

BankAccount* CreateNode() {
	BankAccount* newNode = malloc(sizeof(BankAccount));
	newNode->next = NULL;
	return newNode;
}

/*Function to swap the nodes */
BankAccount* swap(BankAccount* ptr1, BankAccount* ptr2)
{
	// Hilfspointer
	BankAccount* A = ptr1->prev;
	BankAccount* B = ptr1;
	BankAccount* C = ptr2;
	BankAccount* D = ptr2->next;

	// Swapping
	if (A)
		A->next = C;
	B->prev = C;
	B->next = D;
	C->prev = A;
	C->next = B;
	if (D)
		D->prev = B;

	return ptr2;
}

void Sort(BankAccount** head, SortType type)
{
	int marked[1] = { -1 };
	int count = GetArrayLength(&_BankAccountHead);
	BankAccount** h;
	int i, j, swapped;

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
				break;
			case LastName:
				if (strcmp(p1->LastName, p2->LastName) > 0) {
					*h = swap(p1, p2);
					swapped = 1;
				}
				break;
			case AccountNumber:
				if (p1->AccountNumber > p2->AccountNumber) {
					*h = swap(p1, p2);
					swapped = 1;
				}
				break;
			case Id:
				if (p1->Id > p2->Id) {
					*h = swap(p1, p2);
					swapped = 1;
				}
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
	SaveListInFile(&_BankAccountHead);
	printf(GRN"\t\t Sorted successfully\n\n" RESET);
	PrintList(&_BankAccountHead, marked, 1, 25);
}

/// <summary>
/// Add to the end
/// </summary>
/// <param name="head"></param>
/// <param name="val"></param>
void PushAtTheEnd(BankAccount** head, BankAccount** next) {

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

int contains(int* array, int key, int len)
{
	for (int i = 0; i < len; i++)
	{
		if (key == array[i])
			return 1;
	}
	return 0;
}

void PrintList(BankAccount** head, int* toDelete, int arrayLen, int limit)
{
	char* result = malloc(1024 * sizeof(char));
	char* temp = malloc(1024 * sizeof(char));
	char* prevName = malloc(100 * sizeof(char));
	char* nextName = malloc(100 * sizeof(char));
	int limitCounter = 0;

	BankAccount* current = *head;

	while (current && current->Id > -1)
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

		

		int Id = contains(toDelete, current->Id, arrayLen);

		if (Id > 0)
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
			snprintf(result, 1024, YEL" (%d)"RESET CYN"\tVorname: "RESET"%-15s"BLK";"RESET CYN"Nachname: "RESET"%-15s"BLK";"RESET CYN"KontoNummer: "RESET"%-15d"BLK";"RESET
				CYN"Davor: "RESET"%-15s"BLK";"RESET CYN"Danach: "RESET"%-15s", current->Id, current->FirstName, current->LastName,
				current->AccountNumber, prevName, nextName);
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

	printf("\n\n");
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