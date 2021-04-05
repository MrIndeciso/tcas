#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tcas.h"
#include "mem_util.h"
#include "debug_util.h"

static struct TCAS_SETTINGS settings = (struct TCAS_SETTINGS){.type = MODE_RPN};

int main() {

    char *test = "+ 1 / 3 3";

    //std 2 + (5 * 3)
    //pn + 2 * 5 3
    //rpn 5 3 * 2 +

    size_t len = strlen(test);
    struct expr_tree_val *res = evaluate_simple_expr(len, test, settings);
    print_val(res);

    //result(mpz_cmp_ui(res->val->int_val, 2644541903) == 0);
    free_tree_val(res);

    return 0;
}
