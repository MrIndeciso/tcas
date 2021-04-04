#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include "parser_structs.h"
#include "expr_structs.h"

struct expr_tree_head* translate_graph(struct graph_link *head);

#endif
