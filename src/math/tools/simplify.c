#include <assert.h>
#include <gmp.h>
#include <mpfr.h>
#include <stdlib.h>

#include "hash.h"
#include "parse_util.h"
#include "simplify.h"
#include "tree_util.h"
#include "mem_util.h"

//Patterns we try to optimize for:
//1) ln - exp / exp - ln
//2) div - div
//3) times 1
//4) div 1
//5) plus 0
//6) 1 / exp
//7) 1 / exp (a - b) -> (b - a)

struct expr_tree_link *simplify(struct expr_tree_link *link) {
    return truncate_useless(_simplify(_simplify(link)));
}

struct expr_tree_link *_simplify(struct expr_tree_link *link) {
    if (link->type != OPERATOR) return link;

    for (size_t i = 0; i < link->ptr->op->arg_count; i++) {
        link->ptr->op->args[i] = _simplify(link->ptr->op->args[i]);
    }

    switch (link->ptr->op->type) {
        case LN:
        case EXP:
            return analyze_explog(link);
            break;
        case DIVIDE:
            return analyze_division(link);
            break;
        default:
            return link;
            break;
    }
}

struct expr_tree_link *analyze_explog(struct expr_tree_link *link) {
    if (link->ptr->op->args[0]->type != OPERATOR) return link;

    if ((link->ptr->op->type == EXP
         && link->ptr->op->args[0]->ptr->op->type == LN) ||
            (link->ptr->op->type == LN
             && link->ptr->op->args[0]->ptr->op->type == EXP)) {
        struct expr_tree_link *new = link->ptr->op->args[0]->ptr->op->args[0];
        link->ptr->op->args[0]->ptr->op->arg_count = 0;
        free_tree_link(link);
        return new;
    } else {
        return link;
    }
}

struct expr_tree_link *analyze_division(struct expr_tree_link *link) {
    if (link->ptr->op->args[1]->type != OPERATOR) {
        return link;
    } else if (link->ptr->op->args[1]->ptr->op->type == DIVIDE) {
        struct expr_tree_link *new = malloc(sizeof(struct expr_tree_link));
        new->type = OPERATOR;
        new->ptr = malloc(sizeof(union expr_tree_ptr));
        new->ptr->op = malloc(sizeof(struct expr_tree_op));
        new->ptr->op->type = TIMES;
        new->ptr->op->arg_count = 2;
        new->ptr->op->args = malloc(2 * sizeof(struct expr_tree_link*));
        new->ptr->op->args[0] = link->ptr->op->args[0];
        new->ptr->op->args[1] = malloc(sizeof(struct expr_tree_link));
        new->ptr->op->args[1]->type = OPERATOR;
        new->ptr->op->args[1]->ptr = malloc(sizeof(union expr_tree_ptr));
        new->ptr->op->args[1]->ptr->op = malloc(sizeof(struct expr_tree_op));
        new->ptr->op->args[1]->ptr->op->type = DIVIDE;
        new->ptr->op->args[1]->ptr->op->arg_count = 2;
        new->ptr->op->args[1]->ptr->op->args = malloc(2 * sizeof(struct expr_tree_link*));
        new->ptr->op->args[1]->ptr->op->args[0] = link->ptr->op->args[1]->ptr->op->args[1];
        new->ptr->op->args[1]->ptr->op->args[1] = link->ptr->op->args[1]->ptr->op->args[0];
        link->ptr->op->args[1]->ptr->op->arg_count = 0;
        free_tree_link(link->ptr->op->args[1]);
        link->ptr->op->arg_count = 0;
        free_tree_link(link);
        return new;
    } else if (link->ptr->op->args[1]->ptr->op->type == EXP) {
        //Let's have to different behaviour based on what the expression is, just a short path for a common combo
        if (hash(link->ptr->op->args[1]).hash == 107374247936) { //e^x
            return parse_expr("* a exp -x", link->ptr->op->args[0]);
        } else if (hash(link->ptr->op->args[1]).hash == 98784313344) { //e^-x
            return parse_expr("* a exp x", link->ptr->op->args[0]);
        } else if (link->ptr->op->args[1]->ptr->op->args[0]->type == OPERATOR
                   && link->ptr->op->args[1]->ptr->op->args[0]->ptr->op->type == MINUS) { //e^(a-b) becomes e^(b-a)
            struct expr_tree_link *temp = link->ptr->op->args[1]->ptr->op->args[0]->ptr->op->args[0];
            link->ptr->op->args[1]->ptr->op->args[0]->ptr->op->args[0] = link->ptr->op->args[1]->ptr->op->args[0]->ptr->op->args[1];
            link->ptr->op->args[1]->ptr->op->args[0]->ptr->op->args[1] = temp;
            return parse_double_expr("* a exp b", link->ptr->op->args[0], link->ptr->op->args[1]->ptr->op->args[0]);
        } else { //Anything else
            return parse_double_expr("* a exp - 0 b", link->ptr->op->args[0], link->ptr->op->args[1]->ptr->op->args[0]);
        }
    } else {
        return link;
    }
}

struct expr_tree_link *truncate_useless(struct expr_tree_link *link) {
    if (link->type != OPERATOR) return link;

    for (size_t i = 0; i < link->ptr->op->arg_count; i++) {
        link->ptr->op->args[i] = truncate_useless(link->ptr->op->args[i]);
    }

    if (link->ptr->op->type == TIMES) {
        if (link->ptr->op->args[0]->type == VALUE) {
            if (link->ptr->op->args[0]->ptr->val->type == INT) {
                if (mpz_cmp_ui(link->ptr->op->args[0]->ptr->val->val->int_val, 1) == 0) { //Multiply by 1
                    free_tree_link(link->ptr->op->args[0]);
                    link->ptr->op->arg_count = 0;
                    struct expr_tree_link *new = link->ptr->op->args[1];
                    free_tree_link(link);
                    return new;
                } else return link;
            } else return link;
        } else if (link->ptr->op->args[1]->type == VALUE) {
            if (link->ptr->op->args[1]->ptr->val->type == INT) {
                if (mpz_cmp_ui(link->ptr->op->args[1]->ptr->val->val->int_val, 1) == 0) { //Multiply by 1
                    free_tree_link(link->ptr->op->args[1]);
                    link->ptr->op->arg_count = 0;
                    struct expr_tree_link *new = link->ptr->op->args[0];
                    free_tree_link(link);
                    return new;
                } else return link;
            } else return link;
        } else {
            return link;
        }
    } else if (link->ptr->op->type == DIVIDE) {
        if (link->ptr->op->args[1]->type == VALUE) {
            if (link->ptr->op->args[1]->ptr->val->type == INT) {
                if (mpz_cmp_ui(link->ptr->op->args[1]->ptr->val->val->int_val, 1) == 0) { //Divide by 1
                    free_tree_link(link->ptr->op->args[1]);
                    link->ptr->op->arg_count = 0;
                    struct expr_tree_link *new = link->ptr->op->args[0];
                    free_tree_link(link);
                    return new;
                } else return link;
            } else return link;
        } else {
            return link;
        }
    } else if (link->ptr->op->type == PLUS/* || link->ptr->op->type == MINUS*/) {
        if (link->ptr->op->args[0]->type == VALUE) {
            if (link->ptr->op->args[0]->ptr->val->type == INT) {
                if (mpz_cmp_ui(link->ptr->op->args[0]->ptr->val->val->int_val, 0) == 0) { //Sum/subtract by 0
                    free_tree_link(link->ptr->op->args[0]);
                    link->ptr->op->arg_count = 0;
                    struct expr_tree_link *new = link->ptr->op->args[1];
                    free_tree_link(link);
                    return new;
                } else return link;
            } else return link;
        } else if (link->ptr->op->args[1]->type == VALUE) {
            if (link->ptr->op->args[1]->ptr->val->type == INT) {
                if (mpz_cmp_ui(link->ptr->op->args[1]->ptr->val->val->int_val, 0) == 0) { //Sum/subtract by 0
                    free_tree_link(link->ptr->op->args[1]);
                    link->ptr->op->arg_count = 0;
                    struct expr_tree_link *new = link->ptr->op->args[0];
                    free_tree_link(link);
                    return new;
                } else return link;
            } else return link;
        } else {
            return link;
        }
    } else {
        return link;
    }
}
