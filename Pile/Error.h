#ifndef ERROR_H
#define ERROR_H

#define INTERPRETER_TAG "INTERPRETER"
#define DEBUG_TAG "DEBUG"


#define HndlError(tag, errorMsg)\
	printf("[%s] %s	: Error on line %d : %s\n",tag, __FILE__, __LINE__, errorMsg);\
	getch();\
	exit(1);\

#endif