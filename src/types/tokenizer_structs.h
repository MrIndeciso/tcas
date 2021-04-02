#ifndef TOKENIZER_STRUCTS_H
#define TOKENIZER_STRUCTS_H

#include <stddef.h>

#define TOKEN_MAX_LENGTH 64

struct token {
	size_t len;
	char token[TOKEN_MAX_LENGTH];
};

#endif
