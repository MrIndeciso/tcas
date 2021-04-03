#include <assert.h>
#include <gmp.h>
#include <stdlib.h>

#include "translator_util.h"
#include "../parser/rpn_defs.h"
#include "../xml/xml.h"

static void free_tree_link(struct expr_tree_link *link);
static void export_tree_link(struct xml *xml, struct expr_tree_link *link);

void recursive_expr_tree_free(struct expr_tree_head *head) {
	assert(head->head != NULL);

	free_tree_link(head->head);

	free(head);
}

void export_expr_tree_to_xml(char *filename, struct expr_tree_head *head) {
	struct xml *xml = open_xml(filename);

	export_tree_link(xml, head->head);

	close_xml(xml);
}

static void free_tree_link(struct expr_tree_link *link) {
	if (link->type == OPERATOR) {
		for (int i = 0; i < link->ptr->op->arg_count; i++)
			free_tree_link(link->ptr->op->args[i]);

		free(link->ptr->op->args);
		free(link->ptr->op);
	} else {
		if (link->ptr->val->type == INT) {
			mpz_clear(link->ptr->val->val->int_val);
		} else if (link->ptr->val->type == RATIONAL) {
			mpq_clear(link->ptr->val->val->rational_val);
		} else {
			mpf_clear(link->ptr->val->val->fp_val);
		}
		free(link->ptr->val->val);
		free(link->ptr->val);
	}

	free(link->ptr);
	free(link);
}

static void export_tree_link(struct xml *xml, struct expr_tree_link *link) {
	if (link->type == VALUE) {
		if (link->ptr->val->type == INT) {
			inline_tag(xml, "value", mpz_get_str(NULL, 10, link->ptr->val->val->int_val), 0);
		} else if (link->ptr->val->type == RATIONAL) {
			inline_tag(xml, "value", mpq_get_str(NULL, 10, link->ptr->val->val->rational_val), 0);
		} else {
			mp_exp_t exp;
			char *str = mpf_get_str(NULL, &exp, 10, 20, link->ptr->val->val->fp_val);
			char *buffer = malloc(64);
			snprintf(buffer, 64, "%c.%s**%d", buffer[0], buffer + 1, (int) exp);
			inline_tag(xml, "value", buffer, 0);
			free(str);
			free(buffer);
		}
	} else {
		char *buffer = malloc(32);
		snprintf(buffer, 32, "%d", (int) link->ptr->op->arg_count);

		open_tag(xml, "operator", 4, "type", op_value_from_type[link->ptr->op->type], "arg_count", buffer);
		
		free(buffer);

		for (int i = 0; i < link->ptr->op->arg_count; i++)
			export_tree_link(xml, link->ptr->op->args[i]);

		close_tag(xml, "operator");
	}
}
