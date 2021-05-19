#include <gmp.h>
#include <mpfr.h>

#include "tree_util.h"
#include "mem_util.h"

int compare_symbols(struct expr_tree_sym *sym1, struct expr_tree_sym *sym2) {
    return (sym1->representation - sym2->representation) + (sym1->sign - sym2->sign);
}

int compare_symbols_ignore_sign(struct expr_tree_sym *sym1, struct expr_tree_sym *sym2) {
    return sym1->representation - sym2->representation;
}

int compare_vals(struct expr_tree_val *val1, struct expr_tree_val *val2) {
    if (val1->type != val2->type) {
        return 1;
    }

    if (val1->type == FLOAT) {
        return mpfr_cmp(val1->val->fp_val, val2->val->fp_val);
    } else if (val1->type == RATIONAL) {
        return mpq_cmp(val1->val->rational_val, val2->val->rational_val);
    } else {
        return mpz_cmp(val1->val->int_val, val2->val->int_val);
    }
}

int compare_ops(struct expr_tree_op *op1, struct expr_tree_op *op2) {
    if (op1->type != op2->type) {
        return 1;
    } else if (op1->arg_count != op2->arg_count) {
        return 1;
    }

    for (size_t i = 0; i < op1->arg_count; i++) {
        if (compare_links(op1->args[i], op2->args[i])) {
            return 1;
        }
    }

    return 0;
}

int compare_links(struct expr_tree_link *link1, struct expr_tree_link *link2) {
    if (link1->type != link2->type) {
        return 1;
    }

    if (link1->type == OPERATOR) {
        return compare_ops(link1->ptr->op, link2->ptr->op);
    } else if (link1->type == SYMBOL) {
        return compare_symbols(link1->ptr->sym, link2->ptr->sym);
    } else {
        return compare_vals(link1->ptr->val, link2->ptr->val);
    }
}

void invert_symbol_signs(struct expr_tree_link *head, struct expr_tree_sym *sym) {
    if (head->type == OPERATOR) {
        for (size_t i = 0; i < head->ptr->op->arg_count; i++) {
            invert_symbol_signs(head->ptr->op->args[i], sym);
        }
    } else if (head->type == SYMBOL) {
        if (compare_symbols_ignore_sign(head->ptr->sym, sym) == 0) {
            head->ptr->sym->sign *= -1;
        }
    }
}

void recursive_replace(
        struct expr_tree_link *head,
        struct expr_tree_link *find,
        struct expr_tree_link *replace
) {
    if (head->type == OPERATOR) { //Has children
        for (size_t i = 0; i < head->ptr->op->arg_count; i++) {
            recursive_replace(head->ptr->op->args[i], find, replace);
        }

        for (size_t i = 0; i < head->ptr->op->arg_count; i++) {
            if (compare_links(head->ptr->op->args[i], find) == 0) {
                free_tree_link(head->ptr->op->args[i]);
                struct expr_tree_link *clone = clone_link(replace);
                head->ptr->op->args[i] = clone;
                //return;
            }
        }
    }
}

void recursive_sym_replace(
        struct expr_tree_link *head,
        struct expr_tree_link *find,
        struct expr_tree_link *replace
) {
    if (head->type == OPERATOR) { //Has children
        for (size_t i = 0; i < head->ptr->op->arg_count; i++) {
            if (head->ptr->op->args[i]->type == OPERATOR) {
                recursive_sym_replace(head->ptr->op->args[i], find, replace);
            } else if (head->ptr->op->args[i]->type == SYMBOL) {
                if (compare_links(head->ptr->op->args[i], find) == 0) {
                    free_tree_link(head->ptr->op->args[i]);
                    struct expr_tree_link *clone = clone_link(replace);
                    head->ptr->op->args[i] = clone;
                }
            }
        }
    }
}
