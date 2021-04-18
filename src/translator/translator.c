#include <mpfr.h>
#include <stdlib.h>
#include <string.h>

#include "translator.h"

#include "type_util.h"

static struct expr_tree_link* parse(struct graph_link *link);

struct expr_tree_head* translate_graph(struct graph_link *graph_head) {
    struct expr_tree_head *head = malloc(sizeof(struct expr_tree_head));

    head->head = parse(graph_head);

    return head;
}


static struct expr_tree_link* parse(struct graph_link *glink) {
    struct expr_tree_link *link = malloc(sizeof(struct expr_tree_link));

    link->type = glink->type;
    link->ptr = malloc(sizeof(union expr_tree_ptr));

    if (glink->type == OPERATOR) {
        link->ptr->op = malloc(sizeof(struct expr_tree_op));
        link->ptr->op->type = glink->ptr->op->type;
        link->ptr->op->arg_count = glink->ptr->op->children_count;
        link->ptr->op->args = malloc(link->ptr->op->arg_count * sizeof(struct expr_tree_link*));

        for (size_t i = 0; i < link->ptr->op->arg_count; i++)
            link->ptr->op->args[i] = parse(glink->ptr->op->children[i]);
    } else if (glink->type == SYMBOL) {
        link->ptr->sym = malloc(sizeof(struct expr_tree_sym));
        if (glink->ptr->symbol->symbol[0] == '+' || glink->ptr->symbol->symbol[0] == '-') {
            if (glink->ptr->symbol->symbol[0] == '+') {
                link->ptr->sym->sign = 1;
            } else {
                link->ptr->sym->sign = -1;
            }
            link->ptr->sym->representation = glink->ptr->symbol->symbol[1];
        } else {
            link->ptr->sym->sign = 1;
            link->ptr->sym->representation = glink->ptr->symbol->symbol[0];
        }
    } else {
        link->ptr->val = malloc(sizeof(struct expr_tree_val));
        link->ptr->val->val = malloc(sizeof(union expr_tree_val_ref));

        if (strcmp(glink->ptr->value->content, "+infinity") == 0) {
            link->ptr->val->type = FLOAT;
            mpfr_init(link->ptr->val->val->fp_val);
            mpfr_set_inf(link->ptr->val->val->fp_val, 1);
        } else if (strcmp(glink->ptr->value->content, "-infinity") == 0) {
            link->ptr->val->type = FLOAT;
            mpfr_init(link->ptr->val->val->fp_val);
            mpfr_set_inf(link->ptr->val->val->fp_val, -1);
        } else if (strcmp(glink->ptr->value->content, "e") == 0) {
            link->ptr->val->type = FLOAT;
            mpfr_init(link->ptr->val->val->fp_val);
            mpfr_const_euler(link->ptr->val->val->fp_val, MPFR_ROUNDING);
        } else if (strcmp(glink->ptr->value->content, "-e") == 0) {
            link->ptr->val->type = FLOAT;
            mpfr_init(link->ptr->val->val->fp_val);
            mpfr_const_euler(link->ptr->val->val->fp_val, MPFR_ROUNDING);
            mpfr_neg(link->ptr->val->val->fp_val, link->ptr->val->val->fp_val, MPFR_ROUNDING);
        } else if (strcmp(glink->ptr->value->content, "pi") == 0) {
            link->ptr->val->type = FLOAT;
            mpfr_init(link->ptr->val->val->fp_val);
            mpfr_const_pi(link->ptr->val->val->fp_val, MPFR_ROUNDING);
        } else if (strcmp(glink->ptr->value->content, "-pi") == 0) {
            link->ptr->val->type = FLOAT;
            mpfr_init(link->ptr->val->val->fp_val);
            mpfr_const_pi(link->ptr->val->val->fp_val, MPFR_ROUNDING);
            mpfr_neg(link->ptr->val->val->fp_val, link->ptr->val->val->fp_val, MPFR_ROUNDING);
        } else {
            link->ptr->val->type = INT;
            mpz_init_set_str(link->ptr->val->val->int_val, glink->ptr->value->content, 10);
        }
    }

    return link;
}
