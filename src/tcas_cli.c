#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tcas.h"
#include "mem_util.h"
#include "debug_util.h"

static struct TCAS_SETTINGS settings = (struct TCAS_SETTINGS){.type = MODE_PN};

int main() {

    //char *test = "lim / * - ln + ln x ln ln x ln ln x ln x ln + ln x ln ln ln x x +infinity";
    //char *test = "lim / * - ln + ln exp x ln ln exp x ln ln exp x ln exp x ln + ln exp x ln ln ln exp x x +infinity";
    //char *test = "lim / * - ln + x ln x ln x x ln + x ln ln x x +infinity";
    //char *test = "lim - ln ln + * x exp * x exp x 1 exp exp + ln ln x / 1 x x +infinity";
    //char *test = "lim / sin x x x 0";

    char *test = "lim * / - ln + ln x ln ln x ln ln x ln + ln x ln ln ln x ln x x +infinity";

    size_t len = strlen(test);
    struct expr_tree_val *res = evaluate_simple_expr(len, test, settings);
    print_val(res);

    free_tree_val(res);

    return 0;
}
