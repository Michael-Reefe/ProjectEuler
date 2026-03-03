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

BigInt* bigint_init(size_t nbytes);
void    bigint_resize(BigInt *bi, size_t new_nbytes);
void    bigint_copy(BigInt *src, BigInt *dst);
void    bigint_set_zero(BigInt *bi);
void    bigint_set_int(BigInt *bi, u64 num);
BigInt* bigint_from_int(u64 num);
u64     bigint_to_int(BigInt *bi);
void    bigint_set_string(BigInt *bi, char *str);
BigInt* bigint_from_string(char *str);
char*   bigint_to_string(BigInt *bi);
void    bigint_inc(BigInt *bi);
void    bigint_dec(BigInt *bi);
void    bigint_add(BigInt *a, BigInt *b, BigInt *c);
void    bigint_iadd(BigInt *a, BigInt *b);
void    bigint_sub(BigInt *a, BigInt *b, BigInt *c);
void    bigint_isub(BigInt *a, BigInt *b);
void    bigint_mul(BigInt *a, BigInt *b, BigInt *c);
void    bigint_imul(BigInt *a, BigInt *b);
void    bigint_divmod(BigInt *dividend, BigInt *divisor, BigInt *quotient, BigInt *remainder);
void    bigint_div(BigInt *dividend, BigInt *divisor, BigInt *quotient);
void    bigint_idiv(BigInt *dividend, BigInt *divisor);
void    bigint_mod(BigInt *dividend, BigInt *divisor, BigInt *remainder);
void    bigint_imod(BigInt *dividend, BigInt *divisor);
i8      bigint_compare(BigInt *in1, BigInt *in2);
void    bigint_free(BigInt *bi);

#endif // BIGINT_H