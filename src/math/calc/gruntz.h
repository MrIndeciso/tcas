#ifndef GRUNTZ_H
#define GRUNTZ_H

struct expr_tree_link* gruntz_eval(struct expr_tree_link *link);

void gruntz_rewrite_lim(struct expr_tree_link *link);

#endif
