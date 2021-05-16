#include <stdlib.h>
#include <string.h>

#include "parse_util.h"
#include "tokenizer.h"
#include "parser.h"
#include "translator.h"
#include "mem_util.h"
#include "tree_util.h"

static struct expr_tree_link *find = &(struct expr_tree_link){
    .type = SYMBOL,
    .ptr = &(union expr_tree_ptr) {
        .sym = &(struct expr_tree_sym){
            .sign = 1,
            .representation = 'y'
        }
    }
};

struct expr_tree_link* parse_expr(char *expr, struct expr_tree_link *subst) {
    size_t count;
    tokenize(strlen(expr), expr, &count, NULL);
    struct token *tkn = malloc(count * sizeof(struct token));
    tokenize(strlen(expr), expr, &count, tkn);
    struct graph_link *head = parse(count, tkn, MODE_PN);
    free(tkn);
    struct expr_tree_head *expr_head = translate_graph(head);
    recursive_replace(expr_head->head, find, subst);
    return expr_head->head;
}
