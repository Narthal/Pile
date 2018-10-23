// Guard
#ifndef TRANSLATOR_H
#define TRANSLATOR_H

// Includes
#include <string.h>
#include <ctype.h>

#include "Error.h"
#include "Common.h"
#include "Reader.h"

/// TokenStrings
// obj handle
#define OBJ_THIS "this"
// vars
// todo: should move to interpreter
#define COMPONENT_NAME_DESCRIPTOR "Descriptor"
#define COMPONENT_NAME_INTERFACE "Interface"
// user vars
#define VAR0_INT "int"
#define VAR1_CHAR "char"
// base functions
#define FUNC0_WRITE "Write"
// OBJTypes
#define OBJTYPE0_OBJ "OBJ"
#define OBJTYPE1_INTERFACE "INTERFACE"
// Component operations
#define COMP_OP_GET_COMP_W_NAME "GetComponentWithName"
#define COMP_OP_ADD_COMP "AddComponent"

// extern
extern enum Token currentToken;			// why the fuck is the type "Token" unrecogniseable ?! (quickfix : def enum, int is default in c standard)
extern char * currentVal;
extern int currentValLen;

// functions
void TranslateToken(char * buff, int len);

#endif