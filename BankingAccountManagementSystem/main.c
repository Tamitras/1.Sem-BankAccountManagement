#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include "tools.h"

BankAccount* _BankAccountHead;			// Head of List

// FilePointer
FILE* accountFile;
//FILE* accountPasswordFile;			// not used
//FILE* accountTransactionFile;			// not used

void CloseApp(void)
{
	system("cls");
	printf(GRN"\n\n\t\tVielen Dank f%sr Ihren Besuch"RESET"\n\n", "\x81");
	fflush(stdout);

	for (int i = 5; i != 0; i--)
	{
		printf(WHT"\r\t\tSie werden in     "MAG" %d"RESET"     Sekunden automatisch ausgeloggt.", i);
		fflush(stdout);
		Sleep(1000);
	}

	return 1;
}

void DeleteBankAccount(BankAccount** head, int key)
{
	// Store head node
	BankAccount* temp = *head;
	BankAccount* prev = NULL;

	// If head node itself holds the key to be deleted
	if (temp != NULL && temp->Id == key) {
		*head = temp->next;		// Changed head
		(*head)->prev = NULL;	// Set heads prev to null pointer
		free(temp);				// free old head
		return;
	}

	// Search for the key to be deleted, keep track of the
	// previous node as we need to change 'prev->next'
	while (temp != NULL && temp->Id != key) {
		prev = temp;
		temp = temp->next;
	}

	// If key was not present in linked list
	if (temp == NULL)
		return;

	// Unlink the node from linked list
	prev->next = temp->next;
	if (((BankAccount*)temp->next) != NULL)
		((BankAccount*)temp->next)->prev = prev;

	free(temp); // Deallocate memory
}

void RemoveAccount()
{
	int validDecision = 1;
	int toDelete[10] = { -1,-1,-1,-1,-1,-1,-1,-1,-1,-1 };
	int decision = -1;
	int exitReading = 0;
	int marked[1] = { -1 };
	int tempDecision = 0;
	int retry = 0;

	PrintList(&_BankAccountHead, marked, 1, -1);

	if (GetArrayLength(&_BankAccountHead) > 0) // Daten zum Löschen vorhanden
	{
		for (int i = 0; !exitReading; i++)
		{
			if (validDecision == 1)
			{
				if (!retry || i == 0)
				{
					retry = 0;
					printf("\n\n\t\tW%shlen Sie einen Datensatz aus (ID) den sie L%sschen m%schten\n\t\t# ", "\x84", "\x94", "\x94");
					scanf("%d", &tempDecision);
				}
				else
				{
					retry = 0;
					i--;
				}
			}
			else
				validDecision = 1;

			if (tempDecision > 0 && containsInIntArray(toDelete, tempDecision, 10)) // still in list (to delete)
			{
				printf(YEL"\n\t\tDatensatz mit dem Index (%d) wurde bereits zur L%sschen Liste hinzugef%sgt:\n\n" RESET, tempDecision, "\x94", "\x81");
				i--;
				system("pause");
				system("cls");
				PrintList(&_BankAccountHead, toDelete, i + 1, -1);
			}
			else if (tempDecision > 0 && contains(tempDecision))
			{
				toDelete[i] = tempDecision;

				system("cls");
				PrintList(&_BankAccountHead, toDelete, i + 1, -1); // mark index

				printf("\n\n");
				printf("\t\t(%d) Abbruch    \n", 0);
				printf("\t\t(%d) Best\%stigen \n", 1, "\x84");
				printf("\t\t(%d) Wiederhole letzte Eingabe (%d)  \n ", 2, toDelete[i]);
				printf("\t\t(%d) N%schster Datensatz l%sschen  \n\t\t# ", 3, "\x84", "\x94");
				scanf("%d", &decision);

				if (decision != 3)
				{
					if (decision == 2)
					{
						retry = 1;							// mark as retry
						toDelete[i] = tempDecision = -1;	// remove last index
						i--;
						system("cls");
						PrintList(&_BankAccountHead, toDelete, i + 1, -1);
					}
					else if (decision == 1)
					{
						exitReading = 1;
					}
					else if (decision == 0)
					{
						exitReading = 1;
						for (int i = 0; i < 5; i++)
							toDelete[i] = -1;
					}
					else
					{
						// decision is not valid (> 3)
						validDecision = 0;
						i--;
					}
				}
				else
				{
					system("cls");
					PrintList(&_BankAccountHead, toDelete, i + 1, -1);
				}
			}
			else
			{
				system("cls");
				PrintList(&_BankAccountHead, marked, 1, -1);
				printf(YEL"Datensatz mit dem Index (%d) nicht gefunden:\n\n" RESET, toDelete[i]);
				system("pause");
			}
		}
	}
	else
	{
		printf(RED "\n\tEs sind noch keine Daten im Speicher vorhanden, bitte erstellen Sie oder Laden aus der Datei\n\n" RESET);
		system("pause");
	}


	// Multi-Deleting
	for (int i = 0; toDelete[i] >= 0; i++)
		DeleteBankAccount(&_BankAccountHead, toDelete[i]);		// delete all marked index

	system("cls");
}

void CreateNewAccount(void)
{
	int createNew = 1;

	while (createNew)
	{
		BankAccount* newBankAccount = CreateNode();
		char firstName[250], lastName[250];

		int id = GetNewId(&_BankAccountHead);
		int marked[1] = { id };
		int accountNumber;
		system("cls");

		printf("Bitte geben Sie Ihren Vornamen ein\n# ");
		scanf("%s", firstName);
		system("cls");

		printf("Bitte geben Sie Ihren Nachnamen ein\n# ");
		scanf("%s", lastName);
		system("cls");

		newBankAccount->FirstName = _strdup(firstName);
		newBankAccount->LastName = _strdup(lastName);
		newBankAccount->AccountNumber = GetAccountNumber(&_BankAccountHead);
		newBankAccount->next = NULL;
		newBankAccount->Id = id;
		system("cls");

		PushAtTheEnd(&_BankAccountHead, &newBankAccount);			// Add To List
		PrintList(&_BankAccountHead, marked, 1, 25);				// PrintList

		printf(GRN"\t\tAccount wurde erfolgreich erstellt"RESET"\n\n");
		system("pause");
		system("cls");

		printf("\t 1.) Weiteren Account anlegen\n");
		printf("\t 2.) Zur%sck zum Men%s\n", "\x81", "\x81");

		scanf("%d", &createNew);

		if (createNew == 2)
		{
			createNew = 0;
			system("cls");
		}
	}
}

void LoadBankAccounts()
{
	int bufferLength = 255;
	char* token2 = malloc(bufferLength * sizeof(char));
	char* _token2 = malloc(bufferLength * sizeof(char));
	char* buffer = malloc(bufferLength * sizeof(char));
	char* next_token1 = NULL;
	char* next_token2 = NULL;
	int success = 0;

	// Open File (read)
	accountFile = fopen("accounts.txt", "r");

	if (accountFile != NULL)
	{
		_BankAccountHead = NULL;
		while (fgets(buffer, bufferLength, accountFile))			// Read line by line
		{
			BankAccount* newBankAccount = CreateNode();				// Create new BankAccount
			remove_spaces(buffer);									// Remove whitespace from buffer
			char* token1 = strtok_s(buffer, ";", &next_token1);		// Separation by ';'

			while (token1 != NULL)
			{
				_token2 = strtok_s(token1, ":", &next_token2);
				token2 = _strdup(_token2);							// duplicate value (new ref)

				// Key
				if (strcmp(token2, "Vorname") == 0)
				{
					_token2 = strtok_s(NULL, ":", &next_token2);
					token2 = _strdup(_token2);						// duplicate value (new ref)
					newBankAccount->FirstName = token2;
				}
				else if (strcmp(token2, "Nachname") == 0)
				{
					_token2 = strtok_s(NULL, ":", &next_token2);
					token2 = _strdup(_token2);						// duplicate value (new ref)
					newBankAccount->LastName = token2;
				}
				else if (strcmp(token2, "KontoNummer") == 0)
				{
					_token2 = strtok_s(NULL, ":", &next_token2);
					token2 = _strdup(_token2);						// duplicate value (new ref)
					newBankAccount->AccountNumber = atoi(token2);
				}
				else if (strcmp(token2, "Id") == 0)
				{
					_token2 = strtok_s(NULL, ":", &next_token2);
					token2 = _strdup(_token2);						// duplicate value (new ref)
					newBankAccount->Id = atoi(token2);
				}

				token1 = strtok_s(NULL, ";", &next_token1);
			}
			PushAtTheEnd(&_BankAccountHead, &newBankAccount);
			success = 1;
		}
		if (success)
		{
			printf(GRN"\t Daten erfolgreich aus der Datei geladen\n" RESET);
			system("pause");
			system("cls");
		}
	}
	else
	{
		printf(RED"\t Datenbank Datei konnte nicht geöffnet werden\n" RESET);
		system("pause");
		system("cls");
	}

	if (accountFile != NULL)
		fclose(accountFile);

	free(buffer);
	free(token2);
}

int Menu()
{
	int choice = 0;
	int marked[1] = { -1 };

	while (1)
	{
		printf(YEL"\n\n\t ------------------------------- \n" RESET);
		printf(YEL"\t ------- Bank-Verwaltung ------- \n" RESET);
		printf(YEL"\t ------------------------------- \n\n" RESET);
		printf("\t 1.) Neue Accounts anlegen\n");
		printf("\t 2.) Ausgabe auf Terminal\n");
		printf("\t 3.) Daten l%sschen\n", "\x94");
		printf("\t 4.) Daten aus Datei laden\n");
		printf("\t 5.) Daten in Datei speichern\n");
		printf("\t 6.) Sortieren (Vorname)\n");
		printf("\t 7.) Sortieren (Nachname)\n");
		printf("\t 8.) Sortieren (Kontonummer)\n");
		printf("\t 9.) Sortieren (Id)\n");
		printf("\t 10.) Hinzuf%sgen von Testdaten\n", "\x81");
		printf("\t 11.) Bankverwaltung verlassen\n");
		printf("\n\n\t Auswahl treffen: ");

		scanf("%d", &choice);									// waiting for user input
		system("cls");											// clears console

		switch (choice)
		{
		case 1:
			CreateNewAccount();									// Creates a new account
			break;
		case 2:
			PrintList(&_BankAccountHead, marked, 1, 25);		// Print list on terminal
			break;
		case 3:
			RemoveAccount();									// Remove Accounts from heap and file
			break;
		case 4:
			LoadBankAccounts();
			break;
		case 5:
			SaveListInFile(&_BankAccountHead);					// Save in List
			break;
		case 6:
			Sort(&_BankAccountHead, FirstName);					// Sort by Firstname
			break;
		case 7:
			Sort(&_BankAccountHead, LastName);					// Sort by Lastname
			break;
		case 8:
			Sort(&_BankAccountHead, AccountNumber);				// Sort by Accountnumber
			break;
		case 9:
			Sort(&_BankAccountHead, Id);						// Sort by Id
			break;
		case 10:
			AddDummyData();										// Adding dummy data
			break;
		case 11:
			CloseApp();											// Close Application
			return 1;
		default:
			printf("\nBitte w%shlen Sie eine Option zwischen 1 und 10\n\n", "\x84");
			break;
		}
	}
}

int main(int argc, char* argv[])
{
	_BankAccountHead = NULL;

	if (argc > 0) { /*read arg1*/ }
	if (argc > 1) {	/*read arg2*/ }

	Menu();

	freeArray(&_BankAccountHead);
	return 1;
}