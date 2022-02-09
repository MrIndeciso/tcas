#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "derive_test.h"

#include "mem_util.h"
#include "test_util.h"
#include "derive.h"
#include "simplify.h"
#include "parse_util.h"
#include "hash.h"

void test_derive_ops() {
    test_derive_1();
    test_derive_2();
    test_derive_3();
    test_derive_4();
    test_derive_5();
    test_derive_6();
    test_derive_7();
    test_derive_8();
    test_derive_9();
    test_derive_10();
    test_derive_11();
    test_derive_12();
    test_derive_13();
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
    struct expr_tree_link *simplified = parse_expr("+ x x", NULL);
    struct expr_tree_link *derivative = derive(test);
    struct expr_tree_link *simplified_d = simplify(derivative);

    result(compare_link_hash(simplified_d, simplified) == 0);

    free_tree_link(test);
    free_tree_link(result);
    free_tree_link(simplified);
    //free_tree_link(derivative);
    free_tree_link(simplified_d);
}

void test_derive_6() {
    struct expr_tree_link *test = parse_expr("/ x x", NULL);
    struct expr_tree_link *result = parse_expr("/ - * 1 x * x 1 ^ x 2", NULL);
    struct expr_tree_link *derivative = derive(test);

    result(compare_link_hash(result, derivative) == 0);

    free_tree_link(test);
    free_tree_link(result);
    free_tree_link(derivative);
}

void test_derive_7() {
    struct expr_tree_link *test = parse_expr("sqrt x", NULL);
    struct expr_tree_link *result = parse_expr("/ * -1 1 * 2 sqrt x", NULL);
    struct expr_tree_link *derivative = derive(test);

    result(compare_link_hash(result, derivative) == 0);

    free_tree_link(test);
    free_tree_link(result);
    free_tree_link(derivative);
}

void test_derive_8() {
    struct expr_tree_link *test = parse_expr("sin x", NULL);
    struct expr_tree_link *result = parse_expr("* cos x 1", NULL);
    struct expr_tree_link *derivative = derive(test);

    result(compare_link_hash(result, derivative) == 0);

    free_tree_link(test);
    free_tree_link(result);
    free_tree_link(derivative);
}

void test_derive_9() {
    struct expr_tree_link *test = parse_expr("cos x", NULL);
    struct expr_tree_link *result = parse_expr("* - 0 sin x 1", NULL);
    struct expr_tree_link *derivative = derive(test);

    result(compare_link_hash(result, derivative) == 0);

    free_tree_link(test);
    free_tree_link(result);
    free_tree_link(derivative);
}

void test_derive_10() {
    struct expr_tree_link *test = parse_expr("exp sin x", NULL);
    struct expr_tree_link *result = parse_expr("* exp sin x * cos x 1", NULL);
    struct expr_tree_link *derivative = derive(test);

    result(compare_link_hash(result, derivative) == 0);

    free_tree_link(test);
    free_tree_link(result);
    free_tree_link(derivative);
}

void test_derive_11() {
    struct expr_tree_link *test = parse_expr("exp cos sin x", NULL);
    struct expr_tree_link *result = parse_expr("* exp cos sin x * - 0 sin sin x * cos x 1", NULL);
    struct expr_tree_link *derivative = derive(test);

    result(compare_link_hash(result, derivative) == 0);

    free_tree_link(test);
    free_tree_link(result);
    free_tree_link(derivative);
}

void test_derive_12() {
    struct expr_tree_link *test = parse_expr("exp x", NULL);
    struct expr_tree_link *result = parse_expr("exp x", NULL);
    struct expr_tree_link *derivative = derive_n_times(test, 5);

    result(compare_link_hash(result, derivative) == 0);

    free_tree_link(test);
    free_tree_link(result);
    free_tree_link(derivative);
}

void test_derive_13() {
    struct expr_tree_link *test = parse_expr("* x x", NULL);
    struct expr_tree_link *result = parse_expr("+ 1 1", NULL);
    struct expr_tree_link *derivative = derive_n_times(test, 2);

    result(compare_link_hash(result, derivative) == 0);

    free_tree_link(test);
    free_tree_link(result);
    free_tree_link(derivative);
}
