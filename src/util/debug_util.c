#include <gmp.h>
#include <mpfr.h>

#include "debug_util.h"

void print_val(struct expr_tree_val *val) {
    if (val->type == INT) {
        gmp_printf("Value: %.Zd\n", val->val->int_val);
    } else if (val->type == RATIONAL) {
        gmp_printf("Value: %Qx\n", val->val->rational_val);
    } else {
        mpfr_printf("Value: %Re\n", val->val->fp_val);
    }
}
