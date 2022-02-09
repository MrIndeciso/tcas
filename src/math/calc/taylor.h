#ifndef TAYLOR_H
#define TAYLOR_H

struct taylor_expr {
    int grade;
    int is_maclaurin;
    int count;
    struct expr_tree_link **members;
    struct expr_tree_val *center;
    struct expr_tree_link *orig;
};

struct taylor_expr *compute_taylor_series(struct expr_tree_link *link, struct expr_tree_val *center);

struct taylor_expr *compute_maclaurin_series(struct expr_tree_link *link);

struct taylor_expr *expand_series(struct taylor_expr *series);

#endif // TAYLOR_H
