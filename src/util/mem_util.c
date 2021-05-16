#include <assert.h>
#include <gmp.h>
#include <mpfr.h>
#include <stdlib.h>

#include "mem_util.h"
#include "type_util.h"

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
    } else if (link->type == SYMBOL) {
        free(link->ptr->symbol);
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
        mpfr_clear(val->val->fp_val);
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
    } else if (link->type == SYMBOL) {
        free(link->ptr->sym);
    } else {
        free_tree_val(link->ptr->val);
    }

    free(link->ptr);
    free(link);
}

struct expr_tree_link* clone_link(struct expr_tree_link *master) {
    struct expr_tree_link *clone = malloc(sizeof(struct expr_tree_link));
    clone->type = master->type;
    clone->ptr = malloc(sizeof(union expr_tree_ptr));
    if (clone->type == SYMBOL) {
        clone->ptr->sym = clone_tree_sym(master->ptr->sym);
    } else if (clone->type == OPERATOR) {
        clone->ptr->op = clone_tree_op(master->ptr->op);
    } else {
        clone->ptr->val = clone_tree_val(master->ptr->val);
    }
    return clone;
}

struct expr_tree_val* clone_tree_val(struct expr_tree_val *master) {
    struct expr_tree_val *clone = malloc(sizeof(struct expr_tree_val));
    clone->type = master->type;
    clone->val = malloc(sizeof(union expr_tree_val_ref));
    if (clone->type == RATIONAL) {
        mpq_init(clone->val->rational_val);
        mpq_set(clone->val->rational_val, master->val->rational_val);
    } else if (clone->type == INT) {
        mpz_init_set(clone->val->int_val, master->val->int_val);
    } else { //Float
        mpfr_init_set(clone->val->fp_val, master->val->fp_val, MPFR_ROUNDING);
    }
    return clone;
}

struct expr_tree_sym* clone_tree_sym(struct expr_tree_sym *master) {
    struct expr_tree_sym *clone = malloc(sizeof(struct expr_tree_sym));
    clone->representation = master->representation;
    clone->sign = master->sign;
    return clone;
}

struct expr_tree_op* clone_tree_op(struct expr_tree_op *master) {
    struct expr_tree_op *clone = malloc(sizeof(struct expr_tree_op));
    clone->type = master->type;
    clone->arg_count = master->arg_count;
    clone->args = malloc(clone->arg_count * sizeof(struct expr_tree_link*));
    for (size_t i = 0; i < clone->arg_count; i++) {
        clone->args[i] = clone_link(master->args[i]);
    }
    return clone;
}
