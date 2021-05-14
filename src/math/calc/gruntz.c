#include <assert.h>
#include <mpfr.h>
#include <stdlib.h>

//http://www.cybertester.com/data/gruntz.pdf
//https://github.com/sympy/sympy/blob/master/sympy/series/gruntz.py

#define GRUNTZ_DEBUG

#include "gruntz.h"
#include "mem_util.h"
#include "type_util.h"
#include "tree_util.h"

#ifdef GRUNTZ_DEBUG
#include "translator_util.h"
#endif

struct expr_tree_link* gruntz_eval(struct expr_tree_link *link) {
    struct expr_tree_link *new_link = malloc(sizeof(struct expr_tree_link));

#ifdef GRUNTZ_DEBUG
    struct expr_tree_head fake_head = (struct expr_tree_head) {.head = link};
    export_expr_tree_to_xml("gruntz_start.xml", &fake_head);
#endif

    //First thing we need to do is to rewrite the limit so it always tends to +infinity
    gruntz_rewrite_lim(link);

#ifdef GRUNTZ_DEBUG
    export_expr_tree_to_xml("gruntz_rewritten.xml", &fake_head);
#endif

    free_tree_link(link);

    new_link->type = VALUE;
    new_link->ptr = malloc(sizeof(union expr_tree_ptr));

    return new_link;
}

void gruntz_rewrite_lim(struct expr_tree_link *link) {
    assert(link->ptr->op->args[1]->type == SYMBOL);
    assert(link->ptr->op->args[2]->type == VALUE);

    struct expr_tree_link *expr = link->ptr->op->args[0];
    struct expr_tree_sym *sym = link->ptr->op->args[1]->ptr->sym;
    struct expr_tree_val *val = link->ptr->op->args[2]->ptr->val;

    if (val->type == FLOAT) { //Could be infinity, pi, e or something else
        if (mpfr_inf_p(val->val->fp_val)) { //It is +-infinity
            if (mpfr_sgn(val->val->fp_val) > 0) { //Already calculating limit for +infinity, nothing needed to do
                return;
            } else { //Need to swap signs
                invert_symbol_signs(expr, sym);
            }
        }
    } else if (val->type == RATIONAL) { //Oh god please no

    } else { //Int
        if (mpz_cmp_ui(val->val->int_val, 0) == 0) { //Ah finally something good
            struct expr_tree_link *new = malloc(sizeof(struct expr_tree_link));
            new->type = OPERATOR;
            new->ptr = malloc(sizeof(union expr_tree_ptr));
            new->ptr->op = malloc(sizeof(struct expr_tree_op));
            new->ptr->op->type = DIVIDE;
            new->ptr->op->arg_count = 2;
            new->ptr->op->args = malloc(2 * sizeof(struct expr_tree_link*));
            new->ptr->op->args[0] = malloc(sizeof(struct expr_tree_link));
            new->ptr->op->args[0]->type = VALUE;
            new->ptr->op->args[0]->ptr = malloc(sizeof(union expr_tree_ptr));
            new->ptr->op->args[0]->ptr->val = malloc(sizeof(struct expr_tree_val));
            new->ptr->op->args[0]->ptr->val->type = INT;
            new->ptr->op->args[0]->ptr->val->val = malloc(sizeof(union expr_tree_val_ref));
            mpz_init_set_ui(new->ptr->op->args[0]->ptr->val->val->int_val, 1);
            new->ptr->op->args[1] = clone_link(link->ptr->op->args[1]);

            recursive_replace(expr, link->ptr->op->args[1], new);
        }
    }

}
