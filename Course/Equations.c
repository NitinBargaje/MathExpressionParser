#include <stdbool.h>
#include <stdio.h>
#include "ParserExport.h"
#include "MexprEnums.h"
#include <cstring>


#define PARSER_LOG_ERROR(token_obtained, token_expected) \
    printf("%s(%d): Token obtained = %d(%s), expected token = %d\n", \
    __FUNCTION__, __LINE__, token_obtatined, lex_curr_token, expected_token);
// pow(x,2) + pow(y,2) = <CONSTANT>
parse_rc_t circle_eqn() {
    parse_init();

    token_code = cyylex();
    if(token_code != MATH_POW) {
        RETURN_PARSE_ERROR;
    }
    token_code = cyylex();
    if(token_code != MATH_BRACKET_START) {
        RETURN_PARSE_ERROR;
    }
    token_code = cyylex();
    if(token_code != MATH_IDENTIFIER) {
        RETURN_PARSE_ERROR;
    }
    if(strcmp(lex_curr_token, "x") != 0) {
        RETURN_PARSE_ERROR;
    }
    token_code = cyylex();
    if(token_code != MATH_COMMA) {
        RETURN_PARSE_ERROR;
    }
    token_code = cyylex();
    if(token_code != MATH_INTEGER_VALUE) {
        RETURN_PARSE_ERROR;
    }
    if(strcmp(lex_curr_token, "2") != 0) {
        RETURN_PARSE_ERROR;
    }
    token_code = cyylex();
    if(token_code != MATH_BRACKET_END) {
        RETURN_PARSE_ERROR;
    }
    token_code = cyylex();
    if(token_code != MATH_PLUS) {
        RETURN_PARSE_ERROR;
    }

    token_code = cyylex();
    if(token_code != MATH_POW) {
        RETURN_PARSE_ERROR;
    }
    token_code = cyylex();
    if(token_code != MATH_BRACKET_START) {
        RETURN_PARSE_ERROR;
    }
    token_code = cyylex();
    if(token_code != MATH_IDENTIFIER) {
        RETURN_PARSE_ERROR;
    }
    if(strcmp(lex_curr_token, "y") != 0) {
        RETURN_PARSE_ERROR;
    }
    token_code = cyylex();
    if(token_code != MATH_COMMA) {
        RETURN_PARSE_ERROR;
    }
    token_code = cyylex();
    if(token_code != MATH_INTEGER_VALUE) {
        RETURN_PARSE_ERROR;
    }
    if(strcmp(lex_curr_token, "2") != 0) {
        RETURN_PARSE_ERROR;
    }
    token_code = cyylex();
    if(token_code != MATH_BRACKET_END) {
        RETURN_PARSE_ERROR;
    }

    token_code = cyylex();
    if(token_code != MATH_EQ) {
        RETURN_PARSE_ERROR;
    }

    token_code = cyylex();
    if(token_code != MATH_INTEGER_VALUE && token_code != MATH_DOUBLE_VALUE) {
        RETURN_PARSE_ERROR;
    }
    RETURN_PARSE_SUCCESS;
}

static bool ellipse_eqn() {

    return true;
}

void Parse_Equations() {

    bool rc = circle_eqn();

    if(rc) {
        printf("Eqn of circle\n");
    }

    rc = ellipse_eqn();

    if(rc) {
        printf("Eqn of Ellipse\n");
    }
}