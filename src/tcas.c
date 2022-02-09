#include <stdlib.h>

#include "tcas.h"
#include "tokenizer.h"
#include "parser.h"
#include "translator.h"
#include "math.h"
#include "math_constants.h"
#include "debug_util.h"
#include "util.h"
#include "mem_util.h"
#include "translator_util.h"

void init_tcas()
{
    init_constants();
}

struct expr_tree_val* evaluate_simple_expr(size_t len, char *expr, struct TCAS_SETTINGS settings) {
    size_t count;

    tokenize(len, expr, &count, NULL);

    struct token *tkn = malloc(count * sizeof(struct token));

    tokenize(len, expr, &count, tkn);

    struct graph_link *head = parse(count, tkn, settings.type);

    //export_adv_graph_to_xml("graph.xml", head);

    free(tkn);

    struct expr_tree_head *expr_head = translate_graph(head);

    //export_expr_tree_to_xml("op_tree.xml", expr_head);

    struct expr_tree_link *res = math_eval_op(expr_head->head);

    struct expr_tree_val *val = res->ptr->val;

    free(res);

    return val;
}

void free_tcas()
{
    free_constants();
}