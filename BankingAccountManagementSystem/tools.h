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

typedef enum {
	FirstName,
	LastName,
	AccountNumber,
	Id
}SortType;

typedef enum {
	Deposit,
	Withdraw
}TransactionType;

typedef struct
{
	TransactionType type;
	char* DateTime;
	int Value;
	struct Transaction* prev;
	struct Transaction* next;
} Transaction;

typedef struct node
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

#pragma once
void HoldTerminal();
void PrintDatum();
int IsNumber(char* string);
int SeparateThousands(char* text);
BankAccount* CreateNode();
int GetAccountNumber(BankAccount** head);
int GetArrayLength(BankAccount** head);
int GetNewId();
void AddDummyData();
void PushAtTheEnd(BankAccount** head, BankAccount** item);
void PrintList(BankAccount** head, int* toDelete, int arrayLen, int limit);
void remove_spaces(char* s);
void SaveListInFile(BankAccount** head);
void Sort(BankAccount** head, SortType type);

extern BankAccount* _BankAccountHead;
extern FILE* accountFile;
