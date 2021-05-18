#ifndef TRANSLATOR_UTIL_H
#define TRANSLATOR_UTIL_H

#include "expr_structs.h"
#include "xml.h"

void export_expr_tree_to_xml(char *filename, struct expr_tree_head *head);

void export_tree_link(struct xml *xml, struct expr_tree_link *link);

#endif
