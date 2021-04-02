#ifndef TCAS_ENUMS_H
#define TCAS_ENUMS_H

typedef enum {
	RPN_PARSER,
	PN_PARSER,
	CRPN_PARSER,
	STD_PARSER,
} PARSER_TYPE;

typedef enum {
	SUCCESS,
	FAIL
} TCAS_OP_RESULT;


#endif
