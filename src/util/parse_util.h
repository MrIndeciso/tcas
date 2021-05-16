#ifndef PARSE_UTIL_H
#define PARSE_UTIL_H

#include "expr_structs.h"

struct expr_tree_link* parse_expr(char *expr, struct expr_tree_link *subst);

#endif
