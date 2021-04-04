#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rpn_parser.h"
#include "rpn_defs.h"

static int pointer_pos = 0;

static struct graph_link* parse_token(struct token *tkn);

struct graph_link* rpn_parse(size_t len, struct token *tkn) {
    pointer_pos = 0;
    return parse_token(tkn);
}

static struct graph_link* parse_token(struct token *tkn) {
    struct graph_link *link = malloc(sizeof(struct graph_link));
    link->ptr = malloc(sizeof(union graph_linked_ptr));

    if (op_from_token(tkn[pointer_pos].token) != UNKNOWN) {
        link->type = OPERATOR;
        link->ptr->op = malloc(sizeof(struct graph_operator));
        link->ptr->op->type = op_from_token(tkn[pointer_pos].token);
        link->ptr->op->children_count = op_arg_count(link->ptr->op->type);
        link->ptr->op->children = malloc(link->ptr->op->children_count * sizeof(struct graph_link*));
        for (unsigned long i = 0; i < link->ptr->op->children_count; i++) {
            pointer_pos++;
            link->ptr->op->children[i] = parse_token(tkn);
        }
    } else {
        link->type = VALUE;
        link->ptr->value = malloc(sizeof(struct graph_value));
        strncpy(link->ptr->value->content, tkn[pointer_pos].token, TOKEN_MAX_LENGTH);
    }

    return link;
}


