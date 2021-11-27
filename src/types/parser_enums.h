#ifndef PARSER_ENUMS_H
#define PARSER_ENUMS_H

enum PARSER_MODE {
    MODE_PN,
};

enum LINKED_TYPE {
    OPERATOR,
    VALUE,
    SYMBOL
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
    LIM,
    DERIVE,
    TAYLOR,
    MACLAURIN,
    EXP,
    UNKNOWN
};

#endif
