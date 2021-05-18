#ifndef GRUNTZ_TYPES_H
#define GRUNTZ_TYPES_H

#include "expr_structs.h"

struct gruntz_expr {
    int comparability_class;
    struct expr_tree_link *expr;
};

#endif
