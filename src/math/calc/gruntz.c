#include <stdlib.h>

//http://www.cybertester.com/data/gruntz.pdf

#include "gruntz.h"

#include "mem_util.h"

struct expr_tree_link* gruntz_eval(struct expr_tree_link *link) {
    struct expr_tree_link *new_link = malloc(sizeof(struct expr_tree_link));

    free_tree_link(link);

    new_link->type = VALUE;
    new_link->ptr = malloc(sizeof(union expr_tree_ptr));

    return new_link;
}

