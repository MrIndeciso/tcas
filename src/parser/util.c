#include <stdlib.h>
#include <assert.h>

#include "util.h"

static void export_node(struct xml *xml, struct graph_node *node);

void recursive_graph_free(struct graph_node *head) {
	assert(head != NULL);

	for (int i = 0; i < head->children_count; i++)
		recursive_graph_free(head->children[i]);

	free(head);
}

void export_graph_to_xml(char *filename, struct graph_node *head) {
	struct xml *xml = open_xml(filename);
	
	export_node(xml, head);

	close_xml(xml);
}

static void export_node(struct xml *xml, struct graph_node *node) {
	if (node->children_count > 0) {
		char *buffer = malloc(32);
		snprintf(buffer, 32, "%d", (int) node->children_count);

		open_tag(xml, "node", 4, "token", node->token.token, "childrenCount", buffer);
		
		free(buffer);

		for (int i = 0; i < node->children_count; i++)
			export_node(xml, node->children[i]);

		close_tag(xml, "node");
	} else {
		inline_tag(xml, "node", NULL, 2, "token", node->token.token);
	}
}
