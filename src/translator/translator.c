#include <stdlib.h>

#include "translator.h"

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

        for (int i = 0; i < link->ptr->op->arg_count; i++)
            link->ptr->op->args[i] = parse(glink->ptr->op->children[i]);
    } else {
        link->ptr->val = malloc(sizeof(struct expr_tree_val));
        link->ptr->val->val = malloc(sizeof(union expr_tree_val_ref));
        link->ptr->val->type = INT;
        mpz_init(link->ptr->val->val->int_val);
        mpz_set_str(link->ptr->val->val->int_val, glink->ptr->value->content, 10);
    }

    return link;
}
