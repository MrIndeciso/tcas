#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "tokenizer.h"

#define SEPARATOR ' '

void tokenize(size_t len, char *expr, size_t *count, struct token *tkn) {
    assert(expr != NULL);
    assert(count != NULL);
    assert(len > 0);

    if (tkn == NULL) {
        *count = 1;
        for (size_t i = 0; i < len; i++)
            if (expr[i] == SEPARATOR)
                ++(*count);
    } else {
        for (size_t i = 0; i < *count; i++)
            tkn[i].len = 0;

        for (size_t i = 0, cnt = 0; i < len; i++) {
            if (expr[i] == SEPARATOR) {
                cnt++;
                continue;
            } else {
                tkn[cnt].token[tkn[cnt].len] = expr[i];
                tkn[cnt].len++;
                tkn[cnt].token[tkn[cnt].len] = '\0';
            }
        }
    }
}
