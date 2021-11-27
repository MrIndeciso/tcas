#ifndef DERIVE_H
#define DERIVE_H

struct expr_tree_link *derive(struct expr_tree_link *link);

struct expr_tree_link *_derive_op(struct expr_tree_link *link);
struct expr_tree_link *_derive_sym(struct expr_tree_link *link);
struct expr_tree_link *_derive_val(struct expr_tree_link *link);

#endif
