#include "Translator.h"

Token currentToken;
char * currentVal;
int currentValLen;

Context context = eNullContext;
Token tokenExpectation = eNullToken;



void TranslateToken(char * buff, int len)
{
	// Handle len error
	if (len < 1)
	{
		HndlError(INTERPRETER_TAG, "TranslateToken : length was less then 1");
	}

	// Handle single char input
	if (len == 1)
	{
		/*DELIMITER_COLON*/					if (buff[0] == delimiters[0]) currentToken = eColonToken;
		/*DELIMITER_DOT*/					else if (buff[0] == delimiters[1]) currentToken = eDotToken;
		/*DELIMITER_COMMA*/					else if (buff[0] == delimiters[2]) currentToken = eCommaToken;
		/*DELIMITER_CURLY_START*/			else if (buff[0] == delimiters[3]) currentToken = eCurlyStartToken;
		/*DELIMITER_CURLY_END*/				else if (buff[0] == delimiters[4]) currentToken = eCurlyEndToken;
		/*DELIMITER_BRACKET_START*/			else if (buff[0] == delimiters[5]) currentToken = eBracketStartToken;
		/*DELIMITER_BRACKET_END*/			else if (buff[0] == delimiters[6]) currentToken = eBracketEndToken;
		/*DELIMITER_SQUARE_START*/			else if (buff[0] == delimiters[7]) currentToken = eSquareStartToken;
		/*DELIMITER_SQUARE_END*/			else if (buff[0] == delimiters[8]) currentToken = eSquareEndToken;
		/*DELIMITER_EQUALS*/				else if (buff[0] == delimiters[9]) currentToken = eEqualsToken;
		/*DELIMITER_PLUS*/					else if (buff[0] == delimiters[10]) currentToken = ePlusToken;
		/*DELIMITER_MINUS*/					else if (buff[0] == delimiters[11]) currentToken = eMinusToken;
		/*DELIMITER_SEMICOLON*/				else if (buff[0] == delimiters[12]) currentToken = eSemicolonToken;
		/*STRING*/							else if (buff[0] == delimiters[13]) currentToken = eStringToken;
		/*CHAR*/							else if (buff[0] == delimiters[14]) currentToken = eCharToken;
		/*single digit int value*/			else if (isdigit(buff[0]) > 0) currentToken = eIntValueToken;
		/*Has to be new variable name*/		else currentToken = eUserDefinedVariableNameToken;
	}
	// Handle multi char input
	else
	{
		// check for numeric
		int isNumeric = 1;
		for (int i = 0; i < len; i++)
		{
			if (!(isdigit(buff[i]) > 0))
			{
				isNumeric = 0;
			};
		}

		/*String literal value*/			if (isString == 1) currentToken = eStringValueToken;
		/*Int literal value*/				else if (isNumeric == 1) currentToken = eIntValueToken;
		/*OBJ_THIS keyword*/				else if (strcmp(buff, OBJ_THIS) == 0) currentToken = eThisToken;
		/*VAR0_INT keyword*/				else if (strcmp(buff, VAR0_INT) == 0) currentToken = eIntToken;
		/*VA10_CHAR keyword*/				else if (strcmp(buff, VAR1_CHAR) == 0) currentToken = eCharToken;
		/*OBJTYPE0_OBJ keyword*/			else if (strcmp(buff, OBJTYPE0_OBJ) == 0) currentToken = eOBJToken;
		/*OBJTYPE1_INTERFACE keyword*/		else if (strcmp(buff, OBJTYPE1_INTERFACE) == 0) currentToken = eINTERFACEToken;
		/*FUNC0_WRITE keyword*/				else if (strcmp(buff, FUNC0_WRITE) == 0) currentToken = eWriteToken;
		/*COMP_OP_GET_COMP_W_NAME keyword*/	else if (strcmp(buff, COMP_OP_GET_COMP_W_NAME) == 0) currentToken = eGetComponentWithNameToken;
		/*COMP_OP_ADD_COMP keyword*/		else if (strcmp(buff, COMP_OP_ADD_COMP) == 0) currentToken = eAddComponentToken;
		/*Has to be new variable name*/		else currentToken = eUserDefinedVariableNameToken;
	}

	// set other token values
	currentVal = buff;
	currentValLen = len;

	return;
}
