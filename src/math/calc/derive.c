#include <assert.h>
#include <stdlib.h>

#include "derive.h"

#include "mem_util.h"
#include "type_util.h"
#include "tree_util.h"
#include "parse_util.h"
#include "simplify.h"
#include "rpn_defs.h"


struct expr_tree_link *derive(struct expr_tree_link *link) {
    if (link->type == VALUE) {
        return _derive_val(link);
    } else if (link->type == SYMBOL) {
        return _derive_sym(link);
    } else {
        return _derive_op(link);
    }
}

struct expr_tree_link *derive_n_times(struct expr_tree_link *link, int count)
{
    assert(count >= 0);
    struct expr_tree_link *ref = clone_link(link);
    for (int i = 0; i < count; i++) {
        ref = simplify(derive(ref));
    }
    return ref;
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
    int arg_count = op_arg_count(link->ptr->op->type);

    if (arg_count == 3) {
        assert("Not reached");
        return link;
    } else if (arg_count == 2) {
        struct expr_tree_link *first = link->ptr->op->args[0];
        struct expr_tree_link *second = link->ptr->op->args[1];
        struct expr_tree_link *dfirst = derive(first);
        struct expr_tree_link *dsecond = derive(second);

        switch (link->ptr->op->type) {
            case PLUS:
                return parse_double_expr("+ a b", dfirst, dsecond);
            case MINUS:
                return parse_double_expr("- a b", dfirst, dsecond);
            case TIMES:
                return parse_varargs("+ * a b * c d", 4, first, dsecond, dfirst, second);
            case DIVIDE:
                return parse_varargs("/ - * a b * c d ^ b 2", 4, dfirst, second, first, dsecond);
            default:
            {
                assert("Not reached");
                return link;
            }
        }
    } else if (arg_count == 1) {
        struct expr_tree_link *first = link->ptr->op->args[0];
        struct expr_tree_link *dfirst = derive(first);

        switch (link->ptr->op->type) {
            case SQRT:
                return parse_varargs("/ * -1 a * 2 sqrt b", 2, dfirst, first);
            case SIN:
                return parse_varargs("* cos a b", 2, first, dfirst);
            case COS:
                return parse_varargs("* - 0 sin a b", 2, first, dfirst);
            case EXP:
                return parse_varargs("* exp a b", 2, first, dfirst);
            default:
            {
                assert("Not reached");
                return link;
            }
        }
    } else {
        assert("Not reached");
        return link;
    }
}
