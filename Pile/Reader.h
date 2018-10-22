// Guard
#ifndef READER_H
#define READER_H

// Includes
#include <stdio.h>
//#include <string.h>

#include "Translator.h"
#include "Error.h"

// Constants
#define MAX_TOKEN_LENGTH 100
#define MAX_CODE_LENGTH 100

#define TOKEN_SEPARATOR ' '

#define WHITESPACE_SPACE ' '
#define WHITESPACE_TAB '\t'
#define WHITESPACE_NEWLINE '\n'
#define WHITESPACE_LENGTH 3

#define DELIMITER_COLON ':'
#define DELIMITER_DOT '.'
#define DELIMITER_COMMA ','
#define DELIMITER_CURLY_START '{'
#define DELIMITER_CURLY_END '}'
#define DELIMITER_BRACKET_START '('
#define DELIMITER_BRACKET_END ')'
#define DELIMITER_SQUARE_START '['
#define DELIMITER_SQUARE_END ']'
#define DELIMITER_EQUALS '='
#define DELIMITER_PLUS '+'
#define DELIMITER_MINUS '-'
#define DELIMITER_SEMICOLON ';'
#define DELIMITER_STRING '\"'
#define DELIMITER_CHAR '\''
#define DELIMITER_LENGTH 15


// extern vars
extern const char delimiters[];
extern const char whitespaces[];
extern int isString;

// Functions
void ReadFile(char * p);

#endif