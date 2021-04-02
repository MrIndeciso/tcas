#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "tokenizer.h"

int test1();

int main() {
	int return_value = 0;
	return_value += test1();
	return return_value;
}

int test1() {
	char *input = "3 + 5";
	size_t len = strlen(input);
	
	size_t tkn_count;
	tokenize(len, input, &tkn_count, NULL);
	struct token *tkn = malloc(tkn_count * sizeof(struct token));
	tokenize(len, input, &tkn_count, tkn);

	assert(tkn_count == 3);

	assert(tkn[0].len == 1);
	assert(tkn[0].token[0] == '3');
	assert(tkn[1].len == 1);
	assert(tkn[1].token[0] == '+');
	assert(tkn[2].len == 1);
	assert(tkn[2].token[0] == '5');

	printf("Test1 passed!\n");

	return 0;
}
