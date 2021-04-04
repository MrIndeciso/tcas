#ifndef TCAS_H
#define TCAS_H

#include <stddef.h>

#include "tcas_enums.h"
#include "tcas_structs.h"
#include "expr_structs.h"

struct expr_tree_val* evaluate_simple_expr(size_t len, char *expr, struct TCAS_SETTINGS settings);

#endif
