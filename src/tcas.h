#ifndef TCAS_H
#define TCAS_H

#include <stddef.h>

#include "tcas_enums.h"
#include "tcas_structs.h"

TCAS_OP_RESULT evaluate_simple_expr(size_t len, char *expr, TCAS_SETTINGS *settings);

#endif
