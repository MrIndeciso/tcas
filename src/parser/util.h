#ifndef PARSER_UTIL_H
#define PARSER_UTIL_H

#include "parser_structs.h"
#include "xml.h"

void recursive_graph_free(struct graph_node *head);

void recursive_adv_graph_free(struct graph_link *head);

void export_graph_to_xml(char *filename, struct graph_node *head);

void export_adv_graph_to_xml(char *filename, struct graph_link *head);

#endif
