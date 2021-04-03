#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../tokenizer/tokenizer.h"
#include "../parser/rpn_parser.h"
#include "../parser/util.h"
#include "translator_util.h"
#include "translator.h"

int test1();

int main() {
	int return_value = 0;
	return_value += test1();
	return return_value;
}

int test1() {
	char *expr = "+ * - 8 4 + 5 2 7";
	size_t len = strlen(expr), count;

	tokenize(len, expr, &count, NULL);

	struct token *tkn = malloc(count * sizeof(struct token));

	tokenize(len, expr, &count, tkn);

	struct graph_link *head = rpn_parse(count, tkn);

	//export_adv_graph_to_xml("test1.xml", head);

	struct expr_tree_head *expr_head = translate_graph(head);

	recursive_adv_graph_free(head);

	export_expr_tree_to_xml("test1.xml", expr_head);

	recursive_expr_tree_free(expr_head);

	printf("Test1 passed!\n");

	return 0;
}
