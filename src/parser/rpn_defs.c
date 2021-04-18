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
    case LIM:
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
    } else if (strcmp(token, "*") == 0) {
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
    } else if (strcmp(token, "arcsin") == 0) {
        return ARCSIN;
    } else if (strcmp(token, "arccos") == 0) {
        return ARCCOS;
    } else if (strcmp(token, "arctan") == 0) {
        return ARCTAN;
    } else if (strcmp(token, "^") == 0 ||
               strcmp(token, "**") == 0) {
        return POWER;
    } else if (strcmp(token, "root") == 0) {
        return ROOT;
    } else if (strcmp(token, "log") == 0) {
        return LOG;
    } else if (strcmp(token, "log10") == 0) {
        return LOG10;
    } else if (strcmp(token, "log2") == 0) {
        return LOG2;
    } else if (strcmp(token, "ln") == 0) {
        return LN;
    } else if (strcmp(token, "lim") == 0) {
        return LIM;
    } else if (strcmp(token, "exp") == 0) {
        return EXP;
    } else {
        return UNKNOWN;
    }
}

char *op_value_from_type[] = {
    "+", "-", "*", "/", "sqrt", "sin", "cos", "tan", "arcsin", "arccos", "arctan", "^", "root", "log10", "log2", "log", "ln", "lim", "exp", "unknown"
};
