#ifndef TYPE_UTIL_H
#define TYPE_UTIL_H

#include "expr_structs.h"

void make_rational(struct expr_tree_val *val);

void make_float(struct expr_tree_val *val);

void optimize_val(struct expr_tree_val *val);

#endif
