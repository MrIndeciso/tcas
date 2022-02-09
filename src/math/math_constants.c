#include <stdlib.h>
#include "expr_structs.h"
#include "mem_util.h"

#include "math_constants.h"
#include "parse_util.h"

struct expr_tree_val *zero;
struct expr_tree_val *one;
struct expr_tree_val *neg_one;
struct expr_tree_link *sym_x;

void init_constants()
{
    zero = malloc(sizeof(struct expr_tree_val));
    one = malloc(sizeof(struct expr_tree_val));
    neg_one = malloc(sizeof(struct expr_tree_val));

    zero->type = INT;
    one->type = INT;
    neg_one->type = INT;

    zero->val = malloc(sizeof(union expr_tree_val_ref));
    one->val = malloc(sizeof(union expr_tree_val_ref));
    neg_one->val = malloc(sizeof(union expr_tree_val_ref));

    mpz_init_set_si(zero->val->int_val, 0);
    mpz_init_set_si(one->val->int_val, 1);
    mpz_init_set_si(neg_one->val->int_val, -1);

    sym_x = parse_expr("x", NULL);
}

void free_constants()
{
    free_tree_val(zero);
    free_tree_val(one);
    free_tree_val(neg_one);
    free_tree_link(sym_x);
}