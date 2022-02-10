#include <malloc.h>
#include <assert.h>

#include "taylor.h"
#include "derive.h"
#include "math_constants.h"
#include "tree_util.h"
#include "parse_util.h"
#include "taylor_util.h"
#include "mem_util.h"
#include "math.h"

#define TAYLOR_DEBUG

#ifdef TAYLOR_DEBUG
#include "xml.h"
#include "translator_util.h"
#include "simplify.h"

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
#ifdef TAYLOR_DEBUG
    struct expr_tree_head fake_head = (struct expr_tree_head) {.head = series->orig};
    export_expr_tree_to_xml("expand_series_start.xml", &fake_head);
#endif

    int n_grade = series->grade + 1;

    struct expr_tree_link *n_derivative = derive_n_times(series->orig, n_grade);

#ifdef TAYLOR_DEBUG
    fake_head.head = n_derivative;
    export_expr_tree_to_xml("expand_series_n_derivative.xml", &fake_head);
#endif

    struct expr_tree_link *subst = malloc(sizeof(struct expr_tree_link));
    subst->type = VALUE;
    subst->ptr = malloc(sizeof(union expr_tree_ptr));
    subst->ptr->val = series->center;
    recursive_replace_dont_free(n_derivative, sym_x, subst);

#ifdef TAYLOR_DEBUG
    fake_head.head = n_derivative;
    export_expr_tree_to_xml("expand_series_n_deriv_eval.xml", &fake_head);
#endif

    struct expr_tree_link *numerator = math_eval_op(clone_link(n_derivative));

#ifdef TAYLOR_DEBUG
    fake_head.head = numerator;
    export_expr_tree_to_xml("expand_series_numerator.xml", &fake_head);
#endif

    series->grade++;

    if (is_coeff_null(numerator)) {
        printf("Null coeff");
        return expand_series(series);
    } else {
        struct expr_tree_link *denominator = taylor_factorial(n_grade);
        struct expr_tree_link *coeff = parse_double_expr("/ a b", numerator, denominator);
        series->members = realloc(series->members, series->count + 1);

#ifdef TAYLOR_DEBUG
        fake_head.head = denominator;
        export_expr_tree_to_xml("expand_series_factorial.xml", &fake_head);
        fake_head.head = coeff;
        export_expr_tree_to_xml("expand_series_coeff.xml", &fake_head);
#endif

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

#ifdef TAYLOR_DEBUG
        fake_head.head = series->members[series->count];
        export_expr_tree_to_xml("expand_series_new_member.xml", &fake_head);
#endif

        series->members[series->count] = simplify(series->members[series->count]);

#ifdef TAYLOR_DEBUG
        fake_head.head = series->members[series->count];
        export_expr_tree_to_xml("expand_series_new_member_simplified.xml", &fake_head);
#endif

        series->count++;

        return series;
    }
}