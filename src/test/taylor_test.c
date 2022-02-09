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
}

void test_taylor_1()
{
    struct expr_tree_link *input = parse_expr("sin x", NULL);
    struct taylor_expr *result = compute_maclaurin_series(input);
    struct expr_tree_link *expected = parse_expr("x", NULL);

    result(compare_link_hash(result->members[0], expected) == 0);

    free_tree_link(expected);
    free_taylor_expr(result);
}