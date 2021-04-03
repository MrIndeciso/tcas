#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include "../types/parser_structs.h"
#include "../types/expr_structs.h"

struct expr_tree_head* translate_graph(struct graph_link *head);

#endif
