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
    typedef ptrdiff_t ptrdf;

#endif // CTYPES_H

#ifndef PROJECTEULERC_UTILS
#define PROJECTEULERC_UTILS

    #include <stdlib.h>
    #include <stdio.h>
    #include <math.h>
    #include <assert.h>

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
    u64 ndivisors(u64 num);

    // "SArrays" -- sized arrays which hold a length value
    #define ARRAY_TYPES(X) \
        X(i8 ) \
        X(i16) \
        X(i32) \
        X(i64) \
        X(u8 ) \
        X(u16) \
        X(u32) \
        X(u64) \
        X(f32) \
        X(f64)

    #define GEN_SIZED_ARRAY(type)           \
        typedef struct _SArray_##type {     \
            type*  arr;                     \
            size_t length;                  \
        } SArray_##type;
    ARRAY_TYPES(GEN_SIZED_ARRAY)

    #define GEN_SIZED_ARRAY2D(type)         \
        typedef struct _SArray2D_##type {   \
            type** arr;                     \
            size_t len1;                    \
            size_t len2;                    \
        } SArray2D_##type;
    ARRAY_TYPES(GEN_SIZED_ARRAY2D)

    // Functions for SArrays
    #define __GEN_SARRAY_INIT(type) \
        SArray_##type* init_SArray_##type(size_t length);
    ARRAY_TYPES(__GEN_SARRAY_INIT)

    #define __GEN_SARRAY2D_INIT(type) \
        SArray2D_##type* init_SArray2D_##type(size_t len1, size_t len2);
    ARRAY_TYPES(__GEN_SARRAY2D_INIT)

    #define __GEN_SARRAY_RESIZE(type) \
        void resize_SArray_##type(SArray_##type *sarray, size_t new_length);
    ARRAY_TYPES(__GEN_SARRAY_RESIZE)

    #define __GEN_SARRAY2D_RESIZE(type) \
        void resize_SArray2D_##type(SArray2D_##type *s2d, size_t new_len1, size_t new_len2);
    ARRAY_TYPES(__GEN_SARRAY2D_RESIZE)

    #define __GEN_SARRAY_DEST(type) \
        void free_SArray_##type(SArray_##type *sarray); 
    ARRAY_TYPES(__GEN_SARRAY_DEST)

    #define __GEN_SARRAY2D_DEST(type) \
        void free_SArray2D_##type(SArray2D_##type *s2d); 
    ARRAY_TYPES(__GEN_SARRAY2D_DEST)

    // Prime sieve functions
    SArray_u64* sieve_of_eratosthenes(u64 n);
    void segmented_sieve_step(u64 n, u64 chunksize, SArray_u64 *primes);

    // Simple math macros

    // max and min
    #ifdef max
    #undef max
    #endif // max
    #define max(a,b) (((a) > (b)) ? (a) : (b))

    #ifdef min
    #undef min
    #endif //min
    #define min(a,b) (((a) < (b)) ? (a) : (b))

#endif // PROJECTEULERC_UTILS
