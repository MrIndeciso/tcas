#include <stdlib.h>

#include "tcas.h"
#include "tokenizer.h"
#include "parser.h"
#include "translator.h"
#include "math.h"
#include "debug_util.h"
#include "util.h"
#include "translator_util.h"

TCAS_OP_RESULT evaluate_simple_expr(size_t len, char *expr, TCAS_SETTINGS *settings) {

    size_t count;

    tokenize(len, expr, &count, NULL);

    struct token *tkn = malloc(count * sizeof(struct token));

    tokenize(len, expr, &count, tkn);

    struct graph_link *head = parse(count, tkn, settings->type);

    free(tkn);

    struct expr_tree_head *expr_head = translate_graph(head);

    export_expr_tree_to_xml("op_tree.xml", expr_head);

    struct expr_tree_link *res = math_eval_op(expr_head->head);

    print_val(res->ptr->val);

    return SUCCESS;
}
