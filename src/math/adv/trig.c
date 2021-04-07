#include "trig.h"

#include <gmp.h>
#include <mpfr.h>
#include <stdio.h>
#include <stdlib.h>

#include "type_util.h"

inline static struct expr_tree_val* math_trig(int (*fun)(mpfr_t, mpfr_srcptr, mpfr_rnd_t), struct expr_tree_val *op);

struct expr_tree_val* math_sin(struct expr_tree_val *op) {
    return math_trig(&mpfr_sin, op);
}

struct expr_tree_val* math_cos(struct expr_tree_val *op) {
    return math_trig(&mpfr_cos, op);
}

struct expr_tree_val* math_tan(struct expr_tree_val *op) {
    return math_trig(&mpfr_tan, op);
}

struct expr_tree_val* math_arcsin(struct expr_tree_val *op) {
    return math_trig(&mpfr_asin, op);
}

struct expr_tree_val* math_arccos(struct expr_tree_val *op) {
    return math_trig(&mpfr_acos, op);
}

struct expr_tree_val* math_arctan(struct expr_tree_val *op) {
    return math_trig(&mpfr_atan, op);
}

inline static struct expr_tree_val* math_trig(int (*fun)(mpfr_t, mpfr_srcptr, mpfr_rnd_t), struct expr_tree_val *op) {
    struct expr_tree_val *val = malloc(sizeof(struct expr_tree_val));

    make_float(op);

    val->type = FLOAT;
    val->val = malloc(sizeof(union expr_tree_val_ref));

    mpfr_init(val->val->fp_val);

    fun(val->val->fp_val, op->val->fp_val, MPFR_ROUNDING);

    return val;
}

