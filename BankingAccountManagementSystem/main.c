#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include "tools.h"

BankAccount* _BankAccountHead;

// Dateizeiger erstellen
FILE* accountFile;
FILE* accountPasswordFile;
FILE* accountTransactionFile;

void CloseApp(void)
{
	system("cls");
	printf(GRN"\n\n\t\tVielen Dank für Ihren Besuch"RESET"\n\n");
	fflush(stdout);
	for (int i = 5; i != 0; i--)
	{
		printf(WHT"\r\t\tSie werden in     "MAG" %d"RESET"     Sekunden automatisch ausgeloggt.", i);
		fflush(stdout);
		Sleep(1000);
	}

	return 1;
}

/* Given a reference (pointer to pointer) to the head of a
   list and a key, deletes the first occurrence of key in
   linked list */
void deleteBankAccount(BankAccount** head, int key)
{
	// Store head node
	BankAccount* temp = *head;
	BankAccount* prev = NULL;
	BankAccount* idPtr = NULL;

	// If head node itself holds the key to be deleted
	if (temp != NULL && temp->index == key) {
		*head = temp->next; // Changed head
		(*head)->prev = NULL;

		// id adjustment
		while (idPtr->next != NULL)
		{
			idPtr = idPtr->next;
			idPtr->index--;
		}

		free(temp); // free old head
		return;
	}

	// Search for the key to be deleted, keep track of the
	// previous node as we need to change 'prev->next'
	while (temp != NULL && temp->index != key) {
		prev = temp;
		temp = temp->next;
	}

	// If key was not present in linked list
	if (temp == NULL)
		return;

	idPtr = temp;

	// id adjustment
	while (idPtr->next != NULL)
	{
		idPtr = idPtr->next;
		idPtr->index--;
	}

	// Unlink the node from linked list
	prev->next = temp->next;
	if (((BankAccount*)temp->next) != NULL)
	{
		((BankAccount*)temp->next)->prev = prev;
	}

	free(temp); // Free memory
}

void RemoveAccount()
{
	int index = -1;
	int decision = -1;
	char indexAsChar[100];
	char decisionAsChar[100];

	int arrayLength = GetArrayLength(&_BankAccountHead);

	printf("\n\n\t\tWählen Sie einen Index den sie Löschen möchten\n\t\t# ");
	scanf("%s", indexAsChar);
	index = atoi(indexAsChar);

	if (index < arrayLength)
	{
		system("cls");
		PrintList(&_BankAccountHead, index);

		printf("\n\n");
		printf("\t\tAbbruch mit    (%d)\n", 0);
		printf("\t\tBestätigen mit (%d)\n", 1);
		printf("\t\tErneut wählen  (%d)\n\t\t# ", 2);
		scanf("%s", decisionAsChar);
		decision = atoi(decisionAsChar);

		if (decision != 0)
		{
			if (decision == 2)
			{
				system("cls");
				RemoveAccount();
			}
			else
			{
				deleteBankAccount(&_BankAccountHead, index);
				system("cls");
				PrintList(&_BankAccountHead, -1);
				SaveListInFile(&_BankAccountHead);
			}
		}
		else
		{
			system("cls");
		}
	}
	else
	{
		system("cls");
		printf(YEL"Datensatz mit dem Index (%d) nicht gefunden:\n\n" RESET, index);
		PrintList(&_BankAccountHead, -1);
		RemoveAccount();
	}
}

void CreateNewAccount(void)
{
	int current = GetArrayLength(&_BankAccountHead);
	BankAccount* newBankAccount = CreateNode();
	char birthDate[250];
	char firstName[250];
	char lastName[250];
	int accountNumber;

	printf("Bitte geben Sie Ihren Vornamen ein\n# ");
	scanf("%s", firstName);
	system("cls");

	printf("Bitte geben Sie Ihren Nachnamen ein\n# ");
	scanf("%s", lastName);
	system("cls");

	printf("Bitte geben Ihren Geburtsdatum in folgendem Format ein: DD.MM.YYYY z.B. 01.03.1972\n# ");

	scanf("%s", birthDate);
	//scanf("%s", newBankAccount->BirthDate);
	newBankAccount->BirthDate = _strdup(birthDate);
	newBankAccount->FirstName = _strdup(firstName);
	newBankAccount->LastName = _strdup(lastName);
	newBankAccount->AccountNumber = GetAccountNumber(&_BankAccountHead);
	newBankAccount->next = NULL;
	newBankAccount->index = current;
	system("cls");

	// Add To List
	PushAtTheEnd(&_BankAccountHead, &newBankAccount);

	// PrintList
	PrintList(&_BankAccountHead, current);

	// Save in List
	SaveListInFile(&_BankAccountHead);

	printf("Herzlichen Glückwunsch. Konto wurde erfolgreich eröffnet\n\n");
}

int OpenStartMenu()
{
	int choice = 0;
	char choiceAsChar[5];

	printf(GRN"\n\n\t\t\t Willkommen in Ihrer Bank-Verwaltung \n\n\n" RESET);
	while (1)
	{
		printf("\t 1.) Login\n");
		printf("\t 2.) New Account\n");


		printf("\t 5.) Remove Data\n");
		printf("\t 6.) Close Application\n");

		printf("\n\n\n\t Bitte waehlen Sie eine Option: ");

		gets(choiceAsChar);
		choice = atoi(choiceAsChar);

		system("cls");
		PrintList(&_BankAccountHead, -1);

		switch (choice)
		{
		case 1:
			//Login();
			break;
		case 2:
			CreateNewAccount();
			break;
		case 3:

			break;
		case 4:
			//see();
			break;
		case 5:
			RemoveAccount();
			break;
		case 6:
			CloseApp();
			return 1;
			break;
		case 7:
			AddDummyData();
		default:
			printf("\nBitte geben waehlen Sie eine Option zwischen 1 und 7\n\n");
			break;
		}
	}
}

void LoadBankAccounts()
{
	int bufferLength = 255;
	char* token2 = malloc(bufferLength * sizeof(char));
	char* buffer = malloc(bufferLength * sizeof(char));

	int i = 0;

	// Datei oeffnen
	accountFile = fopen("accounts.txt", "r");

	if (accountFile != NULL)
	{
		char* next_token1 = NULL;
		char* next_token2 = NULL;

		while (fgets(buffer, bufferLength, accountFile))
		{
			BankAccount* newBankAccount = CreateNode();
			i++;
			remove_spaces(buffer);									// Remove whitespace from buffer
			char* token1 = strtok_s(buffer, ";", &next_token1);		// Separation by ';'

			while (token1 != NULL) {

				char* _token2 = strtok_s(token1, ":", &next_token2);
				token2 = _strdup(_token2); // duplicate string

				// Key
				if (strcmp(token2, "Vorname") == 0)
				{
					_token2 = strtok_s(NULL, ":", &next_token2);
					token2 = _strdup(_token2); // duplicate value
					newBankAccount->FirstName = token2;
				}
				else if (strcmp(token2, "Nachname") == 0)
				{
					_token2 = strtok_s(NULL, ":", &next_token2);
					token2 = _strdup(_token2);// duplicate value
					newBankAccount->LastName = token2;
				}
				else if (strcmp(token2, "KontoNummer") == 0)
				{
					_token2 = strtok_s(NULL, ":", &next_token2);
					token2 = _strdup(_token2);// duplicate value
					newBankAccount->AccountNumber = atoi(token2);
				}
				else if (strcmp(token2, "Id") == 0)
				{
					_token2 = strtok_s(NULL, ":", &next_token2);
					token2 = _strdup(_token2);// duplicate value
					newBankAccount->index = atoi(token2);
				}

				token1 = strtok_s(NULL, ";", &next_token1);
			}

			PushAtTheEnd(&_BankAccountHead, &newBankAccount);
		}

		printf(GRN"\t\t Daten erfolgreich geladen!\n" RESET);
	}
	else
	{
		printf(RED"\t\t Datenbank Datei konnte nicht geöffnet werden\n" RESET);
	}

	if (accountFile != NULL)
	{
		fclose(accountFile);
	}

	free(buffer);
	free(token2);
	PrintList(&_BankAccountHead, -1);
}


void Initialize()
{
	LoadBankAccounts();
}

void freeArray(BankAccount** head)
{
	BankAccount* current = *head;
	BankAccount* temp = NULL;

	while (current != NULL)
	{
		temp = current->next;
		free(current);
		current = temp;
	}

	free(current);
	free(temp);
}

int main(int argc, char* argv[])
{
	_BankAccountHead = malloc(sizeof(BankAccount));
	_BankAccountHead->index = -1;

	if (argc > 0) {
		// lese arg 1 ein
	}

	if (argc > 1) {
		// lese arg 1 ein
	}

	Initialize();
	OpenStartMenu();

	freeArray(&_BankAccountHead);
	return 1;
}