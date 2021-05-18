#include <gmp.h>
#include <stdio.h>
#include <string.h>

#include "adv_test.h"
#include "basic_test.h"
#include "calc_test.h"
#include "hash_test.h"
#include "util_test.h"

int main() {
    test_basic_ops();
    test_adv_ops();
    //test_calc_ops();
    test_hash_ops();
    test_util_ops();

    return 0;
}


