#pragma once

// Terminal adjustments
#define BLK			"\x1B[30m"
#define RED_BACK    "\x1B[33;41m"
#define RED			"\x1B[31m"
#define GRN			"\x1B[32m"
#define YEL			"\x1B[33m"
#define BLU			"\x1B[34m"
#define MAG			"\x1B[35m"
#define CYN			"\x1B[36m"
#define WHT			"\x1B[37m"
#define RESET		"\x1B[0m"

// Sorting type
typedef enum {
	FirstName,
	LastName,
	AccountNumber,
	Id
}SortType;

// TransactionType
typedef enum {
	Deposit,
	Withdraw
}TransactionType;

// Transaction model
typedef struct
{
	TransactionType type;
	char* DateTime;
	int Value;
	struct Transaction* prev;
	struct Transaction* next;
} Transaction;

// Bankaccount model
typedef struct
{
	char* FirstName;
	char* LastName;
	char* Adress;
	char* LastLogin;
	int AccountNumber;
	struct Transaction* Transaction;
	struct BankAccount* prev;
	struct BankAccount* next;
	int Id;
}BankAccount;

// external variables
extern BankAccount* _BankAccountHead;
extern FILE* accountFile;

// Global Prototypes
BankAccount* CreateNode();

int IsNumber(char* string);
int SeparateThousands(char* text);
int GetAccountNumber(BankAccount** head);
int GetArrayLength(BankAccount** head);
int GetNewId();

// Check if int array contains a key
int containsInIntArray(int* array, int key, int len);

// Check if ListOf BankAccounts contains key
int contains(int key);

void HoldTerminal();
void PrintDatum();
void freeArray(BankAccount** head);
void AddDummyData();
void PushAtTheEnd(BankAccount** head, BankAccount** item);
void PrintList(BankAccount** head, int* toDelete, int arrayLen, int limit);
void remove_spaces(char* s);
void SaveListInFile(BankAccount** head);
void Sort(BankAccount** head, SortType type);


