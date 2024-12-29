%{
    // Write all the supporting C - code declarations/definitions
    #include "ParserExport.h"
    #include <cassert>

    char lex_buffer[MAX_STRING_SIZE];
    stack_t undo_stack = {-1, {0, 0, 0}};
    char* curr_ptr = lex_buffer;
    char* lex_curr_token;
    int lex_curr_token_len;

    void parser_stack_reset() {
        int i;
        lex_data_t* lex_data;
        for(i = 0; i < undo_stack.top; i++) {
            lex_data = &undo_stack.data[i];
            lex_data->token_code = 0;
            lex_data->token_len = 0;
            if(lex_data->token_val) {
                free(lex_data->token_val);
                lex_data->token_val = NULL;
            }
        }
        undo_stack.top = -1;
        curr_ptr = lex_buffer;
        lex_curr_token = NULL;
        lex_curr_token_len = 0;
    }

    void lex_set_scan_buffer(const char* buffer) {
        yy_scan_string(buffer);
    }

    static void lex_push(lex_data_t data) {
        assert(undo_stack.top < MAX_MEXPR_LEN - 1);
        undo_stack.data[++undo_stack.top] = data;
        lex_curr_token = (char*) data.token_val;
        lex_curr_token_len = data.token_len;
    }

    static lex_data_t lex_pop() {
        assert(undo_stack.top > -1);
        lex_data_t res = undo_stack.data[undo_stack.top--];
        if(undo_stack.top > -1) {
            lex_data_t lex_data = undo_stack.data[undo_stack.top];
            lex_curr_token = (char*) lex_data.token_val;
            lex_curr_token_len = lex_data.token_len;
        } else {
            lex_curr_token = NULL;
            lex_curr_token_len = 0;
        }
        return res;
    }

    static void process_white_space(int n) {
        lex_data_t lex_data;
        curr_ptr += n;
        lex_data.token_code = PARSER_WHITE_SPACE;
        lex_data.token_len = n;
        lex_data.token_val = NULL;
        lex_push(lex_data);
    }

    int cyylex() {
        int token_code = yylex();
        lex_data_t data;
        data.token_code = token_code;
        data.token_len = yyleng;
        curr_ptr += yyleng;
        data.token_val = (char*)calloc(1, yyleng + 1);
        strncpy(data.token_val, yytext, yyleng + 1);
        lex_push(data);
        return token_code;
    }
    
    void yyrewind(int n) {
        if(n <= 0) return;
        if(curr_ptr == lex_buffer) return;
        int data_len = 0;
        lex_data_t lex_data;
        while(n) {
            lex_data = lex_pop();
            data_len += lex_data.token_len;
            if(lex_data.token_code == PARSER_WHITE_SPACE) {
                continue;
            }
            n--;
            lex_data.token_code = 0;
            lex_data.token_len = 0;
        }
        curr_ptr -= data_len;
    }

    // dedicated to decalre all global variables which parser will use END

    #include "MexprEnums.h"
%}

%%
"(" {
    return MATH_BRACKET_START;
}

")" {
    return MATH_BRACKET_END;
}

"<=" {
    return MATH_LESS_THAN_EQ;
}

"<" {
    return MATH_LESS_THAN;
}

">" {
    return MATH_GREATER_THAN;
}

"=" {
    return MATH_EQ;
}

"!=" {
    return MATH_NOT_EQ;
}

"and" {
    return MATH_AND;
}

"or" {
    return MATH_OR;
}

"*" {
    return MATH_MUL;
}

"+" {
    return MATH_PLUS;
}

"-" {
    return  MATH_MINUS;
}

"/" {
    return MATH_DIV;
}

"," {
    return MATH_COMMA;
}

"sqrt" {
    return MATH_SQRT;
}

"sqr" {
    return MATH_SQR;
}

"mmax" {
    return MATH_MAX;
}

"mmin" {
    return MATH_MIN;
}

"sin" {
    return MATH_SIN;
}

"cos" {
    return MATH_COS;
}

"pow" {
    return MATH_POW;
}

\n {
    return PARSER_EOL;
}

"\\\n" {

}

[ ] {
    /* Ignore */
    process_white_space(1);
}

[\t] {
    /*ignore*/
    process_white_space(4);
}

"\\q" {
    return PARSER_QUIT;
}

0|-?[1-9][0-9]* {
    return MATH_INTEGER_VALUE;
}

-?[0-9]*\.[0-9]+ {
    return MATH_DOUBLE_VALUE;
}

[a-zA-Z0-9_]+ {
    return MATH_IDENTIFIER;
}

[a-zA-Z0-9_]+\.[a-zA-Z0-9_]+ {
    return MATH_IDENTIFIER_IDENTIFIER;
}

'[^']*' {
    // string enclosed within single quotes
    return MATH_STRING_VALUE;
}

\"[^"]*\" {
    // string enclosed within double quotes
    return MATH_STRING_VALUE;
}


. {
    // ignore any other character
}

%%

// C main function

extern void Parse_Equations();

int main(int argc, char** argv) {
    while(1) {
        printf("Input ->");
        fgets(lex_buffer, sizeof(lex_buffer), stdin);

        if(lex_buffer[0] == '\n') {
            lex_buffer[0] = 0;
            continue;
        }

        lex_set_scan_buffer(lex_buffer);

        Parse_Equations();

        parser_stack_reset();
    }
    return 0;
}