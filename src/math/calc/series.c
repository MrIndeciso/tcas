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

struct expr_tree_link *compute_leadterm(struct expr_tree_link *link) {

}
