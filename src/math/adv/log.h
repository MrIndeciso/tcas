#ifndef LOG_H
#define LOG_H

#include "expr_structs.h"

struct expr_tree_val* math_log10(struct expr_tree_val *op);

struct expr_tree_val* math_log2(struct expr_tree_val *op);

struct expr_tree_val* math_ln(struct expr_tree_val *op);

#endif
