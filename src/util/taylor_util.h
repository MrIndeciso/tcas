//
// Created by mrindeciso on 09/02/2022.
//

#ifndef TCAS_TAYLOR_UTIL_H
#define TCAS_TAYLOR_UTIL_H

#include "taylor.h"
#include "expr_structs.h"

void free_taylor_expr(struct taylor_expr *expr);

int is_coeff_null(struct expr_tree_link *coeff);

struct expr_tree_link *taylor_factorial(int grade);

struct expr_tree_link *raise_to_power(struct expr_tree_link *arg, int power);

#endif //TCAS_TAYLOR_UTIL_H
