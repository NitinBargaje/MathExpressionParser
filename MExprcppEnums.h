#ifndef __MEXPRCPPENUMS__
#define __MEXPRCPPENUMS__

#define MEXPR_OPR   1
#define MEXPR_OPND  -1

typedef enum {

    MATH_CPP_MOD,
    MATH_CPP_PLUS,
    MATH_CPP_MINUS,
    MATH_CPP_OPR_MAX

} mexprcpp_operators_t;

typedef enum {

    MATH_CPP_INT,
    MATH_CPP_DOUBLE,
    MATH_CPP_STRING,
    MATH_CPP_IPV4,
    MATH_CPP_VARIABLE,
    MATH_CPP_DTYPE_INVALID,
    MATH_CPP_DTYPE_WILDCRAD,
    MATH_CPP_DTYPE_MAX
    
} mexprcpp_dtypes_t;


#endif 