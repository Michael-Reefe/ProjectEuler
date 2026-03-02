#include "bigint.h"

// Initializer function
BigInt* init_BigInt(size_t nbytes) {
    BigInt *bi = (BigInt*)malloc(sizeof(BigInt));
    assert(bi != NULL);
    SArray_u32 *data = init_SArray_u32(nbytes/4);  // one u32 is 4 bytes
    // initialize all zeros in the array
    bi->data = data;
    bigint_set_zero(bi);
    return bi;
}

void bigint_set_zero(BigInt *bi) {
    for (size_t i = 0; i < bi->data->length; ++i) bi->data->arr[i] = 0;
}

// Resize function
void resize_BigInt(BigInt *bi, size_t new_nbytes) {
    assert(bi != NULL);
    resize_SArray_u32(bi->data, new_nbytes/4);
}

// left-shift the words in a bigint by nwords
void _lshift_word(BigInt *bi, u32 nwords) {
    assert(bi != NULL);
    for (i32 i = bi->data->length-1; i >= 0; --i) {
        if (i >= nwords) 
            bi->data->arr[i] = bi->data->arr[i - nwords];
        else 
            bi->data->arr[i] = 0;  // zero-pad shifted words
    }
}

// left-shift everything by 1 bit
void _lshift_1bit(BigInt *bi) {
    assert(bi != NULL);
    for (size_t i = bi->data->length-1; i > 0; --i) {
        bi->data->arr[i] = (bi->data->arr[i] << 1) | (bi->data->arr[i-1] >> ((32) - 1));
    }
    bi->data->arr[0] <<= 1;
}

// right-shift the words in a bigint by nwords
void _rshift_word(BigInt *bi, u32 nwords) {
    assert(bi != NULL);
    for (i32 i = 0; i < bi->data->length; ++i) {
        if (i < bi->data->length - nwords) 
            bi->data->arr[i] = bi->data->arr[i + nwords];
        else
            bi->data->arr[i] = 0;  // zero-pad shifted words
    }
}

// right-shift everything by 1 bit
void _rshift_1bit(BigInt *bi) {
    assert(bi != NULL);
    for (size_t i = 0; i < bi->data->length-1; ++i) {
        bi->data->arr[i] = (bi->data->arr[i] >> 1) | (bi->data->arr[i+1] << ((32) - 1));
    }
    bi->data->arr[bi->data->length-1] >>= 1;
}

// copy a bigint from src to dst
void bigint_copy(BigInt *src, BigInt *dst) {
    assert(src != NULL);
    assert(dst != NULL);
    size_t minlen = min(src->data->length, dst->data->length);
    for (size_t i = 0; i < minlen; ++i) dst->data->arr[i] = src->data->arr[i];
}

// Initialize from an integer
BigInt* bigint_from_int(u64 num) {
    // initialize with 8 bytes so we can safely store a u64
    BigInt *bi = init_BigInt(8);  
    bigint_set_int(bi, num);
    return bi;
}

void bigint_set_int(BigInt *bi, u64 num) {
    assert(bi != NULL);
    assert(bi->data->length >= 2);
    // split into lower 4 bytes and upper 4 bytes
    bi->data->arr[0] = num;             // lower bytes (the "end" of the number, assuming little-endian)
    bi->data->arr[1] = (num >> 32);     // upper bytes (the "beginning" of the number, assuming little-endian)
}

// Convert to an integer
u64 bigint_to_int(BigInt *bi) {
    assert(bi != NULL);
    u64 out = bi->data->arr[0];  // we will lose data if bi is larger than 64 bits :(
    free_BigInt(bi);
    return out;
}

// Initialize from a string (MUST BE NULL-TERMINATED)
BigInt* bigint_from_string(char *str) {
    assert(str != NULL);

    // calculate how many bytes we need to store this int
    size_t ndigits = strlen(str);
    size_t nbytes = ceil((ndigits/log10(2))/8) + 4;

    // store a few bigints for doing math
    BigInt *bout   = init_BigInt(nbytes);
    BigInt *btemp  = init_BigInt(nbytes);
    BigInt *bten   = init_BigInt(nbytes);
    BigInt *bdigit = init_BigInt(nbytes);
    u32 digit;
    bigint_set_int(bten, 10);

    for (size_t nd = 0; nd < ndigits; ++nd) {
        bigint_mul(bout, bten, btemp);
        digit = (*(str++)-'0');
        bigint_set_int(bdigit, digit);
        bigint_add(btemp, bdigit, bout);
    }
    bigint_copy(btemp, bout);

    free_BigInt(btemp);
    free_BigInt(bten);
    free_BigInt(bdigit);

    return bout;
}

char* bigint_to_string(BigInt *bi) {
    assert(bi != NULL);

    // calculate how long of a string we need
    size_t nbytes = ceil(bi->data->length*32*log10(2)) + 1;

    // initialize a string of zeros
    char *str = (char*)malloc(nbytes);
    assert(str != NULL);
    // for (i64 si = 0; si < nbytes; ++si) str[si] = '0';
    // str[nbytes-1] = 0;

    BigInt *bzero   = init_BigInt(bi->data->length*4);
    BigInt *bten    = init_BigInt(bi->data->length*4);
    BigInt *brem    = init_BigInt(bi->data->length*4);
    BigInt *next_bi = init_BigInt(bi->data->length*4);
    bigint_set_zero(bzero);
    bigint_set_int(bten, 10);

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

    free_BigInt(next_bi);
    free_BigInt(bzero);
    free_BigInt(bten);
    free_BigInt(brem);
    free_BigInt(bi);

    return str;
}


// Add two BigInts to an output buffer
void bigint_add(BigInt *in1, BigInt *in2, BigInt *out) {
    assert(in1 != NULL);
    assert(in2 != NULL);
    assert(out != NULL);

    // shortest length of both inputs and the output
    // size_t minlen = min(out->data->length, min(in1->data->length, in2->data->length));
    // longest length of both inputs and the output
    size_t maxlen = max(out->data->length, max(in1->data->length, in2->data->length));

    u32 carry = 0;
    u32 d1, d2;
    u64 temp;
    // Loop through "words" (elements of "data") from least significant (end) to most (0)
    for (size_t i = 0; i < maxlen; ++i) {
        d1 = 0;
        d2 = 0;
        if (i < in1->data->length) d1 = in1->data->arr[i];
        if (i < in2->data->length) d2 = in2->data->arr[i];
        temp = (u64) d1 + d2 + carry;
        out->data->arr[i] = (temp & WORD_MAX_VAL);    // bitwise and works like a modulo here (but it's faster)
        carry = (temp > WORD_MAX_VAL);
    }
}

// Subtract two BigInts to an output buffer
void bigint_sub(BigInt *in1, BigInt *in2, BigInt *out) {
    assert(in1 != NULL);
    assert(in2 != NULL);
    assert(out != NULL);

    // shortest length of both inputs and the output
    // size_t minlen = min(out->data->length, min(in1->data->length, in2->data->length));
    // longest length of both inputs and the output
    size_t maxlen = max(out->data->length, max(in1->data->length, in2->data->length));

    u32 borrow = 0;
    u64 temp1, temp2, tempr;
    // Loop through "words" (elements of "data") from least significant (end) to most (0)
    for (size_t i = 0; i < maxlen; ++i) {
        temp1 = (u64)0 + (u64)WORD_MAX_VAL + 1;
        temp2 = (u64)0 + borrow;
        if (i < in1->data->length) temp1 = (u64)in1->data->arr[i] + (WORD_MAX_VAL + 1);  // add WORD_MAX_VAL to allow subtraction with uints
        if (i < in2->data->length) temp2 = (u64)in2->data->arr[i] + borrow;
        tempr = (temp1 - temp2);
        out->data->arr[i] = (u32)(tempr & WORD_MAX_VAL);    // bitwise and works like a modulo here (but it's faster)
        borrow = (tempr <= WORD_MAX_VAL);
    }
}


// Multiply two BigInts to an output buffer
void bigint_mul(BigInt *in1, BigInt *in2, BigInt *out) {
    assert(in1 != NULL);
    assert(in2 != NULL);
    assert(out != NULL);

    // zero the output buffer
    bigint_set_zero(out);

    // shortest length of both inputs and the output
    // size_t minlen = min(out->data->length, min(in1->data->length, in2->data->length));
    // longest length of both inputs and the output
    size_t maxlen = max(out->data->length, max(in1->data->length, in2->data->length));

    // ensure output buffer is zeroed
    for (size_t i = 0; i < out->data->length; ++i) out->data->arr[i] = 0;

    BigInt *bi_row  = init_BigInt(maxlen*4); 
    BigInt *bi_temp = init_BigInt(maxlen*4);
    u32 d1, d2;
    u64 temp;

    // just do the simple multiplication algorithm where we go through each digit
    for (size_t i = 0; i < maxlen; ++i) {
        bigint_set_zero(bi_row);
        assert(bi_row != NULL);
        for (size_t j = 0; j < maxlen; ++j) {
            d1 = 0;
            d2 = 0;
            if (i < in1->data->length) d1 = in1->data->arr[i];
            if (j < in2->data->length) d2 = in2->data->arr[j]; 
            temp = (u64)d1 * (u64)d2;
            bigint_set_int(bi_temp, temp);        // create temporary bigint for this individual word mult
            _lshift_word(bi_temp, i+j);           // left shift by i+j words to align for the addition
            bigint_add(bi_temp, bi_row, bi_row);  // add bi_temp to bi_row
        }
        bigint_add(bi_row, out, out);             // add bi_row to out
    }

    free_BigInt(bi_row);
    free_BigInt(bi_temp);
}

// Divide two BigInts to an output buffer
void bigint_div(BigInt *in1, BigInt *in2, BigInt *quotient) {
    assert(in1 != NULL);
    assert(in2 != NULL);
    assert(quotient  != NULL);

    // zero the output buffers
    for (size_t i = 0; i <  quotient->data->length; ++i)  quotient->data->arr[i] = 0;

    // longest length of both inputs and the output
    size_t maxlen = max(quotient->data->length, max(in1->data->length, in2->data->length));

    // initialize
    BigInt *bzero   = init_BigInt(maxlen*4);
    BigInt *current = init_BigInt(maxlen*4);
    BigInt *divisor = init_BigInt(maxlen*4);
    BigInt *temp    = init_BigInt(maxlen*4);
    bigint_set_int(bzero,   0);
    bigint_set_int(current, 1);
    bigint_copy(in2, divisor);
    bigint_copy(in1, temp);

    u8 overflow = 0;
    const u64 half_max = 1 + (WORD_MAX_VAL / 2);
    while (bigint_compare(divisor, in1) != LARGER) {    // i.e. while denominator is less than or equal to in1
        // check for overflows
        if (divisor->data->arr[maxlen-1] >= half_max) {
            overflow = 1;
            printf("ERROR: bigint_div has overflowed!\n");
            break;
        }
        _lshift_1bit(current);   // current <<= 1;
        _lshift_1bit(divisor);   // divisor <<= 1;
    }
    if (!overflow) {
        _rshift_1bit(divisor);   // divisor >>= 1;
        _rshift_1bit(current);   // current >>= 1;
    }

    while (bigint_compare(current, bzero) != EQUAL) {           // i.e. while current is not 0
        if (bigint_compare(temp, divisor) != SMALLER) {         // if dividend >= divisor;
            bigint_sub(temp, divisor, temp);                    // dividend -= divisor;
            bigint_or(current, quotient, quotient);             // quotient |= current;
        }
        _rshift_1bit(current);   // current >>= 1;
        _rshift_1bit(divisor);   // divisor >>= 1;
    }

    // free memory
    free_BigInt(bzero);
    free_BigInt(current);
    free_BigInt(divisor);
    free_BigInt(temp);
}

void bigint_divmod(BigInt *in1, BigInt *in2, BigInt *quotient, BigInt *remainder) {
    size_t maxlen = max(quotient->data->length, max(in1->data->length, in2->data->length));
    BigInt *temp = init_BigInt(maxlen*4);

    bigint_div(in1, in2, quotient);
    bigint_mul(quotient, in2, temp);
    bigint_sub(in1, temp, remainder);

    free_BigInt(temp);
}

// bitwise or
void bigint_or(BigInt *in1, BigInt *in2, BigInt *out) {
    assert(in1 != NULL);
    assert(in2 != NULL);
    assert(out != NULL);
    assert(in1->data->length == in2->data->length);

    for (size_t i = 0; i < in1->data->length; ++i) {
        out->data->arr[i] = in1->data->arr[i] | in2->data->arr[i];
    }
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
void free_BigInt(BigInt *bi) {
    free_SArray_u32(bi->data);
    free(bi);
}