#include "bigint.h"


// private helper functions

static inline bool bit_check(WORD_TYPE number, WORD_TYPE n) {
    return (number >> n) & (WORD_TYPE)1;
}

static inline WORD_TYPE bit_set(WORD_TYPE number, WORD_TYPE n, bool bit) {
    return (number & ~((WORD_TYPE)1 << n)) | ((WORD_TYPE)bit << n);
}

// left-shift the words in a bigint by nwords
static void _lshift_word(BigInt *bi, u16 nwords) {
    assert(bi != NULL);
    for (i32 i = bi->length-1; i >= 0; --i) {
        if (i >= nwords) 
            bi->data[i] = bi->data[i - nwords];
        else 
            bi->data[i] = 0;  // zero-pad shifted words
    }
}

// left-shift everything by 1 bit
static void _lshift_1bit(BigInt *bi) {
    assert(bi != NULL);
    for (size_t i = bi->length-1; i > 0; --i) {
        bi->data[i] = (bi->data[i] << 1) | (bi->data[i-1] >> ((32) - 1));
    }
    bi->data[0] <<= 1;
}

// // right-shift the words in a bigint by nwords
// static void _rshift_word(BigInt *bi, u16 nwords) {
//     assert(bi != NULL);
//     for (i32 i = 0; i < bi->length; ++i) {
//         if (i < bi->length - nwords) 
//             bi->data[i] = bi->data[i + nwords];
//         else
//             bi->data[i] = 0;  // zero-pad shifted words
//     }
// }

// // right-shift everything by 1 bit
// static void _rshift_1bit(BigInt *bi) {
//     assert(bi != NULL);
//     for (size_t i = 0; i < bi->length-1; ++i) {
//         bi->data[i] = (bi->data[i] >> 1) | (bi->data[i+1] << ((32) - 1));
//     }
//     bi->data[bi->length-1] >>= 1;
// }


// BIGINT

// Initializer function
BigInt* bigint_init(size_t nwords) {
    BigInt *bi = (BigInt*)malloc(sizeof(BigInt));
    assert(bi != NULL);
    WORD_TYPE *data = (WORD_TYPE*)malloc(nwords*WORD_SIZE);
    // initialize all zeros in the array
    bi->data = data;
    bi->length = nwords;
    bigint_set_zero(bi);
    return bi;
}

// copy a bigint from src to dst
void bigint_copy(BigInt *src, BigInt *dst) {
    assert(src != NULL);
    assert(dst != NULL);
    // zero the output buffer
    bigint_set_zero(dst);
    size_t minlen = min(src->length, dst->length);
    for (size_t i = 0; i < minlen; ++i) dst->data[i] = src->data[i];
}

void bigint_set_zero(BigInt *bi) {
    for (size_t i = 0; i < bi->length; ++i) bi->data[i] = 0;
}

// Initialize from an integer
BigInt* bigint_from_int(TEMP_TYPE num) {
    // this size calculation equates to 2 with the default settings, since
    // a u64 takes twice as many bytes as a u32
    BigInt *bi = bigint_init(TEMP_SIZE/WORD_SIZE);
    bigint_set_int(bi, num);
    return bi;
}

// Set to an integer (limited to u64 values)
void bigint_set_int(BigInt *bi, TEMP_TYPE num) {
    assert(bi != NULL);
    assert(bi->length >= TEMP_SIZE/WORD_SIZE);
    // split into lower bytes and upper bytes
    for (size_t i = 0; i < bi->length; ++i) {
        if (i*WORD_SIZE < TEMP_SIZE)
            bi->data[i] = (num >> 8*WORD_SIZE*i);    // shift right by i word sizes 
        else
            bi->data[i] = 0;
    }
}

// Convert to an integer
TEMP_TYPE bigint_to_int(BigInt *bi) {
    assert(bi != NULL);
    // we will lose data if bi is larger than 64 bits :(
    // but we can at least get the last N words by copying their bits
    TEMP_TYPE out = 0;
    for (size_t i = 0; i < bi->length; ++i) {
        if (i*WORD_SIZE < TEMP_SIZE)
            out |= (bi->data[i] << 8*WORD_SIZE*i);   // shift left by i word sizes
    }
    return out;
}

// Initialize from a string (MUST BE NULL-TERMINATED)
BigInt* bigint_from_string(char *str) {
    assert(str != NULL);

    // calculate how many bytes we need to store this int (minimum 8)
    size_t nbytes = ceil((strlen(str)/log10(2))/8) + WORD_SIZE;
    nbytes = max(nbytes, TEMP_SIZE);
    BigInt *bout = bigint_init(nbytes/WORD_SIZE);

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
    size_t ndigits = strlen(str);  // note: strlen does NOT include the null terminator
    size_t len     = bi->length;
    BigInt *bttt9  = bigint_init(len);
    BigInt *bdigit = bigint_init(len);
    bigint_set_int(bttt9, 1000000000);  // 10^9
    char *pstr = str;  // copy so we dont modify the input pointer
    char *str_end;
    // 10-character buffer for string parsing
    char pbuf[10];
    pbuf[9] = '\0';

    // Do the first chunk, which may be < 9
    size_t nfirst = ndigits % 9;
    if (nfirst == 0) nfirst = 9;
    memcpy(pbuf, pstr, nfirst);
    digit = strtoul(pbuf, &str_end, 10);
    bigint_set_int(bdigit, digit);          // bdigit = digit;
    bigint_iadd(bi, bdigit);                // bi += bdigit;
    pstr += nfirst;

    // do the rest in chunks of 10^9 to speed up the read-in time
    while (*pstr) {
        memcpy(pbuf, pstr, 9);
        digit = strtoul(pbuf, &str_end, 10);
        bigint_set_int(bdigit, (TEMP_TYPE)digit);       // bdigit = digit;
        bigint_imul(bi, bttt9);                         // bi *= 10^9;
        bigint_iadd(bi, bdigit);                        // bi += bdigit;   (something < 10^9)
        pstr += 9;
    }

    bigint_free(bttt9);
    bigint_free(bdigit);
}

char* bigint_to_string(BigInt *b) {
    assert(b != NULL);

    // edge case
    if (bigint_iszero(b)) {
        char *str = malloc(2);
        str = "0\0";
        return str;
    }

    // calculate how long of a string we need
    size_t cap = b->length*2 + 1;
    size_t nchunks = 0;
    WORD_TYPE *chunks = malloc(cap*WORD_SIZE);

    // helper numbers
    size_t len = b->length;
    WORD_TYPE rem;
    BigInt *bi      = bigint_init(len);
    BigInt *bttt9   = bigint_init(len);
    BigInt *brem    = bigint_init(len);
    BigInt *next_bi = bigint_init(len);
    bigint_set_int(bttt9, 1000000000);   // 10^9
    bigint_copy(b, bi);

    // repeat division by 10^9, using the remainder as a decimal digit.
    while (!(bigint_iszero(bi))) {
        bigint_divmod(bi, bttt9, next_bi, brem);
        rem = bigint_to_int(brem);
        chunks[nchunks++] = rem;
        bigint_copy(next_bi, bi);
    }

    // initialize a string
    size_t nbytes = ceil(b->length*8*WORD_SIZE*log10(2)) + 1;
    char *str  = (char*)malloc(nbytes);
    assert(str != NULL);
    char *pstr = str;

    // most significant chunk (variable length)
    i32 nwritten = sprintf(pstr, "%u", chunks[nchunks-1]);
    pstr += nwritten;

    // remaining chunks
    i32 i = nchunks - 1;
    while (i-- > 0) {
        nwritten = sprintf(pstr, "%09u", chunks[i]);
        pstr += nwritten;
    }
    *pstr = '\0';

    bigint_free(next_bi);
    bigint_free(bttt9);
    bigint_free(brem);
    bigint_free(bi);
    free(chunks);

    return str;
}

// Increment a BigInt by 1
void bigint_inc(BigInt *bi) {
    assert(bi != NULL);
    WORD_TYPE res;
    TEMP_TYPE temp;

    // this is a loop in case "res" overflows and needs
    // to carry over into the next word
    for (size_t i = 0; i < bi->length; ++i) {
        temp = (TEMP_TYPE)bi->data[i];
        res  = (WORD_TYPE)(temp + 1);
        bi->data[i] = res;
        if (res > temp) break;
    }
}

// Decrement a BigInt by 1
void bigint_dec(BigInt *bi) {
    assert(bi != NULL);
    WORD_TYPE res, temp;

    // this is a loop in case "res" underflows and needs
    // to borrow from the next word
    for (size_t i = 0; i < bi->length; ++i) {
        temp = bi->data[i];
        res  = temp - 1;
        bi->data[i] = res;
        if (!(res > temp)) break;
    }
}


// Add two BigInts to an output buffer
static void _bigint_add_internal(BigInt *a, BigInt *b, BigInt *c) {
    assert(a != NULL);
    assert(b != NULL);
    assert(c != NULL);

    // zero the output buffer
    if (!(bigint_iszero(c))) bigint_set_zero(c);

    // longest length of both inputs and the output
    size_t maxlen = max(c->length, max(a->length, b->length));

    WORD_TYPE carry = 0;
    WORD_TYPE d1, d2;
    TEMP_TYPE temp;
    // Loop through "words" (elements of "data") from least significant (end) to most (0)
    for (size_t i = 0; i < maxlen; ++i) {
        d1 = 0;
        d2 = 0;
        if (i < a->length) d1 = a->data[i];
        if (i < b->length) d2 = b->data[i];
        temp = (TEMP_TYPE)d1 + d2 + carry;
        if (i < c->length) {
            c->data[i] = (temp & WORD_MAX);    // bitwise and works like a modulo here (but it's faster)
        } else if ((temp & WORD_MAX) != 0) {
            printf("ERROR (_bigint_add_internal) | Output buffer is not large enough to hold the result!");
            exit(1);
        }
        carry = (temp > WORD_MAX);
    }
}

// Wrappers for the public functions
void bigint_add(BigInt *a, BigInt *b, BigInt *c) {
    _bigint_add_internal(a, b, c);
}

// in-place version
void bigint_iadd(BigInt *a, BigInt *b) {
    // temporary output buffer
    assert(a != NULL);
    BigInt *temp = bigint_init(a->length);
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
    if (!(bigint_iszero(c))) bigint_set_zero(c);

    // longest length of both inputs and the output
    size_t maxlen = max(c->length, max(a->length, b->length));

    WORD_TYPE borrow = 0;
    TEMP_TYPE temp1, temp2, tempr;
    // Loop through "words" (elements of "data") from least significant (end) to most (0)
    for (size_t i = 0; i < maxlen; ++i) {
        temp1 = (TEMP_TYPE)WORD_MAX + 1;
        temp2 = (TEMP_TYPE)borrow;
        if (i < a->length) temp1 = (TEMP_TYPE)a->data[i] + (WORD_MAX + 1);  // add WORD_MAX to allow subtraction with uints
        if (i < b->length) temp2 = (TEMP_TYPE)b->data[i] + borrow;
        tempr = (temp1 - temp2);
        if (i < c->length) {
            c->data[i] = (WORD_TYPE)(tempr & WORD_MAX);    // bitwise and works like a modulo here (but it's faster)
        } else if ((WORD_TYPE)(tempr & WORD_MAX) != 0) {
            printf("ERROR (_bigint_sub_internal) | Output buffer is not large enough to store the result!");
            exit(1);
        }
        borrow = (tempr <= WORD_MAX);
    }
}

void bigint_sub(BigInt *a, BigInt *b, BigInt *c) {
    _bigint_sub_internal(a, b, c);
}

void bigint_isub(BigInt *a, BigInt *b) {
    // temporary output buffer
    assert(a != NULL);
    BigInt *temp = bigint_init(a->length);
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
    if (!(bigint_iszero(c))) bigint_set_zero(c);

    // longest length of both inputs and the output
    size_t maxlen = max(c->length, max(a->length, b->length));

    BigInt *bi_row  = bigint_init(maxlen); 
    BigInt *bi_temp = bigint_init(maxlen);
    WORD_TYPE d1, d2;
    TEMP_TYPE temp;

    // just do the simple multiplication algorithm where we go through each digit
    for (size_t i = 0; i < maxlen; ++i) {
        bigint_set_zero(bi_row);
        assert(bi_row != NULL);
        for (size_t j = 0; j < maxlen; ++j) {
            d1 = 0;
            d2 = 0;
            if (i < a->length) d1 = a->data[i];
            if (j < b->length) d2 = b->data[j]; 
            temp = (TEMP_TYPE)d1 * d2;
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
    BigInt *temp = bigint_init(a->length);
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
    if (!(bigint_iszero(quotient)))  bigint_set_zero(quotient);
    if (!(bigint_iszero(remainder))) bigint_set_zero(remainder);

    // longest length of both inputs and the output
    size_t maxlen = dividend->length;

    for (i32 wordn = maxlen-1; wordn >= 0; --wordn) {
        for (i32 bitn = 31; bitn >= 0; --bitn) {
            _lshift_1bit(remainder);                // remainder <<= 1;
            // set the 0th bit of remainder to the ith bit of dividend
            // check the value of the ith bit of dividend
            bool bit = bit_check(dividend->data[wordn], bitn);
            // set it to the 0th bit of remainder
            remainder->data[0] = bit_set(remainder->data[0], 0, bit);
            if (bigint_compare(remainder, divisor) != SMALLER) {        // if (remainder >= divisor)
                bigint_isub(remainder, divisor);                        // remainder -= divisor;
                // set the ith bit of quotient to 1
                quotient->data[wordn] = bit_set(quotient->data[wordn], bitn, 1);
            }
        }
    }
}

// do divmod and throw away the remainder
static void _bigint_div_internal(BigInt *dividend, BigInt *divisor, BigInt *quotient) {
    assert(quotient  != NULL);
    BigInt *remainder = bigint_init(quotient->length);
    bigint_divmod(dividend, divisor, quotient, remainder);
    bigint_free(remainder);
}

void bigint_div(BigInt *dividend, BigInt *divisor, BigInt *quotient) {
    _bigint_div_internal(dividend, divisor, quotient);
}

void bigint_idiv(BigInt *dividend, BigInt *divisor) {
    // temporary output buffer
    assert(dividend != NULL);
    BigInt *temp = bigint_init(dividend->length);
    _bigint_div_internal(dividend, divisor, temp);
    // copy temp into dividend
    bigint_copy(temp, dividend);
    // release temp
    bigint_free(temp);
}

// do divmod and throw away the quotient
static void _bigint_mod_internal(BigInt *dividend, BigInt *divisor, BigInt *remainder) {
    assert(remainder  != NULL);
    BigInt *quotient = bigint_init(remainder->length);
    bigint_divmod(dividend, divisor, quotient, remainder);
    bigint_free(quotient);
}

void bigint_mod(BigInt *dividend, BigInt *divisor, BigInt *remainder) {
    _bigint_mod_internal(dividend, divisor, remainder);
}

void bigint_imod(BigInt *dividend, BigInt *divisor) {
    // temporary output buffer
    assert(dividend != NULL);
    BigInt *temp = bigint_init(dividend->length);
    _bigint_mod_internal(dividend, divisor, temp);
    // copy temp into dividend
    bigint_copy(temp, dividend);
    // release temp
    bigint_free(temp);
}

// compare two bigints
i8 bigint_compare(BigInt *in1, BigInt *in2) {
    size_t i = max(in1->length, in2->length);
    while (i != 0) {
        --i;
        if ((i >= in1->length) && (i <  in2->length) && (in2->data[i] > 0))
            return SMALLER;
        else if ((i <  in1->length) && (i >= in2->length) && (in1->data[i] > 0))
            return LARGER;
        else if ((i <  in1->length) && (i <  in2->length) && (in1->data[i] > in2->data[i]))
            return LARGER;
        else if ((i <  in1->length) && (i <  in2->length) && (in1->data[i] < in2->data[i]))
            return SMALLER;
    }
    return EQUAL;
}

bool bigint_iszero(BigInt *bi) {
    bool iszero = true;
    for (size_t i = 0; i < bi->length; ++i) 
        iszero = iszero && (bi->data[i] == 0);
    return iszero;
}

// Destructor function
void bigint_free(BigInt *bi) {
    free(bi->data);
    free(bi);
}
