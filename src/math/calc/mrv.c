#include <assert.h>
#include <stdlib.h>

#define MRV_DEBUG

#include "gruntz.h"
#include "mem_util.h"
#include "mrv.h"
#include "parse_util.h"

#ifdef MRV_DEBUG
#include "translator_util.h"
#endif

inline struct gruntz_mrv *recursive_mrv_finder(struct expr_tree_link *link) {
    return _mrv_generic(link);
}

struct gruntz_mrv *_mrv_max(struct gruntz_mrv *set1, struct gruntz_mrv *set2) {
    if (set1->count == 0) return set2;
    if (set2->count == 0) return set1;

    return set2;
}

struct gruntz_mrv *_mrv_generic(struct expr_tree_link *link) {
    if (link->type == VALUE) {
        return _mrv_val(link);
    } else if (link->type == SYMBOL) {
        return _mrv_sym(link);
    } else {
        return _mrv_op(link);
    }
}

struct gruntz_mrv *_mrv_val(struct expr_tree_link *link) {
    struct gruntz_mrv *mrv = malloc(sizeof(struct gruntz_mrv));
    mrv->count = 0;
    return mrv;
}

struct gruntz_mrv *_mrv_sym(struct expr_tree_link *link) {
    struct gruntz_mrv *mrv = malloc(sizeof(struct gruntz_mrv));
    mrv->count = 1;
    mrv->expr = malloc(1 * sizeof(struct gruntz_expr*));
    struct gruntz_expr *res = malloc(sizeof(struct gruntz_expr));
    res->expr = link;
    mrv->expr[0] = res;
    return mrv;
}

struct gruntz_mrv *_mrv_op(struct expr_tree_link *link) {
    switch (link->ptr->op->type) {
        case PLUS:
        case MINUS:
        case TIMES:
        case DIVIDE:
            return _mrv_max(_mrv_generic(link->ptr->op->args[0]), _mrv_generic(link->ptr->op->args[1]));
            break;
        case SQRT:
        case SIN:
        case COS:
        case TAN:
        case LN:
        case LOG10:
        case LOG2:
            return _mrv_generic(link->ptr->op->args[0]);
            break;
        case ROOT:
        case POWER:
            assert(link->ptr->op->args[1]->type == VALUE);
            return _mrv_generic(link->ptr->op->args[0]);
            break;
        case EXP:
            return _mrv_exp(link);
            break;
        default:
            assert(0);
    }
}

struct gruntz_mrv *_mrv_exp(struct expr_tree_link *link) {
    struct expr_tree_link *recurse = parse_expr("lim y x +infinity", link->ptr->op->args[0]);

#ifdef MRV_DEBUG
    struct expr_tree_head fake_head = (struct expr_tree_head) {.head = recurse};
    export_expr_tree_to_xml("mrv_exp.xml", &fake_head);
#endif

    if (gruntz_eval(recurse)->ptr->val->type == FLOAT) { //Let's assume it's +-infinity for now
        struct gruntz_mrv *mrv = malloc(sizeof(struct gruntz_mrv));
        mrv->count = 1;
        mrv->expr = malloc(1 * sizeof(struct gruntz_expr*));
        mrv->expr[0] = malloc(sizeof(struct gruntz_expr));
        mrv->expr[0]->expr = link;
        return _mrv_max(mrv, _mrv_generic(link->ptr->op->args[0]));
    } else {
        return _mrv_generic(link->ptr->op->args[0]);
    }
}
