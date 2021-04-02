#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <stddef.h>

#include "tokenizer_structs.h"

void tokenize(size_t len, char *expr, size_t *count, struct token *tkn);

#endif
