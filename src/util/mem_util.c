#include <assert.h>
#include <gmp.h>
#include <stdlib.h>

#include "mem_util.h"

void recursive_graph_free(struct graph_node *head) {
    assert(head != NULL);

    for (size_t i = 0; i < head->children_count; i++)
        recursive_graph_free(head->children[i]);

    free(head);
}

void recursive_adv_graph_free(struct graph_link *link) {
    assert(link != NULL);

    if (link->type == OPERATOR) {
        for (size_t i = 0; i < link->ptr->op->children_count; i++)
            recursive_adv_graph_free(link->ptr->op->children[i]);

        free(link->ptr->op);
    } else {
        free(link->ptr->value);
    }

    free(link->ptr);
    free(link);
}

void recursive_expr_tree_free(struct expr_tree_head *head) {
    assert(head->head != NULL);

    free_tree_link(head->head);

    free(head);
}

void free_tree_val(struct expr_tree_val *val) {
    if (val->type == FLOAT) {
        mpf_clear(val->val->fp_val);
    } else if (val->type == RATIONAL) {
        mpq_clear(val->val->rational_val);
    } else {
        mpz_clear(val->val->int_val);
    }

    free(val->val);

    free(val);
}

void free_tree_link(struct expr_tree_link *link) {
    if (link->type == OPERATOR) {
        for (size_t i = 0; i < link->ptr->op->arg_count; i++)
            free_tree_link(link->ptr->op->args[i]);

        free(link->ptr->op->args);
        free(link->ptr->op);
    } else {
        if (link->ptr->val->type == INT) {
            mpz_clear(link->ptr->val->val->int_val);
        } else if (link->ptr->val->type == RATIONAL) {
            mpq_clear(link->ptr->val->val->rational_val);
        } else {
            mpf_clear(link->ptr->val->val->fp_val);
        }
        free(link->ptr->val->val);
        free(link->ptr->val);
    }

    free(link->ptr);
    free(link);
}
