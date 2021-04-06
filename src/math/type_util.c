#include "type_util.h"

#include <assert.h>
#include <gmp.h>
#include <mpfr.h>

void make_rational(struct expr_tree_val *val) {
    if (val->type == RATIONAL)
        return;

    assert(val->type != FLOAT); //Can't turn a float back to rational

    mpz_t int_val;
    mpz_init_set(int_val, val->val->int_val);

    mpz_clear(val->val->int_val);

    mpq_init(val->val->rational_val);

    val->type = RATIONAL;

    mpz_set(mpq_numref(val->val->rational_val), int_val);

    mpz_clear(int_val);
}

void make_float(struct expr_tree_val *val) {
    if (val->type == FLOAT)
        return;

    if (val->type == RATIONAL) {
        mpq_t rational_val;
        mpq_init(rational_val);
        mpq_set(rational_val, val->val->rational_val);

        mpq_clear(val->val->rational_val);

        mpfr_init_set_q(val->val->fp_val, rational_val, MPFR_ROUNDING);

        mpq_clear(rational_val);
    } else { //Int
        mpz_t int_val;
        mpz_init(int_val);
        mpz_set(int_val, val->val->int_val);

        mpz_clear(val->val->int_val);

        mpfr_init_set_z(val->val->fp_val, int_val, MPFR_ROUNDING);

        mpz_clear(int_val);
    }

    val->type = FLOAT;
}

void optimize_val(struct expr_tree_val *val) {

}
