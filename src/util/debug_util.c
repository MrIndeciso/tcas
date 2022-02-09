#include <gmp.h>
#include <mpfr.h>

#include "debug_util.h"

void print_val(struct expr_tree_val *val) {
    if (val->type == INT) {
        gmp_printf("Int value: %.Zd\n", val->val->int_val);
    } else if (val->type == RATIONAL) {
        gmp_printf("Rational value: %Qx\n", val->val->rational_val);
    } else {
        mpfr_printf("FP value: %Re\n", val->val->fp_val);
    }
}
