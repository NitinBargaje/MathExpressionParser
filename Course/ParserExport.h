#ifndef __PARSER_EXPORT__
#define __PARSER_EXPORT__

#include <cassert>

// Define all supportive data structures BEGIN
typedef enum parse_rc_ {
    PARSE_ERR,
    PARSE_SUCCESS
} parse_rc_t;

typedef struct lex_data_
{
    int token_code;
    int token_len;
    char *token_val;
} lex_data_t;

#define MAX_MEXPR_LEN 512
#define MAX_STRING_SIZE 512
#define PARSER_EOL 10000
#define PARSER_WHITE_SPACE 10002
#define PARSER_QUIT 10003

typedef struct stack_
{
    int top;
    lex_data_t data[MAX_MEXPR_LEN];
} stack_t;

// Define all supportive data structures END

// dedicated to decalre all global variables which parser will use BEGIN

extern "C" int yylex();
extern char lex_buffer[MAX_STRING_SIZE];
extern stack_t undo_stack;
extern char *lex_curr_token;
extern int lex_curr_len;
extern int cyylex();
extern void yyrewind(int n);
extern void parser_stack_reset();
extern void lex_set_scan_buffer(const char *buffer);

#define CHECKPOINT(a) a = undo_stack.top
extern void RESTORE_CHKP(int a);

#define RETURN_PARSE_ERROR { RESTORE_CHKP(_lchkp); return PARSE_ERR; }

#define RETURN_PARSE_SUCCESS return PARSE_SUCCESS

#define parse_init() int token_code = 0; int _lchkp = undo_stack.top; parse_rc_t err = PARSE_SUCCESS

#endif