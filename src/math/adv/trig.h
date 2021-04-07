#ifndef TRIG_H
#define TRIG_H

#include "expr_structs.h"

struct expr_tree_val* math_sin(struct expr_tree_val *op);

struct expr_tree_val* math_cos(struct expr_tree_val *op);

struct expr_tree_val* math_tan(struct expr_tree_val *op);

struct expr_tree_val* math_arcsin(struct expr_tree_val *op);

struct expr_tree_val* math_arccos(struct expr_tree_val *op);

struct expr_tree_val* math_arctan(struct expr_tree_val *op);


#endif
