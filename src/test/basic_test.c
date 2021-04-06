#include "basic_test.h"

#include <stdlib.h>
#include <string.h>

#include "mem_util.h"
#include "test_util.h"
#include "tcas.h"

static struct TCAS_SETTINGS settings = (struct TCAS_SETTINGS){.type = MODE_RPN};

void test_basic_ops() {
    test_plus_1();
    test_plus_2();
    test_plus_3();
    test_plus_4();
    test_plus_5();

    test_minus_1();
    test_minus_2();
    test_minus_3();
    test_minus_4();
    test_minus_5();

    test_times_1();
    test_times_2();
    test_times_3();
    test_times_4();
    test_times_5();

    test_divide_1();
    test_divide_2();
    test_divide_3();
    test_divide_4();
    test_divide_5();

    test_basic_all_1();
    test_basic_all_2();
}

void test_plus_1() {
    char *test = "+ 1216121757 1428420146";
    size_t len = strlen(test);
    struct expr_tree_val *res = evaluate_simple_expr(len, test, settings);
    result(mpz_cmp_ui(res->val->int_val, 2644541903) == 0);
    free_tree_val(res);
}

void test_plus_2() {
    char *test = "+ 1 + 2 129318239193";
    size_t len = strlen(test);
    struct expr_tree_val *res = evaluate_simple_expr(len, test, settings);
    result(mpz_cmp_si(res->val->int_val, 129318239196) == 0);
    free_tree_val(res);
}

void test_plus_3() {
    char *test = "+ 1 + 2 -129318239193";
    size_t len = strlen(test);
    struct expr_tree_val *res = evaluate_simple_expr(len, test, settings);
    result(mpz_cmp_si(res->val->int_val, -129318239190) == 0);
    free_tree_val(res);
}

void test_plus_4() {
    char *test = "+ + + 1 -1 + 1 -1 + + 1 -1 + 1 -1";
    size_t len = strlen(test);
    struct expr_tree_val *res = evaluate_simple_expr(len, test, settings);
    result(mpz_cmp_si(res->val->int_val, 0) == 0);
    free_tree_val(res);
}

void test_plus_5() {
    char *test = "+ 1 1";
    size_t len = strlen(test);
    struct expr_tree_val *res = evaluate_simple_expr(len, test, settings);
    result(mpz_cmp_si(res->val->int_val, 2) == 0);
    free_tree_val(res);
}

void test_minus_1() {
    char *test = "- 1216121757 1428420146";
    size_t len = strlen(test);
    struct expr_tree_val *res = evaluate_simple_expr(len, test, settings);
    result(mpz_cmp_si(res->val->int_val, -212298389) == 0);
    free_tree_val(res);
}

void test_minus_2() {
    char *test = "- 1 - 2 129318239193";
    size_t len = strlen(test);
    struct expr_tree_val *res = evaluate_simple_expr(len, test, settings);
    result(mpz_cmp_ui(res->val->int_val, 129318239192) == 0);
    free_tree_val(res);
}

void test_minus_3() {
    char *test = "- 1 - 2 -129318239193";
    size_t len = strlen(test);
    struct expr_tree_val *res = evaluate_simple_expr(len, test, settings);
    result(mpz_cmp_si(res->val->int_val, -129318239194) == 0);
    free_tree_val(res);
}

void test_minus_4() {
    char *test = "- - - 1 -1 - 1 -1 - - 1 -1 - 1 -1";
    size_t len = strlen(test);
    struct expr_tree_val *res = evaluate_simple_expr(len, test, settings);
    result(mpz_cmp_si(res->val->int_val, 0) == 0);
    free_tree_val(res);
}

void test_minus_5() {
    char *test = "- 1 1";
    size_t len = strlen(test);
    struct expr_tree_val *res = evaluate_simple_expr(len, test, settings);
    result(mpz_cmp_si(res->val->int_val, 0) == 0);
    free_tree_val(res);
}

void test_times_1() {
    char *test = "* 1216121757 1428420146";
    size_t len = strlen(test);
    struct expr_tree_val *res = evaluate_simple_expr(len, test, settings);
    result(mpz_cmp_ui(res->val->int_val, 1737132817687716522) == 0);
    free_tree_val(res);
}

void test_times_2() {
    char *test = "* 1 * 2 129318239193";
    size_t len = strlen(test);
    struct expr_tree_val *res = evaluate_simple_expr(len, test, settings);
    result(mpz_cmp_si(res->val->int_val, 258636478386) == 0);
    free_tree_val(res);
}

void test_times_3() {
    char *test = "* 1 * 2 -129318239193";
    size_t len = strlen(test);
    struct expr_tree_val *res = evaluate_simple_expr(len, test, settings);
    result(mpz_cmp_si(res->val->int_val, -258636478386) == 0);
    free_tree_val(res);
}

void test_times_4() {
    char *test = "* * * 1 -1 * 1 -1 * * 1 -1 * 1 -1";
    size_t len = strlen(test);
    struct expr_tree_val *res = evaluate_simple_expr(len, test, settings);
    result(mpz_cmp_si(res->val->int_val, 1) == 0);
    free_tree_val(res);
}

void test_times_5() {
    char *test = "* 1 1";
    size_t len = strlen(test);
    struct expr_tree_val *res = evaluate_simple_expr(len, test, settings);
    result(mpz_cmp_si(res->val->int_val, 1) == 0);
    free_tree_val(res);
}

void test_divide_1() {
    char *test = "/ 1216121757 1428420146";
    size_t len = strlen(test);
    struct expr_tree_val *res = evaluate_simple_expr(len, test, settings);
    result(mpq_cmp_ui(res->val->rational_val, 1216121757, 1428420146) == 0);
    free_tree_val(res);
}

void test_divide_2() {
    char *test = "/ 1 / 2 129318239193";
    size_t len = strlen(test);
    struct expr_tree_val *res = evaluate_simple_expr(len, test, settings);
    result(mpq_cmp_ui(res->val->rational_val, 129318239193, 2) == 0);
    free_tree_val(res);
}

void test_divide_3() {
    char *test = "/ 1 / 2 -129318239193";
    size_t len = strlen(test);
    struct expr_tree_val *res = evaluate_simple_expr(len, test, settings);
    result(mpq_cmp_si(res->val->rational_val, -129318239193, 2) == 0);
    free_tree_val(res);
}

void test_divide_4() {
    char *test = "/ / / 1 -1 / 1 -1 / / 1 -1 / 1 -1";
    size_t len = strlen(test);
    struct expr_tree_val *res = evaluate_simple_expr(len, test, settings);
    result(mpq_cmp_si(res->val->rational_val, 1, 1) == 0);
    free_tree_val(res);
}

void test_divide_5() {
    char *test = "/ 1 1";
    size_t len = strlen(test);
    struct expr_tree_val *res = evaluate_simple_expr(len, test, settings);
    result(mpq_cmp_ui(res->val->rational_val, 1, 1) == 0);
    free_tree_val(res);
}

void test_basic_all_1() {
    char *test = "* + - + 23 * 7 8 * 5 -27 52 * * 2 2 + 1 3";
    size_t len = strlen(test);
    struct expr_tree_val *res = evaluate_simple_expr(len, test, settings);
    result(mpz_cmp_si(res->val->int_val, 4256) == 0);
    free_tree_val(res);
}

void test_basic_all_2() {
    char *test = "/ * + - + 23 * 7 8 * 5 -27 52 * * 2 2 + 1 3 + * 28 - 7 / 7 8 * 29 + 2 3";
    size_t len = strlen(test);
    struct expr_tree_val *res = evaluate_simple_expr(len, test, settings);
    result(mpq_cmp_si(res->val->rational_val, 8512, 633) == 0);
    free_tree_val(res);
}
