#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tcas.h"
#include "mem_util.h"
#include "debug_util.h"

static struct TCAS_SETTINGS settings = (struct TCAS_SETTINGS){.type = MODE_PN};

int main() {

    char *test = "/ exp 2 * exp 1 exp 1";

    size_t len = strlen(test);
    struct expr_tree_val *res = evaluate_simple_expr(len, test, settings);
    print_val(res);

    free_tree_val(res);

    return 0;
}
