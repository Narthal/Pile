#include "Interpreter.h"

Context context = eNullContext;
Token tokenExpectation = eNullToken;

#pragma region CurentTokenHandlers

void HndlNullToken()
{
	HndlError(INTERPRETER_TAG, "HndlNullToken : Null token recieved");
}

#pragma region [multi char] tokens

void HndlThisToken()
{
	return;
}

void HndlUserDefinedVariableNameToken()
{
	return;
}

void HndlIntToken()
{
	return;
}

void HndlCharToken()
{
	return;
}

void HndlStringToken()
{
	return;
}

void HndlOBJToken()
{
	return;
}

void HndlINTERFACEToken()
{
	return;
}

#pragma endregion

#pragma region [multi char] ROOT interface tokens

void HndlStartToken()
{
	return;
}

void HndlEndToken()
{
	return;
}

#pragma endregion

#pragma region [multi char] function tokens

void HndlAddComponentToken()
{
	return;
}

void HndlGetComponentWithNameToken()
{
	return;
}

void HndlWriteToken()
{
	return;
}

#pragma endregion

#pragma region single char tokens

void HndlColonToken()
{
	return;
}

void HndlDotToken()
{
	return;
}

void HndlCommaToken()
{
	return;
}

void HndlCurlyStartToken()
{
	if (context == eNullContext)
	{

	}

	return;
}

void HndlCurlyEndToken()
{
	return;
}

void HndlBracketStartToken()
{
	return;
}

void HndlBracketEndToken()
{
	return;
}

void HndlSquareStartToken()
{
	return;
}

void HndlSquareEndToken()
{
	return;
}

void HndlEqualsToken()
{
	return;
}

void HndlPlusToken()
{
	return;
}

void HndlMinusToken()
{
	return;
}

void HndlSemicolonToken()
{
	return;
}

#pragma endregion

#pragma region value tokens

void HndlStringValueToken()
{
	return;
}

void HndlIntValueToken()
{
	return;
}

void HndlCharValueToken()
{
	return;
}

#pragma endregion


void HndlToken()
{
	switch (currentToken)
	{
		// error
	case eNullToken:						HndlNullToken();					break;

		// [multi char] tokens
	case eThisToken:						HndlThisToken();					break;
	case eUserDefinedVariableNameToken:		HndlUserDefinedVariableNameToken(); break;
	case eIntToken:							HndlIntToken();						break;
	case eCharToken:						HndlCharToken();					break;
	case eStringToken:						HndlStringToken();					break;
	case eOBJToken:							HndlOBJToken();						break;
	case eINTERFACEToken:					HndlINTERFACEToken();				break;

		// [multi char] ROOT interface tokens
	case eStartToken:						HndlStartToken();					break;
	case eEndToken:							HndlEndToken();						break;

		// [multi char] function tokens
	case eAddComponentToken:				HndlAddComponentToken();			break;
	case eGetComponentWithNameToken:		HndlGetComponentWithNameToken();	break;
	case eWriteToken:						HndlWriteToken();					break;

		// single char tokens
	case eColonToken:						HndlColonToken();					break;
	case eDotToken:							HndlDotToken();						break;
	case eCommaToken:						HndlCommaToken();					break;
	case eCurlyStartToken:					HndlCurlyStartToken();				break;
	case eCurlyEndToken:					HndlCurlyEndToken();				break;
	case eBracketStartToken:				HndlBracketStartToken();			break;
	case eBracketEndToken:					HndlBracketEndToken();				break;
	case eSquareStartToken:					HndlSquareStartToken();				break;
	case eSquareEndToken:					HndlSquareEndToken();				break;
	case eEqualsToken:						HndlEqualsToken();					break;
	case ePlusToken:						HndlPlusToken();					break;
	case eMinusToken:						HndlMinusToken();					break;
	case eSemicolonToken:					HndlSemicolonToken();				break;

		// value tokens
	case eStringValueToken:					HndlStringValueToken();				break;
	case eIntValueToken:					HndlIntValueToken();				break;
	case eCharValueToken:					HndlCharValueToken();				break;

		// error
	default:
		HndlError(INTERPRETER_TAG, "HndlToken : current token in switch statement was default");
		break;
	}
}

#pragma endregion