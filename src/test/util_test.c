#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util_test.h"
#include "mem_util.h"
#include "test_util.h"
#include "tree_util.h"
#include "hash.h"
#include "simplify.h"
#include "parse_util.h"
#include "translator_util.h"

void test_util_ops() {
    test_parse_1();
    test_parse_2();

    test_simplify_1();
    test_simplify_2();
    test_simplify_3();
    test_simplify_4();
    test_simplify_5();
    test_simplify_6();
    test_simplify_7();
    test_simplify_8();
    test_simplify_9();
    test_simplify_10();
    test_simplify_11();
    test_simplify_12();
    test_simplify_13();
    test_simplify_14();
    test_simplify_15();

    test_sym_replace_1();
}

void test_parse_1() {
    struct expr_tree_link *exp1 = parse_expr("/ 1 3", NULL);
    struct expr_tree_link *exp2 = parse_expr("* 8 4", NULL);
    struct expr_tree_link *exp3 = parse_double_expr("+ a b", exp1, exp2);
    struct expr_tree_link *final = parse_expr("+ / 1 3 * 8 4", NULL);
    result(compare_links(exp3, final) == 0);
    free_tree_link(exp1);
    free_tree_link(exp2);
    free_tree_link(exp3);
    free_tree_link(final);
}

void test_parse_2() {
    struct expr_tree_link *exp1 = parse_expr("/ 1 3", NULL);
    struct expr_tree_link *exp2 = parse_expr("+ 3 a", exp1);
    struct expr_tree_link *final = parse_expr("+ 3 / 1 3", NULL);

    result(compare_link_hash(exp2, final) == 0);
    free_tree_link(exp1);
    free_tree_link(exp2);
    free_tree_link(final);
}

void test_simplify_1() {
    struct expr_tree_link *exp1 = parse_expr("+ 1 ln exp x", NULL);
    struct expr_tree_link *exp2 = parse_expr("+ 1 x", NULL);
    struct expr_tree_link *simplified = simplify(exp1);

    result(compare_links(exp2, simplified) == 0);

    free_tree_link(exp1);
    free_tree_link(exp2);
}

void test_simplify_2() {
    struct expr_tree_link *exp1 = parse_expr("+ 1 / 1 / 1 x", NULL);
    struct expr_tree_link *exp2 = parse_expr("+ 1 x", NULL);
    struct expr_tree_link *simplified = simplify(exp1);

    result(compare_links(exp2, simplified) == 0);

    free_tree_link(exp1);
    free_tree_link(exp2);
}

void test_simplify_3() {
    struct expr_tree_link *exp1 = parse_expr("+ 1 exp ln x", NULL);
    struct expr_tree_link *exp2 = parse_expr("+ 1 x", NULL);
    struct expr_tree_link *simplified = simplify(exp1);

    result(compare_links(exp2, simplified) == 0);

    free_tree_link(exp1);
    free_tree_link(exp2);
}

void test_simplify_4() {
    struct expr_tree_link *exp1 = parse_expr("+ exp x ln exp x", NULL);
    struct expr_tree_link *exp2 = parse_expr("+ exp x x", NULL);
    struct expr_tree_link *simplified = simplify(exp1);

    result(compare_links(exp2, simplified) == 0);

    free_tree_link(exp1);
    free_tree_link(exp2);
}

void test_simplify_5() {
    struct expr_tree_link *exp1 = parse_expr("/ 2 exp x", NULL);
    struct expr_tree_link *exp2 = parse_expr("* 2 exp -x", NULL);
    struct expr_tree_link *simplified = simplify(exp1);

    result(compare_links(exp2, simplified) == 0);

    struct expr_tree_head fake_head = (struct expr_tree_head) {.head = exp2};
    export_expr_tree_to_xml("exp2.xml", &fake_head);
    fake_head.head = simplified;
    export_expr_tree_to_xml("final.xml", &fake_head);

    free_tree_link(exp1);
    free_tree_link(exp2);
}

void test_simplify_6() {
    struct expr_tree_link *exp1 = parse_expr("/ 3 exp - 8 4", NULL);
    struct expr_tree_link *exp2 = parse_expr("* 3 exp - 4 8", NULL);
    struct expr_tree_link *simplified = simplify(exp1);

    result(compare_links(exp2, simplified) == 0);

    struct expr_tree_head fake_head = (struct expr_tree_head) {.head = exp2};
    export_expr_tree_to_xml("exp2.xml", &fake_head);
    fake_head.head = simplified;
    export_expr_tree_to_xml("final.xml", &fake_head);

    free_tree_link(exp1);
    free_tree_link(exp2);
}

void test_simplify_7() {
    struct expr_tree_link *exp1 = parse_expr("+ 3 * 1 x", NULL);
    struct expr_tree_link *exp2 = parse_expr("+ 3 x", NULL);
    struct expr_tree_link *simplified = simplify(exp1);

    result(compare_links(exp2, simplified) == 0);

    free_tree_link(exp1);
    free_tree_link(exp2);
}

void test_simplify_8() {
    struct expr_tree_link *exp1 = parse_expr("+ 3 / x 1", NULL);
    struct expr_tree_link *exp2 = parse_expr("+ 3 x", NULL);
    struct expr_tree_link *simplified = simplify(exp1);

    result(compare_links(exp2, simplified) == 0);

    free_tree_link(exp1);
    free_tree_link(exp2);
}

void test_simplify_9() {
    struct expr_tree_link *exp1 = parse_expr("* 1 x", NULL);
    struct expr_tree_link *exp2 = parse_expr("x", NULL);
    struct expr_tree_link *simplified = simplify(clone_link(exp1));

    result(compare_links(exp2, simplified) == 0);

    free_tree_link(exp1);
    free_tree_link(exp2);
}

void test_simplify_10() {
    struct expr_tree_link *exp1 = parse_expr("* x 1", NULL);
    struct expr_tree_link *exp2 = parse_expr("x", NULL);
    struct expr_tree_link *simplified = simplify(clone_link(exp1));

    result(compare_links(exp2, simplified) == 0);

    free_tree_link(exp1);
    free_tree_link(exp2);
}

void test_simplify_11() {
    struct expr_tree_link *exp1 = parse_expr("* x / 1 3", NULL);
    struct expr_tree_link *exp2 = parse_expr("/ x 3", NULL);
    struct expr_tree_link *simplified = simplify(clone_link(exp1));

    result(compare_links(exp2, simplified) == 0);

    free_tree_link(exp1);
    free_tree_link(exp2);
}

void test_simplify_12() {
    struct expr_tree_link *exp1 = parse_expr("* sin w / 1 w", NULL);
    struct expr_tree_link *exp2 = parse_expr("/ sin w w", NULL);
    struct expr_tree_link *simplified = simplify(clone_link(exp1));

    result(compare_links(exp2, simplified) == 0);

    free_tree_link(exp1);
    free_tree_link(exp2);
}

void test_simplify_13() {
    struct expr_tree_link *exp1 = parse_expr("+ * x 1 * 1 x", NULL);
    struct expr_tree_link *exp2 = parse_expr("+ x x", NULL);
    struct expr_tree_link *simplified = simplify(clone_link(exp1));

    result(compare_links(exp2, simplified) == 0);

    free_tree_link(exp1);
    free_tree_link(exp2);
}

void test_simplify_14() {
    struct expr_tree_link *exp1 = parse_expr("** x 1", NULL);
    struct expr_tree_link *exp2 = parse_expr("x", NULL);
    struct expr_tree_link *simplified = simplify(clone_link(exp1));

    result(compare_links(exp2, simplified) == 0);

    free_tree_link(exp1);
    free_tree_link(exp2);
}

void test_simplify_15() {
    struct expr_tree_link *exp1 = parse_expr("** x 0", NULL);
    struct expr_tree_link *exp2 = parse_expr("1", NULL);
    struct expr_tree_link *simplified = simplify(clone_link(exp1));

    result(compare_links(exp2, simplified) == 0);

    free_tree_link(exp1);
    free_tree_link(exp2);
}

void test_sym_replace_1() {
    struct expr_tree_link *expr = parse_expr("/ sin x x", NULL);
    struct expr_tree_link *result = parse_expr("/ sin exp x exp x", NULL);
    struct expr_tree_link *newsym = parse_expr("exp x", NULL);
    struct expr_tree_link *sym = parse_expr("x", NULL);
    recursive_sym_replace(expr, sym, newsym);

    result(compare_links(expr, result) == 0);

    free_tree_link(expr);
    free_tree_link(result);
    free_tree_link(newsym);
    free_tree_link(sym);
}
