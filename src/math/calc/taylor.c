#include <malloc.h>
#include <assert.h>

#include "taylor.h"
#include "derive.h"
#include "math_constants.h"
#include "tree_util.h"
#include "parse_util.h"
#include "taylor_util.h"
#include "math.h"

#define TAYLOR_DEBUG

#ifdef TAYLOR_DEBUG
#include "xml.h"
#include "translator_util.h"
#endif

struct taylor_expr *compute_taylor_series(struct expr_tree_link *link, struct expr_tree_val *center)
{
    struct taylor_expr *series = malloc(sizeof(struct taylor_expr));
    series->grade = -1;
    series->is_maclaurin = 0;
    series->count = 0;
    series->members = malloc(sizeof(struct expr_tree_link*));
    series->center = center;
    series->orig = link;

    return expand_series(series);
}

struct taylor_expr *compute_maclaurin_series(struct expr_tree_link *link)
{
    struct taylor_expr *series = malloc(sizeof(struct taylor_expr));
    series->grade = -1;
    series->is_maclaurin = 1;
    series->count = 0;
    series->members = malloc(sizeof(struct expr_tree_link*));
    series->center = zero;
    series->orig = link;

    return expand_series(series);
}

struct taylor_expr *expand_series(struct taylor_expr *series)
{
    int n_grade = series->grade + 1;

    struct expr_tree_link *n_derivative = derive_n_times(series->orig, n_grade);

    struct expr_tree_link *subst = malloc(sizeof(struct expr_tree_link));
    subst->type = VALUE;
    subst->ptr = malloc(sizeof(union expr_tree_ptr));
    subst->ptr->val = series->center;
    recursive_replace(n_derivative, sym_x, subst);

    struct exp

    struct expr_tree_link *numerator = math_eval_op(n_derivative);

    series->grade++;

    if (is_coeff_null(numerator)) {
        printf("Null coeff");
        return expand_series(series);
    } else {
        struct expr_tree_link *denominator = taylor_factorial(n_grade);
        struct expr_tree_link *coeff = parse_double_expr("/ a b", numerator, denominator);
        series->members = realloc(series->members, series->count + 1);

        if (series->is_maclaurin) {
            struct expr_tree_link *power = raise_to_power(sym_x, n_grade);
            struct expr_tree_link *term = parse_double_expr("* a b", coeff, power);
            series->members[series->count] = term;
        } else {
            struct expr_tree_link *base = parse_expr("- x a", subst);
            struct expr_tree_link *power = raise_to_power(base, n_grade);
            struct expr_tree_link *term = parse_double_expr("* a b", coeff, power);
            series->members[series->count] = term;
        }

        series->count++;

        return series;
    }
}