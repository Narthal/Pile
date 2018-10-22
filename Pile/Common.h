// Guard
#ifndef COMMON_H
#define COMMON_H

// Includes
#include <stdlib.h>
#include<stdio.h>

#include "Reader.h"
#include "Error.h"

#pragma region PrimitiveDataStructures

typedef enum
{
	eNullContext,
	eOBJContext,
	eFunctionsContext
} Context;

typedef enum
{
	eNullVarType,
	eINTVarType,
	eCHARVarType,
	eOBJTypeVarType,
	eEventVarType,
	eSTRINGVarType,
	eBOOLVarType			//TODO: implement vartipes
} VarType;

#pragma endregion

#pragma region OBJDefinisions

typedef struct
{
	VarType varType;
	void * ptr;
	struct Variable * nextVar;
} Variable;

typedef enum
{
	// error
	eNullToken,

	// [multi char] tokens
	eThisToken,
	eUserDefinedVariableNameToken,
	eIntToken,
	eCharToken,
	eStringToken,
	eOBJToken,
	eINTERFACEToken,

	// [multi char] ROOT interface tokens
	eStartToken,
	eEndToken,

	// [multi char] function tokens
	eAddComponentToken,
	eGetComponentWithNameToken,
	eWriteToken,


	// single char tokens
	eColonToken,
	eDotToken,
	eCommaToken,
	eCurlyStartToken,
	eCurlyEndToken,
	eBracketStartToken,
	eBracketEndToken,
	eSquareStartToken,
	eSquareEndToken,
	eEqualsToken,
	ePlusToken,
	eMinusToken,
	eSemicolonToken,

	// value tokens
	eStringValueToken,		//[multi char]
	eIntValueToken,			//[multi char]
	eCharValueToken,
} Token;

typedef enum
{
	eNullComponentFlag,
	eProtectedComponentFlag,
} ComponentFlags;

typedef struct
{
	Token token;
	char * value;
	struct TokenNode * nextTokenNode;
} TokenNode;

typedef struct
{
	TokenNode * tn;
	struct SyntaxNode * nextNodeA;
	struct SyntaxNode * nextNodeB;
} SyntaxNode;

typedef struct
{
	SyntaxNode * sn;
	struct FunctionNode * nextFunctionNode;
} FunctionNode;

typedef struct
{
	ComponentFlags cf;
	Variable * var;
	FunctionNode * func;
	char* name;
	struct Component * nextComp;
} Component;

typedef enum
{
	eNullOBJType,
	eOBJ,
	eINTERFACE
} OBJType;

typedef struct
{
	Component * component;
	struct OBJ * nextOBJ;
} OBJ;

#pragma endregion

// public stuff
extern OBJ * obj;

// Functions
OBJ * CreateOBJ(char * name, OBJType ot, int withInterface, char * interF);
int GetNumOfComponentsInObj(OBJ * targetObj);
OBJ * GetLastOBJ();
TokenNode * CreateTokenNode(char * val, Token token);
void AddVariableComponentToOBJ(OBJ * targetObj, char * name, VarType vt, void * value);
void RemoveComponentByIndexFromOBJ(OBJ * targetObj, int index);
void SetVariableValueWithNameInObj(OBJ * targetObj, char * name, void* value);
void AddValueToVariableInObj(OBJ * targetObj, char * name, void* value);
void SetValueInVarAtIndexInObj(OBJ * targetObj, char * name, int index, void* value);
void RemoveLastVariable(OBJ * targetObj, char * name);
Component * GetComponentWithName(OBJ * targetObj, char* name);
Component * GetLastComponent(OBJ * targetObj);
int GetNumOfAllOBJs();
void FreeAllOBJs();



void CreateRootOBJ();

#endif