#ifndef RPN_DEFS_H
#define RPN_DEFS_H

#include <string.h>

#include "../types/parser_enums.h"

int op_arg_count(enum OPERATOR_TYPE type);

enum OPERATOR_TYPE op_from_token(char *token);

extern char *op_value_from_type[];

#endif
