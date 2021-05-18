#include <gmp.h>
#include <mpfr.h>

#include "hash.h"

static unsigned long sym_hash = 0;
static unsigned long op_hash = 0;
static unsigned long val_hash = 0;

struct expr_hash hash(struct expr_tree_link *link) {
    sym_hash = 0;
    op_hash = 0;
    val_hash = 0;
    _hash_link(link);
    struct expr_hash result = {.hash = 0};
    result.hash += sym_hash;
    result.hash << 16;
    result.hash += op_hash;
    result.hash << 16;
    result.hash += val_hash;
    return result;
}

//http://www.cse.yorku.ca/~oz/hash.html
unsigned long djb2_str(char *str) {
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c;

    return hash;
}

void _hash_link(struct expr_tree_link *link) {
    if (link->type == SYMBOL) {
        _hash_sym(link->ptr->sym);
    } else if (link->type == VALUE) {
        _hash_val(link->ptr->val);
    } else {
        _hash_op(link->ptr->op);
    }
}

void _hash_sym(struct expr_tree_sym *sym) {
    sym_hash << 2;
    sym_hash += (unsigned long) sym->sign;
    sym_hash += (unsigned long) (sym->representation & 0b00011111);
}

void _hash_val(struct expr_tree_val *val) {
    val_hash *= (unsigned long)(val->type + 1);
    val_hash << 2;
    char *str = malloc(32);
    if (val->type == INT) {
        gmp_snprintf(str, 32, "%.Zd", val->val->int_val);
    } else if (val->type == RATIONAL) {
        gmp_snprintf(str, 32, "%Qx", val->val->rational_val);
    } else {
        mpfr_snprintf(str, 32, "%Re", val->val->fp_val);
    }
    val_hash += djb2_str(str);
    free(str);
}

void _hash_op(struct expr_tree_op *op) {
    op_hash *= (unsigned int) (op->type + 1);
    op_hash += (unsigned int) op->arg_count);

    for (size_t i = 0; i < op->arg_count; i++)
        _hash_link(op->args[i]);
}
