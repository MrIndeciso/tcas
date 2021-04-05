#include "type_util.h"

#include <assert.h>
#include <gmp.h>

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


}

void optimize_val(struct expr_tree_val *val) {

}
