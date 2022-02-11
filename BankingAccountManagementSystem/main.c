#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include "tools.h"

#define DEFAULT_KONTO_NUMMER 1337000

BankAccount BankAccounts[1024];

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

	return 1;
}

void CreateNewAccount(void)
{
	//BankAccounts* bankAccounts = malloc(sizeof(BankAccounts));

	//printf("Bitte geben Sie Ihren Vornamen ein");
	//scanf("%s", bankAccount->FirstName);
	//system("cls");

	//printf("Bitte geben Sie Ihren Nachnamen ein");
	//scanf("%s", bankAccount->LastName);
	//system("cls");

	//printf("Bitte geben Ihren Geburtsdatum in folgendem Format ein: DD.MM.YYYY z.B. 01.03.1972");
	//scanf("%s", bankAccount->BirthDate);
	//system("cls");


	//for (int i = 0; i < sizeof(_BankAccounts) / sizeof(_BankAccounts->array[0]); i++)
	//{

	//}

	// Kontonummer ermitteln
	// Get Latests KontoNummer von allen gefundenen Konten
	// Öffne Datei und liefere letzte Kontonummer --> Zähle 1 hoch und verwende diese als neue Konto Nummer

		// Datei oeffnen
	fStream = fopen("accounts.txt", "r");

	if (fStream == NULL) {
		// File konnte nicht geöffnet werden
	}
	else {
		// Save new Account to file

	}

	printf("Herzlichen Glückwunsch. Konto wurde erfolgreich eröffnet");
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
	char* buffer = malloc(sizeof(bufferLength + 1));
	int i = 0;
	// Datei oeffnen
	fStream = fopen("accounts.txt", "r");

	if (fStream != NULL)
	{
		char* next_token1 = NULL;
		char* next_token2 = NULL;
		while (fgets(buffer, bufferLength, fStream))
		{
			BankAccount bankAccount_ = BankAccounts[i++];
			BankAccount* bankAccount = &bankAccount_;
			//printf("%s", buffer);
			// Remove whitespace from buffer
			remove_spaces(buffer);
			//printf("%s", buffer);

			// Separation by ';'
			char* token1 = strtok_s(buffer, ";", &next_token1);
			char* token2 = malloc(bufferLength * (sizeof(char)));
			/* walk through other tokens */
			while (token1 != NULL) {
				//printf("%s\n", token1);

				token2 = strtok_s(token1, ":", &next_token2);

				// Key
				if (strcmp(token2, "Vorname") == 0)
				{
					token2 = strtok_s(NULL, ":", &next_token2);
					bankAccount->FirstName = token2;
				}
				else if (strcmp(token2, "Nachname") == 0)
				{
					token2 = strtok_s(NULL, ":", &next_token2);
					bankAccount->LastName = token2;
				}

				token1 = strtok_s(NULL, ";", &next_token1);

			}
			PushAtTheEnd(_BankAccountHead, bankAccount);
		}
		printf(GRN"\t\t Daten erfolgreich geladen!\n" RESET);
	}
	else
	{
		printf(RED"\t\t Datenbank Datei konnte nicht geöffnet werden\n" RESET);
	}

	PrintList(_BankAccountHead);
}


void Initialize()
{
	// Add DummyData 
	//AddDummyData();

	LoadBankAccounts();
}

int main(int argc, char* argv[])
{
	if (argc > 0) {
		// lese arg 1 ein
	}

	if (argc > 1) {
		// lese arg 1 ein
	}


	Initialize();

	OpenStartMenu();
}