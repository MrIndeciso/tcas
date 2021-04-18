#include <gmp.h>
#include <stdio.h>
#include <string.h>

#include "basic_test.h"
#include "adv_test.h"
#include "calc_test.h"

int main() {
    test_basic_ops();
    test_adv_ops();
    test_calc_ops();

    return 0;
}


