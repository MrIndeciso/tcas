#include <gmp.h>
#include <stdlib.h>

#include "power.h"

#include "mem_util.h"
#include "type_util.h"

struct expr_tree_val* math_exp(struct expr_tree_val *op) {
    struct expr_tree_val *val = malloc(sizeof(struct expr_tree_val));

    make_float(op);
    val->type = FLOAT;

    val->val = malloc(sizeof(union expr_tree_val_ref));

    mpfr_init(val->val->fp_val);
    mpfr_exp(val->val->fp_val, op->val->fp_val, MPFR_ROUNDING);

    return val;
}
