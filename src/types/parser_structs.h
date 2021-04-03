#ifndef PARSER_STRUCTS_H
#define PARSER_STRUCTS_H

#include <stddef.h>

#include "parser_enums.h"
#include "tokenizer_structs.h"

struct graph_node {
	struct token token;
	size_t children_count;
	struct graph_node **children;
};

struct graph_intermediate {
	char content[64];
	size_t children_count;
	struct graph_intermediate **children;
};

union graph_linked_ptr {
	struct graph_operator *op;
	struct graph_value *value;
};

struct graph_link {
	enum LINKED_TYPE type;
	union graph_linked_ptr *ptr;
};

struct graph_operator {
	enum OPERATOR_TYPE type;
	size_t children_count;
	struct graph_link **children;
};

struct graph_value {
	char content[64];
};

#endif
