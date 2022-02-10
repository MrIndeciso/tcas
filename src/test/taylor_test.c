#include <stdio.h>
#include <stdlib.h>

#include "taylor_test.h"

#include "parse_util.h"
#include "taylor.h"
#include "taylor_util.h"
#include "test_util.h"
#include "mem_util.h"
#include "hash.h"

void test_taylor_ops()
{
    test_taylor_1();
    test_taylor_2();
}

void test_taylor_1()
{
    struct expr_tree_link *input = parse_expr("exp x", NULL);
    struct taylor_expr *result = compute_maclaurin_series(input);
    struct expr_tree_link *expected = parse_expr("1", NULL);

    result(compare_link_hash(result->members[0], expected) == 0);

    free_tree_link(expected);
    free_taylor_expr(result);
}

void test_taylor_2()
{
    struct expr_tree_link *input = parse_expr("exp x", NULL);
    struct taylor_expr *result = compute_maclaurin_series(input);
    result = expand_series(result);
    result = expand_series(result);
    struct expr_tree_link *expected1 = parse_expr("1", NULL);
    struct expr_tree_link *expected2 = parse_expr("x", NULL);
    struct expr_tree_link *expected3 = parse_expr("/ ** x 2 2", NULL);

    result(compare_link_hash(result->members[0], expected1) == 0
            && compare_link_hash(result->members[1], expected2) == 0
            && compare_link_hash(result->members[2], expected3) == 0);

    free_tree_link(expected1);
    free_tree_link(expected2);
    free_taylor_expr(result);
}