#include <gmp.h>
#include <stdio.h>
#include <string.h>

#include "adv_test.h"
#include "basic_test.h"
#include "calc_test.h"
#include "derive_test.h"
#include "hash_test.h"
#include "util_test.h"
#include "taylor_test.h"
#include "tcas.h"

int main() {
    init_tcas();

    //test_basic_ops();
    //test_adv_ops();
    //test_calc_ops();
    //test_hash_ops();
    //test_util_ops();
    //test_derive_ops();
    test_taylor_ops();

    free_tcas();

    return 0;
}


