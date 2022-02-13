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
	int bankAccountLength = GetArrayLength(&_BankAccountHead);

	int toDelete[5] = {-1,-1,-1,-1,-1};
	int decision = -1;
	int exitReading = 0;

	printf("\n\n\t\tWählen Sie einen Index den sie Löschen möchten\n\t\t# ");
	for (int i = 0; !exitReading; i++)
	{
		scanf("%d", &toDelete[i]);

		if (toDelete[i] < bankAccountLength)
		{
			system("cls");
			PrintList(&_BankAccountHead, toDelete, i + 1); // Index wird markiert

			printf("\n\n");
			printf("\t\t(%d) Abbruch    \n", 0);
			printf("\t\t(%d) Bestätigen \n", 1);
			printf("\t\t(%d) Wiederhole letzte Eingabe(%d)  \n\ ", 2, toDelete[i]);
			printf("\t\t(%d) Nächster Datensatz löschen  \n\t\t# ", 3);
			scanf("%d", &decision);

			if (decision != 3)
			{
				if (decision == 2)
				{
					i--;
				}
				else if (decision == 1)
				{
					exitReading = 1;
				}
				else
				{
					exitReading = 1;
					for (int i = 0; i < 20; i++)
					{
						toDelete[i] = -1;
					}
				}
			}
			else
			{
				printf("\n\n\t\tWählen Sie einen weiteren Index den sie Löschen möchten\n\t\t# ");
			}
		}
		else
		{
			system("cls");
			printf(YEL"Datensatz mit dem Index (%d) nicht gefunden:\n\n" RESET, toDelete[i]);

			int marked[1] = {-1};
			PrintList(&_BankAccountHead, marked, 1);
		}
	}

	for (int i = 0; toDelete[i] >= 0; i++)
	{
		// delete all marked index
		deleteBankAccount(&_BankAccountHead, toDelete[i]);

		int current = toDelete[i];
		// decrease index by 1 when account has been deleted
		for (int k = 0; toDelete[i + k + 1] >= 0; k++)
		{
			// beginned mit dem index nach dem gelöschen
			int next = toDelete[i + k + 1];

			if (current < next)
			{
				// verringere den index des nachfolgers
				toDelete[i + k + 1] = toDelete[i + k + 1]--;
			}
		}
	}

	if (toDelete[0] >= 0)
	{
		// only when index exist, save to file
		SaveListInFile(&_BankAccountHead);
	}

	system("cls");
	int marked[1] = { -1 };
	PrintList(&_BankAccountHead, marked, 1);
}

void CreateNewAccount(void)
{
	BankAccount* newBankAccount = CreateNode();
	char birthDate[250];
	char firstName[250];
	char lastName[250];
	int current = GetArrayLength(&_BankAccountHead);
	int accountNumber;
	system("cls");

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

	int marked[1] = {current};
	PrintList(&_BankAccountHead, marked, 1);

	// Save in List
	SaveListInFile(&_BankAccountHead);

	printf("Herzlichen Glückwunsch. Konto wurde erfolgreich eröffnet\n\n");
}

int OpenStartMenu()
{
	int choice = 0;
	int marked[1] = { -1 };

	printf(GRN"\n\n\t\t\t Willkommen in Ihrer Bank-Verwaltung \n\n\n" RESET);
	while (1)
	{
		printf("\t 1.) New Account\n");
		printf("\t 2.) Print List\n");
		printf("\t 3.) Remove Data\n");
		printf("\t 4.) Add Dummy Data\n");
		printf("\t 5.) Close Application\n");

		printf("\n\n\n\t Bitte waehlen Sie eine Option: ");

		scanf("%d", &choice);
		system("cls");

		switch (choice)
		{
		case 1:
			CreateNewAccount();
			break;
		case 2:
			PrintList(&_BankAccountHead, marked, 1);
			break;
		case 3:
			PrintList(&_BankAccountHead, marked, 1);
			RemoveAccount();
			break;
		case 4:
			AddDummyData();
			break;
		case 5:
			CloseApp();
			return 1;
			break;
		case 6:

			break;
		case 7:
			
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

		//printf(GRN"\t\t Daten erfolgreich geladen!\n" RESET);
	}
	else
	{
		printf(RED"\t\t Datenbank Datei konnte nicht geöffnet werden\n" RESET);
	}

	if (accountFile != NULL)
	{
		fclose(accountFile);
	}

	//int marked[1] = { -1 };
	//PrintList(&_BankAccountHead, marked, 1);

	//free(marked);
	free(buffer);
	free(token2);
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