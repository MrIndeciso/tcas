#ifndef GRUNTZ_H
#define GRUNTZ_H

#include "expr_structs.h"
#include "gruntz_types.h"

struct expr_tree_link* gruntz_eval(struct expr_tree_link *link);

void gruntz_restate_lim(struct expr_tree_link *link);
void gruntz_set_lim_value(struct expr_tree_link *link);
void gruntz_rewrite_lim(struct expr_tree_link *link, struct gruntz_mrv *mrv);

struct gruntz_mrv *gruntz_find_mrv_set(struct expr_tree_link *link);

#endif
