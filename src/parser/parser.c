#include "parser.h"

#include "rpn_parser.h"

struct graph_link* parse(size_t len, struct token *tkn, enum PARSER_MODE mode) {
    switch (mode) {
        case MODE_PN:
            return rpn_parse(len, tkn);
        default:
            return NULL;
    }
}
