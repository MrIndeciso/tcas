//
// Created by mrindeciso on 09/02/2022.
//
#include "factorial.h"

#include <stdlib.h>
#include <gmp.h>
#include <assert.h>
#include "expr_structs.h"

struct expr_tree_val *math_factorial(struct expr_tree_val *op)
{
    assert(op->type == INT);
    long int n = mpz_get_si(op->val->int_val);
    assert(n >= 0);

    struct expr_tree_val *val = malloc(sizeof(struct expr_tree_val));
    val->type = INT;
    val->val = malloc(sizeof(union expr_tree_val_ref));
    mpz_init(val->val->int_val);
    mpz_fac_ui(val->val->int_val, n);

    return val;
}
