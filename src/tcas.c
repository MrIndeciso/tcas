#include <stdlib.h>

#include "tcas.h"
#include "tokenizer.h"
#include "parser.h"

TCAS_OP_RESULT evaluate_simple_expr(size_t len, char *expr, TCAS_SETTINGS *settings) {

    size_t count;

    tokenize(len, expr, &count, NULL);

    struct token *tkn = malloc(count * sizeof(struct token));

    tokenize(len, expr, &count, tkn);

    struct graph_link *head = parse(count, tkn, MODE_RPN);

    free(tkn);



    return SUCCESS;
}
