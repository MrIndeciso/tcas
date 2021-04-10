#include <assert.h>
#include <stdlib.h>

#include "mem_util.h"

#include "math.h"
#include "plus.h"
#include "minus.h"
#include "times.h"
#include "divide.h"
#include "log.h"
#include "trig.h"

struct expr_tree_link* math_eval_op(struct expr_tree_link *link) {
    assert(link != NULL);

    for (size_t i = 0; i < link->ptr->op->arg_count; i++) {
        struct expr_tree_link *arg = link->ptr->op->args[i];

        if (arg->type == OPERATOR) {
            link->ptr->op->args[i] = math_eval_op(arg);
        }

        //assert(link->ptr->op->args[i]->type == VALUE);
    }

    struct expr_tree_val *result = NULL;

    switch (link->ptr->op->type) {
        case PLUS:
            result = math_plus(link->ptr->op->args[0]->ptr->val, link->ptr->op->args[1]->ptr->val);
            break;
        case MINUS:
            result = math_minus(link->ptr->op->args[0]->ptr->val, link->ptr->op->args[1]->ptr->val);
            break;
        case TIMES:
            result = math_times(link->ptr->op->args[0]->ptr->val, link->ptr->op->args[1]->ptr->val);
            break;
        case DIVIDE:
            result = math_divide(link->ptr->op->args[0]->ptr->val, link->ptr->op->args[1]->ptr->val);
            break;
        case LOG10:
            result = math_log10(link->ptr->op->args[0]->ptr->val);
            break;
        case LOG2:
            result = math_log2(link->ptr->op->args[0]->ptr->val);
            break;
        case LN:
            result = math_ln(link->ptr->op->args[0]->ptr->val);
            break;
        case SIN:
            result = math_sin(link->ptr->op->args[0]->ptr->val);
            break;
        case COS:
            result = math_cos(link->ptr->op->args[0]->ptr->val);
            break;
        case TAN:
            result = math_tan(link->ptr->op->args[0]->ptr->val);
            break;
        case ARCSIN:
            result = math_arcsin(link->ptr->op->args[0]->ptr->val);
            break;
        case ARCCOS:
            result = math_arccos(link->ptr->op->args[0]->ptr->val);
            break;
        case ARCTAN:
            result = math_arctan(link->ptr->op->args[0]->ptr->val);
            break;
        default:
            assert(0);
            break;
    }

    struct expr_tree_link *new_link = malloc(sizeof(struct expr_tree_link));

    free_tree_link(link);

    new_link->type = VALUE;
    new_link->ptr = malloc(sizeof(union expr_tree_ptr));
    new_link->ptr->val = result;

    return new_link;
}
