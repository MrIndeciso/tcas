#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "adv_test.h"

#include "mem_util.h"
#include "test_util.h"
#include "tcas.h"

static struct TCAS_SETTINGS settings = (struct TCAS_SETTINGS){.type = MODE_PN};

void test_adv_ops() {
    test_log_1();
    test_log_2();
    test_log_3();
    test_log_4();
    test_log_5();

    test_pow_1();
    //test_pow_2();

    test_factorial_1();
    test_factorial_2();
}

void test_log_1() {
    char *test = "log10 1000";
    size_t len = strlen(test);
    struct expr_tree_val *res = evaluate_simple_expr(len, test, settings);
    result(mpfr_cmp_ui(res->val->fp_val, 3) == 0);
    free_tree_val(res);
}

void test_log_2() {
    char *test = "log2 log10 100";
    size_t len = strlen(test);
    struct expr_tree_val *res = evaluate_simple_expr(len, test, settings);
    result(mpfr_cmp_ui(res->val->fp_val, 1) == 0);
    free_tree_val(res);
}

void test_log_3() {
    char *test = "ln 1";
    size_t len = strlen(test);
    struct expr_tree_val *res = evaluate_simple_expr(len, test, settings);
    result(mpfr_cmp_ui(res->val->fp_val, 0) == 0);
    free_tree_val(res);
}

void test_log_4() {
    char *test = "+ log2 2 log10 10";
    size_t len = strlen(test);
    struct expr_tree_val *res = evaluate_simple_expr(len, test, settings);
    result(mpfr_cmp_ui(res->val->fp_val, 2) == 0);
    free_tree_val(res);
}

void test_log_5() {
    char *test = "/ log2 + 2 + log2 2 log2 2 log10 / 1000 log10 10000000000";
    size_t len = strlen(test);
    struct expr_tree_val *res = evaluate_simple_expr(len, test, settings);
    result(mpfr_cmp_ui(res->val->fp_val, 1) == 0);
    free_tree_val(res);
}

void test_pow_1() {
    char *test = "exp 0";
    size_t len = strlen(test);
    struct expr_tree_val *res = evaluate_simple_expr(len, test, settings);
    result(mpfr_cmp_ui(res->val->fp_val, 1) == 0);
    free_tree_val(res);
}

void test_pow_2() {
    char *test = "/ exp 2 * exp 1 exp 1";
    size_t len = strlen(test);
    struct expr_tree_val *res = evaluate_simple_expr(len, test, settings);
    result(mpfr_cmp_ui(res->val->fp_val, 1) == 0);
    free_tree_val(res);
}

void test_factorial_1()
{
    char *test = "! 2";
    size_t len = strlen(test);
    struct expr_tree_val *res = evaluate_simple_expr(len, test, settings);
    result(mpz_cmp_ui(res->val->int_val, 2) == 0);
    free_tree_val(res);
}

void test_factorial_2()
{
    char *test = "! 12";
    size_t len = strlen(test);
    struct expr_tree_val *res = evaluate_simple_expr(len, test, settings);
    result(mpz_cmp_ui(res->val->int_val, 479001600) == 0);
    free_tree_val(res);
}
