#ifndef PARSER_STRUCTS_H
#define PARSER_STRUCTS_H

#include <stddef.h>

#include "parser_enums.h"

struct graph_node {
	struct token token;
	size_t children_count;
	struct graph_node **children;
};

#endif
