#include <gmp.h>
#include <stdlib.h>

#include "plus.h"
#include "mem_util.h"
#include "type_util.h"

struct expr_tree_val* math_plus(struct expr_tree_val *op1, struct expr_tree_val *op2) {
    enum VAL_TYPE types = op1->type | op2->type;

    struct expr_tree_val *val = malloc(sizeof(struct expr_tree_val));

    if ((types & FLOAT) == FLOAT) { //At least one of them is a float

    } else if ((types & RATIONAL) == RATIONAL) { //At least one of them is a rational
        make_rational(op1);
        make_rational(op2);

        val->type = RATIONAL;
        val->val = malloc(sizeof(union expr_tree_val_ref));
        mpq_init(val->val->rational_val);
        mpq_add(val->val->rational_val, op1->val->rational_val, op2->val->rational_val);
    } else { //All ints
        val->type = INT;
        val->val = malloc(sizeof(union expr_tree_val_ref));
        mpz_init(val->val->int_val);
        mpz_add(val->val->int_val, op1->val->int_val, op2->val->int_val);
    }

    //free_tree_val(op1); Causes double-free down the line
    //free_tree_val(op2); Causes double-free down the line

    return val;
}
