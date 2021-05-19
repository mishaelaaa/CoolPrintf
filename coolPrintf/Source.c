/*
* Name		:	Source.c
* Created	:	04 / 09 / 2021	12:22:22 AM
* Finished	:	05 / 17 / 2021	01:19:52 PM
* Author	:	MIHAELA PETKOVA
* Project	:	coolPrintf.sln
* Target	:	New realization of the function printf
*/

/*
	A `printf` format reference page (cheat sheet) :
	https://alvinalexander.com/programming/printf-format-cheat-sheet/
*/

#pragma region Libraries
/*@ brief include the libraries */
/*@ brief function, whitch allows functions to accept an indefinite number of arguments */
#include <stdarg.h>
/*@ brief Standard library functions for file inputand output */
#include <stdio.h>
/*@ brief Added library in which the individual functions are written */
#include "Func_header.h"
#pragma endregion 

int main() 
{
	int n = -10;
	char dPrints[8][20] = { "'%d'", "'%5d'", "'%-5d'", "'%05d'", "'%+5d'", "'%-+5d'", "'%i'", "'%u'" };

	for (int i = 0; i < 8; i++) 
	{
		coolPrintf(dPrints[i], n);
		printf(" <> ");
		printf(dPrints[i], n);
		printf("\n");
	}

	printf("\n");

	coolPrintf("%%");
	printf(" <> ");
	printf("%%");
	printf("\n");

	coolPrintf("'%o'", 9841);
	printf(" <> ");
	printf("'%o'", 9841);
	printf("\n");

	coolPrintf("'%x'", 666642);
	printf(" <> ");
	printf("'%x'", 666642);
	printf("\n");

	coolPrintf("'%c'", 'K');
	printf(" <> ");
	printf("'%c'", 'K');
	printf("\n");

	printf("\n");

	char str[] = "Hello";
	char sPrints[3][20] = { "'%s'", "'%10s'", "'%-10s'" };

	for (int i = 0; i < 3; i++) 
	{
		coolPrintf(sPrints[i], str);
		printf(" <> ");
		printf(sPrints[i], str);
		printf("\n");
	}

	printf("\n");

	double floatVal1 = 10.3456;
	double floatVal2 = 1234567.3456;
	char fPrints[8][20] = { "'%f'", "'%.1f'", "'%.2f'", "'%8.2f'", "'%8.4f'", "'%08.2f'", "'%-8.2f'", "'%-8.2f'" };

	for (int i = 0; i < 7; i++) 
	{
		coolPrintf(fPrints[i], floatVal1);
		printf(" <> ");
		printf(fPrints[i], floatVal1);
		printf("\n");
	}

	coolPrintf(fPrints[7], floatVal2);
	printf(" <> ");
	printf(fPrints[7], floatVal2);
	printf("\n");
	
	return 0;
}