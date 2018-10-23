#include <stdio.h>

#include "Pile.h"

// Reader -> Translator [+ common] -> Interpreter [+ common]

int main(int argc, char *argv[])
{
	// File read
	puts("[DEBUG] : Starting file read...");
	ReadFile(argv[1]);
	puts("[DEBUG] : Done reading file");

	puts("-----------------------------");



	FreeAllOBJs();

	//getch();

	return 0;
}