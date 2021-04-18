#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "calc_test.h"

#include "mem_util.h"
#include "test_util.h"
#include "tcas.h"

static struct TCAS_SETTINGS settings = (struct TCAS_SETTINGS){.type = MODE_PN};

void test_calc_ops() {
    test_lim_1();
}

void test_lim_1() {
    char *test = "lim / sin x x 0";
    size_t len = strlen(test);
    struct expr_tree_val *res = evaluate_simple_expr(len, test, settings);
    result(mpfr_cmp_ui(res->val->fp_val, 1) == 0);
    free_tree_val(res);
}
