//
// Created by mrindeciso on 09/02/2022.
//

#ifndef TCAS_MATH_CONSTANTS_H
#define TCAS_MATH_CONSTANTS_H

#include "expr_structs.h"

extern struct expr_tree_val *zero;
extern struct expr_tree_val *one;
extern struct expr_tree_val *neg_one;
extern struct expr_tree_link *sym_x;

void init_constants();
void free_constants();

#endif //TCAS_MATH_CONSTANTS_H
