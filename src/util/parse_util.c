#include <assert.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include "parse_util.h"
#include "tokenizer.h"
#include "parser.h"
#include "translator.h"
#include "mem_util.h"
#include "tree_util.h"

static struct expr_tree_link *find = &(struct expr_tree_link){
    .type = SYMBOL,
    .ptr = &(union expr_tree_ptr) {
        .sym = &(struct expr_tree_sym){
            .sign = 1,
            .representation = 'a'
        }
    }
};

static struct expr_tree_link *find2 = &(struct expr_tree_link){
    .type = SYMBOL,
    .ptr = &(union expr_tree_ptr) {
        .sym = &(struct expr_tree_sym){
            .sign = 1,
            .representation = 'b'
        }
    }
};

static struct expr_tree_link *find_generic(int count) {
    struct expr_tree_link *generic = malloc(sizeof(struct expr_tree_link));
    generic->type = SYMBOL;
    generic->ptr = malloc(sizeof(union expr_tree_ptr));
    generic->ptr->sym = malloc(sizeof(struct expr_tree_sym));
    generic->ptr->sym->sign = 1;
    generic->ptr->sym->representation = 'a' + count;
    return generic;
}

static void free_generic(struct expr_tree_link *generic) {
    free_tree_link(generic);
}

//TODO FIX MEMORY LEAK OF HEAD NOT FREED SINCE WE RETURN ONLY CONTAINED POINTER
struct expr_tree_link* parse_expr(char *expr, struct expr_tree_link *subst) {
    size_t count;
    tokenize(strlen(expr), expr, &count, NULL);
    struct token *tkn = malloc(count * sizeof(struct token));
    tokenize(strlen(expr), expr, &count, tkn);
    struct graph_link *head = parse(count, tkn, MODE_PN);
    free(tkn);
    struct expr_tree_head *expr_head = translate_graph(head);

    if (subst != NULL)
        recursive_replace(expr_head->head, find, subst);

    return expr_head->head;
}

//TODO FIX MEMORY LEAK OF HEAD NOT FREED SINCE WE RETURN ONLY CONTAINED POINTER
struct expr_tree_link* parse_double_expr(char *expr, struct expr_tree_link *subst1, struct expr_tree_link *subst2) {
    assert(subst1 != NULL);
    assert(subst2 != NULL);

    size_t count;
    tokenize(strlen(expr), expr, &count, NULL);
    struct token *tkn = malloc(count * sizeof(struct token));
    tokenize(strlen(expr), expr, &count, tkn);
    struct graph_link *head = parse(count, tkn, MODE_PN);
    free(tkn);
    struct expr_tree_head *expr_head = translate_graph(head);

    recursive_replace(expr_head->head, find, subst1);
    recursive_replace(expr_head->head, find2, subst2);

    return expr_head->head;
}

//TODO FIX MEMORY LEAK OF HEAD NOT FREED SINCE WE RETURN ONLY CONTAINED POINTER
struct expr_tree_link* parse_varargs(char *expr, int attribute_count, ...) {
    va_list args;

    size_t count;
    tokenize(strlen(expr), expr, &count, NULL);
    struct token *tkn = malloc(count * sizeof(struct token));
    tokenize(strlen(expr), expr, &count, tkn);
    struct graph_link *head = parse(count, tkn, MODE_PN);
    free(tkn);
    struct expr_tree_head *expr_head = translate_graph(head);

    va_start(args, attribute_count);

    for (int i = 0; i < attribute_count; i++) {
        struct expr_tree_link *link = va_arg(args, struct expr_tree_link*);
        struct expr_tree_link *generic = find_generic(i);
        recursive_replace(expr_head->head, generic, link);
        free_generic(generic);
    }

    va_end(args);

    return expr_head->head;
}
