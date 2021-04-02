#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "parser.h"
#include "util.h"

int test1();

int main() {
	int return_value = 0;
	return_value += test1();
	return return_value;
}

//graph to XML export test
int test1() {
	struct graph_node head, child1, child2, child3, child2_1, child2_2;
	head.token = (struct token) {.len = 2, .token = "ab"};
	child1.token = (struct token) {.len = 1, .token = "a"};
	child2.token = (struct token) {.len = 9, .token = "Provolone"};
	child3.token = (struct token) {.len = 1, .token = "b"};
	child2_1.token = (struct token) {.len = 4, .token = "1234"};
	child2_2.token = (struct token) {.len = 3, .token = "abc"};

	head.children_count = 3;
	head.children = malloc(3 * sizeof(struct graph_node*));
	head.children[0] = &child1;
	head.children[1] = &child2;
	head.children[2] = &child3;

	child1.children_count = 0;
	child1.children = NULL;

	child3.children_count = 0;
	child3.children = NULL;

	child2.children_count = 2;
	child2.children = malloc(2 * sizeof(struct graph_node*));
	child2.children[0] = &child2_1;
	child2.children[1] = &child2_2;

	child2_1.children_count = 0;
	child2_1.children = NULL;

	child2_2.children_count = 0;
	child2_2.children = NULL;

	export_graph_to_xml("test1.xml", &head);

	return 0;
}
