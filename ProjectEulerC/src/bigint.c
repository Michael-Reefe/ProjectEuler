#include "bigint.h"


// private helper functions

static inline bool bit_check(u32 number, u32 n) {
    return (number >> n) & (u32)1;
}

static inline u32 bit_set(u32 number, u32 n, bool bit) {
    return (number & ~((u32)1 << n)) | ((u32)bit << n);
}

// left-shift the words in a bigint by nwords
static void _lshift_word(BigInt *bi, u32 nwords) {
    assert(bi != NULL);
    for (i32 i = bi->data->length-1; i >= 0; --i) {
        if (i >= nwords) 
            bi->data->arr[i] = bi->data->arr[i - nwords];
        else 
            bi->data->arr[i] = 0;  // zero-pad shifted words
    }
}

// left-shift everything by 1 bit
static void _lshift_1bit(BigInt *bi) {
    assert(bi != NULL);
    for (size_t i = bi->data->length-1; i > 0; --i) {
        bi->data->arr[i] = (bi->data->arr[i] << 1) | (bi->data->arr[i-1] >> ((32) - 1));
    }
    bi->data->arr[0] <<= 1;
}

// // right-shift the words in a bigint by nwords
// static void _rshift_word(BigInt *bi, u32 nwords) {
//     assert(bi != NULL);
//     for (i32 i = 0; i < bi->data->length; ++i) {
//         if (i < bi->data->length - nwords) 
//             bi->data->arr[i] = bi->data->arr[i + nwords];
//         else
//             bi->data->arr[i] = 0;  // zero-pad shifted words
//     }
// }

// // right-shift everything by 1 bit
// static void _rshift_1bit(BigInt *bi) {
//     assert(bi != NULL);
//     for (size_t i = 0; i < bi->data->length-1; ++i) {
//         bi->data->arr[i] = (bi->data->arr[i] >> 1) | (bi->data->arr[i+1] << ((32) - 1));
//     }
//     bi->data->arr[bi->data->length-1] >>= 1;
// }


// Initializer function
BigInt* bigint_init(size_t nbytes) {
    BigInt *bi = (BigInt*)malloc(sizeof(BigInt));
    assert(bi != NULL);
    SArray_u32 *data = init_SArray_u32(nbytes/4);  // one u32 is 4 bytes
    // initialize all zeros in the array
    bi->data = data;
    bigint_set_zero(bi);
    return bi;
}

// Resize function
void bigint_resize(BigInt *bi, size_t new_nbytes) {
    assert(bi != NULL);
    resize_SArray_u32(bi->data, new_nbytes/4);
}

// copy a bigint from src to dst
void bigint_copy(BigInt *src, BigInt *dst) {
    assert(src != NULL);
    assert(dst != NULL);
    // zero the output buffer
    bigint_set_zero(dst);
    size_t minlen = min(src->data->length, dst->data->length);
    for (size_t i = 0; i < minlen; ++i) dst->data->arr[i] = src->data->arr[i];
}

void bigint_set_zero(BigInt *bi) {
    for (size_t i = 0; i < bi->data->length; ++i) bi->data->arr[i] = 0;
}

// Initialize from an integer
BigInt* bigint_from_int(u64 num) {
    // initialize with 8 bytes so we can safely store a u64
    BigInt *bi = bigint_init(8);  
    bigint_set_int(bi, num);
    return bi;
}

// Set to an integer (limited to u64 values)
void bigint_set_int(BigInt *bi, u64 num) {
    assert(bi != NULL);
    assert(bi->data->length >= 2);
    // split into lower 4 bytes and upper 4 bytes
    bi->data->arr[0] = num;             // lower bytes (the "end" of the number, assuming little-endian)
    bi->data->arr[1] = (num >> 32);     // upper bytes (the "beginning" of the number, assuming little-endian)
    for (size_t i = 2; i < bi->data->length; ++i) {
        bi->data->arr[i] = 0;
    }
}

// Convert to an integer
u64 bigint_to_int(BigInt *bi) {
    assert(bi != NULL);
    u64 out = bi->data->arr[0];  // we will lose data if bi is larger than 64 bits :(
    return out;
}

// Initialize from a string (MUST BE NULL-TERMINATED)
BigInt* bigint_from_string(char *str) {
    assert(str != NULL);

    // calculate how many bytes we need to store this int (minimum 8)
    size_t nbytes = ceil((strlen(str)/log10(2))/8) + 4;
    nbytes = max(nbytes, 8);
    BigInt *bout = bigint_init(nbytes);

    // set it with the in-place function
    bigint_set_string(bout, str);

    return bout;
}

void bigint_set_string(BigInt *bi, char *str) {
    assert(bi  != NULL);
    assert(str != NULL);

    // zero out the input
    bigint_set_zero(bi);
    
    // store a few bigints for doing math
    u32 digit;
    size_t ndigits = strlen(str);
    size_t nbytes  = bi->data->length*4;
    BigInt *bten   = bigint_init(nbytes);
    BigInt *bdigit = bigint_init(nbytes);
    bigint_set_int(bten, 10);

    for (size_t nd = 0; nd < ndigits; ++nd) {
        digit = (*(str++)-'0');
        bigint_set_int(bdigit, digit);              // bdigit = digit;
        bigint_imul(bi, bten);                      // bi *= 10;
        bigint_iadd(bi, bdigit);                    // bi += bdigit;
    }

    bigint_free(bten);
    bigint_free(bdigit);
}

char* bigint_to_string(BigInt *b) {
    assert(b != NULL);

    // calculate how long of a string we need
    size_t nbytes = ceil(b->data->length*32*log10(2)) + 1;

    // initialize a string of zeros
    char *str = (char*)malloc(nbytes);
    assert(str != NULL);
    // for (i64 si = 0; si < nbytes; ++si) str[si] = '0';
    // str[nbytes-1] = 0;

    BigInt *bi      = bigint_init(b->data->length*4);
    BigInt *bzero   = bigint_init(b->data->length*4);
    BigInt *bten    = bigint_init(b->data->length*4);
    BigInt *brem    = bigint_init(b->data->length*4);
    BigInt *next_bi = bigint_init(b->data->length*4);
    bigint_set_zero(bzero);
    bigint_set_int(bten, 10);
    bigint_copy(b, bi);

    // repeat division by 10, using the remainder as a decimal digit.
    // this will build a string with digits in reverse order.
    size_t pos = 0;
    while (bigint_compare(bi, bzero) != EQUAL) {
        bigint_divmod(bi, bten, next_bi, brem);
        assert(pos < nbytes-1);
        str[pos++] = '0' + brem->data->arr[0];  // (remainder is guaranteed to be 0-9)
        bigint_copy(next_bi, bi);
    }
    if (pos == 0) str[pos++] = '0';  // edge case

    // reverse digits in-place
    for (size_t i = 0; i < pos/2; ++i) {
        char t = str[i];
        str[i] = str[pos-1-i];
        str[pos-1-i] = t;
    }
    // null terminator
    str[pos] = 0;

    bigint_free(next_bi);
    bigint_free(bzero);
    bigint_free(bten);
    bigint_free(brem);
    bigint_free(bi);

    return str;
}

// Increment a BigInt by 1
void bigint_inc(BigInt *bi) {
    assert(bi != NULL);
    u32 res;
    u64 temp;

    // this is a loop in case "res" overflows and needs
    // to carry over into the next word
    for (size_t i = 0; i < bi->data->length; ++i) {
        temp = bi->data->arr[i];
        res  = temp + 1;
        bi->data->arr[i] = res;
        if (res > temp) break;
    }
}

// Decrement a BigInt by 1
void bigint_dec(BigInt *bi) {
    assert(bi != NULL);
    u32 res, temp;

    // this is a loop in case "res" underflows and needs
    // to borrow from the next word
    for (size_t i = 0; i < bi->data->length; ++i) {
        temp = bi->data->arr[i];
        res  = temp - 1;
        bi->data->arr[i] = res;
        if (!(res > temp)) break;
    }
}


// Add two BigInts to an output buffer
static void _bigint_add_internal(BigInt *a, BigInt *b, BigInt *c) {
    assert(a != NULL);
    assert(b != NULL);
    assert(c != NULL);

    // zero the output buffer
    bigint_set_zero(c);

    // longest length of both inputs and the output
    size_t maxlen = max(c->data->length, max(a->data->length, b->data->length));

    u32 carry = 0;
    u32 d1, d2;
    u64 temp;
    // Loop through "words" (elements of "data") from least significant (end) to most (0)
    for (size_t i = 0; i < maxlen; ++i) {
        d1 = 0;
        d2 = 0;
        if (i < a->data->length) d1 = a->data->arr[i];
        if (i < b->data->length) d2 = b->data->arr[i];
        temp = (u64) d1 + d2 + carry;
        if (i < c->data->length) c->data->arr[i] = (temp & WORD_MAX_VAL);    // bitwise and works like a modulo here (but it's faster)
        carry = (temp > WORD_MAX_VAL);
    }
}

void bigint_add(BigInt *a, BigInt *b, BigInt *c) {
    _bigint_add_internal(a, b, c);
}

void bigint_iadd(BigInt *a, BigInt *b) {
    // temporary output buffer
    assert(a != NULL);
    BigInt *temp = bigint_init(a->data->length*4);
    _bigint_add_internal(a, b, temp);
    // copy temp into a
    bigint_copy(temp, a);
    // release temp
    bigint_free(temp);
}

// Subtract two BigInts to an output buffer
static void _bigint_sub_internal(BigInt *a, BigInt *b, BigInt *c) {
    assert(a != NULL);
    assert(b != NULL);
    assert(c != NULL);

    // zero the output buffer
    bigint_set_zero(c);

    // longest length of both inputs and the output
    size_t maxlen = max(c->data->length, max(a->data->length, b->data->length));

    u32 borrow = 0;
    u64 temp1, temp2, tempr;
    // Loop through "words" (elements of "data") from least significant (end) to most (0)
    for (size_t i = 0; i < maxlen; ++i) {
        temp1 = (u64)0 + (u64)WORD_MAX_VAL + 1;
        temp2 = (u64)0 + borrow;
        if (i < a->data->length) temp1 = (u64)a->data->arr[i] + (WORD_MAX_VAL + 1);  // add WORD_MAX_VAL to allow subtraction with uints
        if (i < b->data->length) temp2 = (u64)b->data->arr[i] + borrow;
        tempr = (temp1 - temp2);
        if (i < c->data->length) c->data->arr[i] = (u32)(tempr & WORD_MAX_VAL);    // bitwise and works like a modulo here (but it's faster)
        borrow = (tempr <= WORD_MAX_VAL);
    }
}

void bigint_sub(BigInt *a, BigInt *b, BigInt *c) {
    _bigint_sub_internal(a, b, c);
}

void bigint_isub(BigInt *a, BigInt *b) {
    // temporary output buffer
    assert(a != NULL);
    BigInt *temp = bigint_init(a->data->length*4);
    _bigint_sub_internal(a, b, temp);
    // copy temp into a
    bigint_copy(temp, a);
    // release temp
    bigint_free(temp);
}


// Multiply two BigInts to an output buffer
void _bigint_mul_internal(BigInt *a, BigInt *b, BigInt *c) {
    assert(a != NULL);
    assert(b != NULL);
    assert(c != NULL);

    // zero the output buffer
    bigint_set_zero(c);

    // longest length of both inputs and the output
    size_t maxlen = max(c->data->length, max(a->data->length, b->data->length));

    BigInt *bi_row  = bigint_init(maxlen*4); 
    BigInt *bi_temp = bigint_init(maxlen*4);
    u32 d1, d2;
    u64 temp;

    // just do the simple multiplication algorithm where we go through each digit
    for (size_t i = 0; i < maxlen; ++i) {
        bigint_set_zero(bi_row);
        assert(bi_row != NULL);
        for (size_t j = 0; j < maxlen; ++j) {
            d1 = 0;
            d2 = 0;
            if (i < a->data->length) d1 = a->data->arr[i];
            if (j < b->data->length) d2 = b->data->arr[j]; 
            temp = (u64)d1 * (u64)d2;
            bigint_set_int(bi_temp, temp);        // create temporary bigint for this individual word mult
            _lshift_word(bi_temp, i+j);           // left shift by i+j words to align for the addition
            bigint_iadd(bi_row, bi_temp);         // bi_row += bi_temp;
        }
        bigint_iadd(c, bi_row);                   // c += bi_row;
    }

    bigint_free(bi_row);
    bigint_free(bi_temp);
}

// public multiplication functions
void bigint_mul(BigInt *a, BigInt *b, BigInt *c) {
    _bigint_mul_internal(a, b, c);
}

// in-place multiplication function
void bigint_imul(BigInt *a, BigInt *b) {
    // temporary output buffer
    assert(a != NULL);
    BigInt *temp = bigint_init(a->data->length*4);
    _bigint_mul_internal(a, b, temp);
    // copy temp into a
    bigint_copy(temp, a);
    // release temp
    bigint_free(temp);
}

// Divide two BigInts to an output buffer
void bigint_divmod(BigInt *dividend, BigInt *divisor, BigInt *quotient, BigInt *remainder) {
    assert(dividend  != NULL);
    assert(divisor   != NULL);
    assert(quotient  != NULL);
    assert(remainder != NULL);

    // zero the output buffers
    bigint_set_zero(quotient);
    bigint_set_zero(remainder);

    // longest length of both inputs and the output
    size_t maxlen = dividend->data->length;

    for (i32 wordn = maxlen-1; wordn >= 0; --wordn) {
        for (i32 bitn = 31; bitn >= 0; --bitn) {
            _lshift_1bit(remainder);                // remainder <<= 1;
            // set the 0th bit of remainder to the ith bit of dividend
            // check the value of the ith bit of dividend
            bool bit = bit_check(dividend->data->arr[wordn], bitn);
            // set it to the 0th bit of remainder
            remainder->data->arr[0] = bit_set(remainder->data->arr[0], 0, bit);
            if (bigint_compare(remainder, divisor) != SMALLER) {        // if (remainder >= divisor)
                bigint_isub(remainder, divisor);                        // remainder -= divisor;
                // set the ith bit of quotient to 1
                quotient->data->arr[wordn] = bit_set(quotient->data->arr[wordn], bitn, 1);
            }
        }
    }
}

// do divmod and throw away the remainder
static void _bigint_div_internal(BigInt *dividend, BigInt *divisor, BigInt *quotient) {
    assert(quotient  != NULL);
    BigInt *remainder = bigint_init(quotient->data->length*4);
    bigint_divmod(dividend, divisor, quotient, remainder);
    bigint_free(remainder);
}

void bigint_div(BigInt *dividend, BigInt *divisor, BigInt *quotient) {
    _bigint_div_internal(dividend, divisor, quotient);
}

void bigint_idiv(BigInt *dividend, BigInt *divisor) {
    // temporary output buffer
    assert(dividend != NULL);
    BigInt *temp = bigint_init(dividend->data->length*4);
    _bigint_div_internal(dividend, divisor, temp);
    // copy temp into dividend
    bigint_copy(temp, dividend);
    // release temp
    bigint_free(temp);
}

// do divmod and throw away the quotient
static void _bigint_mod_internal(BigInt *dividend, BigInt *divisor, BigInt *remainder) {
    assert(remainder  != NULL);
    BigInt *quotient = bigint_init(remainder->data->length*4);
    bigint_divmod(dividend, divisor, quotient, remainder);
    bigint_free(quotient);
}

void bigint_mod(BigInt *dividend, BigInt *divisor, BigInt *remainder) {
    _bigint_mod_internal(dividend, divisor, remainder);
}

void bigint_imod(BigInt *dividend, BigInt *divisor) {
    // temporary output buffer
    assert(dividend != NULL);
    BigInt *temp = bigint_init(dividend->data->length*4);
    _bigint_mod_internal(dividend, divisor, temp);
    // copy temp into dividend
    bigint_copy(temp, dividend);
    // release temp
    bigint_free(temp);
}

// compare two bigints
i8 bigint_compare(BigInt *in1, BigInt *in2) {
    size_t i = max(in1->data->length, in2->data->length);
    while (i != 0) {
        --i;
        if ((i >= in1->data->length) && (i <  in2->data->length) && (in2->data->arr[i] > 0))
            return SMALLER;
        else if ((i <  in1->data->length) && (i >= in2->data->length) && (in1->data->arr[i] > 0))
            return LARGER;
        else if ((i <  in1->data->length) && (i <  in2->data->length) && (in1->data->arr[i] > in2->data->arr[i]))
            return LARGER;
        else if ((i <  in1->data->length) && (i <  in2->data->length) && (in1->data->arr[i] < in2->data->arr[i]))
            return SMALLER;
    }
    return EQUAL;
}

// Destructor function
void bigint_free(BigInt *bi) {
    free_SArray_u32(bi->data);
    free(bi);
}