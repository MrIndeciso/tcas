#include <stdio.h>

#include "tcas.h"

int main() {

    char *testexpr = "+ 8 5";

    evaluate_simple_expr(sizeof(testexpr), testexpr, &(TCAS_SETTINGS){.type = MODE_RPN});

    return 0;
}
