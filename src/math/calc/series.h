#ifndef SERIES_H
#define SERIES_H

#include "expr_structs.h"

struct expr_tree_link *compute_gruntz_result(struct expr_tree_link *link);

struct expr_tree_link *compute_taylor_series(struct expr_tree_link *link, struct expr_tree_val center);

struct expr_tree_link *computer_maclaurin(struct expr_tree_link *link);

#endif
