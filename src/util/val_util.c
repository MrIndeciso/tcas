//
// Created by mrindeciso on 10/02/2022.
//

#include "val_util.h"

int is_node_zero(struct expr_tree_link *node)
{
    if (node->type != VALUE)
        return 0;

    if (node->ptr->val->type == INT
        && mpz_cmp_ui(node->ptr->val->val->int_val, 0) == 0)
        return 1;
    else if (node->ptr->val->type == RATIONAL
             && mpq_cmp_ui(node->ptr->val->val->rational_val, 0, 1) == 0)
        return 1;
    else if (node->ptr->val->type == FLOAT
             && mpfr_zero_p(node->ptr->val->val->fp_val))
        return 1;
    else
        return 0;
}

int is_node_one(struct expr_tree_link *node)
{
    if (node->type != VALUE)
        return 0;

    if (node->ptr->val->type == INT
        && mpz_cmp_ui(node->ptr->val->val->int_val, 1) == 0)
        return 1;
    else if (node->ptr->val->type == RATIONAL
             && mpq_cmp_ui(node->ptr->val->val->rational_val, 1, 1) == 0)
        return 1;
    else if (node->ptr->val->type == FLOAT
             && mpfr_cmp_ui(node->ptr->val->val->fp_val, 1) == 0)
        return 1;
    else
        return 0;
}