#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "parser.h"

int test1();

int main() {
	int return_value = 0;
	return_value += test1();
	return return_value;
}

int test1() {
	return 0;
}
