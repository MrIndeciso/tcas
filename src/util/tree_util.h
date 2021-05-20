#ifndef TREE_UTIL_H
#define TREE_UTIL_H

#include "expr_structs.h"

//0 for equality
int compare_symbols(struct expr_tree_sym *sym1, struct expr_tree_sym *sym2);
int compare_symbols_ignore_sign(struct expr_tree_sym *sym1, struct expr_tree_sym *sym2);
int compare_vals(struct expr_tree_val *val1, struct expr_tree_val *val2);
int compare_ops(struct expr_tree_op *op1, struct expr_tree_op *op2);
int compare_links(struct expr_tree_link *link1, struct expr_tree_link *link2);

void invert_symbol_signs(struct expr_tree_link *head, struct expr_tree_sym *sym);

//
void recursive_replace(
        struct expr_tree_link *head,
        struct expr_tree_link *find,
        struct expr_tree_link *replace
);

void recursive_replace_dont_free(
        struct expr_tree_link *head,
        struct expr_tree_link *find,
        struct expr_tree_link *replace
);

void recursive_sym_replace(
        struct expr_tree_link *head,
        struct expr_tree_link *find,
        struct expr_tree_link *replace
);

#endif
