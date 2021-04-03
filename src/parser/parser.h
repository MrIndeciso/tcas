#ifndef PARSER_H
#define PARSER_H

#include <stddef.h>

#include "../types/tokenizer_structs.h"
#include "../types/parser_structs.h"

struct graph_node* parse(size_t len, struct token *tkn, enum PARSER_MODE mode);

#endif
