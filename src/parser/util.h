#ifndef UTIL_H
#define UTIL_H

#include "../types/parser_structs.h"
#include "../xml/xml.h"

void recursive_graph_free(struct graph_node *head);

void export_graph_to_xml(char *filename, struct graph_node *head);

void export_adv_graph_to_xml(char *filename, struct graph_link *head);

#endif
