#include <assert.h>
#include <stdlib.h>

#define MRV_DEBUG

#include "gruntz.h"
#include "hash.h"
#include "mem_util.h"
#include "mrv.h"
#include "tree_util.h"
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

    //Let's add a check for some common cases
    if (set1->count == 1 && set2->count == 1 && compare_links(set1->expr[0]->expr, set2->expr[0]->expr) == 0) { //same
        return set1;
    } else if (set1->count == 1 && set2->count == 1
               && hash(set1->expr[0]->expr).hash == 107374247936
               && hash(set2->expr[0]->expr).hash == 107374182400) { //set1 is e^x and set2 is x
        return set1;
    } else if (set1->count == 1 && set2->count == 1
               && hash(set1->expr[0]->expr).hash == 107374247936
               && hash(set2->expr[0]->expr).hash == 107374182400) { //set2 is e^x and set1 is x
        return set2;
    } else if (set1->count == 1 && set2->count == 1
               && hash(set1->expr[0]->expr).hash == 107374247936
               && hash(set2->expr[0]->expr).hash == 98784313344) { // set1 is e^x and set2 is e^-x
        return _mrv_join_sets(set1, set2);
    } else if (set1->count == 1 && set2->count == 1
               && hash(set2->expr[0]->expr).hash == 107374247936
               && hash(set1->expr[0]->expr).hash == 98784313344) { // set2 is e^x and set1 is e^-x
        return _mrv_join_sets(set1, set2);
    }

    //assert(0); //TODO Finish implementation

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
    assert(link->ptr->op->type == EXP);
    //Short path for e^x
    if (link->ptr->op->args[0]->type == SYMBOL
            && link->ptr->op->args[0]->ptr->sym->sign == 1) {
        struct gruntz_mrv *mrv = malloc(sizeof(struct gruntz_mrv));
        mrv->count = 1;
        mrv->expr = malloc(1 * sizeof(struct gruntz_expr*));
        mrv->expr[0] = malloc(sizeof(struct gruntz_expr));
        mrv->expr[0]->expr = link;
        return _mrv_max(mrv, _mrv_generic(link->ptr->op->args[0]));
    }
    //Short path for e^-x
    if (link->ptr->op->args[0]->type == SYMBOL
            && link->ptr->op->args[0]->ptr->sym->sign == -1) {
        return _mrv_generic(link->ptr->op->args[0]);
    }


    struct expr_tree_link *recurse = parse_expr("lim a x +infinity", link->ptr->op->args[0]);

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

struct gruntz_mrv *_mrv_join_sets(struct gruntz_mrv *set1, struct gruntz_mrv *set2) {
    struct gruntz_mrv *new = malloc(sizeof(struct gruntz_mrv));
    new->count = set1->count + set2->count;
    new->expr = malloc(sizeof(struct gruntz_expr*));

    for (size_t i = 0; i < set1->count; i++)
        new->expr[i] = set1->expr[i];

    for (size_t i = 0; i < set2->count; i++)
        new->expr[set1->count + i] = set2->expr[i];

    free(set1);
    free(set2);

    return new;
}
