#include "Common.h"

#include <stdlib.h>

// Head obj node
OBJ * obj;

// handle spagetti function dependancy
void AddHardValueToVariableInObj(OBJ * targetObj, char * name, VarType varType, void* value);


#pragma region Creators

Variable * CreateVariable(VarType vt, void * value)
{
	Variable * var = malloc(sizeof(Variable));
	var->nextVar = malloc(sizeof(Variable*));
	var->nextVar = NULL;
	var->varType = vt;
	var->ptr = value;

	return var;
}

TokenNode * CreateTokenNode(char * val, Token token)
{
	TokenNode * tn = malloc(sizeof(TokenNode));
	tn->nextTokenNode = malloc(sizeof(TokenNode*));
	tn->nextTokenNode = NULL;
	tn->value = val;
	tn->token = token;

	return tn;
}

SyntaxNode * CreateSyntaxNode(char * val, Token token)
{
	SyntaxNode * sn = malloc(sizeof(SyntaxNode));
	sn->nextNodeA = malloc(sizeof(SyntaxNode*));
	sn->nextNodeA = NULL;
	sn->nextNodeB = malloc(sizeof(SyntaxNode*));
	sn->nextNodeB = NULL;
	sn->tn = CreateTokenNode(val, token);

	return sn;
}

FunctionNode * CreateFunction(char * val, Token token)
{
	FunctionNode * func = malloc(sizeof(FunctionNode));
	func->sn = CreateSyntaxNode(val, token);
	func->nextFunctionNode = malloc(sizeof(Variable*));
	func->nextFunctionNode = NULL;

	return func;
}

Component * CreateComponent(char * name, Variable * var, FunctionNode * func, ComponentFlags cf)
{
	Component * component = malloc(sizeof(Component));
	component->nextComp = malloc(sizeof(Component*));
	component->nextComp = NULL;
	component->var = var;
	component->func = func;
	component->name = name;
	component->cf = cf;

	return component;
}

OBJ * CreateOBJ(char * name, OBJType ot, int withInterface, char * interF)
{
	// Create obj
	OBJ * newObj = malloc(sizeof(OBJ));						// Main data region
	newObj->nextOBJ = malloc(sizeof(OBJ*));					// Alloc next obj data pointer
	newObj->nextOBJ = NULL;									// Set next obj pointer to null

	newObj->component = CreateComponent("Descriptor", CreateVariable(eCHARVarType, name), NULL, eProtectedComponentFlag);
	AddHardValueToVariableInObj(newObj, "Descriptor", eOBJTypeVarType, (void*)ot);
	Component * comp = newObj->component->nextComp;
	if (withInterface)
	{
		comp->nextComp = CreateComponent("Interface", CreateVariable(eINTERFACE, interF), NULL, eProtectedComponentFlag);
	}
	

	return newObj;
}

#pragma endregion

#pragma region ObjUtils

OBJ * GetLastOBJ()
{
	// traverse to last obj
	OBJ * tempOBJ = obj;
	while (tempOBJ->nextOBJ != NULL)
	{
		tempOBJ = tempOBJ->nextOBJ;
	}

	return tempOBJ;
}

OBJ * GetOBJAtIndex(int index)
{
	OBJ * tempOBJ = obj;
	for (int i = 0; i < index; i++)
	{
		tempOBJ = tempOBJ->nextOBJ;
	}

	return tempOBJ;
}

int GetNumOfAllOBJs()
{
	// traverse to last obj
	OBJ * tempOBJ = obj;
	int i = 0;
	if (tempOBJ == NULL)
	{
		return 0;
	}
	else
	{
		i++;
		while (tempOBJ->nextOBJ != NULL)
		{
			i++;
			tempOBJ = tempOBJ->nextOBJ;
		}
		return i;
	}
}

#pragma endregion

#pragma region ComponentUtils

Component * GetLastComponent(OBJ * targetObj)
{
	Component * com = targetObj->component;

	if (com == NULL)
	{
		return NULL;
	}
	else if (com->nextComp == NULL)
	{
		return com->nextComp;
	}
	else
	{
		while (com->nextComp != NULL)
		{
			com = com->nextComp;
		}
		return com;
	}
}

Component * GetComponentAtIndex(OBJ * targetObj, int index)
{
	Component * com = targetObj->component;

	if (com == NULL)
	{
		return NULL;
	}
	else if (com->nextComp == NULL)
	{
		return com->nextComp;
	}
	else
	{
		for (int i = 0; i < index; i++)
		{
			com = com->nextComp;
		}
		return com;
	}
}

Component * GetComponentWithName(OBJ * targetObj, char* name)
{
	Component * com = targetObj->component;

	if (com == NULL)
	{
		return NULL;
	}
	else
	{
		while (com->name != name)
		{
			com = com->nextComp;
			if (com == NULL) break;
		}
		return com;
	}
	return NULL;
}

int GetNumOfComponentsInObj(OBJ * targetObj)
{
	int i = 0;
	Component * comp = targetObj->component;
	while (comp != NULL)
	{
		i++;
		comp = comp->nextComp;
	}

	return i;
}

Variable * GetVariableFromComponent(Component * comp)
{
	if (comp->func != NULL && comp->var != NULL)
	{
		HndlError(INTERPRETER_TAG, "GetVariableFromComponent : incorrect component");
	}

	return comp->var;
}

Variable * GetVariableComponentWithNameFromObj(OBJ * targetObj, char * name)
{
	Component * comp = GetComponentWithName(targetObj, name);
	if (comp == NULL)
	{
		HndlError(INTERPRETER_TAG, "GetVariableComponentWithNameFromObj : component is empty");
	}
	Variable * var = GetVariableFromComponent(comp);
	if (var == NULL)
	{
		HndlError(INTERPRETER_TAG, "GetVariableComponentWithNameFromObj : variable is empty");
	}
	return var;
}

int GetComponentIndexInOBJ(OBJ * targetObj, char * name)
{
	int i = 0;

	Component * com = targetObj->component;

	if (com == NULL)
	{
		HndlError(INTERPRETER_TAG, "GetComponentIndexInOBJ : component is empty");
	}
	else
	{
		while (com->name != name)
		{
			i++;
			com = com->nextComp;
			if (com == NULL) break;
		}
		return i;
	}

	HndlError(INTERPRETER_TAG, "GetComponentIndexInOBJ : no component with such name");
	return -1;

}

#pragma endregion

#pragma region FREE

void FreeNULL(void** ptr)
{
	if (*ptr != NULL)
	{
		free(*ptr);
		*ptr = NULL;
	}

	return;
}

void FreeTokenNode(TokenNode * tn)
{
	if (tn->nextTokenNode != NULL) FreeTokenNode(&tn->nextTokenNode);
	FreeNULL(&tn);

	return;
}

void FreeSyntaxNode(SyntaxNode * sn)
{
	if (sn->nextNodeA != NULL) FreeSyntaxNode(&sn->nextNodeA);
	if (sn->nextNodeB != NULL) FreeSyntaxNode(&sn->nextNodeB);
	FreeTokenNode(&sn->tn);
	FreeNULL(&sn);

	return;
}

void FreeFunction(FunctionNode * func)
{
	FreeNULL(&func->nextFunctionNode);
	FreeSyntaxNode(&func->sn);
	FreeNULL(&func);

	return;
}

void FreeVariable(Variable * var)
{
	FreeNULL(&var->nextVar);
	//FreeNULL(&var->ptr);
	FreeNULL(&var);

	return;
}

void FreeComponent(Component * com)
{
	if (com->var != NULL) FreeVariable(com->var);
	if (com->func != NULL) FreeFunction(com->func);
	//FreeNULL(com->nextComp);
	//FreeNULL(&com);

	return;
}

void FreeOBJ(OBJ * tempObj)
{
	int compLen = GetNumOfComponentsInObj(tempObj);
	for (int i = compLen - 1; i >= 0; i--)
	{
		Component * com = GetComponentAtIndex(tempObj, i);
		FreeComponent(com);
	}
	//FreeNULL(tempObj->nextOBJ);
	FreeNULL(tempObj);

	return;
}

void FreeAllOBJs()
{
	int objLen = GetNumOfAllOBJs();
	for (int i = objLen - 1; i >= 0; i--)
	{
		OBJ * temp = GetOBJAtIndex(i);
		FreeOBJ(temp);
		FreeNULL(&temp);
	}

	obj = NULL;

	return;
}

#pragma endregion

#pragma region ComponentOperations

void AddVariableComponentToOBJ(OBJ * targetObj, char* name, VarType vt, void * value)
{
	Component * tempComp = GetLastComponent(targetObj);
	Variable * var = CreateVariable(vt, value);
	tempComp->nextComp = CreateComponent(name, var, NULL, eNullComponentFlag);

	return;
}

void RemoveComponentByIndexFromOBJ(OBJ * targetObj, int index)
{
	// try to remove something that doesnt exist, ehh..?
	int numOfCompsInObj = GetNumOfComponentsInObj(targetObj);
	if (index >= numOfCompsInObj)
	{
		HndlError(INTERPRETER_TAG, "RemoveComponentByIndexFromOBJ : index out of bounds");
	}

	// component before removal
	Component * comp = GetComponentAtIndex(targetObj, index - 1);

	// get component at removal index
	Component * removalComp = comp->nextComp;

	// if not last component, chain through the hole
	if (index < numOfCompsInObj - 1)
	{
		comp->nextComp = removalComp->nextComp;
	}

	// free that component!
	FreeComponent(removalComp);

	return;
}

void RemoveComponentWithNameFromOBJ(OBJ * targetObj, char* name)
{
	Component * comp = GetComponentWithName(targetObj, name);
	RemoveComponentByIndexFromOBJ(targetObj, GetComponentIndexInOBJ(targetObj, name));

	return;
}

#pragma endregion

#pragma region VariableUtils

Variable * GetLastVariable(Variable * var)
{
	Variable * tempVar = var;
	while (tempVar->nextVar != NULL)
	{
		tempVar = tempVar->nextVar;
	}

	return tempVar;
}

Variable * GetVariableAtIndex(Variable * var, int index)
{
	Variable * tempVar = var;

	for (int i = 0; i < index; i++)
	{
		tempVar = tempVar->nextVar;
	}
	return tempVar;
}

int GetNumOfVariables(Variable * var)
{
	Variable * tempVar = var;
	int i = 0;

	while (tempVar != NULL)
	{
		tempVar = tempVar->nextVar;
		i++;
	}
	return i;
}

#pragma endregion

#pragma region Variables

void SetVariableHardValue(Variable * var, VarType vt, void* value)
{
	var->varType = vt;
	var->ptr = value;

	return;
}

void SetVariableValue(Variable * var, void* value)
{
	var->ptr = value;

	return;
}

void SetVariableValueWithNameInObj(OBJ * targetObj, char * name, void* value)
{
	Variable * var = GetVariableComponentWithNameFromObj(targetObj, name);
	SetVariableValue(var, value);

	return;
}

void AddValueToVariableInObj(OBJ * targetObj, char * name, void* value)
{
	Variable * var = GetVariableComponentWithNameFromObj(targetObj, name);
	var = GetLastVariable(var);
	var->nextVar = CreateVariable(var->varType, value);
	
	return;
}

void AddHardValueToVariableInObj(OBJ * targetObj, char * name, VarType varType, void* value)
{
	Variable * var = GetVariableComponentWithNameFromObj(targetObj, name);
	var = GetLastVariable(var);
	var->nextVar = CreateVariable(varType, value);

	return;
}

void SetValueInVarAtIndexInObj(OBJ * targetObj, char * name, int index, void* value)
{
	Variable * var = GetVariableComponentWithNameFromObj(targetObj, name);
	var = GetVariableAtIndex(var, index);

	SetVariableValue(var, value);

	return;
}

void RemoveLastVariable(OBJ * targetObj, char * name)
{
	Variable * var = GetVariableComponentWithNameFromObj(targetObj, name);
	int len = GetNumOfVariables(var);

	// Handle null variable
	if (var == NULL)
	{
		return;
	}

	// handle sigle variable
	if (var->nextVar == NULL)
	{
		RemoveComponentWithNameFromOBJ(targetObj, name);
		return;
	}

	// remove last
	var = GetVariableAtIndex(var, len - 2);
	FreeVariable(var->nextVar);
	var->nextVar = NULL;



	return;
}

#pragma endregion

#pragma region Global

void CreateRootOBJ()
{
	obj = CreateOBJ("ROOT", eINTERFACE, 0, "");
	obj->component->nextComp = CreateComponent("Events", CreateVariable(eEventVarType, "Start"), NULL, eProtectedComponentFlag);
	AddValueToVariableInObj(obj, "Events", "End");

	return;
}

#pragma endregion
