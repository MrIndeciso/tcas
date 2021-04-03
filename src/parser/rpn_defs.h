#ifndef RPN_DEFS_H
#define RPN_DEFS_H

#include <string.h>

#include "../types/parser_enums.h"

int op_arg_count(enum OPERATOR_TYPE type) {
	switch(type) {
		case PLUS:
		case MINUS:
		case TIMES:
		case OBELUS:
		case POWER:
		case LOG:
			return 2;
			break;
		case default:
			return 1;
			break;
	}
}

enum OPERATOR_TYPE op_from_token(char *token) {
	if (strcmp(token, "+") == 0) {

	} else if (strcmp(token, "-") == 0) {

	} else if (strcmp(token, "*") == 0 ||
		   strcmp(token, "x") == 0) {

	} else if (strcmp(token, "/") == 0) {

	} else if (strcmp(token, "sqrt") == 0) {

	} else if (strcmp(token, "sin") == 0) {

	} else if (strcmp(token, "cos") == 0) {

	} else if (strcmp(token, "sin") == 0) {

	} else if (strcmp(token, "tan") == 0) {

	} else if (strcmp(token, "^") == 0 ||
		   strcmp(token, "**") == 0) {

	} else if (strcmp(token, "root") == 0) {

	} else if (strcmp(token, "log") == 0) {

	} else if (strcmp(token, "ln") == 0) {

	} else {

	}
}

#endif
