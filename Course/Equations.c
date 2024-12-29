#include <stdbool.h>
#include <stdio.h>
#include "ParserExport.h"
#include "MexprEnums.h"
#include <cstring>

// pow(x,2) + pow(y,2) = <CONSTANT>
static bool circle_eqn() {
    int token_code;
    token_code = cyylex();
    if(token_code != MATH_POW) {
        yyrewind(1);
        return false;
    }
    token_code = cyylex();
    if(token_code != MATH_BRACKET_START) {
        yyrewind(2);
        return false;
    }
    token_code = cyylex();
    if(token_code != MATH_IDENTIFIER) {
        yyrewind(3);
        return false;
    }
    if(strcmp(lex_curr_token, "x") != 0) {
        yyrewind(3);
        return false;
    }
    token_code = cyylex();
    if(token_code != MATH_COMMA) {
        yyrewind(4);
        return false;
    }
    token_code = cyylex();
    if(token_code != MATH_INTEGER_VALUE) {
        yyrewind(5);
        return false;
    }
    if(strcmp(lex_curr_token, "2") != 0) {
        yyrewind(5);
        return false;
    }
    token_code = cyylex();
    if(token_code != MATH_BRACKET_END) {
        yyrewind(6);
        return false;
    }
    token_code = cyylex();
    if(token_code != MATH_PLUS) {
        yyrewind(7);
        return false;
    }

    token_code = cyylex();
    if(token_code != MATH_POW) {
        yyrewind(8);
        return false;
    }
    token_code = cyylex();
    if(token_code != MATH_BRACKET_START) {
        yyrewind(9);
        return false;
    }
    token_code = cyylex();
    if(token_code != MATH_IDENTIFIER) {
        yyrewind(10);
        return false;
    }
    if(strcmp(lex_curr_token, "y") != 0) {
        yyrewind(10);
        return false;
    }
    token_code = cyylex();
    if(token_code != MATH_COMMA) {
        yyrewind(11);
        return false;
    }
    token_code = cyylex();
    if(token_code != MATH_INTEGER_VALUE) {
        yyrewind(12);
        return false;
    }
    if(strcmp(lex_curr_token, "2") != 0) {
        yyrewind(12);
        return false;
    }
    token_code = cyylex();
    if(token_code != MATH_BRACKET_END) {
        yyrewind(13);
        return false;
    }

    token_code = cyylex();
    if(token_code != MATH_EQ) {
        yyrewind(14);
        return false;
    }

    token_code = cyylex();
    if(token_code != MATH_INTEGER_VALUE && token_code != MATH_DOUBLE_VALUE) {
        yyrewind(15);
        return false;
    }

    return true;
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