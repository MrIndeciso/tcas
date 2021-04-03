#include <stdlib.h>

#include "rpn_parser.h"

static struct graph_node* tokens_to_basic_graph(size_t size, struct token *tkn);

struct graph_node* rpn_parse(size_t len, struct token *tkn) {
	struct graph_node *basic_graph = tokens_to_basic_graph(len, tkn);
}

static struct graph_node* tokens_to_basic_graph(size_t size, struct token *tkn) {
	struct graph_node *head = malloc(sizeof(struct graph_node));
	head->token = tkn[0];
	head->children_count = 1;
	head->children = malloc(sizeof(struct graph_node*));

	struct graph_node *node = malloc(sizeof(struct graph_node));
	
	head->children[0] = node;

	for (int i = 1; i < size; i++) {
		node->token = tkn[i];
		node->children_count = 1;
		node->children = malloc(sizeof(struct graph_node*));
		struct graph_node *next = malloc(sizeof(struct graph_node));
		node->children[0] = next;

		node = next;
	}

	return head;
}


