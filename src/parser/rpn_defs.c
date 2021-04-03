#include <string.h>

#include "rpn_defs.h"

int op_arg_count(enum OPERATOR_TYPE type) {
	switch(type) {
		case PLUS:
		case MINUS:
		case TIMES:
		case DIVIDE:
		case POWER:
		case LOG:
			return 2;
			break;
		default:
			return 1;
			break;
	}
}

enum OPERATOR_TYPE op_from_token(char *token) {
	if (strcmp(token, "+") == 0) {
		return PLUS;
	} else if (strcmp(token, "-") == 0) {
		return MINUS;
	} else if (strcmp(token, "*") == 0 ||
		   strcmp(token, "x") == 0) {
		return TIMES;
	} else if (strcmp(token, "/") == 0) {
		return DIVIDE;
	} else if (strcmp(token, "sqrt") == 0) {
		return SQRT;
	} else if (strcmp(token, "sin") == 0) {
		return SIN;
	} else if (strcmp(token, "cos") == 0) {
		return COS;
	} else if (strcmp(token, "tan") == 0) {
		return TAN;
	} else if (strcmp(token, "^") == 0 ||
		   strcmp(token, "**") == 0) {
		return POWER;
	} else if (strcmp(token, "root") == 0) {
		return ROOT;
	} else if (strcmp(token, "log") == 0) {
		return LOG;
	} else if (strcmp(token, "ln") == 0) {
		return LN;
	} else {
		return UNKNOWN;
	}
}

char *op_value_from_type[] = {
	"+", "-", "*", "/", "sqrt", "sin", "cos", "tan", "^", "root", "log", "ln", "unknown"
};