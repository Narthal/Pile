#include <stdio.h>

#include "Pile.h"

int main(int argc, char *argv[])
{
	// File read
	puts("[DEBUG] : Starting file read...");
	ReadFile(argv[1]);
	puts("[DEBUG] : Done reading file");

	puts("-----------------------------");

	// Data translation
	puts("[DEBUG] : Starting translation...");
	//Translate();
	puts("[DEBUG] : Done translating");

	puts("-----------------------------");

	CreateRootOBJ();

	//obj = CreateOBJ("mainOBJ", eOBJ, "ROOT");
	//OBJ * iROOT = CreateOBJ("otherOBJ", eINTERFACE, "asdf");
	//obj->nextOBJ = iROOT;



	/*AddVariableComponentToOBJ(obj, "newVar", eINT, 69);
	RemoveComponentByIndexFromOBJ(obj, 1);


	SetVariableValueWithNameInObj(obj, "Name", "hello");

	AddValueToVariableInObj(obj, "Interface", "ROOT");
	SetValueInVarAtIndexInObj(obj, "Interface", 1, "newInterface");

	RemoveLastVariable(obj, "Interface");
	RemoveLastVariable(obj, "Interface");*/

	FreeAllOBJs();

	//getch();

	return 0;
}