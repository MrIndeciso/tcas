#include <assert.h>
#include <stdlib.h>

#include "derive.h"

#include "mem_util.h"
#include "type_util.h"
#include "tree_util.h"
#include "parse_util.h"


struct expr_tree_link *derive(struct expr_tree_link *link) {
    if (link->type == VALUE) {
        return _derive_val(link);
    } else if (link->type == SYMBOL) {
        return _derive_sym(link);
    } else {
        return _derive_op(link);
    }
}

struct expr_tree_link  *_derive_sym(struct expr_tree_link *link) {
    if (link->ptr->sym->sign == -1) {
        return parse_expr("-1", NULL);
    } else {
        return parse_expr("1", NULL);
    }
}

struct expr_tree_link *_derive_val(struct expr_tree_link *link) {
    return parse_expr("0", NULL);
}

struct expr_tree_link *_derive_op(struct expr_tree_link *link) {
    switch (link->ptr->op->type) {
        case PLUS:
        {
            struct expr_tree_link *first = link->ptr->op->args[0];
            struct expr_tree_link *second = link->ptr->op->args[1];
            struct expr_tree_link *dfirst = derive(first);
            struct expr_tree_link *dsecond = derive(second);
            return parse_double_expr("+ a b", dfirst, dsecond);
        }
        case MINUS:
        {
            struct expr_tree_link *first = link->ptr->op->args[0];
            struct expr_tree_link *second = link->ptr->op->args[1];
            struct expr_tree_link *dfirst = derive(first);
            struct expr_tree_link *dsecond = derive(second);
            return parse_double_expr("- a b", dfirst, dsecond);
        }
        case TIMES:
        {
            struct expr_tree_link *first = link->ptr->op->args[0];
            struct expr_tree_link *second = link->ptr->op->args[1];
            struct expr_tree_link *dfirst = derive(first);
            struct expr_tree_link *dsecond = derive(second);
            return parse_varargs("+ * a b * c d", 4, first, dsecond, dfirst, second);
        }
        default:
            return link;
    }
}
