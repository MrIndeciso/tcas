#ifndef TRANSLATOR_UTIL_H
#define TRANSLATOR_UTIL_H

#include "../types/expr_structs.h"

void recursive_expr_tree_free(struct expr_tree_head *head);

void export_expr_tree_to_xml(char *filename, struct expr_tree_head *head);

#endif
