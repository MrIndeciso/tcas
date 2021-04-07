#ifndef PARSER_ENUMS_H
#define PARSER_ENUMS_H

enum PARSER_MODE {
    MODE_STANDARD,
    MODE_RPN,
    MODE_CUSTOM_RPN
};

enum LINKED_TYPE {
    OPERATOR,
    VALUE
};

enum OPERATOR_TYPE {
    PLUS,
    MINUS,
    TIMES,
    DIVIDE,
    SQRT,
    SIN,
    COS,
    TAN,
    ARCSIN,
    ARCCOS,
    ARCTAN,
    POWER,
    ROOT,
    LOG10,
    LOG2,
    LOG,
    LN,
    UNKNOWN
};

#endif
