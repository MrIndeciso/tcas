#include <gmp.h>
#include <stdio.h>
#include <string.h>

#include "test_util.h"
#include "mem_util.h"

#include "tcas.h"

//Simple expression evaluation
void test1_1();
void test1_2();
void test1_3();
void test1_4();
void test1_5();

static struct TCAS_SETTINGS settings = (struct TCAS_SETTINGS){.type = MODE_RPN};

int main() {
    test1_1();
    test1_2();
    test1_3();
    test1_4();
    test1_5();

    return 0;
}

void test1_1() {
    char *test = "+ 1216121757 1428420146";
    size_t len = strlen(test);
    struct expr_tree_val *res = evaluate_simple_expr(len, test, settings);
    result(mpz_cmp_ui(res->val->int_val, 2644541903) == 0);
    free_tree_val(res);
}

void test1_2() {
    char *test = "+ 1 + 2 129318239193";
    size_t len = strlen(test);
    struct expr_tree_val *res = evaluate_simple_expr(len, test, settings);
    result(mpz_cmp_si(res->val->int_val, 129318239196) == 0);
    free_tree_val(res);
}

void test1_3() {
    char *test = "+ 1 + 2 -129318239193";
    size_t len = strlen(test);
    struct expr_tree_val *res = evaluate_simple_expr(len, test, settings);
    result(mpz_cmp_si(res->val->int_val, -129318239190) == 0);
    free_tree_val(res);
}

void test1_4() {
    char *test = "+ + + 1 -1 + 1 -1 + 1 -1 + 1 -1";
    size_t len = strlen(test);
    struct expr_tree_val *res = evaluate_simple_expr(len, test, settings);
    result(mpz_cmp_si(res->val->int_val, 0) == 0);
    free_tree_val(res);
}

void test1_5() {
    char *test = "+ 1 1";
    size_t len = strlen(test);
    struct expr_tree_val *res = evaluate_simple_expr(len, test, settings);
    result(mpz_cmp_si(res->val->int_val, 2) == 0);
    free_tree_val(res);
}
