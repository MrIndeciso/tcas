#include "parser.h"

#include "rpn_parser.h"

struct graph_node* parse(size_t len, struct token *tkn, enum PARSER_MODE mode) {
	switch (mode) {
		case MODE_STANDARD:
			return NULL;
		case MODE_RPN:
			rpn_parse(len, tkn);
		case MODE_CUSTOM_RPN:
			return NULL;
		default:
			return NULL;
	}
}
