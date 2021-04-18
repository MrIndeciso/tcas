#include <assert.h>
#include <stdlib.h>

//http://www.cybertester.com/data/gruntz.pdf
//https://github.com/sympy/sympy/blob/master/sympy/series/gruntz.py

#define GRUNTZ_DEBUG

#include "gruntz.h"
#include "mem_util.h"
#include "type_util.h"

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

    struct expr_tree_sym *sym = link->ptr->op->args[1]->ptr->sym;
    struct expr_tree_val *val = link->ptr->op->args[2]->ptr->val;


}
