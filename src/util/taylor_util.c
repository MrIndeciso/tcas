//
// Created by mrindeciso on 09/02/2022.
//
#include <stdlib.h>
#include <gmp.h>
#include <assert.h>

#include "taylor_util.h"

#include "mem_util.h"
#include "parse_util.h"

void free_taylor_expr(struct taylor_expr *expr)
{
    for (int i = 0; i < expr->count; i++)
        free_tree_link(expr->members[i]);

    // TODO decide if we should free 'orig'
    free_tree_link(expr->orig);
    free_tree_val(expr->center);

    free(expr);
}

struct expr_tree_link *taylor_factorial(int grade)
{
    struct expr_tree_link *res = malloc(sizeof(struct expr_tree_link));
    res->type = VALUE;
    res->ptr = malloc(sizeof(union expr_tree_ptr));
    res->ptr->val = malloc(sizeof (struct expr_tree_val));
    res->ptr->val->type = INT;
    res->ptr->val->val = malloc(sizeof (union expr_tree_val_ref));
    mpz_init(res->ptr->val->val->int_val);
    mpz_fac_ui(res->ptr->val->val->int_val, grade);
    return res;
}

int is_coeff_null(struct expr_tree_link *coeff)
{
    if (coeff->type == VALUE
        && coeff->ptr->val->type == INT
        && mpz_cmp_ui(coeff->ptr->val->val->int_val, 0) == 0)
        return 1;
    else
        return 0;
}

struct expr_tree_link *raise_to_power(struct expr_tree_link *arg, int power)
{
    // TODO fix this
    assert(power < 10);
    char input[] = "pow a b";
    input[4] = power + '0';
    return parse_expr(input, arg);
}