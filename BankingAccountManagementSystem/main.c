#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include "tools.h"

BankAccount* BankAccounts;

BankAccount* _BankAccountHead = NULL;
BankAccount* _BankAccountTail = NULL;

// Dateizeiger erstellen
FILE* fStream;

void CloseApp(void)
{
	printf(GRN"\n\n\t\tVielen Dank für Ihren Besuch"RESET"\n\n");
	fflush(stdout);
	for (int i = 5; i != 0; i--)
	{
		printf(WHT"\r\t\tSie werden in     "MAG" %d"RESET"     Sekunden automatisch ausgeloggt.", i);
		fflush(stdout);
		Sleep(1000);
	}

	system("cls");

	free(_BankAccountHead);
	free(_BankAccountTail);
	free(BankAccounts);
	return 1;
}

int GetArrayLength(BankAccount* head)
{
	int counter = 0;
	if (head != NULL)
	{
		counter = 1;
		BankAccount* lastNode = ((BankAccount*)head);

		while (lastNode->next != NULL)
		{
			lastNode = lastNode->next;
			counter++;
		}
	}
	return counter;
}

int getAccountNumber(BankAccount* head)
{
	int accountNumber = 0;
	if (head != NULL)
	{
		BankAccount* lastNode = ((BankAccount*)head);

		while (lastNode->next != NULL)
		{
			lastNode = lastNode->next;
		}

		accountNumber = lastNode->AccountNumber;
	}
	return ++accountNumber;
}

void CreateNewAccount(void)
{
	int current = GetArrayLength(BankAccounts);
	BankAccount* newBankAccount = &BankAccounts[current++];
	_BankAccountHead = &BankAccounts[0];
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
	newBankAccount->AccountNumber = getAccountNumber(_BankAccountHead);
	newBankAccount->next = NULL;
	system("cls");

	// Add To List
	PushAtTheEnd(_BankAccountHead, newBankAccount);

	// PrintList
	PrintList(_BankAccountHead, 1);

	// Save in List
	SaveListInFile(_BankAccountHead);

	printf("Herzlichen Glückwunsch. Konto wurde erfolgreich eröffnet\n\n");
}

int OpenStartMenu()
{
	int choice;
	printf(GRN"\n\n\t\t\t Willkommen in Ihrer Bank-Verwaltung \n\n\n" RESET);
	while (1)
	{
		printf("\t 1.) Login\n");
		printf("\t 2.) New Account\n");
		printf("\t 3.) Close Application\n");

		printf("\n\n\n\t Bitte waehlen Sie eine Option: ");
		scanf_s("%d", &choice);

		system("cls");
		switch (choice)
		{
		case 1:
			//new_acc();
			break;
		case 2:
			CreateNewAccount();
			break;
		case 3:
			//transact();
			break;
		case 4:
			//see();
			break;
		case 5:
			//erase();
			break;
		case 6:
			//view_list();
			break;
		case 7:
			CloseApp();
			return 1;
		default:
			printf("Bitte geben waehlen Sie eine Option zwischen 1 und 7");
			break;
		}
	}
}

void LoadBankAccounts()
{
	int bufferLength = 255;
	char* token2 = malloc(bufferLength * sizeof(char));
	char* buffer = malloc(bufferLength + 1 * sizeof(char));

	int i = 0;
	// Datei oeffnen
	fStream = fopen("accounts.txt", "r");

	if (fStream != NULL)
	{
		char* next_token1 = NULL;
		char* next_token2 = NULL;

		while (fgets(buffer, bufferLength, fStream))
		{
			BankAccount * newBankAccount = &BankAccounts[i++];

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

				token1 = strtok_s(NULL, ";", &next_token1);
			}

			PushAtTheEnd(_BankAccountHead, newBankAccount);
		}
		printf(GRN"\t\t Daten erfolgreich geladen!\n" RESET);
	}
	else
	{
		printf(RED"\t\t Datenbank Datei konnte nicht geöffnet werden\n" RESET);
	}

	PrintList(_BankAccountHead, 0);
	_BankAccountHead = &BankAccounts[0];
	fclose(fStream);
	free(buffer);
	free(token2);
}


void Initialize()
{
	// Add DummyData 
	//AddDummyData();

	LoadBankAccounts();
}

int main(int argc, char* argv[])
{
	BankAccounts = malloc(1024 * sizeof(BankAccount));

	if (argc > 0) {
		// lese arg 1 ein
	}

	if (argc > 1) {
		// lese arg 1 ein
	}


	Initialize();

	OpenStartMenu();
}