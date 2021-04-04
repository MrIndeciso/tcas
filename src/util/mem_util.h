#ifndef MEM_UTIL_H
#define MEM_UTIL_H

#include "parser_structs.h"
#include "expr_structs.h"

void recursive_graph_free(struct graph_node *head);

void recursive_adv_graph_free(struct graph_link *head);

void recursive_expr_tree_free(struct expr_tree_head *head);

void free_tree_link(struct expr_tree_link *link);

void free_tree_val(struct expr_tree_val *val);

#endif
