#ifndef GRUNTZ_TYPES_H
#define GRUNTZ_TYPES_H

#include "expr_structs.h"

struct gruntz_mrv {
    size_t count;
    struct gruntz_expr **expr;
};

struct gruntz_expr {
    struct expr_tree_link *expr;
};

#endif
