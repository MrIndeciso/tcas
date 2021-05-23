#include <assert.h>
#include <gmp.h>
#include <mpfr.h>

#define SERIES_DEBUG

#include "series.h"
#include "hash.h"
#include "mem_util.h"
#include "mrv.h"
#include "tree_util.h"
#include "parse_util.h"
#include "simplify.h"

#ifdef SERIES_DEBUG
#include "translator_util.h"
#endif

struct expr_tree_link *compute_gruntz_result(struct expr_tree_link *link) {
    //Let's fasthpath sin(w)/w
    if (hash(link).hash == 515396927488) { // / sin w w
        return parse_expr("1", NULL);
    }

    return NULL;
}
