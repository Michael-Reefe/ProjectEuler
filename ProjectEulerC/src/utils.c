#include <stdio.h>
#include <math.h>
#include "utils.h"

/*

This utils module contains various functions that will be
useful for many problems in Project Euler.

*/

// PrimeFactor initializers and destructors
PrimeFactorIterator *initialize_prime_factor_iterator(u64 number) {
    PrimeFactorIterator *it = (PrimeFactorIterator*)malloc(sizeof(PrimeFactorIterator));
    it->nreduced   = number;
    it->candidate  = 3;
    it->primelimit = (u64)sqrt((f64)number);
    it->stop       = 0;
    return it;
}

void destroy_prime_factor_iterator(PrimeFactorIterator *it) {
    free(it);
}

// SArray initializers 
#define GEN_SARRAY_INIT(type)                                                   \
    SArray_##type* init_SArray_##type(size_t length) {                          \
        SArray_##type *sarray = (SArray_##type*)malloc(sizeof(SArray_##type));  \
        assert(sarray != NULL);                                                 \
        type *arr = (type*)malloc(length*sizeof(type));                         \
        assert(arr != NULL);                                                    \
        sarray->arr = arr;                                                      \
        sarray->length = length;                                                \
        return sarray;                                                          \
    }
ARRAY_TYPES(GEN_SARRAY_INIT)

// SArray resize
#define GEN_SARRAY_RESIZE(type)                                                     \
    void resize_SArray_##type(SArray_##type *sarray, size_t new_length) {           \
        type *newarr = (type*)realloc(sarray->arr, new_length*sizeof(type));        \
        assert(newarr != NULL);                                                     \
        sarray->arr = newarr;                                                       \
        sarray->length = new_length;                                                \
    }
ARRAY_TYPES(GEN_SARRAY_RESIZE)

// SArray destructors
#define GEN_SARRAY_DEST(type)                           \
    void free_SArray_##type(SArray_##type *sarray) {    \
        free(sarray->arr);                              \
        free(sarray);                                   \
    }
ARRAY_TYPES(GEN_SARRAY_DEST)

// This function calculates the prime factorization of a number,
// returning it as a PrimeFactorization object, which is just two 
// linked lists containing the prime factors and exponents
PrimeFactor prime_iterate(PrimeFactorIterator *it) {

    // Default value
    PrimeFactor pf;
    pf.factor = 2;
    pf.exponent = 0;

    // Error handling
    if (it->stop == 1) {
        printf("ERROR: PrimeFactorIterator iterated too many times!");
        exit(1);
    }

    // Edge case
    if (it->nreduced < 2) {

        // Tell the iterator that we should stop
        it->stop = 1;
        return pf;
    }

    // Remove factors of 2 first
    if (it->nreduced % 2 == 0) {
        while (it->nreduced % 2 == 0) {
            it->nreduced /= 2;
            pf.exponent += 1;
        }
        it->primelimit = (u64)sqrt((f64)it->nreduced);
        it->candidate = 3;
        return pf;
    }

    // We will find the prime factors by trial division, in other words
    // just checking every number to see if it evenly divides the target.
    while (it->nreduced > 1) {
        // if candidate ever exceeds primelimit, then we know that
        // the remaining "nreduced" must be a prime, so we can stop
        if (it->candidate > it->primelimit + 1) {
            pf.factor = it->nreduced;
            pf.exponent = 1;
            it->nreduced = 1;
            it->stop = 1;
            return pf;
        }
        // see if candidate evenly divides number 
        if (it->nreduced % it->candidate == 0) {
            pf.factor = it->candidate;
            pf.exponent = 0;
            while (it->nreduced % it->candidate == 0) {
                // update the running division result
                it->nreduced /= it->candidate;
                pf.exponent += 1;
            }
            it->primelimit = (u64)sqrt((f64)it->nreduced);
            it->candidate += 2;
            return pf;
        }
        // increment candidate by 2 since all factors of 2 have already been removed
        it->candidate += 2;
    }

    // If we ever reach the end of the while loop, we know we have found all factors and can stop
    it->stop = 1;

    return pf;
}

// Implement the Sieve of Eratosthenes algorithm to generate all primes <= n
// !! THIS FUNCTION ALLOCATES AN SARRAY !!
SArray_u64* sieve_of_eratosthenes(u64 n) {
    // a boolean array that will keep track of which numbers are prime
    u8 primemask[n+1];
    // initialize as all 1s
    for (u64 i = 0; i < n+1; ++i) primemask[i] = 1;

    // to make interpretation easier, the index will equal the number that
    // is being marked as prime.  0 and 1 are not prime:
    primemask[0] = 0;
    primemask[1] = 0;

    /* this is a well known algorithm that works by marking all of the
        multiples of every number less than sqrt(n) as composite, thereby
        leaving the remaining numbers as the primes */
    u64 primelimit = (u64)sqrt((f64)n);
    for (u64 i = 2; i <= primelimit; ++i) {
        if (primemask[i] == 1) {
            for (u64 j = i*i; j <= n; j += i) {
                primemask[j] = 0;
            }
        }
    }

    // now, allocate an array to hold all of the primes found
    size_t nprimes = (size_t)i_sum(primemask, n+1);
    SArray_u64 *primes = init_SArray_u64(nprimes);

    u32 j = 0;
    for (u64 i = 0; i < n+1; ++i) {
        if (primemask[i] == 1) {
            assert(j < primes->length);
            primes->arr[j] = i;
            j += 1;
        }
    }

    return primes;
}

// an iteration of the segmented sieve algorithm, which allows us to
// find primes efficiently without having to use massive boolean arrays
void segmented_sieve_step(u64 n, u64 chunksize, SArray_u64 *primes) {

    // n is the FIRST integer to check
    // m is the LAST integer to check
    u64 m = n + chunksize - 1;
    // initialize everything as prime at first like the regular sieve
    u8 primemask[chunksize];
    for (u32 i = 0; i < chunksize; ++i) primemask[i] = 1;

    size_t n_primes = primes->length;
    u64 primelimit = (u64)sqrt((f64)m);
    for (u64 i = 0; i < n_primes; ++i) {
        u64 p = primes->arr[i];
        if (p > primelimit) break;
        // j enumerates the multiples of p within the range (n, m)
        for (u64 j = n - n % p; j <= m - m % p; j += p) {
            if (j < n) continue;
            assert((j-n < chunksize));
            primemask[j-n] = 0;
        }
    }

    // how many new primes did we find?
    size_t n_newprimes = (size_t)i_sum(primemask, chunksize);

    // reallocate the primes array to hold the new elements
    resize_SArray_u64(primes, n_primes + n_newprimes);

    // fill up the new values with our newly found primes
    size_t j = n_primes;
    for (u64 i = 0; i < chunksize; ++i) {
        if (primemask[i] == 1) {
            assert(j < primes->length);
            primes->arr[j] = i + n;
            j += 1;
        }
    }
}