#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <assert.h>

#include "xml.h"

static void lf_indent(struct xml *xml);

struct xml* open_xml(const char *filename) {
    struct xml *xml = malloc(sizeof(struct xml));

    FILE *file = fopen(filename, "w");
    assert(file != NULL);

    xml->xml_file = file;
    xml->indent_num = 0;

    return xml;
}

void close_xml(struct xml *xml) {
    write_str(xml, "\n");
    if (xml->indent_num > 0) {
        printf("Attention! Invalid XML detected!\n");
        write_str(xml, "Attention! Invalid XML detected!\n");
    }
    fclose(xml->xml_file);
    free(xml);
}

void open_tag(struct xml *xml, char *name, int attribute_count, ...) {
    va_list args;

    assert(attribute_count % 2 == 0); //Odd number makes no sense for pairs of attribute-value

    char *text = malloc(512);
    snprintf(text, 512, "%s", name);

    va_start(args, attribute_count);

    for (int i = 0; i < attribute_count; i += 2) {
        char *attribute = va_arg(args, char*);
        char *value = va_arg(args, char*);
        char *temp = malloc(128);
        snprintf(temp, 128, " %s=\"%s\"", attribute, value);
        strcat(text, temp);
        free(temp);
    }

    va_end(args);

    lf_indent(xml);

    fprintf(xml->xml_file, "<%s>", text);

    xml->indent_num++;

    free(text);
}

void close_tag(struct xml *xml, char *name) {
    xml->indent_num--;
    lf_indent(xml);

    fprintf(xml->xml_file, "</%s>", name);
}

void write_str(struct xml *xml, char *text) {
    lf_indent(xml);
    int result = fputs(text, xml->xml_file);
    assert(result != EOF);
}

void inline_tag(struct xml *xml, char *name, char *value, int attribute_count, ...) {
    va_list args;

    assert(attribute_count % 2 == 0);

    char *text = malloc(512);
    snprintf(text, 512, "%s", name);

    va_start(args, attribute_count);

    for (int i = 0; i < attribute_count; i += 2) {
        char *attribute = va_arg(args, char*);
        char *attr_value = va_arg(args, char*);
        char *temp = malloc(128);
        snprintf(temp, 128, " %s=\"%s\"", attribute, attr_value);
        strcat(text, temp);
        free(temp);
    }

    va_end(args);

    lf_indent(xml);

    if (value != NULL)
        fprintf(xml->xml_file, "<%s>%s</%s>", text, value, name);
    else
        fprintf(xml->xml_file, "<%s/>", text);

    free(text);
}

static void lf_indent(struct xml *xml) {
    assert(fputs("\n", xml->xml_file) != EOF);
    for (int i = 0; i < xml->indent_num; i++) {
        int result = fputs("\t", xml->xml_file);
        assert(result != EOF);
    }
}
