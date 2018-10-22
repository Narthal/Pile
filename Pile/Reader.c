#include "Reader.h"

// vars
char * path;
FILE * fp;

char buff[MAX_TOKEN_LENGTH] = "";
int len = 0;

int readSuccess = 0;
int isString = 0;

const char whitespaces[] =
{
	WHITESPACE_SPACE,
	WHITESPACE_TAB,
	WHITESPACE_NEWLINE
};

const char delimiters[] =
{
	DELIMITER_COLON,			// 0
	DELIMITER_DOT,				// 1
	DELIMITER_COMMA,			// 2
	DELIMITER_CURLY_START,		// 3
	DELIMITER_CURLY_END,		// 4
	DELIMITER_BRACKET_START,	// 5
	DELIMITER_BRACKET_END,		// 6
	DELIMITER_SQUARE_START,		// 7
	DELIMITER_SQUARE_END,		// 8
	DELIMITER_EQUALS,			// 9
	DELIMITER_PLUS,				// 10
	DELIMITER_MINUS,			// 11
	DELIMITER_SEMICOLON,		// 12
	DELIMITER_STRING,			// 13
	DELIMITER_CHAR,				// 14
};

void OpenFile()
{
	// Open file
	fp = fopen(path, "r");
	if (fp == NULL)
	{
		HndlError(INTERPRETER_TAG, "OpenFile : couldn't open file");
	}

	return;
}

void CloseFile()
{
	fclose(fp);

	return;
}

void ReadNextToken()
{
	// reader dump
	char c;

	// flags
	int foundDelimiter = 0;
	int foundWhiteSpace = 0;
	int isFirstChar = 1;

	// clear buff
	for (int i = 0; i < len; i++)
	{
		buff[i] = '\0';
	}
	len = 0;

	while (foundDelimiter == 0)
	{
		// read char
		readSuccess = fscanf(fp, "%c", &c);
		// handle eof
		if (readSuccess == EOF)
		{
			return;
		}

		// check for delimiter
		for (int i = 0; i < DELIMITER_LENGTH; i++)
		{
			if (c == delimiters[i])
			{
				// handle delimiter flag
				foundDelimiter = 1;
				// handle string flags
				if (delimiters[i] == DELIMITER_STRING && isFirstChar == 1)
				{
					if (isString == 0)
					{
						isString = 1;
					}
					else
					{
						isString = 0;
					}
				}
			}
		}

		// if just delimiter token, store and return
		if (isFirstChar == 1 && foundDelimiter == 1)
		{
			buff[0] = c;
			len = 1;
			return;
		}

		// check for whitespace
		for (int i = 0; i < WHITESPACE_LENGTH; i++)
		{
			if (c == whitespaces[i])
			{
				foundWhiteSpace = 1;
			}
		}

		// write char to buff
		if (foundWhiteSpace == 0 && foundDelimiter == 0)
		{
			buff[len] = c;
			len++;
		}
		else
		{
			// if it is string write char to buff, even if whitespace
			if (foundWhiteSpace == 1 && isString == 1 && foundDelimiter == 0)
			{
				buff[len] = c;
				len++;
			}
		}




		// reset flags
		isFirstChar = 0;
		foundWhiteSpace = 0;
	}

	fseek(fp, ftell(fp) - 1, SEEK_SET);

	if (buff[0] == '\0')
	{
		ReadNextToken();
	}

	return;
}

void ReadFile(char * p)
{
	path = p;
	OpenFile();

	while (readSuccess != EOF)
	{
		ReadNextToken();
		if (readSuccess == 1) TranslateToken(buff, len);
	}

	CloseFile();
	return;
}