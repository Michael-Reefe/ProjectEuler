#ifndef BIGINT_H
#define BIGINT_H

// Note: HEAVILY stolen from: https://github.com/kokke/tiny-bignum-c
//                       and: https://github.com/ilia3101/Big-Integer-C

#include <string.h>
#include "utils.h"

#define WORD_SIZE 4
#define WORD_MAX_VAL ((u64)0xFFFFFFFF)

// BigInt structs are an arbitrarily sized array of u32s
typedef struct _BigInt {
    SArray_u32 *data;
} BigInt;

enum {
    SMALLER = -1,
    EQUAL   =  0,
    LARGER  =  1,
};

BigInt* init_BigInt(size_t nbytes);
void    bigint_set_zero(BigInt *bi);
void    bigint_set_int(BigInt *bi, u64 num);
void    resize_BigInt(BigInt *bi, size_t new_nbytes);
void    bigint_copy(BigInt *src, BigInt *dst);
BigInt* bigint_from_int(u64 num);
u64     bigint_to_int(BigInt *bi);
BigInt* bigint_from_string(char *str);
char*   bigint_to_string(BigInt *bi);
void    bigint_add(BigInt *in1, BigInt *in2, BigInt *out);
void    bigint_sub(BigInt *in1, BigInt *in2, BigInt *out);
void    bigint_mul(BigInt *in1, BigInt *in2, BigInt *out);
void    bigint_div(BigInt *in1, BigInt *in2, BigInt *quotient);
void    bigint_divmod(BigInt *in1, BigInt *in2, BigInt *quotient, BigInt *remainder);
void    bigint_or(BigInt *in1, BigInt *in2, BigInt *out);
i8      bigint_compare(BigInt *in1, BigInt *in2);
void    free_BigInt(BigInt *bi);

#endif // BIGINT_H