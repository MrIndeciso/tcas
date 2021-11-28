#ifndef PARSE_UTIL_H
#define PARSE_UTIL_H

#include "expr_structs.h"

struct expr_tree_link* parse_expr(char *expr, struct expr_tree_link *subst);

struct expr_tree_link* parse_double_expr(char *expr, struct expr_tree_link *subst1, struct expr_tree_link *subst2);

struct expr_tree_link* parse_varargs(char *expr, int attribute_count, ...);

#endif
