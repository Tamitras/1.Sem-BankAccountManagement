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

void SaveListInFile(BankAccount* head)
{
	// Datei oeffnen
	fStream = fopen("accounts.txt", "wb");

	if (fStream == NULL) {
		// Create new file if not exist
		printf("Neue Datei wurde angelegt\n");
	}

	printf("\t\t Dummy Daten werden als TXT gespeichert\n\n");
	while (_BankAccountHead != NULL) {

		char* prevName = ((BankAccount*)_BankAccountHead->prev) ? ((BankAccount*)_BankAccountHead->prev)->FirstName : "NULL(void*)";
		char* nextName = ((BankAccount*)_BankAccountHead->next) ? ((BankAccount*)_BankAccountHead->next)->FirstName : "NULL(void*)";

		// Write concatted string into fileStream
		fprintf(fStream,
			"Vorname: %-14s;"
			"Nachname: %-14s;"
			"KontoNummer: %-14d;"
			"Davor: %-14s;"
			"Danach: %-14s"
			"\n",
			_BankAccountHead->FirstName,
			_BankAccountHead->LastName,
			_BankAccountHead->AccountNumber,
			prevName,
			nextName);

		//fwrite(_BankAccountHead, sizeof(BankAccount), 1, fStream);
		_BankAccountHead = _BankAccountHead->next;
	}

	fclose(fStream);
	printf(GRN"\t\t Speichern erfolgreich\n\n" RESET);
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
	acc1->BirthDate = "06.07.1991";
	acc1->Adress = "Testwohnort";
	acc1->LastLogin = "11.02.2022";
	acc1->AccountNumber = default_accountNumber++;
	PushAtTheEnd(_BankAccountHead, acc1);

	acc2->FirstName = "Pascal";
	acc2->LastName = "Lorenz";
	acc2->AccountNumber = "99999";
	acc2->BirthDate = "01.01.2001";
	acc2->Adress = "Testwohnort";
	acc2->LastLogin = "11.02.2022";
	acc2->AccountNumber = default_accountNumber++;
	PushAtTheEnd(_BankAccountHead, acc2);

	acc3->FirstName = "Lukas";
	acc3->LastName = "Haaf";
	acc3->AccountNumber = "99999";
	acc3->BirthDate = "01.01.2001";
	acc3->Adress = "Testwohnort";
	acc3->LastLogin = "11.02.2022";
	acc3->AccountNumber = default_accountNumber++;
	PushAtTheEnd(_BankAccountHead, acc3);

	acc4->FirstName = "Donald";
	acc4->LastName = "Trump";
	acc4->AccountNumber = "99999";
	acc4->BirthDate = "01.01.2001";
	acc4->Adress = "Testwohnort";
	acc4->LastLogin = "11.02.2022";
	acc4->AccountNumber = default_accountNumber++;
	PushAtTheEnd(_BankAccountHead, acc4);

	acc5->FirstName = "Winfred";
	acc5->LastName = "Kretschmann";
	acc5->AccountNumber = "99999";
	acc5->BirthDate = "01.01.2001";
	acc5->Adress = "Testwohnort";
	acc5->LastLogin = "11.02.2022";
	acc5->AccountNumber = default_accountNumber++;
	PushAtTheEnd(_BankAccountHead, acc5);

	acc6->FirstName = "Freddy";
	acc6->LastName = "Krüger";
	acc6->AccountNumber = "99999";
	acc6->BirthDate = "01.01.2001";
	acc6->Adress = "Testwohnort";
	acc6->LastLogin = "11.02.2022";
	acc6->AccountNumber = default_accountNumber++;
	PushAtTheEnd(_BankAccountHead, acc6);

	acc7->FirstName = "Osama";
	acc7->LastName = "Binladen";
	acc7->AccountNumber = "99999";
	acc7->BirthDate = "01.01.2001";
	acc7->Adress = "Testwohnort";
	acc7->LastLogin = "11.02.2022";
	acc7->AccountNumber = default_accountNumber++;
	PushAtTheEnd(_BankAccountHead, acc7);

	acc8->FirstName = "Max";
	acc8->LastName = "Mustermann";
	acc8->AccountNumber = "99999";
	acc8->BirthDate = "01.01.2001";
	acc8->Adress = "Testwohnort";
	acc8->LastLogin = "11.02.2022";
	acc8->AccountNumber = default_accountNumber++;
	PushAtTheEnd(_BankAccountHead, acc8);

	acc9->FirstName = "Rolf";
	acc9->LastName = "Gerber";
	acc9->AccountNumber = "99999";
	acc9->BirthDate = "01.01.2001";
	acc9->Adress = "Testwohnort";
	acc9->LastLogin = "11.02.2022";
	acc9->AccountNumber = default_accountNumber++;
	PushAtTheEnd(_BankAccountHead, acc9);

	acc10->FirstName = "Liselotte";
	acc10->LastName = "Schutte";
	acc10->AccountNumber = "99999";
	acc10->BirthDate = "01.01.2001";
	acc10->Adress = "Testwohnort";
	acc10->LastLogin = "11.02.2022";
	acc10->AccountNumber = default_accountNumber++;
	PushAtTheEnd(_BankAccountHead, acc10);

	// Save in File
	SaveListInFile(_BankAccountHead);

	free(acc1);
	free(acc2);
	free(acc3);
	free(acc4);
	free(acc5);
	free(acc6);
	free(acc7);
	free(acc8);
	free(acc9);
	free(acc10);
}

BankAccount CreateBankAccount() {
	//BankAccount * temp= malloc(sizeof(BankAccount));	// allocate memory using malloc()
	//temp->next = temp->prev = NULL;						// make next point to NULL
	//temp->FirstName = "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";


	BankAccount temp;
	temp.next = temp.prev = NULL;
	temp.FirstName = "!!!!!!!!!!!!!!!!!!!!!!!";
	return temp;										//return the new node
}

void PushAtTheEnd(BankAccount** head, BankAccount** newAccount)
{
	if (head != NULL)
	{
		BankAccount* lastNode = ((BankAccount*)head);
		BankAccount* newNode = ((BankAccount*)newAccount);

		while (lastNode->next != NULL)
			lastNode = lastNode->next;

		newNode->prev = lastNode;
		lastNode->next = newNode;
		newNode->next = NULL;

		//printf("Added: %s %s \n", ((BankAccount*)newAccount)->FirstName, ((BankAccount*)newAccount)->LastName);
	}
	else
	{
		_BankAccountHead = _BankAccountTail = (BankAccount*)newAccount;
		_BankAccountHead->next = _BankAccountTail->next = NULL;
		_BankAccountHead->prev = _BankAccountTail->prev = NULL;
		//printf("Initial hinzugefügt: %s %s \n", ((BankAccount*)newAccount)->FirstName, ((BankAccount*)newAccount)->LastName);
	}
}

void PrintList(BankAccount* n, int highlightNewest)
{
	printf("------------------------------------\n");
	char* result = malloc(1024 * sizeof(char));
	char* temp = malloc(1024 * sizeof(char));

	while (n != NULL)
	{
		BankAccount* prev = (BankAccount*)n->prev;
		BankAccount* next = (BankAccount*)n->next;
		char* prevName = ((BankAccount*)n->prev) ? ((BankAccount*)n->prev)->FirstName : "NULL(void*)";
		char* nextName = ((BankAccount*)n->next) ? ((BankAccount*)n->next)->FirstName : "NULL(void*)";

		sprintf(result,
			"Vorname: %-14s;"
			"Nachname: %-14s;"
			"KontoNummer: %-14d;"
			"Davor: %-14s;"
			"Danach: %-14s",
			n->FirstName,
			n->LastName,
			n->AccountNumber,
			prevName,
			nextName);		

		if (highlightNewest)
		{
			if (n->next)
				printf("%s\n", result);
			else
			{
				printf(YEL"\n\t\t\t\t\t -------- new --------\n" RESET);
				printf(GRN"%s\n\n"RESET, result);
			}
		}
		else
			printf("%s\n", result);

		n = n->next;
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
// Public End