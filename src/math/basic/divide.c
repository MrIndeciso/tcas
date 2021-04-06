#include "divide.h"

#include <gmp.h>
#include <stdlib.h>

#include "mem_util.h"
#include "type_util.h"

struct expr_tree_val* math_divide(struct expr_tree_val *op1, struct expr_tree_val *op2) {
    enum VAL_TYPE types = op1->type | op2->type;

    struct expr_tree_val *val = malloc(sizeof(struct expr_tree_val));

    if ((types & FLOAT) == FLOAT) { //At least one of them is a float
        make_float(op1);
        make_float(op2);

        val->type = FLOAT;
        val->val = malloc(sizeof(union expr_tree_val_ref));

        mpfr_init(val->val->fp_val);
        mpfr_div(val->val->fp_val, op1->val->fp_val, op2->val->fp_val, MPFR_ROUNDING);
    } else if ((types & RATIONAL) == RATIONAL) { //At least one of them is a rational
        make_rational(op1);
        make_rational(op2);

        val->type = RATIONAL;
        val->val = malloc(sizeof(union expr_tree_val_ref));
        mpq_init(val->val->rational_val);
        mpq_div(val->val->rational_val, op1->val->rational_val, op2->val->rational_val);
    } else { //All ints
        val->type = RATIONAL;
        val->val = malloc(sizeof(union expr_tree_val_ref));
        mpq_init(val->val->rational_val);

        if (mpz_sgn(op2->val->int_val) == -1) {
            mpz_abs(op2->val->int_val, op2->val->int_val);
            mpz_neg(op1->val->int_val, op1->val->int_val);
        }

        mpz_set(mpq_numref(val->val->rational_val), op1->val->int_val);
        mpz_set(mpq_denref(val->val->rational_val), op2->val->int_val);
    }

    //free_tree_val(op1); Causes double-free down the line
    //free_tree_val(op2); Causes double-free down the line

    return val;
}
