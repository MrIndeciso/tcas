#include <stdlib.h>

#include "reducer.h"

static struct expr_tree_link* reduce_link(struct expr_tree_link *link);

struct expr_tree_val* reduce(struct expr_tree_head *head) {
    return reduce_link(head->head)->ptr->val; //TODO fix
}

static struct expr_tree_link* reduce_link(struct expr_tree_link *link) {
    if (link->type == VALUE) {
        return link;
    } else {
        for (size_t i = 0; i < link->ptr->op->arg_count; i++)
            link->ptr->op->args[i] = reduce_link(link->ptr->op->args[i]);


    }
}
