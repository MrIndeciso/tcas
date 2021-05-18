#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash_test.h"

#include "hash.h"
#include "mem_util.h"
#include "parse_util.h"
#include "test_util.h"
#include "tcas.h"

void test_hash_ops() {
    test_hash_1();
    test_hash_2();
    //test_hash_3();
}

void test_hash_1() {
    char *part1 = "* * 2 3 28";
    char *part2 = "* * * 2 1 3 28";
    struct expr_tree_link *exp1 = parse_expr(part1, NULL);
    struct expr_tree_link *exp2 = parse_expr(part2, NULL);

    result(compare_link_hash(exp1, exp2) != 0);

    free_tree_link(exp1);
    free_tree_link(exp2);
}

void test_hash_2() {
    char *part = "* * * 2 1 3 28";
    struct expr_tree_link *exp = parse_expr(part, NULL);

    result(compare_link_hash(exp, exp) == 0);

    free_tree_link(exp);
}

void test_hash_3() { //Not really sure how this one should go, maybe some sort of sorting before hashing?
    char *part1 = "* 3 2";
    char *part2 = "* 2 3";
    struct expr_tree_link *exp1 = parse_expr(part1, NULL);
    struct expr_tree_link *exp2 = parse_expr(part2, NULL);

    result(compare_link_hash(exp1, exp2) == 0);

    free_tree_link(exp1);
    free_tree_link(exp2);
}
