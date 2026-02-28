#ifndef CTYPES_H
#define CTYPES_H

    #include <stdint.h>
    #include <stddef.h>
    #include <stdbool.h>

    typedef int8_t i8;
    typedef int16_t i16;
    typedef int32_t i32;
    typedef int64_t i64;

    typedef uint8_t u8;
    typedef uint16_t u16;
    typedef uint32_t u32;
    typedef uint64_t u64;

    typedef float f32;
    typedef double f64;

    typedef uintptr_t uptr;
    typedef ptrdiff_t ptrdiff;

#endif // CTYPES_H

#ifndef PROJECTEULERC_UTILS
#define PROJECTEULERC_UTILS

    #include <stdlib.h>

    // A prime factorization iterator structure.
    // Like in the Julia version, this is conceptually an iterator
    // that, at any given time, holds a state vector containing 
    // information about the prime factorization calculation
    typedef struct _PrimeFactorIterator {
        u64 nreduced;
        u64 primelimit;
        u64 candidate;
        u8  stop;
    } PrimeFactorIterator;

    // This PrimeFactor structure, meanwhile, holds the result of one
    // step in the iteration process (the factor itself, and the exponent)
    typedef struct _PrimeFactor {
        u64 factor;
        u64 exponent;
    } PrimeFactor;

    // Functions for PrimeFactorizations
    PrimeFactorIterator *initialize_prime_factor_iterator(uint64_t number);
    void destroy_prime_factor_iterator(PrimeFactorIterator *it);
    PrimeFactor prime_iterate(PrimeFactorIterator *it);

#endif
