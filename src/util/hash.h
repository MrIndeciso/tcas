#ifndef HASH_H
#define HASH_H

#include "expr_structs.h"

struct expr_hash {
    unsigned long long int hash;
};

struct expr_hash hash(struct expr_tree_link *link);

unsigned long djb2_str(char *str);

void _hash_link(struct expr_tree_link *link);
void _hash_sym(struct expr_tree_sym *sym);
void _hash_val(struct expr_tree_val *val);
void _hash_op(struct expr_tree_op *op);

int compare_hashes(struct expr_hash hash1, struct expr_hash hash2);
int compare_links(struct expr_tree_link *link1, struct expr_tree_link *link2);

#endif
