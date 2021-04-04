#ifndef XML_H
#define XML_H

#include <stdio.h>

struct xml {
    FILE *xml_file;
    int indent_num;
};

struct xml* open_xml(const char *filename);
void close_xml(struct xml *xml);

void open_tag(struct xml *xml, char *name, int attribute_count, ...);
void close_tag(struct xml *xml, char *name);

void write_str(struct xml *xml, char *text);

void inline_tag(struct xml *xml, char *name, char *value, int attribute_count, ...);

#endif
