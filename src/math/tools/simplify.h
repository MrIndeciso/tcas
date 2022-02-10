#ifndef SIMPLIFY_H
#define SIMPLIFY_H

#include "expr_structs.h"

struct expr_tree_link *simplify(struct expr_tree_link *link);
struct expr_tree_link *_simplify(struct expr_tree_link *link);

struct expr_tree_link *analyze_explog(struct expr_tree_link *link);

struct expr_tree_link *analyze_division(struct expr_tree_link *link);

struct expr_tree_link *analyze_times(struct expr_tree_link *link);

struct expr_tree_link *analyze_power(struct expr_tree_link *link);

struct expr_tree_link *truncate_useless(struct expr_tree_link *link);

#endif
