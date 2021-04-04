#include <assert.h>
#include <stdlib.h>

#include "mem_util.h"

#include "math.h"
#include "plus.h"

struct expr_tree_link* math_eval_op(struct expr_tree_link *link) {
    assert(link != NULL);

    for (size_t i = 0; i < link->ptr->op->arg_count; i++)
        assert(link->ptr->op->args[i]->type == VALUE);

    struct expr_tree_val *result = NULL;

    switch (link->ptr->op->type) {
    case PLUS:
        result = math_plus(link->ptr->op->args[0]->ptr->val, link->ptr->op->args[1]->ptr->val);
        break;
    default:
        break;
    }

    struct expr_tree_link *new_link = malloc(sizeof(struct expr_tree_link));

    free_tree_link(link);

    new_link->type = VALUE;
    new_link->ptr = malloc(sizeof(union expr_tree_ptr));
    new_link->ptr->val = result;

    return new_link;
}
