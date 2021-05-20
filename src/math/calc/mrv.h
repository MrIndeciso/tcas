#ifndef MRV_H
#define MRV_H

#include "expr_structs.h"
#include "gruntz_types.h"

struct gruntz_mrv *recursive_mrv_finder(struct expr_tree_link *link);

struct gruntz_mrv *_mrv_max(struct gruntz_mrv *set1, struct gruntz_mrv *set2);

struct gruntz_mrv *_mrv_generic(struct expr_tree_link *link);
struct gruntz_mrv *_mrv_val(struct expr_tree_link *link);
struct gruntz_mrv *_mrv_sym(struct expr_tree_link *link);
struct gruntz_mrv *_mrv_op(struct expr_tree_link *link);

struct gruntz_mrv *_mrv_exp(struct expr_tree_link *link);

struct gruntz_mrv *_mrv_join_sets(struct gruntz_mrv *set1, struct gruntz_mrv *set2);

struct gruntz_mrv *mrv_rewrite(struct gruntz_mrv *mrv);

#endif
