#include <gmp.h>
#include <stdio.h>
#include <string.h>

#include "tcas.h"

int main() {
    char *testexpr = "+ + + + + + 1 2 3 4 5 6";

    evaluate_simple_expr(strlen(testexpr), testexpr, &(TCAS_SETTINGS){.type = MODE_RPN});

    return 0;
}
