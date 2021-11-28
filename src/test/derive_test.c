#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "derive_test.h"

#include "mem_util.h"
#include "test_util.h"
#include "derive.h"
#include "parse_util.h"
#include "hash.h"

void test_derive_ops() {
    test_derive_1();
    test_derive_2();
    test_derive_3();
    test_derive_4();
    test_derive_5();
}

void test_derive_1() {
    struct expr_tree_link *test = parse_expr("x", NULL);
    struct expr_tree_link *result = parse_expr("1", NULL);

    struct expr_tree_link *derivative = derive(test);

    result(compare_link_hash(derivative, result) == 0);

    free_tree_link(test);
    free_tree_link(result);
    free_tree_link(derivative);
}

void test_derive_2() {
    struct expr_tree_link *test = parse_expr("-x", NULL);
    struct expr_tree_link *result = parse_expr("-1", NULL);

    struct expr_tree_link *derivative = derive(test);

    result(compare_link_hash(derivative, result) == 0);

    free_tree_link(test);
    free_tree_link(result);
    free_tree_link(derivative);
}

void test_derive_3() {
    struct expr_tree_link *test = parse_expr("33", NULL);
    struct expr_tree_link *result = parse_expr("0", NULL);

    struct expr_tree_link *derivative = derive(test);

    result(compare_link_hash(derivative, result) == 0);

    free_tree_link(test);
    free_tree_link(result);
    free_tree_link(derivative);
}

void test_derive_4() {
    struct expr_tree_link *test = parse_expr("+ x x", NULL);
    struct expr_tree_link *result = parse_expr("+ 1 1", NULL);

    struct expr_tree_link *derivative = derive(test);

    result(compare_link_hash(derivative, result) == 0);

    free_tree_link(test);
    free_tree_link(result);
    free_tree_link(derivative);
}

void test_derive_5() {
    struct expr_tree_link *test = parse_expr("* x x", NULL);
    struct expr_tree_link *result = parse_expr("+ * x 1 * 1 x", NULL);

    struct expr_tree_link *derivative = derive(test);

    result(compare_link_hash(derivative, result) == 0);

    free_tree_link(test);
    free_tree_link(result);
    free_tree_link(derivative);
}
