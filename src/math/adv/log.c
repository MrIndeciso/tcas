#include "log.h"

#include <gmp.h>
#include <mpfr.h>
#include <stdio.h>
#include <stdlib.h>

#include "type_util.h"

struct expr_tree_val* math_log10(struct expr_tree_val *op) {
    struct expr_tree_val *val = malloc(sizeof(struct expr_tree_val));

    make_float(op);

    val->type = FLOAT;
    val->val = malloc(sizeof(union expr_tree_val_ref));

    mpfr_init(val->val->fp_val);

    mpfr_log10(val->val->fp_val, op->val->fp_val, MPFR_ROUNDING);

    return val;
}

struct expr_tree_val* math_log2(struct expr_tree_val *op) {
    struct expr_tree_val *val = malloc(sizeof(struct expr_tree_val));

    make_float(op);

    val->type = FLOAT;
    val->val = malloc(sizeof(union expr_tree_val_ref));

    mpfr_init(val->val->fp_val);

    mpfr_log2(val->val->fp_val, op->val->fp_val, MPFR_ROUNDING);

    return val;
}

struct expr_tree_val* math_ln(struct expr_tree_val *op) {
    struct expr_tree_val *val = malloc(sizeof(struct expr_tree_val));

    make_float(op);

    val->type = FLOAT;
    val->val = malloc(sizeof(union expr_tree_val_ref));

    mpfr_init(val->val->fp_val);

    mpfr_log2(val->val->fp_val, op->val->fp_val, MPFR_ROUNDING);

    return val;
}
