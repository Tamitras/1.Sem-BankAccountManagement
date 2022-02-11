#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "tools.h"


#define DEFAULT_KONTO_NUMMER 1337000

// Dateizeiger erstellen
FILE* fileStream;

BankAccount* BankAccountHead = NULL;

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
	fileStream = fopen("accounts.txt", "r");

	if (fileStream == NULL) {
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
	int c;
	// Datei oeffnen
	fileStream = fopen("accounts.txt", "r");

	char* buffer = calloc(1024, sizeof(char));

	while (fscanf(fileStream, "%s", buffer) == 1) // expect 1 successful conversion
	{
		// process buffer
	}
	if (feof(fileStream))
	{
		// hit end of file
	}
	else
	{
		// some other error interrupted the read
	}
}

void AddToList(BankAccount* head, BankAccount* newAccount)
{
	if (head == NULL)
	{
		head = newAccount;
		head->prev = NULL;
		head->next = NULL;
	}
	else
	{
		BankAccount* current = head;
		while (1) {
			if (current->next == NULL)
			{
				current->next = newAccount;
				newAccount->prev = current;
				break; 
			}
			current = current->next;
		};
	}
}

void AddDummyData()
{
	BankAccountHead = NULL;

	BankAccount * acc1 = malloc(sizeof(BankAccount));
	acc1->FirstName = "Erik";
	acc1->LastName = "Kaufmann";
	acc1->AccountNumber = "123456";
	acc1->BirthDate = "06.07.1991";
	acc1->Adress = "Testwohnort";
	acc1->LastLogin = "11.02.2022";
	AddToList(BankAccountHead, acc1);

	BankAccount * acc2 = malloc(sizeof(BankAccount));
	acc2->FirstName = "Pascal";
	acc2->LastName = "Lorenz";
	acc2->AccountNumber = "99999";
	acc2->BirthDate = "01.01.2001";
	acc2->Adress = "Testwohnort";
	acc2->LastLogin = "11.02.2022";


	AddToList(BankAccountHead, acc2);

	for (BankAccount *current = BankAccountHead; current->next == NULL;)
	{
		printf("------------------------------------");
		printf("Nachname:%s Vorname:%s \n\n", current->FirstName, current->LastName);
	}
}

void Initialize()
{
	AddDummyData();

	// Datei oeffnen
	fileStream = fopen("accounts.txt", "r");

	if (fileStream == NULL) {
		// Create new file if not exist
		fileStream = fopen("accounts.txt", "a");
		printf("Neue Datei wurde angelegt\n");
	}

	// Load all BankAccounts from File

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