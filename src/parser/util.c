#include <stdlib.h>
#include <assert.h>

#include "util.h"
#include "rpn_defs.h"

static void export_node(struct xml *xml, struct graph_node *node);
static void export_link(struct xml *xml, struct graph_link *link);

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

        for (size_t i = 0; i < node->children_count; i++)
            export_node(xml, node->children[i]);

        close_tag(xml, "node");
    } else {
        inline_tag(xml, "node", NULL, 2, "token", node->token.token);
    }
}

void export_adv_graph_to_xml(char *filename, struct graph_link *head) {
    struct xml *xml = open_xml(filename);

    export_link(xml, head);

    close_xml(xml);
}

static void export_link(struct xml *xml, struct graph_link *link) {
    if (link->type == VALUE) {
        inline_tag(xml, "value", link->ptr->value->content, 0);
    } else {
        char *buffer = malloc(32);
        snprintf(buffer, 32, "%d", (int) link->ptr->op->children_count);

        open_tag(xml, "operator", 4, "type", op_value_from_type[link->ptr->op->type], "children_count", buffer);

        free(buffer);

        for (size_t i = 0; i < link->ptr->op->children_count; i++)
            export_link(xml, link->ptr->op->children[i]);

        close_tag(xml, "operator");
    }
}
