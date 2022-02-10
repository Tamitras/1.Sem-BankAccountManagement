#pragma once
void HoldTerminal();
void PrintDatum();
int IsNumber(char* string);
int SeparateThousands(char* text);

typedef enum {
	Deposit,
	Withdraw
}TransactionType;

typedef struct
{
	TransactionType type;
	char* DateTime;
	int Value;
}Transaction;

typedef struct
{
	char* FirstName;
	char* LastName;
	char* BirthDate;
	char* Adress;
	int AccountNumber;
	char* LastLogin;
	struct Transaction* Transaction;
	int Transactions;
	struct BankAccount* prev;
	struct BankAccount* next;
}BankAccount;

typedef struct {
	int* array;
	int used;
	int size;
} BankAccounts;

void freeArray(BankAccounts* a);

void initArray(BankAccounts* a, int initialSize);

void insertArray(BankAccounts* a, BankAccount * element);

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"