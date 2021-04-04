#ifndef EXPR_STRUCTS_H
#define EXPR_STRUCTS_H

#include <stdio.h>
#include <stddef.h>
#include <gmp.h>

#include "parser_enums.h"

enum VAL_TYPE {
    INT = 0b001,
    RATIONAL = 0b010,
    FLOAT = 0b100,
};

struct expr_tree_head {
    struct expr_tree_link *head;
};

struct expr_tree_op {
    enum OPERATOR_TYPE type;
    size_t arg_count;
    struct expr_tree_link **args;
};

struct expr_tree_val {
    enum VAL_TYPE type;
    union expr_tree_val_ref *val;
};

struct expr_tree_link {
    enum LINKED_TYPE type;
    union expr_tree_ptr *ptr;
};

union expr_tree_ptr {
    struct expr_tree_val *val;
    struct expr_tree_op *op;
};

union expr_tree_val_ref {
    mpz_t int_val;
    mpq_t rational_val;
    mpf_t fp_val;
};


#endif
