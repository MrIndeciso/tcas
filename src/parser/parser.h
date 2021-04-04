#ifndef PARSER_H
#define PARSER_H

#include <stddef.h>

#include "tokenizer_structs.h"
#include "parser_structs.h"

struct graph_link* parse(size_t len, struct token *tkn, enum PARSER_MODE mode);

#endif
