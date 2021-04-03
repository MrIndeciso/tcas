#ifndef RPN_PARSER_H
#define RPN_PARSER_H

#include <stddef.h>

#include "../types/tokenizer_structs.h"
#include "../types/parser_structs.h"

struct graph_link* rpn_parse(size_t len, struct token *tkn);

#endif
