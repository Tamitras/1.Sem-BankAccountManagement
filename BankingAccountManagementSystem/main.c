#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

//printf("%sred\n", KRED);
//printf("%sgreen\n", KGRN);
//printf("%syellow\n", KYEL);
//printf("%sblue\n", KBLU);
//printf("%smagenta\n", KMAG);
//printf("%scyan\n", KCYN);
//printf("%swhite\n", KWHT);
//printf("%snormal\n", KNRM);


void CloseApp()
{
	printf(KNRM"\n\n\t\tVielen Dank für Ihren Besuch\n\n");
	fflush(stdout);
	for (int i = 5; i != 0; i--)
	{
		printf(KBLU"\r\t\tSie werden in     %d     Sekunden automatisch ausgeloggt.", i);
		fflush(stdout);
		Sleep(1000);
	}

	system("cls");
	printf(KNRM"");
	return 1;
}


int OpenStartMenu()
{
	int choice;
	printf(KGRN"\n\n\t\t\t Willkommen in Ihrer Bank-Verwaltung \n\n\n");
	while (1)
	{
		printf(KNRM"\t 1.) Login\n");
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
			//edit();
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




int main(int argc, char* argv[])
{
	if (argc > 0) {
		// lese arg 1 ein
	}

	if (argc > 1) {
		// lese arg 1 ein
	}

	OpenStartMenu();
}